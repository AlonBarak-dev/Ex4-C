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
pnode allocate_graph(int k);



int main(){
    
    char curr;
    int size;
    
    pnode head = NULL;
    int exit = 0;   // variable that tells whem to program has ended
    
    while(exit != EOF){ // loop until the end of the file has been reached
        
        exit = scanf("%c", &curr);
        
        if (curr == 'A'){
            deleteGraph_cmd(&head);
            scanf("%d", &size);
            head = allocate_graph(size);
        }
        
        if (curr == 'n'){
            build_graph_cmd(&head);
        }
        
        if (curr == 'B'){
            insert_node_cmd(&head);
        }
        
        if (curr =='D'){
            delete_node_cmd(&head);
        }
        
        if (curr =='T'){
            TSP_cmd(head);
        }

        if (curr =='S'){
            shortsPath_cmd(head);
        }
        
    }






    deleteGraph_cmd(&head); // free the graph when done using
    return 0;
}
