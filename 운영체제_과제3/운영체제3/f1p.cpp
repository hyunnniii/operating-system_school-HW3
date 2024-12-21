/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 프로세스 제어 블록 구조체 정의
typedef struct {
    int pid; // 프로세스 ID
    int priority; // 우선순위
    int arrival_time; // 도착 시간
    int burst_time; // 실행 시간

    // 통계를 위해 필요한 값
    int wait_time; // 대기 시간
    int response_time; // 응답 시간
    int turnaround_time; // 반환 시간
} ProcessControlBlock;

// 함수 선언
float WaitTime(ProcessControlBlock processes[], int n);
float ResponseTime(ProcessControlBlock processes[], int n);
float TurnaroundTime(ProcessControlBlock processes[], int n);
void fcfs(ProcessControlBlock processes[], int num_processes);
void ArrivalTime(ProcessControlBlock processes[], int num_processes);

int main() {
    // 파일에서 프로세스 정보 읽기
    FILE* newfile;
    errno_t err = fopen_s(&newfile, "input.dat", "r");
    if (newfile == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    // 프로세스 배열 생성
    ProcessControlBlock processes[10];
    int num_processes = 0;

    // 프로세스 정보 읽기
    while (fscanf_s(newfile, "%d %d %d %d", &processes[num_processes].pid, &processes[num_processes].priority, &processes[num_processes].arrival_time, &processes[num_processes].burst_time) == 4) {
        num_processes++;
    }
    fclose(newfile);

    ArrivalTime(processes, num_processes);

    // 도착 시간에 따라 프로세스 정렬

    // 스케줄링 시뮬레이션 실행
    fcfs(processes, num_processes);

    return 0;
}

// 평균 대기 시간 계산 함수
float WaitTime(ProcessControlBlock processes[], int n) {
    int total = 0;
    ProcessControlBlock* ptr = processes; // 배열의 첫 번째 요소를 가리키는 포인터

    while (ptr < processes + n) { // 배열의 끝까지 반복
        total += ptr->wait_time;
        ptr++; // 다음 요소를 가리키도록 포인터 이동
    }

    return (float)total/ n;
}

// 평균 응답 시간 계산 함수
float ResponseTime(ProcessControlBlock processes[], int n) {
    int total = 0;
    ProcessControlBlock* ptr = processes;

    while (ptr < processes + n) { // 배열의 끝까지 반복
        total += ptr->response_time;
        ptr++; // 다음 요소를 가리키도록 포인터 이동
    }
    return (float)total / n;
}

// 평균 반환 시간 계산 함수
float TurnaroundTime(ProcessControlBlock processes[], int n) {
    int total= 0;
    ProcessControlBlock* ptr = processes; // 배열의 첫 번째 요소를 가리키는 포인터

    while (ptr < processes + n) { // 배열의 끝까지 반복
        total += ptr->turnaround_time;
        ptr++; // 다음 요소를 가리키도록 포인터 이동
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


// 스케줄링 시뮬레이션 함수
void fcfs(ProcessControlBlock processes[], int num) {
    int time = 0;

    // 각 프로세스마다 대기 시간, 응답 시간, 반환 시간 계산
    for (int i = 0; i < num; i++) {
        if (time < processes[i].arrival_time) {
            time = processes[i].arrival_time;
        }

        processes[i].wait_time = time - processes[i].arrival_time;
        processes[i].response_time = processes[i].wait_time;
        processes[i].turnaround_time = processes[i].wait_time + processes[i].burst_time;

       time += processes[i].burst_time;
    }

    // 스케줄링 차트 출력
    printf("스케줄링: FCFS!\n");
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


    // 통계 계산
    float cpu_usage = (float)time / time * 100;
    float wait_time = WaitTime(processes, num);
    float response_time = ResponseTime(processes, num);
    float turnaround_time = TurnaroundTime(processes, num);

    // 성능 결과 출력
    printf("==========================================\n");
    printf("평균 CPU 사용률: %.2f %%\n", cpu_usage);
    printf("평균 대기 시간: %.1f\n", wait_time);
    printf("평균 응답 시간: %.1f\n", response_time);
    printf("평균 반환 시간: %.1f\n", turnaround_time);

    return;
}
*/