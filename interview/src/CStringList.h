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

#include <vector>

#define CHAR_NB_IN_STRING 4 // Number of char in elements of the list

using namespace std;

class CStringList {
    private:
	vector<string> myList;
	
    public:
	CStringList ();
        void initializeList (string prefix, const int k);
        void shuffleList ();
        void findMatchingSubList (const string searchingString, vector<size_t>& matchingIndices);
	void stringSanityCheck (const string myInput);
        void printSubList (const vector<size_t> indices);
        void printList ();
};
