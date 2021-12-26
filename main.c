#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void build_graph_cmd(pnode head, int size);
char add_edges_to_node(pnode head, int id);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
void shortsPath_cmd(pnode head);
void TSP_cmd(pnode head);


int main(){

    char ch;
    pnode head;

    while (scanf(" %c", &ch) != EOF)
    {

        // A -> build a new Graph
        if(ch == 'A'){
            scanf(" %c",&ch);
            int size = ch - '0';     // size of the graph
            head = (pnode)malloc(sizeof(node));     // allocating memory for the graph's Nodes
            build_graph_cmd(head, size);  // build graph
        }

    }
    


    printGraph_cmd(head);




}