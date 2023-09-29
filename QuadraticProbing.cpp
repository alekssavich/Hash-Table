#include "QuadraticProbing.h"
#include <iostream>
using namespace std;

// pre- int n is passed
// post- return true or false.
bool isPrime(int n) { // checks if n is a prime number.
	if (n == 2 || n == 3) { // if n is equal to two or three, then n is a prime number
		return true;
	}

	if (n == 1 || n % 2 == 0) { // if n is equal to one or if n modulus 2 equals 0, then n is not a prime number
		return false;
	}

	for (int i = 3; i * i <= n; i += 2) { // will run for loop to check if n is a prime number
		if (n % i == 0) {
			return false;
		}
	}

	return true; // return true otherwise.
}

// pre- int n is passed
// post- n equals 3, add one to n, return n.
int nextPrime(int n) { // finds the next prime number after n.
	if (n <= 0) { // if n is negative or 0, then set n equal to 3.
		n = 3;
	}

	if (n % 2 == 0) { // if n modulus 2 equals 0, then add one to n.
		n++;
	}

	for (; !isPrime(n); n += 2) { // for loop keeps adding 2 to n and checks if n is a prime number and will keep running until it is.
		;
	}

	return n; // return the value of n.
}

// pre- pass key into function.
// post- hashVal equals 0, hashVal equals 37 * hashVal * key at index i.
int hash1(const string& key) {
	int hashVal = 0;

	for (unsigned int i = 0; i < key.length(); i++) {
		hashVal = 37 * hashVal + key[i];
	}

	return hashVal;
}

// pre- pass key into function.
// post- return key.
int hash1(int key) {
	return key;
}


