/*
 * Name: Shantanu Acharya
 * Date: 15th Oct, 2017
 * Language: C
 * Description: Several customers have opened a joint bank account. They can perform concurrent transactions
                on the account. The transactions include: read balance, deposit and withdraw. Each customer
                has its own file which contains a list of transactions he is going to perform.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>                 // For using sleep();

#define BUFFER 1024
#define NUM_CUST 3                  // number of customers


typedef struct {
    double balance;                 // shared variable
    pthread_mutex_t mutex;          // mutual exclusion for the joint bank account
} account;

account joint;

const char* delimiter_character_line;       // delimiter for line tokenization
const char* delimiter_character_col;        // delimiter for column tokenization


// Read the current account balance
void read_balance(char *c_id) {
    printf("Customer %s reads balance:%lf\n", c_id, joint.balance);
    fflush(stdout);
}

// Deposit money to account
void deposit(char *c_id, double amount) {
    joint.balance += amount;
    printf("Customer %s deposited amount:%lf\n", c_id, amount);
    fflush(stdout);
}

// Withdraw money from account
void withdraw(char *c_id, double amount) {
    if(joint.balance >= amount) {
        joint.balance -= amount;
        printf("Customer %s withdrawed amount:%lf\n", c_id, amount);
    }
    fflush(stdout);
}

void *customer(void *arg) {

    // thread id i.e. index is the filename
    int index = (intptr_t)arg;
    char *f_name = malloc(sizeof(char) * 10);
    sprintf(f_name, "%d", index);
    f_name = strcat(f_name, ".txt");

    FILE *fc;
    fc = fopen(f_name, "r");

    char line[BUFFER];
    char *c_id;
    int flag = 0;

    char *instruction, *value;

    while(fgets(line, BUFFER, fc)) {

        char *token_for_line = (char *)strtok(line, delimiter_character_line);

        if (!flag) {
            // First line of each file contains a single value: customer ID
            c_id = strdup(token_for_line);
            flag = 1;
            continue;
        }

        // Each file has two space separated values in each row, except the first
        char *line_ptr = strdup(token_for_line);
        char *token_for_column = (char *)strtok(line_ptr, delimiter_character_col);
        instruction = strdup(token_for_column);
        token_for_column = (char *)strtok(NULL, delimiter_character_col);
        value = strdup(token_for_column);

        if(!strcmp(instruction, "Read")) {
            pthread_mutex_lock(&joint.mutex);
            read_balance(c_id);
            pthread_mutex_unlock(&joint.mutex);
        }
        else if(!strcmp(instruction, "Deposit")) {
            pthread_mutex_lock(&joint.mutex);
            deposit(c_id, atof(value));
            pthread_mutex_unlock(&joint.mutex);
        }
        else if(!strcmp(instruction, "Withdraw")) {
            pthread_mutex_lock(&joint.mutex);
            withdraw(c_id, atof(value));
            pthread_mutex_unlock(&joint.mutex);
        }

        sleep(1);
    }

    fclose(fc);
}

int main() {

    joint.balance = 0;

    delimiter_character_col = " ";
    delimiter_character_line = "\n";

    pthread_t customer_thread;
    int index;

    pthread_mutex_init(&joint.mutex, NULL); // Initialize the mutex

    /*
     * Each thread represents a single customer.
     * The number of customers are specified by NUM_CUST defined above.
    */
    for (index = 1; index <= NUM_CUST; index++) {
        pthread_create(&customer_thread, NULL, customer, (void *)(intptr_t)index);
    }

    pthread_exit(NULL);

    return 0;
}
