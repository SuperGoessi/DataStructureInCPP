// adjacency matrix with induction array, with STP function (v1), with path record
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//int N = 8;
double ma [28][3];
int idx [9];

void LoadData(int m, int n) {
  int x, y;
  ifstream in("testfile.txt");

  if (!in) {
    cout << "Cannot open file.\n";
    return;
  }

  for (x = 0; x < m; x++) {
    for (y = 0; y < n; y++) {
      in >> ma[x][y];
    }
  }

  in.close();
}

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

void printMa(int m, int n){
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            cout << ma[i][j] << " ";
        }
        cout << endl;
    }
}

void printArr(int m){
    for(int i=0; i< m; i++){
        cout << idx[i] << " ";
    }
    cout << endl;
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

void printArr(int dist[], int n, int parent [], int src)
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

bool* checkSTP(int dist [], int n, int budget){
    bool *isInSTP= new bool[n];
    for(int i=0; i<n; i++){
        if(dist[i] < budget){
            isInSTP[i] = true;
        }
        else {
            isInSTP[i] = false;
        }
    }
    return isInSTP;
}

void printSTP(bool isInSTP [], int n){
    cout << "The following nodes are in the STP: ";
    for(int i=0; i<n; i++){
        if(isInSTP[i] == true){
            cout << i << " ";
        }
    }
    cout <<endl;
}

void dijkstra(int src, unsigned int N)
{
    int *dist = new int[N];
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

    bool *STP = checkSTP(dist, V, 10);
    printSTP(STP, V);
}

int main(){
    // load data, each edge with 2 record in text
    LoadData(28, 3);
    printMa(28, 3);
    recordIdx(28);
    printArr(9);

    dijkstra(0, 8);


    return 0;
}
