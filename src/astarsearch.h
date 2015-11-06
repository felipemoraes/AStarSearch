#ifndef __astarsearch__
#define __astarsearch__

#include <queue>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "nodestate.h"



using namespace std;

enum class SearchState{
    SEARCH_STATE_SEARCHING,
    SEARCH_STATE_SUCCEEDED,
    SEARCH_STATE_FAILED
};

class AStarSearch {
private:
    NodeState start_;
    NodeState goal_;
    priority_queue<NodeState,vector<NodeState>,HeapComparator >* open_pq_;
    unordered_set<NodeState, hash_comp>* open_;
    unordered_set<NodeState, hash_comp>* close_;
    unordered_map<NodeState, NodeState, hash_comp>* came_from_;
    int depth_;
    int n_;
    float goal_distance_estimate(const vector<int> &state);
    bool is_goal(const NodeState &node);
    void get_sucessors(NodeState &current_node);
    void add_sucessor(NodeState &node, NodeState &current_node);
    float manhattan_distance(const vector<int> &state);
    float hamming_distance(const vector<int> &state);
    float double_manhattan_distance(const vector<int> &state);
public:
    AStarSearch(NodeState start, NodeState goal, int n);
    ~AStarSearch();
    SearchState search_step();
    void print_solution(NodeState &current_node);
};


#endif /* defined(__astarsearch__) */
