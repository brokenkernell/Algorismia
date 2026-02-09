#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef vector<int> VE;
typedef vector<string> VS;
typedef vector<bool> VB;

int S, n;
VB cont;
VE X;

void escriu() {
	bool primer = true;
	cout << "{";
	for (int i = 0; i < n; ++i) {
		if(cont[i]) {
			if (primer) primer = false;
			else cout << ",";
			cout << X[i];
		}
	}
	cout << "}";
	cout << endl;
} 
	
void f (int s, int i, bool nou) {
	if (s == S and nou) escriu();
	if (i < n) {
		cont[i] = true;
		f(s + X[i], i+1, true);
		cont[i] = false;
		f(s, i+1, false);
	}
}

int main () {
	cin >> S >> n;
	X = VE(n);
	for (int& e : X ) cin >> e;
	cont = VB(n);
	f(0,0, true);
}

