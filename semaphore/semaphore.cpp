
#include <iostream>
#include <Windows.h>

#define SEMAPHORE_COUNT 1 //same effect as mutex 
#define THREAD_COUNT 2
#define LOOP_COUNT 10

using namespace std;

HANDLE semaphore;
int temp_number = 0;

DWORD WINAPI ThreadProc(LPVOID lp_param) {
    for(int i=0; i<LOOP_COUNT; i++) {
        //Critical zone start
        WaitForSingleObject(semaphore, INFINITE);

        temp_number += 1;
        printf("Thread (%d) : %d\n", GetCurrentThreadId(), temp_number);

        ReleaseSemaphore(semaphore, 1, NULL);   
        //Critical zone end
    }

    return TRUE;
}

int main() {
    HANDLE threads[THREAD_COUNT];
    DWORD thread_ids[THREAD_COUNT];

    semaphore = CreateSemaphore(
        NULL,
        SEMAPHORE_COUNT,
        SEMAPHORE_COUNT,
        NULL
    );

    if(semaphore == NULL) {
        printf("CreateSemaphore error : ", GetLastError());
        return 0;
    }

    for(int i=0; i<THREAD_COUNT; i++) {
        threads[i] = CreateThread(
            NULL,
            NULL,
            ThreadProc,
            NULL,
            NULL,
            &thread_ids[i]
        );
    }

    WaitForMultipleObjects(THREAD_COUNT, threads, TRUE, INFINITE);

    for(int i=0; i<THREAD_COUNT; i++) {
        CloseHandle(threads[i]);
    }

    CloseHandle(semaphore);

    return 0;
}