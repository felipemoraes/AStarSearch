#ifndef __astarsearch__
#define __astarsearch__

#include <queue>
#include <vector>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <cmath>
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
    NodeState current_node_;
    priority_queue<NodeState,vector<NodeState>,HeapComparator > open_pq_;
    unordered_set<NodeState, hash_comp> open_;
    unordered_set<NodeState, hash_comp> close_;
    int depth_;
    int n_;
    float goal_distance_estimate(vector<int> state);
    bool is_goal(NodeState node);
    void get_sucessors();
    void add_sucessor(NodeState node);
    float manhattan_distance(vector<int> state);
    float hamming_distance(vector<int> state);

public:
    AStarSearch(NodeState start, NodeState goal, int n);
    void set_start(NodeState start);
    void set_goal(NodeState goal);
    SearchState search_step();
    void print_solution();
};


#endif /* defined(__astarsearch__) */
