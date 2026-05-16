#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Number of processes (P0 to P4) and resource types (A, B, C)
    int n = 5, r = 3;
    
    // ALLOCATION MATRIX: Resources currently held by each process
    // Format: [Process][Resource A, B, C]
    // Example: P0 has 0 of A, 1 of B, 0 of C
    vector<vector<int>> a = {
        {0, 1, 0},  // P0
        {2, 0, 0},  // P1
        {3, 0, 2},  // P2
        {2, 1, 1},  // P3
        {0, 0, 2}   // P4
    };
    
    // MAX MATRIX: Maximum resources each process may ever need
    vector<vector<int>> m = {
        {7, 5, 3},  // P0 may need up to 7 of A, 5 of B, 3 of C
        {3, 2, 2},  // P1
        {9, 0, 2},  // P2
        {2, 2, 2},  // P3
        {4, 3, 3}   // P4
    };
    
    // NEED MATRIX: Remaining resources each process still needs
    // Need = Max - Allocation
    vector<vector<int>> need(n, vector<int>(r));
    
    // AVAILABLE VECTOR: Resources currently free in the system
    vector<int> av = {3, 3, 2};  // 3 of A, 3 of B, 2 of C available
    
    // Calculate Need Matrix
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < r; j++) {
            need[i][j] = m[i][j] - a[i][j];
        }
    }
    
    
    // f[i] = 1 means process i has finished, 0 means still running
    vector<int> f(n, 0);
    
    // s[] will store the safe sequence (order processes can run)
    vector<int> s(n);
    
    // w[] is a copy of available resources (will change as processes run)
    vector<int> w(av);
    
    int c = 0;  // Counter for how many processes have finished
    
    // BANKER'S SAFETY ALGORITHM
    while(c < n) {
        bool found = false;  // Did we find a process to run this iteration?
        
        // Check each process to see if it can run
        for(int i = 0; i < n; i++) {
            
            // Only check processes that haven't finished yet
            if(!f[i]) {
                
                // Assume this process can run (optimistic)
                bool canRun = true;
                
                // Check if process's NEED ≤ AVAILABLE resources
                for(int j = 0; j < r; j++) {
                    if(need[i][j] > w[j]) {
                        canRun = false;  // Not enough resources
                        break;
                    }
                }
                
                // If process can run (needs ≤ available)
                if(canRun) {
                    // Process finishes and releases its allocated resources
                    for(int j = 0; j < r; j++) {
                        w[j] += a[i][j];  // Add allocation back to available
                    }
                    
                    // Record this process in safe sequence
                    s[c] = i;
                    c++;
                    
                    // Mark process as finished
                    f[i] = 1;
                    
                    // We found at least one process to run this iteration
                    found = true;
                    
                    // Display progress (for understanding)
                    cout << "P" << i << " finishes. Available now: ("
                         << w[0] << "," << w[1] << "," << w[2] << ")\n";
                }
            }
        }
        
        // If no process could run this iteration, system is UNSAFE
        if(!found) {
            cout << "\n UNSAFE STATE! Deadlock may occur.\n";
            return 0;
        }
    }
    
    // All processes finished → SAFE STATE
    cout << "\n SAFE STATE!\n";
    cout << "Safe Sequence: ";
    for(int i = 0; i < n; i++) {
        cout << "P" << s[i];
        if(i < n-1) cout << "->  ";
    }
    cout << endl;
    
    return 0;
}