#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Player {
    char name[30];
    int threat_level;       // PRIORITY KEY (Highest gets attacked)
    int class_id;           // 1=Tank, 2=DPS, 3=Healer
} Player;

typedef struct {
    Player *aggro_list;     // Dynamic Array
    int count;
    int size;
} BossAI;

// ======================== PROTOTYPES ========================

/* 1. INIT. */
void engage_boss(BossAI *ai, int max_players);

/* 2. INSERT (Taunt): Swim Up. */
void player_enters_combat(BossAI *ai, char *name, int threat, int cls);

/* 3. EXTRACT MAX (Tank Buster): Remove root. Sink Down. */
Player perform_tank_buster(BossAI *ai);

/* 4. LOGIC TEST: FADE AGGRO (Update Key).
 * Find player. Reduce threat.
 * Since value Decreased in Max-Heap, SINK DOWN.
 */
void cast_invisibility(BossAI *ai, char *name);

/* 5. LOGIC TEST: SNAP AGGRO (Update Key).
 * Find player. Set threat to (Current_Max_Threat + 1).
 * Read root threat, update target, SWIM UP to root.
 */
void cast_provoke(BossAI *ai, char *name);

/* 6. LOGIC TEST: AOE KNOCKBACK (Global Update).
 * Reduce EVERYONE'S threat by 10%.
 * Does this break the heap property? 
 * (Mathematically no, but iterate through and update everyone).
 */
void global_threat_drop(BossAI *ai);

/* 7. LOGIC TEST: WIPE MECHANIC.
 * Remove ALL players with class_id == 2 (DPS).
 * This is complex: You have to iterate, delete, swap with end, 
 * but be careful because the array shrinks while you loop. 
 * Re-heapifying afterwards might be safer.
 */
void kill_all_dps(BossAI *ai);

/* 8. PEEK. */
Player* get_current_target(BossAI *ai);

/* 9. CLEANUP. */
void boss_defeated(BossAI *ai);


// ======================== MAIN TESTER ========================
int main() {
    BossAI raid;
    engage_boss(&raid, 25);

    printf("=== PHASE 1: COMBAT START ===\n");
    player_enters_combat(&raid, "MainTank", 500, 1);
    player_enters_combat(&raid, "Healer", 100, 3);
    player_enters_combat(&raid, "Rogue", 600, 2); // Stole aggro!
    
    printf("Target: %s (%d)\n", get_current_target(&raid)->name, get_current_target(&raid)->threat_level);

    printf("\n=== PHASE 2: TANK SWAP ===\n");
    // MainTank casts Provoke (Current Max + 1)
    cast_provoke(&raid, "MainTank"); 
    // MainTank should now be 601 and at root.
    printf("Target after Provoke: %s (%d)\n", get_current_target(&raid)->name, get_current_target(&raid)->threat_level);

    printf("\n=== PHASE 3: THREAT REDUCTION ===\n");
    // MainTank uses Invisibility (Logic test: Max Heap Decrease Key -> Sink)
    cast_invisibility(&raid, "MainTank"); 
    // Rogue should be top again.
    printf("Target after Fade: %s\n", get_current_target(&raid)->name);

    printf("\n=== PHASE 4: EXECUTE DPS ===\n");
    kill_all_dps(&raid); // Removes Rogue
    printf("Target after DPS Wipe: %s\n", get_current_target(&raid)->name);

    boss_defeated(&raid);
    return 0;
}

// ====================== IMPLEMENTATIONS ======================
// TODO: Implement all 9 functions.
void engage_boss(BossAI *ai, int max_players) {
    ai->aggro_list = malloc(sizeof(Player)* max_players);
    ai->count = -1;
    ai->size = max_players;
}


void player_enters_combat(BossAI *ai, char *name, int threat, int cls) {

    int child, pr;

    if  (ai->count == ai->size) return;


    ai->count++;
    child = ai->count;
    pr = (child-1)/2;


    while (child > 0 && ai->aggro_list[pr].threat_level < ai->aggro_list[child].threat_level) {
        ai->aggro_list[child] = ai->aggro_list[pr];
        child = pr;
        pr = (child-1)/2;
    }
    strcpy(ai->aggro_list[child].name, name);
    ai->aggro_list[child].threat_level = threat;
    ai->aggro_list[child].class_id = cls;

}

Player perform_tank_buster(BossAI *ai) {

    Player root, swap, empty;
    int child, pr;


    empty.threat_level = -1;
    empty.class_id = -1;

    if (ai->count == ai->size-1) return empty;

    root = ai->aggro_list[0];
    ai->aggro_list[0] = ai->aggro_list[ai->count];
    ai->count--;

    pr = 0;
    child = 2 * pr +1;

    while (child <= ai->count) {
        if (child+1 <= ai->count && ai->aggro_list[child+1].threat_level > ai->aggro_list[child].threat_level) {
            child++;
        }

        if (ai->aggro_list[pr].threat_level < ai->aggro_list[child].threat_level){
            swap = ai->aggro_list[pr];
            ai->aggro_list[pr] = ai->aggro_list[child];
            ai->aggro_list[child] = swap;


            pr = child;
            child = 2 * pr+1;
        } else {
            break;
        }
    }

    return root;
}

void cast_invisibility(BossAI *ai, char *name) {

    for(int i = 0; i <= ai->count; i++) {
        if (strcmp(ai->aggro_list[i].name, name) == 0) {
            ai->aggro_list[i].threat_level-=100; 

            
            int pr = 0;
            int child = 2 * pr +1;


            while (child <= ai->count) {
                if (child +1 <= ai->count && ai->aggro_list[child+1].threat_level>ai->aggro_list[child].threat_level) {
                    child++;
                }

                if (ai->aggro_list[pr].threat_level < ai->aggro_list[child].threat_level) {
                    Player swap = ai->aggro_list[pr];
                    ai->aggro_list[pr] = ai->aggro_list[child];
                    ai->aggro_list[child] = swap;

                    pr = child;
                    child = 2 * pr +1;
                } else {
                    break;
                }
            }
        
        }
    }
}


void global_threat_drop(BossAI *ai) {
    for(int i = 0; i <= ai->count; i++) {
        ai->aggro_list[i].threat_level-=10;
    }
}


void cast_provoke(BossAI *ai, char *name) {
    for(int i = 0; i <= ai->count; i++) {
        if (strcmp(ai->aggro_list[i].name, name) == 0) {
            ai->aggro_list[i].threat_level+=1; 

            int child = i;
            int pr = (child-1)/2;

            while (child > 0 && ai->aggro_list[pr].threat_level < ai->aggro_list[child].threat_level) {
                Player swap = ai->aggro_list[pr];
                ai->aggro_list[pr] = ai->aggro_list[child];
                ai->aggro_list[child] = swap;

                child = pr;
                pr = (child-1)/2;
            }
        
        }
    }
}

void kill_all_dps(BossAI *ai) {


    for(int i = 0; i <= ai->count; i++) {
        if (ai->aggro_list[i].class_id == 2) {

            ai->aggro_list[i] = ai->aggro_list[ai->count];
            ai->count--;

            int pr = 0;
            int child = (2 * pr +1);



            while (child <= ai->count) {
                if (child +1 <= ai->count && ai->aggro_list[child+1].threat_level>ai->aggro_list[child].threat_level) {
                    child++;
                }

                if (ai->aggro_list[pr].threat_level < ai->aggro_list[child].threat_level) {
                    Player swap = ai->aggro_list[pr];
                    ai->aggro_list[pr] = ai->aggro_list[child];
                    ai->aggro_list[child] = swap;

                    pr = child;
                    child = 2 * pr +1;
                } else {
                    break;
                }
            }

        }
    }

}

Player* get_current_target(BossAI *ai) {
    return &ai->aggro_list[0];
}

void boss_defeated(BossAI *ai) {
    free(ai->aggro_list);
    ai->count = -1;
    ai->size = -1;
}

