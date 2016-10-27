/*****************************************************************************
Title:          BQpptest.cpp
Author:         Nishad Sharker
******************************************************************************/
#include <iostream>
#include "BinomialQueuePlusPlus.h"
#include <fstream>
#include <string>

using namespace std;


int main ()
{

    BinomialQueuePlusPlus<string> test1;

    ifstream wordFile;
    wordFile.open("words.txt");
    string words;

    //Grab the words in the file line by line
    while(getline(wordFile,words))
    {
        test1.insert(words);
        //cout << words << ": at : " << test1.find(words) << endl;
    }

    //TASK 2
    //REMEMBER assign counter also counts i++ because it is equivalent to i = i + 1
    cout << "Assign counter : " << test1.getAssignCounter() << endl;
    cout << "Comparison counter : " << test1.getComparisonCounter() << endl;

    //TASK 3

    for(int i = 0; i < 10;i++)
    {
        string minString = test1.findMin();
        test1.deleteMin();
        if (!(test1.findNode(minString)))
        {
            cout << minString << " was deleted successfully!" << endl;
        }
        else
        {
            cout << minString << " was not deleted! ERROR!" << endl;
        }

    }

    //TASK 4
    cout << "Please enter a string that you want to search for: " << endl;
    string userString;
    cin >> userString;

    //findNode calls the private function find in BQ++
    if (test1.findNode(userString))
    {
        cout << userString << " was found!" << endl;
    }
    else
    {
        cout << userString << " was not found!" << endl;
    }





    //TASK 6
    for(int i = 0; i < 5; i++)
    {
        cout << "Enter a string to remove: ";
        string userInput;
        cin >> userInput;

        cout << "Removing the string " << userInput << endl;
        test1.remove(userInput);

        cout << "Checking if " << userInput << " is found." << endl;
        if (test1.findNode(userInput))
        {
            cout << userInput << "was found!" << endl;
        }
        else
        {
            cout << userInput << " was not found!" << endl;
        }

    }

    return 0;
}
