#include <bits/stdc++.h>
using namespace std;

// global variables:
vector<vector<pair<int, int>>> adj;	// representation of graph - adjacency list with weight.
vector<int> visited;		        // visited vertices - temporary vector.
vector<int> dist;                   // vector of distances to each vertex from vertex with zero index.
deque<int> q;                       // vector for deque.
int n, k, newN, numberOfArcs;       // the number of vertices (building's) and maps.

// function for reading input data (except the first string) and creating graph:
void readAndCreateGraph() {
    scanf("%d %d", &n, &k);
    newN = 1 + n * k + n;            // calculating the number of vertices including dummy vertices.
    adj.resize(newN);

    for (int i = 0; i < k; ++i) {
        //cin >> numberOfArcs;
        scanf("%d", &numberOfArcs);
        int vertex1, vertex2;
        for (int j = 0; j < numberOfArcs; ++j) {
            //cin >> vertex1 >> vertex2;
            scanf("%d %d", &vertex1, &vertex2);
            vertex1 += n * i;
            vertex2 += n * i;
            // making arc's inside one map with weight = 0:
            adj[vertex1].push_back(make_pair(vertex2, 0));
            adj[vertex2].push_back(make_pair(vertex1, 0));
            // making arc's from one map to fictive map with weight = 1 (only for one direction):
            adj[vertex1].push_back(make_pair(vertex1 + n * (k - i), 0));
            adj[vertex1 + n * (k - i)].push_back(make_pair(vertex1, 1));
            adj[vertex2].push_back(make_pair(vertex2 + n * (k - i), 0));
            adj[vertex2 + n * (k - i)].push_back(make_pair(vertex2, 1));
        }
        // making arc's from adj[0] (fictive vertex) to the first vertices in each maps:
        adj[0].push_back(make_pair(1 + n * i, 1));
    }

    dist.resize(newN);
    dist.assign(newN, newN);        // by default all distances equal to: 1 + n * k + n (= "infinity").
}
// function for 0 - 1 BFS:
void BFS() {
    q.push_back(0);
    dist[0] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (int i = 0; i < (int)adj[v].size(); ++i) {
            if (dist[adj[v][i].first] > dist[v] + adj[v][i].second) {
                dist[adj[v][i].first] = dist[v] + adj[v][i].second;
                if (adj[v][i].second == 0) {
                    q.push_front(adj[v][i].first);
                }
                else {
                    q.push_back(adj[v][i].first);
                }
            }
        }
    }

    //output
    if (dist[newN - 1] < newN) {
        cout << dist[newN - 1] << endl;
    }
    else {                                // if dist[newN] >= "infinty", then there is no solution.
        cout << -1 << endl;
    }
}

int main() {
    readAndCreateGraph();             // reading from standard input and creating graph.
    BFS();                            // calling BFS function. 
    return 0;
}