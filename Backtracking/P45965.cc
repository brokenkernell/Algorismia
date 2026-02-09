#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VE = vector<int>;
using VB = vector<bool>;
using VS = vector<string>;

VE V;
int n, u;

void escriu() {
	for (int i = 0; i < n; ++i) cout << (i ? " " : "" ) << V[i];
	cout << endl;
}

void f (int p, int uns) {
	if (p == n) return escriu();
	if (p-uns < n-u) {
		V[p] = 0;
		f(p+1, uns);
	}
	if (uns < u) {
		V[p] = 1;
		f(p+1, uns+1);
	}
}

int main () {
	cin >> n >> u;
	V = VE(n);
	f(0,0);
}
