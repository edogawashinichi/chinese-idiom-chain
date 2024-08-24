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

# keep larger one between forward.bin and cp-forward.bin
# keep larger one between backward.bin and cp-backward.bin
function getFileSize() {
  file_name=$1
  file_size=0
  if [ -f ${file_name} ]; then
    file_size=`stat -c "%s" ${file_name}`
    # echo "getFileSize: ${file_name} size ${file_size}"
  fi
  echo ${file_size}
  # return ${file_size}
  # $? return value mod 256
}
function keepLargerFile() {
  file=$1
  file_size=$(getFileSize $1)
  cp_file=$2
  cp_file_size=$(getFileSize $2)
  ratio=0.95
  cp_file_size_discount=$(echo "scale=2;${ratio}*${cp_file_size}"|bc)
  echo "keepLargerFile: ${file} size ${file_size}"
  echo "keepLargerFile: ${cp_file} size ${cp_file_size_discount}"
  if [ `echo "${cp_file_size_discount} < ${file_size}" | bc` -eq 1 ]; then
    cp ${file} ${cp_file}
    echo "keep ${file}"
  elif [ `echo "${cp_file_size_discount} > ${file_size}" | bc` -eq 1 ]; then
    cp ${cp_file} ${file}
    echo "keep ${cp_file}"
  fi
}

src_path="../src/"
# gtest requires at least C++14
# O2 optmization may modify primary output, turn off for debug purpose
g++ -ljsoncpp -std=c++17 -o ${obj_file} -cpp ${test_file} ${src_path}reader.cpp ${src_path}encoder.cpp ${src_path}builder.cpp ${src_path}filter.cpp ${src_path}common_math.cpp ${src_path}writer.cpp ${src_path}solver.cpp ${src_path}mapper.cpp ${src_path}graph.cpp ${src_path}solver_naive.cpp ${src_path}path.cpp ${src_path}solver_gene.cpp ${src_path}pool.cpp ${src_path}pool_forward.cpp ${src_path}pool_backward.cpp ${src_path}population.cpp


forward_bin_file="../data/cache/snippets/forward.bin"
backward_bin_file="../data/cache/snippets/backward.bin"
cp_forward_bin_file="../data/cache/snippets/cp-forward.bin"
cp_backward_bin_file="../data/cache/snippets/cp-backward.bin"
N=20
for ((i=1;i<=N;i++))
do
  echo "${obj_file} loop $i"

  keepLargerFile ${forward_bin_file} ${cp_forward_bin_file}
  seconds=10
  echo "sleep ${seconds}s..."
  sleep ${seconds}s
  
  keepLargerFile ${backward_bin_file} ${cp_backward_bin_file}
  seconds=10
  echo "sleep ${seconds}s..."
  sleep ${seconds}s

  ./${obj_file}
  seconds=10
  echo "sleep ${seconds}s..."
  sleep ${seconds}s
done

echo "end running..."
