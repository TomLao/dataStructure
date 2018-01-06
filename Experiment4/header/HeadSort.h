//
// Created by heze on 18-1-6.
//

#ifndef DATASTRUCTURE_HEADSORT_H
#define DATASTRUCTURE_HEADSORT_H

#include <iostream>
using namespace std;

//调整对，调整非叶节点a[h]使之满足最大堆，n为数组a的元素个数
template<typename DataType>
void CreatHeap(DataType a[], int n, int h){
    int i, j, flag;
    DataType temp;
    i=h;            //i为要建堆的二叉树根节点下标
    j=2*i+1;        //j为i的左孩子节点下标
    temp=a[i];
    flag=0;
    while(j<n && flag!=1){      //沿左右儿子中值最大者重复向下筛选
        if(j<n-1 && a[j]<a[j+1])
            j++;                //选j为左右儿子中较大一个
        if(temp>a[j])
            flag=1;             //标记结果筛选条件
        else{
            a[i]=a[j];
            i=j;
            j=2*i+1;            //按公式移动到下一组
        }
    }
    a[i]=temp;      //把最初的a[i]赋予最后的a[j]
}


//建堆
template<typename DataType>
void InitCreatHeap(DataType a[], int n){
    int i;
    for(i=(n-2)/2;i>=0;i--)
        CreatHeap(a, n, i);
}


//堆排序控制主算法,数组a，n个数据元素
template<typename DataType>
void HeapSort(DataType a[], int n){
    int i;
    DataType temp;
    InitCreatHeap(a, n);    //建堆
    for(i=n-1;i>0;i--){
        temp=a[0];          //将堆顶a[0]和最大堆最后一个元素交换
        a[0]=a[i];
        a[i]=temp;
        CreatHeap(a, i, 0); //调整为满足最大堆
    }
}


#endif //DATASTRUCTURE_HEADSORT_H
