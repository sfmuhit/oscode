#include<bits/stdc++.h>
using namespace std;
int main(){
    int bt[] = {5,8,12};
    int wt[3],tat[3];
    wt[0] = 0;
    for(int i=1;i<3;i++) wt[i] = wt[i-1] + bt[i-1];
    for(int i=0;i<3;i++) tat[i] = wt[i] + bt[i];
    cout<<"\nprocess"<<"\t"<<"bt"<<"\t"<<"wt"<<"\t"<<"\t"<<"tat"<<endl;
    for(int i=0;i<3;i++)
        cout<<(i+1)<<"\t"<<bt[i]<<"\t"<<wt[i]<<"\t"<<tat[i]<<endl;
}