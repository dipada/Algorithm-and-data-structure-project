/**
 * @file ordered_records_main.c
 * @author Daniele Di Palma
 * @brief Application for sort records
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "msort.h"

#define ERROR_EXIT(x) { fprintf(stderr, "[%s]-Line:%d >> "x"\n",    \
                          __FILE__,                                 \
                          __LINE__ );                               \
                        exit(EXIT_FAILURE);}                        \

#define INITIAL_CAPACITY 4
#define BUFFER_SIZE 1024
#define ASCENDING_SORT (1)
#define DESCENDING_SORT (0)

// It rappresents a single record internal struct, specific for this implementation
typedef struct _Record{
  int id_field;
  char *string_field;
  int integer_field;
  double float_field;
} Record;

// It rappresents internal structure array of records of this implementation
typedef struct _RecordArray{

  Record *array;
  unsigned long el_num;
  unsigned long array_capacity;

} RecordArray;

/**
 * @brief       It takes as input two record pointer and compare integer fields 
 *              of two records using ascending method
 * 
 * @param r1_p  first record pointer
 * @param r2_p  second record pointer
 * @return      int return 1 if the integer field of the first record is greater than
 *              second, 2 if are equals, 0 otherwise
 */
static int precedes_record_int_ascending(void *r1_p, void *r2_p){
  if(r1_p == NULL){
    ERROR_EXIT("first parameter is a null pointer");
  }
  if(r2_p == NULL){
    ERROR_EXIT("second parameter is a null pointer");
  }

  Record *rec1_p = *(Record **)r1_p;
  Record *rec2_p = *(Record **)r2_p;

  if (rec1_p->integer_field == rec2_p->integer_field){
    return (2);
  }else if (rec1_p->integer_field > rec2_p->integer_field)
    return (1);
  return (0);
}

/**
 * @brief       It takes as input two record pointer and compare integer fields 
 *              of two records using descending method
 * 
 * @param r1_p  first record pointer
 * @param r2_p  second record pointer
 * @return      int return 1 if the integer field of the first record is less than
 *              second, 2 if are equals, 0 otherwise
 */
static int precedes_record_int_descending(void *r1_p, void *r2_p){
  if(r1_p == NULL){
    ERROR_EXIT("first parameter is a null pointer");
  }
  if(r2_p == NULL){
    ERROR_EXIT("second parameter is a null pointer");
  }

  Record *rec1_p = *(Record **)r1_p;
  Record *rec2_p = *(Record **)r2_p;
  if (rec1_p->integer_field == rec2_p->integer_field){
    return (2);
  }else if (rec1_p->integer_field < rec2_p->integer_field)
    return (1);
  return (0);
}

/**
 * @brief       It takes as input two record pointer and compare string fields 
 *              of two records using ascending method
 * 
 * @param r1_p  first record pointer
 * @param r2_p  second record pointer
 * @return      int return 1 if the string field of the first record is greater than
 *              second, 2 if are equals, 0 otherwise
 */
static int precedes_record_string_ascending(void *r1_p, void *r2_p){
  if(r1_p == NULL){
    ERROR_EXIT("first parameter is a null pointer");
  }
  if(r2_p == NULL){
    ERROR_EXIT("second parameter is a null pointer");
  }

  Record *rec1_p = *(Record **)r1_p;
  Record *rec2_p = *(Record **)r2_p;
  int cmp = strcmp(rec1_p->string_field, rec2_p->string_field);
  if (cmp == 0){
    return (2);
  }else if (cmp > 0)
    return (1);
  return (0);
}

/**
 * @brief       It takes as input two record pointer and compare string fields 
 *              of two records using descending method
 * 
 * @param r1_p  first record pointer
 * @param r2_p  second record pointer
 * @return      int return 1 if the string field of the first record is less than
 *              second, 2 if are equals, 0 otherwise
 */
static int precedes_record_string_descending(void *r1_p, void *r2_p){
  if(r1_p == NULL){
    ERROR_EXIT("first parameter is a null pointer");
  }
  if(r2_p == NULL){
    ERROR_EXIT("second parameter is a null pointer");
  }

  Record *rec1_p = *(Record **)r1_p;
  Record *rec2_p = *(Record **)r2_p;
  int cmp = strcmp(rec1_p->string_field, rec2_p->string_field);
  if (cmp == 0){
    return (2);
  }else if (cmp < 0)
    return (1);
  return (0);
}

/**
 * @brief       It takes as input two record pointer and compare double fields 
 *              of two records using ascending method
 * 
 * @param r1_p  first record pointer
 * @param r2_p  second record pointer
 * @return      int return 1 if the double field of the first record is greater than
 *              second, 2 if are equals, 0 otherwise
 */
static int precedes_record_double_ascending(void *r1_p, void *r2_p){
  if(r1_p == NULL){
    ERROR_EXIT("first parameter is a null pointer");
  }
  if(r2_p == NULL){
    ERROR_EXIT("second parameter is a null pointer");
  }

  Record *rec1_p = *(Record **)r1_p;
  Record *rec2_p = *(Record **)r2_p;
  if (rec1_p->float_field == rec2_p->float_field){
    return (2);
  }else if (rec1_p->float_field > rec2_p->float_field)
    return (1);
  return (0);
}

/**
 * @brief       It takes as input two record pointer and compare double fields 
 *              of two records using descending method
 * 
 * @param r1_p  first record pointer
 * @param r2_p  second record pointer
 * @return      int return 1 if the double field of the first record is less than
 *              second, 2 if are equals, 0 otherwise
 */
static int precedes_record_double_descending(void *r1_p, void *r2_p){
  if(r1_p == NULL){
    ERROR_EXIT("first parameter is a null pointer");
  }
  if(r2_p == NULL){
    ERROR_EXIT("second parameter is a null pointer");
  }

  Record *rec1_p = *(Record **)r1_p;
  Record *rec2_p = *(Record **)r2_p;
  if (rec1_p->float_field == rec2_p->float_field){
    return (2);
  }else if (rec1_p->float_field < rec2_p->float_field)
    return (1);
  return (0);
}

/**
 * @brief This function add a record to array of records, realloc if necessary
 * 
 * @param record_array  array of records 
 * @param record_p      record to add
 */
static void add_record(RecordArray *record_array, Record *record_p){
  if(record_array->el_num >= record_array->array_capacity){
    record_array->array = (Record *)realloc(record_array->array, 2*(record_array->array_capacity)*sizeof(Record));
    if(record_array->array == NULL){
      ERROR_EXIT("unable to reallocate memory for host the new element");
    }

    record_array->array_capacity *= 2;
  }
  
  unsigned long index = record_array->el_num;
  
  (record_array->array)[index].id_field = record_p->id_field;
  (record_array->array)[index].integer_field = record_p->integer_field;
  (record_array->array)[index].string_field = record_p->string_field;
  (record_array->array)[index].float_field = record_p->float_field;

  (record_array->el_num)++;
}

/**
 * @brief Load data in the file, create record and then add it to the array
 * 
 * @param file_name     file for load data
 * @param record_array  array where insert records
 */
static void load_array(const char *file_name, RecordArray *record_array) {
  char buffer[BUFFER_SIZE];
  FILE *fp = NULL;

  printf("\nLoading data from file...\n");
  fp = fopen(file_name, "r");
  if (fp == NULL) {
    ERROR_EXIT("unable to open the file");
  }
  
  while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
    
    Record *read_record_p = malloc(sizeof(Record));
    if (read_record_p == NULL) {
      ERROR_EXIT("unable to allocate memory for the read record");
    }
  
    char *id_field_in_read_line_p = strtok(buffer, ",");
    char *string_field_in_read_line_p = strtok(NULL, ",");
    char *integer_field_in_read_line_p = strtok(NULL, ",");
    char *float_field_in_read_line_p = strtok(NULL, ",");
    
    read_record_p->id_field = atoi(id_field_in_read_line_p);
    read_record_p->string_field = malloc((strlen(string_field_in_read_line_p)+1) * sizeof(char));
    if (read_record_p->string_field == NULL) {
      ERROR_EXIT("unable to allocate memory for the string field of the read record");
    }
    strcpy(read_record_p->string_field, string_field_in_read_line_p);
    read_record_p->integer_field = atoi(integer_field_in_read_line_p);
    read_record_p->float_field = atof(float_field_in_read_line_p);
    
    add_record(record_array, read_record_p);

    free(read_record_p);
    
  }
  fclose(fp);
  printf("Data loaded\n");
}

/**
 * @brief initialize the RecordArray structure
 * 
 * @param record_array structure to inizialize
 */
static void init_record_array(RecordArray *record_array){

  record_array->array = (Record *)malloc(INITIAL_CAPACITY * sizeof(Record));
  if(record_array->array == NULL){
    ERROR_EXIT("unable to allocate memory for records");
  }
  record_array->array_capacity = INITIAL_CAPACITY;
  record_array->el_num = 0; 
}

/**
 * @brief Print records in array, according to format of this implementation
 * 
 * @param record_array_p  array to print
 * @param num_el          number of array elements
 */
static void print_records(Record **record_array_p, unsigned long num_el){
  for(register unsigned long i = 0; i < num_el; ++i){
    printf("ID: %d %s %d %f\n", record_array_p[i]->id_field, record_array_p[i]->string_field, record_array_p[i]->integer_field, record_array_p[i]->float_field);
  }
}

/**
 * @brief Free allocated memory by array
 * 
 * @param record_array struct where to free
 */
static void free_record_array(RecordArray* record_array) {

  for(register unsigned long i=0; i < record_array->el_num; i++)
    free(record_array->array[i].string_field);

  free(record_array->array);
}

/**
 * @brief Allocate memory in a single block allocation for array of records pointers by original array loaded.
 * 
 * @param record_array  struct of original array
 * @return Record**     allocated array of records pointers
 */
static Record **init_array_pointers(const RecordArray *record_array){
  Record **record_array_p = (Record **)malloc(sizeof(Record *) * record_array->el_num);
  for(unsigned long i = 0; i < record_array->el_num; i++){
    record_array_p[i] = &(record_array->array)[i];
  }
  return record_array_p;
}

/**
 * @brief It drive the program
 * 
 * @param file_name     file of data
 * @param sorting_mode  sorting mode (ascending/descending)
 */
static void start_with_comparison_function(const char *file_name, int sorting_mode){
  RecordArray record_array;
  Record **record_array_p;
  
  clock_t start_time;
  double elapsed_integer_time, elapsed_string_time, elapsed_double_time;
  init_record_array(&record_array);
  load_array(file_name, &record_array);

  printf("\nStart sorting\n");

  if(sorting_mode == ASCENDING_SORT){
    record_array_p = init_array_pointers(&record_array);
    start_time = clock();
    sort(record_array_p, sizeof(Record *), 0, record_array.el_num-1, precedes_record_int_ascending);
    elapsed_integer_time = (double)(clock() - start_time)/CLOCKS_PER_SEC;
    printf(".\n"); 
  
    record_array_p = init_array_pointers(&record_array);
    start_time = clock();
    sort(record_array_p, sizeof(Record *), 0, record_array.el_num-1, precedes_record_string_ascending);
    elapsed_string_time = (double)(clock() - start_time)/CLOCKS_PER_SEC;
    printf(".\n"); 

    record_array_p = init_array_pointers(&record_array);
    start_time = clock();
    sort(record_array_p, sizeof(Record *), 0, record_array.el_num-1, precedes_record_double_ascending);
    elapsed_double_time = (double)(clock() - start_time)/CLOCKS_PER_SEC;
    printf(".\n"); 

  }else{
    record_array_p = init_array_pointers(&record_array);
    start_time = clock();  
    sort(record_array_p, sizeof(Record *), 0, record_array.el_num-1, precedes_record_int_descending);
    elapsed_integer_time = (double)(clock() - start_time)/CLOCKS_PER_SEC;
    printf(".\n");
    
    record_array_p = init_array_pointers(&record_array);
    start_time = clock();
    sort(record_array_p, sizeof(Record *), 0, record_array.el_num-1, precedes_record_string_descending);
    elapsed_string_time = (double)(clock() - start_time)/CLOCKS_PER_SEC;
    printf(".\n"); 
    
    record_array_p = init_array_pointers(&record_array);
    start_time = clock();
    sort(record_array_p, sizeof(Record *), 0, record_array.el_num-1, precedes_record_double_descending);
    elapsed_double_time = (double)(clock() - start_time)/CLOCKS_PER_SEC;
    printf(".\n");  
  }

    getchar();
    printf("End\nWant print result? [y/n] >> ");
    if(getchar() == 'y'){
      printf("\n");
      print_records(record_array_p, record_array.el_num);
    }

    printf("\nTime to sort field (sec):\nInteger\t-> %f\nString\t-> %f\nDouble\t-> %f\nTotal\t-> %f\n", \
            elapsed_integer_time, elapsed_string_time, elapsed_double_time,                       \
            (elapsed_integer_time+elapsed_string_time+elapsed_double_time));

    free(record_array_p);
    free_record_array(&record_array);
}

int main(int argc, char **argv){

  setvbuf(stdout, NULL, _IONBF, 0);
  if(argc < 2){
    printf("Usage: ordered_array_main <file_name>\n");
    exit(EXIT_FAILURE);
  }

  printf("Select sort order:\n(1)   Ascending order\n(2)   Descending order\n(any) Exit\n>> ");
  int user_choise = getchar();
  if(user_choise == '1'){
    start_with_comparison_function(argv[1], ASCENDING_SORT);
  }else if(user_choise == '2'){
    start_with_comparison_function(argv[1], DESCENDING_SORT);
  }
  
  printf("Exiting..\n");

  exit(EXIT_SUCCESS);
}