#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

typedef struct proccess
{
    int AT, bt, ct, ta, wt, btt;
    string pro_id;
} Schedule;
bool compare(Schedule a, Schedule b)
{
    return a.AT < b.AT;
}
bool compare2(Schedule a, Schedule b)
{
    return a.bt < b.bt;
}

int main()
{
    Schedule pro[10];
    int n, i, j, pcom;

    cout << "Enter the number of processes: ";
    cin >> n;

    cout << "Enter the Process ID, Arrival Time, and Burst Time for each process:\n";
    for (i = 0; i < n; i++)
    {
        cin >> pro[i].pro_id;
        cin >> pro[i].AT;
        cin >> pro[i].bt;
        pro[i].btt = pro[i].bt; 
    }

    sort(pro, pro + n, compare);

    int time = 0; // System time
    pcom = 0;     // Number of completed processes

    // Loop until all processes are completed
    while (pcom < n)
    {
        vector<Schedule*> readyQueue;

        // Find processes that have arrived and are not yet completed
        for (i = 0; i < n; i++)
        {
            if (pro[i].AT <= time && pro[i].bt > 0)
            {
                readyQueue.push_back(&pro[i]);
            }
        }

        // If there are processes that are ready, select the one with the shortest burst time
        if (!readyQueue.empty())
        {
            // Sort the ready queue by burst time (SJF)
            sort(readyQueue.begin(), readyQueue.end(), [](Schedule* a, Schedule* b) {
                return a->bt < b->bt;  // Sort by burst time (shortest first)
            });

            // Process the one with the shortest burst time
            Schedule* current = readyQueue[0];
            time += current->bt;  // Increase system time by burst time of the selected process
            current->ct = time;   // Set the completion time for the selected process
            current->bt = 0;      // Mark the process as completed
            pcom++;               // Increment the count of completed processes
        }
        else
        {
            time++;  // If no process is ready, increment time
        }
    }

    // Calculate turnaround time and waiting time
    cout << "ProID\tAtime\tBtime\tCtime\tTtime\tWtime\n";
    for (i = 0; i < n; i++)
    {
        pro[i].ta = pro[i].ct - pro[i].AT;         // Turnaround time
        pro[i].wt = pro[i].ta - pro[i].btt;        // Waiting time
        cout << pro[i].pro_id << "\t" << pro[i].AT << "\t" << pro[i].btt << "\t" << pro[i].ct << "\t" << pro[i].ta << "\t" << pro[i].wt << endl;
    }

    return 0;
}
