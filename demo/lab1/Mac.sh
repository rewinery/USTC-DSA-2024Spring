#!/bin/zsh
# This shell script is used for Mac OS Users

g++ yourcode.cpp -o yourcode

for i in {1..5}
do
    python3 -u generate_test_case.py
    ./ans_mac > ./output/ans.txt
    ./yourcode > ./output/your_output.txt
    python3 -u judge.py
done