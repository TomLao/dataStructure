#pragma once
#include<iostream>
#include<iomanip>
#include<vector>
#include<queue>
#include"tools.h"
using namespace std;

template<class dataType>
class adjMaxtrix
{
public:
	//构造函数，初始图
	adjMaxtrix();

	//在图G中插入n个顶点信息V和e条边信息E
	void CreatGraph(dataType V[], int n, RowColWeight E[], int e);

	//输出邻接矩阵
	void print();

	//函数功能：DFS遍历，假设为非连通图的接口函数，内部会逐个顶点地调用连通图的函数。
	void DepthFirstSearch(void Visited(dataType item));

	//函数功能：BFS遍历，假设为非连通图的接口函数，内部会逐个顶点地调用连通图的函数。
	void BroadFirstSearch(void Visited(dataType item));

	//函数功能：Prim构建最小生成树,参数是开始点的下标
	int prim(int n);


	//析构函数撤销图
	~adjMaxtrix();

private:
	vector<dataType> vexs;	//顶点
	int **edge;
	int edgeNum;
	int const MAX_VEX;
	int const MAX_WEIGHT;


	//函数功能：插入一个顶点，在顶点矩阵
	//参数：新顶点
	void InsertVertex(dataType vertex);

	//函数功能：无向图插入一条边
	//参数：顶点v1和v2连接的边，权值为weight
	void InsertEdge(int v1, int v2, int weight);

	//函数功能：删除一条边，无向图
	//参数：点v1与点v2
	void DeleteEdge(int v1, int v2);

	//函数功能：取顶点v行的第一个邻接顶点
	//参数：顶点v。返回值，成功返回该行第一个顶点的列下标,失败返回-1
	int GetFirstVex(int v);

	//函数功能，取v1行v2后的下一个顶点
	//参数：v1行，v2列
	int GetNextVex(int v1, int v2);

	//函数功能：连通图的dfs，会被假设为非连通图的接口函数的逐个顶点调用
	void DFS(int v, int visited[], void Visit(dataType));

	//函数功能：连通图的bfs，会被假设为非连通图的接口函数的逐个顶点调用
	void BFS(int v, int visited[], void Visit(dataType));
};

template<class dataType>
adjMaxtrix<dataType>::adjMaxtrix() :MAX_VEX(5), MAX_WEIGHT(999999)
{
	//矩阵置空
	edge = new int *[MAX_VEX];
	for (int i = 0; i < MAX_VEX; i++) {
		edge[i] = new int[MAX_VEX];
		for (int j = 0; j < MAX_VEX; j++)
			edge[i][j] = MAX_WEIGHT;
	}
	edgeNum = 0;
}

template<class dataType>
void adjMaxtrix<dataType>::InsertVertex(dataType vertex) {
	vexs.push_back(vertex);	//向向量中添加一个点
}

template<class dataType>
void adjMaxtrix<dataType>::InsertEdge(int v1, int v2, int weight) {
	if (v1 < 0 || v1 >= vexs.size() || v2 < 0 || v2 >= vexs.size()) {
		cout << "插入边v1或v2越界";
		return;
	}
	edge[v1][v2] = edge[v2][v1] = weight;	//插入一条无向边
	edgeNum++;
}

template<class dataType>
void adjMaxtrix<dataType>::DeleteEdge(int v1, int v2) {
	if (v1 < 0 || v1 >= vexs.size() || v2 < 0 || v2 >= vexs.size()) {
		cout << "插入边v1或v2越界";
		return;
	}
	if (edge[v1][v2] == MAX_WEIGHT || edge[v2][v1] == MAX_WEIGHT || v1 == v2) {
		cout << "边不存在";
		return;
	}
	edge[v1][v2] == edge[v2][v1] == MAX_WEIGHT;	//删除边，置为最大值
	edgeNum--;
}

template<class dataType>
int adjMaxtrix<dataType>::GetFirstVex(int v) {
	int col;
	if (v < 0 || v >= vexs.size()) {
		cout << "取第一个邻接顶点参数v越界";
		return -1;
	}
	//查找v顶点的，也就是第v行的第一个有效顶点，放回其列col
	for (col = 0; col < vexs.size(); col++) {
		if (edge[v][col] != MAX_WEIGHT)
			return col;
	}
	return -1;
}

template<class dataType>
int adjMaxtrix<dataType>::GetNextVex(int v1, int v2) {
	int col;
	if (v1 < 0 || v1 >= vexs.size() || v2 < 0 || v2 >= vexs.size()) {
		cout << "参数v1或v2越界";
		return -1;
	}
	//查找v顶点的，也就是第v行的第一个有效顶点，放回其列col
	for (col = v2 + 1; col < vexs.size(); col++) {
		if (edge[v1][col] != MAX_WEIGHT)
			return col;
	}
	return -1;
}

template<class dataType>
adjMaxtrix<dataType>::~adjMaxtrix()
{
	//撤销矩阵
	for (int i = 0; i < vexs.size(); i++)
		delete[] edge[i];
}

//在图G中插入n个顶点信息V和e条边信息E
template<class dataType>
void adjMaxtrix<dataType>::CreatGraph(dataType V[], int n, RowColWeight E[], int e)
{
	int i, k;
	//Initiate(n);	//顶点顺序表初始化
	for (i = 0; i < n; i++)
		InsertVertex(V[i]);	//插入顶点
	for (k = 0; k < e; k++)
		InsertEdge(E[k].row, E[k].col, E[k].weight);//插入边
}

//输出邻接矩阵
template<class dataType>
void adjMaxtrix<dataType>::print() {
	for (int i = 0; i < vexs.size(); i++) {
		for (int j = 0; j < vexs.size(); j++) {
			cout << setw(6) << edge[i][j] << " ";
		}
		cout << endl;
	}
}

//接口的dfs，非连通图
template<class dataType>
void adjMaxtrix<dataType>::DepthFirstSearch(void Visit(dataType item)) {
	int i;
	int *visited = new int[vexs.size()];
	for (i = 0; i < vexs.size(); i++)
		visited[i] = 0;			//初始标记数组
	for (i = 0; i < vexs.size(); i++)
		if (!visited[i])
			DFS(i, visited, Visit);	//以每个顶点为初始顶点进行调用
	delete[] visited;
}

//连通图的dfs
//这里的Visit是函数当参数，为用户想要的访问操作
//参数：v为以v为初始顶点，visited[]标记是否访问过
template<class dataType>
void adjMaxtrix<dataType>::DFS(int v, int visited[], void Visit(dataType)) {
	int w;
	Visit(vexs[v]);			//访问顶点v,只是遍历顶点
	visited[v] = 1;			//标记为访问过
	w = GetFirstVex(v);		//获取第一个邻接顶点
	while (w != -1) {
		if (!visited[w])
			DFS(w, visited, Visit);	//如果没访问过，递归调用访问
		w = GetNextVex(v, w);
	}
}

//广度优先搜索
template<class dataType>
void adjMaxtrix<dataType>::BroadFirstSearch(void Visit(dataType item)) {
	int i;
	int *visited = new int[vexs.size()];
	for (i = 0; i < vexs.size(); i++)
		visited[i] = 0;
	for (i = 0; i < vexs.size(); i++)
		if (!visited[i])
			BFS(i, visited, Visit);
	delete[] visited;
}

template<class dataType>
void adjMaxtrix<dataType>::BFS(int v, int visited[], void Visit(dataType item)) {
	int u, w;
	queue<int> myQueue;			//队列
	Visit(vexs[v]);				//访问
	visited[v] = 1;
	myQueue.push(v);			//初始顶点v入队列
	while (!myQueue.empty()) {
		u = myQueue.front();	//出队列
		myQueue.pop();
		w = GetFirstVex(u);		//取顶点u的第一个邻接顶点
		while (w != -1) {
			if (!visited[w]) {
				Visit(vexs[w]);	//访问顶点w
				visited[w] = 1;	//置为已访问
				myQueue.push(w);//入队w
			}
			w = GetNextVex(u, w);
		}
	}
}

//Prim算法构建最小生成树，参照：http://blog.csdn.net/yeruby/article/details/38615045
template<class dataType>
int adjMaxtrix<dataType>::prim(int n){
	int lowcost[5];				//以lowcost[i]是以i为终点的边的最小权值
	int mst[5];					//mst[i]表示对应于lowcost[i]的起点
	int i,j,min,minid,sum=0;	//sum最小代价，min临时权值，minid临时路径
	int path[5];
	int begin=0;
	int temp;
	for(i=0;i<n;i++){
		lowcost[i]=edge[0][i];	//置lowcost为图矩阵的第一行
		mst[i]=0;				//置所有路径为1，记得改begin
	}
	mst[begin]=0;					//以下标为0开始构建最小生成树
	minid=0;
	for(i=1;i<n;i++){
		min=MAX_WEIGHT;		
		for(j=0;j<n;j++){
			if(minid!=j&&lowcost[j]<min&&lowcost[j]!=0){
				min=lowcost[j];
				minid=j;
			}
		}
		//cout<<"v"<<mst[minid]<<"-v"<<minid<<"="<<min<<endl;
		cout<<vexs[mst[minid]]<<"-"<<vexs[minid]<<"="<<min<<endl;
		sum+=min;
		lowcost[minid]=0;		//表示加入U集合，已访问过

		//这一块与上面的的一样，全部更新lowcost[]和mst[]为对应图的下一行
		temp=mst[minid];
		for(j=0;j<n;j++){			
			if(edge[minid][j]<lowcost[j]){
				lowcost[j]=edge[minid][j];
				mst[j]=minid;
			}
		}
		lowcost[temp]=0;
	}
	return sum;
}