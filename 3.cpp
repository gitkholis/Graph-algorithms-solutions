#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

// global variables:
vector<tuple<int, int, int>> edjes;	        // representation of graph - list of edges with weight.
vector<tuple<int, int, int>> copyOfEdjes;   // temporary vector.
vector<pair<int, int>> mstEdjes;            // vector of second MST's edjes.
vector<pair<int, int>> minMstEdjes;         // vector of MST's edjes.
vector<int> p;		                        // temporary vector will be used for set's.
int cost;                                   // tmp variable for storing cost of the secondary MST's.
int minCost;                                // tmp variable for storing cost of the MST's.
int minMstSize;                             // tmp variable for storing size of res vector's size.
int n, m, indextmp;

// function for reading input data (except the first string) and creating graph:
void readAndCreateGraph() {                          
    //cin >> n >> m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int vertex1, vertex2, price;
        scanf("%d %d %d", &vertex1, &vertex2, &price);
        //cin >> vertex1 >> vertex2 >> price;
        edjes.push_back(make_tuple(vertex1, vertex2, price));
    }
    //for (int i = 0; i < m; ++i) {
        // here, we will sort vector of edjes by weight (min to max).
        //sort(edjes.begin(), edjes.end(), [](auto& left, auto& right) {return get<2>(left) < get<2>(right);}); for c++14.
        sort(edjes.begin(), edjes.end(), [](const tuple<int, int, int>& left, const tuple<int, int, int>& right) {
            return get<2>(left) < get<2>(right);
        }); // for c++11.
    //}
    copyOfEdjes = edjes;                     // doing the copy of list of edjes.
}
// this function returns: in which set, vertex "v" is located.
int dsu_get(int v) {
    return (v == p[v]) ? v : (p[v] = dsu_get(p[v]));
}
// this function does: unites two received set's (trees).
void dsu_unite(int a, int b) {
    a = dsu_get(a);
    b = dsu_get(b);
    if (rand() & 1) swap(a, b);
    if (a != b) p[a] = b;
}
// function that find's Minimal Spanning Tree using Disjoint-Set-Union.
void mst(int n, int m) {
    cost = 0;
    p.resize(n + 1);
    for (int i = 1; i < n + 1; ++i) {
        p[i] = i;
    }
    for (int i = 0; i < m; ++i) {
        int a = get<0>(edjes[i]), b = get<1>(edjes[i]), l = get<2>(edjes[i]);
        if (dsu_get(a) != dsu_get(b)) {
            cost += l;
            mstEdjes.push_back({a, b});
            dsu_unite(a, b);
        }
    }
}
// this function find's an edge in list of edjes and returns its index.
int findInEdjes(int a, int b) {
    for (int i = 0; i < edjes.size(); ++i) { 
        if ((get<0>(edjes[i]) == a) and (get<1>(edjes[i]) == b)) return i;
    }
}

void secondMST() {
    minMstSize = n - 1;                        // the number of edjes in MST always equal to n - 1 (n - number of vertices).
    minMstEdjes = mstEdjes;                    // storing the MST's edjes.
    int bestMinCost = cost;                    // storing MST's cost in this variable.
    minCost = cost * cost;                     // in minCost we will store the second MST's cost.
    tuple<int, int, int> tmpEdge;              // tmp tuple for storing some edjes.
    /*
    * In this loop, we will be delete all edjes that included for MST
    * one by one from list of edjes and then we will call MST function in each case.
    * if the cost of new MST is satisfies our condition, this cost will be stored minCost variable (second MST's cost).
    * Then we insert back the edje which we deleted and we will go next iteration.
    */
    for (int iter = 0; iter < minMstSize; ++iter) {
        //mstEdjes.erase(mstEdjes.begin(), mstEdjes.end());
        mstEdjes.clear();
        indextmp = findInEdjes(minMstEdjes[iter].first, minMstEdjes[iter].second);
        tmpEdge = edjes[indextmp];
        edjes.erase((edjes.begin() + indextmp));
        mst(n, (m - 1));
        if ((cost < minCost) and (cost > bestMinCost)) {
            minCost = cost;
        }
        edjes = copyOfEdjes;
    }
    cout << minCost << endl;
}

int main() {
    readAndCreateGraph();                     // reading from standard input and creating graph.
    mst(n, m);                                 // calling Minimal Spanning Tree function.
    secondMST();
    return 0;
}