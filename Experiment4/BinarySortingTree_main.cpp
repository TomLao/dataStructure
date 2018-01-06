////
//// Created by heze on 17-12-29.
////
//
//#include "header/BinarySortingTree.h"
//#include "header/randPerm.h"
//
//using namespace std;
//
//int main20171231() {
//    int arr[50];
//    int count;
//
//    randPerm(50, 200, 1000, arr);    //50个，范围为从200到1000
//
//    BinarySortingTree<int> bst(arr);
//
//    if ((count = bst.Search(666)) == 0)
//        cout << "找不到数值666" << endl;
//    else
//        cout << "找到666了，经过了" << count << "次查找" << endl;
//
//    cout << "原二叉排序树中序遍历：";
//    bst.print();
//    cout << endl;
//
//    if ((count = bst.Delete(666)) == 0)
//        cout << "找不到666" << endl;
//    else {
//        cout << "删除成功" << ",经过了" << count << "次查找" << endl;
//        cout << "删除666后：";
//        bst.print();
//        cout << endl;
//    }
//}