/// test_filter.cpp

#include "common_header.h"

void test_1() {
  const int EXP = 29502;
  const string file(DATA_FILE);
  Reader reader;
  Data data;
  reader.readData(file, &data);
  Encoder encoder;
  Mapper mapper;
  encoder.encodeData(data, &mapper);
  Filter filter;
  const int mode = 1;/// mode 1: length four
  const auto idiom2code = filter.idiom2Code(mapper, mode);
  const auto code2idiom = filter.code2Idiom(mapper, mode);
  cout << "idiom2code size: " << idiom2code.size() << "\n";
  cout << "code2idiom size: " << code2idiom.size() << "\n";
  if (EXP != idiom2code.size() || EXP != code2idiom.size()) {
    cout << "EXP: " << EXP << "\n";
    cout << "test_1 FAILED!\n";
  } else {
    cout << "test_1 PASSED!\n";
  }
}/// test_1

int main(int argc, char* argv[]) {
  test_1();
  return 0;
}
