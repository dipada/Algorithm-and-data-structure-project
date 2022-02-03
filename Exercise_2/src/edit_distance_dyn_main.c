/**
 *
 * @file edit_distance_dyn_main.c
 * @author Daniele Di Palma
 * @brief Application that suggests possible corrections of a text file
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "edit_distance_dyn.h"

#define ERROR_EXIT(x){  fprintf(stderr, "[%s]-Line:%d >> " x "\n",  \
                        __FILE__,                                   \
                        __LINE__);                                  \
                      exit(EXIT_FAILURE);}

#define BUFFER_SIZE (1024)
#define INITIAL_CAPACITY (2)
#define USER_FILE_DELIM (" .,:\n")
#define DICTIONARY_DELIM (" \n")


/**
 * @brief It rappresents corrections for a word
 * 
 */
struct WordCorrections{
  char *word; // word on which corrections are based

  // Rappresents single correction for a word
  struct Correction{
    char *correction;         // correction for word
    unsigned edit_distance;   // edit distance of this correction by word
  } *array_corrections_word;  // array of all corrections for word
  
  unsigned min_ed;                      // min edit distance found between all corrections
  unsigned num_corrections;             // number of total corrections found
  unsigned capacity_array_corrections;  // corrections_array capacity
};

/**
 * @brief It rappresents an array of corrections (Multiple words)
 *        Used for maintain corrections of user_file (correctme.txt)
 * 
 */
typedef struct _ArrayCorrections{
  
  struct WordCorrections *array;  // array of corrections 
  unsigned array_capacity;        // capacity of array
  unsigned num_el;                // number of array elements

}ArrayCorrections;

/**
 * @brief It rappresents an array of string for this specific implementation.
 *        Used for rappresent user input file (correctme.txt) and dictionary
 * 
 */
typedef struct _ArrayWords{
  char **word;
  unsigned array_capacity;
  unsigned el_num;
}ArrayWords;

/**
 * @brief This function read passed file, parse it with given delimiters 
 *        and load it in ArrayWords structure.
 * 
 * @param file_path     file where operate
 * @param array_words   pointer to structure where parsed data will be insert
 * @param delimiters    delimiters to use for correcting parse the file
 */
static void load_file(const char *file_path, ArrayWords *array_words, char *delimiters){
  FILE *fp = NULL;
  char buffer[BUFFER_SIZE];
  char *read_line_p = NULL;

  fp = fopen(file_path,"r");
  if(fp == NULL){
    ERROR_EXIT("unable to open the file");
  }

  while(fgets(buffer, BUFFER_SIZE, fp) != NULL){
    read_line_p = (char *)malloc(strlen(buffer)+1 * sizeof(char));
    if(read_line_p == NULL){
      ERROR_EXIT("unable to allocate memory for the read line");
    }
    strcpy(read_line_p, buffer);
    char *parsed_string = strtok(read_line_p, delimiters);
    
    while(parsed_string != NULL){
      if(array_words->array_capacity <= array_words->el_num){
        array_words->word = realloc(array_words->word, ((array_words->array_capacity*2)*sizeof(char *)));
        array_words->array_capacity = array_words->array_capacity * 2;
      }

      array_words->word[array_words->el_num] = (char *)malloc(strlen(parsed_string)+1 * sizeof(char));
      strcpy(array_words->word[array_words->el_num], parsed_string);

      array_words->el_num++;
      parsed_string = strtok(NULL, delimiters);
    }
    free(read_line_p);
  }

  fclose(fp);
  printf("Loaded\n");
}

/**
 * @brief This function allocate and initialize a given pointer to ArrayWords struct
 * 
 * @param arraywords    struct that will be allocated and inizialized
 * @return ArrayWords*  address to initialized ArrayWords struct
 */
static ArrayWords* init_structure_arraywords(ArrayWords *arraywords){
  arraywords = (ArrayWords *)malloc(sizeof(ArrayWords));
  if(arraywords == NULL){
    ERROR_EXIT("Unable to allocate ArrayWords structure");
  }

  arraywords->word = (char **)malloc(INITIAL_CAPACITY * sizeof(char *));
  if(arraywords == NULL){
    ERROR_EXIT("Unable to allocate word array of pointers");
  }
  arraywords->el_num = 0;
  arraywords->array_capacity = INITIAL_CAPACITY;

  return arraywords;
}

/**
 * @brief This function allocate and initialize a given pointer to ArrayCorrections struct
 * 
 * @param array_corrections   struct that will be allocated and inizialized
 * @return ArrayCorrections*  address to initialized ArrayCorrections struct
 */
static ArrayCorrections* init_array_corrections(ArrayCorrections *array_corrections){

  array_corrections = (ArrayCorrections *)malloc(sizeof(ArrayCorrections));
  if(array_corrections == NULL){
    ERROR_EXIT("Unable to allocate Array of corrections structure")
  }
  array_corrections->array = (struct WordCorrections *)malloc(INITIAL_CAPACITY * sizeof(struct WordCorrections));
  if(array_corrections->array == NULL){
    ERROR_EXIT("Unable to allocate array");
  }

  array_corrections->array_capacity = INITIAL_CAPACITY;
  array_corrections->num_el = 0;

  for(register unsigned i = 0; i < INITIAL_CAPACITY; i++){
    array_corrections->array[i].array_corrections_word = (struct Correction*)malloc(INITIAL_CAPACITY * sizeof(struct Correction));
    for(register unsigned j = 0; j < INITIAL_CAPACITY; j++){
      array_corrections->array[i].array_corrections_word[j].correction = NULL;
      array_corrections->array[i].array_corrections_word[j].edit_distance = UINT_MAX;
    }
    array_corrections->array[i].capacity_array_corrections = INITIAL_CAPACITY;
    array_corrections->array[i].min_ed = UINT_MAX;
    array_corrections->array[i].num_corrections = 0;
  }
  return array_corrections;
}


/**
 * @brief This function de-allocate struct given as ArrayWords pointer
 * 
 * @param arraywords  pointer to ArrayWords structure that will be de-allocate
 */
static void free_structure_arraywords(ArrayWords *arraywords){
  for(register unsigned i = 0; i < arraywords->el_num; i++){
    free(arraywords->word[i]);
  }
  free(arraywords->word);
  free(arraywords);
}


/**
 * @brief This functions de-allocate struct given as ArrayCorrections pointer
 * 
 * @param array_corrections   pointer to ArrayCorrections structure that will be de-allocate
 */
static void free_array_corrections(ArrayCorrections *array_corrections){
  for(register unsigned i = 0; i < array_corrections->num_el; i++){
    free(array_corrections->array[i].array_corrections_word);
  }
  free(array_corrections->array);
  free(array_corrections);  
}

/**
 * @brief This function compute corrections for user file, and save corrections in a struct.
 *        Used for compute correctionts of (correctme.txt).
 * 
 * @param user_file           pointer to ArrayWords struct where user file words are stored
 * @param dictionary          pointer to ArrayWords struct where dictionary words are stored
 * @param array_corrections   pointer to ArrayCorrections struct where corrections of all words will be stored
 * @return double             total time spent for compute all corrections
 */
static double compute_corrections(ArrayWords *user_file, ArrayWords *dictionary, ArrayCorrections *array_corrections){
  clock_t start_time = 0;
  double total_time = 0;
  unsigned result_ed, act_dim, index;

  for(register unsigned i = 0; i < user_file->el_num; i++){

    if(array_corrections->num_el >= array_corrections->array_capacity){
      array_corrections->array = (struct WordCorrections *)realloc(array_corrections->array, (sizeof(struct WordCorrections) *array_corrections->array_capacity*2));
      if(array_corrections->array == NULL){
        ERROR_EXIT("Unable to re-allocate array");
      }
      for(register unsigned k = array_corrections->array_capacity; k < array_corrections->array_capacity*2; ++k){
        
        array_corrections->array[k].min_ed = UINT_MAX;
        array_corrections->array[k].array_corrections_word = (struct Correction *)malloc(INITIAL_CAPACITY * sizeof(struct Correction));
        if(array_corrections->array[k].array_corrections_word == NULL){
          ERROR_EXIT("Unable to re-allocate array corrections word");
        }
        array_corrections->array[k].capacity_array_corrections = INITIAL_CAPACITY;
        array_corrections->array[k].num_corrections = 0;
        array_corrections->array[k].word = NULL;
      }
      array_corrections->array_capacity *= 2;
    }
    
    array_corrections->array[i].word = user_file->word[i];

    for(register unsigned j = 0; j < dictionary->el_num; j++){

      start_time = clock();
      result_ed = edit_distance_dyn(dictionary->word[j], user_file->word[i]);
      total_time += (double)(clock() - start_time)/CLOCKS_PER_SEC;

      if(result_ed <= array_corrections->array[i].min_ed){
        if(array_corrections->array[i].num_corrections >= array_corrections->array[i].capacity_array_corrections){
          act_dim = array_corrections->array[i].capacity_array_corrections;
          array_corrections->array[i].array_corrections_word = realloc(array_corrections->array[i].array_corrections_word, ((act_dim*2)*sizeof(struct Correction)));
          if(array_corrections->array[i].array_corrections_word == NULL){
            ERROR_EXIT("Unable to re-allocate array corrections word");
          }
          array_corrections->array[i].capacity_array_corrections *= 2;
        }
        
        array_corrections->array[i].min_ed = result_ed;
        index = array_corrections->array[i].num_corrections;
        array_corrections->array[i].array_corrections_word[index].correction = dictionary->word[j];
        
        array_corrections->array[i].array_corrections_word[index].edit_distance = result_ed;
        array_corrections->array[i].num_corrections++;
      }
    }
    
    array_corrections->num_el++;
    printf("\r%.2f%%", ((float)i/(float)user_file->el_num*100));
  }
  printf("\rCompleted\n");
  return total_time;
}

/**
 * @brief This function prints results obtained
 * 
 * @param array_corrections   pointer to ArrayCorrections where corrections of all words are stored
 * @param execution_time      execution time to print
 */
static void print_results(ArrayCorrections *array_corrections, double *execution_time){
  printf("\nWant print result? [y/n] >> ");
  if(getchar() == 'y'){
    for(unsigned i = 0; i < array_corrections->num_el; i++){
      printf("\033[0;33m%s\033[0m\n", array_corrections->array[i].word);
      for(unsigned j = 0; j < array_corrections->array[i].num_corrections; j++){
        if(array_corrections->array[i].min_ed == array_corrections->array[i].array_corrections_word[j].edit_distance)
        printf("|\n|-- %s\n", array_corrections->array[i].array_corrections_word[j].correction);
      }
      printf("|\n*-> edit distance: %d\n",array_corrections->array[i].min_ed);
      printf("\n");
    }
  }
  printf("Execution time: %f\n", *execution_time);
}

static void correct_text_with_dictionary(const char *file_path, const char *dictionary_path){

  ArrayWords *user_file = NULL, *dictionary = NULL;
  ArrayCorrections *array_corrections = NULL;
  double execution_time = 0;
  
  setvbuf(stdout, NULL, _IONBF, 0); // For some terminal compatibility

  user_file = init_structure_arraywords(user_file);
  dictionary = init_structure_arraywords(dictionary);

  printf("Loading file... ");
  load_file(file_path, user_file, USER_FILE_DELIM);

  printf("Loading dictionary... ");
  load_file(dictionary_path, dictionary, DICTIONARY_DELIM);
  
  array_corrections = init_array_corrections(array_corrections);

  printf("\nCorrecting  *\n          <-*\r");
  execution_time = compute_corrections(user_file, dictionary, array_corrections);

  print_results(array_corrections, &execution_time);

  free_structure_arraywords(user_file);
  free_structure_arraywords(dictionary);
  free_array_corrections(array_corrections);
}

int main(int argc, char **argv){
  
  if(argc < 2){
    printf("Usage: dyn_edit_distance_main <file to be correct> <dictionary>\n");
    exit(EXIT_FAILURE);
  }

  correct_text_with_dictionary(argv[1],argv[2]);

  printf("Exiting\n");
  exit(EXIT_SUCCESS);
}