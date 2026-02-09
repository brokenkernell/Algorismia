#include <iostream>
#include <vector>
#include <string>
using namespace std;

using VE  = vector<int>;
using VS = vector<string>;

int n, t;
VE V;

void escriu () {
	cout << "{";
	int j = 0;
	bool primer = true;
	
	while (V[j] == 0 and j <= n) ++j;
	
	if (j >= n) {
		cout << "}" << endl;
		return;
	}
	while (j < n) {
		if (V[j] != 0) {
			if (not primer) cout << ",";
			primer = false;
			cout << j+1;
			for (int k = 0; k < V[j] - 1; ++k) cout << "," << j+1;
		}
		++j;
	}
	cout << "}" << endl;
}

void f (int p, int vegades) {
	if (p == n and vegades == t) {
		escriu();
		return;
	}
	if (p == n or vegades > t) return;
	for (int i = 0; i <= t; ++i) {
		V[p] = i;
		f(p+1, vegades+i);
	}
}

int main () {
	cin >> n >> t;
	V = VE(n);
	f(0, 0);
}
