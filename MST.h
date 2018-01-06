//*******************************************************
//Author:                       Matt Matuk
//Created:                      12/6/17
//Source File:                  MST.h
//Description:
//  Determines the Minium spaning tree from a file containing
//  the node and vector info.
//
//  ReadMe.txt display the proper format for the input file.
//
//Editor:                          Visual Studio Code
//*******************************************************

#ifndef MST_H
#define MST_H

#include <iostream>
#include <string>

#include "HeapMin.h"

class MST
{
    struct mstNode
    {
        int id;
        mstNode *parent;
        int key;

        bool operator>(const mstNode &n1) { return key > n1.key; }
        bool operator>=(const mstNode &n1) { return key >= n1.key; }
        bool operator<(const mstNode &n1) { return key < n1.key; }
        bool operator<=(const mstNode &n1) { return key <= n1.key; }
        bool operator==(const mstNode &n1) { return (key != n1.key); }
        bool operator!=(const mstNode &n1) { return (key != n1.key); }
        friend ostream &operator<<(ostream &os, const mstNode &node)
        {
            os << "id:" << node.id << " Key:" << node.key << ", ";
            return os;
        }
    };

    struct mstEdge
    {
        mstNode *node1;
        mstNode *node2;
    };

  public:
    //Constructor
    MST();

    //Functions
    int Prim(std::string const);          // Determines the minium spaning tree from passed file loc
    void printMST();                       // prints the MST to CLI
    int printMSTtoFILE(std::string const); // Printst he MST to file by pased file name
    void printAdjMatrix();                 //print out the read adjMatrix
    int **getMSTadjMatrix();

  private:
    //Variables
    int size;
    int indexVnew;
    int indexEnew;
    mstNode **Vnew;     // array of nodes completed
    mstEdge **Enew;     // array of min span edges
    mstNode **V;        // array of node left to check
    int **adjMatrix;    // adj martix for nodes and edge weights
    int **mstAdjMatrix; // stores mst matrix
    HeapMin<mstNode> *mstHeap;

    //functions
    void addToHeap();
    int readFromFile(std::string const); // read input from the file and save to array;
    void addToV();
    void mstUpdate(int const, int const); // check to see if esge is in heap and need to be updated.
    void initVars();                      //init the vars
    void PrimCal();                       // use Prims algo to cal the min span tree.
    void updateHeap(int const);           // move changed node in heap
    void createMSTadjMatrix();            // create new adj matrix for the mst.
};

#endif /* MST_H */
