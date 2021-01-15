#include <iostream>

using namespace std;
unsigned int edgeNum = 3996000;
unsigned int nodeNum = 1000000;
double ma [3996000][3];
int idx [1000001];

void getGrid(int xNum, int yNum){
    int edgeCount = 0;
    // from left to right
    for(int i=0;i<yNum;i++){
        for(int j=0;j<xNum-1;j++){
            ma[edgeCount][0] = i*1000 + j;
            ma[edgeCount][1] = i*1000 + j + 1;
            ma[edgeCount][2] = 1;
            edgeCount = edgeCount + 1;
        }

    }
    cout << edgeCount << endl;

    // from left to right reverse
    for(int i=0;i<yNum;i++){
        for(int j=0;j<xNum-1;j++){
            ma[edgeCount][0] = i*1000 + j + 1;
            ma[edgeCount][1] = i*1000 + j;
            ma[edgeCount][2] = 1;
            edgeCount = edgeCount + 1;
        }

    }
    cout << edgeCount << endl;

    // from bottom to up
    for(int j=0;j<xNum;j++){
        for(int m=0;m<yNum-1;m++){
            ma[edgeCount][0] = j+m*1000;
            ma[edgeCount][1] = j+m*1000+1000;
            ma[edgeCount][2] = 1;
            edgeCount = edgeCount + 1;
        }

    }
    cout << edgeCount << endl;

    // from bottom to up reverse
    for(int j=0;j<xNum;j++){
        for(int m=0;m<yNum-1;m++){
            ma[edgeCount][0] = j+m*1000+1000;
            ma[edgeCount][1] = j+m*1000;
            ma[edgeCount][2] = 1;
            edgeCount = edgeCount + 1;
        }

    }
    cout << edgeCount << endl;
}

int main()
{
    getGrid(1000, 1000);

    return 0;
}
