#include <stdio.h>
#include <stdlib.h>
#include "graph.h"



void build_graph_cmd(pnode *head, int size){

    // in case the malloc failed, exit
    if(! *head){
        printf("Couldn't allocate memory for head Node");
        exit(0);
    }

    node **cpy = head;
    for(int i = 0; i < size-1; i++){
        (*cpy)->next = (pnode)malloc(sizeof(node));
        cpy = &((*cpy)->next);
    }

    node *ptr = *head;
    node *next;

    for (int i = 0; i < size; i++)
    {
        if (i > 2)
            {
                next = NULL;
            }
        else{ 
                next = (*ptr).next;
            }
    
        
        (*ptr).node_num = i;
        (*ptr).next = next;
        (*ptr).edges = NULL;
        
        ptr = ptr->next;
        
    }

    node *ptr2 = *head;
    char ch;
    scanf(" %c", &ch);
    while (ch == 'n')
    {
        scanf(" %c", &ch);
        int node_id = ch - '0';
        add_edges_to_node(head,&ptr2, node_id, &ch);
    }
    
}


void add_edges_to_node(pnode *head, pnode *node, int id, char *ch){

    scanf(" %c", ch);

    
    edge *edges = (pedge)malloc(sizeof(edge));
    (*node)->edges = edges;
    while (!(*ch < '0') && !(*ch > '9'))
    { 
        int dest = *ch - '0';
        pnode dst = *head;
        while ((*dst).node_num != dest)
        {
            dst = (*dst).next;
        }
        
        scanf(" %c", ch);
        int weight = *ch - '0';
        
        (*edges).endpoint = dst;
        (*edges).weight = weight;
        (*edges).next = (pedge)malloc(sizeof(edge));
        edges = (*edges).next;
        scanf(" %c", ch);
    }

}



void printGraph_cmd(pnode head){

    
    pnode ptr = head;
    int id = 0;
    while(ptr != NULL){
        if(id != 0 && ptr->node_num == 0){
            break;
        }
        pedge edges = (*ptr).edges;
        id++;
        printf("node number: %d\n", ptr->node_num);
        while (edges != NULL)
        {
            printf("dest: %d\n", edges->endpoint->node_num);
            printf("weight : %d\n", edges->weight);
            edges = edges->next;
        }
        ptr = ptr->next;
        
    }

}


