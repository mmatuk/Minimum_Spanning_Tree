//*******************************************************
//Author:                       Matt Matuk
//Created:                      09/07/2017
//Source File:                  Heap.cpp
//Description:
//
//Editor:                          Emacs
//*******************************************************

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

template <class T>
HeapMin<T>::HeapMin() : MAX_SIZE(100)
{
  heapSize = 0;
  A = new T *[MAX_SIZE];
}

template <class T>
HeapMin<T>::HeapMin(int const maxSize) : MAX_SIZE(maxSize)
{
  heapSize = 0;
  A = new T *[maxSize];
}

template <class T>
void HeapMin<T>::PrintHeap()
{
  for (int i = 0; i < heapSize; i++)
  {
    cout << *A[i];
  }
  cout << "\n";
}

template <class T>
int HeapMin<T>::Parent(int const i)
{
  if (i % 2 == 0)
  {
    return ((i - 1) / 2);
  }
  else
  {
    return (i / 2);
  }
}

template <class T>
int HeapMin<T>::LeftChild(int const i)
{
  return ((2 * i) + 1);
}

template <class T>
int HeapMin<T>::RightChild(int const i)
{
  return ((2 * i) + 2);
}

template <class T>
void HeapMin<T>::BuildHeap()
{
  for (int i = ((heapSize / 2) - 1); i >= 0; i--)
  {
    Heapify(i);
  }
}

template <class T>
void HeapMin<T>::Heapify(int const i)
{
  int l = LeftChild(i);  // index of left child
  int r = RightChild(i); // index of right child
  int smallest = -1;
  if (l <= heapSize - 1 && A[l] < A[i])
  {
    smallest = l;
  }
  else
  {
    smallest = i;
  }

  if (r <= heapSize - 1 && A[r] < A[smallest])
  {
    smallest = r;
  }

  if (smallest != i)
  {
    swap(A[i], A[smallest]);
    Heapify(smallest);
  }
}

template <class T>
void HeapMin<T>::Heapify(T *arr, int const i, int size)
{
  int l = LeftChild(i);
  int r = RightChild(i);
  int smallest = -1;
  if (l <= size - 1 && arr[l] < arr[i])
  {
    smallest = l;
  }
  else
  {
    smallest = i;
  }

  if (r <= size - 1 && arr[r] < arr[smallest])
  {
    smallest = r;
  }

  if (smallest != i)
  {
    swap(arr[i], arr[smallest]);
    Heapify(arr, smallest, size);
  }
}

template <class T>
void HeapMin<T>::swap(T *first, T *second)
{
  T *temp = first;
  first = second;
  second = temp;
}

template <class T>
T *HeapMin<T>::ExtractMin()
{
  if (heapSize < 1)
  {
    cout << "Error: heap Underflow";
    return NULL;
  }
  else
  {
    T *min = A[0];
    A[0] = A[heapSize - 1];
    heapSize--;
    Heapify(0);
    return min;
  }
}

template <class T>
T HeapMin<T>::Minimun()
{
  return A[0];
}

template <class T>
void HeapMin<T>::DeleteHeap()
{
  delete[] A;
}

/*
 * Returns -1 if no more room in heap array, else returns 0 if insert completed; 
 */
template <class T>
int HeapMin<T>::Insert(T *key)
{
  if (heapSize < MAX_SIZE)
  {
    heapSize++;
    int i = heapSize - 1;
    while (i > 0 && A[Parent(i)] > key)
    {
      A[i] = A[Parent(i)];
      i = Parent(i);
    }
    A[i] = key;
    return 0;
  }
  else
  {
    return -1;
  }
}

template <class T>
T *HeapMin<T>::HeapSort()
{
  T *temp = new T[heapSize];
  int tempSize = heapSize;
  copy(A, A + heapSize, temp);
  for (int i = tempSize - 1; i >= 1; i--)
  {
    swap(temp[0], temp[i]);
    tempSize--;
    Heapify(temp, 0, tempSize);
  }
  return temp;
}

template <class T>
int HeapMin<T>::getSize()
{
  return heapSize;
}