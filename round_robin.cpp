#include<bits/stdc++.h>
using namespace std;
int main(){
  int bt[4] = {0,2,4,6};
    int rem[4] = {5,3,8,6};
    int tat[4],wt[4]={0};
    int tq = 4;
    int t = 0;
    while(true){
        bool f = true;
        for(int i=0;i<4;i++){
            if(rem[i]>0){
                f=false;
                if(rem[i]>tq){
                    t+=tq;
                    rem[i]-=tq;
                }else{
                    t+=rem[i];
                    wt[i]=t-bt[i];
                    rem[i]=0;
                }
            }
        }
        if(f) break;
    }
    for(int i=0;i<4;i++)
        tat[i] = bt[i] + wt[i];
     cout << "\nProcess\tAT\tBT\tTAT\tWT\n";
    for(int i = 0; i < 4; i++) {
        cout << "P" << i+1 << "\t" << rem[i] << "\t" << bt[i]<< "\t" << tat[i]<<"\t"<<wt[i] << endl;
    }
}