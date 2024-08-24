/// common_notation.h

#pragma once

///*
#ifndef CIC__DEBUG_INFO
#define CIC__DEBUG_INFO
#endif
//*/

/*
#ifdef CIC__DEBUG_INFO
#undef CIC__DEBUG_INFO
#endif
*/

#include <vector>
#include <list>
#include <set>
#include <unordered_map>
#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <jsoncpp/json/json.h>
using std::string;
using std::to_string;
using std::vector;
using std::list;
using std::set;
using std::unordered_map;
using std::pair;
using std::unique_ptr;
using std::make_unique;
using VS = vector<string>;
using VI = vector<int>;
using LI = list<int>;
using SI = set<int>;
using VLI = vector<LI>;
using TLI = LI*;
using VULI = vector<unique_ptr<LI>>;
using MSI = unordered_map<string, int>;
using MIS = unordered_map<int, string>;
using PII = pair<int, int>;
using PIS = pair<int, string>;
using PIVI = pair<int, VI>;
using MIVI = unordered_map<int, VI>;
using std::cout;
using std::cin;
using std::ofstream;
using std::ifstream;
using std::ios;

#define MAIN_START \
int main(int argc, char* argv[]) {
//ios::sync_with_stdio(false);/*cause segmentation fault*/

#define MAIN_END \
  return 0;\
}

#define STR(s) #s

#define STR_L(s) \
cout << s << "\n";

#define STR_VAR_L(s) \
cout << STR(s) << ": " << s << "\n";

#define STR_VAR_2_L(s, t) \
cout << STR(s) << ":" << s << "  " << STR(t) << ":" << t << "\n";

#define TEST_SEPAR(i) \
cout << "\033[34m---------\033[0m" << STR(test_##i) << "\033[34m---------\033[0m\n";

#define FAIL_INFO_RET(i) \
cout << STR(test_##i) << " \033[31mFAILED\033[0m!\n";\
return;

#define PASS_INFO(i) \
cout << STR(test_##i) << " \033[32mPASSED\033[0m!\n";

#define CIC__READ_JSON_START(file, ptr, in, root) \
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

#define CIC__WRITE_JSON_START(file, out, root) \
ofstream out(file);\
if (!out.is_open()) {\
  return false;\
}\
Json::Value root;

#define CIC__WRITE_JSON_END(out, root) \
Json::StyledWriter sw;\
out << sw.write(root);\
out.close();\
return true;

#define CIC__READ_BIN_START(file, in) \
ifstream in(file, ios::binary);\
if (!in.is_open()) {\
  return false;\
}

#define CIC__READ_BIN_END(in) \
in.close();\
return true;

#define CIC__WRITE_BIN_START(file, out) \
ofstream out(file, ios::binary);\
if (!out.is_open()) {\
  return false;\
}

#define CIC__WRITE_BIN_END(out) \
out.close();\
return true;
