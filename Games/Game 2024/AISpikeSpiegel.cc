#include "Player.hh"
#include <queue>
#include <algorithm>
#include <cmath>

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME SpikeSpiegel


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
    const vector<Dir> dirs = {Up, Down, Left, Right};
    
    //Funció per calcular la dist entre dues posicions
    int manhattan_distance (const Pos& a, const Pos& b) {
        return abs(a.i - b.i) + abs(a.j - b.j);
    }
    /**
     * Funció auxiliar: calcula la probabilitat de guanyar un atac.
     */
    double calculate_win_probability(int my_strength, int enemy_strength, bool surprise = false) {
        if (surprise) return 0.3; // 30% de probabilitat d'atac sorpresa
        if (my_strength + enemy_strength == 0) return 0.5; // Igual probabilitat si tots dos són iguals i 0
        return double(my_strength) / (my_strength + enemy_strength);
    }
    
    /**
     * Funció auxiliar: comprova si un atac és favorable.
     */
    bool should_attack(int my_id, int enemy_id) {
      Unit my_unit = unit(my_id);
      Unit enemy = unit(enemy_id);

      // Només ataquem mags enemics o fantasmes enemics
      if (enemy.player == me() || (enemy.type != Wizard && enemy.type != Ghost)) return false;

      int my_strength = magic_strength(me());
      int enemy_strength = magic_strength(enemy.player);

      // Calculem la probabilitat de guanyar
      double win_prob = calculate_win_probability(my_strength, enemy_strength, /*surprise=*/false);

      // Si és un mag en procés de conversió, tenim avantatge addicional
      if (enemy.type == Wizard && enemy.rounds_pending > 0) win_prob += 0.2;

      // Atacar només si la probabilitat és favorable (> 50%)
      return win_prob > 0.5;
    }
    
    /**
     * Funció auxiliar: prioritza enemics per probabilitat de guanyar.
     */
    vector<int> prioritize_enemies(const Pos& p) {
      vector<pair<double, int>> enemy_list; // Probabilitat i id de l'enemic

      for (Dir d : dirs) {
        Pos new_pos = p + d;
        if (pos_ok(new_pos)) {
          int enemy_id = cell(new_pos.i, new_pos.j).id;
          if (enemy_id != -1 && unit(enemy_id).player != me()) {
            int my_strength = magic_strength(me());
            int enemy_strength = magic_strength(unit(enemy_id).player);
            double win_prob = calculate_win_probability(my_strength, enemy_strength);
            enemy_list.push_back({win_prob, enemy_id});
          }
        }
      }

      // Ordenem els enemics per probabilitat de guanyar (descendent)
      sort(enemy_list.begin(), enemy_list.end(), greater<pair<double, int>>());

      // Retornem només els ids dels enemics
      vector<int> sorted_ids;
      for (auto& [prob, id] : enemy_list) {
        sorted_ids.push_back(id);
      }
      return sorted_ids;
    }

    /**
     * Algoritme A*: calcula el camí més curt fins a un objectiu.
     */
    Dir a_star(const Pos& start, const Pos& target) {
      if (start == target) return Down; // No cal moure's si ja som a l'objectiu

      // Nodes per explorar
      priority_queue<pair<int, Pos>, vector<pair<int, Pos>>, greater<pair<int, Pos>>> pq;
      map<Pos, int> dist;  // Cost acumulat fins a cada node
      map<Pos, Pos> prev;  // Traçabilitat per reconstruir el camí

      pq.push({0, start});
      dist[start] = 0;

      while (!pq.empty()) {
        auto [current_cost, current] = pq.top();
        pq.pop();

        // Si arribem al destí, reconstruïm el camí
        if (current == target) {
          Pos p = target;
          while (prev[p] != start) p = prev[p];
          for (Dir d : dirs) if (start + d == p) return d; // Retorna la direcció inicial
        }

        // Explorem els veïns
        for (Dir d : dirs) {
          Pos new_pos = current + d;
          if (pos_ok(new_pos) && cell(new_pos).type != Wall) {
            int new_cost = current_cost + 1;
            if (!dist.count(new_pos) || new_cost < dist[new_pos]) {
              dist[new_pos] = new_cost;
              prev[new_pos] = current;
              pq.push({new_cost + manhattan_distance(new_pos, target), new_pos}); // Cost + heurística
            }
          }
        }
      }
      return Down; // Direcció per defecte si no trobem cap camí
    }
    
    /**
     * Funció auxiliar: trobar l'objectiu prioritari (llibre, cel·la neutra, bloqueig enemic).
     */
    pair<Pos, string> find_priority_target(const Pos& p) {
      queue<Pos> q;
      map<Pos, int> dist;
      q.push(p);
      dist[p] = 0;

      while (!q.empty()) {
        Pos current = q.front();
        q.pop();

        // Prioritat 1: Llibres
        if (cell(current).book) return {current, "book"};

        // Prioritat 2: Cel·les neutres
        if (cell(current).owner == -1) return {current, "cell"};

        // Prioritat 3: Bloquejar enemics
        int id_in_cell = cell(current).id;
        if (id_in_cell != -1 && unit(id_in_cell).player != me()) {
          return {current, "block"};
        }

        // Afegir veïns a la cua
        for (Dir d : dirs) {
          Pos new_pos = current + d;
          if (pos_ok(new_pos) && dist.find(new_pos) == dist.end() && cell(new_pos).type != Wall) {
            q.push(new_pos);
            dist[new_pos] = dist[current] + 1;
          }
        }
      }
      return {p, "none"}; // Si no hi ha cap objectiu
    }
    
    /**
     * Exploració activa: moviment en cercles concèntrics.
     */
    Dir explore(const Pos& p) {
      for (Dir d : dirs) {
        Pos new_pos = p + d;
        if (pos_ok(new_pos) && cell(new_pos).type != Wall && cell(new_pos).owner != me()) {
          return d; // Mou-te cap a una nova cel·la
        }
      }
      return Down; // Direcció per defecte
    }

    /**
      * Moviments intel·ligents per mags i fantasmes, incloent atacs.
      */
     void move_unit(int id) {
       Pos p = unit(id).pos;

       // Evitar Voldemort si està a prop
       if (voldemort_is_near(p)) {
         Dir safe_dir = find_safe_direction(p);
         move(id, safe_dir);
         return;
       }

       // Buscar enemics adjacents
       vector<int> enemies = prioritize_enemies(p);

       for (int enemy_id : enemies) {
         if (should_attack(id, enemy_id)) {
           // Si l'atac és favorable, moure's cap a l'enemic
           for (Dir d : dirs) {
             if (p + d == unit(enemy_id).pos) {
               move(id, d);
               return;
             }
           }
         }
       }

       // Si no hi ha cap atac favorable, buscar altres objectius (llibres, cel·les)
       auto [target, type] = find_priority_target(p);
       if (target != p) {
         Dir best_dir = a_star(p, target);
         move(id, best_dir);
         return;
       }

       // Exploració activa si no hi ha cap objectiu
       Dir explore_dir = explore(p);
       move(id, explore_dir);
     }
    
    //Funció per moure el fantasma
    void move_ghost (int id) {
        Pos ghost_pos = unit(id).pos;

        //Capture areas with books
        Pos book_target = find_nearest_book(ghost_pos);
        if (book_target != ghost_pos) {
          Dir move_dir = Down; // Default no movement
          for (auto d : dirs) {
            if (ghost_pos + d == book_target) {
              move_dir = d;
              break;
            }
          }
        move(id, move_dir);
        return; // Ghost action completed
        }

        //Block enemy wizards
        vector<int> enemies = nearby_enemy_wizards(ghost_pos);
        if (!enemies.empty()) {
          for (int enemy_id : enemies) {
            Pos enemy_pos = unit(enemy_id).pos;
            for (auto d : dirs) {
              Pos block_pos = ghost_pos + d;
              if (block_pos == enemy_pos && pos_ok(block_pos)) {
                move(id, d); // Block enemy wizard
                return; // Ghost action completed
              }
            }
          }
        }

        //Default: Random movement for exploration
        for (auto d : dirs) {
          Pos new_pos = ghost_pos + d;
          if (pos_ok(new_pos) && cell(new_pos.i, new_pos.j).type != Wall) {
            move(id, d);
            return; // Ghost action completed
          }
        }
      }
    
    /**
     * Funció per evitar Voldemort.
     */
    bool voldemort_is_near(const Pos& p) {
      Pos voldemort_pos = pos_voldemort();
      return manhattan_distance(p, voldemort_pos) <= 1; // Adjacent
    }
    
    /**
       * Buscar una direcció segura per evitar Voldemort.
       */
      Dir find_safe_direction(const Pos& p) {
        for (Dir d : dirs) {
          Pos new_pos = p + d;
          if (pos_ok(new_pos) && !voldemort_is_near(new_pos) && cell(new_pos).type != Wall) {
            return d;
          }
        }
        return Down; // Per defecte
      }
    
    //Algoritme per trobar llibres
    Pos find_nearest_book(const Pos& start) {
        queue<Pos> q;
        map<Pos, int> dist;
        q.push(start);
        dist[start] = 0;
        while (!q.empty()) {
            Pos p = q.front(); q.pop();
            if (cell(p).book) return p;
            
            for (Dir d : dirs) {
                Pos new_pos = p+d;
                if (pos_ok(new_pos) and dist.find(new_pos) == dist.end() and cell(new_pos).type != Wall) {
                    q.push(new_pos);
                    dist[new_pos] = dist[p] + 1;
                }
            }
        }
        return start; //Si no hi ha cap llibre
    }
    
    // Find enemy wizards near the ghost
    vector<int> nearby_enemy_wizards(Pos ghost_pos) {
      vector<int> enemy_wizards;
      for (auto d : dirs) {
        Pos adj = ghost_pos + d;
        if (pos_ok(adj)) {
          int id = cell(adj.i, adj.j).id;
          if (id != -1 && unit(id).type == Wizard && unit(id).player != me()) {
            enemy_wizards.push_back(id);
          }
        }
      }
      return enemy_wizards;
    }
    
    //Algoritme per resoldre encanteris
    vector<int> solve_spell (const vector<int>& ingredients) {
        int sum = accumulate(ingredients.begin(), ingredients.end(), 0);
        int target = sum/5; //Suposem 5 grups
        vector<int> assignment(ingredients.size(), 0);
        vector<int> group_sums(5, 0);
        
        function<bool(int)> backtrack = [&](int i) {
            if (i == ingredients.size()) return true;
            for (int g = 0; g < 5; ++g) {
                if (group_sums[g] + ingredients[i] <= target) {
                    group_sums[g] += ingredients[i];
                    assignment[i] = g;
                    if (backtrack(i+1)) return true;
                    group_sums[g] -= ingredients[i];
                }
            }
            return false;
        };
        backtrack(0);
        return assignment;
    }
    
    // Calculate the number of neutral cells in the area affected by a spell
    int count_neutral_cells_in_spell_area(Pos center, int radius) {
      int count = 0;
      for (int i = -radius; i <= radius; ++i) {
        for (int j = -radius; j <= radius; ++j) {
          Pos p = center + Pos(i, j);
          if (pos_ok(p)) {
            if (cell(p.i, p.j).owner == -1) { // Neutral cell
              count++;
            }
          }
        }
      }
      return count;
    }
    
    // Decide if it's worth casting a spell at a given position
     bool should_cast_spell(Pos center, int radius) {
       // Threshold: Cast spell only if we can capture at least 5 neutral cells
       int neutral_cells = count_neutral_cells_in_spell_area(center, radius);
       return neutral_cells >= 5; // Adjust this threshold as needed
     }
    
    // Find the best position to cast a spell
      Pos find_best_spell_position(int radius) {
        Pos best_pos = {-1, -1}; // Default to an invalid position
        int max_neutral_cells = 0;

        for (int i = 0; i < board_rows(); ++i) {
          for (int j = 0; j < board_cols(); ++j) {
            Pos p = {i, j};
            if (cell(p.i, p.j).owner == me()) { // We can only cast spells from owned cells
              int neutral_cells = count_neutral_cells_in_spell_area(p, radius);
              if (neutral_cells > max_neutral_cells) {
                max_neutral_cells = neutral_cells;
                best_pos = p;
              }
            }
          }
        }
        return best_pos;
      }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
      if (status(me()) >= 0.9) return;
      
      // Handle spells
      /*int radius = 3; // Assume spell affects a 7x7 area (radius = 3)
      if (can_spell(me())) { // Check if we can cast a spell
        Pos best_pos = find_best_spell_position(radius);
        if (best_pos.i != -1 && should_cast_spell(best_pos, radius)) {
          cast_spell(best_pos); // Cast the spell at the best position
          return; // Spell action completed
        }
      }*/
      
      for (int id : wizards(me())) move_unit(id);
      
      int g = ghost(me());
      move_ghost(g);
      
      vector<int> ingredients = spell_ingredients();
      
      if (!ingredients.empty()) {
          vector<int> solution = solve_spell(ingredients);
          spell(g, solution);
      }
  }
};

/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
