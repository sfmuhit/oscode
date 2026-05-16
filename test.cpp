#include<bits/stdc++.h>
using namespace std;
int main(){
    int n = 5, r = 3;

    vector<vector<int>> a = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
    vector<vector<int>> m = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
    vector<vector<int>> need(n, vector<int>(r));
    vector<int> av = {3, 3, 2};

    for(int i=0;i<n;i++){
      for(int j=0;j<r;j++){
        need[i][j] = m[i][j]-a[i][j];
      }
    }
    vector<int> f(n,0),s(n),w(av);
    int c = 0;
    while(c<n){
      bool found = 0;
      for(int i=0;i<n;i++){
        if(!f[i]){
          bool ok =1;
          
        }
      }
    }
}