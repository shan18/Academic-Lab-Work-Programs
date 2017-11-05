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
            if(proc[j].at > proc[j+1].at) {
                struct process t = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = t;
            }
        }
    }
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

    // Sort according to arrival time
    sort(proc, pc);

    proc[0].complete = proc[0].at + proc[0].bt;
    proc[0].tat = proc[0].complete - proc[0].at;
    proc[0].wt = proc[0].tat - proc[0].bt;
    double avg_tat = proc[0].tat;
    double avg_wt = proc[0].wt;

    puts("PID\tTAT\tWT");
    printf("%d\t%d\t%d\n", proc[0].pid, proc[0].tat, proc[0].wt);
    for(int i = 1; i < pc; i++) {
        if(proc[i].at < proc[i-1].complete)
            proc[i].complete = proc[i-1].complete + proc[i].bt;
        else
            proc[i].complete = proc[i].at + proc[i].bt;
        proc[i].tat = proc[i].complete - proc[i].at;
        proc[i].wt = proc[i].tat - proc[i].bt;
        printf("%d\t%d\t%d\n", proc[i].pid, proc[i].tat, proc[i].wt);
        avg_tat += proc[i].tat;
        avg_wt += proc[i].wt;
    }
    puts("");

    avg_tat /= pc;
    avg_wt /= pc;

    printf("Average Turn Around Time: %lf\n", avg_tat);
    printf("Average Wait Time: %lf\n", avg_wt);

    fclose(fp);

    return 0;
}