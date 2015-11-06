#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdlib.h>  // for size_t.
#include <stdint.h>
#include <utility>

#ifndef __nodestate__
#define __nodestate__

using namespace std;

struct vec_comp {
    std::size_t operator()(const vector<int> &vec) const {
        std::size_t seed = 0;
        for(auto& i : vec) {
            seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};


class NodeState {
public:
    float g_;
    float h_;
    float f_;
    vector<int> state_;
    int blank_pos_;
    int label_;
    NodeState(): g_(0.0f),h_(0.0f),f_(0.0f),label_(0){}
    NodeState(vector<int> state, float g, float h, int blank_pos, int label){
        state_ = state;
        g_ = g;
        h_ = h;
        f_ = g + h;
        blank_pos_ = blank_pos;
        label_ = label;
    }
};

struct hash_comp {
    std::size_t operator()(const NodeState &node) const {
        std::size_t seed = 0;
        for(auto& i : node.state_) {
            seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};


class HeapComparator{
public:
    bool operator () (const NodeState &x, const NodeState &y ) const {
        if (x.f_ > y.f_) {
            return true;
        }
        return false;

    }
};




inline bool operator == (NodeState const& lhs, NodeState const& rhs){
    return (lhs.state_ == rhs.state_);
}


class MapComparator{
public:
    bool operator() (const NodeState *x, const NodeState *y ) const {
        return x->state_ == y->state_;
    }
};



#endif /* defined(__nodestate__) */


