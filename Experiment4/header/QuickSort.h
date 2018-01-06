//
// Created by heze on 18-1-6.
//

#ifndef DATASTRUCTURE_QUICKSORT_H
#define DATASTRUCTURE_QUICKSORT_H

#include <iostream>

using namespace std;

int count_Quick=0;

template<typename DataType>
int QuickSort(DataType a[], int low, int high){
    int i=low, j=high;
    DataType temp=a[low];       //简单地取最低位
    while(i<j){                 //外循环条件
        while(i<j && temp<=a[j])//在数组右端扫描
            j--;
        if(i<j){                //在右边遇到比temp小的，交换到temp左边
            a[i]=a[j];
            i++;
        }
        while(i<j && a[i]<temp) //数组左端扫描
            i++;
        if(i<j){                //在左边遇到比temp大的，交换到temp右边
            a[j]=a[i];
            j--;
        }
        count_Quick++;
    }
    a[i]=temp;                  //退出循环，找到了temp的正确位置
    if(low<i)
        QuickSort(a,low,i-1);   //在temp左边一侧递归
    if(i<high)
        QuickSort(a, j+1, high);//在temp右边一侧递归
}


#endif //DATASTRUCTURE_QUICKSORT_H
