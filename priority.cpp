#include<bits/stdc++.h>
using namespace std;
int main(){
    int bt[4] = {0,2,4,6};
    int pr[4] = {5,3,8,6};
    int tat[4],wt[4];
    int n = 4;
    for(int i=0;i<n-1;i++){
        int m = i;
        for(int j=i+1;j<n;j++){
            if(pr[j] > pr[m]) m = j;
        }
        swap(pr[i], pr[m]);
        swap(bt[i], bt[m]);
    }
    wt[0] =0;
    for(int i=1;i<4;i++) wt[i] = wt[i-1]+bt[i-1];
    for(int i=0;i<4;i++) tat[i] = wt[i]+bt[i];

cout << "\nProcess\tAT\tBT\tTAT\tWT\n";
    for(int i = 0; i < 4; i++) {
        cout << "P" << i+1 << "\t" << pr[i] << "\t" << bt[i]<< "\t" << tat[i]<<"\t"<<wt[i] << endl;
    }
}