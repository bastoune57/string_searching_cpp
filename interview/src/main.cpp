/*!
 * \file
 *
 * \author hmt
 * \date 2021-01-04
 *
 * \brief Main file of Vector interview
 * \details
 * This file contains the main of the case study.
 * Case Study:
 * Developing a parallel search for a word list
 *  
 * Assume that there is a data structure in terms of a list that contains different words. A search algorithm is supposed to find a sub-list containing all the words that start with a given search string. The algorithm shall make use of the multi-core CPU for distributing the search on several cores.
 *  
 * Task
 * Design a suitable data structure for the word list. Choose a suitable search algorithm and implement it in Java, C# or C++. You may assume that the word list is exclusively available to the search algorithm throughout the whole search. Implement a test client that accepts a search string, measures the search’s runtime and outputs the results.
 *  
 * How would you proceed if the task was to implement an incremental search (i.e. the search starts while typing the first letter)? How would the GUI look like?
 *  
 * For demonstration purpose use a word list which consists of all possible combinations of 4 upper case letters (AAAA to ZZZZ). The list is not sorted.
 *
 */

#include <iostream>
#include <vector>
#include <ctime>

// get run time
#include <chrono>

// import CStringList 
#include "CStringList.h"

using namespace std;

/*
 *
 *  Main fct
 *
 */
int main (void){
    // declare variables
    CStringList stringList; // List of string class
    string searchString; // String to use for search
    vector<size_t> matchingIndices; // matching indices from search

    // get input string
    cout << "Please input a search string of at least " << CHAR_NB_IN_STRING << " characters:" << endl;
    cin >> searchString;

    // make input sanity check
    stringList.stringSanityCheck(searchString);

    // Start measuring time
    auto begin = std::chrono::high_resolution_clock::now();

    // find matching sub list
    stringList.findMatchingSubList(searchString, matchingIndices);

    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    // print result
    stringList.printSubList(matchingIndices);
    cout << matchingIndices.size() << " matchs found in " << elapsed.count()*1e-6 << "miliseconds" << endl;
    
    // print list 
    //stringList.printList();
    
    return 0;
}
