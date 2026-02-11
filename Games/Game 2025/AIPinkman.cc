#include "Player.hh"
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <cmath>
#include <functional>

#define PLAYER_NAME Pinkman

struct PLAYER_NAME : public Player {

  static Player* factory () {
    return new PLAYER_NAME;
  }

  const vector<Dir> dirs = {Up, Down, Left, Right};
  
  // =========================================================
  // MOTOR MATEMÀTIC (BACKTRACKING)
  // =========================================================
  map<vector<int>, vector<int>> solution_cache;
  vector<pair<int,int>> _working_hints;
  vector<bool> _used;
  vector<int> _current_sol;
  int _N;

  inline bool is_valid_triplet(int a, int b, int c) {
      return (a + b == c) || (a + c == b) || (b + c == a);
  }

  bool solve_recursive(int triplet_id) {
      if (triplet_id == _N) return true;
      int i = 0;
      while (i < (int)_working_hints.size() && _used[i]) i++;
      if (i == (int)_working_hints.size()) return false;
      
      _used[i] = true;
      for (int j = i + 1; j < (int)_working_hints.size(); ++j) {
          if (_used[j]) continue;
          _used[j] = true;
          for (int k = j + 1; k < (int)_working_hints.size(); ++k) {
              if (_used[k]) continue;
              
              if (is_valid_triplet(_working_hints[i].first, _working_hints[j].first, _working_hints[k].first)) {
                  _used[k] = true;
                  int idx_i = _working_hints[i].second;
                  int idx_j = _working_hints[j].second;
                  int idx_k = _working_hints[k].second;
                  
                  _current_sol[idx_i] = triplet_id;
                  _current_sol[idx_j] = triplet_id;
                  _current_sol[idx_k] = triplet_id;
                  
                  if (solve_recursive(triplet_id + 1)) return true;
                  _used[k] = false;
              }
          }
          _used[j] = false;
      }
      _used[i] = false;
      return false;
  }

  vector<int> get_safety_box_solution(const vector<int>& hints) {
      if (hints.empty()) return {};
      _N = hints.size() / 3;
      _current_sol = vector<int>(hints.size(), 0);
      _used = vector<bool>(hints.size(), false);
      _working_hints.clear();
      for (int i = 0; i < (int)hints.size(); ++i) _working_hints.push_back({hints[i], i});
      
      // Ordenem per optimitzar la cerca
      sort(_working_hints.begin(), _working_hints.end());
      
      if (solve_recursive(0)) return _current_sol;
      return {};
  }

  // =========================================================
  // AVALUACIÓ DE RISC
  // =========================================================

  // Detecta si una posició és adjacent a un soldat enemic armat amb verí
  bool is_extremely_dangerous(Pos p) {
      for (int pl = 0; pl < num_players(); ++pl) {
          if (pl == me()) continue;
          const vector<int>& enemies = soldiers(pl);
          for (int id : enemies) {
              Unit u = unit(id);
              if (u.poison > 0) {
                  int dist = abs(p.i - u.pos.i) + abs(p.j - u.pos.j);
                  if (dist <= 2) return true;
              }
          }
      }
      return false;
  }

  // Detecta carrerons sense sortida (per evitar quedar atrapats)
  bool is_dead_end(Pos p) {
      int walls = 0;
      for (Dir d : dirs) {
          Pos n = p + d;
          if (!pos_ok(n) || cell(n).type == Wall) walls++;
      }
      return walls >= 3;
  }

  // =========================================================
  // MOTOR DE NAVEGACIÓ AVANÇAT (COSTOS)
  // =========================================================
  
  struct Node {
      Pos p;
      int cost;
      Dir first_move;
      
      // Prioritat inversa: volem el cost mínim al capdamunt
      bool operator>(const Node& other) const {
          return cost > other.cost;
      }
  };

  // Cerca el millor camí ponderant riscos i beneficis
  // incentive_money: Si true, descompta cost si hi ha diners pel camí
  pair<Dir, bool> find_best_path(Pos origin, const function<bool(Pos)>& goal_checker, int max_cost, bool incentive_money) {
      priority_queue<Node, vector<Node>, greater<Node>> pq;
      vector<vector<int>> min_cost(board_rows(), vector<int>(board_cols(), 1e9));

      min_cost[origin.i][origin.j] = 0;
      
      // Randomització
      vector<Dir> start_dirs = dirs;
      for (int i = 0; i < (int)start_dirs.size(); ++i) {
          int r = random(0, start_dirs.size() - 1);
          swap(start_dirs[i], start_dirs[r]);
      }

      // Expansió inicial
      for (Dir d : start_dirs) {
          Pos neighbor = origin + d;
          if (pos_ok(neighbor) && cell(neighbor).type != Wall && cell(neighbor).id == -1) {
              int move_cost = 10;
              
              if (is_extremely_dangerous(neighbor)) move_cost += 500;
              if (incentive_money && cell(neighbor).money > 0) move_cost -= 5;

              if (goal_checker(neighbor)) return {d, true};

              if (move_cost < max_cost) {
                  min_cost[neighbor.i][neighbor.j] = move_cost;
                  pq.push({neighbor, move_cost, d});
              }
          }
      }

      while (!pq.empty()) {
          Node current = pq.top();
          pq.pop();

          if (current.cost > min_cost[current.p.i][current.p.j]) continue;
          if (current.cost >= max_cost) continue;

          for (Dir d : dirs) {
              Pos next_p = current.p + d;

              if (pos_ok(next_p) && cell(next_p).type != Wall && cell(next_p).id == -1) {
                  
                  int step_cost = 10;
                  
                  // Ajust de pesos tàctic
                  if (incentive_money && cell(next_p).money > 0) step_cost -= 4;
                  if (is_extremely_dangerous(next_p)) step_cost += 500;
                  if (is_dead_end(next_p)) step_cost += 50;

                  int new_total_cost = current.cost + step_cost;

                  if (new_total_cost < min_cost[next_p.i][next_p.j]) {
                      min_cost[next_p.i][next_p.j] = new_total_cost;
                      
                      if (goal_checker(next_p)) {
                          return {current.first_move, true};
                      }
                      
                      pq.push({next_p, new_total_cost, current.first_move});
                  }
              }
          }
      }
      return {Up, false};
  }

  // =========================================================
  // LÒGICA DE JOC PRINCIPAL
  // =========================================================

  void play_professor(int id) {
      Unit p = unit(id);
      
      // Accions immediates (adjacents)
      for (Dir d : dirs) {
          Pos adj = p.pos + d;
          if (!pos_ok(adj)) continue;
          
          // 1. Obrir caixa forta
          if (cell(adj).box != -1) {
             auto sol = get_safety_box_solution(safety_box_hints(cell(adj).box));
             if (!sol.empty()) { open(id, sol, d); return; }
          }
          // 2. Agafar kits per denegar-los al rival
          if (cell(adj).health_kit && cell(adj).id == -1) { move(id, d); return; }
      }

      // Estratègia 1: Supervivència
      if (p.health < professor_max_health() / 2) {
          auto res = find_best_path(p.pos, [&](Pos x){ return cell(x).health_kit; }, 400, false);
          if (res.second) { move(id, res.first); return; }
      }

      // Estratègia 2: Cerca de Caixes amb Oportunisme (Diners pel camí)
      auto res_box = find_best_path(p.pos, [&](Pos x){
          for(Dir d:dirs) {
              Pos a = x+d;
              if(pos_ok(a) && cell(a).box != -1) return true;
          }
          return false;
      }, 600, true);

      if (res_box.second) {
          move(id, res_box.first);
          return;
      }

      // Estratègia 3: Recol·lecció de diners (Fallback)
      auto res_money = find_best_path(p.pos, [&](Pos x){ return cell(x).money > 0; }, 300, true);
      if (res_money.second) {
           move(id, res_money.first);
           return;
      }
      
      // Moviment Aleatori Segur
      int r = random(0,3);
      for(int i=0;i<4;++i) {
           Dir d = dirs[(r+i)%4];
           Pos np = p.pos + d;
           if(pos_ok(np) && cell(np).type!=Wall && cell(np).id==-1 && !is_extremely_dangerous(np)) {
               move(id, d);
               return;
           }
      }
  }

  void play_soldier(int id) {
      Unit s = unit(id);
      
      // 1. Logística (Recàrrega necessària)
      if (s.poison == 0) {
          if (available_poison(me()) > 0) { charge(id); return; }
          auto res = find_best_path(s.pos, [&](Pos x){ return cell(x).poison_kit; }, 300, false);
          if (res.second) { move(id, res.first); return; }
      }

      // 2. Combat Immediat
      if (s.poison > 0) {
          for (Dir d : dirs) {
              Pos t = s.pos + d;
              if (pos_ok(t)) {
                  int eid = cell(t).id;
                  if (eid != -1 && unit(eid).player != me()) {
                      move(id, d); return;
                  }
              }
          }
      }

      // 3. Caça de Professors
      if (s.poison > 0) {
          auto res_hunt = find_best_path(s.pos, [&](Pos x) {
              for (Dir d : dirs) {
                  Pos adj = x + d;
                  if (pos_ok(adj)) {
                      int uid = cell(adj).id;
                      if (uid != -1) {
                          Unit v = unit(uid);
                          if (v.type == Professor && v.player != me()) return true;
                      }
                  }
              }
              return false;
          }, 300, false);

          if (res_hunt.second) {
              move(id, res_hunt.first);
              return;
          }
      }

      // 4. Recol·lecció Secundària
      auto res_money = find_best_path(s.pos, [&](Pos x){ return cell(x).money > 0; }, 200, true);
      if (res_money.second) {
          move(id, res_money.first);
          return;
      }

      // Moviment Aleatori
       int r = random(0,3);
      for(int i=0;i<4;++i) {
           Dir d = dirs[(r+i)%4];
           Pos np = s.pos + d;
           if(pos_ok(np) && cell(np).type!=Wall && cell(np).id==-1) { move(id, d); return;}
      }
  }

  virtual void play () {
      int my_prof = professor(me());
      if (my_prof != -1) play_professor(my_prof);

      vector<int> my_soldiers = soldiers(me());
      for (int id : my_soldiers) play_soldier(id);
  }
};

RegisterPlayer(PLAYER_NAME);
