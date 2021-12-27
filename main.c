#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

char build_graph_cmd(pnode *head, int size);
void add_edges_to_node(pnode *head, pnode *node, int id, char *ch);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
void shortsPath_cmd(pnode head);
void TSP_cmd(pnode head);


int main(){

    char ch = ' ';
    pnode head = NULL;

    while (scanf(" %c", &ch) != EOF)
    {
        
        // A -> build a new Graph
        if(ch == 'A'){
            scanf(" %c",&ch);
            int size = ch - '0';     // size of the graph
            if (head)
            {
                deleteGraph_cmd(&head);
            }
            
            head = (pnode)malloc(sizeof(node));     // allocating memory for the graph's Nodes
            ch = build_graph_cmd(&head, size);  // build graph
        }

        if(ch == 'B'){
            insert_node_cmd(&head);
        }

        if(ch == 'D'){

        }

        if(ch == 'T'){

        }

        if(ch == 'S'){

        }

    }
    


    printGraph_cmd(head);
    deleteGraph_cmd(&head);



}