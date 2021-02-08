
#include <Windows.h>
#include <iostream>

using namespace std;

int main(void) {
    SYSTEM_INFO si;
    GetSystemInfo(&si);

    int page_size = si.dwPageSize;

    HANDLE heap = HeapCreate(
        NULL,
        page_size,
        page_size * 5
    );

    int* memory1 = (int*) HeapAlloc(heap, NULL, page_size);
    int* memory2 = (int*) HeapAlloc(heap, NULL, page_size);
    
    *memory1 = 11;
    *memory2 = 55;

    //print memory valye
    cout << "memory1 value : " << *memory1 << endl;
    cout << "memory2 value : " << *memory2 << endl;

    HeapFree(heap, NULL, memory1); //free memory1
    HeapDestroy(heap); //delete all memory (in heap)

    cout << "delete heap succeed." << endl;

    return 0;
}