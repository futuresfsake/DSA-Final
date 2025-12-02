#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TICKER 10

typedef struct Order {
    int order_id;               // Unique ID
    char *ticker;    // "AAPL", "TSLA"
    double bid_amount;          // PRIORITY KEY (Highest wins)
} Order;

typedef struct {
    Order *ledger;              // Dynamic Array
    int active_orders;          // Count
    int buffer_size;            // Capacity
} TradingEngine;

// ======================== PROTOTYPES ========================

/* 1. SETUP: Malloc the array. Set active_orders to 0. */
void init_market(TradingEngine *eng, int capacity);

/* 2. INSERT (SWIM UP):
 * Add new order to end. Swap with parent until Max-Heap rule valid.
 */
void place_bid(TradingEngine *eng, int id, char *tick, double amount);

/* 3. EXTRACT MAX (SINK DOWN):
 * Remove root. Move last item to root. Swap with largest child until valid.
 * Return the removed Order.
 */
Order execute_trade(TradingEngine *eng);

/* 4. ARBITRARY DELETE (The Hard Logic):
 * Find order by ID (Linear search).
 * Replace it with the LAST item in the array.
 * Determine if you need to Swim Up or Sink Down based on the values swapped.
 */
void cancel_order(TradingEngine *eng, int id);

// /* 5. UPDATE KEY (Modify Priority):
//  * Find order by ID. Change its bid_amount.
//  * If new > old -> Swim Up.
//  * If new < old -> Sink Down.
//  */
// void amend_bid(TradingEngine *eng, int id, double new_amount);

/* 6. PEEK: Return root without removing. Return NULL order if empty. */
Order view_top_bid(TradingEngine *eng);

/* 7. LOGIC TEST: MARKET CRASH (Bulk Update).
 * Loop through every order. Decrease bid by percentage.
 * Since relative order might stay same, does the heap break? 
 * (Actually, simple scalar multiplication preserves heap property, but verify it).
 */
void trigger_market_crash(TradingEngine *eng, double percent_drop);

/* 8. HEAPIFY (Build Heap from Scratch).
 * Given an unsorted array of Orders, rearrange them into a valid heap
 * O(n) complexity preferred (Start from last parent node and Sink Down backwards).
 */
void bulk_import_orders(TradingEngine *eng, Order *raw_data, int size);

/* 9. CLEANUP: Free memory. */
void close_market(TradingEngine *eng) {

    for(int i = 0; i <= eng->active_orders; i++) {
        free(eng->ledger[i].ticker);
    }
    free(eng->ledger);
    eng->active_orders = -1;
    eng->buffer_size = -1;
}


void display_market(TradingEngine *eng) {
    if (eng->active_orders == -1) {
        printf("[Market is empty]\n");
        return;
    }

    printf("Index | OrderID | Ticker | BidAmount\n");
    printf("---------------------------------------\n");
    for (int i = 0; i <= eng->active_orders; i++) {
        printf("%5d | %7d | %-6s | %.2f\n",
               i,
               eng->ledger[i].order_id,
               eng->ledger[i].ticker,
               eng->ledger[i].bid_amount);
    }
}


// ======================== MAIN TESTER ========================
int main() {
    TradingEngine wolf_algo;
    init_market(&wolf_algo, 20);

    printf("=== PHASE 1: TRADING OPEN ===\n");
    place_bid(&wolf_algo, 101, "NVDA", 150.00);
    place_bid(&wolf_algo, 102, "AMD", 120.00); // 120 < 150 (Child)
    place_bid(&wolf_algo, 103, "INTC", 200.00); // 200 > 150 (Swim up to Root)
    place_bid(&wolf_algo, 104, "TSM", 180.00);  // 180 > 150 (Swap with old root child)
    place_bid(&wolf_algo, 105, "LBM", 130.00);  // 180 > 150 (Swap with old root child)


    printf("\n=== CURRENT MARKET ===\n");
    display_market(&wolf_algo);


    printf("\nTop Bid: %.2f\n", view_top_bid(&wolf_algo).bid_amount);

  
    // Cancel INTC (200). It's in the middle. Replace with last, then rebalance.
    cancel_order(&wolf_algo, 104);

    printf("\n=== PHASE 3: EXECUTION ===\n");
    Order trade = execute_trade(&wolf_algo); // Should be NVDA (250)
    printf("Sold: %s at %.2f\n", trade.ticker, trade.bid_amount);

    printf("\n=== CURRENT MARKET ===\n");
    display_market(&wolf_algo);


    printf("\n=== PHASE 4: BULK IMPORT (Heapify Logic) ===\n");
    // Resetting for test
    close_market(&wolf_algo); 
    init_market(&wolf_algo, 20);
    
    Order batch[] = {
        {1, "A", 10}, {2, "B", 50}, {3, "C", 20}, {4, "D", 90}, {5, "E", 30}
    };
    // Should turn this random list into a heap without calling place_bid 5 times.
    bulk_import_orders(&wolf_algo, batch, 5); 
    
    printf("Top of Bulk Heap: %.2f\n", view_top_bid(&wolf_algo).bid_amount); // Should be 90

    close_market(&wolf_algo);
    return 0;
}

// ====================== IMPLEMENTATIONS ======================
// TODO: Implement all 9 functions here.

void init_market(TradingEngine *eng, int capacity) {

    eng->ledger = malloc(sizeof(Order)*capacity);
    if (eng->ledger == NULL) return;

    eng->active_orders = -1;
    eng->buffer_size = capacity;

    printf("Successfully initialized!\n");
}

void place_bid(TradingEngine *eng, int id, char *tick, double amount) {

    if (eng->active_orders == eng->buffer_size-1) return;

    int child, pr;

    eng->active_orders++;
    child = eng->active_orders;
    pr = (child-1)/2;


    while (child > 0 && eng->ledger[pr].bid_amount < amount) {
        eng->ledger[child] = eng->ledger[pr];
        child = pr;
        pr = (child-1)/2;
    }


    eng->ledger[child].ticker = malloc(strlen(tick)+1);
    strcpy(eng->ledger[child].ticker, tick);
    eng->ledger[child].bid_amount = amount;
    eng->ledger[child].order_id = id;
}



Order execute_trade(TradingEngine *eng) {
     
    Order empty;
    empty.bid_amount = -1;
    empty.order_id = -1; //! setting the dynamic string into NULL
    
    
    if (eng->active_orders == -1) {
        return empty;}

       

    Order  root;
    int child, pr;



    root = eng->ledger[0];
    eng->ledger[0] = eng->ledger[eng->active_orders];
    eng->active_orders--;

    pr = 0;
    child = 2 * pr +1;

    while (child <= eng->buffer_size) {
        if (child +1 <= eng->buffer_size && eng->ledger[child+1].bid_amount > eng->ledger[child].bid_amount) {
            child++;
        }
        if (eng->ledger[pr].bid_amount < eng->ledger[child].bid_amount) {
            Order swap = eng->ledger[pr];
            eng->ledger[pr] = eng->ledger[child];
            eng->ledger[child] = swap;

            pr = child;
            child = (pr * 2+1);
        } else {
            break;
        }
    }

    return root;

}


Order view_top_bid(TradingEngine *eng) {
    if (eng->buffer_size == -1) {
        Order dummy;
        dummy.bid_amount = -1;
        dummy.order_id = -1;
        return dummy;
    }

    return eng->ledger[0];
}


void cancel_order(TradingEngine *eng, int id) {

    for(int i = 0; i <= eng->buffer_size; i++) {
        if (eng->ledger[i].order_id == id) {



            eng->ledger[i] = eng->ledger[eng->active_orders];
            eng->active_orders--;

           int  pr = i;
           int  child = 2 * pr +1;

            while (child <= eng->buffer_size) {
                if (child+1 <= eng->buffer_size && eng->ledger[child+1].bid_amount > eng->ledger[child].bid_amount) {
                    child++;
                }

                if (eng->ledger[pr].bid_amount < eng->ledger[child].bid_amount) {
                     Order swap = eng->ledger[pr];
            eng->ledger[pr] = eng->ledger[child];
            eng->ledger[child] = swap;

            pr = child;
            child = (pr * 2+1);

                } else {
                    break;
                }
            }

           
        }

        
    }
    
}

void bulk_import_orders(TradingEngine *eng, Order *raw_data, int size) {


    eng->ledger = malloc(sizeof(Order)*size);
    eng->active_orders = -1;
    eng->buffer_size = size;

    for(int i = 0; i < size; i++) {

        if (eng->active_orders == eng->buffer_size-1) {return;}

        eng->active_orders++;
        int child = eng->active_orders;
        int pr = (child-1)/2;

        while (child > 0 && eng->ledger[pr].bid_amount < raw_data[i].bid_amount) {
            eng->ledger[child] = eng->ledger[pr];
            child = pr;
            pr = (child-1)/2;
        }

        eng->ledger[child] = raw_data[i];
    }

}