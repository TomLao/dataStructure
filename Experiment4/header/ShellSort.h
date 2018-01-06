//
// Created by heze on 18-1-6.
//

#ifndef DATASTRUCTURE_SHELLSORT_H
#define DATASTRUCTURE_SHELLSORT_H

#include "iostream"

template<typename DataType>
int ShellSort(DataType a[], int n, int distance[], int numofDist){
    //a[]数组，n数组个数，diatance[]跨度数组（递减），numOfDiatance的个数
    int i, j, k, m, gap;
    int count=0;
    DataType temp;
    for(m=0;m<numofDist;m++){   //外循环哦日distance[]个数
        gap=distance[m];        //取本次增量值
        for(k=0;k<gap;k++){     //共有gap个小组
            for(i=k;i<n-gap;i=i+gap){   //组内循环用直接插入排序，每次跨度的增量不是1而是gap
                temp=a[i+gap];
                j=i;
                while(j>-1&&temp<a[j]){
                    a[j+gap]=a[j];
                    j=j-gap;
                    count++;
                }
                a[j+gap]=temp;
            }
        }
    }
    return count;
}


#endif //DATASTRUCTURE_SHELLSORT_H
