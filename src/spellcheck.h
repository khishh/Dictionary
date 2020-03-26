#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include "HashTable.h"
#include <exception>
#include <string>

using namespace std;

void printVector(vector<string> & v){
  for(vector<string>::iterator it = v.begin(); it != v.end(); it++)
    cout << *it << " => ";
  cout <<endl;
}

void printVector2(vector<string>::iterator start, vector<string>::iterator end){
  for(vector<string>::iterator it = start; it != end; it++){
    cout << *it << "=>";
  }
  cout << endl;
}

// swap the two strings stored inside vector
void swap(vector<string>::iterator a, vector<string>::iterator b){

  string temp = *a;
  *a = *b;
  *b = temp;

}

// find method for vector.
// if vector has string parameter, return true. Otherwise return false.
// This function is used for preventing some words to be multiply saved into vector for my 5 spellcheck function.
bool find(vector<string> & v, string toFind){
  
  for(vector<string>::iterator it = v.begin(); it != v.end(); it++)
    if(*it == toFind)
      return true;
  return false;
}

// vectorSort's helper.
vector<string>::iterator partition(vector<string>::iterator start, vector<string>::iterator end){

  vector<string>::iterator firstPtr = start+1;
  vector<string>::iterator secndPtr = end;

  // pivot chosen from the left most element
  vector<string>::iterator pivot = start;

  while(firstPtr <= secndPtr){
    if(*secndPtr < *pivot){
      if(*firstPtr > *pivot){
        swap(firstPtr, secndPtr);
      }
      else
        firstPtr++;
    }
    else
      secndPtr--;
  }

  if(*secndPtr < *pivot)
    swap(secndPtr, pivot);

  return secndPtr;
}

// sort strings inside vectors. Used quicksort for implementation. 
// This is made for sorting strings inside a vector to keep contents inside a vector orderly.
void vectorSort(vector<string>::iterator start, vector<string>::iterator end){

  if(start < end){
    vector<string>::iterator pivot = partition(start, end-1);

    vectorSort(start, pivot);
    vectorSort(pivot+1, end);
  }
}

// Read each line inside a file and save them into a vector. Return a vector.
vector<string> readFile(string infile){

  ifstream ist(infile.c_str());

  if(ist.fail())
    throw runtime_error(infile + " not found");

  istream_iterator<string> start(ist), end;
  vector<string> result(start, end);

  ist.close();
  return result;
}

// extraLetter
// What it does: First check if string parameter exists inside hashtable reference parameter. If it exists return a vector containing the string parameter. If not, erase one letter at index of 0 to length of string parameter - 1 to obtain all possible strings with has one extra letter compared to string parameter. And return a vector containing those strings found inside hashtable.
vector<string> extraLetter(const HashTable & ht, string word){

  vector<string> result;

  // case where string parameter existd inside text file
  if(ht.find(word)){
    result.push_back(word);
  }
  else{

    // Here erasing a letter at index from 0 to length of string parameter-1 and compare that word is stored inside hashtable.

    string extraLetter;
    // int count = 0;
    string keep = word;

    for(unsigned int i = 0; i < word.length(); i++){
      extraLetter = word.erase(i, 1);
      cout << i << "'s erase : " << extraLetter << endl;

      // if extraLetter found inside hashtable, add it to result vector
      if(ht.find(extraLetter) && !find(result, extraLetter)){
        result.push_back(extraLetter);
      }

      // let word have its original value
      word = keep;
    }
  }

  // quicksort the contents of vector
  vectorSort(result.begin(), result.end());

  return result;
}

// transportation
// What it does: First check if string parameter exists inside hashtable reference parameter. If it exists return a vector containing the string parameter.If not, check all possible strings can be created by swapping one pair of adjacent letters, and check whether they exists inside hashtable. Return a vector containing them.
vector<string> transportation(const HashTable & ht, string word){

  vector<string> result;

  // case where string parameter is found inside hashtable
  if(ht.find(word))
    result.push_back(word);
  else{

    // in for loop, swap adjacent letters and try to find it in hashtable. 

    string keep = word;
    for(unsigned int i = 0; i < word.length()-1; i++){
      char temp = word[i];
      word[i] = word[i+1];
      word[i+1] = temp;

      // find it in hashtable
      if(ht.find(word) && !find(result, word)){
        result.push_back(word);
      }
      word = keep;
    }
  }

  // quicksort the contents of vector
  vectorSort(result.begin(), result.end());
  return result;
}

// helper function for missing space.
// split string parameter at splitIndex.
vector<string> strSplit(string str, int splitIndex){

  // vector storing first part of splitted word and second part of splitted word.
  vector<string> strList;

  unsigned int count = 0;
  string first = "";

  while((int)count < splitIndex){
    first += str[count++];
  }

  string second = "";
  while(count < str.length()){
    second += str[count++];
  }

  strList.push_back(first);
  strList.push_back(second);

  return strList;
}

// missingSpace
// What it does: First check if string parameter exists inside hashtable reference parameter. If it exists return a vector containing the string parameter. I made an strSplit function above which split string parameter into two words based on splitIndex and return a vector containing two words after splitting a string parameter. Check if those two words exist inside hashtable and if so store inside a returning vector.
vector<string> missingSpace(const HashTable & ht, string word){
  vector<string> result;

  // case when you find string parameter inside hashtable
  if(ht.find(word)){
    result.push_back(word);
  }
  // case when you could not find string parameter
  else{
    // inside for loop, splitting string at indec from 1 to length-1
    for(unsigned int i = 1; i < word.length(); i++){
      vector<string> splitStr = strSplit(word, i);

      // we have to check that two divided string both exist in the dictionary
      if(ht.find(splitStr[0]) && ht.find(splitStr[1])){
        result.push_back(splitStr[0]);
        result.push_back(splitStr[1]);
      }
    }
  }

  return result;
}


string insert(string str, char c, int index){

  char temp = str[index];
  
  while(temp){
    str[index] = c;
    c = temp;
    index++;
    temp = str[index];
  }

  str += c;
  return str;
}

// missingLeter's helper
// create a vector containing all possible strings inserted one letter from a to z at all possible indexes.
vector<string> insertLetterAtAllIndex(string str){

  vector<string> insertedList;
  
  char start = 'a';

  for(int i = str.length(); i >= 0; i--){
    for(int j = 0; j < 26; j++){

      string inserted = insert(str, start+j, i);
      insertedList.push_back(inserted);
    }
  }

  return insertedList;
}

// missingLetter
// What it does: First check if string parameter exists inside hashtable reference parameter. If it exists return a vector containing the string parameter. If not, call insertLetterAtAllIndex function which returns a vector containing all possible strings which can be created by inserting one letter. After that check if those strings are present inside hashtable or not. Then return a vector storing strings found inside hashtable.
vector<string> missingLetter(const HashTable & ht, string word){

  vector<string> result;

  // case when you find string parameter inside hashtable
  if(ht.find(word)){
    result.push_back(word);
  }
  else{
    vector<string> insertedStrList = insertLetterAtAllIndex(word);
  
    // check whether all one letter inserted strings are stored inside hashtable or not
    for(vector<string>::iterator it = insertedStrList.begin(); it != insertedStrList.end(); it++){
      if(ht.find(*it) && !find(result, *it)){
        result.push_back(*it);
      }
    }
  }

  // quicksort the contents of vector
  vectorSort(result.begin(), result.end());
  return result;
}

// changeLetterAtIndex's helper
// change the letter of string at index to parameter c
string changeLetter(string str, char c, int index){

  str[index] = c;

  return str;
}

// changeLetterAtIndex's helper
// create an vector containing all possible strings which can be obtained by changing one letter of string parameter at all possible indexes one per time. 
vector<string> changeLetterAtIndex(string str){

  vector<string> changedList;
  char start = 'a';

  for(unsigned int i = 0; i < str.length(); i++){
    for(int j = 0; j < 26; j++){
      string changed = changeLetter(str, start+j, i);
      changedList.push_back(changed);
    }
  }

  return changedList;
}

//  incorrectLetter
// What it does: First check if string parameter exists inside hashtable reference parameter. If it exists return a vector containing the string parameter. If not, call changeLetterAtIndex function which creates all possible strings by changing one letter to another at index from 0 to length of string parameter-1 and return a vector storing them. After that, check if hashtable keeps these strings or not and return a vector containing strings found in hashtable.
vector<string> incorrectLetter(const HashTable & ht, string word){

  vector<string> result;

  // case when you find string parameter inside hashtable
  if(ht.find(word)){
    result.push_back(word);
  }
  else{
    // if string parameter is not found inside hashtable, call changeLetterAtIndex to obtain all possible strings and store them inside vector.
    vector<string> changedStrList = changeLetterAtIndex(word);

    // check if there are any string inside changedStrList found inside hashtable
    for(vector<string>::iterator it = changedStrList.begin(); it != changedStrList.end(); it++){
      if(ht.find(*it) && !find(result, *it))
        result.push_back(*it);
    }
  }

  // quicksort the constent of vector
  vectorSort(result.begin(), result.end());
  return result;
}

