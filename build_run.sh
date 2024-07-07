#!/bin/bash

if [ -f "chain.o" ]; then
  echo "romove last chain.o"
  rm chain.o
fi

if [ -f "1.log" ]; then
  echo "remove last 1.log"
  rm 1.log
fi

g++ chain.cpp -o chain.o -ljsoncpp -lpthread
#./chain.o &> 1.log #docker centos7 redirection bug
./chain.o
