#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define CLUSTER_CAP 10

// ================== NODE ==================
typedef struct Drone {
    int ip_hash;           // Key
    int cpu_load;          // Data
    struct Drone* link;    // Next Pointer
} Drone;

// ================== TABLE ==================
typedef struct {
    Drone* clusters[CLUSTER_CAP];
} Hive;

// ================== FUNCTION PROTOTYPES ==================
void awaken_hive(Hive* hive);
Drone* ping_drone(Hive* hive, int ip);
void deploy_drone(Hive* hive, int ip, int load);
void migrate_swarm(Hive* hive, int src_index, int dest_index);
int count_cluster_density(Hive* hive, int index);
void kill_switch(Hive* hive);
void filter_drones(Hive* hive, int threshold);
int hash_ip(int ip);
bool delete_dron();

void display_hive(Hive* hive) {
    printf("\n--- Hive Cluster Contents ---\n");
    for (int i = 0; i < CLUSTER_CAP; i++) {
        printf("Cluster %d:", i);
        if (!hive->clusters[i]) {
            printf(" <empty>\n");
            continue;
        }

        Drone* trav = hive->clusters[i];
        while (trav) {
            printf(" [IP:%d CPU:%d]", trav->ip_hash, trav->cpu_load);
            trav = trav->link;
        }
        printf("\n");
    }
    printf("-----------------------------\n");
}


int main() {
    Hive hive;
    awaken_hive(&hive);

    // ----------------- Deploy drones -----------------
    deploy_drone(&hive, 12, 40);
    deploy_drone(&hive, 22, 70);
    deploy_drone(&hive, 32, 20);
    deploy_drone(&hive, 5, 90);
    deploy_drone(&hive, 15, 10);

    // Attempt to deploy duplicate drone
    deploy_drone(&hive, 12, 55); // should not insert

    display_hive(&hive);


    // ----------------- Ping drone -----------------
    int target = 22;
    Drone* found = ping_drone(&hive, target);
    if (found)
        printf("\nPinged drone %d: CPU load = %d\n", target, found->cpu_load);
    else
        printf("\nDrone %d not found.\n", target);

    // Ping non-existent drone
    target = 99;
    found = ping_drone(&hive, target);
    if (found)
        printf("\nPinged drone %d: CPU load = %d\n", target, found->cpu_load);
    else
        printf("\nDrone %d not found.\n", target);

    // ----------------- Delete drone -----------------
    delete_dron(&hive, 32);
    delete_dron(&hive, 99); // not present

    printf("After deleting...\n");

    display_hive(&hive);


   
    // ----------------- Filter drones -----------------
    printf("\nFiltering drones with CPU < 50...\n");
    filter_drones(&hive, 50);
   
        printf("After filtering...\n");

    display_hive(&hive);

    // ----------------- Shutdown -----------------
    kill_switch(&hive);
    printf("\nHive shutdown complete.\n");

    return 0;
}




void awaken_hive(Hive* hive) {
    for(int i = 0; i < CLUSTER_CAP; i++) {
        hive->clusters[i] = NULL;
    }
}

Drone* ping_drone(Hive* hive, int ip) {

    int index =hash_ip(ip);

    Drone* trav = hive->clusters[index];
    while (trav) {
        if (trav->ip_hash == ip) {
            return trav;
        }
        trav = trav->link;
    }
    return NULL;


}

void deploy_drone(Hive* hive, int ip, int load) {
    int index = hash_ip(ip);

    Drone* trav = hive->clusters[index];
    while (trav) {
        if (trav->ip_hash== ip) {
            return;
        }
        trav = trav->link;
    }


    Drone* new = malloc(sizeof(Drone));
    new->cpu_load = load;
    new->ip_hash = ip;
    new->link = hive->clusters[index];
    hive->clusters[index] = new;
}



bool delete_dron(Hive* hive, int ip) {

    int index = hash_ip(ip);
    
    Drone** trav = &hive->clusters[index];

    for(; *trav != NULL ; trav = &(*trav)->link) {
        if ((*trav)->ip_hash == ip) {
            Drone* temp = *trav;
            *trav = temp->link;
            free(temp);
            printf("%d deleted.\n", ip);
            return true;
        }
    }

    return false;
}
void filter_drones(Hive* hive, int threshold) {

    for(int i = 0; i < CLUSTER_CAP; i++) {

        Drone**  trav = &hive->clusters[i];

       while ((*trav) != NULL) {
        if ((*trav)->cpu_load < threshold) {
            Drone* temp = *trav;
            *trav= (*trav)->link;
              printf("%d will be deleted with CPU load of %d ...\n", temp->ip_hash, temp->cpu_load);
                free(temp);
        } else {
            trav = &(*trav)->link;
        }
       }

    }

}

void kill_switch(Hive* hive) {
    for(int i = 0; i < CLUSTER_CAP; i++) {
        Drone* head = hive->clusters[i];

        while (head) {
            Drone* temp = head;
            head = head->link;
            free(temp);
        }
        hive->clusters[i] = NULL;
    }
}

int hash_ip(int ip) {
    return ip % CLUSTER_CAP;
}