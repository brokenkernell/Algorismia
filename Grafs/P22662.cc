#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> VI;

const int N = 100000;
int n;
VI pare;
VI v;

int busca(int i) {
    if(i == pare[i]) return i;
    pare[i] = busca(pare[i]);
    return pare[i];
}

void uneix(int a, int b) {
    pare[busca(a)] = busca(b);
}

int main() {
    vector<int> primers; // guarda els nombres primers fins a 100000 en ordre
    vector<int> t(N+1, -1); // t[k] guarda la posicio al vector primers del primer mes petit que divideix k
    int compt = 0;
    //Garbell d'Eratostenes
    for (int i = 2; i <= N; ++i) {
        if(t[i] == -1) {
            for(int j = i; j <= N; j += i) if(t[j] == -1) t[j] = compt;
            primers.push_back(i);
            ++compt;
        }
    }
    int M = primers.size();
    //Precalculem els factors primers de cada nombre entre 2 i 100000
    vector<vector<int> > factors(N+1);
    for(int i = 2; i <= N; ++i) {
        int aux = i;
        while(aux > 1) {
            int divisor = primers[t[aux]];
            factors[i].push_back(t[aux]);
            while(aux%divisor == 0) aux /= divisor;
        }
    }
    while (cin >> n) {
        v = VI(n);
        for (int i = 0; i < n; ++i) cin >> v[i];
        //Fem un MF-set amb els nombres primers entre 2 i 100000 de manera que dos primers estan relacionats si un dels nombres te tots dos factors
        pare = VI(M);
        for(int i = 0; i < M; ++i) pare[i] = i;
        for(int i = 0; i < n; ++i) {
            int aux = v[i];
            for(int j = 0; j < factors[aux].size(); ++j) {
                for(int k = 0; k < j; ++k) {
                    uneix(factors[aux][j], factors[aux][k]);
                }
            }
        }
        //per a cada factor primer que esta al cim d'una component connexa del MF-set guarda quants nombres de v en son fills
        VI num(M, 0);
        for(int i = 0; i < n; ++i) {
            ++num[busca(t[v[i]])];
        }
        int maxim = 0;
        for(int i = 0; i < M; ++i) maxim = max(maxim, num[i]);
        cout << maxim << endl;
    }
}
