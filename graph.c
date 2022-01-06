#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include <float.h>
#include <limits.h>


pnode newnode(int k, pnode next){
    pnode p = (pnode) malloc(sizeof(node));
    p->node_num = k;
    p->next = next;
    p->edges = NULL;
    return p;
}

pnode find_node(int data, pnode head){
    while (head){
        if (head->node_num == data){
            return head;
        }
        head = head->next;
    }
    return NULL;
}

pnode generate(int k){
    pnode head = NULL;
    for (int i=k-1;i>=0;i--){
        head = newnode(i,head);
    }
    return head;
}

void remove_out_edges(pnode here){
    pedge next = here->edges;
    while(next){
        pedge prev = next;
        next = next->next;
        free(prev);
    }
}

void remove_edge_to(int data, pnode here){
    pedge check_edge = here->edges;
    if(check_edge){
        if (check_edge->endpoint->node_num == data){
            pedge delete = check_edge;
            here->edges = check_edge->next;
            free(delete);
            return;
        }
        while(check_edge->next != NULL){
            if (check_edge->next->endpoint->node_num == data){
                pedge delete = check_edge->next;
                check_edge->next = delete->next;
                free(delete);
                return;
            }
            check_edge = check_edge->next;
        }
    }
}

pnode insert_node(int data, pnode *head){
    pnode *p = head;
    while ((*p)->next)
    {
        if((*p)->node_num< data && (*p)->next->node_num> data){
            pnode new = newnode(data,(*p)->next);
            (*p)->next = new;
            return new;
        }
        p=&((*p)->next);
    }
    pnode new = newnode(data,(*p)->next);
    (*p)->next = new;
    return new;
}


pedge new_edge(int weight, pedge next, pnode dest){
    pedge p = (pedge) malloc(sizeof(edge));
    p->endpoint = dest;
    p->next = next;
    p->weight = weight;
    return p;
}



void build_graph_cmd(pnode *head){
    int i;
    scanf("%d", &i);
    pnode here = find_node(i, *head);
    pedge prev = NULL;
    while(scanf("%d", &i)==1){
        pnode dest = find_node(i, *head);
        scanf("%d", &i);
        prev = new_edge(i,prev,dest);
    }
    here->edges = prev;
}


void insert_node_cmd(pnode *head){
    int i;
    scanf("%d", &i);
    pnode here = find_node(i, *head);
    if (*head == NULL){
        *head = newnode(i, NULL);
        here = *head;
    }
    else if(here != NULL){
        remove_out_edges(here);
    }
    else{
        here = insert_node(i, head);
    }
    pedge prev = NULL;
    while(scanf("%d", &i)==1){
        pnode dest = find_node(i, *head);
        scanf("%d", &i);
        prev = new_edge(i,prev,dest);
    }
    here->edges = prev;
}


void delete_node_cmd(pnode *head){
    int i;
    scanf("%d", &i);
    pnode check_node = *head;
    pnode delete = NULL;
    if (check_node->node_num == i){
        head = &(check_node->next);
        delete = check_node;
    }
    else{
        while(check_node->next){
            if (check_node->next->node_num == i){
                delete = check_node->next;
                check_node->next = delete->next;
                break;
            }
            check_node= check_node->next;
        }
    }
    check_node = *head;
    while(check_node){
        remove_edge_to(i, check_node);
        check_node = check_node->next;
    }
    remove_out_edges(delete);
    free(delete);
}



void deleteGraph_cmd(pnode* head){
    pnode here = *head;
    while(here){
        remove_out_edges(here);
        pnode delete = here;
        here = here->next;
        free(delete);
    }
}




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



void swap(int *x, int *y){
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
        swap((cities+start), (cities+i));
        permute(head, cities, start+1, end, size, fsum);
        swap((cities+start), (cities+i)); //backtrack
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








// #include <stdio.h>
// #include "graph.h"
// #include <stdlib.h>
// #include <float.h>
// #include <limits.h>

// /**
//  * The methods below focused on allocating memory for structs.
//  * They capeable of:
//  * allocating memory to node, edge and a whole graph (nodes)
//  * They use the malloc method from stdlib.h library
//  * */

// pnode allocate_node(int id, pnode node){

//     pnode ptr = (pnode) malloc(sizeof(node));     // allocate memory for a struct node
//     // initialize the pointer values to default
//     ptr->node_num = id;
//     ptr->next = node;
//     ptr->edges = NULL;
//     // return the pointer
//     return ptr;
// }

// pedge allocate_edge(int weight, pedge next, pnode dest){

//     pedge edge = (pedge) malloc(sizeof(edge));     // allocate memory for a struct edge
//     // initialize the pointer values to default
//     edge->endpoint = dest;
//     edge->next = next;
//     edge->weight = weight;
//     // return the pointer
//     return edge;
// }

// pnode allocate_graph(int size){

//     pnode head = NULL;
//     // loop the size of the graph and allocate nodes
//     for (int i = size - 1; i >= 0; i--){

//         head = allocate_node(i,head);
//     }
//     // return the head of the graph
//     return head;
// }

// /**
//  * END OF ALLOCATING METHODS
//  * */


// pnode getNode(int key, pnode head){
//     /**
//      * This method return a node from the graph,
//      * base on a given key
//      * */

//     while (head){
    
//         if (head->node_num == key){
//             return head;
//         }
    
//         head = head->next;
    
//     }
//     // if node is not exist
//     return NULL;
// }


// void del_out(pnode cpy){
//     /**
//      * This method delets all out edges of a given node.
//      * */

//     pedge next = cpy->edges;
    
//     while(next != NULL){
    
//         pedge prev = next;
//         next = next->next;
//         free(prev);
    
//     }
// }

// void del_to(int key, pnode cpy){

//     pedge edge = cpy->edges;

//     if(edge != NULL){     // do only if the node has edges

//         if (edge->endpoint->node_num == key){

//             pedge pe = edge;
//             cpy->edges = edge->next;
//             free(pe);

//             return;
//         }
//         // loop until has no next
//         while(edge->next != NULL){

//             if (edge->next->endpoint->node_num == key){

//                 pedge pe = edge->next;
//                 edge->next = pe->next;
//                 free(pe);

//                 return;
//             }

//             edge = edge->next;
//         }
//     }
// }

// pnode insert(int key, pnode *head){
//     /**
//      * This methos is an auxoliary method to inser_node_cmd.
//      * */

//     pnode *ptr = head;
//     // check if the given id is between the graph's nodes
//     while ((*ptr)->next)
//     {
//         if((*ptr)->node_num < key && (*ptr)->next->node_num > key){

//             pnode new_node = allocate_node(key,(*ptr)->next);        // create a new node in the graph
        
//             (*ptr)->next = new_node;
        
//             return new_node;
        
//         }

//         ptr = &((*ptr)->next);
//     }
//     // in case the node is not in the graph
//     pnode new_node = allocate_node(key,(*ptr)->next);
    
//     (*ptr)->next = new_node;
    
//     return new_node;
// }


// /**
//  * The methods below are an implementation to the graph.h library of evgeny.
//  * it contains the methods:
//  * build_graph_cmd
//  * insert_node_cmd
//  * delete_node_cmd
//  * deleteGraph_cmd
//  * */


// void build_graph_cmd(pnode *head){

//     /*
//     This method build a new graph, while his root is head.
//     */

//     int id;
//     scanf("%d", &id);
    
//     pnode cpy = getNode(id, *head);
//     pedge pe = NULL;
    
//     // allocate edges for each desired node in the graph
//     while(scanf("%d", &id)==1){
    
//         pnode dest = getNode(id, *head);
    
//         scanf("%d", &id);
    
//         pe = allocate_edge(id, pe, dest);   // allocate memory for new edge
    
//     }
    
//     cpy->edges = pe;    // make cpy.edges as pe
// }


// void insert_node_cmd(pnode *head){
//     /*
//     This method add a node to the graph.
//     if its a new node it adds it.
//     if node already exsits in th egraph, update it. 
//     */
    
//     int i;
//     scanf("%d", &i);
//     pnode cpy = getNode(i, *head);
    
//     if (*head == NULL){     // in case the graph is empty, the node will be the head of the graph

//         *head = allocate_node(i, NULL);
//         cpy = *head;
//     }
//     // in case the node exsits in the graph, deletes its edges
//     else if(cpy != NULL){
//         del_out(cpy);
//     }
//     // in case its a new node, insert the node to the graph
//     else{
//         cpy = insert(i, head);
//     }
    
//     pedge pe = NULL;
//     // add new edges to the node and the graph
//     while(scanf("%d", &i)==1){
    
//         pnode dest = getNode(i, *head);
    
//         scanf("%d", &i);
    
//         pe = allocate_edge(i,pe,dest);
    
//     }
    
//     cpy->edges = pe;
// }


// void delete_node_cmd(pnode *head){
//     /*
//     This method delete a node from the graph.
//     */
    
//     int i;
//     scanf("%d", &i);
//     pnode check_node = *head;
//     pnode delete = NULL;
    
//     // in case the desired node is the root
//     if (check_node->node_num == i){
    
//         head = &(check_node->next);
//         delete = check_node;
    
//     }
    
//     else{
//         // loop over the nodes, search the desire node and delete him
//         while(check_node->next){
//             // in case it is the node we desired
//             if (check_node->next->node_num == i){
    
//                 delete = check_node->next;
//                 check_node->next = delete->next;
//                 break;
    
//             }
    
//             check_node= check_node->next;
    
//         }
    
//     }
//     check_node = *head;
//     // delets all edges to the node
//     while(check_node != NULL){
    
//         del_to(i, check_node);
    
//         check_node = check_node->next;
    
//     }
//     // delete the edges of the node
//     del_out(delete);
//     free(delete);
// }



// void deleteGraph_cmd(pnode* head){
//     /*
//     This method delets the entire graph.
//     */

//     pnode cpy = *head;
    
//     while(cpy != NULL){
//         // delets the edges of the node
//         del_out(cpy);
//         pnode delete = cpy;
//         cpy = cpy->next;
    
//         free(delete);
//     }

// }

// /**
//  * The methods below focus on the Algorithm part of the assignment.
//  * it contain the following methods:
//  * shortsPath_cmd
//  * TSP_cmd
//  * */


// int min(int a, int b){
//     /*
//         return the minimum between two numbers
//         a and b.
//     */

//     if (a < 0)
//     {
//         return b;
//     }
//     if (b < 0)
//     {
//         return a;
//     }
//     if (a < b)
//     {
//         return a;
//     }
//     else{
//         return b;
//     }
    
    
    
// }


// int findIndex(pnode head, int id){
//     /*
//         this method receive the id of the node and
//         return its index in the arrays used in
//         the functions below
//     */
//    pnode cpy = NULL;        // new
//    cpy = head;
//    if (id == -1)
//    {
//        return id;
//    }
//    int i = 0;
//    while (cpy != NULL)
//    {
//        if ((*cpy).node_num < id)
//        {
//            i++;
//        }
//        cpy = (*cpy).next;
//    }
//    return i;
// }


// int findMin(int distance[], int visited[], int n){
//     /*
//         this method find the closest unvisited 
//         node to src and return its index in the array
//     */
    
//     int min = 100000;
//     int w = 0;
//     for (int  i = 0; i < n; i++)
//     {
//         if ((visited[i] == 0) && (distance[i] < min) && (distance[i] > 0))
//         {
//             min = distance[i];
//             w = i;
//         }
//     }
//     return w;
// }



// int dijkstra(pnode head, int src, int dest){


//     pnode counter = NULL;
//     counter = head;
//     int n = 0;      // number of odes in the graph

//     int shortestPath = 0;       // the weight of the shortest path from src to dest

//     //find the current size of the graph
//     while (counter != NULL)
//     {
//         counter = counter->next;
//         n++;
//     }

//     int adjList[n][n];      // adj list of the graph using 2D array
//     // insert INF value at start
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < n; j++)
//         {
//             adjList[i][j] = 100000;
//         }
//     }

//     pnode nodes = NULL;
//     nodes = head;
//     pedge edges = NULL;
//     int x = 0, y = 0;

//     // insert the weights of the edges into the adj matrix
//     while (nodes != NULL)
//     {
//         edges = (*nodes).edges;
//         while (edges != NULL)
//         {
//             x = findIndex(head, nodes->node_num);
//             y = findIndex(head, edges->endpoint->node_num);
//             adjList[x][y] = edges->weight;
//             edges = (*edges).next;
//         }
//         nodes = (*nodes).next;
//     }

//     // initilaize the visited array to zeros at start
//     int visited[n];
//     for (int i = 0; i < n; i++)
//     {
//         visited[i] = 0;
//     }

//     visited[src] = 1;       // mark the src node as visited

//     //initilaize the distances from src to all the nodes
//     int distance[n];
//     for (int i = 0; i < n; i++)
//     {
//         if (i == src)
//         {
//             distance[i] = 0;
//         }
//         else{
//             distance[i] = adjList[src][i];
//         }
//     }

//     int w = 0;
//     for (int i = 0; i < n; i++)
//     {
//         w = findMin(distance, visited, n);
//         visited[w] = 1;
//         for (int v = 0; v < n; v++)
//         {
//             if (visited[v] == 0)
//             {
//                 distance[v] = min(distance[v], distance[w] + adjList[w][v]);
//             }
//         }
//     }
    
//     shortestPath = distance[dest];
//     return shortestPath;
// }



// void shortsPath_cmd(pnode head){
//     /*
//     this method print the shortes path weight 
//     from node src to node dest using
//     dijkstra algorithm.
//     time complexity of O(n*n)
//     */
    
//     int s = 0;
//     scanf("%d", &s);
//     int src = findIndex(head, s);        // changed
//     scanf("%d", &s);
//     int dest = findIndex(head,s);       // changed

//     int weight = dijkstra(head, src, dest);

//     if ((weight > 100000) || (weight < 0))
//     {
//         weight = -1;
//     }
    

//     printf("Dijsktra shortest path: %d \n", weight);
    
// }



// void replace(int *x, int *y){
//     int temp = 0;
//     temp = *x;
//     *x = *y;
//     *y = temp;
// }

// int shortsPath_array(pnode head, int cities[], int len){
//     /*
//     calculate the path from each node to another in cities.
//     */

//     int sum = 0;
//     for (int i = 0; i < len-1; i++)
//     {
//         if (sum >= 20000)
//         {
//             return sum;
//         }
//         sum += dijkstra(head, findIndex(head,cities[i]), findIndex(head,cities[i+1]));
//     }
//     return sum;

// }

// void permute(pnode head, int cities[], int start, int end, int size, int* fsum){
//     /*
//         find all the possible permutation of cities,
//         find the permutation with the lowest weight in TSP.
//     */

//     int i = 0;
//     if (start == end)
//     {
//         int sum = shortsPath_array(head, cities, size);
//         if (min(sum, *fsum) == sum)
//         {
//             *fsum = sum;
//         }
//     }
//     else{
//         for (i = start; i <= end; i++)
//         {
//         replace((cities+start), (cities+i));
//         permute(head, cities, start+1, end, size, fsum);
//         replace((cities+start), (cities+i)); //backtrack
//         }
//     }

// }
    



// void TSP_cmd(pnode head){
//     /*
//     This method prin the TSP of k nodes
//     */

//     pnode counter = NULL;
//     counter = head;
//     int size = 0;       // number of nodes in the graph

//     // find the current size of the graph
//     while (counter != NULL)
//     {
//         counter = counter->next;
//         size++;
//     }
//     int p = 0;      //number of cities to visit in tsp
//     scanf("%d", &p);
//     int cities[p];  
//     int i = 0;
//     // receive the list of the cities from the user
//     while (i < p)
//     {
//         int city = 0;
//         scanf("%d",&city);
//         cities[i] = city;
//         i++;
//     }

//     int fsum = 100000;

//     permute(head, cities, 0, p-1, p, &fsum);

//     if ((fsum <= 0) || (fsum > 10000))
//     {
//         fsum = -1;
//     }
//     printf("TSP shortest path: %d \n", fsum);

// }
