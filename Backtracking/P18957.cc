#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VE = vector<int>;
using VB = vector<bool>;
using VS = vector<string>;

VE V;
VS S;
int n;

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

void f (int p) {
	if (p == n) return escriu();
	V[p] = 0;
	f(p+1);
	V[p] = 1;
	f(p+1);
}

int main () {
	cin >> n;
	V = VE(n);
	S = VS(n);
	for (int i = 0; i < n; ++i) cin >> S[i];
	f(0);
}
