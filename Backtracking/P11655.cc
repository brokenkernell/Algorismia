#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VE = vector<int>;
using VB = vector<bool>;
using VS = vector<string>;

VE V, U;
int n, s, suma;

void escriu() {
	cout << "{";
	bool primer = true;
	for (int i = 0; i < n; ++i) {
		if (V[i]) {
			cout << (primer ? "" : ",") << U[i];
			primer = false;
		}
	}
	cout << "}" << endl;
}

void f (int p, int sum, int tot) {
	if (p == n or sum > s or tot < s - sum) {
		if (sum == s) escriu();
		return;
	}
	
	V[p] = 0;
	f(p+1, sum, tot-U[p]);
	if (sum < s or U[p] == 0) {
		V[p] = 1;
		f(p+1, sum+U[p], tot-U[p]);
	}
}

int main () {
	cin >> s >> n;
	V = VE(n);
	U = VE(n);
	for ( int i = 0; i < n; ++i ) {
		cin >> U[i];
		suma += U[i];
	}
	f(0,0, suma);
}
