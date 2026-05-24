#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asserts.h"
// Necessary due to static functions in game.c
#include "game.c"

/* Look at asserts.c for some helpful assert functions */

int greater_than_forty_two(int x) { return x > 42; }

bool is_vowel(char c) {
  char *vowels = "aeiouAEIOU";
  for (int i = 0; i < strlen(vowels); i++) {
    if (c == vowels[i]) {
      return true;
    }
  }
  return false;
}

/*
  Example 1: Returns true if all test cases pass. False otherwise.
    The function greater_than_forty_two(int x) will return true if x > 42. False otherwise.
    Note: This test is NOT comprehensive
*/
bool test_greater_than_forty_two() {
  int testcase_1 = 42;
  bool output_1 = greater_than_forty_two(testcase_1);
  if (!assert_false("output_1", output_1)) {
    return false;
  }

  int testcase_2 = -42;
  bool output_2 = greater_than_forty_two(testcase_2);
  if (!assert_false("output_2", output_2)) {
    return false;
  }

  int testcase_3 = 4242;
  bool output_3 = greater_than_forty_two(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  return true;
}

/*
  Example 2: Returns true if all test cases pass. False otherwise.
    The function is_vowel(char c) will return true if c is a vowel (i.e. c is a,e,i,o,u)
    and returns false otherwise
    Note: This test is NOT comprehensive
*/
bool test_is_vowel() {
  char testcase_1 = 'a';
  bool output_1 = is_vowel(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'e';
  bool output_2 = is_vowel(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 'i';
  bool output_3 = is_vowel(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'o';
  bool output_4 = is_vowel(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'u';
  bool output_5 = is_vowel(testcase_5);
  if (!assert_true("output_5", output_5)) {
    return false;
  }

  char testcase_6 = 'k';
  bool output_6 = is_vowel(testcase_6);
  if (!assert_false("output_6", output_6)) {
    return false;
  }

  return true;
}

/* Task 4.1 */

bool test_is_tail() {
  char testcase1 = 'w';
  bool output1 = is_tail(testcase1);
  if (!assert_true("output1", output1)) {
    return false;
  }

  char testcase2 = 'W';
  bool output2 = is_tail(testcase2);
  if (!assert_false("output2", output2)) {
    return false; 
  }

  char testcase3 = '>';
  bool output3 = is_tail(testcase3);
  if (!assert_false("output3", output3)) {
    return false;
  }

  char testcase4 = 'k';
  bool output4 = is_tail(testcase4);
  if (!assert_false("output4", output4)) {
    return false;
  }

  return true;
}

bool test_is_head() {
  char testcase1 = 'w';
  bool output1 = is_head(testcase1);
  if (!assert_false("output1", output1)) {
    return false;
  }

  char testcase2 = 'W';
  bool output2 = is_head(testcase2);
  if (!assert_true("output2", output2)) {
    return false; 
  }

  char testcase3 = '>';
  bool output3 = is_head(testcase3);
  if (!assert_false("output3", output3)) {
    return false;
  }

  char testcase4 = 'k';
  bool output4 = is_head(testcase4);
  if (!assert_false("output4", output4)) {
    return false;
  }

  return true;
}

bool test_is_snake() {
  char testcase1 = 'w';
  bool output1 = is_snake(testcase1);
  if (!assert_true("output1", output1)) {
    return false;
  }

  char testcase2 = 'W';
  bool output2 = is_snake(testcase2);
  if (!assert_true("output2", output2)) {
    return false; 
  }

  char testcase3 = '>';
  bool output3 = is_snake(testcase3);
  if (!assert_true("output3", output3)) {
    return false;
  }

  char testcase4 = 'k';
  bool output4 = is_snake(testcase4);
  if (!assert_false("output4", output4)) {
    return false;
  }

  return true;
}

bool test_body_to_tail() {
  char testcase1 = '^';
  char output1 = body_to_tail(testcase1);
  if (!assert_equals_char("output1", output1, 'w')) {
    return false;
  } 

  char testcase2 = '<';
  char output2 = body_to_tail(testcase2);
  if (!assert_equals_char("output2", output2, 'a')) {
    return false;
  } 

  char testcase3 = 'v';
  char output3 = body_to_tail(testcase3);
  if (!assert_equals_char("output3", output3, 's')) {
    return false;
  }

  char testcase4 = '>';
  char output4 = body_to_tail(testcase4);
  if (!assert_equals_char("output4", output4, 'd')) {
    return false;
  }

  char testcase5 = 'w';
  char output5 = body_to_tail(testcase5);
  if (!assert_equals_char("output5", output5, '?')) {
    return false;
  }

  return true;
}

bool test_head_to_body() {
  char testcase1 = 'W';
  char output1 = head_to_body(testcase1);
  if (!assert_equals_char("output1", output1, '^')) {
    return false;
  }

  char testcase2 = 'A';
  char output2 = head_to_body(testcase2);
  if (!assert_equals_char("output2", output2, '<')) {
    return false;
  }

  char testcase3 = 'S';
  char output3 = head_to_body(testcase3);
  if (!assert_equals_char("output3", output3, 'v')) {
    return false;
  }

  char testcase4 = 'D';
  char output4 = head_to_body(testcase4);
  if (!assert_equals_char("output4", output4, '>')) {
    return false;
  }

  char testcase5 = 'w';
  char output5 = head_to_body(testcase5);
  if (!assert_equals_char("output5", output5, '?')) {
    return false;
  } 

  return true;
}

bool test_get_next_row() {
  char testcase1 = 'v';
  unsigned int output1 = get_next_row(5, testcase1);
  if (!assert_equals_unsigned_int("output1", output1, 6)) {
    return false;
  }

  char testcase2 = 's';
  unsigned int output2 = get_next_row(5, testcase2);
  if (!assert_equals_unsigned_int("output2", output2, 6)) {
    return false;
  }

  char testcase3 = 'S';
  unsigned int output3 = get_next_row(5, testcase3);
  if (!assert_equals_unsigned_int("output3", output3, 6)) {
    return false;
  } 

  char testcase4 = '^';
  unsigned int output4 = get_next_row(5, testcase4);
  if (!assert_equals_unsigned_int("output4", output4, 4)) {
    return false;
  } 

  char testcase5 = 'w';
  unsigned int output5 = get_next_row(5, testcase5);
  if (!assert_equals_unsigned_int("output5", output5, 4)) {
    return false;
  }

  char testcase6 = 'W';
  unsigned int output6 = get_next_row(5, testcase6);
  if (!assert_equals_unsigned_int("output6", output6, 4)) {
    return false;
  }

  char testcase7 = '>';
  unsigned int output7 = get_next_row(5, testcase7);
  if (!assert_equals_unsigned_int("output7", output7, 5)) {
    return false;
  }

  return true;
}

bool test_get_next_col() {
  char testcase1 = '>';
  unsigned int output1 = get_next_col(5, testcase1);
  if (!assert_equals_unsigned_int("output1", output1, 6)) {
    return false;
  }

  char testcase2 = 'd';
  unsigned int output2 = get_next_col(5, testcase2);
  if (!assert_equals_unsigned_int("output2", output2, 6)) {
    return false;
  }

  char testcase3 = 'D';
  unsigned int output3 = get_next_col(5, testcase3);
  if (!assert_equals_unsigned_int("output3", output3, 6)) {
    return false;
  }

  char testcase4 = '<';
  unsigned int output4 = get_next_col(5, testcase4);
  if (!assert_equals_unsigned_int("output4", output4, 4)) {
    return false;
  }

  char testcase5 = 'a';
  unsigned int output5 = get_next_col(5, testcase5);
  if (!assert_equals_unsigned_int("output5", output5, 4)) {
    return false;
  }

  char testcase6 = 'A';
  unsigned int output6 = get_next_col(5, testcase6);
  if (!assert_equals_unsigned_int("output6", output6, 4)) {
    return false;
  }

  char testcase7 = '^';
  unsigned int output7 = get_next_col(5, testcase7);
  if (!assert_equals_unsigned_int("output7", output7, 5)) { 
    return false;
  }

  return true;
}

bool test_customs() {
  if (!test_greater_than_forty_two()) {
    printf("%s\n", "test_greater_than_forty_two failed.");
    return false;
  }
  if (!test_is_vowel()) {
    printf("%s\n", "test_is_vowel failed.");
    return false;
  }
  if (!test_is_tail()) {
    printf("%s\n", "test_is_tail failed");
    return false;
  }
  if (!test_is_head()) {
    printf("%s\n", "test_is_head failed");
    return false;
  }
  if (!test_is_snake()) {
    printf("%s\n", "test_is_snake failed");
    return false;
  }
  if (!test_body_to_tail()) {
    printf("%s\n", "test_body_to_tail failed");
    return false;
  }
  if (!test_head_to_body()) {
    printf("%s\n", "test_head_to_body failed");
    return false;
  }
  if (!test_get_next_row()) {
    printf("%s\n", "test_get_next_row failed");
    return false;
  }
  if (!test_get_next_col()) {
    printf("%s\n", "test_get_next_col failed");
    return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  init_colors();

  if (!test_and_print("custom", test_customs)) {
    return 0;
  }

  return 0;
}
