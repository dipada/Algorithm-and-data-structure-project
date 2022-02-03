/**
 * @file edit_distance_main.c
 * @author Daniele Di Palma
 * @brief Simple program for calculate edit distance between two string. Hint: use short strings.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "edit_distance.h"

int main(int argc, char **argv){
  if(argc < 3 || argc > 3){
    fprintf(stderr, "Usage: edit_distance_main <first string> <second string>\n"                      \
        "Use \"\" for strings that contains whitespace.\nExample: Hello there -> \"Hello there\"\n");
    exit(EXIT_FAILURE);
  }
  
  clock_t start_time = clock();
  unsigned result = edit_distance(argv[1], argv[2]);
  double elapsed_time = (double)(clock() - start_time)/CLOCKS_PER_SEC;

  printf("First string given: <%s>\nSecond string given: <%s>\nedit distance: [%d], time: %fs\n",     \
          argv[1], argv[2], result, elapsed_time);

  exit(EXIT_SUCCESS);
}