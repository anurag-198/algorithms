#include <cstdio>
#include <cstdlib>
 
using namespace std;
 
struct node {
    int val;
    int weight;
    struct node * next;
};
 
struct edge {
    int weight;
    int u, v;   // edge from u ---> v
};
 
// Adds an edge to an Adjacency List element
struct node * addEdge(struct node * head, int num, int weight)
{
    struct node * p = (struct node *) malloc(sizeof(struct node));
 
    p->val = num;
    p->next = head;
    p->weight = weight;
    head = p;
 
    return p;
}
 
// Enqueues an entry into the Priority Queue
void Enqueue(struct edge heap[], int size, struct edge value)
{
    heap[size] = value;
 
    int i = size;
    struct edge temp;
 
    while (i >= 1) {
        if (heap[i / 2].weight > heap[i].weight) {
            temp = heap[i / 2];
            heap[i / 2] = heap[i];
            heap[i] = temp;
 
            i = i / 2;
        } else {
            break;
        }
    }
}
 
void Heapify(struct edge heap[], int size, int index)
{
    int i = index;
    struct edge temp;
 
    while ((2 * i) < size) {
        if ((2 * i) + 1 >= size) {
            if (heap[i].weight > heap[2 * i].weight) {
                temp = heap[i];
                heap[i] = heap[2 * i];
                heap[2 * i] = temp;
 
                break;
            }
        }
 
        if (heap[i].weight > heap[2 * i].weight || heap[i].weight > heap[2 * i + 1].weight) {
            if (heap[2 * i].weight <= heap[(2 * i) + 1].weight) {
                temp = heap[2 * i];
                heap[2 * i] = heap[i];
                heap[i] = temp;
 
                i = 2 * i;
            } else if (heap[2 * i].weight > heap[(2 * i) + 1].weight) {
                temp = heap[(2 * i) + 1];
                heap[(2 * i) + 1] = heap[i];
                heap[i] = temp;
 
                i = (2 * i) + 1;
            }
        } else {
            break;
        }
    }
}
 
// Deletes and entry in the Priority Queue
void DeleteNode(struct edge heap[], int size, int index)
{
    struct edge temp = heap[index];
 
    heap[index] = heap[size - 1];
    heap[size - 1] = temp;
 
    int i = index;
    --size;
 
    Heapify(heap, size, i);
}
 
// Returns the element with
// Minimum Priority and deletes it
struct edge ExtractMin(struct edge heap[], int size)
{
    struct edge min = heap[0];
 
    DeleteNode(heap, size, 0);
 
    return min;
}
 
// Prim's Algorithm function
void Prim(struct node * adjacencylist[], int vertices, int edges, int startVertex, struct node * MST[])
{
    int current = startVertex, newVertex;
    bool visited[vertices + 1];
    struct node * temp;
    struct edge var;
    struct edge PriorityQueue[2 * edges + 2];
    int QueueSize = 0;
 
    int i;
 
    for (i = 1; i <= vertices; ++i) {        // Initializing
        visited[i] = false;
    }
 
    i = 0;
    
    printf ("hello 1\n");
    while (i < vertices) {
        if (!visited[current]) {            // If current node is not visited
            visited[current] = true;        // Mark it visited
            temp = adjacencylist[current];
 
            while (temp != NULL) {
                var.u = current;
                var.v = temp->val;
                var.weight = temp->weight;
 
                if (!visited[var.v]) {
                    // If the edge leads to an un-visited
                    // vertex only then enqueue it
                    Enqueue(PriorityQueue, QueueSize, var);
                    ++QueueSize;
                }
 
                temp = temp->next;
            }
 
            var = ExtractMin(PriorityQueue, QueueSize);     // The greedy choice
            --QueueSize;
 
            newVertex = var.v;
            current = var.u;
 
            if (!visited[newVertex]) {
                // If it leads to an un-visited vertex, add it to MST
                MST[current] = addEdge(MST[current], newVertex, var.weight);
                MST[newVertex] = addEdge(MST[newVertex], current, var.weight);
                 printf ("hello 3\n");
                 printf("%d  %d\n",newVertex, current);
            }
 
            current = newVertex;
            ++i;
        } else {
 
            var = ExtractMin(PriorityQueue, QueueSize);
            --QueueSize;
 
            newVertex = var.v;
            current = var.u;
 
            if (!visited[newVertex]) {
                MST[current] = addEdge(MST[current], newVertex, var.weight);
                MST[newVertex] = addEdge(MST[newVertex], current, var.weight);
                 printf ("hello 4\n");
                  printf("%d  %d\n",newVertex, current);
            }
 
            current = newVertex;
        }
    }
}
 
int main()
{
    int vertices, edges, i, j, v1, v2, weight;
 
    printf("Enter the Number of Vertices -\n");
    scanf("%d", &vertices);
 
    printf("Enter the Number of Edges -\n");
    scanf("%d", &edges);
 
    struct node * adjacency_list[vertices + 1];
    struct node * MST[vertices + 1];
 
    for (i = 1; i <= vertices; ++i) {
        adjacency_list[i] = NULL;
        MST[i] = NULL;
    }
 
    for (i = 1; i <= edges; ++i) {
        scanf("%d%d%d", &v1, &v2, &weight);
        adjacency_list[v1] = addEdge(adjacency_list[v1], v2, weight);       //Adding edge v1 ---W---> v2
        adjacency_list[v2] = addEdge(adjacency_list[v2], v1, weight);       //Adding edge v2 ---W---> v1
    }
 
    // Printing Adjacency List
    printf("\nAdjacency List -\n\n");
    for (i = 1; i <= vertices; ++i) {
        printf("adjacency_list[%d] -> ", i);
 
        struct node * temp = adjacency_list[i];
 
        while (temp != NULL) {
            printf("%d -> ", temp->val);
            temp = temp->next;
        }
 
        printf("NULL\n");
    }
 
    int startVertex;
 
    printf("\nEnter a Start Vertex - ");
    scanf("%d", &startVertex);
    Prim(adjacency_list, vertices, edges, startVertex, MST);
 
    // Printing MST
    printf("\nMinimum Spanning Tree -\n\n");
    for (i = 1; i <= vertices; ++i) {
        printf("MST[%d] -> ", i);
 
        struct node * temp = MST[i];
 
        while (temp != NULL) {
            printf("%d -> ", temp->val);
            temp = temp->next;
        }
 
        printf("NULL\n");
    }
 
    return 0;
}