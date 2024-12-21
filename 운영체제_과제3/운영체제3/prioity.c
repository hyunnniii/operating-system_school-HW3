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
}  ProcessControlBlock;



typedef struct Node {
    ProcessControlBlock process;
    struct Node* next;
} Node;


Node* createNode(ProcessControlBlock process) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->process = process;
    newNode->next = NULL;
    return newNode;
}

void insertNode(Node** head, ProcessControlBlock process) {
    Node* newNode = createNode(process);
    if (*head == NULL) {
        *head = newNode;
    }
    else {
        Node* currNode = *head;
        while (currNode->next != NULL) {
            currNode = currNode->next;
        }
        currNode->next = newNode;
    }
}


Node* delete(Node** head) {
    if (*head == NULL) {
        return NULL;
    }
    Node* currNode = *head;
    Node* prevNode = NULL;
    Node* highestPriorityNode = *head;
    Node* prevHighestPriorityNode = NULL;

    while (currNode != NULL) {
        if (currNode->process.priority > highestPriorityNode->process.priority) {
            highestPriorityNode = currNode;
            prevHighestPriorityNode = prevNode;
        }
        prevNode = currNode;
        currNode = currNode->next;
    }
    if (prevHighestPriorityNode == NULL) {
        *head = highestPriorityNode->next;
    }
    else {
        prevHighestPriorityNode->next = highestPriorityNode->next;
    }
    return highestPriorityNode;
}


float WaitingTime(ProcessControlBlock* processes, int n) {
    float totalWaitingTime = 0;
    for (int i = 0; i < n; i++) {
        totalWaitingTime = totalWaitingTime + processes[i].waiting_time;
    }
    return totalWaitingTime / n;
}

float ResponseTime(ProcessControlBlock* processes, int n) {
    float totalResponseTime = 0;
    for (int i = 0; i < n; i++) {
        totalResponseTime = totalResponseTime + processes[i].response_time;
    }
    return totalResponseTime / n;
}

float TurnaroundTime(ProcessControlBlock* processes, int n) {
    float totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        totalTurnaroundTime = totalTurnaroundTime + processes[i].turnaround_time;
    }
    return totalTurnaroundTime / n;
}

void Priority(ProcessControlBlock* processes, int numProcesses, float alpha) {
    Node* readyQueue = NULL;
    int currentTime = 0;
    int completedProcesses = 0;

    printf("Scheduling : Priority Scheduling \n");
    printf("==========================================\n");

    while (completedProcesses < numProcesses) {
        //Check for new arrivals and insert them into the ready queue
        for (int i = 0; i < numProcesses; i++) {
            if (processes[i].arrival_time == currentTime) {
                insertNode(&readyQueue, processes[i]);
                printf("<time %d> [new arrival] process %d\n", currentTime, processes[i].pid);
            }
        }
        if (readyQueue == NULL) {
            printf("<time %d> ---- system is idle ----\n", currentTime);
        }
        else {
            Node* runningProcessNode = delete(&readyQueue);
            ProcessControlBlock* runningProcess = &(runningProcessNode->process);
            runningProcess->response_time = currentTime - runningProcess->arrival_time;

            printf("<time %d> process %d is running\n", currentTime, runningProcess->pid);

            runningProcess->burst_time--;

            if (runningProcess->burst_time == 0) {
                completedProcesses++;
                printf("<time %d> process %d is finished\n", currentTime + 1, runningProcess->pid);
                runningProcess->turnaround_time = currentTime + 1 - runningProcess->arrival_time;
            }
            else {
                insert(&readyQueue, *runningProcess);
            }
            Node* temp = readyQueue;
            while (temp != NULL) {
                temp->process.waiting_time++;
                temp = temp->next;
            }
        }
        //Aging
        Node* temp = readyQueue;
        while (temp != NULL) {
            temp->process.priority += alpha * temp->process.waiting_time;
            temp = temp->next;
        }
        currentTime++;
    }

    printf("==========================================\n");
    printf("Average CPU usage: %.2f%%\n", ((float)(currentTime - 1) / currentTime) * 100);
    printf("Average waiting time: %.2f\n", WaitingTime(processes, numProcesses));
    printf("Average response time: %.2f\n", ResponseTime(processes, numProcesses));
    printf("Average turnaround time: %.2f\n", TurnaroundTime(processes, numProcesses));
}

int main() {

    FILE* newfile;
    errno_t err = fopen_s(&newfile, "input.dat", "r");
    if (newfile == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }
    ProcessControlBlock processes[10];
    int num= 0;

    while (fscanf_s(newfile, "%d %d %d %d", &processes[num].pid, &processes[num].priority, &processes[num].arrival_time, &processes[num].burst_time) == 4) {
        num++;
    }
    fclose(newfile);


    float alpha = 0.2; 

    Priority(processes, num, alpha);

    return 0;
}