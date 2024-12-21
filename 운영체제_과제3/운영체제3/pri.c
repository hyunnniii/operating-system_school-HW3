/*
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct {
    int pid;
    int priority;
    int arrival_time;

    int burst_time;
    int waiting_time;
    int response_time;

    int turnaround_time;
} ProcessControlBlock;


typedef struct Node {
    ProcessControlBlock process;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
} PriorityQueue;

PriorityQueue* createPriorityQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->front = NULL;
    return pq;
}

Node* create(ProcessControlBlock process) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->process = process;
    newNode->next = NULL;
    return newNode;
}


void insertNode(Node** head, ProcessControlBlock process) {
    Node* newNode = createNode(process);
    newNode->next = *head;
    *head = newNode;
}

Node* deleteNode(Node** head) {
    if (*head == NULL) {
        return NULL;
    }

    Node* highestPriorityNode = *head;
    Node* prevHighestPriorityNode = NULL;

    for (Node* currNode = *head; currNode != NULL; currNode = currNode->next) {
        if (currNode->process.priority > highestPriorityNode->process.priority) {
            highestPriorityNode = currNode;
            prevHighestPriorityNode = currNode; // Modification: Fixed assignment for prevHighestPriorityNode
        }
    }
    if (prevHighestPriorityNode == NULL) {
        *head = highestPriorityNode->next;
    }
    else {
        prevHighestPriorityNode->next = highestPriorityNode->next;
    }


    return highestPriorityNode;
}



float WaitingTime(ProcessControlBlock* processes, int n);
float ResponseTime(ProcessControlBlock* processes, int n);
float TurnaroundTime(ProcessControlBlock* processes, int n);
void PriorityScheduling(ProcessControlBlock* processes, int numProcesses, float alpha);


int main() {
    FILE* file;
    errno_t err = fopen_s(&file, "input.dat", "r");
    if (file == NULL) {
        printf("Error : Cannot open file.\n");
        return 1;
    }
    ProcessControlBlock processes[10];
    int numProcesses = 0;

    while (fscanf_s(file, "%d %d %d %d", &processes[numProcesses].pid, &processes[numProcesses].priority, &processes[numProcesses].arrival_time, &processes[numProcesses].burst_time) == 4) {
        numProcesses++;
    }
    fclose(file);

    float alpha = 0.2;

    PriorityScheduling(processes, numProcesses, alpha);

    return 0;
}


float WaitingTime(ProcessControlBlock* processes, int n) {
    float total = 0;
    int i = 0;
    while (i < n) {
        total += processes[i].waiting_time;
        i++;
    }
    return total / n;
}

float ResponseTime(ProcessControlBlock* processes, int n) {
    float total = 0;
    int i = 0;
    while (i < n) {
        total += processes[i].response_time;
        i++;
    }
    return total / n;
}

float TurnaroundTime(ProcessControlBlock* processes, int n) {
    float total = 0;
    int i = 0;
    while (i < n) {
        total += processes[i].turnaround_time;
        i++;
    }
    return total / n;
}

void PriorityScheduling(ProcessControlBlock* processes, int numProcesses, float alpha) {
    Node* readyQueue = NULL;
    int time = 0;
    int finish = 0;
    int status = 0; 

    printf("Scheduling : Preemptive Priority Scheduling with Aging\n");
    printf("==========================================\n");

    while (finish < numProcesses) {
        if (status == 0) {
            for (int i = 0; i < numProcesses; i++) {
                if (processes[i].arrival_time == time) {
                    insertNode(&readyQueue, processes[i]);
                    printf("<time %d> [new arrival] process %d\n", time, processes[i].pid);
                }
            }
            if (readyQueue == NULL) {
                printf("<time %d> ---- system is idle ----\n", time);
                status = 2; 
            }
            else {
                status = 1; 
            }
        }
        else if (status == 1) { 
            Node* runningProcessNode = removeHighestPriorityNode(&readyQueue);
            ProcessControlBlock* runningProcess = &(runningProcessNode->process);
            runningProcess->response_time = time - runningProcess->arrival_time;

            printf("<time %d> process %d is running\n", time, runningProcess->pid);

            runningProcess->burst_time--;

            if (runningProcess->burst_time == 0) {
                finish++;
                printf("<time %d> process %d is finished\n", time + 1, runningProcess->pid);
                runningProcess->turnaround_time = time + 1 - runningProcess->arrival_time;
            }
            else {
                insertNode(&readyQueue, *runningProcess);
            }

            Node* temp = readyQueue;
            while (temp != NULL) {
                temp->process.waiting_time++;
                temp = temp->next;
            }

            status = 2; 
        }
        else if (status == 2) { 
            Node* swap = readyQueue;
            while (swap != NULL) {
                swap->process.priority += alpha * swap->process.waiting_time;
                swap = swap->next;
            }
            time++;
            status = 0; 
        }
    }

    printf("==========================================\n");
    printf("Æò±Õ CPU »ç¿ë·ü: %.2f%%\n", ((float)(time - 1) / time) * 100);
    printf("Æò±Õ ´ë±â ½Ã°£: %.2f\n", WaitingTime(processes, numProcesses));
    printf("Æò±Õ ¹ÝÀÀ ½Ã°£: %.2f\n", ResponseTime(processes, numProcesses));
    printf("Æò±Õ º¹±Í ½Ã°£: %.2f\n", TurnaroundTime(processes, numProcesses));
}
*/