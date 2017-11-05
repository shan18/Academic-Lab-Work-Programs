#include <stdio.h>
#include <stdlib.h>

#define BUFFER 1024

int front, rear;
int proc_counter;
int time;
int pc;     // process counter

FILE *fp;

struct process {
    int pid;    // process id
    int at;     // arrival time
    int bt;     // burst time
    int complete;   // completion time
    int tat;    // turn around time
    int wt;     // wait time
};

struct process proc[100], queue[100];

// Insertion Sort
void sort(struct process proc[], char mode) {
    for(int i = 1; i < pc; i++) {
        for(int j = i-1; j >= 0; j--) {
            if(mode == 'a') {
                if(proc[j].at > proc[j+1].at) {
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

void add_arriving() {
    for(int i = proc_counter + 1; i < pc; i++) {
        if(proc[i].at <= time)
            queue[++rear] = proc[++proc_counter];
        else
            break;
    }
}

void add_complete_time(int id) {
    for(int i = 0; i < pc; i++) {
        if(proc[i].pid == id) {
            proc[i].complete = time;
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        puts("Improper arguments");
        exit(0);
    }

    front = rear = proc_counter = pc = 0;

    fp = fopen(argv[1], "r");

    char line[BUFFER];
    fgets(line, BUFFER, fp);

    while(fscanf(fp, "%d,%d,%d", &proc[pc].pid, &proc[pc].at, &proc[pc].bt) != EOF) {
        pc++;
    }

    int time_slice;
    printf("Enter Time Slice: ");
    scanf("%d", &time_slice);
    int p_left = pc;    // processes left to be executed

    // Sort according to arrival time
    sort(proc, 'a');

    queue[rear] = proc[proc_counter];
    time = queue[front].at;

    while(p_left > 0) {

        if(queue[front].bt >= time_slice) {
            time += time_slice;
            queue[front].bt -= time_slice;
        } else {
            time += queue[front].bt;
            queue[front].bt = 0;
        }

        if(queue[front].bt <= 0) {
            p_left--;
            if(p_left == 0 && proc[proc_counter + 1].at > time)
                time = proc[proc_counter].at;
            if(proc_counter < pc - 1)
                add_arriving(queue);
            add_complete_time(queue[front].pid);
        } else {
            if(proc_counter < pc - 1)
                add_arriving(queue);
            queue[++rear] = queue[front];
        }
        front++;
    }

    // Sort according to process id
    sort(proc, 'i');

    double avg_tat = 0;
    double avg_wt = 0;

    puts("\nPID\tTAT\tWT");
    for(int i = 0; i < pc; i++) {
        proc[i].tat = proc[i].complete - proc[i].at;
        proc[i].wt = proc[i].tat - proc[i].bt;
        printf("%d\t%d\t%d\n", proc[i].pid, proc[i].tat, proc[i].wt);
        avg_tat += proc[i].tat;
        avg_wt += proc[i].wt;
    }
    puts("");

    avg_tat /= (pc * 1.0);
    avg_wt /= (pc * 1.0);

    printf("Average Turn Around Time: %lf\n", avg_tat);
    printf("Average Wait Time: %lf\n", avg_wt);

    fclose(fp);

    return 0;
}