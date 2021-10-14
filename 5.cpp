#include <bits/stdc++.h>
using namespace std;

// global variables:
vector<vector<int>> Ancestors;
vector<vector<int>> Graph;           
vector<int> destination_points;
vector<int> edjes;
vector<set<int>> color;
vector<bool> mark;
vector<int> dist;

const int INF = 999999;             
int max_length = 0;

void read_and_create_graph(int& n, int& m) {
    edjes.resize(n);
    mark.resize(n);
    int from, to, cost;
    for (int i = 0; i < n; ++i) {
        Graph[i].resize(n);
        Graph[i].assign(n, INF);
    }
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &from, &to, &cost);
        //cin >> from >> to >> cost;
        Graph[from][to] = cost;
        Graph[to][from] = cost;
        if (!from) {
            edjes[to] = cost;
        }
    }
}

int minDistance(vector<int> dist, vector<bool> sptSet, int &V) {
    // Initialize min value
    int min = INF;
    int min_index = 0;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void dijkstra(int &n) {
    int src = 0;
    int V = n;
    //vector<int> dist; The output array.  dist[i] will hold the shortest
    // distance from src to i
    dist.resize(n);
    vector<bool> sptSet;
    sptSet.resize(n);
    //bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized
    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INF, sptSet[i] = false;
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet, V);
        // Mark the picked vertex as processed
        sptSet[u] = true;
        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++) {
            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller (or equal) than current value of dist[v]
            int a = dist[v];
            int b = dist[u];
            int c = Graph[u][v];
            if (!sptSet[v] && c && b != INF && b + c <= a) {
                dist[v] = b + c;
                if (b + c == a) {
                    Ancestors[v].push_back(u);
                }
                if (b + c < a) {
                    Ancestors[v].clear();
                    Ancestors[v].push_back(u);
                }
            }
            
        }
    }
}

void find_ancestor_and_color_it(int& v, int &color_num) {
    vector<vector<int>> copyAncestors = Ancestors;
    int tmpv = v;
    for (int i = 0; i < Ancestors[v].size(); ++i) {
        color[v].insert(color_num);
        if (Ancestors[v][i] != 0)
            find_ancestor_and_color_it(Ancestors[v][i], color_num);
        else
            break;
    }
}

int main() {
    int n, m, k, tmp;
    scanf("%d %d %d", &n, &m, &k);
    //cin >> n >> m >> k;    
    Graph.resize(n);
    Ancestors.resize(n);
    color.resize(n);
    for (int i = 0; i < k; ++i) {
        scanf("%d", &tmp);
        //cin >> tmp;
        destination_points.push_back(tmp);
    }
    read_and_create_graph(n, m);
    Graph[0][0] = 0;

    dijkstra(n);
    int shortest = n;
    int v;
    
    for (int i = 0; i < k; ++i) {
        v = destination_points[i];
        color[v].insert(i);
        int tmpv = v;
        for (int j = 0; j < Ancestors[v].size(); j++) {
            find_ancestor_and_color_it(Ancestors[tmpv][j], i);
        }
    }

    int color_reach_index = 0;
    int x;
    for (int i = 0; i < n; ++i) {
        if (int(color[i].size()) == k) {
            if (dist[i] > dist[color_reach_index]) {
                color_reach_index = i;
            }
        }
    }
    x = dist[color_reach_index];
    cout << x << endl;
    return 0;
}