#include <iostream>
#include "HashTable.h"
#include "spellcheck.h"
#include <vector>


using namespace std;

// enum Difficulties {easy, medium, hard};

int main(){

    string inputCheck;
    vector<string> dictionary;
    
    cout << "Do you have your own dictionary you want to set?(Enter Y or N)" << endl;
        cin >> inputCheck;

    while(inputCheck != "Y" && inputCheck != "N"){
        cout << "Again, do you have your own dictionary you want to set? Enter Y or N " << endl;
        cin >> inputCheck;
    }

    // set up a dictironary

    if(inputCheck ==  "Y"){
        string pathOfFile;
        cout << "Enter your file's full path here" << endl;
        cin >> pathOfFile;

        dictionary = readFile(pathOfFile);
    }
    else{
        int difficulty;
        cout << "We will prepare our own dictionary.\n Which difficulties do you like?\n 1:easy 2:medium 3:hard\n Type your number" << endl;
        cin >> difficulty;
        if(difficulty > 2 || difficulty < 0){
            cout << "We will prepare our own dictionary.\n Which difficulties do you like?\n 1:easy 2:medium 3:hard\n Type your number" << endl;
            cin >> difficulty;
        }

        if(difficulty == 0)
            dictionary = readFile("wordlistData/wordlist100.txt");
        else if(difficulty == 1)
            dictionary = readFile("wordlistData/wordlist1000.txt");
        else
            dictionary = readFile("wordlistData/wordlist10000.txt");
        
    }

    
}
