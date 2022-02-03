/**
 * @file edit_distance.c
 * @author Daniele Di Palma
 * @brief Recursive version of edit distance without dynamic programming
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "edit_distance.h"

#define ERROR_EXIT(x){  fprintf(stderr, "[%s]-Line:%d >> " x "\n",  \
                        __FILE__,                                   \
                        __LINE__);                                  \
                      exit(EXIT_FAILURE);}


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
 * @return unsigned number of operation
 */
static unsigned no_op(char *s1, char *s2){
  if (s1[0] == s2[0]){
    return edit_distance(rest(s1), rest(s2));
  }
  else{
    return UINT_MAX;
  }
}

/**
 * @brief Delete a character on second string
 * 
 * @param s1 first string, can't be NULL
 * @param s2 second string, can't be NULL
 * @return unsigned number of operation
 */
static unsigned canc(char *s1, char *s2){
  return 1 + edit_distance(s1, rest(s2));
}

/**
 * @brief Insert a character on head of second string
 * 
 * @param s1 first string, can't be NULL
 * @param s2 second string, can't be NULL
 * @return unsigned number of operation
 */
static unsigned ins(char *s1, char *s2){
  return 1 + edit_distance(rest(s1), s2);
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

unsigned edit_distance(char *s1, char *s2){
  if(s1 == NULL){
    ERROR_EXIT("First string is NULL");
  }
  if(s2 == NULL){
    ERROR_EXIT("Second string is NULL");
  }

  if(strlen(s1) == 0){
    return (unsigned)strlen(s2);
  }

  if(strlen(s2) == 0){
    return (unsigned)strlen(s1);
  }

  return min(no_op(s1, s2), canc(s1, s2), ins(s1, s2));
}
