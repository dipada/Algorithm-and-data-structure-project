#include <stdio.h>
#include <string.h>
#include "unity/unity.h"
#include "edit_distance.h"

static void test_empty_strings(void){
  char *s1 = "";
  char *s2 = "";
  TEST_ASSERT_EQUAL_INT(0, edit_distance(s1, s2));
}

static void test_first_empty_string(void){
  char *s1 = "";
  char *s2 = "welcome";
  TEST_ASSERT_EQUAL_INT(7, edit_distance(s1, s2));
}

static void test_second_empty_string(void){
  char *s1 = "hello";
  char *s2 = "";
  TEST_ASSERT_EQUAL_INT(5, edit_distance(s1, s2));
}

static void test_equal_strings(void){
  char *s1 = "pioppo";
  char *s2 = "pioppo";
  TEST_ASSERT_EQUAL_INT(0, edit_distance(s1, s2));
}

static void test_two_string_different_len(void){
  char *s1 = "tassa";
  char *s2 = "passato";
  TEST_ASSERT_EQUAL_INT(4, edit_distance(s1, s2));
}

static void test_two_string_same_len(void){
  char *s1 = "casa";
  char *s2 = "cara";
  TEST_ASSERT_EQUAL_INT(2, edit_distance(s1, s2));
}

int main(void){

  // test session
  UNITY_BEGIN();
  RUN_TEST(test_empty_strings);
  RUN_TEST(test_first_empty_string);
  RUN_TEST(test_second_empty_string);
  RUN_TEST(test_equal_strings);
  RUN_TEST(test_two_string_different_len);
  RUN_TEST(test_two_string_same_len);

  return UNITY_END();
}
