#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void build_graph_cmd(pnode *head, int size, char **ch);
void insert_node_cmd(pnode *head, char **ch);
void add_edges_to_node(pnode *head, pnode *node, int id, char **ch);
void delete_node_cmd(pnode *head, char **ch);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
void shortsPath_cmd(pnode head, char **ch);
void TSP_cmd(pnode head, char **ch);
int toStr(char **data);
void TSP_cmd2(pnode head, char **ch);



int main(){


    char data[1000] = {'\0'};
    fgets(data,1000,stdin); // gets the input
    char *ch = data;
    pnode head = NULL;

    while ((*ch != '\n') && (*ch != EOF) && (*ch != '\0'))
    {
        
        if (*ch == 'A')
        {
            if (head)
            {
                deleteGraph_cmd(&head);
            }
            ch += 2;
            int size = toNum(&ch);
            head = (pnode)malloc(sizeof(node));
            build_graph_cmd(&head, size, &ch);

        }

        if (*ch == 'B')
        {
            ch += 2;
            insert_node_cmd(&head, &ch);
        }

        if (*ch == 'D')
        {
            ch += 2;
            delete_node_cmd(&head, &ch);
        }
        
        if (*ch == 'S')
        {
            ch += 2;
            shortsPath_cmd(head, &ch);
        }

        if (*ch == 'T')
        {
            // printGraph_cmd(head);
            ch += 2;
            TSP_cmd2(head, &ch);
        }
        
        
        
        

        
    }

    

















    deleteGraph_cmd(&head);
    return 0;
}