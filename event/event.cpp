
#include <iostream>
#include <Windows.h>

#define THREAD_COUNT 2

using namespace std;

HANDLE event;
int number;

DWORD WINAPI InputThreadProc(LPVOID lp_param) {
    cout << "input : ";
    cin >> number;

    //set event to signaled
    SetEvent(event);

    return TRUE;
}

DWORD WINAPI OutputThreadProc(LPVOID lp_param) {
    WaitForSingleObject(event, INFINITE);

    printf("output : %d", number);

    return TRUE;
}

void setThreads(HANDLE threads[], DWORD thread_ids[]) {
    threads[0] = CreateThread(
        NULL,
        NULL,
        InputThreadProc,
        NULL,
        NULL,
        &thread_ids[0]
    );

    threads[1] = CreateThread(
        NULL,
        NULL,
        OutputThreadProc,
        NULL,
        NULL,
        &thread_ids[1]
    );
}

int main(void) {
    HANDLE threads[THREAD_COUNT];
    DWORD thread_ids[THREAD_COUNT];

    event = CreateEvent(
        NULL,
        TRUE,
        FALSE,
        NULL
    );

    if(event == NULL) {
        printf("CreateEvent error : %d", GetLastError());
        return 0;
    }

    setThreads(threads, thread_ids);

    WaitForMultipleObjects(THREAD_COUNT, threads, TRUE, INFINITE);

    for(int i=0; i<THREAD_COUNT; i++) {
        CloseHandle(threads[i]);
    }

    CloseHandle(event);

    return 0;
}