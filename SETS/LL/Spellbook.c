

/*
Spellbook - ADT Sets

Objective:
Implement an ADT for sets of strings in C to manage a wizard’s spellbook. 
Each spell is a unique string, and the spellbook must support typical set operations.
The implementation is linked list.

Create a C program that defines and uses a Set ADT with the following operations:

    Set* createSet()
        – Initializes an empty set.

    bool addSpell(Set*, const char*)
        – Adds a spell to the set (no duplicates).

    bool removeSpell(Set**, const char*)
        – Removes a spell from the set.

    bool containsSpell(Set*, const char*)
        – Checks if a spell exists in the set.

    void printSet(Set*)
        – Displays all spells in the set.

    void destroySet(Set* set)
        – Frees all memory associated with the set.

    Set* unionSets(Set*, Set*)
        – Returns a new set containing all spells from both sets.

    Set* intersectSets(Set*, Set*)
        – Returns a new set containing only common spells.
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef char String[30];
typedef struct Node {
    String spell;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
}Set;


Set* createSet();
bool addSpell();
void printSet();
Set* unionSets(Set*, Set*);
void destroySet(Set* set);
 Set* intersectSets();
bool removeSpell();





int main() {
    String spell;
    Set* fireSpells = createSet();
    Set* waterSpells = createSet();

	strncpy(spell,"Flame Burst",12);
	spell[11]='\0';
	addSpell(fireSpells, spell);

	strncpy(spell,"Inferno",8);
	spell[7]='\0';
	addSpell(fireSpells, spell);
	// ** CHECK IF IT HANDLES DUPLICATES
	strncpy(spell,"Inferno",8);
	spell[7]='\0';
	addSpell(fireSpells, spell);
	// ** CHECK IF IT HANDLES DUPLCIATES

	strncpy(spell,"Aqua Jet",9);
	spell[8]='\0';
	addSpell(waterSpells, spell);

	strncpy(spell,"Inferno",8);
	spell[7]='\0';
	addSpell(waterSpells, spell);


	// // ** THIS IS MY CHECKING NOT PART OF THE REAL MAIN
	// printf("\nFire Spells\n");
	// printSet(fireSpells);
	// printf("Water Spells\n");
	// printSet(waterSpells);
	// // ** THIS IS MY CHECKING NOT PART OF THE REAL MAIN

	

	Set* commonSpells = intersectSets(fireSpells, waterSpells);
	Set* allSpells = unionSets(fireSpells, waterSpells);

	printf("Common Spells:\n");
	printSet(commonSpells);

	printf("\nAll Spells:\n");
	printSet(allSpells);

	strncpy(spell,"Aqua Jet",9);
	spell[8]='\0';
	removeSpell(&allSpells,spell);

	printf("\nAll Spells:\n");
	printSet(allSpells);

	destroySet(fireSpells);
	destroySet(waterSpells);
	destroySet(commonSpells);
	destroySet(allSpells);

return 0;
}





// Create a new empty set
Set* createSet() {
	Set* newS = malloc(sizeof(Set)); // Todo: It is very important to dynamically allocate, 
	newS->head = NULL; // todo : 	so this pointer SET from main can refer to a real memory that can hold a structure

	newS->size = 0;
	
	return newS;

	
}

// Add a spell to the set (no duplicates)
bool addSpell(Set* set, String spell) {

	bool flag = false;
	Node* temp = (set)->head;
	
	for (; temp != NULL; temp = temp->next) {
		if (strcmp(temp->spell, spell) == 0) {
			flag = true;
			return flag;
		}

		
	}


	if (!flag) {
		Node* new = malloc(sizeof(Node));
		if (!new) {
			return false;
		}
		strcpy(new->spell, spell);
		new->next = (set)->head;
		(set)->head = new;

		set->size++;
		
		return true;
		

	}

}

// Remove a spell from the set
bool removeSpell(Set** set, String spell) {

	Node** temp = &(*set)->head;

	for(; *temp != NULL; temp = &(*temp)->next) {
		if (strcmp((*temp)->spell, spell)==0) {
			Node* toRemove = *temp;
			*temp = (toRemove)->next;
			free(toRemove);
			(*set)->size--;
			return true;

		}
	}
	return false;
		
}


void printSet(Set* set) {
	Node* temp = (*set).head;
	int i = 0;
	while (temp != NULL) {
		
		printf("%d. %s\n", i+1, temp->spell);
		i++;
		temp = temp->next;
	}
	printf("\n");
}

// Free all memory associated with the set
void destroySet(Set* set) {
	Set* temp;

	while (set != NULL) {
		temp = set;
		temp->head = NULL;
		temp->size = 0;
		free(set);
	}
}

Set* unionSets(Set* set1, Set* set2) {

	Set* S = createSet();

	Node* pa = set1->head;
	Node* pb = set2->head;

	while (pa) {
		String data;
		strcpy(data, pa->spell);
		bool inC = false;
		Node* C = (S)->head;

		while (C != NULL) {
			if (C->spell == data) {
				inC = true;
				break;
			}
			C = C->next;
		}

		if (!inC) {
			Node* new = malloc(sizeof(Node));
			strcpy(new->spell, data);
			new->next = S->head;
			S->head = new;
		}
		pa = pa->next;

	}


	while (pb) {
		String data;
		strcpy(data, pb->spell);
		bool inC = false;
		Node* C = (S)->head;

		while (C != NULL) {
			if (strcmp(C->spell, data) ==0) {
				inC = true;
				break;
			}
			C = C->next;
			
		}

		if (!inC) {
			Node* new = malloc(sizeof(Node));
			if (!new) {return NULL;}
			strcpy(new->spell, data);
			new->next = S->head;
			S->head = new;
		}
		pb = pb->next;
	}


	return S;
}


Set* intersectSets(Set* set1, Set* set2) {
		Set* S = createSet();
		
		Node* pa = set1->head;
		

		while (pa) {
			String data;
			strcpy(data, pa->spell);
			Node* pb = set2->head;
			bool inB = false;
			while (pb!= NULL) {
				if (strcmp(pb->spell, data) == 0) {
					inB = true;
					break;
				}
				pb = pb->next;

			}

			if (inB) {
				Node* C = S->head;
				bool inC = false;

				while (C != NULL) {
					if (strcmp(C->spell, data) ==0) {
						inC = true;
						break;
					}
					C = C->next;
				}

				if (!inC) {
					Node* new = malloc(sizeof(Node));
					if (!new) {return NULL;}
					strcpy(new->spell, data);
					new->next = S->head;
					S->head = new;
					}
				}

				pa = pa->next;

			}
			return S;

			
		}



