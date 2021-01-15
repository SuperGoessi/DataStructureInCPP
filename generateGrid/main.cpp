#include <iostream>

using namespace std;

int xNum = 100;
int yNum = 100;
//int edgeNum = 2*(yNum*(xNum - 1) + xNum*(yNum - 1));
//int idxNum = xNum*yNum +1;
double ma [39600][3];
int idx [10001];

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

int main()
{
    int edgeNum = 2*(yNum*(xNum - 1) + xNum*(yNum - 1));

    creatGrid(xNum, yNum);
    recordIdx(edgeNum);

    for(int x=98; x<202; x++){
        cout << idx[x] << " " << endl;
    }




    return 0;
}
