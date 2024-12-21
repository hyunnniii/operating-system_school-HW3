/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ���μ��� ���� ��� ����ü ����
typedef struct {
    int pid; // ���μ��� ID
    int priority; // �켱����
    int arrival_time; // ���� �ð�
    int burst_time; // ���� �ð�

    // ��踦 ���� �ʿ��� ��
    int wait_time; // ��� �ð�
    int response_time; // ���� �ð�
    int turnaround_time; // ��ȯ �ð�
} ProcessControlBlock;

// �Լ� ����
float WaitTime(ProcessControlBlock processes[], int n);
float ResponseTime(ProcessControlBlock processes[], int n);
float TurnaroundTime(ProcessControlBlock processes[], int n);
void fcfs(ProcessControlBlock processes[], int num_processes);
void ArrivalTime(ProcessControlBlock processes[], int num_processes);

int main() {
    // ���Ͽ��� ���μ��� ���� �б�
    FILE* newfile;
    errno_t err = fopen_s(&newfile, "input.dat", "r");
    if (newfile == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return 1;
    }

    // ���μ��� �迭 ����
    ProcessControlBlock processes[10];
    int num_processes = 0;

    // ���μ��� ���� �б�
    while (fscanf_s(newfile, "%d %d %d %d", &processes[num_processes].pid, &processes[num_processes].priority, &processes[num_processes].arrival_time, &processes[num_processes].burst_time) == 4) {
        num_processes++;
    }
    fclose(newfile);

    ArrivalTime(processes, num_processes);

    // ���� �ð��� ���� ���μ��� ����

    // �����ٸ� �ùķ��̼� ����
    fcfs(processes, num_processes);

    return 0;
}

// ��� ��� �ð� ��� �Լ�
float WaitTime(ProcessControlBlock processes[], int n) {
    int total = 0;
    ProcessControlBlock* ptr = processes; // �迭�� ù ��° ��Ҹ� ����Ű�� ������

    while (ptr < processes + n) { // �迭�� ������ �ݺ�
        total += ptr->wait_time;
        ptr++; // ���� ��Ҹ� ����Ű���� ������ �̵�
    }

    return (float)total/ n;
}

// ��� ���� �ð� ��� �Լ�
float ResponseTime(ProcessControlBlock processes[], int n) {
    int total = 0;
    ProcessControlBlock* ptr = processes;

    while (ptr < processes + n) { // �迭�� ������ �ݺ�
        total += ptr->response_time;
        ptr++; // ���� ��Ҹ� ����Ű���� ������ �̵�
    }
    return (float)total / n;
}

// ��� ��ȯ �ð� ��� �Լ�
float TurnaroundTime(ProcessControlBlock processes[], int n) {
    int total= 0;
    ProcessControlBlock* ptr = processes; // �迭�� ù ��° ��Ҹ� ����Ű�� ������

    while (ptr < processes + n) { // �迭�� ������ �ݺ�
        total += ptr->turnaround_time;
        ptr++; // ���� ��Ҹ� ����Ű���� ������ �̵�
    }
    return (float)total / n;
}

void ArrivalTime(ProcessControlBlock processes[], int num_processes) {
    for (int i = 0; i < num_processes - 1; i++) {
        int num= i;
        for (int j = i + 1; j < num_processes; j++) {
            if (processes[j].arrival_time < processes[num].arrival_time) {
                num = j;
            }
        }
        if (num != i) {
            ProcessControlBlock swap = processes[i];
            processes[i] = processes[num];
            processes[num] = swap;
        }
    }
}


// �����ٸ� �ùķ��̼� �Լ�
void fcfs(ProcessControlBlock processes[], int num) {
    int time = 0;

    // �� ���μ������� ��� �ð�, ���� �ð�, ��ȯ �ð� ���
    for (int i = 0; i < num; i++) {
        if (time < processes[i].arrival_time) {
            time = processes[i].arrival_time;
        }

        processes[i].wait_time = time - processes[i].arrival_time;
        processes[i].response_time = processes[i].wait_time;
        processes[i].turnaround_time = processes[i].wait_time + processes[i].burst_time;

       time += processes[i].burst_time;
    }

    // �����ٸ� ��Ʈ ���
    printf("�����ٸ�: FCFS!\n");
    printf("==========================================\n");

    time = 0;
    for (int i = 0; i < num; i++) {
        if (time < processes[i].arrival_time) {
            printf("<TIME %d> ---- SYSTEM IDLE ----\n", time);
            time = processes[i].arrival_time;
            printf("<TIME %d> [NEW ARRIVAL] PROCESS %d\n",time, processes[i].pid);
        }

        printf("<TIME %d> PROCESS %d RUNNNING\n",time, processes[i].pid);
        time++;

        if (i != num- 1 && time == processes[i + 1].arrival_time) {
            printf("------------------------------------------ (CONTEXT-SWITCH)\n");
        }
    }


    // ��� ���
    float cpu_usage = (float)time / time * 100;
    float wait_time = WaitTime(processes, num);
    float response_time = ResponseTime(processes, num);
    float turnaround_time = TurnaroundTime(processes, num);

    // ���� ��� ���
    printf("==========================================\n");
    printf("��� CPU ����: %.2f %%\n", cpu_usage);
    printf("��� ��� �ð�: %.1f\n", wait_time);
    printf("��� ���� �ð�: %.1f\n", response_time);
    printf("��� ��ȯ �ð�: %.1f\n", turnaround_time);

    return;
}
*/