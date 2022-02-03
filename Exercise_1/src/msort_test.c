/**
 * @file msort_test.c
 * @author Daniele Di Palma
 * @brief Test suite for Merge-binary-Insertion-sort
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "unity.h"
#include "msort.h"

/*
 * Test suite for merge binary insertion sort library and algorithms
 */

// precedence relations used in tests
static int precedes_int(void *el_1, void *el_2){
  int *iel_1_p = (int *)el_1;
  int *iel_2_p = (int *)el_2;
  if(*iel_1_p == *iel_2_p){
    return (2);
  }else if(*iel_1_p > *iel_2_p)
    return (1);
  return (0);
}

static int precedes_double(void *el_1, void *el_2){
  double *del_1_p = (double *)el_1;
  double *del_2_p = (double *)el_2;
  if(*del_1_p == *del_2_p){
    return (2);
  }else if(*del_1_p > *del_2_p)
    return (1);
  return (0);
}

static int precedes_string(void *el_1, void *el_2){
  char *sel_1_p = (char *)el_1;
  char *sel_2_p = (char *)el_2;
  if(strcmp(sel_1_p, sel_2_p) == 0){
    return (2);
  }else if(strcmp(sel_1_p, sel_2_p) > 0)
    return (1);
  return (0);
}

// Data elements that are initialized befor each test
static int iel_1, iel_2, iel_3, iel_4, iel_5, iel_6;
static char *sel_1, *sel_2, *sel_3;
static double del_1, del_2, del_3;
int *array_i;
char **array_s;
double *array_d;

void setUp(void){
  iel_1 = -12;
  iel_2 = 0;
  iel_3 = 4;
  iel_4 = -123;
  iel_5 = 10;
  iel_6 = 413;
  sel_1 = "abba";
  sel_2 = "balp";
  sel_3 = "cbaz";
  del_1 = -48.4;
  del_2 = 0.0001;
  del_3 = 1.123;
  array_i = (int *)malloc(3 * sizeof(int));
  array_s = (char **)malloc(3 * sizeof(char *));
  array_d = (double *)malloc(3 * sizeof(double));
}

void tearDown(void){
  free(array_i);
  free(array_s);
  free(array_d);
}

static void test_sort_two_equal_int_el(void){
  int exp_arr[] = {iel_1, iel_1, iel_2};
  
  array_i[0] = iel_2;
  array_i[1] = iel_1;
  array_i[2] = iel_1;
  sort(array_i, sizeof(int), 0, 2, precedes_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(exp_arr, array_i, 3);
}

static void test_sort_three_equal_int_el(void){
  int exp_arr[] = {iel_1, iel_1, iel_1};
  
  array_i[0] = iel_1;
  array_i[1] = iel_1;
  array_i[2] = iel_1;
  sort(array_i, sizeof(int), 0, 2, precedes_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(exp_arr, array_i, 3);
}

static void test_sort_descending_int_array(void){
  int exp_arr[] = {iel_1, iel_2, iel_3};
  
  array_i[0] = iel_3;
  array_i[1] = iel_2;
  array_i[2] = iel_1;
  sort(array_i, sizeof(int), 0, 2, precedes_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(exp_arr, array_i, 3);

}

static void test_sort_ascending_int_array(void){
  int exp_arr[] = {iel_1, iel_2, iel_3};

  array_i[0] = iel_1;
  array_i[1] = iel_2;
  array_i[2] = iel_3;
  sort(array_i, sizeof(int), 0, 2, precedes_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(exp_arr, array_i, 3);
}

static void test_sort_three_int_el(void){
  int exp_arr[] = {iel_1, iel_2, iel_3};
  
  array_i[0] = iel_3;
  array_i[1] = iel_1;
  array_i[2] = iel_2;
  sort(array_i, sizeof(int), 0, 2, precedes_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(exp_arr, array_i, 3);
}

static void test_sort_six_int_el(void){
  int exp_arr[] = {iel_4, iel_1, iel_2, iel_3, iel_5, iel_6};
  array_i[0] = iel_6; 
  array_i[1] = iel_3; 
  array_i[2] = iel_2; 
  array_i[3] = iel_5; 
  array_i[4] = iel_1; 
  array_i[5] = iel_4; 
  sort(array_i, sizeof(int), 0, 5, precedes_int);
  TEST_ASSERT_EQUAL_INT_ARRAY(exp_arr, array_i, 6);
}

static void test_null_array(void){
  int *array = NULL;  
  
  sort(array, 0, 0, 0, precedes_int);
  TEST_ASSERT_EQUAL_PTR(NULL, array);
}

static void test_sort_three_string_el(void){
  char *exp_arr[] = {sel_1, sel_2, sel_3};

  array_s[0] = sel_3;
  array_s[1] = sel_1;
  array_s[2] = sel_2;
  sort(array_s, sizeof(char *), 0, 2, precedes_string);
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_arr, array_s, 3);
}

static void test_sort_two_equal_string_el(void){
  char *exp_arr[] = {sel_1, sel_1, sel_3};

  array_s[0] = sel_3;
  array_s[1] = sel_1;
  array_s[2] = sel_1;
  sort(array_s, sizeof(char *), 0, 2, precedes_string);
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_arr, array_s, 3);
}

static void test_sort_three_equal_string_el(void){
  char *exp_arr[] = {sel_1, sel_1, sel_1};

  array_s[0] = sel_1;
  array_s[1] = sel_1;
  array_s[2] = sel_1;
  sort(array_s, sizeof(char *), 0, 2, precedes_string);
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_arr, array_s, 3);
}

static void test_sort_descending_string_array(void){
  char *exp_arr[] = {sel_1, sel_2, sel_3};

  array_s[0] = sel_3;
  array_s[1] = sel_2;
  array_s[2] = sel_1;
  sort(array_s, sizeof(char *), 0, 2, precedes_string);
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_arr, array_s, 3);

}

static void test_sort_ascending_string_array(void){
  char *exp_arr[] = {sel_1, sel_2, sel_3};

  array_s[0] = sel_1;
  array_s[1] = sel_2;
  array_s[2] = sel_3;
  sort(array_s, sizeof(char *), 0, 2, precedes_string);
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_arr, array_s, 3);
}

static void test_sort_empty_string(void){
  char *exp_arr[] = {sel_1, sel_2, ""};

  array_s[0] = "";
  array_s[1] = sel_1;
  array_s[2] = sel_2;
  sort(array_s, sizeof(char *), 0, 2, precedes_string);
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_arr, array_s, 3);
}

static void test_sort_null_string(void){
  char *exp_arr[] = {NULL, sel_1, sel_2};

  array_s[0] = sel_1;
  array_s[1] = sel_2;
  array_s[2] = NULL;
  sort(array_s, sizeof(char *), 0, 2, precedes_string);
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_arr, array_s, 3);
}

static void test_sort_two_equal_double_el(void){
  double exp_arr[] = {del_1, del_1, del_2};
  
  array_d[0] = del_2;
  array_d[1] = del_1;
  array_d[2] = del_1;
  sort(array_d, sizeof(double), 0, 2, precedes_double);
  TEST_ASSERT_EQUAL_INT_ARRAY(exp_arr, array_d, 3);
}

static void test_sort_three_equal_double_el(void){
  double exp_arr[] = {del_1, del_1, del_1};
  
  array_d[0] = del_1;
  array_d[1] = del_1;
  array_d[2] = del_1;
  sort(array_d, sizeof(double), 0, 2, precedes_double);
  TEST_ASSERT_EQUAL_INT_ARRAY(exp_arr, array_d, 3);
}

static void test_sort_descending_double_array(void){
  double exp_arr[] = {del_1, del_2, del_3};
  
  array_d[0] = del_3;
  array_d[1] = del_2;
  array_d[2] = del_1;
  sort(array_d, sizeof(double), 0, 2, precedes_double);
  TEST_ASSERT_EQUAL_INT_ARRAY(exp_arr, array_d, 3);

}

static void test_sort_ascending_double_array(void){
  double exp_arr[] = {del_1, del_2, del_3};

  array_d[0] = del_1;
  array_d[1] = del_2;
  array_d[2] = del_3;
  sort(array_d, sizeof(double), 0, 2, precedes_double);
  TEST_ASSERT_EQUAL_INT_ARRAY(exp_arr, array_d, 3);
}

static void test_sort_three_double_el(void){
  double exp_arr[] = {del_1, del_2, del_3};
  
  array_d[0] = del_3;
  array_d[1] = del_1;
  array_d[2] = del_2;
  sort(array_d, sizeof(double), 0, 2, precedes_double);
  TEST_ASSERT_EQUAL_INT_ARRAY(exp_arr, array_d, 3);
}

int main(void){
  
  // test session
  UNITY_BEGIN();

  RUN_TEST(test_sort_three_string_el);
  RUN_TEST(test_sort_two_equal_string_el);
  RUN_TEST(test_sort_three_equal_string_el);
  RUN_TEST(test_sort_descending_string_array);
  RUN_TEST(test_sort_ascending_string_array);
  RUN_TEST(test_sort_empty_string);
  RUN_TEST(test_sort_null_string);

  RUN_TEST(test_sort_two_equal_int_el);
  RUN_TEST(test_sort_three_equal_int_el);
  RUN_TEST(test_sort_descending_int_array);
  RUN_TEST(test_sort_ascending_int_array);
  RUN_TEST(test_sort_three_int_el);
  RUN_TEST(test_sort_six_int_el);
  RUN_TEST(test_null_array);

  RUN_TEST(test_sort_two_equal_double_el);
  RUN_TEST(test_sort_three_equal_double_el);
  RUN_TEST(test_sort_descending_double_array);
  RUN_TEST(test_sort_ascending_double_array);
  RUN_TEST(test_sort_three_double_el);

  return UNITY_END();
}

