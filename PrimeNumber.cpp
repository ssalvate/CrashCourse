#include "PrimeNumber.h"

bool PrimeIterator::operator!=(int x)const {
	return x >= current;
}

PrimeIterator PrimeIterator::operator++() {
	last = current;
	current++;
	while (!isPrime(current)) {
		current++;
	}
	return *this;
}

int PrimeIterator::operator*()const {
	return current;
}

//function to check if a given number is prime
bool PrimeIterator::isPrime(int n) {
	//since 0 and 1 is not prime return false.
	if (n == 1 || n == 0) return false;

	//Run a loop from 2 to n-1
	for (int i = 2; i < n; i++) {
		// if the number is divisible by i, then n is not a prime number.
		if (n % i == 0) return false;
	}
	//otherwise, n is prime number.
	return true;
}


PrimeRange::PrimeRange(int max) : max{ max } {}

PrimeIterator PrimeRange::begin() const {
	return PrimeIterator{};
}

int PrimeRange::end() const {
	return max;
}
