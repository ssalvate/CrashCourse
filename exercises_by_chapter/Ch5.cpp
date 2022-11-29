#include <cstdio>
#include <map>

struct Logger {
    virtual ~Logger() = default;
    virtual void log_transfer(long from, long to, double amount) = 0;
};

struct ConsoleLogger : Logger {
    ConsoleLogger(const char* s) : prepend{ s } {}

    void log_transfer(long from, long to, double amount) override {
        printf("[cons] %s : %ld -> %ld: %f\n", prepend, from, to, amount);
    }

    const char* prepend;
};

struct FileLogger : Logger {
    void log_transfer(long from, long to, double amount) override {
        printf("[file] %ld,%ld,%f\n", from, to, amount);
    }
};

struct AccountDatabase {

    virtual ~AccountDatabase() = default;

    virtual void setAmount(long id, double amount) = 0;

    virtual double retrieveAmount(long id) = 0;
};


struct InMemoryAccountDatabase : AccountDatabase {

    InMemoryAccountDatabase() {
        printf("InMemoryAccountDatabase created\n");
    }

    void setAmount(long id, double amount) override {
        Map[id] = amount;
    }

    double retrieveAmount(long id) override {
        if (Map.count(id)) return Map[id];
        else return -1.0;
    }

    ~InMemoryAccountDatabase() override {
        printf("Deleting InMemoryAccountDatabase\n");
    }

    std::map<long, double> Map{};

};

struct Bank {

    Bank(AccountDatabase& d, Logger* l) : database{ d }, logger{ l }{}

    void set_logger(Logger* new_logger) {
        logger = new_logger;
    }
    void make_transfer(long from, long to, double amount) {
        if (logger)
            logger->log_transfer(from, to, amount);
    }

private:
    Logger* logger;
    AccountDatabase& database;
};


int main() {
    InMemoryAccountDatabase ad;
    ad.setAmount(1, 300.06);
    ad.setAmount(45600, 600);
    ad.setAmount(2, 400.02);
    double r = ad.retrieveAmount(45600);
    if (r >= -1) printf("Account id 45600: %lf \n", r);
    ConsoleLogger console_logger{ "Console 5" };
    FileLogger file_logger;
    Bank bank{ ad, nullptr };
    bank.set_logger(&console_logger);
    bank.make_transfer(1000, 2000, 49.95);
    bank.set_logger(&file_logger);
    bank.make_transfer(2000, 4000, 20.00);
}
