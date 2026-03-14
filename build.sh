#!/bin/bash

clang++ -o build/GassinRT main.cpp -I ./src -std=c++20 -luv -lv8
