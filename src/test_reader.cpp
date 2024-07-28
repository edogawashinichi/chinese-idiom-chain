/// test_reader.cpp

#include "common_header.h"

void test_1() {
  const int EXP = 30895;
  const string file(DATA_FILE);
  Reader reader;
  Data data;

  if (false == reader.readData(file, &data)) {
    cout << "test_1 FAILED!\n";
    return;
  }

  cout << "data size: " << data.data_.size() << "\n";
  if (EXP != data.data_.size()) {
    cout << "EXP: " << EXP << "\n";
    cout << "test_1 FAILED!\n";
    return;
  }

  cout << "test_1 PASSED!\n";
}/// test_1

int main(int argc, char* argv[]) {
  test_1();
  return 0;
}
