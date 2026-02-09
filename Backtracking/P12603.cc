#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VE = vector<int>;
using VB = vector<bool>;
using VS = vector<string>;

VE V;
VS par;
int n;

void escriu() {
	for (int i = 0; i < n; ++i) cout << (i ? "," : "(") << par[V[i]];
	cout << ")" << endl;
}

void f (int m) {
	if (m == n) return escriu();
	for (int i = 0; i < n; ++i) {	
		V[m] = i;
		f(m+1);
	}
}

int main () {
	cin >> n;
	V = VE(n);
	par = VS(n);
	for ( int i = 0; i < n; ++i) cin >> par[i];
	f(0);
}

