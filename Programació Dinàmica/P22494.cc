#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 *
 * El problema equival a trobar el nombre de particions de l'enter n
 * on cada part té una mida >= 2, i el nombre total de parts és >= 2.
 *
 * Siguin P2(n) el nombre de particions de l'enter n on totes les parts >= 2.
 * La resposta és P2(n) - 1 (per excloure la partició trivial n = n, amb 1 part).
 */
void solve() {
    const long long MOD = 100000000 + 7;
    
    const int MAX_N = 30000;
    
    // DP[i] emmagatzemarà P2(i): el nombre de particions de l'enter i
    // on totes les parts tenen una mida d'almenys 2.
    // L'índex va de 0 a MAX_N.
    vector<long long> dp(MAX_N + 1, 0);

    // Condició inicial: 1 manera de particionar 0 (la partició buida).
    // Això permet que el bucle de PD funcioni correctament.
    dp[0] = 1;

    // La PD s'executa una sola vegada per precalcular tots els valors fins a MAX_N.
    // Aquesta PD fa servir l'equivalent de la funció generadora:
    // G(x) = Prod_{j=2}^inf 1/(1 - x^j)
    
    // Iterem sobre la mida de les parts 'j'.
    // Com que totes les parts han de ser de mida >= 2, 'j' comença a 2.
    for (int j = 2; j <= MAX_N; ++j) {
        // Iterem sobre l'enter 'i' a particionar.
        // dp[i] = dp[i] + dp[i-j]
        // Això vol dir: El nombre de particions de 'i' usant només parts de mida >= 2
        // és igual al nombre de particions que NO usen 'j' com a part (dp[i] actual)
        // MÉS el nombre de particions que SÍ usen 'j' com a part (dp[i-j]).
        for (int i = j; i <= MAX_N; ++i) {
            dp[i] = (dp[i] + dp[i - j]) % MOD;
        }
    }

    int n;
    while (cin >> n) {
        // Casos on no és possible tenir cap partició agradable:
        // Una partició agradable ha de tenir almenys 2 subconjunts (parts),
        // i cada subconjunt ha de tenir almenys 2 elements (part >= 2).
        // Amb n=1, 2, 3 no es pot complir la suma de parts >= 2, amb un mínim de 2 parts.
        // O bé, si P2(n) és 1, vol dir que l'única partició amb parts >= 2 és n = n (una sola part).
        if (n < 4) {
             cout << 0 << endl; // Coincideix amb els exemples n=3 -> 0
             continue;
        }

        // P2(n) és el nombre total de particions de l'enter 'n' amb parts >= 2.
        long long num_partitions = dp[n];
        
        // Cal restar 1 per excloure el cas on el nombre de subconjunts (parts) és només 1.
        // La partició n = n, que correspon a {{1, ..., n}}, no és agradable.
        // La condició 'at least two subsets'  es tradueix a 'almenys 2 parts'.
        
        // (P2(n) - 1) mod MOD, assegurant un resultat positiu.
        long long nice_partitions = (num_partitions - 1 + MOD) % MOD;
        
        cout << nice_partitions << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}
