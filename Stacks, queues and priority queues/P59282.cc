#include<iostream>
#include<queue>
using namespace std;

const int INF = 1e9;
priority_queue<int> Q;
int maxim = -INF;
double avg = 0;
string s;

void print (bool b) {
    if (b)
        cout << "minimum: " << -Q.top() << ", maximum: " << maxim << ", average: " << avg/Q.size() << endl;
    else cout << "no elements" << endl;
}

int main() {
    cout.setf(ios::fixed);
    cout.precision(4);
    
    while (cin >> s) {
        if (s == "number") {
            int n;
            cin >> n;
            if (maxim < n) maxim = n;
            Q.push(-n);
            avg += n;
            print(true);
        }
        else if (Q.empty()) print(false);
        else {
            int x = Q.top();
            avg += x;
            Q.pop();
            if (not Q.empty()) print(true);
            else {
                maxim = -INF;
                print(false);
            }
        }
    }
}
