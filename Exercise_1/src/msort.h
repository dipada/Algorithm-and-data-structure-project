#ifndef _M_SORT_H_
#define _M_SORT_H_

// Sort an array of elements
/**
 * @brief Sort passed array using precedes function pointer.
 * 
 * @param array     array pointer to sort
 * @param size_el   size of array element
 * @param left      start index of array
 * @param right     last index of array
 * @param precedes  pointer function for precedence relation between elements. 
 *                  This function must return 2 if elements are equal, 1 if first element precede second, 0 otherwise.
 */
void sort(void *array, unsigned long size_el ,unsigned long left, unsigned long right,  int(*precedes)(void *, void *));

#endif