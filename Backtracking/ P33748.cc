#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VE = vector<int>;
using VB = vector<bool>;
using VS = vector<string>;

VE V;
VS S;
int n, m;

void escriu() {
	string coma = "";
	cout << "{";
	for (int i = 0; i < n; ++i) {
		if (V[i] == 1) {
			cout << coma << S[i];
			coma = ",";		
		}
	}
	cout << "}" << endl;
}

void f (int p, int par) {
	if (p == n) return escriu();
	if (p - par < n - m) {
		V[p] = 0;
		f(p+1, par);
	}
	if (par < m) {
		V[p] = 1;
		f(p+1, par+1);
	}
}

int main () {
	cin >> m >> n;
	V = VE(n);
	S = VS(n);
	for (int i = 0; i < n; ++i) cin >> S[i];
	f(0,0);
}

