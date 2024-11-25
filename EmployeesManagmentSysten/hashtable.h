#ifndef HASHTABLE
#define HASHTABLE

// #define TABLESIZE 16225

/**
 * @file hashtable.h
 
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-08-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#define TABLESIZE 3


#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>


typedef uint32_t u32;
typedef struct employee employee;
typedef struct node node;
typedef struct hashtable hashtable;

struct node;

node* newNode( employee *e );
//-------------------------------------------------------

struct employee;

void initemployee( employee *e);

void freeemployee( employee *e );

// node* getNodeFromName(hashtable ht, char name[]);



//-------------------------------------------------------


// struct hashtable;
struct hashtable
{
    node* heads[ TABLESIZE ];
    u32 _size;
    u32 (*size) ( hashtable* );
    // bool (*contains) ( hashtable*, employee *e );
    bool (*insertNode)( hashtable*, employee *e);
    void (*printTable) ( hashtable* );
    // bool (*removeNode) (hashtable*, employee *e);
    
};

u32 idHash(char postion);

// u32 sum( u32 n );

void initTable( hashtable *ht);

void freeTable( hashtable *ht );



// node* findInChain( node *curr, int val );

bool insertNode(hashtable *ht, employee *e);



#endif /* HASHTABLE */