#include <iostream>
#include <climits>
using namespace std;

int main() {
    // Process burst times and arrival times
    int bt[] = {5, 3, 8, 6};      // Burst time (total CPU time needed)
    int at[] = {0, 2, 4, 6};      // Arrival time (when process enters)
    int n = 4;                    // Number of processes
    
    // Arrays to store results
    int rem[4];                   // Remaining time (decreases as CPU runs)
    int ct[4];                    // Completion time (when process finishes)
    int tat[4];                   // Turnaround time (CT - AT)
    int wt[4] = {0};              // Waiting time (TAT - BT)
    int completed[4] = {0};       // 1 = finished, 0 = still running
    
    // Initialize remaining time = burst time
    for(int i = 0; i < n; i++) 
        rem[i] = bt[i];
    
    int time = 0;                 // Current CPU time
    int done = 0;                 // Number of processes completed
    
    // Loop until all processes are done
    while(done < n) {
        
        // Find process with smallest remaining time that has arrived
        int idx = -1;             // Index of selected process
        int minRem = INT_MAX;     // Smallest remaining time found so far
        
        for(int i = 0; i < n; i++) {
            // Check 4 conditions:
            // 1. Process has arrived (arrival time <= current time)
            // 2. Process not yet completed
            // 3. Remaining time is smaller than current minimum
            // 4. Process still has work left (remaining > 0)
            if(at[i] <= time && !completed[i] && rem[i] < minRem && rem[i] > 0) {
                minRem = rem[i];
                idx = i;          // Select this process
            }
        }
        
        // If no process is ready (CPU idle), advance time
        if(idx == -1) {
            time++;
            continue;
        }
        
        // Execute the selected process for 1 time unit
        rem[idx]--;               // Decrease remaining time by 1
        time++;                   // Increase current time by 1
        
        // Check if process just finished
        if(rem[idx] == 0) {
            ct[idx] = time;                       // When it finished
            tat[idx] = ct[idx] - at[idx];         // Turnaround time
            wt[idx] = tat[idx] - bt[idx];         // Waiting time
            completed[idx] = 1;                   // Mark as completed
            done++;                               // Increment completion count
        }
    }
    
    // Display results
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for(int i = 0; i < n; i++) {
        cout << "P" << i+1 << "\t" << at[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }
    
    // Calculate averages
    float avgTAT = 0, avgWT = 0;
    for(int i = 0; i < n; i++) {
        avgTAT += tat[i];
        avgWT += wt[i];
    }
    
    cout << "\nAverage Turnaround Time: " << avgTAT / n << endl;
    cout << "Average Waiting Time: " << avgWT / n << endl;
    
    return 0;
}