#include<bits/stdc++.h>
using namespace std;
int main(){
   cout << "\n====== SJF ======" << endl;
    int bt[] = {1,5,2,7,5};
    int n = sizeof(bt) / sizeof(bt[0]); 

    int at[n]={3,4,0,3,5};
    int tat[n];

    // Sort burst times in ascending order (SJF)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (bt[j] < bt[i]) {
                swap(bt[j], bt[i]);
            }
        }
    }

    for (int i = 1; i < n; i++)
        at[i] = at[i - 1] + bt[i - 1];
    for (int i = 0; i < n; i++)
        tat[i] = at[i] + bt[i];

    cout << "Process\tBT\tWT\tTAT" << endl;
    for (int i = 0; i < n; i++)
        cout << "P" << (i + 1) << "\t" << bt[i] << "\t" << at[i] << "\t" << tat[i] << endl;
}