#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
#include <limits>
#include <algorithm>
using namespace std;

class Graph {
    unordered_map<string, unordered_map<string, int>> adj;

public:
    void addVertex(const string &label) {
        adj[label];
    }

    void addEdge(const string &from, const string &to, int weight) {
        adj[from][to] = weight;
    }

    void removeVertex(const string &label) {
        adj.erase(label);
        for (auto &p : adj)
            p.second.erase(label);
    }
