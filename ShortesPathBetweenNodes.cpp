#include<iostream>
#include<unordered_map>
#include<vector>
#include<list>
#include<stack>
#include<limits.h>

using namespace std;

class graph {
    public:
    
    unordered_map<int, list<pair<int, int> > > adj;
    
    void addEdges(int u, int v, int weight) {
        pair<int, int> p = make_pair(v, weight);
        
        adj[u].push_back(p);
    }
    
    void printAdj() {
        for(auto i : adj) {
            cout << i.first << "->";
            for(auto j : i.second) {
                cout << "(" << j.first << "," << j.second << ")";
            }
            cout << endl;
        }
    }
    
    void topoSort(int node, unordered_map<int, bool> &vis, stack<int> &s) {
        vis[node] = 1;
        
        for(auto neighbour : adj[node]) {
            if(!vis[neighbour.first]) {
                topoSort(neighbour.first, vis, s);
            }
        }
        
        s.push(node);
    }
    
    void getShortestPath(int src, vector<int> &dist, stack<int> &topo) {
        dist[src] = 0;
        
        while(!topo.empty()) {
            int top = topo.top();
            topo.pop();
            
            if(dist[top] != INT_MAX) {
                for(auto it : adj[top]) {
                    if((dist[top] + it.second) < dist[it.first]) {
                        dist[it.first] = dist[top] + it.second;
                    }
                }
            }
        }
    }
};

int main() {
    
    graph g;
    
    int n = 6;
    
    g.addEdges(0, 1, 5);
    g.addEdges(0, 2, 3);
    g.addEdges(1, 2, 2);
    g.addEdges(1, 3, 6);
    g.addEdges(2, 3, 7);
    g.addEdges(2, 4, 4);
    g.addEdges(2, 5, 2);
    g.addEdges(3, 4, -1);
    g.addEdges(4, 5, -2);
    
    g.printAdj();
    
    unordered_map<int, bool> visited;
    stack<int> s;
    
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            g.topoSort(i, visited, s);
        }
    }
    
    vector<int> dis(n, INT_MAX);
    
    int src = 1;
    
    g.getShortestPath(src, dis, s);
    
    cout << endl << "The shortest path between Nodes are : " << endl;
    for(int i = 0; i < n; i++) {
        cout << dis[i] << " ";
    } 
    cout << endl;
    
    return 0;
}