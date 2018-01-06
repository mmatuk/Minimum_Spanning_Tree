//*******************************************************
//Author:                       Matt Matuk
//Created:                      09/07/2017
//Source File:                  Heap.h
//Description:
//
//Editor:                          Emacs
//*******************************************************
#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>

#include "MST.h"

/**
 * Constructor for the MST
 */
MST::MST()
{
    mstAdjMatrix = NULL;
    adjMatrix = NULL;
}

int MST::Prim(std::string const file)
{
    if (readFromFile(file) != -1)
    {
        addToV();
        addToHeap();
        PrimCal();
        createMSTadjMatrix();
        return 1;
    }
    else
    {
        std::cout << "Error: reading the file. Is the name correct? " << file << std::endl;
        return 0;
    }
}
/**
 * Read from the passed file name and add contents to adjMatrix.
 * 
 * @param file Lcoation of the file.
 * 
 * @return -1 if file not open, else file opened and read completed.
 */
int MST::readFromFile(std::string const file)
{
    ifstream myfile(file.c_str());

    if (myfile.is_open())
    {
        myfile >> size;
        initVars();
        int weight;
        for (int r = 0; r < size; r++) // get all the wegihts and set in the adj matrix
        {
            for (int c = 0; c < size; c++)
            {
                myfile >> weight;
                adjMatrix[r][c] = weight;
            }
        }
        myfile.close();
        return 1;
    }
    else
    {
        return -1;
    }
}

/**
 * Init all the vars
 */
void MST::initVars()
{
    indexVnew = 0;
    indexEnew = 0;
    Vnew = new mstNode *[size];
    Enew = new mstEdge *[size];
    V = new mstNode *[size];
    mstHeap = new HeapMin<mstNode>(size);
    adjMatrix = new int *[size];   // int rows
    for (int i = 0; i < size; ++i) // int col
    {
        adjMatrix[i] = new int[size];
    }

    for (int r = 0; r < size; r++) // set all weights to 0
    {
        for (int c = 0; c < size; c++)
        {
            adjMatrix[r][c] = 0;
        }
    }
}

/**
 * Print out all the values of the adj matrix
 */
void MST::printAdjMatrix()
{
    if (adjMatrix != NULL)
    {
        for (int r = 0; r < size; r++) // set all weights to 0
        {
            for (int c = 0; c < size; c++)
            {
                std::cout << adjMatrix[r][c] << " ";
            }
            std::cout << std::endl;
        }
    }
}

/**
 * Create a node and adds it to the V array.
 * 
 * key = infinite
 * parent = NULL
 * id = 1 - size;
 */
void MST::addToV()
{
    for (int i = 1; i <= size; i++) // create n amounts of node
    {
        mstNode *node = new mstNode();
        node->parent = NULL;
        node->key = std::numeric_limits<int>::max(); // set value to infinte
        node->id = i;

        V[i - 1] = node;
    }
}

/**
 * Adds each node to the heap
 */
void MST::addToHeap()
{
    for (int i = 0; i < size; i++) // create n amounts of node
    {
        mstHeap->Insert(V[i]);
    }
}

/**
 * Use Prims algo to calulate the minmun spaanning tree from the adj matrix.
 */
void MST::PrimCal()
{
    Vnew[indexVnew] = mstHeap->ExtractMin();
    Vnew[indexVnew]->key = 0;
    mstEdge *edge;

    for (int num = 0; num < size - 1; num++) // loop until no more nodes are left in V
    {

        for (int i = 0; i < indexVnew + 1; i++) // loop for each node in Vnew to check for smallest weight
        {
            for (int c = 0; c < size; c++) // find an edge for the node currently being checked
            {
                if (adjMatrix[Vnew[i]->id - 1][c] > 0) //edge exist
                {
                    mstUpdate(i + 1, c + 1);
                }
            }
        }
        //mstHeap->PrintHeap();
        indexVnew++;
        Vnew[indexVnew] = mstHeap->ExtractMin();
        edge = new mstEdge();
        edge->node1 = Vnew[indexVnew]->parent;
        edge->node2 = Vnew[indexVnew];
        Enew[indexEnew] = edge;
        indexEnew++;
    }
}

/**
 * This determines if the node id is still in V.
 * If found, then will update the key value of the node and move the ndoe to
 * the correct location of the heap to keep the heap min property.
 * 
 * @param searchID The nodes id to check for.
 * 
 * @return -1 if node was not found, else return node location after update.
 */
void MST::mstUpdate(int const parentNodeID, int const searchID)
{
    int parIndex = parentNodeID - 1;
    int searchIndex = searchID - 1;
    for (int i = 0; i < mstHeap->heapSize; i++) // search to see if node is in V (heap)
    {
        if (mstHeap->A[i]->id == searchID) // node in heap (V)
        {
            if (mstHeap->A[i]->parent == NULL) // node has not been checked
            {
                ///std::cout << "*******";

                mstHeap->A[i]->parent = Vnew[parIndex];                              //set parent to last node pulled out of heap
                mstHeap->A[i]->key = adjMatrix[Vnew[parIndex]->id - 1][searchIndex]; // adds parents key to weight of edge and set to current node
                //std::cout << "par " << Vnew[parIndex]->id - 1 << " cur: " << searchIndex << " key: " << mstHeap->A[i]->key << "\n";
            }
            else if (mstHeap->A[i]->key > adjMatrix[Vnew[parIndex]->id - 1][searchIndex]) // node has a value already and value is bigger then current check
            {
                //std::cout << "-----";
                mstHeap->A[i]->parent = Vnew[parIndex];                              //set parent to last node pulled out of heap
                mstHeap->A[i]->key = adjMatrix[Vnew[parIndex]->id - 1][searchIndex]; // adds parents key to weight of edge and set to current node
            }
            //std::cout << "else par " << Vnew[parIndex]->id - 1 << " cur: " << searchIndex << " key: " << mstHeap->A[i]->key << "adj " << adjMatrix[Vnew[parIndex]->id - 1][searchIndex] << "\n";

            updateHeap(i);
            //std::cout << "++++++else par " << Vnew[parIndex]->id - 1 << " cur: " << searchIndex << " key: " << mstHeap->A[i]->key << "adj " << adjMatrix[Vnew[parIndex]->id - 1][searchIndex] << "\n";
            break;
        }
    }
}

/**
 * Update the heap by moveing the cchenged node up until heap properity is no longer violated.
 */
void MST::updateHeap(int const i)
{
    int index = i;
    int parIndex = mstHeap->Parent(index);
    //mstHeap->PrintHeap();

    while (mstHeap->A[index]->key < mstHeap->A[parIndex]->key) // while parent is bigger
    {
        // swap parent and child
        mstNode *temp = mstHeap->A[index];
        mstHeap->A[index] = mstHeap->A[parIndex];
        mstHeap->A[parIndex] = temp;
        index = parIndex; // parent index in new current index
        parIndex = mstHeap->Parent(index);
    }
}

/**
 * Adds all the mst edges to the new adj matrix.
 */
void MST::createMSTadjMatrix()
{
    mstAdjMatrix = new int *[size]; // int rows
    for (int i = 0; i < size; ++i)  // int col
    {
        mstAdjMatrix[i] = new int[size];
    }

    for (int r = 0; r < size; r++) // set all weights to 0
    {
        for (int c = 0; c < size; c++)
        {
            mstAdjMatrix[r][c] = 0;
        }
    }

    int r, c, w;
    for (int i = 1; i <= indexVnew; i++) // for each node in Vnew, get the edge.
    {
        r = Vnew[i]->parent->id - 1;
        c = Vnew[i]->id - 1;
        w = Vnew[i]->key;

        mstAdjMatrix[r][c] = w;
        mstAdjMatrix[c][r] = w;
    }
}

/**
 * Display the MST to the CLI
 * 
 *  EX:
 *           1   2   4   5   6   7
 *          ______________________
 *        1| 1  14 500   7   6   8
 *        2| 0   0   5   3   6   0
 *        etc...
 * 
 * Finds the largest weight to determine the amount of digits is in the 
 * largest to keep matrix alined.
 */
void MST::printMST()
{
    if (mstAdjMatrix != NULL)
    {
        int largest = 0;                    // largest weight
        for (int i = 0; i < indexVnew; i++) // find largest weight for edge.
        {
            if (Vnew[i]->key > largest)
            {
                largest = Vnew[i]->key;
            }
        }

        int mul = 1;
        int digits = 1; // amount to use for setw()

        //get amount of digits in largest
        //EX: largest = 15, then 100 / 15 is > 1, then digits = 3.
        while (mul / largest < 1)
        {
            digits++;
            mul = mul * 10;
        }

        //print node ids for columns
        std::cout << "  ";
        for (int i = 1; i <= size; i++)
        {
            std::cout << setw(digits) << i;
        }
        std::cout << std::endl;
        for (int i = 0; i < (size * digits) + 2; i++)
        {
            std::cout << "_";
        }
        std::cout << std::endl;

        //print adj matrix
        for (int r = 0; r < size; r++)
        {
            std::cout << r + 1 << "|";
            for (int c = 0; c < size; c++)
            {
                std::cout << setw(digits) << mstAdjMatrix[r][c];
            }
            std::cout << std::endl;
        }
    }
}

/**
 * Prints the MST adj matrix to a file.
 * 
 * @param file The file name to print to.
 * 
 * @return 0 if failed to print, else pos if done.
 */
int MST::printMSTtoFILE(std::string const file)
{
    ofstream myfile(file.c_str());
    if (myfile.is_open() && mstAdjMatrix != NULL) // if opn file happened.
    {
        int largest = 0;                    // largest weight
        for (int i = 0; i < indexVnew; i++) // find largest weight for edge.
        {
            if (Vnew[i]->key > largest)
            {
                largest = Vnew[i]->key;
            }
        }

        int mul = 1;
        int digits = 1; // amount to use for setw()

        //get amount of digits in largest
        //EX: largest = 15, then 100 / 15 is > 1, then digits = 3.
        while (mul / largest < 1)
        {
            digits++;
            mul = mul * 10;
        }

        //print node ids for columns
        myfile << "  ";
        for (int i = 1; i <= size; i++)
        {
            myfile << setw(digits) << i;
        }
        myfile << std::endl;
        for (int i = 0; i < (size * digits) + 2; i++)
        {
            myfile << "_";
        }
        myfile << std::endl;

        //print adj matrix
        for (int r = 0; r < size; r++)
        {
            myfile << r + 1 << "|";
            for (int c = 0; c < size; c++)
            {
                myfile << setw(digits) << mstAdjMatrix[r][c];
            }
            myfile << std::endl;
        }
        myfile.close();
        return 1;
    }
    else
    {
        return 0;
    }
}
