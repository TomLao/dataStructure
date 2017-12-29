//
// Created by heze on 17-12-29.
//

#ifndef DATASTRUCTURE_BINARYSORTINGTREE_H
#define DATASTRUCTURE_BINARYSORTINGTREE_H

//建立二叉排序树，二叉排序树是数据元素不重复的。内部有序，左子树小于根，右子树大于根

#include<iostream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;

//定义树结点
template<typename DataType>
struct BiTreeNode{
    DataType date;
    BiTreeNode *leftChild;
    BiTreeNode *rightChild;
};

template<typename DataType>
class BinarySortingTree
{
public:
    BinarySortingTree(DataType *arr);

    int Insert(DataType item);

    int Search(DataType item);

    void print();
    void print(BiTreeNode<DataType> *p);

    int Delete(DataType item);
    int Delete(BiTreeNode<DataType> *p,  DataType item);

    ~BinarySortingTree();

private:
    BiTreeNode<DataType> *root;

};


template<typename DataType>
BinarySortingTree<DataType>::BinarySortingTree(DataType *arr)
{
    root=NULL;
    for(int i=0;i<50;i++)
        Insert(arr[i]);
}


//在BST中插入一个节点，如果没有就不操作，item大于某个节点往右边走，小于往左边走
template<typename DataType>
int BinarySortingTree<DataType>::Insert(DataType item) {
    BiTreeNode<DataType> *current=NULL, *parent = NULL, *p;
    //BiTreeNode *current=NULL, *parent = NULL, *p;
    current=root;
    while(current!=NULL){
        if(current->date==item)         //数据已经存在，回去不进行任何操作
            return 0;
        parent=current;
        if(item > current->date)
            current=current->rightChild;//当前item大于根节点值，得往右边去找
        else
            current=current->leftChild; //当前item小于根节点值，得往左边去找
    }

    //到这里了代表在BST中没有item这个值，新建一个节点，准备插入
    p=new BiTreeNode<DataType>();

    p->date=item;
    p->leftChild=NULL;
    p->rightChild=NULL;
    if(parent==NULL)            //空树？直接插入做根节点
        root=p;
    else if(item > parent->date)
        parent->rightChild=p;   //大于前面一个节点，插再右边
    else
        parent->leftChild=p;    //小于前面一个节点，插再右边
    return 1;
}


//中序遍历输出所有结点
template<typename DataType>
void BinarySortingTree<DataType>::print() {
    print(root);    //递归输出
}
template<typename DataType>
void BinarySortingTree<DataType>::print(BiTreeNode<DataType> *p) {
    if(root==NULL)
        return;
    if(p->leftChild!=NULL)
        print(p->leftChild);
    cout<< p->date << " ";
    if(p->rightChild!=NULL)
        print(p->rightChild);
}


//二叉排序树的查找,类似与二分查找，这里是循环方法。找到了返回操作次数，否则返回0.
template<typename DataType>
int BinarySortingTree<DataType>::Search(DataType item) {
    BiTreeNode<DataType> *p;
    int count=0;
    if(root!=NULL){
        p=root;
        while(p!=NULL){
            count++;
            if(p->date == item)
                return count;       //找到了，返回查找次数
            else if(p->date < item)
                p=p->rightChild;
            else
                p=p->leftChild;
        }
    }
    return 0;                   //没找到，返回count的初始值0
}


//删除指定节点,四种情况:
// 1要删除结点无孩子结点。2只有左孩子。3只有右孩子。4都有左右孩子。
template<typename DataType>
int BinarySortingTree<DataType>::Delete(DataType item) {
    return Delete(root, item);
}
template<typename DataType>
int BinarySortingTree<DataType>::Delete(BiTreeNode<DataType> *current, DataType item) {
    BiTreeNode<DataType> *parent=NULL;
    int count=0;
    if(current!=NULL) {

        //查找
        while (current != NULL) {
            count++;
            if (current->date == item)
                break;
            parent = current;                 //记录parent
            if (item > current->date)
                current = current->rightChild;//当前item大于根节点值，得往右边去找
            else
                current = current->leftChild; //当前item小于根节点值，得往左边去找
        }

        //判断是否找到了
        if (current != NULL && current->date == item) {
            if (current->leftChild == NULL && current->rightChild == NULL) {    //无孩子结点
                if (parent->leftChild == current)
                    parent->leftChild = NULL;
                else
                    parent->rightChild = NULL;
                delete current;
            } else if (current->leftChild != NULL && current->rightChild == NULL) { //只有左孩子
                if (parent->leftChild == current)
                    parent->leftChild = current->leftChild;
                else
                    parent->rightChild = current->leftChild;
                delete current;
            } else if (current->leftChild == NULL && current->rightChild != NULL) { //只有右孩子
                if (parent->leftChild == current)
                    parent->leftChild = current->rightChild;
                else
                    parent->rightChild = current->rightChild;
                delete current;
            }
                //左右孩子都有，往右子树找最左的结点替换，然后在删原来最左的那个结点
            else if (current->leftChild != NULL && current->rightChild != NULL) {
                BiTreeNode<DataType> *temp = current->rightChild;
                while (temp->leftChild != NULL) {
                    temp = temp->leftChild;     //找最左结点
                }
                current->date = temp->date;       //替换
                Delete(current->rightChild, temp->date);
            }
            return count;
        }
    }
    return 0;
}


//析构函数，delete所有节点，释放空间
template<typename DataType>
BinarySortingTree<DataType>::~BinarySortingTree()
{

}
#endif //DATASTRUCTURE_BINARYSORTINGTREE_H
