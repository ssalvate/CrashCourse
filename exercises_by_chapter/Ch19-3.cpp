#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// Ch 19.3

#include <queue>
#include <mutex>
#include <array>
#include <future>
#include <condition_variable>

struct TinyObj {
	TinyObj() {}
	TinyObj(std::string id, std::array<int, 5> v) :ID{ id }, values{ v } {}

	std::string ID;
	std::array<int, 5> values;

};

template <typename T>
struct SafeQueue {
	std::condition_variable cv;
	std::queue<T> queue;
	mutable std::mutex mut; //Mutable allows for use in the const methods

	SafeQueue() {}
	~SafeQueue() {}

	void push(T elem) {
		std::lock_guard<std::mutex> lock(mut);
		std::cout << elem << " added to Q" << std::endl;
		queue.push(elem);
		cv.notify_all();
	}

	void pop() {
		std::lock_guard<std::mutex> lock(mut);
		return queue.pop();
	}

	void wait_and_pop() {
		std::unique_lock<std::mutex> lock(mut);
		std::cout << "Pop Check" << std::endl;
		cv.wait(lock);
		cv.wait(lock, [this] {
			return this->queue.size() > 4; //Condition that also must be met, besides wakeup call from cv.notify()
			});
		std::cout << "Wait over" << std::endl;
		queue.pop();
	}

	bool empty() const {
		std::lock_guard<std::mutex> lock(mut);
		return queue.empty();
	}
	size_t size() const {
		std::lock_guard<std::mutex> lock(mut);
		return queue.size();
	}

};

int main() {

	SafeQueue<int> my_Q;

	TinyObj to1{ "First", std::array<int, 5>{1,2,3,4,5} };
	TinyObj to2{ "Second", std::array<int, 5>{5,4,3,2,1} };

	auto tp = std::async(std::launch::async, [&] {
		my_Q.wait_and_pop();
		});
	auto t1 = std::async(std::launch::async, [&] {
		my_Q.push(1);
		my_Q.push(2);
		my_Q.push(3);
		});
	auto t2 = std::async(std::launch::async, [&] {
		my_Q.push(4);
		my_Q.push(5);
		my_Q.push(6);
		my_Q.push(7);
		});
	auto t3 = std::async(std::launch::async, [&] {
		my_Q.push(8);
		my_Q.push(9);
		my_Q.push(10);
		});

	tp.wait();
	t1.wait();
	t2.wait();
	t3.wait();

	std::cout << "Size of Q is : " << my_Q.size() << std::endl;
}