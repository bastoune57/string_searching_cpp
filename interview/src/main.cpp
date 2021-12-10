/*!
 * \file
 *
 * \author hmt
 * \date 2021-01-04
 *
 * \brief Main file of Toptal interview
 * \details
 * This file contains the code that will be done during the interview.
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

using namespace std;

/*
 *
 *  global settings variable for program 
 *
 */

#define CHAR_NB_IN_STRING 4 // Number of char in elements of the list

/*
 *
 * Helpers fct to organize in files / libraries
 * (Not needed here)
 *
 */

// Create initialization function for an unsorted list
// of 4 upper characters (Recursive method)
void initializeList(vector<string>& myList, string prefix, const int k){
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
        initializeList(myList, newPrefix, k-1);
    }
}

// Unoptimized way to shuffle a vector
// Not really part of the exercise
void shuffleList (vector<string>& myList){
    auto rng = default_random_engine {};
    shuffle(begin(myList), end(myList), rng);    
}

// Sanity check from user's input
void inputSanityCheck(const string myInput){
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
void findMatchingSubList (const vector<string> myList, const string searchingString, vector<size_t>& matchingIndices){
    // Go through all list entries
    // Parallelized
omp_lock_t lck; // declare lock
omp_init_lock(&lck); // init lock
omp_set_dynamic( 0 ); // disable dynamic adjustement of threads nb
omp_set_num_threads( omp_get_num_procs() ); // request as many threads as nb of processors
cout << omp_get_num_procs () << endl;
#pragma omp parallel for
    for (size_t i = 0; i < myList.size() ; i++ ){
	// If it starts with the searchString, save the index
        if (myList[i].rfind(searchingString, 0) == 0) {
            omp_set_lock(&lck);// enable lock
            matchingIndices.push_back(i);
	    omp_unset_lock(&lck);// disable lock
	}
    }
omp_destroy_lock(&lck); // free lock resources
}

/*
 *
 *  Main fct
 *
 */
int main (void){
    // declare variables
    vector<string> myList;
    std::string searchString;
    vector<size_t> matchingIndices;
    
    // initialise list of CHAR_NB_IN_STRING char
    initializeList(myList, "", CHAR_NB_IN_STRING);
    // shuffle list
    shuffleList(myList);
  
    // get input string
    cout << "Please input a search string of at least " << CHAR_NB_IN_STRING << " characters:" << endl;
    cin >> searchString;
    // make input sanity check
    inputSanityCheck(searchString);

    // Start measuring time
    auto begin = std::chrono::high_resolution_clock::now();

    // find matching sub list
    findMatchingSubList(myList, searchString, matchingIndices);

    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    // print sub list
    for (size_t i = 0; i < matchingIndices.size(); i++)
    	cout << myList[matchingIndices[i]] << endl;
    cout << matchingIndices.size() << " matchs found in " << elapsed.count()*1e-6 << "miliseconds" << endl;
    
    /*
    // print list 
    for (size_t i = 0; i < myList.size(); i++)
    	cout << myList[i] << endl;
    */
    return 0;
}
