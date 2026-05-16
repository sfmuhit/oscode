#include <bits/stdc++.h>
using namespace std;

void fcfs()
{
    int bt[] = {5, 8, 12};
    int wt[3], tat[3];
    wt[0] = 0;
    for (int i = 1; i < 3; i++)
        wt[i] = wt[i - 1] + bt[i - 1];
    for (int i = 0; i < 3; i++)
        tat[i] = wt[i] + bt[i];
    cout << "\nprocess" << "\t" << "bt" << "\t" << "wt" << "\t" << "\t" << "tat" << endl;
    for (int i = 0; i < 3; i++)
        cout << (i + 1) << "\t" << bt[i] << "\t" << wt[i] << "\t" << tat[i] << endl;
}
void sjf()
{
    cout << "\n====== SJF ======" << endl;
    int bt[] = {1, 5, 2, 7, 5};
    int n = sizeof(bt) / sizeof(bt[0]);

    int at[n] = {3, 4, 0, 3, 5};
    int tat[n];

    // Sort burst times in ascending order (SJF)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (bt[j] < bt[i])
            {
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

void round_robin()
{
    int bt[4] = {0, 2, 4, 6};
    int rem[4] = {5, 3, 8, 6};
    int tat[4], wt[4] = {0};
    int tq = 4;
    int t = 0;
    while (true)
    {
        bool f = true;
        for (int i = 0; i < 4; i++)
        {
            if (rem[i] > 0)
            {
                f = false;
                if (rem[i] > tq)
                {
                    t += tq;
                    rem[i] -= tq;
                }
                else
                {
                    t += rem[i];
                    wt[i] = t - bt[i];
                    rem[i] = 0;
                }
            }
        }
        if (f)
            break;
    }
    for (int i = 0; i < 4; i++)
        tat[i] = bt[i] + wt[i];
    for (int i = 0; i < 4; i++)
        cout << wt[i] << " " << tat[i] << endl;
}

void priority()
{
    //     4
    // 0 2 4 6
    // 5 3 8 6
    // 2 1 3 4
    int bt[4] = {0, 2, 4, 6};
    int pr[4] = {5, 3, 8, 6};
    int tat[4], wt[4];
    for (int i = 0; i < n - 1; i++)
    {
        int m = i;
        for (int j = i + 1; j < n; j++)
        {
            if (pr[j] > pr[m])
                m = j;
        }
        swap(pr[i], pr[m]);
        swap(bt[i], bt[m]);
    }
    wt[0] = 0;
    for (int i = 1; i < 4; i++)
        wt[i] = wt[i - 1] + bt[i - 1];
    for (int i = 0; i < 4; i++)
        tat[i] = wt[i] + bt[i];

    for (int i = 0; i < 4; i++)
        cout << wt[i] << " " << tat[i] << endl;
}

void srtf()
{
    int bt[] = {5, 3, 8, 6}, at[] = {0, 2, 4, 6}, n = 4;
    int rem[4], ct[4], tat[4], wt[4] = {0}, completed[4] = {0};
    for (int i = 0; i < n; i++)
        rem[i] = bt[i];

    int time = 0, done = 0;

    while (done < n)
    {
        int idx = -1, minRem = 9999;
        for (int i = 0; i < n; i++)
            if (at[i] <= time && !completed[i] && rem[i] < minRem && rem[i] > 0)
                idx = i, minRem = rem[i];

        if (idx == -1)
        {
            time++;
            continue;
        }

        rem[idx]--;
        time++;

        if (rem[idx] == 0)
        {
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            completed[idx] = 1;
            done++;
        }
    }

    for (int i = 0; i < n; i++)
        cout << "P" << i + 1 << "\t" << at[i] << "\t" << bt[i] << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
}

void bankers()
{
    int n = 5, r = 3;

    vector<vector<int>> a = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
    vector<vector<int>> m = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
    vector<vector<int>> need(n, vector<int>(r));
    vector<int> av = {3, 3, 2};

    for (int i = 0; i < n; i++)
        for (int j = 0; j < r; j++)
            need[i][j] = m[i][j] - a[i][j];

    vector<int> f(n, 0), s(n), w(av);
    int c = 0;

    while (c < n)
    {
        bool found = 0;
        for (int i = 0; i < n; i++)
        {
            if (!f[i])
            {
                bool ok = 1;
                for (int j = 0; j < r; j++)
                    if (need[i][j] > w[j])
                    {
                        ok = 0;
                        break;
                    }
                if (ok)
                {
                    for (int j = 0; j < r; j++)
                        w[j] += a[i][j];
                    s[c++] = i;
                    f[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found)
        {
            cout << "Unsafe";
            return 0;
        }
    }

    cout << "Safe: ";
    for (int i = 0; i < n; i++)
        cout << "P" << s[i] << " ";
}

void bestfit()
{

    int b[] = {100, 500, 200, 300, 600}, p[] = {212, 417, 112, 426}, m = 5, n = 4, a[4] = {-1, -1, -1, -1};
    for (int i = 0; i < n; i++)
    {
        int best = -1;
        for (int j = 0; j < m; j++)
            if (b[j] >= p[i] && (best == -1 || b[j] < b[best]))
                best = j;
        if (best != -1)
        {
            a[i] = best;
            b[best] -= p[i];
        }
    }
    for (int i = 0; i < n; i++)
        cout << i + 1 << "\t" << p[i] << "\t" << (a[i] == -1 ? "Not Allocated" : to_string(a[i] + 1)) << endl;
}
void worstfit()
{

    int b[] = {100, 500, 200, 300, 600}, p[] = {212, 417, 112, 426}, m = 5, n = 4, a[4] = {-1, -1, -1, -1};
    for (int i = 0; i < n; i++)
    {
        int worst = -1;
        for (int j = 0; j < m; j++)
            if (b[j] >= p[i] && (worst == -1 || b[j] > b[worst]))
                worst = j;
        if (worst != -1)
        {
            a[i] = worst;
            b[worst] -= p[i];
        }
    }
    for (int i = 0; i < n; i++)
        cout << i + 1 << "\t" << p[i] << "\t" << (a[i] == -1 ? "Not Allocated" : to_string(a[i] + 1)) << endl;
}
void firstfit()
{

    int b[] = {100, 500, 200, 300, 600}, p[] = {212, 417, 112, 426}, m = 5, n = 4, a[4] = {-1, -1, -1, -1};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (b[j] >= p[i])
            {
                a[i] = j;
                b[j] -= p[i];
                break;
            }
        }
    }
    for (int i = 0; i < n; i++)
        cout << i + 1 << "\t" << p[i] << "\t" << (a[i] == -1 ? "Not Allocated" : to_string(a[i] + 1)) << endl;
}

void fifoPagRe()
{
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2}, n = 13, cap = 4;
    unordered_set<int> s;
    queue<int> q;
    int faults = 0;
    for (int i = 0; i < n; i++)
    {
        if (s.size() < cap)
        {
            if (s.find(pages[i]) == s.end())
            {
                s.insert(pages[i]);
                q.push(pages[i]);
                faults++;
            }
        }
        else
        {
            if (s.find(pages[i]) == s.end())
            {
                int val = q.front();
                q.pop();
                s.erase(val);
                s.insert(pages[i]);
                q.push(pages[i]);
                faults++;
            }
        }
    }
    cout << faults;
}

void lruPagRe()
{
    int p[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2}, n = 13, cap = 4, f = 0;
    unordered_set<int> s;
    unordered_map<int, int> m;
    for (int i = 0; i < n; i++)
    {
        if (s.size() < cap)
        {
            if (s.find(p[i]) == s.end())
            {
                s.insert(p[i]);
                f++;
            }
            m[p[i]] = i;
        }
        else
        {
            if (s.find(p[i]) == s.end())
            {
                int lru = INT_MAX, val;
                for (auto x : s)
                    if (m[x] < lru)
                    {
                        lru = m[x];
                        val = x;
                    }
                s.erase(val);
                s.insert(p[i]);
                f++;
            }
            m[p[i]] = i;
        }
    }
    cout << f;
}

int main()
{
    // int bt[] = {5,8,12};
    // int wt[3],tat[3];

    // wt[0] =0;
    // for(int i=1;i<3;i++) wt[i] = wt[i-1]+bt[i-1];
    // for(int i=0;i<3;i++) tat[i] = wt[i]+bt[i];
    // cout<<"\nProcess\tBT\tWT\ttat\n";
    // for(int i=0;i<3;i++)
    //     cout<<i+1<<"\t"<<bt[i]<<"\t"<<wt[i]<<"\t"<<tat[i]<<endl;

    // fcfs();
    // sjf();
    // round_robin();

    cout << "Press 1(fcfs) 2(sjf) 3(round_robin) 4(priority)";
    int n;
    cin >> n;
    switch (n)
    {
    case 1:
        fcfs();
        break;
    case 2:
        sjf();
        break;
    case 3:
        round_robin();
        break;
    case 4:
        priority();
        break;
    case 5:
        srtf();
        break;
    }
}