#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include <float.h>
#include <limits.h>

/**
 * The methods below focused on allocating memory for structs.
 * They capeable of:
 * allocating memory to node, edge and a whole graph (nodes)
 * They use the malloc method from stdlib.h library
 * */

pnode allocate_node(int k, pnode next){
    pnode p = (pnode) malloc(sizeof(node));
    p->node_num = k;
    p->next = next;
    p->edges = NULL;
    return p;
}

pnode allocate_graph(int k){
    pnode head = NULL;
    for (int i=k-1;i>=0;i--){
        head = allocate_node(i,head);
    }
    return head;
}

pedge allocate_edge(int weight, pedge next, pnode dest){
    pedge p = (pedge) malloc(sizeof(edge));
    p->endpoint = dest;
    p->next = next;
    p->weight = weight;
    return p;
}

/**
 * END OF ALLOCATING METHODS
 * */

pnode getNode(int key, pnode head){
    /**
     * This method return a node from the graph,
     * base on a given key
     * */
    while (head){

        
        if (head->node_num == key){
        
            return head;
        
        }
        
        head = head->next;
    }
    
    return NULL;
}



void del_out(pnode here){
    /**
     * This method delets all out edges of a given node.
     * */
    
    pedge next = here->edges;
    
    while(next){
    
        pedge prev = next;
    
        next = next->next;
    
        free(prev);
    
    }
}

void del_to(int data, pnode here){
    
    pedge c_edge = here->edges;
    
    if(c_edge){     // do only if the node has edges
    
        if (c_edge->endpoint->node_num == data){
    
            pedge delete = c_edge;
    
            here->edges = c_edge->next;
    
            free(delete);
    
            return;
    
        }
    
        while(c_edge->next != NULL){
    
            if (c_edge->next->endpoint->node_num == data){
    
                pedge delete = c_edge->next;
    
                c_edge->next = delete->next;
    
                free(delete);
    
                return;
    
            }
            c_edge = c_edge->next;
        }
    }
}

pnode insert(int data, pnode *head){
    /**
    * This methos is an auxoliary method to inser_node_cmd.
    * */
   
    pnode *ptr = head;
   // check if the given id is between the graph's nodes
    while ((*ptr)->next)
    {
   
        if((*ptr)->node_num< data && (*ptr)->next->node_num> data){
   
            pnode new_node = allocate_node(data,(*ptr)->next);     // create a new node in the graph
   
            (*ptr)->next = new_node;
   
            return new_node;
   
        }
   
        ptr = &((*ptr)->next);
   
    }
    // in case the node is not in the graph
    pnode new_node = allocate_node(data,(*ptr)->next);
   
    (*ptr)->next = new_node;
   
    return new_node;
}




/**
 * The methods below are an implementation to the graph.h library of evgeny.
 * it contains the methods:
 * build_graph_cmd
 * insert_node_cmd
 * delete_node_cmd
 * deleteGraph_cmd
 * */

void build_graph_cmd(pnode *head){
    /*
    This method build a new graph, while his root is head.
    */

    int i;
    scanf("%d", &i);
    pnode ptr = getNode(i, *head);
    pedge pe = NULL;
   
    // allocate edges for each desired node in the graph
    while(scanf("%d", &i)==1){
   
        pnode dest = getNode(i, *head);
   
        scanf("%d", &i);
   
        pe = allocate_edge(i,pe,dest);
   
    }
   
    ptr->edges = pe;
}


void insert_node_cmd(pnode *head){
    /*
    This method add a node to the graph.
    if its a new node it adds it.
    if node already exsits in th egraph, update it. 
    */

    int i;
    scanf("%d", &i);
    pnode ptr = getNode(i, *head);
   
    if (*head == NULL){ // in case the graph is empty, the node will be the head of the graph
   
        *head = allocate_node(i, NULL);
   
        ptr = *head;
   
    }
    // in case the node exsits in the graph, deletes its edges
    else if(ptr != NULL){
        del_out(ptr);
    }
    // in case its a new node, insert the node to the graph
    else{
        ptr = insert(i, head);
    }
   
    pedge pe = NULL;
    // add new edges to the node and the graph
    while(scanf("%d", &i)==1){
   
        pnode dest = getNode(i, *head);
   
        scanf("%d", &i);
   
        pe = allocate_edge(i,pe,dest);
    }
   
    ptr->edges = pe;
}


void delete_node_cmd(pnode *head){
    /*
    This method delete a node from the graph.
    */

    int i;
    scanf("%d", &i);
    pnode c_node = *head;
    pnode delete = NULL;
    // in case the desired node is the root
    if (c_node->node_num == i){

        head = &(c_node->next);

        delete = c_node;

    }
    else{
        // loop over the nodes, search the desire node and delete him
        while(c_node->next){

            if (c_node->next->node_num == i){

                delete = c_node->next;

                c_node->next = delete->next;

                break;
            }

            c_node= c_node->next;
        }
    }

    c_node = *head;
    // delets all edges to the node
    while(c_node){

        del_to(i, c_node);

        c_node = c_node->next;
    }
    // delete the edges of the node
    del_out(delete);
    free(delete);
}



void deleteGraph_cmd(pnode* head){
    /*
    This method delets the entire graph.
    */
    pnode ptr = *head;
   
    while(ptr){
   
        del_out(ptr);
   
        pnode delete = ptr;
   
        ptr = ptr->next;
   
        free(delete);
    }
}


// /**
//  * The methods below focus on the Algorithm part of the assignment.
//  * it contain the following methods:
//  * shortsPath_cmd
//  * TSP_cmd
//  * */

int min(int a, int b){
    /*
        return the minimum between two numbers
        a and b.
    */

    if (a < 0)
    {
        return b;
    }
    if (b < 0)
    {
        return a;
    }
    if (a < b)
    {
        return a;
    }
    else{
        return b;
    }
    
    
    
}


int findIndex(pnode head, int id){
    /*
        this method receive the id of the node and
        return its index in the arrays used in
        the functions below
    */
   pnode cpy = NULL;        // new
   cpy = head;
   if (id == -1)
   {
       return id;
   }
   int i = 0;
   while (cpy != NULL)
   {
       if ((*cpy).node_num < id)
       {
           i++;
       }
       cpy = (*cpy).next;
   }
   return i;
}


int findMin(int distance[], int visited[], int n){
    /*
        this method find the closest unvisited 
        node to src and return its index in the array
    */
    
    int min = 100000;
    int w = 0;
    for (int  i = 0; i < n; i++)
    {
        if ((visited[i] == 0) && (distance[i] < min) && (distance[i] > 0))
        {
            min = distance[i];
            w = i;
        }
    }
    return w;
}



int dijkstra(pnode head, int src, int dest){


    pnode counter = NULL;
    counter = head;
    int n = 0;      // number of odes in the graph

    int shortestPath = 0;       // the weight of the shortest path from src to dest

    //find the current size of the graph
    while (counter != NULL)
    {
        counter = counter->next;
        n++;
    }

    int adjList[n][n];      // adj list of the graph using 2D array
    // insert INF value at start
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            adjList[i][j] = 100000;
        }
    }

    pnode nodes = NULL;
    nodes = head;
    pedge edges = NULL;
    int x = 0, y = 0;

    // insert the weights of the edges into the adj matrix
    while (nodes != NULL)
    {
        edges = (*nodes).edges;
        while (edges != NULL)
        {
            x = findIndex(head, nodes->node_num);
            y = findIndex(head, edges->endpoint->node_num);
            adjList[x][y] = edges->weight;
            edges = (*edges).next;
        }
        nodes = (*nodes).next;
    }

    // initilaize the visited array to zeros at start
    int visited[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }

    visited[src] = 1;       // mark the src node as visited

    //initilaize the distances from src to all the nodes
    int distance[n];
    for (int i = 0; i < n; i++)
    {
        if (i == src)
        {
            distance[i] = 0;
        }
        else{
            distance[i] = adjList[src][i];
        }
    }

    int w = 0;
    for (int i = 0; i < n; i++)
    {
        w = findMin(distance, visited, n);
        visited[w] = 1;
        for (int v = 0; v < n; v++)
        {
            if (visited[v] == 0)
            {
                distance[v] = min(distance[v], distance[w] + adjList[w][v]);
            }
        }
    }
    
    shortestPath = distance[dest];
    return shortestPath;
}



void shortsPath_cmd(pnode head){
    /*
    this method print the shortes path weight 
    from node src to node dest using
    dijkstra algorithm.
    time complexity of O(n*n)
    */
    
    int s = 0;
    scanf("%d", &s);
    int src = findIndex(head, s);        // changed
    scanf("%d", &s);
    int dest = findIndex(head,s);       // changed

    int weight = dijkstra(head, src, dest);

    if ((weight > 100000) || (weight < 0))
    {
        weight = -1;
    }
    

    printf("Dijsktra shortest path: %d \n", weight);
    
}



void replace(int *x, int *y){
    int temp = 0;
    temp = *x;
    *x = *y;
    *y = temp;
}

int shortsPath_array(pnode head, int cities[], int len){

    int sum = 0;
    for (int i = 0; i < len-1; i++)
    {
        if (sum >= 20000)
        {
            return sum;
        }
        sum += dijkstra(head, findIndex(head,cities[i]), findIndex(head,cities[i+1]));
    }
    return sum;

}

void permute(pnode head, int cities[], int start, int end, int size, int* fsum){

    int i = 0;
    if (start == end)
    {
        int sum = shortsPath_array(head, cities, size);
        if (min(sum, *fsum) == sum)
        {
            *fsum = sum;
        }
    }
    else{
        for (i = start; i <= end; i++)
        {
        replace((cities+start), (cities+i));
        permute(head, cities, start+1, end, size, fsum);
        replace((cities+start), (cities+i)); //backtrack
        }
    }

}
    



void TSP_cmd(pnode head){
    pnode counter = NULL;
    counter = head;
    int size = 0;       // number of nodes in the graph

    // find the current size of the graph
    while (counter != NULL)
    {
        counter = counter->next;
        size++;
    }
    int p = 0;      //number of cities to visit in tsp
    scanf("%d", &p);
    int cities[p];  
    int i = 0;
    // receive the list of the cities from the user
    while (i < p)
    {
        int city = 0;
        scanf("%d",&city);
        cities[i] = city;
        i++;
    }

    int fsum = 100000;
    permute(head, cities, 0, p-1, p, &fsum);

    if ((fsum <= 0) || (fsum > 10000))
    {
        fsum = -1;
    }
    printf("TSP shortest path: %d \n", fsum);

}

