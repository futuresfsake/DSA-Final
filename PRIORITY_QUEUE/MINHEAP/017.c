#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define MAX_MESSENGERS 15
#define NAME_LEN 50

/*
    ======================================================
        ELDORIA KINGDOM – ROYAL MESSENGER DISPATCH QUEUE
    ------------------------------------------------------
    Messengers are dispatched based on priority:
        - lower number = higher urgency
    Iterative operations:
        - insertMessenger
        - removeHighestPriority
        - updatePriority
        - searchMessenger
        - displayQueue
    ======================================================
*/

typedef struct {
    int messengerID;
    char messengerName[NAME_LEN];
    int priorityLevel; // 1 = urgent, 10 = routine
} Messenger;

typedef struct {
    Messenger queue[MAX_MESSENGERS];
    int count;
} MessengerQueue;

void initQueue(MessengerQueue *mq);
bool insertMessenger(MessengerQueue *mq, Messenger m);
bool removeHighestPriority(MessengerQueue *mq, Messenger *removed);
int searchMessenger(MessengerQueue *mq, int messengerID);
bool updatePriority(MessengerQueue *mq, int messengerID, int newPriority);
void displayQueue(MessengerQueue *mq);

int main() {
    MessengerQueue mq;
    initQueue(&mq);

    Messenger m1 = {601, "Sir Galen", 5};
    Messenger m2 = {602, "Lady Aria", 2};
    Messenger m3 = {603, "Sir Cedric", 1};
    Messenger m4 = {604, "Lady Elowen", 3};
    Messenger m5 = {605, "Sir Rowan", 4};

    insertMessenger(&mq, m1);
    insertMessenger(&mq, m2);
    insertMessenger(&mq, m3);
    insertMessenger(&mq, m4);
    insertMessenger(&mq, m5);

    printf("\n=== INITIAL MESSENGER QUEUE ===\n");
    displayQueue(&mq);

    printf("\n=== REMOVE HIGHEST PRIORITY MESSENGER ===\n");
    Messenger removed;
    removeHighestPriority(&mq, &removed);
    printf("Removed Messenger: %d (%s) Priority: %d\n",
           removed.messengerID, removed.messengerName, removed.priorityLevel);
    displayQueue(&mq);

    printf("\n=== UPDATE PRIORITY (Messenger 605 -> Priority 1) ===\n");
    updatePriority(&mq, 605, 1);
    displayQueue(&mq);

    printf("\n=== SEARCH FOR Messenger 604 ===\n");
    int idx = searchMessenger(&mq, 604);
    if (idx != -1) {
        printf("Found at index %d: %s Priority %d\n",
               idx, mq.queue[idx].messengerName, mq.queue[idx].priorityLevel);
    } else {
        printf("Messenger not found.\n");
    }

    return 0;
}

void initQueue(MessengerQueue *mq) {
    mq->count = -1;
}

bool insertMessenger(MessengerQueue *mq, Messenger m) {

   int child, pr;
   if (mq->count == MAX_MESSENGERS -1) return false;

   mq->count++;
   child = mq->count;
   pr = (child-1)/2;


   while (child > 0 && mq->queue[pr].priorityLevel > m.priorityLevel) {
    mq->queue[child] = mq->queue[pr];
    child = pr;
    pr = (child-1)/2;
   }

   mq->queue[child] = m;

   return true;
}

bool removeHighestPriority(MessengerQueue *mq, Messenger *removed) {

    int child, pr;

    if (mq->count == -1) return false;

    *removed = (mq->queue[0]);
    mq->queue[0] = mq->queue[mq->count];
    mq->count--;

    pr = 0;
    child = pr * 2 +1;

    while (child <= mq->count) {
        if (child+1 <= mq->count && mq->queue[child+1].priorityLevel < mq->queue[child].priorityLevel) {
            child++;
        }
        if (mq->queue[pr].priorityLevel >mq->queue[child].priorityLevel) {
            Messenger swap = mq->queue[pr];
            mq->queue[pr] = mq->queue[child];
            mq->queue[child] = swap;

            pr = child;
            child = (2*pr)+1;
        } else {
            break;
        }
    }


    return true;


}

int searchMessenger(MessengerQueue *mq, int messengerID) {
    
    for(int i = 0; i <= mq->count; i++) {
        if (mq->queue[i].messengerID == messengerID) {
            return i;
        }
    }
    return -1;
}


bool updatePriority(MessengerQueue *mq, int messengerID, int newPriority) {

    for(int i = 0; i <= mq->count; i++) {
        if (mq->queue[i].messengerID == messengerID) {
            mq->queue[i].priorityLevel = newPriority;


            int child, pr;

            child = i;
            pr = (child-1)/2;
            while (child>0 && mq->queue[pr].priorityLevel > mq->queue[child].priorityLevel) {
                Messenger swap = mq->queue[pr];
                mq->queue[pr]=mq->queue[child];
                mq->queue[child] = swap;

                child = pr;
                pr = (child-1)/2;

                
            }
            return true;
        }
    }
    return false;
}


void displayQueue(MessengerQueue *mq) {
    if (mq->count == -1) {
        printf("[Queue is empty]\n");
        return;
    }

    printf("Index | ID   | Priority | Name\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i <= mq->count; i++) {
        printf("%5d | %-4d | %-8d | %s\n",
               i,
               mq->queue[i].messengerID,
               mq->queue[i].priorityLevel,
               mq->queue[i].messengerName);
    }
}
