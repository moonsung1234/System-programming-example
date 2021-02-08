
#include <Windows.h>
#include <iostream>

using namespace std;

int main(void) {
    //get page size
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    int page_size = si.dwPageSize;

    cout << "page size : " << page_size << endl;

    HANDLE mm_file = CreateFile(
        TEXT("C:\\mmf.dat"), //유니코드
        GENERIC_READ | GENERIC_WRITE, //읽기모드 쓰기모드
        FILE_SHARE_READ | FILE_SHARE_WRITE, //프로세스 읽기 쓰기 공유
        NULL, //보안 속성 설정
        OPEN_ALWAYS, //있으면 열기, 없으면 생성
        FILE_ATTRIBUTE_NORMAL, //기본 특성 정보
        NULL //새파일 관련 인자 설정
    );
    HANDLE map = CreateFileMapping(
        mm_file,
        NULL,
        PAGE_READWRITE,
        NULL, //0
        page_size / 8,
        NULL
    );

    int* file_asmemory = (int*) MapViewOfFile(
        map,
        FILE_MAP_ALL_ACCESS,
        NULL,
        NULL,
        NULL
    );

    *file_asmemory = 2952;

    //print value
    cout << "value : " << *file_asmemory << endl;

    //close
    CloseHandle(map);
    CloseHandle(mm_file);

    cout << "close handle succeed." << endl;

    return 0;
}