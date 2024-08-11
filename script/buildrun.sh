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

src_path="../src/"
# gtest requires at least C++14
# O2 optmization may modify primary output, turn off for debug purpose
g++ -ljsoncpp -std=c++17 -o ${obj_file} -cpp ${test_file} ${src_path}reader.cpp ${src_path}encoder.cpp ${src_path}builder.cpp ${src_path}filter.cpp ${src_path}common_math.cpp ${src_path}writer.cpp ${src_path}solver.cpp ${src_path}mapper.cpp ${src_path}graph.cpp ${src_path}solver_naive.cpp ${src_path}path.cpp ${src_path}solver_gene.cpp ${src_path}pool.cpp ${src_path}pool_forward.cpp ${src_path}pool_backward.cpp ${src_path}population.cpp
./${obj_file}

echo "end running..."
