/**
 * @file edit_distance_dyn.c
 * @author Daniele Di Palma
 * @brief Recursive version of edit distance with dynamic programming
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "edit_distance_dyn.h"

#define ERROR_EXIT(x){  fprintf(stderr, "[%s]-Line:%d >> " x "\n",  \
                        __FILE__,                                   \
                        __LINE__);                                  \
                      exit(EXIT_FAILURE);}

/**
 * @brief Calculate edit distance between two strings. 
 *				Determines minimum number of operation 
 *				to transform @param s2 into @param s1 
 *        using @param memoization for store results.
 * 
 * @param s1  first string, can't be NULL
 * @param s2  second string, can't be NULL
 * @param s1_len  length of first string
 * @param s2_len  length of second string
 * @param memoization reference for memoization array of pointers
 * @return unsigned number of operation
 */
static unsigned edit_distance(char *s1, char *s2, unsigned s1_len, unsigned s2_len, unsigned** memoization);

/**
 * @brief Skip by one the given string address (move to next character skipping current)
 * 
 * @param str     address of string
 * @return char*  new skipped address
 */
static char *rest(char *str){
  return ++str;
}

/**
 * @brief	Calculate edit distance on rest of strings, excluding first character of strings
 * 
 * @param s1  first string, can't be NULL
 * @param s2  second string, can't be NULL
 * @param s1_len  length of first string
 * @param s2_len  length of second string
 * @param memoization reference for memoization array of pointers
 * @return unsigned number of operation
 */
static unsigned no_op(char *s1, char *s2, unsigned s1_len, unsigned s2_len, unsigned** memoization){
  if (s1[0] == s2[0]){
    return edit_distance(rest(s1), rest(s2), s1_len-1, s2_len-1, memoization);
  }
  else{
    return UINT_MAX-1;
  }
}

/**
 * @brief Delete a character on second string
 * 
 * @param s1 first string, can't be NULL
 * @param s2 second string, can't be NULL
 * @param s1_len  length of first string
 * @param s2_len  length of second string
 * @param memoization reference for memoization array
 * @return unsigned number of operation
 */
static unsigned canc(char *s1, char *s2, unsigned s1_len, unsigned s2_len, unsigned** memoization){
  return 1 + edit_distance(s1, rest(s2), s1_len, s2_len-1, memoization);
}

/**
 * @brief Insert a character on head of second string
 * 
 * @param s1 first string, can't be NULL
 * @param s2 second string, can't be NULL
 * @param s1_len  length of first string
 * @param s2_len  length of second string
 * @param memoization reference for memoization array
 * @return unsigned number of operation
 */
static unsigned ins(char *s1, char *s2, unsigned s1_len, unsigned s2_len, unsigned** memoization){
  return 1 + edit_distance(rest(s1), s2, s1_len-1, s2_len, memoization);
}

/**
 * @brief Calculate minimum value between three numbers
 * 
 * @param n1 first number >= 0
 * @param n2 second number >= 0
 * @param n3 third number >= 0
 * @return unsigned minimum value
 */
static unsigned min(unsigned n1, unsigned n2, unsigned n3){
  if((n1 < n2) && (n1 < n3))
    return n1;
  else if (n2 < n3)
    return n2;
  return n3;
}

static unsigned edit_distance(char *s1, char *s2, unsigned s1_len, unsigned s2_len, unsigned** memoization){
  if(s1_len == 0){
    return s2_len;
  }

  if(s2_len == 0){
    return s1_len;
  }

  if(memoization[s1_len-1][s2_len-1] < UINT_MAX){
    return memoization[s1_len-1][s2_len-1];
  }

  return memoization[s1_len-1][s2_len-1] = min(no_op(s1, s2, s1_len, s2_len, memoization), canc(s1, s2, s1_len, s2_len, memoization), ins(s1, s2, s1_len, s2_len, memoization));
}

/**
 * @brief Allocate array memoization passed, then initialize it. 
 * 
 * @param memoization array of pointers to allocate
 * @param n_row number of row
 * @param n_col number of colums
 * @return unsigned** address of memory area where allocate array starts
 */
static unsigned **init_memoization(unsigned **memoization, unsigned n_row, unsigned n_col){
  memoization = (unsigned **)malloc(n_row * sizeof(unsigned *));
  if(memoization == NULL){
    ERROR_EXIT("Unable to allocate memory for memoization pointers\n");
  }

  for(register unsigned i = 0; i < n_row; i++){
    *(memoization+i) = (unsigned *)malloc(n_col * sizeof(unsigned));
    if(*(memoization+i) == NULL){
      ERROR_EXIT("Unable to allocate memory for memoization\n");
    }
  }

  for(register unsigned i = 0; i < n_row; i++){
    for(register unsigned j = 0; j < n_col; j++){
      memoization[i][j] = UINT_MAX;
    }
  }

  return memoization;
}

/**
 * @brief frees memoization array
 * 
 * @param memoization array pointers to free
 * @param n_row number of rows
 */
static void free_memoization(unsigned **memoization, unsigned n_row){
  for(register unsigned i = 0; i < n_row; i++)
    free(memoization[i]);

  free(memoization);
}

/**
 * @brief Calculate edit distance between two strings. 
 *				Determines minimum number of operation 
 *				to transform @param s2 into @param s1.
 *        If passed string are (or just one is) NULL, program will terminate.
 *        If string lengths are greater than UINT_MAX-1, program will terminate.
 * 
 * @param s1  first string, can't be NULL
 * @param s2  second string, can't be NULL
 * @return unsigned number of operation
 */
unsigned edit_distance_dyn(char *s1, char *s2){
  unsigned **memoization = NULL;
  unsigned s1_len, s2_len;

  if(s1 == NULL){
    ERROR_EXIT("First string is NULL");
  }
  if(s2 == NULL){
    ERROR_EXIT("Second string is NULL");
  }

  if(strlen(s1) >= UINT_MAX){
    ERROR_EXIT("First string too long");
  }
  if(strlen(s2) >= UINT_MAX){
    ERROR_EXIT("Second string too long");
  }
  
  s1_len = (unsigned)strlen(s1);
  s2_len = (unsigned)strlen(s2);

  memoization = init_memoization(memoization, s1_len, s2_len);

  unsigned result = edit_distance(s1, s2, s1_len, s2_len, memoization);

  free_memoization(memoization, s1_len);

  return result;
}