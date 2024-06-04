
#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
#include <limits>
#include <algorithm>

using namespace std;

class Graph {

    //storing the graph
    typedef unordered_map<string, unordered_map<string, int> > AdjMap;
    AdjMap adj;

public:
    void addVertex(const string &label) {
       
       //adding vertex to the graph
       adj[label];

    }

    void addEdge(const string &from, const string &to, int weight) {
        
        //adding edge 
        adj[from][to] = weight;

    }

    void removeVertex(const string &label) {
        //removing vertex from the graph
        adj.erase(label);
        for (AdjMap::iterator it = adj.begin(); it != adj.end(); ++it) {

            it->second.erase(label);

        }
    }

    void removeEdge(const string &from, const string &to) {
       
        adj[from].erase(to);

    }

    void printTable() {

        //printing table
        for (AdjMap::const_iterator it = adj.begin(); it != adj.end(); ++it) {

            cout << it->first << ": ";

            for (unordered_map<string, int>::const_iterator inner_it = it->second.begin(); inner_it != it->second.end(); ++inner_it) {
                
                cout << "(" << inner_it->first << ", " << inner_it->second << ") ";

            }

            cout << endl;

        }
    }

    void shortestPath(const string &start, const string &end) {

        typedef unordered_map<string, int> DistMap;
        typedef unordered_map<string, string> PrevMap;
        typedef set<pair<int, string> > PQ;

        DistMap dist;
        PrevMap prev;
        PQ pq;

        for (AdjMap::const_iterator it = adj.begin(); it != adj.end(); ++it) {
            dist[it->first] = numeric_limits<int>::max();
        }

        dist[start] = 0;
        pq.insert(make_pair(0, start));

        while (!pq.empty()) {

            string u = pq.begin()->second;
            pq.erase(pq.begin());

            if (u == end) break;

            for (unordered_map<string, int>::const_iterator it = adj[u].begin(); it != adj[u].end(); ++it) {

                int alt = dist[u] + it->second;
                if (alt < dist[it->first]) {
                    pq.erase(make_pair(dist[it->first], it->first));
                    dist[it->first] = alt;
                    prev[it->first] = u;
                    pq.insert(make_pair(alt, it->first));

                }
            }
        }

        if (dist[end] == numeric_limits<int>::max()) {

            cout << "No path exists" << endl;

        } else {

            vector<string> path;
            for (string at = end; at != start; at = prev[at])

                path.push_back(at);

            path.push_back(start);
            reverse(path.begin(), path.end());

            cout << "Shortest path: ";
            for (vector<string>::iterator it = path.begin(); it != path.end(); ++it)
                cout << *it << " ";
            cout << "\nTotal weight: " << dist[end] << endl;

        }
    }
};

int main() {

    Graph g;
    string command, from, to, label;
    int weight;

    while (true) {

        cout << "Commands: add_vertex, add_edge, remove_vertex, remove_edge, print, shortest_path, quit" << endl;
        cout << "Enter command: ";
        cin >> command;

        if (command == "add_vertex") {

            cout << "Enter vertex label: ";
            cin >> label;
            g.addVertex(label);

        } else if (command == "add_edge") {

            cout << "Enter from vertex, to vertex, and weight: ";
            cin >> from >> to >> weight;
            g.addEdge(from, to, weight);

        } else if (command == "remove_vertex") {

            cout << "Enter vertex label: ";
            cin >> label;
            g.removeVertex(label);

        } else if (command == "remove_edge") {

            cout << "Enter from vertex and to vertex: ";
            cin >> from >> to;
            g.removeEdge(from, to);

        } else if (command == "print") {

            g.printTable();

        } else if (command == "shortest_path") {

            cout << "Enter start vertex and end vertex: ";
            cin >> from >> to;
            g.shortestPath(from, to);

        } else if (command == "quit") {

            break;

        } else {

            cout << "Invalid command." << endl;

        }
    }

    return 0;
    
}
