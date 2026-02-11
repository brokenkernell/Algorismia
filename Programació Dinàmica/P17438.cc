#include <iostream>
#include <vector>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
using vvvvi = vector<vvvi>;
using vvvvvi = vector<vvvvi>;
using vvvvvvi = vector<vvvvvi>;

vvvvvvi guanyador (2, vvvvvi(3, vvvvi(4, vvvi(5, vvi(6, vi(7, -1))))));

int f (int x1, int x2, int x3, int x4, int x5, int x6) {
    int& res = guanyador[x1][x2][x3][x4][x5][x6];
    if (res != -1) return res;
    
    for (int i = 1; i <= x1; ++i) {if (not f(x1 - i, x2, x3, x4, x5,x6)) return res = 1;}
    for (int i = 1; i <= x2; ++i) {if (not f(x1, x2 - i, x3, x4, x5,x6)) return res = 1;}
    for (int i = 1; i <= x3; ++i) {if (not f(x1, x2, x3 - i, x4, x5,x6)) return res = 1;}
    for (int i = 1; i <= x4; ++i) {if (not f(x1, x2, x3, x4 - i, x5,x6)) return res = 1;}
    for (int i = 1; i <= x5; ++i) {if (not f(x1, x2, x3, x4, x5 - i,x6)) return res = 1;}
    for (int i = 1; i <= x6; ++i) {if (not f(x1, x2, x3, x4, x5,x6 - i)) return res = 1;}
    return res = 0;
}

int main () {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        string j1, j2;
        cin >> j1 >> j2;
        int p1, p2, p3, p4, p5, p6;
        cin >> p1 >> p2 >> p3 >> p4 >> p5 >> p6;
        cout << "Joc #" << i << ": ";
        if ( f(p1, p2, p3, p4, p5, p6)) cout << j1 << endl;
        else cout << j2 << endl;
    }
}
