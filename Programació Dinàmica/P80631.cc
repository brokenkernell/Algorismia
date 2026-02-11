#include <iostream>
#include <vector>
#include <cstring> // Per memset

using namespace std;

const int MOD = 100000007;
const int MAX = 85;

// Taules de memoització i precomputació
long long memo_part[MAX][MAX];
long long C[MAX][MAX];
long long fact[MAX];

// 1. Precomputació de Binomials i Factorials (O(N^2))
// Això es fa una sola vegada a l'inici del programa.
void precompute() {
    // Factorials
    fact[0] = 1;
    for (int i = 1; i < MAX; ++i)
        fact[i] = (fact[i - 1] * i) % MOD;

    // Triangle de Pascal (Binomials)
    for (int i = 0; i < MAX; ++i) {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }
}

// 2. DP Optimitzada: Particions en k subconjunts de mida >= 2
// Complexitat: O(1) per estat gràcies a la recurrència matemàtica.
// Recurrència: f(n, k) = k*f(n-1, k) + (n-1)*f(n-2, k-1)
long long get_partitions(int n, int k) {
    if (k == 0) return (n == 0) ? 1 : 0;
    if (n < 2 * k) return 0; // Poda: no hi ha prou elements
    if (k == 1) return 1;    // Si n >= 2, només hi ha 1 manera de fer 1 grup
    
    if (memo_part[n][k] != -1) return memo_part[n][k];

    // Opció A: L'element 'n' s'uneix a un dels k grups existents
    long long join_existing = (k * get_partitions(n - 1, k)) % MOD;

    // Opció B: L'element 'n' crea un nou grup amb un soci (triat entre n-1)
    long long create_new = ((n - 1) * get_partitions(n - 2, k - 1)) % MOD;

    return memo_part[n][k] = (join_existing + create_new) % MOD;
}

void solve() {
    int n, c;
    while (cin >> n >> c) {
        long long total_ways = 0;
        
        // Iterem sobre 'r': nombre de pastissos que es repeteixen (multis)
        // Restricció 1: Almenys la meitat han de ser repetits -> r >= (c+1)/2
        // Restricció 2: No podem repetir més tipus dels que hi ha -> r <= c
        int min_r = (c + 1) / 2;

        for (int r = min_r; r <= c; ++r) {
            int singles = c - r;
            int remaining_slots = n - singles;

            // Comprovacions ràpides de validesa per evitar càlculs inútils
            if (singles < 0 || remaining_slots < 2 * r) continue;

            // 1. Triar quins 'r' tipus seran els repetits
            long long ways = C[c][r];

            // 2. Col·locar els pastissos 'singles' (triar llocs i ordenar-los)
            //    Triar llocs: C[n][singles]
            //    Ordenar: singles!
            long long ways_singles = (C[n][singles] * fact[singles]) % MOD;
            ways = (ways * ways_singles) % MOD;

            // 3. Col·locar els 'r' tipus repetits en els llocs restants
            //    Particionar els llocs en r grups vàlids * r! (per assignar sabors als grups)
            long long ways_repeats = (get_partitions(remaining_slots, r) * fact[r]) % MOD;
            
            ways = (ways * ways_repeats) % MOD;
            total_ways = (total_ways + ways) % MOD;
        }
        cout << total_ways << endl;
    }
}

int main() {
    // Inicialització ràpida
    memset(memo_part, -1, sizeof(memo_part));
    precompute();
    
    solve();
    return 0;
}
