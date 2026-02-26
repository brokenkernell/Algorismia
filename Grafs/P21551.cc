#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

int n, m;
VVI G;
VI C;

bool OK(queue<pair<int,int> >& q) {
    bool ok = true;
    while(not q.empty()) {
        int node = q.front().first;
        int color = q.front().second;
        q.pop();
        if(C[node] != -1 and C[node] != color) ok = false;
        if(C[node] == -1) {
            C[node] = color;
            for (int j = 0; j < G[node].size(); ++j) {
                q.push(make_pair(G[node][j], (color+1)%2));
            }
        }
    }
    return ok;
}

int main() {
    while(cin >> n >> m) {
        G = VVI(n);
        for (int i = 0; i < m; ++i) {
          int x, y;
          cin >> x >> y;
          G[x].push_back(y);
          G[y].push_back(x);
        }
        C = VI(n, -1);
        queue<pair<int,int> > q;
        q.push(make_pair(0, 0));
        bool b = OK(q);
        bool connex = true;
        for (int i = 0; i < n; ++i) if(C[i] == -1) connex = false;
        if(not connex) cout << "NC" << endl;
        else if(b) cout << "yes" << endl;
        else cout << "no" << endl;
    }
}

