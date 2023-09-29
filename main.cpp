/*
Author: Aleks Savich
Date Created: 6-1-2019
Date Edited: 6-14-2019
Problem: You're to create a spell checker. Your program will first create a hash table and 
you have to edit the header file and create a main file which will spell chech words from 
a text file and check the hash table if its in there. Your program is to output all the 
words not found in the dictionary and tell you from which line in the text file it was 
in and the correpsonding words that have been edited that are in the dictionary.
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include "QuadraticProbing.h"
using namespace std;

int main(int argc, char* argv[]) {
	char numWords = *argv[1];
	string lineStr;
	string line;
	string word;
	string wordCopy;
	string testWord;
	int numLine = 0;
	ifstream file;
	ofstream ofs;
	HashTable<string> dictionary = HashTable<string>(2 * numWords);
	char alphabet[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };

	file.open(argv[2]); // open dictionary file.

	if (!file.is_open()) {
		cout << "Can not open file.";
		exit(0);
	}

	while (file.good()) { // insert every word in dictionary into hash table.
		file >> word;
		dictionary.insert(word);
	}
	file.close(); // close file
	dictionary.printStatistics(); // print statitics

	file.open(argv[3]); // open jabber.txt file.
	if (!file.is_open()) {
		exit(0);

	}
	while (file.good()) {
		numLine = 0;
		file >> word;
		for (int i = 0; i < word.length(); i++) { // for loop to get rid of non letter characters
			if (!isalpha(word[i])) {
				if (i == 0) { // if first letter is being deleted then do...
					for (int j = i; j < word.length(); j++) { // for loop to delete element at index i and move other elements over to the left by one.
						word[j] = word[j + 1];
					}
					word.resize(word.length() - 1); // resize word to one smaller since letter was deleted.
				}
				else if (i == word.length() - 1) { // if last letter in word is deleted just change the size.
					word.resize(word.length() - 1);
				}
				else {
					for (int j = 0; j < word.length(); j++) { // otherwise move all letters over to the left by one starting from i.
						word[i] = word[i + 1];
					}
					word.resize(word.length() - 1);
				}
			}
		}

		testWord = word;
		testWord[0] = tolower(testWord[0]);

		while (dictionary.contains(testWord) == true) { // if word is already in dictionary then move onto next word
			file >> word;
			for (int i = 0; i < word.length(); i++) { // for loop to get rid of non letter characters
				if (!isalpha(word[i])) { // removes all non letter characters in word.
					if (i == word.length() - 1) { // if non letter charcter is found at last index of word, resize to one size smaller.
						word.resize(word.length() - 1);
					}
					else {
						for (int j = 0; j < word.length(); j++) {
							word[i] = word[i + 1];
						}
						word.resize(word.length() - 1);
					}
				}
			}
			testWord = word;
			testWord[0] = tolower(testWord[0]);
		}

		cout << word << "(" << numLine << ") : ";
		for (int i = 0; i < word.length(); i++) { // for loop to go through each element in string and deletes it.
			wordCopy = word;
			for (int j = i; j < word.length(); j++) { // for loop to delete element at index i and move other elements over to the left by one.
				wordCopy[j] = wordCopy[j + 1];
			}
			wordCopy.resize(wordCopy.length() - 1);

			if (dictionary.contains(wordCopy) == true) {
				cout << wordCopy << " ";
			}

			else {
				for (int k = 0; k < wordCopy.length(); k++) { // if the word is not in the dictionary, take the word and make it all lower case.
					wordCopy[k] = tolower(wordCopy[k]);
				}
				if (dictionary.contains(wordCopy) == true) {
					cout << wordCopy << " ";
				}
			}
		}

		for (int i = 0; i < 26; i++) { // for loop goes through each letter of alphabet
			wordCopy = word;
			wordCopy.resize(word.length() + 1);
			for (int j = 0; j < word.length() + 1; j++) {// goes through each element in word where new character will go
				wordCopy = word;
				for (unsigned long k = word.length(); k > j; k--) { // for loop to move all elements to the right until position is reached.
					wordCopy[k] = wordCopy[k - 1];
				}
				wordCopy[j] = alphabet[i];
				if (dictionary.contains(wordCopy) == true) {
					cout << wordCopy << " ";
				}
				else {
					for (int k = 0; k < wordCopy.length(); k++) { // if the word is not in the dictionary, take the word and make it all lower case.
						wordCopy[k] = tolower(wordCopy[k]);
					}
					if (dictionary.contains(wordCopy) == true) {
						cout << wordCopy << " ";
					}
				}
			}
		}

		for (int i = 0; i < word.length() - 1; i++) { //for loop swaps neighboring elements in the string.
			wordCopy = word; // use wordCopy so actual word isnt changed and can still be used.
			char charCopy = wordCopy[i];
			wordCopy[i] = wordCopy[i + 1];
			wordCopy[i + 1] = charCopy;
			if (dictionary.contains(wordCopy) == true) {
				cout << wordCopy << " ";
			}
			else {
				for (int k = 0; k < wordCopy.length(); k++) { // if the word is not in the dictionary, take the word and make it all lower case.
					wordCopy[k] = tolower(wordCopy[k]);
				}
				if (dictionary.contains(wordCopy) == true) {
					cout << wordCopy << " ";
				}
			}
		}

		for (int i = 0; i < 26; i++) { // for loop replaces each element in array with every letter in the alphabet.
			for (int j = 0; j < word.length(); j++) {
				wordCopy = word;
				wordCopy[j] = alphabet[i];
				if (dictionary.contains(wordCopy) == true) {
					cout << wordCopy << " ";
				}
				else {
					for (int k = 0; k < wordCopy.length(); k++) { // if the word is not in the dictionary, take the word and make it all lower case.
						wordCopy[k] = tolower(wordCopy[k]);
					}
					if (dictionary.contains(wordCopy) == true) {
						cout << wordCopy << " ";
					}
				}
			}
		}
		cout << endl;
	}
	ofs.close(); // close files.

	return 0;
}


