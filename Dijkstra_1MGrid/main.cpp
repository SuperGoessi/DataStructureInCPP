//Dijkstra with 1M nodes applying induction and matrix
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;

int xNum = 10000;
int yNum = 10000;
//int edgeNum = 2*(yNum*(xNum - 1) + xNum*(yNum - 1));
//int idxNum = xNum*yNum +1;
double ma [399960000][3];
int idx [100000001];

void recordIdx(int m){
    int id = 0;
    idx[id] = 0;
    for(int i=1; i<m; i++){
        if(ma[i][0] != ma[i-1][0]){
            id = id + 1;
            idx[id] = i;
        }
        if(i == m-1){
            id = id + 1;
            idx[id] = m;
        }
    }
}

void creatGrid(int xNum, int yNum){
    int id1 = 0;
    int id2 = 0;
    int edgeCount = 0;

    for(int i=0; i< yNum; i++){
        for(int j=0; j < xNum; j++){
            id1 = j + i*xNum;
            if(i+1 < yNum){
                id2 = id1 + xNum;
                ma[edgeCount][0] = id1;
                ma[edgeCount][1] = id2;
                ma[edgeCount][2] = 1;
                edgeCount = edgeCount +1;
            }

            if(i-1 >= 0){
                id2 = id1 - xNum;
                ma[edgeCount][0] = id1;
                ma[edgeCount][1] = id2;
                ma[edgeCount][2] = 1;
                edgeCount = edgeCount +1;
            }

            if(j+1 < xNum){
                id2 = id1 + 1;
                ma[edgeCount][0] = id1;
                ma[edgeCount][1] = id2;
                ma[edgeCount][2] = 1;
                edgeCount = edgeCount +1;
            }

            if(j-1 >= 0){
                id2 = id1 -1;
                ma[edgeCount][0] = id1;
                ma[edgeCount][1] = id2;
                ma[edgeCount][2] = 1;
                edgeCount = edgeCount +1;
            }
        }
    }

    cout << edgeCount << endl;
}

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

void printPath(int parent[], int j)
{
    if(parent[j] == -1){
        return;
    }
    printPath(parent, parent[j]);
    cout << j << " > ";
}

void printArr(double dist[], int n, int parent [], int src)
{
    cout << "Vertex Distance from Source " << src << endl;
    for (int i = 0; i < n; ++i){
        cout <<"shortest path: " << src << " > ";
        printPath(parent, i);
        cout << endl;
        cout << i << "'s shortest path cost is: " << dist[i] << endl;
        cout << endl;

    }

}


bool* checkSTP(double distO [], double distD [], unsigned int n, double budget){
    bool *isInSTP= new bool[n];

    // check the total time budget
    for(unsigned int i=0; i<n; i++){

        if(distO[i] + distD[i]< budget){
            isInSTP[i] = true;
        }
        else {
            isInSTP[i] = false;
        }


    }
    return isInSTP;
}

void printSTP(bool isInSTP [], unsigned int n){
    cout << "The following nodes are in the STP: ";
    for(unsigned int i=0; i<n; i++){
        if(isInSTP[i] == true){
            cout << i << " ";
        }
    }
    cout <<endl;
}

double* dijkstra(int src, unsigned int N)
{
    double *dist = new double[N];
    int *parent = new int[N];
    int V = (int)N;
    struct MinHeap* minHeap = createMinHeap(N);


    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        parent[v] = -1;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
    minHeap->size = V;

    while (!isEmpty(minHeap))
    {
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;
        //cout << "u: " <<u <<endl;
        int firstIdx = idx[u];
        int lastIdx = idx[u+1];
        for(int i=firstIdx; i<lastIdx; i++){
            int v = ma[i][1];
            if(isInMinHeap(minHeap, v) && dist[u] != INT_MAX && ma[i][2] + dist[u] < dist[v]){
                parent[v] = u;
                dist[v] = dist[u] + ma[i][2];
                decreaseKey(minHeap, v, dist[v]);
            }
        }
    }
    printArr(dist, V, parent, src);
    return dist;

}

void dijkstra1(int src, unsigned int N)
{
    double *dist = new double[N];
    int *parent = new int[N];
    int V = (int)N;
    struct MinHeap* minHeap = createMinHeap(N);


    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        parent[v] = -1;
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
        //cout << "u: " <<u <<endl;
        int firstIdx = idx[u];
        int lastIdx = idx[u+1];
        for(int i=firstIdx; i<lastIdx; i++){
            int v = ma[i][1];
            if(isInMinHeap(minHeap, v) && dist[u] != INT_MAX && ma[i][2] + dist[u] < dist[v]){
                parent[v] = u;
                dist[v] = dist[u] + ma[i][2];
                decreaseKey(minHeap, v, dist[v]);
            }
        }
    }
    t2 = Clock::now();

    //printArr(dist, V, parent, src);
    cout << " time: " <<std::chrono::duration_cast<res>(t2-t1).count()/1e3 << " ms." << endl;

}

int main(){

    creatGrid(xNum, yNum);
    recordIdx(399960000);
    //unsigned int N = 100000000;

    dijkstra1(0, 100000000);
    //double* distD = dijkstra(500000, N);
    //printSTP(checkSTP(distO, distD, N, 500), N);


    return 0;
}

