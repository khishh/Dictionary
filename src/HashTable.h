#pragma once

using namespace std;

class HashTable{

  public:
  // default constructor
  HashTable();

  // constructor
  HashTable(int n);

  // copyConstructor
  HashTable(const HashTable & copyHash);

  // destructor
  ~HashTable();

  // overload assignment
  HashTable& operator=(const HashTable & copyHash);

  // insert
  void insert(string strToInsert);

  // find
  bool find(string strToFind) const;

  // arrSize
  int size() const;

  // maxSize
  int maxSize() const;

  // loadfactor occupancy
  float loadFactor() const;

  void printArr() const;

  

  // Attributes

  private:
  
  int arrSize;
  int halfPrime;
  int currentSize;
  string* arrString;
  
  // Helper functions
  bool checkPrime(int n) const;
  int getHashIndex(string & str, int primeNum) const;
  void copyHashTable(const HashTable & copyHash);
  void doubleSize();
};


