/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define _CRT_SECURE_NO_WARNINGS
#define MAX_PROCESS 15
#define MAX 20

#define IDLE 0
#define NEW_ARRIVAL 1
#define RUNNING 2
#define FINISHED 3
#define CONTEXT_SWITCH 4
#define ALL_FINISHED 5

#define YES 1
#define NO 0

typedef struct _PCB
{
    int pid;
    int priority;
    int arrival_time;
    int burst_time;
    int firstServedTime;
    int isFirstServed;
    int finishTime;

    double waitingTime;
    double responseTime;
    double turnaroundTime;
} PCB;

PCB job_queue[MAX];
PCB ready_queue[MAX];
PCB process[MAX_PROCESS];

int numberOfJobs = 0;              // �Է¹��� ��ü ���μ��� ����
int processNumberInReadyQueue = 0; // ready_queue�� �� ���μ��� ����
int ready_idx = 0;                 // ready_queue�� idx
int numberOfFinishedProcess = 0;   // ����� ���μ��� ����
int finishedFlag = NO;             // ��� ���μ����� ����Ǿ����� ����
int runningState = NO;             // ���� running state�� �ִ� ���μ����� �ִ��� ����
int currentTime = 0;               // ���������� ����. ����ð��� �ǹ��Ѵ�.
int noMoreArrival = NO;            // ���̻� �����ϴ� ���μ����� ���� ��� YES�� �ٲ��ش�.

// �Ʒ� �������� FCFS�� cpu usage, waiting time, response time, turnaround time �� ����ϱ� ���� �����Ѵ�.
int numberOfIdle = 0;          // cpu�� idle �� Ƚ��
int numberOfContextSwitch = 0; // contextSwitch �� Ƚ��
int allFinishTime = 0;         // ��� ���μ����� ����� �ð�

void checkIfProcessArrive();

// =================================================

// job_queue�� �ִ� process���� arrival time �� �������� �������ش�. process ������ �ⲯ�ؾ� 10���ۿ� ���� �����Ƿ� �ܼ��ϰ� sort ���ش�. �������� ����.
void sortJobQueue()
{
    for (int i = 0; i < numberOfJobs - 1; i++)
    {

        for (int j = i + 1; j < numberOfJobs; j++)
        {
            PCB frontProcess = job_queue[j - 1];
            PCB backProcess = job_queue[j];
            PCB temp;

            if (frontProcess.arrival_time > backProcess.arrival_time)
            {
                temp = backProcess;
                job_queue[j] = frontProcess;
                job_queue[j - 1] = temp;
            }
        }
    }
}

// TimeFlow�� ����ϴ� �Լ�
void printTimeFlow(int state, PCB* p)
{
    if (state != CONTEXT_SWITCH)
    {
        printf("<time %d> ", currentTime);
    }

    switch (state)
    {
    case IDLE:
        printf("---- system is idle ----\n");
        numberOfIdle++;
        break;
    case NEW_ARRIVAL:
        printf("[new arrival] process %d\n", p->pid);

        for (int i = 0; i < numberOfJobs; i++)
        {
            if (job_queue[i].pid == p->pid)
            {
                job_queue[i].arrival_time = currentTime;
                job_queue[i].isFirstServed = YES;
                break;
            }
        }
        break;
    case RUNNING:
        printf("process %d is running\n", p->pid);

        for (int i = 0; i < numberOfJobs; i++)
        {
            if (job_queue[i].pid == p->pid)
            {
                if (job_queue[i].isFirstServed == YES)
                {
                    job_queue[i].isFirstServed = NO;
                    job_queue[i].firstServedTime = currentTime;
                    break;
                }
            }
        }

        break;
    case FINISHED:
        printf("process %d is finished\n", p->pid);
        processNumberInReadyQueue--; // ���μ����� ���������Ƿ� 1 ���ҽ����ش�.
        numberOfFinishedProcess++;
        runningState = NO;
        for (int i = 0; i < numberOfJobs; i++)
        {
            if (job_queue[i].pid == p->pid)
            {
                job_queue[i].finishTime = currentTime;
                break;
            }
        }
        break;
    case CONTEXT_SWITCH:
        printf("--------------------------------- (Context-Switch)\n");
        numberOfContextSwitch++;
        currentTime += 1;
        break;
    case ALL_FINISHED:
        printf("all processes finish\n");
        finishedFlag = YES;
        allFinishTime = currentTime;
        break;
    default:
        break;
    }
}

// ������ ������ �Լ�
// void jobCheck(PCB p)
// {
//     printf("============\n");
//     printf("%d\n", p.arrival_time);
//     printf("%d\n", p.burst_time);
//     printf("%d\n", p.finishTime);
//     printf("%d\n", p.firstServedTime);
//     printf("%d\n", p.isFirstServed);
//     printf("%f\n", p.responseTime);
//     printf("%f\n", p.turnaroundTime);
// }

// performance�� ����ϱ� ���� �Լ�
void calculateCriteria()
{
    double averageCpuUsage;
    double averageWaitingTime = 0;
    double averageResponseTime = 0;
    double averageTurnaroundTime = 0;

    // 1. cpu usage
    // allFinishedTime - (idle + switch Ƚ��) / allFinishedTime
    averageCpuUsage = ((double)(allFinishTime - (numberOfIdle + numberOfContextSwitch)) / allFinishTime) * 100;

    for (int i = 0; i < numberOfJobs; i++)
    {
        // 2. waiting time
        // for each process, waitingTime = finishedTime - arrivedTime - burstTime
        job_queue[i].waitingTime = (double)(job_queue[i].finishTime - job_queue[i].arrival_time - job_queue[i].burst_time);

        // 3. response time
        // firstServedTime - arrivedTime
        job_queue[i].responseTime = (double)(job_queue[i].firstServedTime - job_queue[i].arrival_time);

        // 4. turnaround time
        // finishedTime - arrivedTime
        job_queue[i].turnaroundTime = (double)(job_queue[i].finishTime - job_queue[i].arrival_time);

        averageResponseTime += job_queue[i].responseTime;
        averageTurnaroundTime += job_queue[i].turnaroundTime;
        averageWaitingTime += job_queue[i].waitingTime;

        // jobCheck(job_queue[i]);
    }

    averageResponseTime /= numberOfJobs;
    averageTurnaroundTime /= numberOfJobs;
    averageWaitingTime /= numberOfJobs;

    printf("Average cpu usage : %.2f\n", averageCpuUsage);
    printf("Average waiting time : %.1f\n", averageWaitingTime);
    printf("Average response time : %.1f\n", averageResponseTime);
    printf("Average turnaround time : %.1f\n", averageTurnaroundTime);
}

// ���μ����� �����Ű�� �Լ�. ���� �������� �߻��� �� �ִ� �ϵ鿡 ���� ��� ǥ���س��Ҵ�.
void runProcess(PCB* p)
{
    if (processNumberInReadyQueue > 0)
    {
        int burstTime = p->burst_time;
        while (noMoreArrival != YES) // Ȥ�� �ٸ� ���μ����� �����ߴ��� Ȯ���Ѵ�.
        {
            checkIfProcessArrive();
        }

        for (int i = 0; i < burstTime; i++)
        {
            printTimeFlow(RUNNING, p);
            currentTime++;
            checkIfProcessArrive();
        }
        printTimeFlow(FINISHED, p); // burst Time�� ��� ����Ǹ� finish��Ų��.

        // ���� ��� ���μ����� ���� �۾��� �����ٸ� ��� �����Ѵ�.
        if (numberOfFinishedProcess == numberOfJobs)
        {
            printTimeFlow(ALL_FINISHED, NULL);
        }

        // �̶�, ���� readyQueue�� �ϳ� �̻��� ���μ����� ��� ������ ��� context switch �� �Բ� ���� ���μ����� ��������ָ� �ȴ�. ���� �ƴ� ��� idle �����̴�.
        if (processNumberInReadyQueue > 0)
        {
            printTimeFlow(CONTEXT_SWITCH, p);
            runningState = YES;
            noMoreArrival = NO;
            runProcess(&ready_queue[numberOfFinishedProcess]);
        }
    }
}

// ���μ����� �����ߴ��� üũ�ϰ�, �������� ��� ready_queue�� ���μ����� �ִ� �Լ�.
void checkIfProcessArrive()
{
    if (numberOfFinishedProcess >= numberOfJobs)
    {
        finishedFlag = YES;
        return;
    }

    PCB arriveProcess = job_queue[ready_idx]; // �̸� �����س��ұ� ������ �� ���� job_queue�� ���� ���� �����Ѵٰ� ������ �� �ִ�.

    if (arriveProcess.arrival_time == currentTime && ready_idx < numberOfJobs)
    {
        ready_queue[ready_idx] = arriveProcess;
        printTimeFlow(NEW_ARRIVAL, &ready_queue[ready_idx]);
        processNumberInReadyQueue++;
        ready_idx++;
        if (runningState == NO)
        {
            runningState = YES;
            runProcess(&ready_queue[numberOfFinishedProcess]);
        }
    }
    else if (runningState == NO)
    {
        printTimeFlow(IDLE, NULL);
    }
    else
    {
        noMoreArrival = YES;
    }
}

// �����ٸ� �����ϴ� �Լ�
void FCFS_scheduling()
{
    printf("Scheduling : FCFS\n");
    printf("=============================================\n");

    sortJobQueue();
    while (finishedFlag == NO)
    {
        checkIfProcessArrive();
        currentTime++;
    }
    printf("=============================================\n");
    calculateCriteria();
}

int main(int argc, char* argv[])
{
    // ����, ������ �Է��ϴ� ������ �����Ͽ� ��� �� �� �ִ� �����ͷ� �����ϴ� �۾��� ���ش�.
    FILE* openFile;
    errno_t err = fopen_s(&openFile, "input.dat", "r");
    int userData[MAX];
    int userData_idx = 1;

    if (openFile == 0)
    {
        printf("Could not open file\n");
    }
    else
    {
        int data;
        while (!feof(openFile))
        {
            //�������� �и��� ���� �б�
            fscanf_s(openFile, "%d\n", &data);
            userData[userData_idx] = data;

            userData_idx++;
        }

        fclose(openFile);
    }

    // ���� userData �����ǰ����� PCB�� �־��־�� �Ѵ�.
    int process_idx = 1;
    for (int i = 1; i <= userData_idx; i++)
    {
        int mod = i % 4;
        switch (mod)
        {
        case 1:
            process[process_idx].pid = userData[i];
            break;
        case 2:
            process[process_idx].priority = userData[i];
            break;
        case 3:
            process[process_idx].arrival_time = userData[i];
            break;
        case 0:
            process[process_idx].burst_time = userData[i];
            job_queue[numberOfJobs] = process[process_idx];
            process_idx++;
            numberOfJobs++;
            break;
        default:
            break;
        }
    }

    /*
        FCFS Scheduling

        arrival time�������� ���� ���� �켱���� �����Ű�� �ȴ�.
        job_queue�� arrival time�� �����ͼ�, ������ ���ϰ� �����Ų��.

        - process�� arrive ���� ��
        - process�� �����Ͽ��� ��
        - process�� context-switch �Ǿ��� ��
        - ��� process�� ����Ǿ��� ��
        - �ƹ��� process�� ���� �������� �ʾ��� ��
        - process�� ���� ���϶�

        ��� ������ time�� �������� �����Ѵ�. 1millisecond �� � ���� �߻��ϴ��� print�ؾ� �Ѵ�.
    */
/*
    FCFS_scheduling();

    /*
        CPU usage = ��ü ��� time���� cpu idle �ð��� �� ��
        waiting time = ���μ����� ready queue���� ��ٸ� �ð�
        response time = ���μ����� ready queue�� ���ͼ�, ó������ running �Ǳ���� �ɸ� �ð�
        turnaround time = ���μ����� arrive �� �� finish �ϱ���� �ɸ� �ð�
    *//*
    return 0; 
}
*/