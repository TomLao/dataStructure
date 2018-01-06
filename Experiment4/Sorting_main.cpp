//
// Created by heze on 18-1-6.
//

#include "header/ShellSort.h"
#include "header/randPerm.h"
#include "header/QuickSort.h"
#include "header/HeadSort.h"
#include <sys/timeb.h>

using namespace std;

int main() {
    int arr[50], distance[3] = {6, 3, 1};
    struct timeb startTime , endTime;


    //ShellSort测试
    randPerm(50, 200, 1000, arr);    //50个，范围为从200到1000

    ftime(&startTime);
    int count_Shell = ShellSort(arr, 50, distance, 3);
    ftime(&endTime);

    for (int i = 0; i < 50; i++) {
        cout << arr[i] << " ";
    }
    cout << endl << "ShellSort内部操作次数：" << count_Shell << " 运行时间："<<(endTime.time-startTime.time)*1000 + (endTime.millitm - startTime.millitm) << "毫秒"<<endl << endl;


    //QuickSort测试
    randPerm(50, 200, 1000, arr);    //50个，范围为从200到1000

    ftime(&startTime);
    QuickSort(arr, 0, 50 - 1);
    ftime(&endTime);

    for (int i = 0; i < 50; i++) {
        cout << arr[i] << " ";
    }
    cout << endl << "QuickSort内部操作次数：" << count_Quick << " 运行时间："<<(endTime.time-startTime.time)*1000 + (endTime.millitm - startTime.millitm) << "毫秒" << endl << endl;


    //HeapSort测试
    randPerm(50, 200, 1000, arr);    //50个，范围为从200到1000

    ftime(&startTime);
    HeapSort(arr, 50);
    ftime(&endTime);

    for (int i = 0; i < 50; i++) {
        cout << arr[i] << " ";
    }
    cout << endl << "HeapSort:"<< " 运行时间："<<(endTime.time-startTime.time)*1000 + (endTime.millitm - startTime.millitm) << "毫秒";

}