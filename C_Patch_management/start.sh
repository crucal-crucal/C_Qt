#!/bin/bash

cd bin/
mkdir build && cd build
cmake ../.. && make -j${nproc}
./application
