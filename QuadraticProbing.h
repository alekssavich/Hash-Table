#ifndef QUADRATICPROBING_H
#define QUADRATICPROBING_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int nextPrime(int n);
int hash1(const string& key);
int hash1(int key);

template <typename HashedObj>
class HashTable {
public:
	// pre- makeEmpty must be a valid function.
	// post-  numCollisions, totalChainLength, and longestChain will equal 0.
	explicit HashTable(int size = 101) : array(nextPrime(size)) { // constructor
		makeEmpty();
		numCollisions = 0;
		totalChainLength = 0;
		longestChain = 0;
	}

	// pre- There has to be some input x.
	// post- isActive(findPos(x)) is returned
	bool contains(const HashedObj& x) {
		return isActive(findPos(x));
	}

	// pre- array has info associated to it and has some size
	// post-  all array.info elements equal EMPTY.
	void makeEmpty() { // Make the hash table empty.
		currentSize = 0;
		for (unsigned int i = 0; i < array.size(); i++) {
			array[i].info = EMPTY;
		}
	}

	// pre- There has to be some value x going into the function, currentPos and findPos(x) are of same type.
	// post- currentPos equals findPos(x). numCollisions, totalChainLength, and longestChain equal 0. 
	bool insert(const HashedObj& x) { // Insert item x into the hash table. If the item is already present, then do nothing.
		int currentPos = findPos(x);
		if (isActive(currentPos)) {
			return false;
		}
		array[currentPos] = HashEntry(x, ACTIVE); // inserts x into the hash table in current position and makes it active.
		if (++currentSize > array.size() / 2) { // if the current size + 1 is bigger than half the array size, then rehash and set varaibles back to 0.
			rehash();
			numCollisions = 0;
			totalChainLength = 0;
			longestChain = 0;
		}
		return true;
	}

	// pre- There is some value x being passes in the function. currentPos and findPos(x) are of same type.
	// post- array info at index currentPos equals DELETED
	bool remove(const HashedObj& x) { // Remove item x from the hash table. 
		int currentPos = findPos(x);
		if (!isActive(currentPos)) { // if the isActive function with parameter currentPos returns false then function returns false
			return false;
		}
		array[currentPos].info = DELETED; // else delete currentPos in array and return true.
		return true;
	}

	// pre- all variables are defined.
	// post- none
	void printStatistics() { // Print statistical data from hash table.
		cerr << "Number of words " << currentSize;
		cerr << ", Table Size " << array.size();
		cerr << ", Load Factor " << (double)currentSize / array.size() << endl;
		cerr << "Collisions " << numCollisions;
		cerr << ", Average Chain Length " << (double)totalChainLength / (double)currentSize;
		cerr << ", Longest Chain Length " << longestChain << endl;
	}

	enum EntryType { ACTIVE, EMPTY, DELETED };
private:
	struct HashEntry {
		HashedObj element;
		EntryType info;

		HashEntry(const HashedObj& e = HashedObj(), EntryType i = EMPTY)
			: element(e), info(i) { }
	};

	vector<HashEntry> array;
	int currentSize;
	int chainLength;
	int totalChainLength;
	int numCollisions;
	int longestChain;

	// pre- currentPos is an integer.
	// post- array info at index currentPos equals ACTIVE and is returned.
	bool isActive(int currentPos) const { // Return true if currentPos exists and is active.
		return array[currentPos].info == ACTIVE;
	}

	// pre- currentPos and myhash(x) are of same type.
	// post- currentPos equals myhash(x).offset = 1, chainLength = 1, newWord = true. currentPos += 2, offset += 2, numCollisions++.
	int findPos(const HashedObj& x) { // Method that performs quadratic probing resolution. Return the position where the search for x terminates.
		int offset = 1;
		chainLength = 1;
		bool newWord = true;
		int currentPos = myhash(x);

		while (array[currentPos].info != EMPTY && array[currentPos].element != x) { // While array at position currentPos does not equal EMPTY and the element at currenPos does not equal x, then do the following.
			currentPos += offset;
			offset += 2;
			if (currentPos >= array.size()) {
				currentPos -= array.size();
			}

			if (newWord) { // If you're finding a new word add one to numCollisions and change newWord to false.
				numCollisions++;
				newWord = false;
			}
			chainLength++;
		}

		totalChainLength += chainLength;
		if (chainLength > longestChain) {
			longestChain = chainLength;
		}
		return currentPos;
	}

	// pre- oldArray and array are of same type.
	// post- array info at index j equals EMPTY. if oldArray info at i is ACTIVE then insert oldArray at i element.
	void rehash() { // Expand the hash table.
		vector<HashEntry> oldArray = array; // copying array so you can expand hash table.
		array.resize(nextPrime(2 * oldArray.size())); // take size of hashtable and multiply it by 2.
		for (unsigned int j = 0; j < array.size(); j++) { // for loop starts at 0 and will run until it reaches the value of array.size().
			array[j].info = EMPTY; // will set each hashtable info to EMPTY.
		}

		currentSize = 0;
		for (int i = 0; i < oldArray.size(); i++) {// for loop will copy elements of old array to the new array.
			if (oldArray[i].info == ACTIVE) {
				insert(oldArray[i].element);
			}
		}
	}

	// pre- There is some value of x being passed.
	// post- hashVal equals hash1(x). hashVal %= array.size(). if hashVal is less than 0, then add array.size to hashVal.
	int myhash(const HashedObj& x) const {
		int hashVal = hash1(x);
		hashVal %= array.size();
		if (hashVal < 0) {
			hashVal += array.size();
		}
		return hashVal;
	}
};



#endif



