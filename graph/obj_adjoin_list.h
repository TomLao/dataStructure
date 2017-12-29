#pragma once
#include<iostream>
#include<iomanip>
#include<vector>
#include<queue>
#include<stack>
#include"tools.h"
using namespace std;

//边结点，链表
typedef struct node {
	int dest;				//弧头顶点序号
	int weight;
	struct node* next;
}Edge;

//顶点，一个三元组,在类外定义结构体模板
template<class dataType>
struct Triple {
	dataType data;		//顶点数据元素
	int source;			//邻接边的弧尾顶点序号
	Edge* adj;			//邻接边的头指针
};

template<class dataType>
class adjList
{
public:

	adjList();

	void InsertVertex(int i, dataType vertex);

	void InsertEdge(int v1, int vw2, int weight);

	void DeleteEdge(int v1, int v2);

	int GetFirstVex(int v);

	int GetNextVex(int v1, const int v2);

	void CreatGraph(dataType V[], int n, RowColWeight E[], int e);

	void print();



	//接口的dfs，非连通图
	void DepthFirstSearch(void Visit(dataType item));

	//连通图的dfs
	//这里的Visit是函数当参数，为用户想要的访问操作
	//参数：v为以v为初始顶点，visited[]标记是否访问过
	void DFS(int v, int visited[], void Visit(dataType));

	//广度优先搜索
	void BroadFirstSearch(void Visit(dataType item));

	void BFS(int v, int visited[], void Visit(dataType item));





	~adjList();

private:

	vector<Triple<dataType>> Graph;	//邻接表向量
	int edgeNum;			//边个数3+

	int const MAX_VEX;		//最大顶点数
	int const MAX_WEIGHT;	//置权值不存在

};
template<class dataType>
adjList<dataType>::adjList() :MAX_VEX(5), MAX_WEIGHT(999999)
{
	int i;
	edgeNum = 0;
}

template<class dataType>
void adjList<dataType>::InsertVertex(int i, dataType vertex) {
	if (i >= 0 && i < MAX_VEX) {
		Triple<dataType> temp;
		temp.data = vertex;
		temp.source = Graph.size();
		temp.adj = NULL;
		Graph.push_back(temp);
	}
	else
		cout << "顶点越界";
}

template<class dataType>
void adjList<dataType>::InsertEdge(int v1, int v2, int weight) {
	Edge *p, *pp;
	if (v1 < 0 || v1 >= Graph.size() || v2 < 0 || v2 >= Graph.size()) {
		cout << "参数v1或v2越界";
		return;
	}
	p = new Edge();
	p->dest = v2;			//置邻接边的弧头序号
	p->next = Graph[v1].adj;//新结点插入单链表的表头
	p->weight = weight;

	pp = new Edge();		//因为是无向图，要插入两条边
	pp->dest = v1;
	pp->next = Graph[v2].adj;
	pp->weight = weight;

	Graph[v1].adj = p;		//头指针指向新的单链表表头
	Graph[v2].adj = pp;
	edgeNum++;
}

template<class dataType>
void adjList<dataType>::DeleteEdge(int v1, int v2) {
	Edge *current, *pre;
	if (v1 < 0 || v1 >= Graph.size() || v2 < 0 || v2 >= Graph.size()) {
		cout << "参数v1或v2越界";
		return;
	}
	pre = NULL;
	current = Graph[v1].adj;

	//在v1顶点的邻接边单链表中查找v2顶点
	while (current != NULL&&current->dest != v2) {
		pre = current;
		current = current->next;	//后移查找
	}
	//删除邻接边v1--v2，邻接边结点为单链表的第一个结点
	if (current != NULL&&current->dest == v2&&pre == NULL) {
		Graph[v1].adj = current->next;
		delete current;
		edgeNum--;
	}
	else if (current != NULL&&current->dest == v2&&pre != NULL) {//不是第一个结点
		pre->next = current->next;
		delete current;
		edgeNum--;
	}
	else
		cout << "边<v1--v2>不存在";
}

template<class dataType>
int adjList<dataType>::GetFirstVex(int v) {
	Edge* p;
	if (v < 0 || v >= Graph.size()) {
		cout << "参数v越界";
		return -1;
	}
	p = Graph[v].adj;
	if (p != NULL)
		return p->dest;			//返回该邻接顶点的对应序号
	else
		return -1;
}

template<class dataType>
int adjList<dataType>::GetNextVex(int v1, const int v2) {
	Edge* p;
	if (v1 < 0 || v1 >= Graph.size() || v2 < 0 || v2 >= Graph.size()) {
		cout << "参数v1或v2越界";
		return -1;
	}
	p = Graph[v1].adj;
	while (p != NULL) {			//寻找顶点v1的邻接顶点v2
		if (p->dest != v2) {
			p = p->next;
			continue;
		}
		else
			break;
	}
	p = p->next;				//v2的下一个顶点
	if (p != NULL)
		return p->dest;
	else
		return -1;
}

template<class dataType>
adjList<dataType>::~adjList()
{
	int i;
	Edge *p, *q;
	for (i = 0; i < Graph.size(); i++) {
		p = Graph[i].adj;
		while (p != NULL) {
			q = p->next;
			delete p;
			p = q;
		}
	}
}

template<class dataType>
void adjList<dataType>::CreatGraph(dataType V[], int n, RowColWeight E[], int e) {
	int i, j;
	for (i = 0; i < n; i++)
		InsertVertex(i, V[i]);

	for (i = 0; i < e; i++)
		InsertEdge(E[i].row, E[i].col, E[i].weight);
}

template<class dataType>
void adjList<dataType>::print() {
	Edge *p, *temp = NULL;
	stack<Edge*> reverse;
	for (int i = 0; i < Graph.size(); i++) {
		p = Graph[i].adj;
		while (p != NULL) {
			reverse.push(p);
			p = p->next;
		}
		for (int j = 0; j < Graph.size(); j++) {
			if (!reverse.empty() && temp == NULL) {
				temp = reverse.top();
				reverse.pop();
			}
			if (temp != NULL&&temp->dest == j) {
				cout << setw(6) << temp->weight << " ";
				temp = NULL;
			}
			else
				cout << setw(6) << MAX_WEIGHT << " ";
		}
		cout << endl;
	}
}

/*TODO:邻接表的dfs和bfs，暂时不做了*/

//
////接口的dfs，非连通图
//template<class dataType>
//void adjList<dataType>::DepthFirstSearch(void Visit(dataType item)) {
//	int i;
//	int *visited = new int[Graph.size()];
//	for (i = 0; i < vexs.size(); i++)
//		visited[i] = 0;			//初始标记数组
//	for (i = 0; i < vexs.size(); i++)
//		if (!visited[i])
//			DFS(i, visited, Visit);	//以每个顶点为初始顶点进行调用
//	delete[] visited;
//}
//
////连通图的dfs
////这里的Visit是函数当参数，为用户想要的访问操作
////参数：v为以v为初始顶点，visited[]标记是否访问过
//template<class dataType>
//void adjList<dataType>::DFS(int v, int visited[], void Visit(dataType)) {
//	int w;
//	Visit(vexs[v]);			//访问顶点v,只是遍历顶点
//	visited[v] = 1;			//标记为访问过
//	w = GetFirstVex(v);		//获取第一个邻接顶点
//	while (w != -1) {
//		if (!visited[w])
//			DFS(w, visited, Visit);	//如果没访问过，递归调用访问
//		w = GetNextVex(v, w);
//	}
//}
//
////广度优先搜索
//template<class dataType>
//void adjList<dataType>::BroadFirstSearch(void Visit(dataType item)) {
//	int i;
//	int *visited = new int[Graph.size()];
//	for (i = 0; i < vexs.size(); i++)
//		visited[i] = 0;
//	for (i = 0; i < vexs.size(); i++)
//		if (!visited[i])
//			BFS(i, visited, Visit);
//	delete[] visited;
//}
//
//template<class dataType>
//void adjList<dataType>::BFS(int v, int visited[], void Visit(dataType item)) {
//	int u, w;
//	queue<int> myQueue;			//队列
//	Visit(vexs[v]);				//访问
//	visited[v] = 1;
//	myQueue.push(v);			//初始顶点v入队列
//	while (!myQueue.empty()) {
//		u = myQueue.front();	//出队列
//		myQueue.pop();
//		w = GetFirstVex(u);		//取顶点u的第一个邻接顶点
//		while (w != -1) {
//			if (!visited[w]) {
//				Visit(vexs[w]);	//访问顶点w
//				visited[w] = 1;	//置为已访问
//				myQueue.push(w);//入队w
//			}
//			w = GetNextVex(u, w);
//		}
//	}
//}
//
