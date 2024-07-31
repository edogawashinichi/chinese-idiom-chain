/// test_encoder.cpp

#include "common_test_header.h"

void test_1() {
  TEST_SEPAR(1)
  const string file(DATA_FILE);
  Reader reader;
  Data data;
  reader.readData(file, &data);
  Encoder encoder;
  Mapper mapper;
  if (false == encoder.encodeData(data, &mapper)) {
    FAIL_INFO_RET(1)
  }

  cout << "idiom2code size: " << mapper.idiom2code_.size() << "\n";
  cout << "code2idiom size: " << mapper.code2idiom_.size() << "\n";
  if (mapper.idiom2code_.size() != mapper.code2idiom_.size()) {
    FAIL_INFO_RET(1)
  }

  for (const auto& kv : mapper.idiom2code_) {
    const string& idiom = kv.first;
    const int code = kv.second;
    if (mapper.code2idiom_[code] != idiom) {
      cout << idiom << " -> " << code << " -> " << mapper.code2idiom_[code] << "\n";
      FAIL_INFO_RET(1)
    }/// if
  }/// for

  PASS_INFO(1)
  TEST_SEPAR(2)
}/// test_1

MAIN_START
test_1();
MAIN_END
