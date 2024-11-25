#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "hashtable.h"

typedef struct employee employee;

//---------------------------------------------------------
struct employee {

    char *name;
    char position;
    int id;
    int exp;
    int age;

  
};



void initEmployee( employee *this) {
    employee* e = (employee *) malloc( sizeof(employee) );
    this -> name = NULL;
    this -> position = 'a';
    this -> id = 0;
    this -> exp = 0;
    this -> age = 0;

    
}

void freeEmployee(employee *this){
    free(this);
}


//---------------------------------------------------------


struct node
{
    employee *e;
    node *next;   
};

node* newNode( employee *e ) {
    node* n = (node *) malloc( sizeof(node) );
    char newC = e -> position;
    n -> e = e;
    n -> next = NULL;

    return n;
}

void freeNode( node *this ) {
    free(this);
}

// static node* getNode( hashtable *this, employee *e ) {
//     if (e -> position == 'B'){
//     u32 idx = 0;
//     node *head = this -> heads[idx];
//     return findingInChain( head, 'B' );
//     }
    
// }

// static node* getNodeFromName( hashtable *this, char name[] ) {
//     for (int i = 0; i > TABLESIZE; i++){
//         u32 idx = i;
//         node *head = this -> heads[idx];
//         node* pNode = findingInChainFromName( head, name );
//         if (pNode != NULL){
//             return pNode;
//         }
//     }
//     return NULL;
// }


//---------------------------------------------------------


static node* findingInChain( node *changedNode, employee *e2 ) {

    while ( changedNode != NULL ) {
        if ( changedNode -> e -> name == e2 -> name ) {
            return changedNode;
        } else {
            changedNode = changedNode -> next;
        }      
    }

    return NULL;
}

static node* findingInChainFromName( node *changedNode, char findname[] ) {
    while ( changedNode != NULL ) {
        if ( changedNode -> e -> name == findname ) {
            return changedNode;
        } else {
            changedNode = changedNode -> next;
        }      
    }

    return NULL;
}

// static bool HT_contains( hashtable *this, char c) {
//     return getNode( this, c ) != NULL ;
// }

//---------------------------------------------------------

static bool HT_insertNode( hashtable *this, employee *e ) {
    char position = e -> position;
    if (position == 'B'){
        int idx = 0;
        node *head = this -> heads[idx];
        node *found = findingInChain( head, e );
        if ( found == NULL) {
        node *newHead = newNode( e );
        ++(this -> _size);
        if ( newHead == NULL) {
            return false;
        }

        node *oldHead = head;

        this -> heads[idx] = newHead; // Update bucket head
        newHead -> next  = oldHead; // Update new head to point to old head
        return true;

    } else {
        return false;
    }
    }
    if (position == 'M'){
            int idx = 1;
        node *head = this -> heads[idx];
        node *found = findingInChain( head, e );
        if ( found == NULL) {
        node *newHead = newNode( e );
        ++(this -> _size);
        if ( newHead == NULL) {
            return false;
        }


        node *oldHead = head;

        this -> heads[idx] = newHead; // Update bucket head
        newHead -> next  = oldHead; // Update new head to point to old head
        return true;

    } else {
        return false;
    }
        
    }
    if (position == 'W'){
        int idx = 2;
        node *head = this -> heads[idx];
        node *found = findingInChain( head, e );
        if ( found == NULL) {
        node *newHead = newNode( e );
        ++(this -> _size);
        if ( newHead == NULL) {
            return false;
        }


        node *oldHead = head;

        this -> heads[idx] = newHead; // Update bucket head
        newHead -> next  = oldHead; // Update new head to point to old head
        return true;

    } else {
        return false;
    }
        
    }
    return false;
}

static void HT_printTable( hashtable *ht) {
    for (int idx = 0; idx < TABLESIZE; ++idx) {
        node *curr = ht -> heads[idx];
        printf("%d: ", idx);
        while (curr != NULL) {
            printf("%s -> ", curr -> e -> name );
            curr = curr -> next;
        }
        printf("\n");
    }
}

static u32 HT_size( hashtable *this ) {
    return this -> _size;
}


void initTable(hashtable *this)
{
    for (int idx = 0; idx < TABLESIZE; ++idx) {
        this -> heads[idx] = NULL;
    }

    this -> _size = 0;
    this -> size        = HT_size;
    // this -> contains    = HT_contains; 
    this -> insertNode  = HT_insertNode;
    this -> printTable  = HT_printTable;
    // this -> removeNode  = HT_removeNode;
  
}

void freeTable(hashtable *this) {
    for (int idx = 0; idx < TABLESIZE; ++idx) {
        node *deleteNode = this -> heads[idx];
        node *next;
        while (deleteNode != NULL) {
            next = deleteNode -> next;
            free(deleteNode);
            deleteNode = next;
        }
    }
}
