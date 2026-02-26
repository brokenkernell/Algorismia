#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<bool> VB;
typedef vector<VB> VVB;

VB used;
VVI G;
int n, m;

int posicio(VI& v, int val) {
    for (int i = 0; i < v.size(); ++i) if(v[i] == val) return i;
}

void backtrack(int i, VI& perm, VB& usats, VVB& G1, VVB& G2, bool& isomorfs, int& n1) {
    if(isomorfs) return;
    if (i == n1) {
        for(int j = 0; j < n1; ++j) {
            for (int k = 0; k < n1; ++k) {
                if(G1[j][k] != G2[perm[j]][perm[k]]) return;
            }
        }
        isomorfs = true;
        return;
    }
    for (int j = 0; j < n1; ++j) {
        if(not usats[j]) {
            perm[i] = j;
            usats[j] = true;
            backtrack(i+1, perm, usats, G1, G2, isomorfs, n1);
            usats[j] = false;
        }
    }
}

bool comparacio(const int& x, const int& y) {
    if(G[x].size() != G[y].size()) return G[x].size() > G[y].size();
    return x > y;
}

//retorna si son isomorfs els subgrafs amb vertexs els elements de v1 i v2
//els vertexs de v1 i v2 estan ordenats per ordre decreixent de grau dels nodes
bool son_isomorfs(VI& v1, VI& v2) {
    if(v1.size() != v2.size()) return false;
    int n1 = v1.size();
    for (int i = 0; i < n1; ++i) {
        if(G[v1[i]].size() != G[v2[i]].size()) return false;
    }
    VVB G1(n1, VB(n1, false));
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < G[v1[i]].size(); ++j) G1[i][posicio(v1, G[v1[i]][j])] = true;
    }
    VVB G2(n1, VB(n1, false));
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < G[v2[i]].size(); ++j) G2[i][posicio(v2, G[v2[i]][j])] = true;
    }
    bool isomorfs = false;
    VI perm(n1);
    VB usats(n1, false);
    backtrack(0, perm, usats, G1, G2, isomorfs, n1);
    return isomorfs;
}

void DFS(int i, VI& v1) {
    used[i] = true;
    v1.push_back(i);
    for (int j = 0; j < G[i].size(); ++j) {
        if(not used[G[i][j]]) DFS(G[i][j], v1);
    }
}

int main() {
    while (cin >> n >> m) {
        VVI grafiso; // emmagatzema representants de les classes d'isomorfisme trobades
        VI numiso; // emmagatzema el nombre de representants trobats de les classes d'isomorfisme trobades
        G = VVI(n);
        for (int i = 0; i < m; ++i) {
            int x, y;
            cin >> x >> y;
            G[x].push_back(y);
            G[y].push_back(x);
        }
        used = VB(n, false);
        for (int i = 0; i < n; ++i) {
            if(not used[i]) {
                VI v1;
                DFS(i, v1);
                sort(v1.begin(), v1.end(), comparacio);
                bool found = false;
                for (int j = 0; j < grafiso.size() and not found; ++j) {
                    if(son_isomorfs(v1, grafiso[j])) {
                        ++numiso[j];
                        found = true;
                    }
                }
                if (not found) {
                    grafiso.push_back(v1);
                    numiso.push_back(1);
                }
            }
        }
        int total = 0;
        for (int i = 0; i < numiso.size(); ++i) {
            total += (numiso[i]*(numiso[i]-1))/2;
        }
        cout << total << endl;
}
}
