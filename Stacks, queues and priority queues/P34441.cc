#include <iostream>
#include <stack>
using namespace std;

void escriu (int n) {
    stack<int> S;
    S.push(n);
    while (not S.empty()) {
        if (S.top() == 1) {
            cout << ' ' << S.top();
            S.pop();
            if (not S.empty()) {
                int x = S.top();
                cout << ' ' << x;
                S.pop();
                S.push(x-1);
            }
        }
        else {
            int x = S.top();
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
