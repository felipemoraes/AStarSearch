#include "astarsearch.h"

AStarSearch::AStarSearch(NodeState start, NodeState goal, int n){
    this->start_ = start;
    this->goal_ = goal;
    this->open_.insert(this->start_);
    this->open_pq_.push(this->start_);
    this->depth_ = 1;
    this->n_ = n;
}

float AStarSearch::goal_distance_estimate(vector<int> state){
   return manhattan_distance(state);
}

float AStarSearch::manhattan_distance(vector<int> state){
    float distance = 0.0f;
    for(int i = 0; i < state.size(); ++i){
       int x1 = state[i]/n_;
       int y1 = x1 - x1*n_;
       int xs = i/n_;
       int ys = xs - xs*n_;
       distance += abs(xs-x1) + abs(ys-y1);
    }
    return distance;
}

float AStarSearch::hamming_distance(vector<int> state){
    float distance = 0.0f;
    for(int i = 0; i < state.size(); ++i){
       if (state[i] != i){
           distance++;
        }
    }
    return distance;
}



bool AStarSearch::is_goal(NodeState node){
    return (goal_ == node);
}


void AStarSearch::get_sucessors(){
    int k = this->current_node_.blank_pos_;
    if (k+1 < this->n_*this->n_ && k+1 >= 0){
        vector<int> vec(this->current_node_.state_);
        swap(vec[k+1],vec[k]);
        float distance = goal_distance_estimate(vec);
        NodeState node(vec, this->current_node_.g_ + 1, distance, k+1,"direita");
        add_sucessor(node);
    }
    if (k-1 < this->n_*this->n_ && k-1 >= 0){
        vector<int> vec(this->current_node_.state_);
        swap(vec[k-1],vec[k]);
        float distance = goal_distance_estimate(vec);
        NodeState node(vec, this->current_node_.g_ + 1, distance, k-1,"esquerda");
        add_sucessor(node);
    }
    if (k+this->n_ < this->n_*this->n_ && k+this->n_ >= 0){
        vector<int> vec(this->current_node_.state_);
        swap(vec[k+n_],vec[k]);
        float distance = goal_distance_estimate(vec);
        NodeState node(vec, this->current_node_.g_ + 1, distance, k+n_,"abaixo");
        add_sucessor(node);
    }
    if (k-this->n_ < this->n_*this->n_ && k-this->n_ >= 0){
        vector<int> vec(this->current_node_.state_);
        swap(vec[k-this->n_],vec[k]);
        float distance = goal_distance_estimate(vec);
        NodeState node(vec, this->current_node_.g_ + 1, distance, k-this->n_,"acima");
        add_sucessor(node);
    } 
    close_.insert(current_node_);
}

void AStarSearch::add_sucessor(NodeState node){
    node.parent_ = new NodeState(current_node_);
    auto it = this->open_.find(node);
    if (it == this->open_.end()){
        auto got = this->close_.find(node);
        if (got == this->close_.end()){
            
            this->open_.insert(node);
            this->open_pq_.push(node);
        }
    } else {
        if (it->f_ > node.f_) {
            this->open_.erase(node);
            this->open_.insert(node);
            this->open_pq_.push(node);
        }
    }
}

void AStarSearch::print_solution(){
    cout << current_node_.label_  << " ";
    for (auto v: current_node_.state_){
        cout << v << " ";
    }
    cout << endl;
    NodeState *node = current_node_.parent_;
    while (node->label_ != "start"){
        cout << node->label_ << " ";
        for (auto v : node->state_){
            cout << v << " ";
        }
        cout << endl;
        node = node->parent_;
    }
    cout << node->label_ << " ";
    for (auto v: node->state_){
        cout << v << " ";
    }
    cout << endl;
}

void AStarSearch::set_start(NodeState start){
    this->start_ = start;
}

void AStarSearch::set_goal(NodeState goal){
    this->goal_ = goal;
}


SearchState AStarSearch::search_step(){
    if (!this->open_pq_.empty()){
        while (!this->open_pq_.empty()){
            current_node_ = this->open_pq_.top();
            this->open_pq_.pop();
            auto it = this->close_.find(current_node_);
            if (it != this->close_.end()){
                if (this->open_pq_.empty() && !is_goal(current_node_)){
                    return SearchState::SEARCH_STATE_FAILED;
                }  
            } else {
                break;
            }
        }
        this->open_.erase(current_node_);
        if (is_goal(current_node_)) {
            return SearchState::SEARCH_STATE_SUCCEEDED;
        } else {
            get_sucessors();
        }
        cout << "Close list length: " << close_.size() << endl;
    }
    return SearchState::SEARCH_STATE_SEARCHING;
}
