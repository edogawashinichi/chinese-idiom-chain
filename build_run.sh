#!/bin/bash

if [ -f "chain.o" ]; then
  echo "romove last chain.o"
  rm chain.o
fi

if [ -f "1.log" ]; then
  echo "remove last 1.log"
  rm 1.log
fi

cachefile="cache.txt"
cachesz=0
if [ -f ${cachefile} ]; then
  cachesz=`stat -c "%s" $cachefile`
  echo "${cachefile} size ${cachesz}"
fi
cpfile="cp-cache.txt"
cpsz=0
if [ -f ${cpfile} ]; then
  cpsz=`stat -c "%s" $cpfile`
  echo "${cpfile} size ${cpsz}"
fi
if [ $cachesz -gt $cpsz ]; then
  cp $cachefile $cpfile
  echo "recover ${cpfile}"
elif [ $cachesz -lt $cpsz ]; then
  cp $cpfile $cachefile
  echo "recover ${cachefile}"
fi

g++ chain.cpp -o chain.o -ljsoncpp -lpthread
#./chain.o &> 1.log #docker centos7 redirection bug
./chain.o
