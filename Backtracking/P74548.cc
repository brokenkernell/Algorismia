#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VE = vector<int>;

VE V, body, legs;
int n;

void escriu() {
	for (int i = 0; i < 2*n; i += 2) {
		char head = 'A' + i/2;
		char legs = 'a' + V[i+1];
		cout << (i ? "-" : "") << head << V[i] << legs;
	}
	cout << endl;
}

void g (int m) {
	if (m == 2*n) return escriu();
	for (int i = 0; i < n; ++i) {
		if (m%2 == 0 and not body[i]) {
			V[m] = i;
			body[i] = 1;
			g(m+1);
			body[i] = 0;
		}
		if(m%2 == 1 and not legs[i]) {
			V[m] = i;
			legs[i] = 1;
			g(m+1);
			legs[i] = 0;
		}
	}
}

int main () {
	for (int cas = 1; cin >> n and n!= 0; ++cas) {
		V = VE(2*n);
		body = legs = VE(n, 0);
		cout << "Case " << cas << endl;
		g(0);
	}
}
