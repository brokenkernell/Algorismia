#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        vector<int> l(n);
        int imin = 0;
        for (int i = 0; i < n; ++i) {
            cin >> l[i];
            if(l[i] < l[imin]) imin = i;
        }
        vector<int> wins(n);
        for (int i = 0; i < n; ++i) wins[i] = min(l[i], l[imin] + (l[i]+l[imin]+3)/4);
        string s, t;
        cin >> s >> t;
        vector<vector<int> > M(s.size()+1, vector<int> (t.size()+1, 0));
        for (int i = 1; i <= s.size(); ++i) M[i][0] = M[i-1][0] + wins[s[i-1]-'a'];
        for (int j = 1; j <= t.size(); ++j) M[0][j] = M[0][j-1] + wins[t[j-1]-'a'];
        for (int i = 1; i <= s.size(); ++i) {
            for (int j = 1; j <= t.size(); ++j) {
                if (s[i-1] == t[j-1]) M[i][j] = M[i-1][j-1];
                else {
                    int x = M[i-1][j] + wins[s[i-1]-'a'];
                    int y = M[i][j-1] + wins[t[j-1]-'a'];
                    int z = M[i-1][j-1]+(l[s[i-1]-'a']+l[t[j-1]-'a']+3)/4;
                    M[i][j] = min(min(x,y), z);
                }
            }
        }
        cout << M[s.size()][t.size()] << endl;
    }
}
