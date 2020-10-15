#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Queue data structure
struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};

struct Queue* createQueue(unsigned capacity){

    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;

    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}
// Queue is full
int isFull(struct Queue* queue)
{
    return (queue->size == queue->capacity);
}

// Queue is empty
int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}

void enqueue(struct Queue* queue, int item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

// Function to remove an item from queue.
// It changes front and size
int dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// AdjacentList and graph data structure
struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};

struct AdjList
{
    struct AdjListNode *head;
};

struct Graph
{
    int V;
    struct AdjList* array;
};

// Create a new adj list node
struct AdjListNode* newAdjListNode(int vertexDestination)
{
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = vertexDestination;
    newNode->next = NULL;
    return newNode;
}

// Creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;

    // Allocate memory for an  array
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));

    // Initialized adjacent
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int u, int v){
    // Create a new node and add it on the beginning
    struct AdjListNode* newNode = newAdjListNode(v);
    newNode->next = graph->array[u].head;
    graph->array[u].head = newNode;

    // Adds an edge from v to u in the graph
    newNode = newAdjListNode(u);
    newNode->next = graph->array[v].head;
    graph->array[v].head = newNode;
}

// Print the graph unsorted
void printGraph(struct Graph* g, char **arr)
{
    for (int v = 0; v < g->V; ++v){
        struct AdjListNode* ptr = g->array[v].head;
        printf("\n Adjacency list of vertex %s %d\n head ", arr[v], v);
        while (ptr){
            printf("-> %s %d", arr[ptr->dest], ptr->dest );
            ptr = ptr->next;
        }
        printf("\n");
    }
}

int letterToNumberMapping(char **matrix,int size, char *input){
    for (int i = 0; i <= size; i++){
        if ( strcmp(matrix[i], input ) == 0){
            return i;
        }
    }
    return -1;
}

void deleteArray(char **arr, int size){
    // Deallocate the memory
    for ( int i = 0; i < size; i++ )
    {
        free(arr[i]);
    }
    free(arr);
}

void deleteGraph(struct Graph *g, int V){
    for (int i=0; i < V; i++ ){
        free(g->array[i].head);
    }
    free(g);
}

int getDegreeVertex(struct Graph *g, int V, char *option){

    // Check for degree
    if ( strcmp(option,"d") != 0){
        return -1;
    }
    // Graph is empty
    if ( g == NULL){
        return -1;
    }

    int counter = 0;
    // Pointer to the linked list of the graph
    struct AdjList ptr = g->array[V];
    if ( ptr.head == NULL){
        return counter;
    }
    while ( ptr.head != NULL){
        counter++;
        ptr.head = ptr.head->next;
    }
    return counter;
}

// Create a 2D array
char **createArray(int row, int col){
    // Allocate memory for 2D array
    char **arr = (char**) malloc(row*sizeof(char*));
    for ( int i = 0; i < row; i++ ){
        arr[i] = (char*) malloc(col*sizeof(char));
    }
    return arr;
}
// Create a bool array
int *createArrayBool(int size ){
    // Allocate memory for 2D array
    int *arr = (int*) calloc(size,sizeof(int));

    return arr;
}

// Return a sorted adjacent list from the graph at V vertex populated by letters Nodes
char** sortedAdjList(struct Graph *g, int V, char **matrix){

    // Error check
    if (V < 0){
        return NULL;
    }
    if ( g == NULL){
        return NULL;
    }

    // Create and initialize an array and degree as the size
    int degree = getDegreeVertex(g,V,"d");
    char **arr = createArray(degree,10);
    struct AdjListNode* head = g->array[V].head;
    int i = 0;

    if ( head == NULL){
        return NULL;
    }
    // Traverse the adjacent list and copy to the matrix
    while (head){
        strcpy(arr[i], matrix[head->dest]);
        i++;
        head = head->next;
    }

    // Sort the adjacent list lexicographically
    char temp[10];
    for(int p=0;p<degree-1;p++){
        for(int q=p+1;q<degree;q++){
            if(strcmp(arr[p],arr[q])>0){
                strcpy(temp,arr[p]);
                strcpy(arr[p],arr[q]);
                strcpy(arr[q],temp);
            }
        }
    }
    return arr;
}

// Prints the lexicographically sorted adjacent list from the graph
void printAdjVertexSorted( struct Graph *g, int V, char **indexArr){
    char **sortedlist = sortedAdjList(g, V,indexArr);
    //printf("degree: %d\n", getDegreeVertex(graph,vertex,"d"));
    for (int i = 0; i < getDegreeVertex(g,V,"d"); ++i) {
        printf("%s ",sortedlist[i]);
    }
    printf("\n");
}

void insertionSort(int arr[], int size){
    int i, key, j;
    for (i = 1; i < size; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void printArraySorted(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void printArrayNumToLetters(const int *arrNum, char **arrLetters, int size){
    for (int i = 0; i < size; ++i) {
        int index = arrNum[i];
        printf("%s",arrLetters[index]);
    }
    printf("\n");
}

void sortGraph(struct Graph *g) {
    if (g == NULL){
        return;
    }
    for (int i = 0; i < g->V; ++i) {
        //IF null then only has one note;
        struct AdjListNode *ptr = g->array[i].head;
        struct AdjListNode *first = g->array[i].head;
        if (ptr == NULL) {
            continue;
        }
        int degree = getDegreeVertex(g, i, "d");
        int *holder = (int *) malloc(degree * sizeof(int));
        int p = 0;

        while (ptr != NULL) {
            holder[p] = ptr->dest;
            p++;
            ptr = ptr->next;
        }
        insertionSort(holder, degree);
        int q = 0;
        while (first != NULL){
            first->dest = holder[q];
            q++;
            first = first->next;
        }
        //printArraySorted(holder,degree);
        free(holder);
    }
}
void BFS(struct Graph *g, int source, char **arrIndex){
    int v = source;
    int u;
    // Error check at lease one node
    if (g == NULL){
        return;
    }
    int numberNodes = g->V;
    if (numberNodes < 1){
        return;
    }
    // Create a Queue
    struct Queue *queue = createQueue(numberNodes);
    // Create a bool array / free later
    int *visited = createArrayBool(numberNodes);

    //printf("%d ",v);
    printf("%s ",arrIndex[v]);
    // Mark entry node as visited
    visited[v]=1;
    // Create queue of nodes
    enqueue(queue,v);
    while (!isEmpty(queue)) {
        v = dequeue(queue);
        struct AdjListNode *ptr = g->array[v].head;
        while (ptr != NULL){
            u = ptr->dest;
            if ( visited[u] == 0 ){
                //printf("%d ",u);
                printf("%s ",arrIndex[u]);
                visited[u]=1;
                enqueue(queue,u);
            }
            ptr = ptr->next;
        }

    }
    // Traverse if the tree if there are disconnected nodes

    printf("\n");
    // Free the queue
    free(queue);
    free(visited);
}
void sortLexically(char **arrInput, int size){
    char temp[30];
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {

            // swapping strings if they are not in the lexicographical order
            if (strcmp(arrInput[i], arrInput[j]) > 0) {
                strcpy(temp, arrInput[i]);
                strcpy(arrInput[i], arrInput[j]);
                strcpy(arrInput[j], temp);
            }
        }
    }
}
int main( int argc, char *argv[argc+1]) {

    //File name from arguments
    if (argc != 3 ){
        printf("no file");
        return EXIT_SUCCESS;
    }

    // Declare the read file
    FILE *fp;

    fp = fopen( argv[1], "r");

    // Check if the file is empty
    if ( fp == NULL ){
        printf("Unable to read");
        return EXIT_SUCCESS;
    }
    // Get the data FREE later
    int size;
    fscanf( fp, "%d", &size );
    //printf("SIZE LINKEDLIST%d\n", size);
    char **indexArr = malloc(size * sizeof(char *));

    for (int i = 0; i < size; ++i) {
        char tmp[10];
        unsigned len = strlen(tmp);
        indexArr[i] = malloc(len);
        fscanf( fp, "%s", tmp );
        strcpy(indexArr[i], tmp);
        //printf("a[%d]:%s\n",i,indexArr[i]);
    }
    sortLexically(indexArr,size);
    char tmp0[10];
    char tmp1[10];
    struct Graph* graph = createGraph(size);
    while (fscanf( fp, "%s %s", tmp0, tmp1 ) != EOF) {
        int indexMapSource = letterToNumberMapping(indexArr,size, tmp0);
        int indexMapDestination = letterToNumberMapping(indexArr,size, tmp1);
        addEdge(graph, indexMapSource, indexMapDestination);
    }
    // Close the file 1
    fclose(fp);
    sortGraph(graph);
    // NEXT FILE
    fp = fopen( argv[2], "r");
    if ( fp == NULL ){
        printf("Unable to read");
        return EXIT_SUCCESS;
    }
    while ( fscanf( fp, "%s", tmp0) != EOF ){
        char *option = tmp0;
        int vertex = letterToNumberMapping(indexArr,size,tmp0);
        if ( vertex < 0 ){
            printf("Error Vertex does not exist\n");
            continue;
        }
        //printf("Vertex: %s\n", tmp0);
        BFS(graph,vertex,indexArr);
    }
    // Close the file 2
    fclose(fp);

    //printGraph(graph,indexArr);

    // Deallocate memory and graph
    deleteArray(indexArr,size);
    deleteGraph(graph,size);

    return EXIT_SUCCESS;
}
