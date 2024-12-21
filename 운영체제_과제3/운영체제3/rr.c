/*
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define RUNNING 2
#define FINISHED 3
#define CONTEXT_SWITCH 4
#define ALL_FINISHED 5

// 프로세스 제어 블록 구조체 정의
struct PCB {
    int pid;
    int priority;
    int arrival_time;
    int burst_time;

    int remaining_time;
    // 통계를 위해 필요한 값
    int waiting_time;
    int turnaround_time;
    int response_time;
};

//기본 구조체 모듈
struct Node {
    struct PCB data;
    struct Node* next;
}Node;

struct Queue {
    struct Node* front;
    struct Node* rear;
}Queue;


void add(struct Queue* queue, struct PCB task);
struct PCB delete(struct Queue* queue);
int checking(struct Queue* queue);
void initProcesses(struct PCB processes[], char* filename);
void result(int time, struct PCB* process);
void finalresult(struct PCB processes[], int n);
void roundrobin(struct PCB processes[], int totalProcesses);

int main() {
    struct PCB processes[10];

    char* filename = "input.dat";

    initProcesses(processes, filename);

    printf("Scheduling: RR\n");
    roundrobin(processes, 10);

    return 0;
}


void add(struct Queue* queue, struct PCB task) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = task;
    newNode->next = NULL;
    (queue->rear == NULL) ? (queue->front = newNode, queue->rear = newNode) : (queue->rear->next = newNode, queue->rear = newNode);
}

struct PCB delete(struct Queue* queue) {
    // If the queue is empty, return an empty process
    if (queue->front == NULL) {
        struct PCB emptyProcess = { 0 };
        return emptyProcess;
    }

    struct Node* frontNode = queue->front;
    struct PCB frontProcess = frontNode->data;

    queue->front = (queue->front == queue->rear) ? NULL : queue->front->next;

    queue->rear = (queue->front == NULL) ? NULL : queue->rear;

    free(frontNode);

    return frontProcess;
}

int checking(struct Queue* queue) {
    return (queue->front == NULL);
}

void initProcesses(struct PCB processes[], char* filename) {

    FILE* newfile;
    errno_t err = fopen_s(&newfile, "input.dat", "r");
    if (newfile == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    int i = 0;
    while (fscanf_s(newfile, "%d %d %d %d", &processes[i].pid, &processes[i].priority, &processes[i].arrival_time, &processes[i].burst_time) != EOF) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].response_time = -1;
        i++;

        if (i >= 10) {
            break;
        }
    }

    fclose(newfile);
}

void result(int time, struct PCB* process) {
    printf("<time %d>", time);
    if (process->pid != 0) {
        printf(" process %d is running\n", process->pid);
    }
    else {
        printf(" ---- system is idle ----\n");
    }
}

void finalresult(struct PCB processes[], int n) {
    float cpuUsage = 0, avgWaitingTime = 0, avgResponseTime = 0, avgTurnaroundTime = 0;

    for (int i = 0; i < n; i++) {
        cpuUsage = cpuUsage + processes[i].burst_time;
        avgWaitingTime = avgWaitingTime + processes[i].waiting_time;
        avgResponseTime = avgResponseTime + processes[i].response_time;
        avgTurnaroundTime = avgTurnaroundTime + processes[i].turnaround_time;
    }

    cpuUsage = (cpuUsage / 1 ) * 100;
    avgWaitingTime = avgWaitingTime / n;
    avgResponseTime = avgResponseTime / n;
    avgTurnaroundTime = avgTurnaroundTime / n;

    printf("==========================================\n");
    printf("평균 cpu 시간: %.2f %%\n", cpuUsage);
    printf("평균 대기 시간: %.2f\n", avgWaitingTime);
    printf("평균 반응 시간: %.2f\n", avgResponseTime);
    printf("평균 복귀 시간: %.2f\n", avgTurnaroundTime);
    printf("==========================================\n");
}

void roundrobin(struct PCB processes[], int lasttask) {
    struct Queue readyQueue;
    readyQueue.front = NULL;
    readyQueue.rear = NULL;

    int time = 0;
    int finish = 0;
    int Index = -1;
    int counter = 0;

    while (finish < lasttask) {
        // Check new arrivals
        for (int i = 0; i < lasttask; i++) {
            if (processes[i].arrival_time == time) {
                processes[i].response_time = time;
               add(&readyQueue, processes[i]);
            }
        }

        // Process execution
        switch (Index) {
        case -1: {
            if (readyQueue.front != NULL) {
                struct PCB newProcess = delete(&readyQueue);
                if (newProcess.pid != 0) {
                    Index = newProcess.pid - 1;
                    counter = 0;
                    result(time, &processes[Index]);
                }
                else {
                    result(time, &newProcess);
                }
            }
            break;
        }
        default: {
            struct PCB* currentProcess = &processes[Index];
            if (currentProcess->remaining_time > 1) {
                currentProcess->remaining_time -= 1;
                counter += 1;
                if (counter >= 1) {
                    add(&readyQueue, *currentProcess);
                    Index = -1;
                    counter = 0;
                }
            }
            else {
                counter += currentProcess->remaining_time;
                currentProcess->remaining_time = 0;
                currentProcess->turnaround_time = time - currentProcess->arrival_time + 1;
                currentProcess->waiting_time = currentProcess->turnaround_time - currentProcess->burst_time;
                finish++;
                Index = -1;
                counter = 0;
            }
            result(time, currentProcess);
            break;
        }
        }
        time++;
    }
    finalresult(processes, lasttask);
}
*/