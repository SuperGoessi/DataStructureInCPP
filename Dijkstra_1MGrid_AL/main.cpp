// adjacency list with minheap, from internet with small edit

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <chrono>
using namespace std;

struct AdjListNode
{
    int dest;
    int weight;
    struct AdjListNode* next;
};

struct AdjList
{
   struct AdjListNode *head;
};

struct MinHeapNode
{
    int v;
    int dist;
};

struct MinHeap
{
    int size;
    unsigned int capacity;
    int *pos;
    struct MinHeapNode **array;
};

struct Graph
{
    unsigned int V;
    struct AdjList* array;
};

struct AdjListNode* newAdjListNode(int dest, int weight)
{
    struct AdjListNode* newNode = new AdjListNode;
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = nullptr;
    return newNode;
}

struct Graph* createGraph(unsigned int V)
{
    struct Graph* graph = new Graph;
    graph->V = V;

    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));

    for (unsigned int i = 0; i < V; ++i)
        graph->array[i].head = nullptr;

    return graph;
}

// change grid to AL
void addEdge(struct Graph* graph, int xNum, int yNum)
{
    int id1 = 0;
    int id2 = 0;
    int edgeCount = 0;

    for(int i=0; i<yNum; i++){
        for(int j=0; j<xNum; j++){
            id1 = j + i*xNum;

            if(i+1 < yNum){
                id2 = id1 + xNum;
                struct AdjListNode* newNode = newAdjListNode(id2, 1);
                newNode->next = graph->array[id1].head;
                graph->array[id1].head = newNode;

                edgeCount = edgeCount +1;
            }

            if(i-1 >= 0){
                id2 = id1 - xNum;
                struct AdjListNode* newNode = newAdjListNode(id2, 1);
                newNode->next = graph->array[id1].head;
                graph->array[id1].head = newNode;

                edgeCount = edgeCount +1;
            }

            if(j+1 < xNum){
                id2 = id1 + 1;
                struct AdjListNode* newNode = newAdjListNode(id2, 1);
                newNode->next = graph->array[id1].head;
                graph->array[id1].head = newNode;

                edgeCount = edgeCount +1;
            }

            if(j-1 >= 0){
                id2 = id1 -1;
                struct AdjListNode* newNode = newAdjListNode(id2, 1);
                newNode->next = graph->array[id1].head;
                graph->array[id1].head = newNode;

                edgeCount = edgeCount +1;
            }
        }
    }

    cout << edgeCount << endl;
}

struct MinHeapNode* newMinHeapNode(int v, int dist)
{
    struct MinHeapNode* minHeapNode = new MinHeapNode();
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

struct MinHeap* createMinHeap(unsigned int capacity)
{
    struct MinHeap* minHeap = new MinHeap();
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =(struct MinHeapNode**)malloc(capacity *sizeof(struct MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->dist <
         minHeap->array[smallest]->dist )
      smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->dist <
         minHeap->array[smallest]->dist )
      smallest = right;

    if (smallest != idx)
    {
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode = minHeap->array[idx];

        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;

    struct MinHeapNode* root = minHeap->array[0];

    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

void decreaseKey(struct MinHeap* minHeap, int v, int dist)
{
    int i = minHeap->pos[v];

    minHeap->array[i]->dist = dist;

    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

bool isInMinHeap(struct MinHeap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}

void printArr(int dist[], int n)
{
    cout << "Vertex Distance from Source" << endl;
    for (int i = 0; i < n; ++i){
        cout << i << " " << dist[i] << endl;
    }

}

void dijkstra(struct Graph* graph, int src)
{
    unsigned int temp = graph->V;
    int *dist = new int[temp];
    int V = (int)temp;
    struct MinHeap* minHeap = createMinHeap(temp);


    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
    minHeap->size = V;

    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::microseconds res;
    Clock::time_point t1;
    Clock::time_point t2;
    t1 = Clock::now();


    while (!isEmpty(minHeap))
    {
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;
        struct AdjListNode* pCrawl =graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->weight;
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
    //printArr(dist, V);
    t2 = Clock::now();

    cout << " time: " <<std::chrono::duration_cast<res>(t2-t1).count()/1e3 << " ms." << endl;
}

int main(){
    unsigned int V = 100000000;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 10000, 10000);

    dijkstra(graph, 100000000);

    return 0;
}
