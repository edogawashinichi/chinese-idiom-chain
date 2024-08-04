/// common_notation.h

#pragma once

/*
#ifndef CIC__DEBUG_INFO
#define CIC__DEBUG_INFO
#endif
*/

#ifdef CIC__DEBUG_INFO
#undef CIC__DEBUG_INFO
#endif

#define MAIN_START \
int main(int argc, char* argv[]) {
#define MAIN_END \
return 0;\
}

#define STR(s) #s
#define STR_VAR_L(s) \
cout << STR(s) << ": " << s << "\n";
#define STR_VAR_LL(s, t) \
cout << STR(s) << ":" << s << "  " << STR(t) << ":" << t << "\n";
#define TEST_SEPAR(i) \
cout << "\033[34m---------\033[0m" << STR(test_##i) << "\033[34m---------\033[0m\n";
#define FAIL_INFO_RET(i) \
cout << STR(test_##i) << " \033[31mFAILED\033[0m!\n";\
return;
#define PASS_INFO(i) \
cout << STR(test_##i) << " \033[32mPASSED\033[0m!\n";

#define CIC__READ_JSON_START(ptr, in, root) \
if (nullptr == ptr) {\
  return false;\
}\
ifstream in(file, ios::binary);\
if (!in.is_open()) {\
  return false;\
}\
Json::Reader reader;\
Json::Value root;\
if (!reader.parse(in, root)) {\
  return false;\
}
#define CIC__READ_JSON_END(in) \
in.close();\
return true;

#define CIC__WRITE_JSON_START \
ofstream out(file);\
if (!out.is_open()) {\
  return false;\
}\
Json::Value root;
#define CIC__WRITE_JSON_END \
Json::StyledWriter sw;\
out << sw.write(root);\
out.close();\
return true;

#include <vector>
#include <list>
#include <unordered_map>
#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <jsoncpp/json/json.h>

using std::string;
using std::vector;
using std::list;
using std::unordered_map;
using std::pair;
using VS = vector<string>;
using VI = vector<int>;
using LI = list<int>;
using MSI = unordered_map<string, int>;
using MIS = unordered_map<int, string>;
using PIS = pair<int, string>;
using MIVI = unordered_map<int, VI>;
using std::cout;
using std::unique_ptr;
using std::make_unique;
using std::ofstream;
using std::ifstream;
using std::ios;
