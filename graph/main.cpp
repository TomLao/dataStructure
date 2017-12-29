#include<iostream>
//#include"adjoin_maxtrix.h"	//普通邻接矩阵
#include"obj_adjoin_maxtrix.h"	//面向对象邻接矩阵
#include"obj_adjoin_list.h"		//面向对象邻接表
using namespace std;

void Visit(char temp) {
	cout << setw(4) << temp << " ";
}

int main20171228()
{
	char a[] = { 'A','B','C','D','E' };	//顶点
	RowColWeight rcw[] = { { 0,1,10 },{ 0,4,20 },{ 1,2,40 },{ 1,3,30 },{ 3,2,50 } };

	//普通邻接矩阵图
	//MGraph G;
	//CreatGraph(&G, a, 5, rcw, 5);
	//printAdjoinMaxtrix(G);

	////面向对象邻接矩阵
	adjMaxtrix<char> aMaxtrix;
	aMaxtrix.CreatGraph(a, 5, rcw, 5);
	cout << "深度优先遍历顶点：";
	aMaxtrix.DepthFirstSearch(Visit);			//深度优先遍历顶点
	cout << endl;
	cout << "广度优先遍历顶点：";
	aMaxtrix.BroadFirstSearch(Visit);			//广度优先遍历顶点
	cout << endl;
	cout << "邻接矩阵："<<endl;
	aMaxtrix.print();
	cout<<"Prim构建最小生成树的路径为："<<endl;
	cout<<"最小路径权值为："<<aMaxtrix.prim(5);

	//面向对象邻接表
//	adjList<char> aList;
//	aList.CreatGraph(a, 5, rcw, 5);				//创建图
//	//cout << "深度优先遍历顶点：";
//	//aList.DepthFirstSearch(Visit);			//深度优先遍历顶点
//	//cout << endl;
//	//cout << "广度优先遍历顶点：";
//	//aList.BroadFirstSearch(Visit);			//广度优先遍历顶点
//	cout << endl;
//	cout <<endl<< "邻接表："<<endl;
//	aList.print();
	return 0;
}