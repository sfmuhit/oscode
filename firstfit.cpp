#include<bits/stdc++.h>
using namespace std;

int main() {
    // Memory blocks available (5 blocks with different sizes)
    int b[] = {100, 500, 200, 300, 600};  // Block sizes in KB
    // Processes to allocate (4 processes with their sizes)
    int p[] = {212, 417, 112, 426};        // Process sizes in KB
    int m = 5;  // Number of memory blocks
    int n = 4;  // Number of processes
    
    // Allocation array: stores which block each process gets
    // -1 means process not allocated yet
    int a[4] = {-1, -1, -1, -1};
    
    // ============================================
    // BEST FIT ALLOCATION ALGORITHM
    // ============================================
    // For each process, find the smallest block that can fit it
    for(int i = 0; i < n; i++) {
        
        int best = -1;  // Index of the best fitting blockZ
        
        // Check all memory blocks to find the best fit
        for(int j = 0; j < m; j++) {
            
            // Condition 1: Block must be large enough for the process
            // Condition 2: Either this is the first suitable block OR
            //              this block is smaller than the previously found best block
            if(b[j] >= p[i] && (best == -1 || b[j] < b[best])) {
                best = j;  // Update best block index
            }
        }
        
        // If a suitable block was found
        if(best != -1) {
            a[i] = best;                // Record which block this process gets
            b[best] -= p[i];            // Reduce block size by process size
        }
        // If best == -1, process cannot be allocated (no suitable block)
    }
    
    // ============================================
    // DISPLAY RESULTS
    // ============================================
    cout << "Process\tSize\tBlock Allocated\n";
    cout << "================================\n";
    
    for(int i = 0; i < n; i++) {
        cout << i+1 << "\t" << p[i] << "\t";
        
        if(a[i] == -1) {
            cout << "Not allocated";      // No block could fit this process
        } else {
            cout << "Block " << a[i] + 1; // +1 for human-readable (1-indexed)
        }
        cout << endl;
    }
    
    return 0;
}