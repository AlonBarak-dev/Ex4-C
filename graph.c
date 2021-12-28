#include <stdio.h>
#include <stdlib.h>
#include "graph.h"



void build_graph_cmd(pnode *head, int size, char *ch){

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

    node *ptr2;
    scanf(" %c", ch);
    while (*ch == 'n')
    {
        ptr2 = *head;
        scanf(" %c", ch);
        int node_id = *ch - '0';
        while ((*ptr2).node_num != node_id)
        {
            ptr2 = (*ptr2).next;
        }
        
        add_edges_to_node(head, &ptr2, node_id, ch);
    }
    
}


void add_edges_to_node(pnode *head, pnode *node, int id, char *ch){

    scanf(" %c", ch);
    edge *edges;
    if((*ch <= '9') && (*ch >= '0')){
        edges = (pedge)malloc(sizeof(edge));
        (*node)->edges = edges;
    }
    else{
        (*node)->edges = NULL;  //dont have edges
        return;
    }
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
        if(scanf(" %c", ch) == EOF){
            break;
        }
        if((*ch <= '9') && (*ch >= '0')){
            (*edges).next = (pedge)malloc(sizeof(edge));
            edges = (*edges).next;
        }
        else{
            (*edges).next = NULL;
        }
    }
}


void deleteGraph_cmd(pnode *head){

    if (! *head)
    {
        return;
    }
    

    pnode * nodes = head;
    pedge * edges = NULL;
    pnode pn = NULL;
    pedge pe = NULL;

    while ((*nodes) != NULL)
    {
        edges = &((*nodes)->edges);
        while ((*edges) != NULL)
        {
            pe = (*edges);
            edges = &((*edges)->next);
            free(pe);
        }

        pn = (*nodes);
        nodes = &((*nodes)->next);
        free(pn);
        
    }

}


void insert_node_cmd(pnode *head, char *ch){

    pnode ptr2 = *head;
    pedge *edges = NULL;
    scanf(" %c", ch);
    pedge pe = NULL;
    int node_id = *ch - '0';
    while ((*ptr2).node_num != node_id && (*ptr2).next != NULL)
    {
        ptr2 = (*ptr2).next;
    }
    if ((*ptr2).next == NULL && (*ptr2).node_num != node_id)
    {
        (*ptr2).next = (pnode)malloc(sizeof(node));
        ptr2 = (*ptr2).next;
        (*ptr2).node_num = node_id;
    }
    else {
        edges = &((*ptr2).edges);
        while ((*edges) != NULL)
        {
            pe = *edges;
            edges = &((*edges)->next);
            free(pe);
        }
    }
    add_edges_to_node(head, &ptr2, node_id, ch);

}


void printGraph_cmd(pnode head){

    
    pnode ptr = head;
    pedge edges;
    while(ptr != NULL){
        edges = (*ptr).edges;
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


   
