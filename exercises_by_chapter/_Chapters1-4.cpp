#include <chrono>
#include <iostream>
#include <Windows.h>


struct SimpleString {
	SimpleString(size_t max) : max_size{ max }, length{} {
		if (max_size < 1) {
			throw std::runtime_error("String size must be at least 1.");
		}
		buffer = new char[max_size];
		buffer[0] = 0;
	}

	~SimpleString() {
		delete[] buffer;
	}

	//Copy constructor
	SimpleString(const SimpleString& other) : max_size{ other.max_size },
		length{ other.length }, buffer{ new char[other.max_size] }
	{
		std::strncpy(buffer, other.buffer, max_size);
	}

	//Copy assignment
	SimpleString& operator=(const SimpleString& other) {
		if (&other == this) return *this;
		const auto new_buffer = new char[other.max_size];
		delete[] buffer;
		this->buffer = new_buffer;
		this->max_size = other.max_size;
		this->length = other.length;
		std::strncpy(buffer, other.buffer, max_size);
		return *this;
	}

	//Move constructor
	SimpleString(SimpleString&& other) noexcept : max_size{ other.max_size },
		length{ other.length }, buffer{ other.buffer }
	{
		other.buffer = nullptr;
		other.length = 0;
		other.max_size = 0;
	}

	//Move assignment
	SimpleString& operator=(SimpleString&& other) noexcept
	{
		if (&other == this)return *this;
		delete[] this->buffer;
		this->buffer = other.buffer;
		this->max_size = other.max_size;
		this->length = other.length;
		other.buffer = nullptr;
		other.length = 0;
		other.max_size = 0;
		return *this;
	}

	bool appendLine(const char* x) {
		auto x_len = strlen(x);
		if (x_len + length + 2 > max_size) return false;
		std::strncpy(buffer + length, x, max_size - length);//Check max-size - length = x_len ? NO
		length += x_len;
		buffer[length++] = '\n';
		buffer[length++] = 0;
		return true;
	}

	void print(const char* tag) {
		printf("%s: %s", tag, buffer);
	}

private:
	size_t max_size;
	char* buffer;
	size_t length;
};


struct Timer
{
	Timer(const char* i_name) : name{ i_name } {
		printf("%s constructed\n", name);
		timestamp = std::chrono::system_clock::now();
		dead = false;
	}

	Timer(const Timer& other) :name{ other.name } {
		printf("Copy Constructor\n");
		this->timestamp = other.timestamp;
		dead = false;
	}

	Timer& operator=(const Timer& other) {
		printf("Copy Assignment\n");
		if (this == &other) return *this;
		this->name = other.name;
		this->timestamp = other.timestamp;
		return *this;
	}

	Timer(Timer&& other) noexcept {
		printf("Move Constructor\n");
		this->timestamp = other.timestamp;
		this->name = other.name;
		other.dead = true;
	}

	Timer& operator=(Timer&& other) noexcept {
		printf("Move Asignment\n");
		if (this == &other) return *this;
		this->timestamp = other.timestamp;
		this->name = other.name;
		other.dead = true;
		return *this;
	}

	~Timer() {
		if (dead == false) {//Moved from 
			std::chrono::time_point<std::chrono::system_clock> end_timestamp = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = end_timestamp - timestamp;
			std::cout << "Elapsed time for " << this->name << " is: " << elapsed_seconds.count() << "s\n";
		}
	}

	const char* name;
	std::chrono::time_point<std::chrono::system_clock> timestamp;
	bool dead = false;
};

void tester() {
	Timer t{ "Test timer" };
	Sleep(3000);//Miliseconds
}

int main() {
	Timer t{ "Timer A" };

	SimpleString a{ 50 };
	a.appendLine("We apologise for the");
	SimpleString b{ 50 };
	b.appendLine("Last message");
	SimpleString c(std::move(b));
	a.print("a");
	b.print("b_dead");
	b = std::move(a);
	// a is "moved-from"
	b.print("b");
	c.print("c");
}
