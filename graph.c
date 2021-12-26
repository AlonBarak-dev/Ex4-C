#include <stdio.h>
#include <stdlib.h>
#include "graph.h"



void build_graph_cmd(pnode head, int size){

    
    int id = 0;
    if(head == NULL){
        printf("couldn't allocate memory for head of the graph");
        exit(0);
    }

    pnode ptr = head;

    for (int i = 0; i < size; i++)
    {
        (*ptr).node_num = id;       // node id
        (*ptr).next = (pnode)malloc(sizeof(node));  // allocating memory
        if ((*ptr).next == NULL)
        {
            exit(0);
        }
        id++;
        ptr = ptr->next;        // move the pointer to the next Node
    }


    char ch;
    scanf(" %c", &ch);
    while (ch == 'n')
    {
        scanf(" %c", &ch);
        int id = ch - '0';
        ch = add_edges_to_node(head, id);      
    }
    
    return;
}



char add_edges_to_node(pnode head, int id){

    char ch = ' ';
    pedge edge;
    while (ch != 'n')
    {
        
    
    
        scanf(" %c", &ch);

        if (ch < '0' || ch > '9')
        {
            return ch;
        }
        
        int dest = ch - '0';
        pnode d = head;
        while ((*d).node_num != dest)
        {
            d = d->next;
        }
        
        scanf(" %c", &ch);
        int weight = ch - '0';
        
       
        //edge = (*ptr).edges;

    
        edge = (pedge)malloc(sizeof(edge));
        (*edge).endpoint = d;
        (*edge).weight = weight;
        (*edge).next = NULL;
    
         // the desired node
        pnode ptr = head;
        while ((*ptr).node_num != id)
        {
            ptr = ptr->next;
        }







        scanf(" %c", &ch);

    }

    return 'n';






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


