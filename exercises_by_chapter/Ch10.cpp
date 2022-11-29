#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <functional>
#include <stdexcept>

using namespace std;

struct SpeedUpdate {
    double velocity_mps;
};

struct CarDetected {
    double distance_m;
    double velocity_mps;
};

struct SpeedLimitDetected {
    unsigned short speed_mps;
};

struct BrakeCommand {
    double time_to_collision_s;
};

using SpeedUpdateCallback = function<void(const SpeedUpdate&)>;
using CarDetectedCallback = function<void(const CarDetected&)>;
using SpeedLimitCallback = function<void(const SpeedLimitDetected&)>;

struct IServiceBus {
    virtual ~IServiceBus() = default;
    virtual void publish(const BrakeCommand&) = 0;
    virtual void subscribe(SpeedUpdateCallback) = 0;
    virtual void subscribe(CarDetectedCallback) = 0;
    virtual void subscribe(SpeedLimitCallback) = 0;
};

struct MockServiceBus : IServiceBus {
    void publish(const BrakeCommand& cmd) override {
        commands_published++;
        last_command = cmd;
    };
    void subscribe(SpeedUpdateCallback callback) override {
        speed_update_callback = callback;
    };
    void subscribe(CarDetectedCallback callback) override {
        car_detected_callback = callback;
    };
    void subscribe(SpeedLimitCallback callback) override {
        speed_limit_callback = callback;
    };

    BrakeCommand last_command{};
    int commands_published{};
    SpeedUpdateCallback speed_update_callback{};
    CarDetectedCallback car_detected_callback{};
    SpeedLimitCallback speed_limit_callback{};
};

struct AutoBrake {
    AutoBrake(IServiceBus& bus)
        : collision_threshold_s{ 5 }
        , speed_mps{}
        , speed_limit{}{
        bus.subscribe([this](const SpeedUpdate& update) { speed_mps = update.velocity_mps; });
        bus.subscribe([this, &bus](const SpeedLimitDetected& update) {
            speed_limit = update.speed_mps;
            if (speed_mps > speed_limit) bus.publish(BrakeCommand{ .0 });
            });
        bus.subscribe([this, &bus](const CarDetected& cd) {
            auto relative_velocity_mps = speed_mps - cd.velocity_mps;
            auto time_to_collision_s = cd.distance_m / relative_velocity_mps;
            if (time_to_collision_s > 0 && time_to_collision_s <= collision_threshold_s) {
                bus.publish(BrakeCommand{ time_to_collision_s });
            }
            });
    }
    void set_collision_threshold_s(double x) {
        if (x < 1)
            throw runtime_error{ "Collision less than 1." };
        collision_threshold_s = x;
    }
    double get_collision_threshold_s() const {
        return collision_threshold_s;
    }
    double get_speed_mps() const {
        return speed_mps;
    }
    unsigned short get_speed_limit() const {
        return speed_limit;
    }

private:
    double collision_threshold_s;
    double speed_mps;
    unsigned short speed_limit;
};

TEST_CASE("AutoBrake") {
    MockServiceBus bus{};
    AutoBrake auto_brake{ bus };

    SECTION("initializes speed to zero") {
        REQUIRE(auto_brake.get_speed_mps() == Approx(0));
    }

    SECTION("initialize speed limit to 35") {
        bus.speed_limit_callback(SpeedLimitDetected{ 35 });
        REQUIRE(auto_brake.get_speed_limit() == Approx(35));
    }

    SECTION("initializes sensitivity to five") {
        REQUIRE(auto_brake.get_collision_threshold_s() == Approx(5));
    }

    SECTION("throws when sensitivity less than one") {
        REQUIRE_THROWS(auto_brake.set_collision_threshold_s(0.5L));
    }

    SECTION("saves speed after update") {
        bus.speed_update_callback(SpeedUpdate{ 100L });
        REQUIRE(100L == auto_brake.get_speed_mps());
        bus.speed_update_callback(SpeedUpdate{ 50L });
        REQUIRE(50L == auto_brake.get_speed_mps());
        bus.speed_update_callback(SpeedUpdate{ 0L });
        REQUIRE(0L == auto_brake.get_speed_mps());
    }

    SECTION("saves last speed limit after update") {
        bus.speed_limit_callback(SpeedLimitDetected{ 80 });
        REQUIRE(80 == auto_brake.get_speed_limit());
        bus.speed_limit_callback(SpeedLimitDetected{ 65 });
        REQUIRE(65 == auto_brake.get_speed_limit());
        bus.speed_limit_callback(SpeedLimitDetected{ 15 });
        REQUIRE(15 == auto_brake.get_speed_limit());
    }

    SECTION("no alert when not imminent") {
        auto_brake.set_collision_threshold_s(2L);
        bus.speed_update_callback(SpeedUpdate{ 100L });
        bus.car_detected_callback(CarDetected{ 1000L, 50L });
        REQUIRE(bus.commands_published == 0);
    }

    SECTION("no alert when 1 under speed limit") {
        bus.speed_limit_callback(SpeedLimitDetected{ 35 });
        REQUIRE(35 == auto_brake.get_speed_limit());
        REQUIRE(bus.commands_published == 0);
    }

    SECTION("1 alert when over speed limit") {
        bus.speed_update_callback(SpeedUpdate{ 36L });
        REQUIRE(36L == auto_brake.get_speed_mps());
        bus.speed_limit_callback(SpeedLimitDetected{ 35 });
        REQUIRE(35L == auto_brake.get_speed_limit());
        REQUIRE(bus.commands_published == 1);
    }
    SECTION("1 alert when over speed limit after being under it") {
        bus.speed_limit_callback(SpeedLimitDetected{ 35 });
        REQUIRE(35 == auto_brake.get_speed_limit());
        bus.speed_update_callback(SpeedUpdate{ 30L });
        REQUIRE(30L == auto_brake.get_speed_mps());
        bus.speed_limit_callback(SpeedLimitDetected{ 25 });
        REQUIRE(25 == auto_brake.get_speed_limit());
        REQUIRE(bus.commands_published == 1);
    }

    SECTION("alert when imminent") {
        auto_brake.set_collision_threshold_s(10L);
        bus.speed_update_callback(SpeedUpdate{ 100L });
        bus.car_detected_callback(CarDetected{ 100L, 0L });
        assert(bus.commands_published == 1);
        assert(bus.last_command.time_to_collision_s == Approx(1));
    }
}
