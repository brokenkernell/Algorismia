#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef vector<int> Vec;

int n;
Vec V, posats;

void escriu() {
    cout << "(";
    cout << V[0];
   for (int i = 1; i < n; ++i) cout << "," << V[i];
    cout << ")" << endl;
}

void f(int p) {
    if(p==n) return  escriu();
    for (int i = 1; i <= n; ++i) {
        if(not posats[i-1]) {
            V[p] = i;
            posats[i-1] = true;
            f(p+1);
            posats[i-1] = false;
        }
    }

}

int main() {
    cin >> n;
    V = Vec(n);
    posats = Vec(n, false);
    
    f(0);
}
