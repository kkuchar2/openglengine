#!/bin/bash

rm -rf build
mkdir build
cd build
cmake -DGLM_TEST_ENABLE=OFF -DNANOGUI_USE_GLAD=ON ..
make -j8
cd ..
