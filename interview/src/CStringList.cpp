/*!
 * \file
 *
 * \author hmt
 * \date 2021-01-04
 *
 * \brief Class CStringList that generates a list of String.
 * \details
 * This class will be able to: 
 * - generate list of string with all combinaisons of n characters [A-Z].
 * - shuffle the list to have them unsorted
 * - search through list all elements that starts with a given string
 *
 */

#include <iostream>
#include <vector>
#include <ctime>

// isupper()
#include <cctype>

// to shuffle list
#include <algorithm>
#include <random>

// get run time
#include <chrono>

// parallel programing
#include <omp.h>

// class header
#include "CStringList.h"

using namespace std;

// class constructor (Init + shuffle)
CStringList::CStringList(){
	initializeList("", CHAR_NB_IN_STRING);
	shuffleList();
}

// Initialization function for an unsorted list
// of k upper characters with prefix (Recursive method)
void CStringList::initializeList(string prefix, const int k){
    // Base case: k is 0,
    // add prefix as element to the list
    // k < 0 to check for erroneous function entry
    if (k <= 0){
	myList.push_back(prefix);
        return;
    }
    // One by one add all possible characters [A-Z]
    // call for k equals to k-1
    for (auto i = 0; i < 26; i++){
        string newPrefix;
	char currentChar = 'A'+i; 
        // add character as prefix to list element
        newPrefix = prefix + currentChar;

        // k is decreased, because
        // we have added a new character
	initializeList(newPrefix, k-1);
    }
}

// Unoptimized way to shuffle a vector
// Not really part of the exercise
void CStringList::shuffleList (){
    auto rng = default_random_engine {};
    shuffle(begin(myList), end(myList), rng);    
}

// Sanity check from user's input
void CStringList::stringSanityCheck(const string myInput){
    // wrong length
    if (myInput.size() > CHAR_NB_IN_STRING){
	cout << "Wrong input size (Must be <= " << CHAR_NB_IN_STRING << ")" << endl;
	exit(-1);
    }
    // each charater must be between A and Z
    for(std::size_t i = 0; i < myInput.size(); i++){
	if (!isupper(myInput[i])){
	    cout << "Wrong input type. Each element must be a character [A-Z]." << endl;
	    exit(-1);
	}
    } 
}

/*
 *
 * searching fct
 *
 * Function that populates the matchingIndices vector 
 * with the indices of that start with the searchString prefix
 */
void CStringList::findMatchingSubList (const string searchString, vector<size_t>& matchingIndices){
    // Go through all list entries
    // Parallelized
omp_lock_t lck; // declare lock
omp_init_lock(&lck); // init lock
omp_set_dynamic( 0 ); // disable dynamic adjustement of threads nb
omp_set_num_threads( omp_get_num_procs() ); // request as many threads as nb of processors
cout << "Searching strings in list with " << omp_get_num_procs () << " threads" << endl;
#pragma omp parallel for
    for (size_t i = 0; i < myList.size() ; i++ ){
	// If it starts with the searchString, save the index
        if (myList[i].rfind(searchString, 0) == 0) {
            omp_set_lock(&lck);// enable lock
            matchingIndices.push_back(i);
	    omp_unset_lock(&lck);// disable lock
	}
    }
omp_destroy_lock(&lck); // free lock resources
}

// print list
void CStringList::printList (){
    cout << "Sub list of " << myList.size() << " elements:" << endl;
    for (size_t i=0 ; i < myList.size() ; i++){
        cout << myList[i] << endl;
    }
}

// print sub list
void CStringList::printSubList (const vector<size_t> indices){
    cout << "The string list to be searched is as follow :" << endl;
    for (size_t i=0 ; i < indices.size() ; i++){
        cout << myList[indices[i]] << endl;
    }
}
