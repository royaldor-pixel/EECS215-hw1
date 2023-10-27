/**
 *  \file quick-sort.cc
 *
 *  \brief Implement your randomized quick sort in this file.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sort.hh"

// Quicksort implementation
void mySort(int N, keytype *A)
{
  /* Lucky you, you get to start from scratch*/
  srand(time(0));
  myQuickSort(A, 0, N - 1);
}

/**
 * Swap two elements in an array
 */
void swap(keytype *a, keytype *b)
{
  keytype temp = *a;
  *a = *b;
  *b = temp;
}

/**
 * Partition the array into two parts,
 * which elements greater than pivot is on the right of pivot
 * and elements smaller than pivot is on the left of pivot
 * then return the index of pivot
 */
int partition(keytype *A, int p, int r)
{
  int randNum = (rand() % (r - p + 1)) + p; // generate a random number in [p, r] as the index of pivot
  swap(A + p, A + randNum);                 // swap the randomly selected element with the first element
  keytype pivot = A[p];                     // Pivot element
  int i = p;
  for (int j = p + 1; j <= r; j++)
  {
    if (A[j] <= pivot)
    {
      i++;
      swap(A + i, A + j);
    }
  }
  swap(A + p, A + i); // Swap the pivot element to its correct position
  return i;           // Return the index of the pivot element
}

/**
 * Recursive function to perform quicksort
 */

void myQuickSort(keytype *A, int p, int r)
{
  if (p < r)
  {
    int q = partition(A, p, r); // Finds the pivot element
    myQuickSort(A, p, q - 1);   // Recursively calls quicksort on the left partition
    myQuickSort(A, q + 1, r);   // Recursively calls quicksort on the right partition
  }
}
