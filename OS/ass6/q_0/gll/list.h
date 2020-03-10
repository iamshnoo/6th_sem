#ifndef LIST_H
#define LIST_H

#include<stdlib.h>
#include<string.h>
#include<stdio.h>
/* ....Diagrammatic representation of the structures involved.....

             g             <<------(gll1)
        ------------
        |   dsize  |
        |   (int)  |
        ------------
        | compareFn|
        |  (_,_)   |
        ------------
        |  list    |                    node1
        | (g->list)|------------>>>>>>----------
        ------------                  |  data  |
         genericLL                    |   ()   |
                                      ----------
                                      |  next  |                     node2
                                      |        |------------>>>>>>-----------
                                      ----------                  |  data   |
                                                                  |   ()    |
                                        node                      -----------
                                                                  |   NULL  |
                                                                  |         |
                                                                  -----------

                                                                    node
*/

typedef struct Node
{
    //Points to an array of dsize bytes.
    void *data;

    //Points to the next node.
    struct Node * next;
}node;

/*
Can take data of 2 nodes of this list as parameters and compare them.
Returns 0 if data1 and data2 are "same",-1 if data1 is "less than" data2
and 1 if data1 is "greater than" data2.
*/

typedef struct genericLL
{
    int dsize; //For storing the size (number of  bytes) of data that each node of this linked will have.

    //Pointer to function compareFn().
    //required to compare data of 2 nodes of a linked list for the purpose of ordering them.
    int (*compareFn)(void*,void*);

    node *list; //"list" points to the first node of the list.

}genericLL;

int intCompare(void* ,void* );
int stringCompare(void* ,void* );
int floatCompare(void*, void* );
genericLL* createGLL(int, int (*cfunction)(void *, void *));
void addNodeGLL(genericLL*, void* );
void addNodeGLLSorted(genericLL* , void* );
int isPresentGLL(genericLL* , void* );
int deleteNodeGLL(genericLL* , void*);
int getNodeDataGLL(genericLL* , int , void* );
void printLL_char(genericLL* );
void printLL_int(genericLL* );
void printLL_float(genericLL* );
void printLL_string(genericLL* );

#endif