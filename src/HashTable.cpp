#include <iostream>
#include "HashTable.h"
#include <math.h>

using namespace std;

// Takes a parameter of integer and check if that integer is a prime number or not.

bool HashTable::checkPrime(int n) const{

  for(int i = 2; i*i <= n; i++){
    if(n % i == 0)
      return 0;
  }

  return 1;
}

// This function computes the index(=key) of a given string to properly insert into HashTable based on a given prime number. 

int HashTable::getHashIndex(string & str, int primeNum) const{
  unsigned int count = 0;
  
  // Here computing the index using the Horner Method to avoid number overflow.
  int hashIndex = (str[count] - 96);
  while(count < str.length()-1){
    count++;
    hashIndex = hashIndex*32 + str[count] - 96;

    hashIndex = hashIndex % primeNum;
  }
  return hashIndex;
}


// default constructor
HashTable::HashTable(){

  // default size
  arrSize = 101;
  currentSize = 0;
  
  // ----- setting halfPrime(the value used by h2) here ----

  // compute the prime number bigger than arrSize/2
  halfPrime = arrSize/2+1;

  // increment until checkPrime returns true meaning halfPrime is actually a prime number
  while(!checkPrime(halfPrime))
    halfPrime++;
  
  arrString = new string[arrSize];

  // set all elements to the empty string
  for(int i = 0; i < arrSize; i++)
    arrString[i] = "";
}

// constructor
HashTable::HashTable(int n){
  
  // get closest prime number for arrSize
  arrSize = n*2;
  while(!checkPrime(arrSize)){
    arrSize++;
  }
  
  currentSize = 0;
  arrString = new string[arrSize];
  
  // ----- setting halfPrime(the value used by h2) here ----

  halfPrime = arrSize/2+1;
  while(!checkPrime(halfPrime))
    halfPrime++;

  // set all elements to the empty string
  for(int i = 0; i < arrSize; i++)
    arrString[i] = "";
}

// copyConstructor
HashTable::HashTable(const HashTable & copyHash){

  copyHashTable(copyHash);

}

// destructor
HashTable::~HashTable(){

  delete [] arrString;

}

// // overload assignment
HashTable& HashTable::operator=(const HashTable & copyHash){
  if(this != &copyHash){
    delete this;
    copyHashTable(copyHash);
  }
  
  return *this;
}

// create an new hashtable with double size. Called by insert function.

void HashTable::doubleSize(){

  // Find the new arrSize of prime number
  // greater than twice of priginal size
  int newPrime = 2*arrSize+1;
  
  while(!checkPrime(newPrime))
    newPrime++;

  // Find the new halfPrime which will be the value used for second hash function
  int newHalfPrime = newPrime/2+1;

  while(!checkPrime(newHalfPrime)){
    newHalfPrime++;
  }

  halfPrime = newHalfPrime;

  string* newArr = new string[newPrime];

  // set all index to "" in newArr
  for(int i = 0; i < newPrime; i++)
    newArr[i] = "";

  for(int i = 0; i < arrSize; i++){

    // if string is empty, move on to next itteration
    if(arrString[i] == "")
      continue;
    else{
      
      // use first hash function
      int firstHashIndex = getHashIndex(arrString[i], newPrime);

      if(newArr[firstHashIndex] == ""){
        newArr[firstHashIndex] = arrString[i];
      }

      // use second hash function
      else{

        int secondHashIndex = getHashIndex(arrString[i], halfPrime);

        secondHashIndex = halfPrime - secondHashIndex;

        int index = (firstHashIndex + secondHashIndex)%newPrime;

        while(newArr[index] != ""){
          index += secondHashIndex;
          index = index % newPrime;
        }

        newArr[index] = arrString[i];

      }
    } 
  }

  arrSize = newPrime;
  delete [] arrString;
  arrString = newArr;

}

// insert
void HashTable::insert(string strToInsert){

  // if strToInsert is not in the hashtable, insert that string at the appropriate index computed by getHashIndex function.  
  if(!find(strToInsert)){

    // Computing the index based on the first hash function using strToInsert and arrSize.
    int firstHashIndex = getHashIndex(strToInsert, arrSize);

    // case when index given by the first function is not filled yet
    if(arrString[firstHashIndex] == ""){
      arrString[firstHashIndex] = strToInsert; 
      currentSize++;
    }

    // the index given by the first hash function was already used. Compute the new index using second hash function.
    else{

      int secondHashIndex = getHashIndex(strToInsert, halfPrime);

      // computing h2
      secondHashIndex = halfPrime - secondHashIndex;
      
      int index = (firstHashIndex + secondHashIndex)%arrSize;

      // while we find the non-occupied index, we keep searching by incrementing secondHashIndex
      while(arrString[index] != ""){
        index += secondHashIndex;
        index = index % arrSize;
      }

      // insert at the appropriate index
      arrString[index] = strToInsert;

      currentSize++;
    }
 
    // check loadFactor. if bigger than .67, call doubleSize function
    if(loadFactor() > .67){

      doubleSize();

    }
  }

}

// find
bool HashTable::find(string strToFind) const{

  // get the possible index of strToFind by getHashIndex.
  int firstHashIndex = getHashIndex(strToFind, arrSize);

  // if we find strToFind at firstHashIndex, we return true
  if(arrString[firstHashIndex] == strToFind){
    return 1;
  }

  // if we could not find strToFind with firstHashIndex, we compute the new possible index. 
  int secondHashIndex = getHashIndex(strToFind, halfPrime);

  secondHashIndex = halfPrime - secondHashIndex;

  int index = (firstHashIndex + secondHashIndex)%arrSize;

  // we will keep searching till we find strToFind or empty string
  while(arrString[index] != ""){
    if(arrString[index] == strToFind){
      return 1;
    }
    index += secondHashIndex;
    index = index % arrSize;
  }
  
  return 0;
}

// arrSize
int HashTable::size() const{
  return currentSize;
}

// maxSize
int HashTable::maxSize() const{
  return arrSize;
}

// loadfactor occupancy
float HashTable::loadFactor() const{
  return (float)currentSize/arrSize;
}

// copyHashTable
// do the deep copy of HashTable reference parameter
void HashTable::copyHashTable(const HashTable & copyHash){
  arrSize = copyHash.arrSize;
  currentSize = copyHash.currentSize;
  halfPrime = copyHash.halfPrime;

  arrString = new string[arrSize];
  for(int i = 0; i < arrSize; i++)
    arrString[i] = copyHash.arrString[i];
}

void HashTable::printArr()const{
  cout << arrSize << endl;
  for(int i = 0; i<arrSize ; i++)
    cout << i << ": " << arrString[i]<<endl;
}

