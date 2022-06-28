#pragma once

struct PrimeIterator
{
	bool operator!=(int)const;

	PrimeIterator operator++();

	int operator*()const;

	bool isPrime(int);

private:
	int current{ 1 }, last{ 1 };
};

struct PrimeRange
{
	explicit PrimeRange(int);

	PrimeIterator begin() const;

	int end() const;
private:
	const int max;
};