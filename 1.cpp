#include <bits/stdc++.h>
using namespace std;

// global variables:
vector<string> words;		// array of word's
string chars = "";			// string of used unique letter's in all word's
vector<vector<int>> adj;	// representation of graph - adjacency list
vector<int> visited;		// visited vertices - temporary vector
vector<int> ans;			// vertices by order
bool flagLoop = false;				// if flag = true, then graph looped
int indexMismatch1, indexMismatch2;  // mismatched letters index in word's

// function for reading input data (except first string = (int)):
void read(int n) {
    for (int i = 0; i < n; i++) {
        cin >> words[i];
    }
}
// searching char in chars:
bool search(char ch) {
    int size = chars.size();
    bool var = false;
    for (int i = 0; i < size; i++) {
        var = var or (ch == chars[i]);
    }
    return var;
}
// defining which characters are used in words:
void convert(int n) {
    for (int i = 0; i < n; i++) {
        int m = words[i].size();
        for (int j = 0; j < m; j++) {
            bool charExists = search(words[i][j]);
            if (!charExists) {
                chars += words[i][j];
            }
        }
    }
}
// what number this char matches: char --> number(from 1 to chars.size())
int whatNumber(char ch) {
    return (chars.find(ch));
}
// compare two words and returning first mismatching chars index if their exist:
int compareWords(string word1, string word2) {
    int size1 = word1.size();
    int size2 = word2.size();
    int checker = 0;
    int n;
    if (size1 <= size2) {
        n = size1;
    } else n = size2;
    for (int i = 0; i < n; i++) {
        if (word1[i] == word2[i]) checker += 1;
        else break;
    }
    if (checker == n) {
        indexMismatch1 = -1;
        indexMismatch2 = -1;
    }
    if (checker < n) {
        indexMismatch1 = checker;
        indexMismatch2 = checker;
    }
    if (indexMismatch1 == -1) return -1;
    else return 1;
}
// creating graph:
void createGraph(int n) {
    for (int i = 0; i < n - 1; i++) {
        int v1, v2;
        int cmpRes = compareWords(words[i], words[i + 1]);
        if (cmpRes == -1) continue;
        else {
            v1 = whatNumber(words[i][indexMismatch1]);
            v2 = whatNumber(words[i + 1][indexMismatch2]);
            adj[v1].push_back(v2);
        }
    }
}
// delete copies of edges in adj. list
void delCopy(int n) {
    for (int i = 0; i < n; i++) {
        auto result = unique(begin(adj[i]), end(adj[i]));
        adj[i].erase(result, end(adj[i]));
    }
}
// dfs
void dfs(int v) {
    visited[v] = 1;
    for (int u : adj[v]) {
        if (visited[u] == 1) {
            flagLoop = true;
            break;
        }
        else {
            if (visited[u] == 0) dfs(u);
        }
    }
    ans.push_back(v);
    visited[v] = 2;
}
// top. sort
void topological_sort(int size) {
    visited.assign(size, 0);
    ans.clear();
    for (int i = 0; i < size; ++i) {
        if (flagLoop) {
            break;
        }
        else {
            if (visited[i] == 0)
                dfs(i);
        }
    }
    reverse(ans.begin(), ans.end());
}

int main() {
    int n;
    cin >> n;		    // the number of word's
    words.resize(n);
    read(n);		    // reading from standard input
    convert(n);		    // getting from word's: unsorted string of letter's/char's.
    int size = chars.size();		// the number of letter's in a word (unique letters)
    adj.resize(size);				// setting size of vector's
    visited.resize(size);
    ans.resize(size);
    createGraph(n);					// making adj. list
    delCopy(size);
    topological_sort(size);			// sorting
    if (flagLoop) {
        cout << "-" << endl;
        return 0;
    }
    else {							// printing result
        for (int i = 0; i < size; i++) {
            cout << chars[ans[i]];
        }
    }
    cout << endl;
    return 0;
}