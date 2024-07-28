/// test_encoder.cpp

#include "common_header.h"

void test_1() {
  const string file(DATA_FILE);
  Reader reader;
  Data data;
  reader.readData(file, &data);
  Encoder encoder;
  Mapper mapper;
  if (false == encoder.encodeData(data, &mapper)) {
    cout << "test_1 FAILED!\n";
    return;
  }

  cout << "idiom2code size: " << mapper.idiom2code_.size() << "\n";
  cout << "code2idiom size: " << mapper.code2idiom_.size() << "\n";
  if (mapper.idiom2code_.size() != mapper.code2idiom_.size()) {
    cout << "SIZE NOT EQUAL!\n";
    cout << "test_1 FAILED!\n";
    return;
  }

  for (const auto& kv : mapper.idiom2code_) {
    const string& idiom = kv.first;
    const int code = kv.second;
    if (mapper.code2idiom_[code] != idiom) {
      cout << idiom << " -> " << code << " -> " << mapper.code2idiom_[code] << "\n";
      cout << "test_1 FAILED!\n";
      return;
    }/// if
  }/// for

  cout << "test_1 PASSED!\n";
}/// test_1

int main(int argc, char* argv[]) {
  test_1();
  return 0;
}
