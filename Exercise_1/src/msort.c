/**
 * @file msort.c
 * @author Daniele Di Palma
 * @brief Merge-binary-insertion-Sort implementation
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msort.h"

#ifdef TEST
    #define TEST_SESSION (1)
  #else
    #define TEST_SESSION (0)
#endif

#define ERROR_EXIT(x) { if(TEST_SESSION == 0){                        \
                          fprintf(stderr, "[%s]-Line:%d >> "x"\n",    \
                          __FILE__,                                   \
                          __LINE__ );                                 \
                        exit(EXIT_FAILURE);}}                         \

#define K (10)

static void binary_insertion_sort(void *array, unsigned long size_el, unsigned long left, unsigned long right, int (precedes)(void *, void*));
static unsigned long binary_search(void *key, void *array, unsigned long size_el, unsigned long left, unsigned long right, int (precedes)(void *,void *));

/**
 * @brief Merge two sub-array in a single array, using specified rule for sorting 
 * 
 * @param array     array pointer that will be merged
 * @param size_el   size of array element
 * @param left      start index of array
 * @param mid       mid position index of array
 * @param right     last index of array
 * @param precedes  pointer to a function that implement the precedence relation between the array elements,
 *                  this function have to return 2 if first and second element are equal
 *                  1 if the first element precede the second one, 0 otherwise
 * @return void*    return pointer to ordinated array memory allocation
 */
static void merge(void *array_p, unsigned long size_el, unsigned long left, unsigned long mid, unsigned long right, int(*precedes)(void *, void *)){
  
  char *ordered_array = (char *)malloc((right-left + 1) * size_el);
  if(ordered_array == NULL){
    ERROR_EXIT("unable to allocate memory for ordered_array");
  }

  char *array = (char *)array_p;

  unsigned long i = left;     // index for left sub-array
  unsigned long j = mid + 1;  // index for right sub-array
  unsigned long k = 0;        // index for ordered array

  void *el_sx = NULL, *el_dx = NULL, *to_pos = NULL, *from_pos = NULL;

  while(i <= mid && j <= right){
    el_sx = &array[size_el * i];
    el_dx = &array[size_el * j];
    to_pos = &ordered_array[size_el * k];
    
    if((*precedes)(el_sx, el_dx)){
      memmove(to_pos, el_dx, size_el);
      j++;
    }else{
      memmove(to_pos, el_sx, size_el);
      i++;            
    }
    k++;
  }

  if(i <= mid){

    while(i <= mid){
      to_pos = &ordered_array[size_el * k];
      from_pos = &array[size_el * i];
      memmove(to_pos, from_pos, size_el);
      i++;
      k++;
    }
  }else{

    while(j <= right){
      to_pos = &ordered_array[size_el * k];
      from_pos = &array[size_el * j];
      memmove(to_pos, from_pos, size_el);
      j++;
      k++;
    }
  }

  i = 0;
  j = left;

  while(j <= right){
    to_pos = &array[size_el * j];
    from_pos = &ordered_array[size_el * i];
    memmove(to_pos, from_pos, size_el);
    ++i;
    ++j;
  }
  free(ordered_array);
}

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
void sort(void *array, unsigned long size_el, unsigned long left, unsigned long right, int(*precedes)(void *, void *)){
  
  if(array == NULL){
    ERROR_EXIT("array reference can't be NULL");
  }
  if(precedes == NULL){
    ERROR_EXIT("function pointer for precedence relation can't be NULL");
  }
  if(right < left){
    ERROR_EXIT("right must be greater or equal to left");
  }
  if(left < right){
    unsigned long mid = (left + right)/2;

    if((right - left + 1) <= K){
      binary_insertion_sort(array, size_el, left, right, precedes);
    }else{
      sort(array, size_el, left, mid, precedes);    
      sort(array, size_el, mid + 1, right, precedes); 
    }
  
    merge(array, size_el, left, mid, right, precedes);    
  }
}

/**
 * @brief sort an array of elements using precedes function pointer for sort in ascending or discending mode
 * 
 * @param array       pointer to array 
 * @param size_el     size of one array element
 * @param left        start index of array
 * @param right       last index of array
 * @param precedes    pointer function for precedence relation between elements. 
 *                    This function must return 2 if elements are equal, 1 if first element precede second, 0 otherwise.
 */
static void binary_insertion_sort(void *array_p, unsigned long size_el, unsigned long left, unsigned long right, int (precedes)(void *, void*)){
  unsigned long pos, j;
  
  char *array = (char *)array_p;

  void *key, *temp, *next_pos, *pre_pos;
  
  temp = (void *)malloc(size_el);

  for(unsigned long i = left+1; i <= right; i++){
    j = i - 1;

    key = &array[size_el * i];
    pos = binary_search(key, array, size_el, left, j, precedes);
    
    memmove(temp, key, size_el);
    
    // move all elements by one to create space for key element
    while(j > pos){
      next_pos = &array[size_el * (j+1)];
      pre_pos = &array[size_el * j];
    
      memmove(next_pos, pre_pos, size_el);
      j--;
    }

    pre_pos = &array[size_el * pos];
    next_pos = &array[size_el * (j+1)];

    memmove(next_pos, pre_pos, size_el);
    memmove(pre_pos, temp, size_el); 
    
  }
  free(temp);
}

/**
 * @brief search using precedes pointer function, the position where element pointed by key can be insert.
 * 
 * @param key       pointer to a key element
 * @param array     pointer to array where search
 * @param size_el   size of single element of array
 * @param left      array start index
 * @param right     array last index
 * @param precedes  pointer function for precedence relation between elements. 
 *                  This function must return 2 if elements are equal, 1 if first element precede second, 0 otherwise.
 * @return          The index where insert element.
 */
static unsigned long binary_search(void *key, void *array_p, unsigned long size_el, unsigned long left, unsigned long right, int (precedes)(void *,void *)){

  char *array = (char *)array_p;

  void *act_search = NULL;

  if(right <= left){
    act_search = &array[size_el * left];
    if((precedes)(key, act_search)){
        return left + 1;
    }else{
        return left;
    }
  }
  
  unsigned long mid = (right + left)/2;
  
  act_search = &array[size_el * mid];

  int cmp = (precedes)(key, act_search);
    
  if(cmp == 2){
    return mid+1;
  }else if(cmp){
    return binary_search(key, array, size_el, mid+1, right, precedes);
  }else{
    return binary_search(key, array, size_el, left, mid, precedes);
  }
}