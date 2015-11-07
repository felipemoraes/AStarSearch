#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <sys/time.h>
#include <sys/resource.h>

#include "astarsearch.h"
#include "util.h"

using namespace std;

int main(int argc, char** argv){
    int n = 1;
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
    NodeState start = get_start_state(infile,n);
    if (!is_solvable(start,n)) {
        write_no_solution();
        return 0;
    } 
    NodeState goal = get_goal_state(n);
    
    float execution_time = 0;
    struct timeval t_start;
    struct timeval t_end;
    gettimeofday(&t_start, NULL);
    AStarSearch* astarsearch = new AStarSearch(start,goal,n);
    SearchState sstate = astarsearch->search_step();
    while (sstate == SearchState::SEARCH_STATE_SEARCHING){
        sstate = astarsearch->search_step();
    }
    gettimeofday(&t_end, NULL);
    execution_time = (t_end.tv_sec-t_start.tv_sec)*1000000;
    execution_time = (execution_time+(t_end.tv_usec-t_start.tv_usec))/1000000;
    delete astarsearch;
    printf("%.5f\n", execution_time);
    return 0;
}
