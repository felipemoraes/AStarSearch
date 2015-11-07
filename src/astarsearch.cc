#include "astarsearch.h"

AStarSearch::AStarSearch(NodeState start, NodeState goal, int n){
    this->start_ = start;
    this->goal_ = goal;
    open_pq_ = new priority_queue<NodeState,vector<NodeState>,HeapComparator >();
    open_ = new unordered_set<NodeState, hash_comp>();
    close_ = new unordered_set<NodeState, hash_comp>();
    this->open_->insert(start_);
    this->open_pq_->push(start_);
    this->depth_ = 1;
    this->n_ = n;
}

AStarSearch::~AStarSearch(){
    delete open_;
    delete open_pq_;
    delete close_;
}

float AStarSearch::goal_distance_estimate(const vector<int> &state){
   return manhattan_distance(state);
}

float AStarSearch::manhattan_distance(const vector<int> &state){
    float distance = 0.0f;
    for(int i = 0; i < state.size(); ++i){
       int x1 = state[i]/n_;
       int y1 = state[i] - x1*n_;
       int xs = i/n_;
       int ys = i - xs*n_;
       distance += abs(xs-x1) + abs(ys-y1);
    }
    return distance;
}

float AStarSearch::double_manhattan_distance(const vector<int> &state){
    float distance = 0.0f;
    for(int i = 0; i < state.size(); ++i){
        int x1 = state[i]/n_;
        int y1 = state[i] - x1*n_;
        int xs = i/n_;
        int ys = i - xs*n_;
        distance += abs(xs-x1) + abs(ys-y1);
    }
    return distance;
}


float AStarSearch::hamming_distance(const vector<int> &state){
    float distance = 0.0f;
    for(int i = 0; i < state.size(); ++i){
       if (state[i] != i){
           distance++;
        }
    }
    return distance;
}



bool AStarSearch::is_goal(const NodeState &node){
    return (goal_ == node);
}


void AStarSearch::get_sucessors(shared_ptr<NodeState> current_node){
    int k = current_node->blank_pos_;
    // Right
    if (((k+1)%n_) &&  k+1 < this->n_*this->n_ && k+1 >= 0){
        vector<int> vec(current_node->state_);
        swap(vec[k+1],vec[k]);
        float distance = goal_distance_estimate(vec);
        NodeState node(vec, current_node->g_ + 1, distance, k+1,1);
        add_sucessor(node,current_node);
    }
    // Left
    if ((k%n_) && (k-1 < this->n_*this->n_) && (k-1 >= 0)){
        vector<int> vec(current_node->state_);
        swap(vec[k-1],vec[k]);
        float distance = goal_distance_estimate(vec);
        NodeState node(vec, current_node->g_ + 1, distance, k-1,2);
        add_sucessor(node,current_node);
    }
    // Down
    if (k+this->n_ < this->n_*this->n_ && k+this->n_ >= 0){
        vector<int> vec(current_node->state_);
        swap(vec[k+n_],vec[k]);
        float distance = goal_distance_estimate(vec);
        NodeState node(vec, current_node->g_ + 1, distance, k+n_,3);
        add_sucessor(node,current_node);
    }
    // Up
    if (k-this->n_ < this->n_*this->n_ && k-this->n_ >= 0){
        vector<int> vec(current_node->state_);
        swap(vec[k-this->n_],vec[k]);
        float distance = goal_distance_estimate(vec);
        NodeState node(vec, current_node->g_ + 1, distance, k-this->n_,4);
        add_sucessor(node,current_node);
    } 
}

void AStarSearch::add_sucessor(NodeState &node, shared_ptr<NodeState> current_node){
    auto it = this->open_->find(node);
    if (it != this->open_->end()){
        if (it->f_ > node.f_){
            //delete node.parent_;
            this->open_->erase(*it);
        }
    }
    it = close_->find(node);
    if (it != close_->end()) {
        if (it->f_ > node.f_) {
            close_->erase(*it);
        }
    }
    node.parent_ = current_node;
    open_->insert(node);
    open_pq_->push(node);
}

string get_label(const int n){
    switch (n) {
        case 1:
            return "direita";
        case 2:
            return "esquerda";
        case 3:
            return "abaixo";
        case 4:
            return "acima";
        default:
            return "";
    }
}



void AStarSearch::print_solution(NodeState &current_node){
    ofstream foutput("output.txt");
    vector<int> solution;
    solution.push_back(current_node.label_);
    auto node = current_node.parent_;
    while (node->label_ != 0){
        solution.push_back(node->label_);
        node = node->parent_;
    }
    reverse(solution.begin(),solution.end());
    foutput << solution.size() << endl;
    for (auto s: solution) {
        foutput << get_label(s) << endl;
    }
    foutput.close();
    cout << close_->size()  << endl;
}


SearchState AStarSearch::search_step(){
    if (!this->open_pq_->empty()){
        shared_ptr<NodeState> current_node;
        while (!this->open_pq_->empty()){
            NodeState node = open_pq_->top();
            this->open_pq_->pop();
            auto it = close_->find(node);
            if (it == close_->end()){
                current_node = make_shared<NodeState>(node);
                break;
            }
        }
        this->open_->erase(*current_node);
        close_->insert(*current_node);
        if (is_goal(*current_node)) {
            print_solution(*current_node);
            return SearchState::SEARCH_STATE_SUCCEEDED;
        } else {
            get_sucessors(current_node);
        }
    }
    return SearchState::SEARCH_STATE_SEARCHING;
}
