//*******************************************************
//Author:                       Matt Matuk
//Created:                      09/07/2017
//Source File:                  Test.cpp
//Description:
//
//Editor:                          Emacs
//*******************************************************

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

#include "MST.h"

using namespace std;

//Global Variables
//Function Header

int main()
{
    string inFile;
    string outFile;
    cout << "Please enter input file name: ";
    cin >> inFile;
    cout << "Please enter output file name (-1 for no out file): ";
    cin >> outFile;
    MST test = MST();
    if (test.Prim(inFile))
    {
        cout << "Minium spaning tree ADJ Matrix: \n";
        test.printMST();

        if (outFile != "-1")
        {
            test.printMSTtoFILE(outFile);
        }
    }
    else
    {
        cout << "failed\n";
    }
}
