#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include <float.h>
#include <limits.h>



void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void deleteGraph_cmd(pnode* head);
void shortsPath_cmd(pnode head);
void TSP_cmd(pnode head);
pnode allocate_graph(int size);



int main(){

    char ch;
    int size;
    pnode head = NULL;
    
    while(scanf("%c", &ch) != EOF){

        if (ch == 'A'){
            deleteGraph_cmd(&head);
            scanf("%d", &size);
            head = allocate_graph(size);
        }

        if (ch == 'n'){
            build_graph_cmd(&head);
        }

        if (ch == 'B'){
            insert_node_cmd(&head);
        }

        if (ch =='S'){
            shortsPath_cmd(head);
        }

        if (ch =='D'){
            delete_node_cmd(&head);
        }

        if (ch =='T'){
            TSP_cmd(head);
        }
        
    }
    deleteGraph_cmd(&head);
    return 0;
}
