//
// Created by heze on 18-1-7.
//

#include <iostream>
#include "header/randPerm.h"
#define MyNull 9999999
using namespace std;

typedef struct node {
	int key;
	int value;
	struct node* next;
}Node;

template<typename DataType>
class HashTable {
public:
	//构造哈希表
	void CreatHashTable() {
		int address;
		for (int i = 0; i < numOfArray; i++) {
			address = GetHashAddress(copyArr[i]);
			Insert(copyArr[i], address);
		}
	}

	//插入
	bool Insert(DataType value, int address) {
		//哈希数组为空
		if (HashArray[address].value == MyNull) {
			HashArray[address].key = address;
			HashArray[address].value = value;
			HashArray[address].next = NULL;
		}
		else {   //数组中已被占用，用链址法构建单链表
			Node *p = &HashArray[address];

			while (p->next != NULL)
				p = p->next;

			Node *newNode = new Node;
			newNode->key = address;
			newNode->value = value;
			newNode->next = NULL;

			p->next = newNode;
		}
		return true;
	}

	//哈希函数，用值取余19得到存储数组的下标
	//即 key = H(value) = value%19
	int GetHashAddress(DataType value) {
		return value % 19;
	}

	//查找关键字，返回查找次数
	int Find(DataType value) {
		int count = 1;
		int address = GetHashAddress(value);
		if (HashArray[address].value == value)
			return count;
		else {
			Node *p = HashArray[address].next;
			while (p != NULL) {
				count++;
				if (p->value == value)
					return count;
				p = p->next;
			}
		}
		return 0;   //没找到
	}

	//删除指定数据
	int Delete(DataType value) {
		int address=GetHashAddress(value);
		Node *current, *parent = NULL,*p,*pp;
		if (Find(value) != 0) {									//在HashTable中存在这个值
			current = &HashArray[address];

			if (current->next == NULL) {						//同key存储的数据只有一个，在数组中
				current->key = MyNull;
				current->value = MyNull;
				current->next = NULL;
			}
			else {												//同key有多个数据
				parent = current;
				while (current != NULL&&current->value != value) {
					parent = current;
					current = current->next;
				}
				if (current == &HashArray[address]) {			//找到了，是第一个，在数组里面，用最后一个替换
					p = current;
					pp = current->next;
					while (current->next != NULL) {
						parent=current;
						current = current->next;
					}
					p->key = current->key;
					p->value = current->value;
					p->next = pp;
					parent->next = NULL;
				}
				else if (current != NULL&&current->next != NULL) {//找到了，在链表中间，不是尾结点
					parent->next = current->next;
				}
				else if (current->next == NULL)					//找到了，且是在链表最尾
					parent->next = NULL;
			}
			return 1;
		}
		else {
			return 0;	//哈希表中不存在这个值
		}
	}

	//构造函数
	HashTable(DataType arr[], int n) {
		copyArr = new DataType[n];
		HashArray = new Node[20];
		numOfArray = n;

		for (int i = 0; i < n; i++) {
			copyArr[i] = arr[i];			//拷贝一遍原数据
		}

		for (int i = 0; i < 20; i++) {		//初始化哈希主数组
				HashArray[i].key = MyNull;
				HashArray[i].value = MyNull;
				HashArray[i].next = NULL;
		}

		CreatHashTable();					//构建哈希表
	}

	//析构函数，回收单链表中的空间
	~HashTable() {
		Node *p, *pp;
		for (int i = 0; i < 20; i++) {
			if (HashArray[i].next != NULL) {
				p = pp = HashArray[i].next;
				while (p->next != NULL) {
					pp = p;
					p = p->next;
					delete pp;
				}
			}
		}
	}

	//显示这个HashTable
	void diaplay() {
		for (int i = 0; i < 20; i++) {
			if (HashArray[i].key != MyNull) {
				cout <<"key:"<< HashArray[i].key << "	value:" << HashArray[i].value;
				Node *p = &HashArray[i];
				while (p->next != NULL) {
					p = p->next;
					cout <<"	key:"<< p->key << "	value:" << p->value;
				}
				cout << endl;
			}
		}
	}


private:
	Node *HashArray;		//哈希数组，下标为键值key
	DataType *copyArr;		//拷贝原数组
	int numOfArray;			//数据元素个数
};


int main() {
	int arr[50];

	randPerm(50, 200, 1000, arr);    //50个，范围为从200到1000

	HashTable<int> hashTable(arr,50);

	hashTable.diaplay();			//显示HashTable


	//查找
	int search_num = 666;
	int count = 0;
	count = hashTable.Find(search_num);
	if (count!=0)
		cout << endl << "value="<<search_num << " 查找成功！";
	else
		cout << endl << "value=" << search_num << " 查找失败！";
	cout<< "查找次数为："<<count<<endl;//查找666，输出查找次数


	//删除
	if(hashTable.Delete(search_num)==0)
		cout << endl << "value=" << search_num << "不存在，删除失败"<<endl;
	else {
		cout << endl << "value=" << search_num << "删除成功"<<endl;
		cout << "删除后的数据：" << endl;
		hashTable.diaplay();
	}

}
