#include <iostream>
#include <vector>
#include <queue>
using namespace std;

using VE = vector<int>;

int main () {
    queue <string> q;
    string s;
    while (cin >> s and s != "alex") q.push(s);
    int n = s.size();
    vector< queue<string> > llista(28);
    string par;
    for (int i = n-1; i >= 0; --i) {
        while (not q.empty()) {
            par = q.front();
            q.pop();
            int on = par[i] - 'a' + 1;
            llista[on].push(par);
        }
        for (int j = 0; j < 28; ++j) {
            while (not llista[j].empty()) {
                par = llista[j].front();
                llista[j].pop();
                q.push(par);
            }
        }
    }
    while (not q.empty()) {
        cout << q.front();
        q.pop();
        if (not q.empty()) cout << ' ';
    }
    cout << endl;
}
