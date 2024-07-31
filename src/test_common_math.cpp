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
  const int index = randomChoose(vec, freq);
  if (index < 0 || index >= n) {
    FAIL_INFO_RET(5)
  }
  PASS_INFO(5)
  TEST_SEPAR(5)
}/// test_5

MAIN_START
test_1();
test_2();
test_3();
test_4();
test_5();
MAIN_END
