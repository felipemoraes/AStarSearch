#include <iostream>
#include <fstream>
#include <vector>
#include "astarsearch.h"
#include <sstream>

using namespace std;

int main(int argc, char** argv){
    int n, blank_pos,i=0;
    string infile;
    if (argc < 2) {
        cout << "Usage: ./n_puzzle --infile [input_file]" << endl; 
        return 1;
    }
    for(int i=0; i<argc; i++){
        string param(argv[i]);
        if(param == "--infile" || param == "-i"){
           i++;
           infile = string(argv[i]);
        }
    }
    ifstream in(infile.c_str());

    vector<int> start_state,goal_state;
    if (in.is_open()){
        string line;
        getline(in,line);
        n = stoi(line);
        while (getline(in,line)){
            stringstream ssin(line);
            while (ssin.good()){
                string tile;
                ssin >> tile; 
                if (tile == "_"){
                    start_state.push_back(0);
                    blank_pos = i;
                } else {
                    start_state.push_back(stoi(tile));
                }
                i++;
            }   
        }
    } else {
         std::cout << "File not found" << std::endl;
    }

    for (int i = 0; i < n*n;++i){
        goal_state.push_back(i);
    }
    NodeState start,goal;
    start.state_ = start_state;
    start.blank_pos_ = blank_pos;
    start.label_ = "start";
    goal.state_ = goal_state;
    goal.blank_pos_ = 0;
    AStarSearch astarsearch(start,goal,n);
    SearchState sstate = astarsearch.search_step();
    while (sstate == SearchState::SEARCH_STATE_SEARCHING){
        sstate = astarsearch.search_step();
    }
    astarsearch.print_solution();
    return 0;
}
