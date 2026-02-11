#include<iostream>
#include<vector>
#include <queue>
using namespace std;

int main() {
    cout.setf(ios::fixed);
    cout.precision(4);
    int n;
    cin >> n;
    priority_queue<double> Q;
    double bits = 0;
    for (int i = 0; i < n; ++i) {
        double x;
        cin >> x;
        Q.push(-x);
    }
    while (Q.top() != -100) {
        double x = Q.top(); Q.pop();
        double y = Q.top(); Q.pop();
        bits += x+y;
        Q.push(x+y);
    }
    cout << "nombre esperat de bits per lletra: " << -bits/100 << endl;
}
