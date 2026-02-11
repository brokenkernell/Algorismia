
# -- ARXIU PER SIMULAR N PARTIDES DEL MEU AI CONTRA EL DUMMY --
# CANVIAR "NUM GAMES" PEL VALOR QUE ES VULGUI
# SI ES VOL COMPETIR CONTRA UN ALTRE JUGADOR NOMÉS CAL CANVIAR LA LÍNIA "OPPONENT"

import subprocess
import os
import sys
import random
import glob
import re

# --- CONFIGURACIÓ BÀSICA ---
NUM_GAMES = 100
OPPONENT = "Dummy"
CONFIG_FILE = "default.cnf"
EXECUTABLE = "./Game"
MIN_SEED = 1
MAX_SEED = 1000000

# --- FUNCIÓ DE DETECCIÓ AUTOMÀTICA ---
def detect_player_name():
    # Busquem fitxers que segueixin el patró AI*.cc
    files = glob.glob("AI*.cc")
    candidates = []

    for filename in files:
        try:
            with open(filename, 'r', encoding='utf-8') as f:
                content = f.read()
                # Regex per trobar: #define PLAYER_NAME Algo
                match = re.search(r'#define\s+PLAYER_NAME\s+(\w+)', content)
                if match:
                    name = match.group(1)
                    # Ignorem els jugadors per defecte del professorat
                    if name not in ["Null", "Demo", "Dummy"]:
                        candidates.append(name)
        except Exception as e:
            print(f"Avís: No s'ha pogut llegir {filename}: {e}")

    if not candidates:
        print("Error: No he trobat cap jugador vàlid (diferent de Null/Demo) als fitxers AI*.cc.")
        sys.exit(1)
    
    if len(candidates) > 1:
        print(f"Avís: He trobat múltiples jugadors possibles: {candidates}")
        print(f"Utilitzant el primer: {candidates[0]}")
        return candidates[0]

    # Cas ideal: només n'hi ha un
    return candidates[0]

def run_tournament():
    if not os.path.exists(EXECUTABLE):
        print(f"Error: No trobo l'executable '{EXECUTABLE}'. Has fet 'make all'?")
        sys.exit(1)

    # --- AUTODETECCIÓ ---
    player_name = detect_player_name()
    # --------------------

    print(f"Jugador detectat: \033[1m{player_name}\033[0m")
    print(f"Iniciant torneig ALEATORI: {player_name} vs 3x {OPPONENT}")
    print(f"Generant {NUM_GAMES} llavors úniques...")
    
    seeds = random.sample(range(MIN_SEED, MAX_SEED), NUM_GAMES)

    wins = 0
    total_score = 0

    print("-" * 65)
    print(f"{'PARTIDA':<10} | {'LLAVOR':<10} | {'RESULTAT':<10} | {'PUNTS':<10}")
    print("-" * 65)

    for i, seed in enumerate(seeds, 1):
        
        cmd = [
            EXECUTABLE,
            player_name, OPPONENT, OPPONENT, OPPONENT,
            "-s", str(seed),
            "-i", CONFIG_FILE,
            "-o", "temp_match.res"
        ]

        try:
            result = subprocess.run(cmd, capture_output=True, text=True)
            output = result.stderr
            
            winner_line = ""
            my_score = 0
            
            for line in output.splitlines():
                if "got top score" in line:
                    winner_line = line
                # Busquem la puntuació del jugador detectat
                if f"player {player_name} got score" in line:
                    try:
                        parts = line.split()
                        my_score = int(parts[-1])
                    except:
                        my_score = 0

            total_score += my_score
            
            # Comprovem si el nom del nostre jugador està a la línia de guanyadors
            if player_name in winner_line:
                wins += 1
                status = "GUANYADA"
                color = "\033[92m" # Verd
            else:
                status = "PERDUDA "
                color = "\033[91m" # Vermell
            
            reset = "\033[0m"
            
            print(f"#{i:<9} | {seed:<10} | {color}{status}{reset}   | {my_score}")

        except Exception as e:
            print(f"Error executant la partida {i}: {e}")

    print("-" * 65)
    win_rate = (wins / NUM_GAMES) * 100
    avg_score = total_score / NUM_GAMES
    
    print(f"RESULTAT FINAL ({NUM_GAMES} partides) per a {player_name}:")
    print(f"Victòries: {wins}")
    print(f"Derrotes:  {NUM_GAMES - wins}")
    print(f"Percentatge: \033[1m{win_rate:.2f}%\033[0m")
    print(f"Mitjana Punts: {avg_score:.1f}")

    if os.path.exists("temp_match.res"):
        os.remove("temp_match.res")

if __name__ == "__main__":
    run_tournament()
