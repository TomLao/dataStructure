//#pragma once
////邻接矩阵存储结构,分为顶点矩阵和实际存储矩阵
////忘了的话自己去看那个图

//#include<iostream>
//#include<iomanip>
//#include<vector>
//int const MAX=100;
//int const MaxWeight=999999;
//using namespace std;
//
//typedef struct{
//	int vexnum, edgenum;//顶点数，边数
//	vector<char> vexs;	//顶点向量，一列数组
//	int edge[MAX][MAX];	//边矩阵
//}MGraph;				/*TODO：这个是图，后面还要一个结构体存这个图的信息，不知道在说什么*/
//
////初始化为有n个顶点的顶点顺序表和邻接矩阵
//void Initiate(MGraph *G, int n)
//{
//	int i, j;
//	for(i = 0; i < n; i++){
//		for(j=0;j< n;j++){
//			if(i==j)
//				G->edge[i][j]=0;
//			else
//				G->edge[i][j]=MaxWeight;
//		}
//	}
//	G->vexnum=0;
//	G->edgenum=0;
//}
//
////在图中插入一个顶点，只是加顶点，没加边，注意
//void InsertVertex(MGraph *G, int vertex)
//{
//	G->vexs.push_back(vertex);	//加入一个顶点
//	G->vexnum++;
//}
//
////插入一条无向边
//void InsertEdge(MGraph *G, int v1, int v2, int weight)
//{
//	if(v1<0||v1>=G->vexs.size()||v2<0||v2>=G->vexs.size()){
//		printf("参数v1或v2越界");
//		return;
//	}
//	G->edge[v1][v2]=weight;	//插入边，就是改变其数值，无向图要改两个
//	G->edge[v2][v1]=weight;
//	G->edgenum++;
//}
//
////删除边
//void DeleteEdge(MGraph *G, int v1, int v2)
//{
//	if(v1<0||v1>=G->vexs.size()||v2<0||v2>=G->vexs.size()){
//		printf("参数v1或v2越界");
//		return;
//	}
//	if(G->edge[v1][v2]==MaxWeight||G->edge[v2][v1]==MaxWeight||v1==v2){
//		printf("该边不存在");
//		return;
//	}
//	G->edge[v1][v2]=MaxWeight;
//	G->edge[v2][v1]=MaxWeight;
//	G->edgenum--;
//}
//
////取第一个邻接顶点
//int GetFirstVex(MGraph G, int v){
//	int col;
//	if(v<0||v>=G.vexnum){
//		printf("参数v1越界");
//		return -1;
//	}
//	for(col=0;col<G.vexnum;col++)
//		if(G.edge[v][col]>0&&G.edge[v][col]!=MaxWeight)
//			return col;
//	return -1;
//}
//
////取下一个邻接顶点
//int GetNextVex(MGraph G, int v1, int v2) {
//	int col;
//	if (v1<0 || v1 >= G.vexs.size() || v2<0 || v2 >= G.vexs.size()) {
//		printf("参数v1或v2越界");
//		return -1;
//	}
//	for (col = v2 + 1; col < G.vexs.size(); col++)
//		if (G.edge[v1][col] > 0 && G.edge[v1][col] != MaxWeight)
//			return col;
//	return -1;
//}
//
////这里开始是应用
////创建图
//typedef struct {
//	int row;
//	int col;
//	int weight;
//}RowColWeight;
//
////在图G中插入n个顶点信息V和e条边信息E
//void CreatGraph(MGraph *G, char V[], int n, RowColWeight E[], int e)
//{
//	int i, k;
//	Initiate(G, n);	//顶点顺序表初始化
//	for (i = 0; i<n; i++)
//		InsertVertex(G, V[i]);	//插入顶点
//	for (k = 0; k<e; k++)
//		InsertEdge(G, E[k].row, E[k].col, E[k].weight);//插入边
//}
//
////输出邻接矩阵
//void printAdjoinMaxtrix(MGraph G) {
//	cout << "邻接矩阵表示：" << endl;
//	for (int i = 0; i < G.vexnum; i++) {
//		for (int j = 0; j < G.vexnum; j++) {
//			cout << setw(6)<<G.edge[i][j] << " ";
//		}
//		cout << endl;
//	}
//}
