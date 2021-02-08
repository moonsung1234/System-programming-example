
#include <iostream>
#include <Windows.h>

using namespace std;

int main(void) {
    SYSTEM_INFO si;
    int page_size;
    int alloc_g;
    int* memory;

    try {
        GetSystemInfo(&si);
        page_size = si.dwPageSize;
        alloc_g = NULL;
        
        //print system infor
        cout << "page size : " << page_size << endl;

        memory = (int*) VirtualAlloc(
            (LPVOID) alloc_g, //window 자동 할당번지 지정
            page_size,
            MEM_RESERVE | MEM_COMMIT,
            PAGE_READWRITE
        );

        *memory = 1120;

        //print memory value
        cout << "memory value : " << *memory << endl;

        VirtualFree(
            memory,
            page_size,
            MEM_DECOMMIT
        );

        cout << "free memory succeed." << endl;

    } catch(int e) {
        cout << "error : " << e << endl;

        VirtualFree(
            memory,
            page_size,
            MEM_DECOMMIT
        );

        cout << "free memory succeed." << endl;
    }
}