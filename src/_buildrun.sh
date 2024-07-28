#!/bin/bash

echo "start building..."

test_file="test.cpp"
if [ $# -ge 1 ]; then
  test_file=$1
fi
#src_file=${test_file:5}
obj_suf=".o"
obj_file=${test_file:0:-4}${obj_suf}

echo "test file: ${test_file}"
#echo "src file: ${src_file}"
echo "obj file: ${obj_file}"

if [ -f ${obj_file} ]; then
  echo "remove ${obj_file}"
  rm ${obj_file}
fi

# gtest requires at least C++14
#g++ -cpp ${test_file} ${src_file} -std=c++17 -o ${obj_file} -ljsoncpp
g++ -ljsoncpp -std=c++17 -o ${obj_file} -cpp ${test_file} reader.cpp encoder.cpp builder.cpp filter.cpp common_math.cpp
./${obj_file}

echo "end running..."
