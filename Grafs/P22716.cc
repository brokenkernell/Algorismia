#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm> // per a std::tie i std::make_tuple

using namespace std;

int N, M;
vector<string> grid;

//array de distàncies 3D: dist[fila][columna][[temps%4]
//Inicialitzat a -1 (no visitat)
int dist[500][500][4];

//Coordenades de l'inici ('I') i final ('F')
int start_r, start_c, end_r, end_c;

//vectors de moviment per a N, E, S, W
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

/**
 * Retorna l'orientació inicial com un enter:
 * 0: Nord, 1: Est, 2: Sud, 3: Oest
 * -1 si la casella no té porta mòbil (com 'F')
 */
int get_initial_orientation (char c) {
    if (c == 'N' || c == 'I') return 0;
    if (c == 'E') return 1;
    if (c == 'S') return 2;
    if (c == 'W') return 3;
    return -1; //'F', 'X' no tenen orientació de sortida
}

/**
 * Comprova si una casella (r, c) és vàlida per moure's-hi.
 */
bool is_valid (int r, int c) {
    return r >= 0 && r < N && c >= 0 && c < M && grid[r][c] != 'X';
}

void solve (int case_num) {
    cin >> N >> M;
    grid.resize(N);
    
    //Reinicialitza l'array de distàncies
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            for (int k = 0; k < 4; ++k) {
                dist[i][j][k] = -1;
            }
        }
    }
    
    //Llegeix la graella i troba 'I' i 'F'
    for (int i = 0; i < N; ++i) {
        cin >> grid[i];
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == 'I') {
                start_r = i; start_c = j;
            }
            else if (grid[i][j] == 'F') {
                end_r = i; end_c = j;
            }
        }
    }
    
    //Cua pel BFS: (fila, columna, temps%4)
    queue<tuple<int, int, int>> q;
    
    //Estat inicial
    q.push({start_r, start_c, 0});
    dist[start_r][start_c][0] = 0;
    
    while (!q.empty()) {
        auto[r, c, k] = q.front();
        q.pop();
        
        int current_time = dist[r][c][k];
        int next_k = (k+1)%4;
        int next_time = current_time + 1;
        
        // --- Opció 1: Esperar ---
        if (dist[r][c][next_k] == -1) {
            dist[r][c][next_k] = next_time;
            q.push({r, c, next_k});
        }
        
        // --- Opció 2: Moure ---
        int init_ori = get_initial_orientation(grid[r][c]);
        if (init_ori != -1) {
            int current_ori = (init_ori + k)%4;
            
            int nr = r + dr[current_ori];
            int nc = c + dc[current_ori];
            
            if (is_valid(nr, nc)) {
                if (dist[nr][nc][next_k] == -1) {
                    dist[nr][nc][next_k] = next_time;
                    q.push({nr, nc, next_k});
                }
            }
        }
    }
    
    //Un cop el BFS ha acabat, trobem el temps mínim per arribar a 'F'
    int min_time = -1;
    for (int k = 0; k < 4; ++k) {
        int time_k = dist[end_r][end_c][k];
        if (time_k != -1) {
            if (min_time == -1 || time_k < min_time) min_time = time_k;
        }
    }
    
    
    //Imprimeix la sortida
    cout << "#" << case_num << ": ";
    if (min_time == -1) cout << "impossible" << endl;
    else cout << min_time << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) solve(i);
    return 0;
}

Jutge.org
