#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define to_battery true
#define to_tower false

//global variables:
vector<vector<int>> magAbilities;
vector<vector<int>> graph;       
vector<vector<int>> reversegraph;
vector<int> used;
int n;
int totalPowerForMags = 0;
const int INF = (int)(1e9) + 310;
int T;                      
int timer = 1;             
int start;


struct Edge {
    int u;
    int v;                 
    int flow;            
    int capacity;          

    Edge(int u, int v, int capacity)
        : u(u), v(v), flow(0), capacity(capacity) {}

    int get_capacity() {    
        return capacity - flow;
    }
};


vector<Edge> edges;
void add_edge(int u, int v, int capacity) {
    graph[u].emplace_back(edges.size());  
    reversegraph[v].emplace_back(edges.size());
    edges.emplace_back(u, v, capacity);                    
}


void delete_edge(int u, int v) { 
    edges.pop_back(); 
    reversegraph[v].pop_back();                       
    graph[u].pop_back();
}


void read_and_create_graph() {
    scanf("%d", &n);
    T = n;
    magAbilities.resize(n);
    graph.resize(n+1);
    reversegraph.resize(n + 1);
    for (int i = 0; i < n; ++i) {
        magAbilities[i].resize(3);
        scanf("%d %d %d", &magAbilities[i][0], &magAbilities[i][1], &magAbilities[i][2]);
        totalPowerForMags += magAbilities[i][0];
    }
    for (int from = 0; from < n; ++from) {
        if (magAbilities[from][2]) {
            for (int q = 0; q < magAbilities[from][2]; ++q) {
                int to, w;
                scanf("%d %d", &to, &w);
                add_edge(from, to, w);
            }
        }
    }
}


int dfs(int v, int min_capacity) {
    if (v == T) {
        return min_capacity;
    }
    used[v] = timer;
    for (int index : graph[v]) {
        if ((edges[index].get_capacity() > 0) && (used[edges[index].v] != timer)) {
            int x = dfs(edges[index].v, min(min_capacity, edges[index].get_capacity()));
            if (x > 0) {
                edges[index].flow += x;
                return x;
            }
        }
    }
    for (int index : reversegraph[v]) {
        if ((edges[index].flow > 0) && (used[edges[index].u] != timer)) {
            int x = dfs(edges[index].u, min(min_capacity, edges[index].flow));
            if (x > 0) {
                edges[index].flow -= x;
                return x;
            }
        }
    }
    return 0;
}


int find_flow() {
    used.clear();
    used.resize(n + 1);    
    timer = 1;
    while (dfs(0, INF)) {
        ++timer;
    }   
    int result = 0;   
    for (int index: reversegraph[n]) {
        result += edges[index].flow;
    }
    for (int index : graph[n]) {
        result -= edges[index].flow;
    }
    return result;
}


void add_dummy_edges(bool flag) {
    start = edges.size();
    if (flag == to_battery) {  
        for (int u = 1; u < n; ++u) {
            if (magAbilities[u][0])
                add_edge(u, n, magAbilities[u][0]);
        }
    }
    else {
        for (int u = 1; u < n; ++u) {
            if (magAbilities[u][1]) {
                add_edge(u, n, INF);
                add_edge(n, u, INF);
            }
        }
    }
}


void delete_dummy_edges() {
    for (int u = 1; u < n; ++u) {
        if (magAbilities[u][0])
            delete_edge(u, n);
    }
}


void create_residual_net() {
    int graphsize = graph.size();
    for (int index = 0; index < graphsize; ++index) {
        if (edges[index].flow > 0) {
            add_edge(edges[index].v, edges[index].u, edges[index].flow);
        }
        edges[index].capacity = edges[index].get_capacity();
        edges[index].flow = 0;
    }
}


int main() {
    read_and_create_graph();
    add_dummy_edges(to_battery);
    if (find_flow() != totalPowerForMags) {
        cout << -1 << endl;
        return 0;
    }
    else {        
        delete_dummy_edges();
        add_dummy_edges(to_tower);
        create_residual_net();        
        cout << find_flow() << endl;
        return 0;
    }
}