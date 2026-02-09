#include <iostream>
#include <vector>

using namespace std;
using VS  = vector<string>;
using VI  = vector< int>;
using VVI = vector< VI>;

int n;
VS l;
string s;
VVI u;

void f(int k) {
  if (k == 2*n) {
    cout << s << endl;
    return;
  }
  string& lletra = l[k%2];
  VI&       usat = u[k%2];
  for (int j = 0; j < n; ++j)
    if (not usat[j]) {
      usat[j] = true;
      s[k] = lletra[j];
      f(k+1);
      usat[j] = false;
    }
}

int main() {
  cin >> n;
  l = VS(2);
  cin >> l[0] >> l[1];
  s = string(2*n, ' ');
  u = VVI(2, VI(n, false));
  f(0);
}
