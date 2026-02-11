#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VE = vector<int>;
using VL = vector<long long>;

int n;
VL uu(151), zero(151), zerou(151);

void f () {
    uu[2] = zero[2] = zerou[2] = 1;
    for (int i = 3; i < 151; ++i) {
        zero[i] = zerou[i-1] + uu[i-1];
        zerou[i] = zero[i-1];
        uu[i] = zerou[i-1];
    }
}

int main() {
    f();
    while (cin >> n){
        if (n <= 2) cout << n+1 << endl;
        else cout << zero[n] +  zerou[n] + uu[n] << endl;
    }
}
