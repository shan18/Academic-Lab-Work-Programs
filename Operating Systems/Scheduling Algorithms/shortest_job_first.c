#include <stdio.h>
#include <stdlib.h>

#define BUFFER 1024


FILE *fp;

struct process {
    int pid;    // process id
    int at;     // arrival time
    int bt;     // burst time
    int complete;   // completion time
    int tat;    // turn around time
    int wt;     // wait time
};

// Insertion Sort
void sort(struct process proc[], int pc) {
    for(int i = 1; i < pc; i++) {
        for(int j = i-1; j >= 0; j--) {
            if(proc[j].bt > proc[j+1].bt) {
                struct process t = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = t;
            }
        }
    }
}

int search(struct process proc[], int pc) {
    int min = proc[0].at;
    int idx = 0;
    for(int i = 1; i < pc; i++) {
        if(proc[i].at < min) {
            min = proc[i].at;
            idx = i;
        }
    }
    return idx;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        puts("Improper arguments");
        exit(0);
    }

    struct process proc[100];
    fp = fopen(argv[1], "r");
    int pc = 0;     // process counter

    char line[BUFFER];
    fgets(line, BUFFER, fp);

    while(fscanf(fp, "%d,%d,%d", &proc[pc].pid, &proc[pc].at, &proc[pc].bt) != EOF)
        pc++;

    // Sort according to burst time
    sort(proc, pc);

    // Search earliest arriving process
    int idx = search(proc, pc);

    proc[idx].complete = proc[idx].at + proc[idx].bt;
    proc[idx].tat = proc[idx].complete - proc[idx].at;
    proc[idx].wt = proc[idx].tat - proc[idx].bt;
    double avg_tat = proc[idx].tat;
    double avg_wt = proc[idx].wt;

    puts("PID\tTAT\tWT");
    for(int i = 0; i < pc; i++) {
        if(i == idx) {
            printf("%d\t%d\t%d\n", proc[i].pid, proc[i].tat, proc[i].wt);
            continue;
        }
        int prev = i-1;
        if(i == 0)
            prev = idx;
        else if(i == idx + 1)
            prev = i - 2;
        if(proc[i].at <= proc[prev].complete)
            proc[i].complete = proc[prev].complete + proc[i].bt;

        proc[i].tat = proc[i].complete - proc[i].at;
        proc[i].wt = proc[i].tat - proc[i].bt;
        printf("%d\t%d\t%d\n", proc[i].pid, proc[i].tat, proc[i].wt);
        avg_tat += proc[i].tat;
        avg_wt += proc[i].wt;
    }

    avg_tat /= pc;
    avg_wt /= pc;

    printf("Average Turn Around Time: %lf\n", avg_tat);
    printf("Average Wait Time: %lf\n", avg_wt);

    fclose(fp);

    return 0;
}