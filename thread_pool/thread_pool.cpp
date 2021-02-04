
#include <iostream>
#include <Windows.h>

#define MAX_LIST 10
#define SEMAPHORE_COUNT 1

using namespace std;

typedef void (*TF) (void);

typedef struct _Thread {
    HANDLE thread;
    DWORD thread_id;
} T;

typedef struct ThreadPool {
    T thread_list[MAX_LIST];
    HANDLE event_list[MAX_LIST];
    unsigned int thread_count;
} TP;

class ThreadPooler {
    private :
        TP pool; 

    public :
        ThreadPooler();
        void addWork();
        void startWork();
        ~ThreadPooler();
};

HANDLE thread_semaphore;

void func() {
    WaitForSingleObject(thread_semaphore, INFINITE);
    
    static int temp_number = 0;
    cout << "Thread " << GetCurrentThreadId() << " : " << ++temp_number << endl;
    
    ReleaseSemaphore(thread_semaphore, SEMAPHORE_COUNT, NULL);
}

DWORD WINAPI ThreadProc(LPVOID lp_void) {
    HANDLE event = (HANDLE) lp_void;
    
    WaitForSingleObject(event, INFINITE);
    func();
    ResetEvent(event);

    return TRUE;
}

ThreadPooler::ThreadPooler() {
    thread_semaphore = CreateSemaphore(
        NULL,
        SEMAPHORE_COUNT,
        SEMAPHORE_COUNT,
        NULL
    );
    this->pool.thread_count = 0;
}

void ThreadPooler::addWork() {
    if(this->pool.thread_count >= MAX_LIST) {
        cout << "thread count over." << endl;
        exit(0);
    }

    this->pool.event_list[this->pool.thread_count] = CreateEvent(
        NULL,
        TRUE,
        FALSE,
        NULL
    );
    this->pool.thread_list[this->pool.thread_count].thread = CreateThread(
        NULL,
        NULL,
        ThreadProc,
        (LPVOID) this->pool.event_list[this->pool.thread_count],
        NULL,
        &this->pool.thread_list[this->pool.thread_count++].thread_id 
    );
}

void ThreadPooler::startWork() {
    for(int i=0; i<this->pool.thread_count; i++) {
        SetEvent(this->pool.event_list[i]);
    }
}

ThreadPooler::~ThreadPooler() {
    CloseHandle(thread_semaphore);

    for(int i=0; i<this->pool.thread_count; i++) {
        CloseHandle(this->pool.event_list[i]);
        CloseHandle(this->pool.thread_list[i].thread);
    }
}

int main(void) {
    ThreadPooler tpr;

    for(int i=0; i<5; i++) {
        tpr.addWork();
    }
    
    tpr.startWork();

    Sleep(2000);

    return 0;    
}


