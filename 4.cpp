#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

// global variables:
vector<bool> visited;		            // visited vertices - temporary vector
vector<int> ans;			            // vertices by order
vector<vector<int>> Graph;              // matrix of graph weights.
vector<vector<int>> adj;	            // representation of graph - adjacency list
vector<int> NodeCalculationTime;        // weights of each node (vertex).
const int INF = 99999;                  // infinity equal to this number.
int n;


// function for reading relations between nodes - matrix of graph weights.
void ReadAndCreateGraph() {
    scanf("%d", &n);
    //cin >> n;

    Graph.resize(n);
    adj.resize(n);

    for (int i = 0; i < n; ++i) {
        int tmp;
        scanf("%d", &tmp);
        //cin >> tmp;
        Graph[i].resize(n);
        NodeCalculationTime.push_back(tmp);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int tmp;
            scanf("%d", &tmp);
            //cin >> tmp;
            if (tmp) {
                Graph[i][j] = NodeCalculationTime[i] + NodeCalculationTime[j];
                adj[i].push_back(j);
            }
            else {
                Graph[i][j] = INF;
            }
        }
    }
}
// function for printing matrix of longest distances (to output.txt).
void PrintGraph() {
    //ofstream output;
    //output.open("output.txt");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (Graph[i][j] < INF) {
                printf("%d ", Graph[i][j]);
            }
            else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

void LongestPath() {
    for (int i = 0; i < n; ++i) {
        int ans_i = ans[i];
        for (int k = i + 1; k < n; ++k) {
            int ans_k = ans[k];
            int b = Graph[ans_i][ans_k];
            if (b != INF) {
                for (int j = k + 1; j < n; ++j) {
                    int ans_j = ans[j];
                    int a = Graph[ans_i][ans_j];
                    int c = Graph[ans_k][ans_j];
                    int d = b + c - NodeCalculationTime[ans_k];
                    if (c != INF) {
                        int min, max;
                        if (a > d) {
                            max = a;
                            min = d;
                        }
                        else {
                            min = a;
                            max = d;
                        }
                        if (a != INF) {
                            Graph[ans_i][ans_j] = max;
                        }
                        else {
                            Graph[ans_i][ans_j] = min;
                        }
                    }
                }
            }
        }
    }
}
// DFS.
void DFS(int v) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (visited[u] == false) DFS(u);
    }
    ans.push_back(v);
}
// topological sort.
void TopologicalSort(int size) {
    visited.resize(n);
    visited.assign(size, 0);
    ans.clear();

    for (int i = 0; i < size; ++i) {
        if (visited[i] == false)
            DFS(i);
    }

    reverse(ans.begin(), ans.end());
}

int main() {
    ReadAndCreateGraph();
    TopologicalSort(n);
    LongestPath();
    PrintGraph();
    return 0;
}
