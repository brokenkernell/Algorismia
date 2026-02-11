#include <iostream>
#include <stack>
using namespace std;

void escriu (int n) {
    stack<int> S;
    S.push(n);
    while (not S.empty()) {
        int x = S.top();
        cout << ' ' << S.top();
        S.pop();
        if (x-1 > 0) {
            S.push(x-1);
            S.push(x-1);
        }
    }
}

int main() {
    int n;
    while (cin >> n) {
        escriu (n);
        cout << endl;
    }
}

