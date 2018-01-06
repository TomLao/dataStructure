//
// Created by heze on 18-1-6.
//

#ifndef DATASTRUCTURE_RANDPERM_H
#define DATASTRUCTURE_RANDPERM_H

#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

void randPerm(int num, int min, int max, int* arr) {
    vector<int> temp;
    for (int i = min; i <= max; i++) {
        temp.push_back(i);
    }

    srand(time(NULL));	//清空时间序列
    random_shuffle(temp.begin(), temp.end());	//打乱

    for (int i = 0; i < num; i++) {	//取前num个
        arr[i] = temp[i];
    }
}

#endif //DATASTRUCTURE_RANDPERM_H
