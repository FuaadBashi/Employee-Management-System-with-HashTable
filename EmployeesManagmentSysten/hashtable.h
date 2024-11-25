#ifndef HASHTABLE
#define HASHTABLE
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



//-------------------------------------------------------


// struct hashtable;
struct hashtable
{
    node* heads[ TABLESIZE ];
    u32 _size;
    u32 (*size) ( hashtable* );

    bool (*insertNode)( hashtable*, employee *e);
    void (*printTable) ( hashtable* );
    
};

u32 idHash(char postion);



void initTable( hashtable *ht);

void freeTable( hashtable *ht );





bool insertNode(hashtable *ht, employee *e);



#endif /* HASHTABLE */
