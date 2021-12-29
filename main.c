#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void build_graph_cmd(pnode *head, int size, char *ch);
void add_edges_to_node(pnode *head, pnode *node, int id, char *ch);
void insert_node_cmd(pnode *head, char *ch);
void delete_node_cmd(pnode *head, char *ch);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
void shortsPath_cmd(pnode head, char *ch);
void TSP_cmd(pnode head, char *ch);


int main(){

    char ch = ' '; 
    pnode head = NULL;

    while (1)
    {
        if (((ch != 'A') && (ch != 'B') && (ch != 'D') && (ch != 'S') && (ch != 'T')) /*|| (ch ==  'z')*/ )
        {
            // if (ch == 'z')
            // {
            //     break;
            // }
            // scanf(" %c", &ch);
            // if (ch == 'z')
            // {
            //     break;
            // }
            if (scanf(" %c", &ch) == EOF)
            {
                break;
            }
            
        }
        
        
        // A -> build a new Graph
        if(ch == 'A'){
            scanf(" %c",&ch);
            int size = ch - '0';     // size of the graph
            if (head)
            {
                printGraph_cmd(head);
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                deleteGraph_cmd(&head);
            }
            
            head = (pnode)malloc(sizeof(node));     // allocating memory for the graph's Nodes
            build_graph_cmd(&head, size, &ch);  // build graph
        }

        if(ch == 'B'){
            printGraph_cmd(head);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            insert_node_cmd(&head, &ch);
        }

        if(ch == 'D'){
            printGraph_cmd(head);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            delete_node_cmd(&head, &ch);
        }

        if(ch == 'T'){
            TSP_cmd(head, &ch);
        }

        if(ch == 'S'){
            shortsPath_cmd(head, &ch);
        }

    }
    


    printGraph_cmd(head);
    deleteGraph_cmd(&head);

    return 0;

}