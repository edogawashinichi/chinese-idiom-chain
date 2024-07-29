#!/bin/bash

echo "start building..."

obj_path="../obj/"
if [ ! -d ${obj_path} ]; then
  echo "mkdir ${obj_path}"
  mkdir ${obj_path}
fi

test_path="../src/"
test_file=${test_path}"test_builder.cpp"
if [ $# -ge 1 ]; then
  test_file=$1
fi
obj_suf=".o"
obj_file=${obj_path}${test_file:7:-4}${obj_suf}

echo "test file: ${test_file}"
echo "obj file: ${obj_file}"

if [ -f ${obj_file} ]; then
  echo "remove ${obj_file}"
  rm ${obj_file}
fi

# gtest requires at least C++14
g++ -ljsoncpp -std=c++17 -o ${obj_file} -cpp ${test_file} ${test_path}reader.cpp ${test_path}encoder.cpp ${test_path}builder.cpp ${test_path}filter.cpp ${test_path}common_math.cpp
./${obj_file}

echo "end running..."
