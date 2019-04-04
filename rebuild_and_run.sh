#!/bin/bash

rm -rf build
mkdir build
cd build
cmake -DGLM_TEST_ENABLE=OFF ..
make -j8
./opengl
