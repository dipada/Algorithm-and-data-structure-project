#ifndef _EDIT_DISTANCE_H_
#define _EDIT_DISTANCE_H_

/**
 * @brief Calculate edit distance between two strings. 
 *				Determines minimum number of operation 
 *				to transform @param s2 into @param s1.
 * 
 * @param s1  first string, can't be NULL
 * @param s2  second string, can't be NULL
 * @return unsigned number of operation
 */
unsigned edit_distance(char *s1, char *s2);

#endif