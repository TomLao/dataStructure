//
// Created by heze on 17-12-29.
//

#include "BinarySortingTree.h"

using namespace std;
//假设已经由一个数组长度为10000的数组，里面分别存储了数据0 - 9999，
//想办法让10000个数进行随机排列，便得到了这样一个随机数列，
//只要其中的100个数，从前面取出100个。利用algorithm.h
//里面的一个函数来进行简单处理.
//就是说给定范围min到max放入所有数值，打乱，只取前面num个
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

int main20171229() {
    int arr[50];
    int count;

    randPerm(50, 200, 1000, arr);    //50个，范围为从200到1000

    BinarySortingTree<int> bst(arr);

    if ((count = bst.Search(666)) == 0)
        cout << "找不到数值666" << endl;
    else
        cout << "找到666了，经过了" << count << "次查找" << endl;

    cout << "原二叉排序树中序遍历：";
    bst.print();
    cout << endl;

    if ((count = bst.Delete(666)) == 0)
        cout << "找不到666" << endl;
    else {
        cout << "删除成功" << ",经过了" << count << "次查找" << endl;
        cout << "删除666后：";
        bst.print();
        cout << endl;
    }
}