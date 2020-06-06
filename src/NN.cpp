#include "NN.h"
#include<iostream>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include <limits>
using namespace std;


bool check_all_visited(int n, int visited[]) {
    for (int i = 0; i <= n ; i++) {
        if (!visited[i]) {
            return false;
        }
    }
    return true;
} 

int find_nearest_neighbour(int n, vector<vector<double> > VehicleCost, int visited[], int current_vertex) {
    double min_distance = numeric_limits<int>::max();
    int min_index = 0;
    for (int i = 0; i <= n; i++) {
        if (!visited[i] && VehicleCost[current_vertex][i] < min_distance) {
            min_distance = VehicleCost[current_vertex][i];
            min_index = i;
        }
    }
    return min_index;
}

void solveTSP (vector <int> &T, vector <vector<double> > VehicleCost, int n) {
    //start node = depot = node 0
    int start_node = 0;
    // initialize visited array    
    int visited[n];

    for (int i = 0; i <= n; i++) {
        visited[i] = 0;
    }

    visited[start_node] = 1;
    int current_vertex = start_node;
    T.push_back(current_vertex);

    while (!check_all_visited(n,visited)) {
        current_vertex = find_nearest_neighbour(n,VehicleCost,visited,current_vertex);
        visited[current_vertex] = 1;
        T.push_back(current_vertex);
    }
    T.push_back(0); 
}                                 



