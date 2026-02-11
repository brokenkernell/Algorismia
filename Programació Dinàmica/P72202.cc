#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<vector<int> > dp(501, vector<int> (500, 0));
    for (int i = 1; i < 501; ++i) {
        if(i < 5) dp[i][0] = (i+1)/2;
        else dp[i][0] = dp[(i+1)/2][0]+dp[(i+2)/2][0]-1;
        for (int j = 1; j < i; ++j) {
            for (int k = 1; k*(j+1) <= i; ++k) {
                dp[i][j] = max(dp[i][j], dp[k][0]+dp[i-k][j-1]);
            }
        }
    }
    int n, eff;
    while (cin >> n >> eff) {
        bool found = false;
        for (int i = 0; i < n and not found; ++i) {
            if((100*dp[n][i]) >= eff*n) {
                found = true;
                cout << i << endl;
            }
        }
    }
}

