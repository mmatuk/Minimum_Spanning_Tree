//*******************************************************
//Author:                       Matt Matuk
//Created:                      09/07/2017
//Source File:                  Heap.h
//Description:
//
//Editor:                          Emacs
//*******************************************************

#ifndef _HEAP_H_
#define _HEAP_H_

template <class T>
class HeapMin
{
  friend class MST;

public:
  HeapMin();
  HeapMin(int const); // max size of heap
  int Insert(T *);
  T *HeapSort();
  T *ExtractMin();
  T Minimun();
  void PrintHeap();
  void DeleteHeap();
  int getSize();

private:
  //Variables
  T **A;              // stored array
  int heapSize;       // curent heap size
  const int MAX_SIZE; // amx heap size

  // Funcitons
  int Parent(int const);
  int LeftChild(int const);
  int RightChild(int const);
  void Heapify(int);
  void Heapify(T *, int, int);
  void BuildHeap();
  void swap(T *, T *);
};

#include "HeapMin.cpp"
#endif
