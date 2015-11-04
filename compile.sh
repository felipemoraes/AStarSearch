mkdir -p bin
g++ -Wall -pg -std=c++11 -O3 -o bin/n_puzzle src/n_puzzle.cc src/astarsearch.cc
