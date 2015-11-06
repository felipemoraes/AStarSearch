#ifndef __util__
#define __util__

#include <stdio.h>
#include <stdlib.h>
#include "nodestate.h"
  
int  _mergeSort(int arr[], int temp[], int left, int right);
int merge(int arr[], int temp[], int left, int mid, int right);
  
int inversions_count(vector<int> arr){
    int array_size = arr.size();
    int *arr_ = (int *)malloc(sizeof(int)*array_size);
    for (int i = 0; i < array_size; ++i){
        arr_[i] = arr[i];
    }
    int *temp = (int *)malloc(sizeof(int)*array_size);
    return _mergeSort(arr_, temp, 0, array_size - 1);
}
  
int _mergeSort(int arr[], int temp[], int left, int right){
  int mid, inv_count = 0;
  if (right > left) {
    mid = (right + left)/2;
    inv_count  = _mergeSort(arr, temp, left, mid);
    inv_count += _mergeSort(arr, temp, mid+1, right);
    inv_count += merge(arr, temp, left, mid+1, right);
  }
  return inv_count;
}
  
int merge(int arr[], int temp[], int left, int mid, int right){
  int i, j, k;
  int inv_count = 0;
  
  i = left; /* i is index for left subarray*/
  j = mid;  /* i is index for right subarray*/
  k = left; /* i is index for resultant merged subarray*/
  while ((i <= mid - 1) && (j <= right)){
    if (arr[i] <= arr[j]){
      temp[k++] = arr[i++];
    }
    else{
      temp[k++] = arr[j++];
      inv_count = inv_count + (mid - i);
    }
  }
  
  while (i <= mid - 1)
    temp[k++] = arr[i++];
  
  while (j <= right)
    temp[k++] = arr[j++];
  for (i=left; i <= right; i++)
    arr[i] = temp[i];
  
  return inv_count;
}

NodeState get_start_state(string infile, int& n){
    int blank_pos = 0,i=0;

    ifstream in(infile.c_str());

    vector<int> start_state;
    
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
    

    NodeState start;
    start.state_ = start_state;
    start.blank_pos_ = blank_pos;
    start.label_ = 0;
    in.close();
    return start;
}


NodeState get_goal_state(int n){
    
    NodeState goal;
    
    vector<int> goal_state;


    for (int i = 0; i < n*n;++i){
        goal_state.push_back(i);
    }
    
    goal.state_ = goal_state;
    goal.blank_pos_ = 0;
    return goal;
}

    
bool is_solvable(NodeState node, int n){
    
    vector<int> state_cp(node.state_);
    state_cp.erase(state_cp.begin()+ node.blank_pos_);
    int inv = inversions_count(state_cp);
    if ((n%2 ==1) && (inv% 2 == 0)) {
        return true;
    } else if ((n%2==0) && ((inv + node.blank_pos_/n )% 2)== 0){
        return true;
    } else {
        return false;
    }
}


#endif /* defined(__util__) */

