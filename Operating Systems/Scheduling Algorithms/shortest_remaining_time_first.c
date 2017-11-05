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
void sort(struct process proc[], int pc, char mode) {
    for(int i = 1; i < pc; i++) {
        for(int j = i-1; j >= 0; j--) {
            if(mode == 'a') {
                if(proc[j].at > proc[j+1].at) {
                    struct process t = proc[j];
                    proc[j] = proc[j+1];
                    proc[j+1] = t;
                }
            } else if(mode == 'b') {
                if(proc[j].bt > proc[j+1].bt) {
                    struct process t = proc[j];
                    proc[j] = proc[j+1];
                    proc[j+1] = t;
                }
            } else {
                if(proc[j].pid > proc[j+1].pid) {
                    struct process t = proc[j];
                    proc[j] = proc[j+1];
                    proc[j+1] = t;
                }
            }
        }
    }
}

int max_burst(struct process proc[], int pc) {
    int max = proc[0].bt;
    for(int i = 1; i < pc; i++) {
        if(proc[i].bt > max)
            max = proc[i].bt;
    }
    return max;
}

int within_arrival(struct process proc[], int pc, int time) {
    int idx = -1;
    for(int i = 0; i < pc; i++) {
        if(proc[i].at <= time) {
            idx = i;
            break;
        }
    }
    return idx;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        puts("Improper arguments");
        exit(0);
    }

    struct process proc[100], proc_copy[100];
    fp = fopen(argv[1], "r");
    int pc = 0;     // process counter

    char line[BUFFER];
    fgets(line, BUFFER, fp);

    while(fscanf(fp, "%d,%d,%d", &proc[pc].pid, &proc[pc].at, &proc[pc].bt) != EOF) {
        proc_copy[pc].pid = proc[pc].pid;
        proc_copy[pc].at = proc[pc].at;
        proc_copy[pc].bt = proc[pc].bt;
        pc++;
    }

    int p_left = pc;    // processes left to be executed
    int max_exec = max_burst(proc, pc) + 1;

    // Sort according to arrival time
    sort(proc, pc, 'a');

    int time = proc[0].at;
    // Executing earliest arriving process
    time += proc[1].at - proc[0].at;
    proc[0].bt -= (proc[1].at - proc[0].at);
    if(proc[0].bt == 0) {
        proc[0].bt = max_exec;
        proc[0].complete = time;
        p_left--;
    }

    while(p_left > 0) {
        // Sort according to burst time
        sort(proc, pc, 'b');

        int idx = within_arrival(proc, p_left, time);
        if(idx == -1) {
            sort(proc, pc, 'a');

            time += proc[1].at - proc[0].at;
            proc[0].bt -= (proc[1].at - proc[0].at);
            if(proc[0].bt == 0) {
                proc[0].bt = max_exec;
                proc[0].complete = time;
                p_left--;
            }
        } else {
            time++;
            proc[idx].bt--;
            if(proc[idx].bt == 0) {
                proc[idx].bt = max_exec;
                proc[idx].complete = time;
                p_left--;
            }
        }
    }

    // Sort according to pid
    sort(proc, pc, 'i');
    sort(proc_copy, pc, 'i');

    proc[0].tat = proc[0].complete - proc[0].at;
    proc[0].wt = proc[0].tat - proc_copy[0].bt;
    double avg_tat = proc[0].tat;
    double avg_wt = proc[0].wt;

    puts("PID\tTAT\tWT");
    printf("%d\t%d\t%d\n", proc[0].pid, proc[0].tat, proc[0].wt);
    for(int i = 1; i < pc; i++) {
        proc[i].tat = proc[i].complete - proc[i].at;
        proc[i].wt = proc[i].tat - proc_copy[i].bt;
        printf("%d\t%d\t%d\n", proc[i].pid, proc[i].tat, proc[i].wt);
        avg_tat += proc[i].tat;
        avg_wt += proc[i].wt;
    }

    avg_tat /= pc;
    avg_wt /= pc;

    printf("\nAverage Turn Around Time: %lf\n", avg_tat);
    printf("Average Wait Time: %lf\n", avg_wt);

    fclose(fp);

    return 0;
}