#include <iostream>
#include <fstream>
#include <string>
using namespace std;

double ma [14][3];
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

void printMa(int m, int n){
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            cout << ma[i][j] << " ";
        }
        cout << endl;
    }
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

void printArr(int m){
    for(int i=0; i< m; i++){
        cout << idx[i] << " ";
    }
    cout << endl;
}

int main()
{
    LoadData(14, 3);
    printMa(14, 3);
    recordIdx(14);
    printArr(9);
    cout << ma[0][1] - ma[1][1] <<endl;

}
