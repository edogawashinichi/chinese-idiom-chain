/// test_common_math.cpp

#include "common_test_header.h"

void test_1() {
  TEST_SEPAR(1)
  const VI EXP = {-1, 1, 3, 5, 7};
  const VI vec(linearVec(5, 2, -1));
  if (!isEqual(EXP, vec)) {
    FAIL_INFO_RET(1)
  }
  PASS_INFO(1)
  TEST_SEPAR(1)
}/// test_1

void test_2() {
  TEST_SEPAR(2)
  const VI EXP = {-1, 0, 1, 2};
  const VI vec(idVec(4, -1));
  if (!isEqual(EXP, vec)) {
    FAIL_INFO_RET(2)
  }
  PASS_INFO(2)
  TEST_SEPAR(2)
}/// test_2

void test_3() {
  TEST_SEPAR(3)
  const VI EXP = {0, 1, 2, 3};
  const VI vec(idVec(4));
  if (!isEqual(EXP, vec)) {
    FAIL_INFO_RET(3)
  }
  PASS_INFO(3)
  TEST_SEPAR(3)
}/// test_3

void test_4() {
  TEST_SEPAR(4)
  const VI vec(linearVec(9, 3, 1));
  const int index = randomChoose(vec);
  if (index < 0 || index >= vec.size()) {
    FAIL_INFO_RET(4)
  }
  PASS_INFO(4)
  TEST_SEPAR(4)
}/// test_4

void test_5() {
  TEST_SEPAR(5)
  const int n = 6;
  const VI vec(linearVec(n, -1, 5));
  const VI freq(idVec(n, 1));
  const int i = randomChoose(vec, freq);
  if (i < 0 || i >= n) {
    FAIL_INFO_RET(5)
  }
  const int j = randomChoose(vec, freq, 2, 3);
  if (j < 2 || j > 2) {
    FAIL_INFO_RET(5)
  }
  PASS_INFO(5)
  TEST_SEPAR(5)
}/// test_5

void test_6() {
  TEST_SEPAR(6)  
  const short a = static_cast<short>(0b1110101010101011);
  char b, c;
  split16bits(a, b, c);
  if (static_cast<char>(0b11101010) != b) {
    STR_VAR_L(static_cast<char>(0b11101010));
    STR_VAR_L(b);
    FAIL_INFO_RET(6)
  }
  if (static_cast<char>(0b10101011) != c) {
    STR_VAR_L(static_cast<char>(0b10101011));
    STR_VAR_L(c);
    FAIL_INFO_RET(6)
  }
  PASS_INFO(6)
  TEST_SEPAR(6)
}/// test_6

void test_7() {
  TEST_SEPAR(7)
  const char b = static_cast<char>(0b10100101);
  const char c = static_cast<char>(0b00111100);
  const short a = composite16bits(b, c);
  if (a != static_cast<short>(0b1010010100111100)) {
    STR_VAR_L(a);
    STR_VAR_L(static_cast<short>(0b1010010100111100));
    FAIL_INFO_RET(7)
  }
  PASS_INFO(7)
  TEST_SEPAR(7)
}/// test_7

MAIN_START
test_1();
test_2();
test_3();
test_4();
test_5();
test_6();
test_7();
MAIN_END
