#include <stdio.h>
#include <string.h>

#define CLUSTER_SIZE 10

// --- Struct Definitions ---
typedef struct {
    char ip_address[16];
    char region[10];
} ServerConfig;

typedef struct {
    int cpu_load; // Priority: Lower load = Higher priority for new jobs
    int ram_usage;
    ServerConfig config;
} ServerNode;

typedef struct {
    ServerNode cluster[CLUSTER_SIZE];
    int active_servers;
} LoadBalancer;

// --- Prototypes ---
void initBalancer(LoadBalancer* lb);
void registerServer(LoadBalancer* lb, int load, char* ip, char* region);
ServerNode assignJob(LoadBalancer* lb); // ExtractMin (Get least loaded)
void siftUp(LoadBalancer* lb, int idx);
void siftDown(LoadBalancer* lb, int idx);

int main() {
    LoadBalancer cloud;
    initBalancer(&cloud);

    printf("=== Server Load Balancer (MinHeap) ===\n");

    // Servers reporting their status
    registerServer(&cloud, 80, "192.168.1.1", "US-East");
    registerServer(&cloud, 15, "192.168.1.2", "US-West"); // Least loaded
    registerServer(&cloud, 45, "192.168.1.3", "EU-Cent");
    registerServer(&cloud, 99, "192.168.1.4", "AP-South");

    printf("Assigning incoming jobs to servers:\n");

    // Should pick 15% first, then 45%, etc.
    while(cloud.active_servers > 0) {
        ServerNode target = assignJob(&cloud);
        printf("Job assigned to %s (Load: %d%%) in %s\n", 
            target.config.ip_address, target.cpu_load, target.config.region);
    }

    return 0;
}

// --- IMPLEMENT LOGIC BELOW ---

void initBalancer(LoadBalancer* lb) {

    lb->active_servers = -1;


}

void registerServer(LoadBalancer* lb, int load, char* ip, char* region) {
    // TODO: Insert node, siftUp (MinHeap property)

    int child, pr;

    if (lb->active_servers == CLUSTER_SIZE-1) return;

    lb->active_servers++;
    child = lb->active_servers;
    pr = (child-1)/2;


    while (child > 0 && lb->cluster[pr].cpu_load > lb->cluster[child].cpu_load) {
        lb->cluster[child] = lb->cluster[pr];
        child = pr;
        pr = (child-1)/2;
    }

    
    lb->cluster[child].cpu_load = load;
    strcpy(lb->cluster[child].config.ip_address, ip);
    strcpy(lb->cluster[child].config.region, region);
}

ServerNode assignJob(LoadBalancer* lb) {
    // TODO: Extract root (min load), replace with last, siftDown
    ServerNode dummy = {0};
    
    if (lb->active_servers == -1) return dummy;


    ServerNode root, swap;
    int child, pr;


    root = lb->cluster[0];
    lb->cluster[0] = lb->cluster[lb->active_servers];
    lb->active_servers--;

    pr = 0;
    child = 2 * pr +1;


    while (child <= lb->active_servers) {
        if (child+1 <= lb->active_servers && lb->cluster[child+1].cpu_load < lb->cluster[child].cpu_load) {
            child++;
        }

        if (lb->cluster[pr].cpu_load > lb->cluster[child].cpu_load) {
            swap = lb->cluster[pr];
            lb->cluster[pr] = lb->cluster[child];
            lb->cluster[child] = swap;
        } else {
            break;
        }
    }

    return root;
}

