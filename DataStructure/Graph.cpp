#include <iostream>
#include "Graph.h"
#include <queue>
using namespace std;

//构造顶点个数为vertexNum,边数为0的有向图
template <class ElemType>
AdjMatrixDirGraph<ElemType>::AdjMatrixDirGraph(ElemType es[], int vertexNum = DEFAULT_SIZE){
	if(vertexNum < 0) throw "顶点个数不能为负！";

	vexNum = vertexNum;
	edgeNum = 0;

	Matrix = new int*[vertexNum];//生成邻接矩阵，生成一个指针数组。其中每个指针指向每一行首地址
	for(int i = 0; i < vertexNum; i++){
		Matrix[i] = new int[vertexNum];//生成二维数组的每一行。其中每一行均为整形数组
		for (int j = 0; j < vertexNum; j++){
			Matrix[i][j] = 0;
		}
	}

	elems = new ElemType[vertexNum];
	for (int i = 0; i < vertexNum; i++){
		elems[i] = es[i];
	}

	tags = new StatusCode[vertexNum];
	for(int i = 0; i < vertexNum; i++){
		tags[i] = UNVISITED;
	}
}

//构造顶点个数为vertexNum,边数为0的有向图
template <class ElemType>
AdjMatrixDirGraph<ElemType>::AdjMatrixDirGraph(int vertexNum = DEFAULT_SIZE){
	if(vertexNum < 0) throw "顶点个数不能为负！";
	
	vexNum = vertexNum;
	edgeNum = 0;

	Matrix = new int*[vertexNum];//生成邻接矩阵，生成一个指针数组。其中每个指针指向每一行首地址
	for(int i = 0; i < vertexNum; i++){
		Matrix[i] = new int[vertexNum];//生成二维数组的每一行。其中每一行均为整形数组
		for (int j = 0; j < vertexNum; j++){
			Matrix[i][j] = 0;
		}
	}

	elems = new ElemType[vertexNum];
	
	tags = new StatusCode[vertexNum];
	for(int i = 0; i < vertexNum; i++){
		tags[i] = UNVISITED;
	}
}

//销毁图
template <class ElemType>
void AdjMatrixDirGraph<ElemType>::DestroyHelp(){
	for(int i = 0; i < vexNum; i++){
		delete[] Matrix[i];//释放邻接矩阵的行
	}
	delete[] Matrix;//释放邻接矩阵

	delete[] elems;

	delete[] tags;
}

template<class ElemType>
AdjMatrixDirGraph<ElemType>::~AdjMatrixDirGraph(){
	this->DestroyHelp();
}

//拷贝构造函数
template <class ElemType>
AdjMatrixDirGraph<ElemType>::AdjMatrixDirGraph(const AdjMatrixDirGraph<ElemType> &copy){
	vexNum = copy.vexNum;
	edgeNum = copy.edgeNum;

	Matrix = new int*[vexNum];//生成邻接矩阵，生成一个指针数组。其中每个指针指向每一行首地址
	for(int i = 0; i < vexNum; i++){
		Matrix[i] = new int[vexNum];//生成二维数组的每一行。其中每一行均为整形数组
		for (int j = 0; j < vexNum; j++){
			Matrix[i][j] = copy.Matrix[i][j];
		}
	}

	elems = new ElemType[vexNum];
	for (int i = 0; i < vexNum; i++){
		elems[i] = copy.elems[i];
	}

	tags = new StatusCode[vexNum];
	for(int i = 0; i < vexNum; i++){
		tags[i] = copy.tags[i];
	}
}

// 操作结果：将有向图的邻接矩阵copy赋值给当前有向图的邻接矩阵——重载赋值运算符
template <class ElemType>
AdjMatrixDirGraph<ElemType>& AdjMatrixDirGraph<ElemType>::operator=(const AdjMatrixDirGraph<ElemType> &copy){
	if(this == &copy)//如果副本是自身，则返回自身
		return *this;

	DestroyHelp();//销毁原对象

	vexNum = copy.vexNum;
	edgeNum = copy.edgeNum;

	Matrix = new int*[vexNum];//生成邻接矩阵，生成一个指针数组。其中每个指针指向每一行首地址
	for(int i = 0; i < vexNum; i++){
		Matrix[i] = new int[vexNum];//生成二维数组的每一行。其中每一行均为整形数组
		for (int j = 0; j < vexNum; j++){
			Matrix[i][j] = copy.Matrix[i][j];
		}
	}

	elems = new ElemType[vexNum];
	for (int i = 0; i < vexNum; i++){
		elems[i] = copy.elems[i];
	}

	tags = new StatusCode[vexNum];
	for(int i = 0; i < vexNum; i++){
		tags[i] = copy.tags[i];
	}

	return *this;
}

// 操作结果：返回顶点个数	
template <class ElemType>
int AdjMatrixDirGraph<ElemType>::GetVexNum() const{
	return vexNum;
}

// 操作结果：返回边数个数
template <class ElemType>
int AdjMatrixDirGraph<ElemType>::GetEdgeNum() const{
	return edgeNum;
}

// 操作结果：插入顶点为v1和v2,权为w的边。v1、v2是顶点编号。
template <class ElemType>
void AdjMatrixDirGraph<ElemType>::InsertEdge(int v1, int v2){
	if (v1 < 0 || v1 >= vexNum) throw "v1不合法!";
	if (v2 < 0 || v2 >= vexNum) throw "v2不合法!";
	if (v1 == v2) throw "v1不能等于v2!";
	
	Matrix[v1][v2] = 1;//适用于有向图

	if (Matrix[v1][v2] == 0)//适用于有向图
		edgeNum++;
}

// 操作结果：删除顶点为v1和v2的边。v1、v2是顶点编号。
template <class ElemType>
void AdjMatrixDirGraph<ElemType>::DeleteEdge(int v1, int v2){
	if (v1 < 0 || v1 >= vexNum) throw "v1不合法!";
	if (v2 < 0 || v2 >= vexNum) throw "v2不合法!";
	if (v1 == v2) throw "v1不能等于v2!";			

	Matrix[v1][v2] = 0;//适用于有向图

	if (Matrix[v1][v2] != 0)//适用于有向图
		edgeNum--;
}

// 操作结果：求顶点v的元素, v的取值范围为0 ≤ v ＜ vexNum, v合法时返回SUCCESS, 否则返回RANGE_ERROR
template <class ElemType>
StatusCode AdjMatrixDirGraph<ElemType>::GetElem(int v, ElemType &e) const{
	if (v < 0 || v >= vexNum){//v范围错
		return RANGE_ERROR;
	}
	else{//v合法
		e = elems[v];
		return SUCCESS;
	}
}

// 操作结果：设置顶点的元素值v的取值范围为0 ≤ v ＜ vexNum, v合法时返回SUCCESS, 否则返回RANGE_ERROR
template <class ElemType>
StatusCode AdjMatrixDirGraph<ElemType>::SetElem(int v, const ElemType &e){
	if (v < 0 || v >= vexNum){// v范围错
		return RANGE_ERROR;
	}
	else{// v合法
		elems[v] = e;
		return SUCCESS;
	}
}

// 操作结果：返回顶点v的第1个邻接点			 
template <class ElemType>
int AdjMatrixDirGraph<ElemType>::FirstAdjVex(int v) const{
	if (v < 0 || v >= vexNum) throw "v不合法!";

	for (int cur = 0; cur < vexNum; cur++){// 查找邻接点
		if (Matrix[v][cur] != 0) return cur;
	}
	return -1;// 返回-1表示无邻接点
}

// 操作结果：返回顶点v1的相对于v2的下1个邻接点			 
template <class ElemType>
int AdjMatrixDirGraph<ElemType>::NextAdjVex(int v1, int v2) const{
	if (v1 < 0 || v1 >= vexNum) throw "v1不合法!";	
	if (v2 < 0 || v2 >= vexNum) throw "v2不合法!";
	if (v1 == v2) throw "v1不能等于v2";

	for (int cur = v2 + 1; cur < vexNum; cur++){// 查找邻接点
		if (Matrix[v1][cur] != 0) return cur;
	}
	return -1;// 返回-1表示无邻接点
}

// 操作结果：返回顶点v的标志	
template <class ElemType>
StatusCode AdjMatrixDirGraph<ElemType>::GetTag(int v) const{
	if (v < 0 || v >= vexNum) throw "v不合法!";
	return tag[v];
}

// 操作结果：设置顶点v的标志为val	
template <class ElemType>
void AdjMatrixDirGraph<ElemType>::SetTag(int v, StatusCode val) const{
	if (v < 0 || v >= vexNum) throw "v不合法!";
	tags[v] = val;
}

// 操作结果: 显示邻接矩阵有向图
template <class ElemType>
void AdjMatrixDirGraph<ElemType>::Display(bool showVexElem = true)const{
	for (int i = 0; i < vexNum; i++){
		if (showVexElem)// 显示顶点元素
			cout << elems[i];

		for (int j = 0; j < vexNum; j++)
			cout << "\t" << Matrix[i][j];

		cout << endl;
	}
}

//深度遍历邻接矩阵有向图
template <class ElemType>
void AdjMatrixDirGraph<ElemType>::DFSTraverse(void (*visit)(const ElemType&))const{
	for(int i = 0; i < vexNum; i++){
		tags[i] = UNVISITED;
	}

	for(int i = 0; i < vexNum; i++){
		if (tags[i] == UNVISITED){
			DFS(i, visit);
		}
	}
}

//深度遍历邻接矩阵有向图，类似树的先根遍历
template <class ElemType>
void AdjMatrixDirGraph<ElemType>::DFS(int v, void (*visit)(const ElemType&))const{
	SetTag(v, VISITED);
	visit(elems[v]);
	for(int u = FirstAdjVex(v); u != -1; u = NextAdjVex(v, u)){
		if(tags[u] == UNVISITED)
			DFS(u, visit);
	}
}

template <class ElemType>
void Visit(const ElemType &e){
	cout<<e<<" ";
}

//////////////////////////////////////////////////////////////////////////

// 操作结果：构造数据为item,指向邻接链表为adj的顶点
template <class ElemType>
AdjListGraphVexNode<ElemType>::AdjListGraphVexNode(ElemType e, list<int> adj){	
	data = e;
	adjList = adj;
}

// 默认的构造函数
template <class ElemType>
AdjListGraphVexNode<ElemType>::AdjListGraphVexNode(){
}

template <class ElemType>
ElemType AdjListGraphVexNode<ElemType>::GetData() const{
	return data;
}

template <class ElemType>
void AdjListGraphVexNode<ElemType>::SetData(ElemType e){
	data = e;
}


template <class ElemType>
list<int> AdjListGraphVexNode<ElemType>::GetAdjList() const{
	return adjList;
}

template <class ElemType>
void AdjListGraphVexNode<ElemType>::SetAdjList(list<int> l){
	adjList = l;
}

// 操作结果：构造顶点数为numVex,顶点数据为es[],边数为0的有向图
template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(ElemType es[], int vertexNum = DEFAULT_SIZE){
	if(vertexNum < 0) throw "顶点个数不能为负！";

	vexNum = vertexNum;
	edgeNum = 0;

	vexTable = new AdjListGraphVexNode<ElemType>[vertexNum];
	for(int i = 0; i < vertexNum; i++)
		vexTable[i].SetData(es[i]);

	tags = new StatusCode[vertexNum];
	for(int i = 0; i < vertexNum; i++)
		tags[i] = UNVISITED;
}

// 操作结果：构造顶点数为numVex,边数为0的有向图
template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(int vertexNum = DEFAULT_SIZE){
	if(vertexNum < 0) throw "顶点个数不能为负！";

	vexNum = vertexNum;
	edgeNum = 0;

	vexTable = new AdjListGraphVexNode<ElemType>[vertexNum];

	tags = new StatusCode[vertexNum];
	for(int i = 0; i < vertexNum; i++)
		tags[i] = UNVISITED;
}

// 操作结果：销毁有向图,释放有向图点用的空间
template <class ElemType>
void AdjListDirGraph<ElemType>::DestroyHelp(){
	delete[] vexTable;
	delete[] tags;
}

template <class ElemType>
AdjListDirGraph<ElemType>::~AdjListDirGraph(){
	DestroyHelp();
}

//拷贝构造函数
template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(const AdjListDirGraph<ElemType> &copy){
	vexNum = copy.vexNum;
	edgeNum = copy.edgeNum;

	vexTable = new AdjListGraphVexNode<ElemType>[vexNum];
	for(int i = 0; i< vexNum; i++){
		vexTable[i].SetData(copy.vexTable[i].GetData());
		vexTable[i].SetAdjList(copy.vexTable[i].GetAdjList());
	}

	tags = new StatusCode[vexNum];
	for(int i = 0; i < vexNum; i++){
		tags[i] = copy.tags[i];
	}
}

template <class ElemType>
AdjListDirGraph<ElemType>& AdjListDirGraph<ElemType>::operator=(const AdjListDirGraph<ElemType> &copy){
	if(this == &copy)
		return *this;
	
	DestroyHelp();

	vexNum = copy.vexNum;
	edgeNum = copy.edgeNum;

	vexTable = new AdjListGraphVexNode<ElemType>[vexNum];
	for(int i = 0; i< vexNum; i++){
		vexTable[i].SetData(copy.vexTable[i].GetData());
		vexTable[i].SetAdjList(copy.vexTable[i].GetAdjList());
	}

	tags = new StatusCode[vexNum];
	for(int i = 0; i < vexNum; i++){
		tags[i] = copy.tags[i];
	}

	return *this;
}

// 操作结果：求顶点v的元素, v的取值范围为0 ≤ v ＜ vexNum, v合法时返回SUCCESS, 否则返回RANGE_ERROR
template <class ElemType>
StatusCode AdjListDirGraph<ElemType>::GetElem(int v, ElemType &e) const{
	if (v < 0 || v >= vexNum){
		return NOT_PRESENT;
	}
	else{
		e = vexTable[v].GetData();
		return ENTRY_FOUND;
	}
}	

// 操作结果：设置顶点的元素值v的取值范围为0 ≤ v ＜ vexNum, v合法时返回SUCCESS, 否则返回RANGE_ERROR
template <class ElemType>
StatusCode AdjListDirGraph<ElemType>::SetElem(int v, const ElemType &e){
	if (v < 0 || v >= vexNum){
		return RANGE_ERROR;
	}
	else{
		vexTable[v].SetData(e);
		return SUCCESS;
	}
}

template <class ElemType>
int AdjListDirGraph<ElemType>::GetVexNum() const{
	return vexNum;
}

template <class ElemType>
int AdjListDirGraph<ElemType>::GetedgeNum() const{
	return edgeNum;
}

// 操作结果：返回顶点v的第一个邻接点	
template <class ElemType>
int AdjListDirGraph<ElemType>::FirstAdjVex(int v) const{
	if (v < 0 || v >= vexNum) throw "v不合法!";

	list<int> list_v = vexTable[v].GetAdjList();

	if (list_v.empty()){//空邻接链表，无邻接点
		return -1; 
	}
	else{
		list<int>::iterator it = list_v.begin();
		return *it;
	}
}

// 操作结果：返回顶点v1的相对于v2的下一个邻接点		
template <class ElemType>
int AdjListDirGraph<ElemType>::NextAdjVex(int v1, int v2) const{
	if (v1 < 0 || v1 >= vexNum) throw "v1不合法！";
	if (v2 < 0 || v2 >= vexNum) throw "v2不合法!";
	if (v1 == v2) throw "v1不能等于v2!";

	list<int> list_v1 = vexTable[v1].GetAdjList();

	if (list_v1.empty())// 空邻接链表，无邻接点
		return -1;
	else{
		list<int>::iterator it = list_v1.begin();
		for( ; it != list_v1.end() && *it != v2; it++);//遍历list_v1
		if(*it == v2){//找到邻接点v2
			it++;
			if(it != list_v1.end())
				return *it;
			else
				return -1;
		}
		else{//未找到邻接点v2
			return -1;
		}
	}
}

// 操作结果：插入顶点为v1和v2的边		
template <class ElemType>
void AdjListDirGraph<ElemType>::InsertEdge(int v1, int v2){
	if (v1 < 0 || v1 >= vexNum) throw "v1不合法！";
	if (v2 < 0 || v2 >= vexNum) throw "v2不合法!";
	if (v1 == v2) throw "v1不能等于v2!";

	list<int> list_v1 = vexTable[v1].GetAdjList();

	if(list_v1.empty()){// 空邻接链表，无邻接点
		list_v1.push_back(v2);
		vexTable[v1].SetAdjList(list_v1);
		edgeNum++;
	}
	else{//如果对应v1结点的邻接表不为空
		list<int>::iterator it = list_v1.begin();
		for( ; it != list_v1.end() && *it != v2; it++);//遍历list_v1
		if(it == list_v1.end()){//不存在边v1-v2
			list_v1.push_back(v2);
			vexTable[v1].SetAdjList(list_v1);
			edgeNum++;
		}
	}
}

// 操作结果：删除顶点为v1和v2的边			 
template <class ElemType>
void AdjListDirGraph<ElemType>::DeleteEdge(int v1, int v2){
	if (v1 < 0 || v1 >= vexNum) throw "v1不合法！";
	if (v2 < 0 || v2 >= vexNum) throw "v2不合法!";
	if (v1 == v2) throw "v1不能等于v2!";

	list<int> list_v1 = vexTable[v1].GetAdjList();

	if(!list_v1.empty()){//如果对应v1结点的邻接表不为空
		list<int>::iterator it = list_v1.begin();
		for( ; it != list_v1.end() && *it != v2; it++);//遍历list_v1
		if(*it == v2){//找到邻接点v2
			list_v1.erase(it);
			vexTable[v1].SetAdjList(list_v1);
			edgeNum--;
		}
	}
}
	
template <class ElemType>
StatusCode AdjListDirGraph<ElemType>::GetTag(int v) const{
	if (v < 0 || v >= vexNum) throw "v不合法!";
	return tags[v];
}

template <class ElemType>
void AdjListDirGraph<ElemType>::SetTag(int v, StatusCode val) const{
	if (v < 0 || v >= vexNum) throw "v不合法!";
	tags[v] = val;
}

// 操作结果: 显示邻接矩阵有向图
template <class ElemType>
void AdjListDirGraph<ElemType>::Display(bool showVexElem = true) const{
	for(int i = 0; i < vexNum; i++){//遍历每一个顶点
		if(showVexElem)
			cout<<vexTable[i].GetData();

		list<int> list_v1 = vexTable[i].GetAdjList();
		if(!list_v1.empty()){
			list<int>::iterator it = list_v1.begin();
			for( ; it != list_v1.end(); it++)
				cout<<" -> "<<*it;
		}
		cout<<endl;
	}
}

// 操作结果：对图g进行广度优先遍历
template <class ElemType>
void AdjListDirGraph<ElemType>::BFSTraverse(void (*visit)(const ElemType &))const{
	for(int i = 0; i < vexNum; i++){
		tags[i] = UNVISITED;
	}

	for(int i = 0; i < vexNum; i++){
		if (tags[i] == UNVISITED){
			tags[i] = VISITED;
			visit(vexTable[i].GetData());
			queue<int> q;
			q.push(i);
			while(!q.empty()){
				int v = q.front();
				q.pop();
				for(int u = FirstAdjVex(v); u != -1; u = NextAdjVex(v, u)){
					if(tags[u] == UNVISITED){
						visit(vexTable[u].GetData());
						tags[u] = VISITED;
						q.push(u);
					}
				}
			}
		}
	}
}



void main(){
	try{
		char vexs[] = {'A', 'B', 'C', 'D'};//顶点向量
		int n = sizeof(vexs)/sizeof(vexs[0]);
		int m[][4] = {
			{0, 1, 0, 1},
			{1, 0, 1, 1},
			{0, 1, 0, 1},
			{1, 1, 1, 0}
		};//邻接矩阵

		AdjMatrixDirGraph<char> g(vexs, n);

		for (int u = 0; u < n; u++){
			for (int v = 0; v < n; v++){// 生成邻接矩阵元素的值
				if (m[u][v] == 1) g.InsertEdge(u, v);
			}
		}

		cout << "原有向图:" << endl;
		g.Display();
		cout << endl;

		cout << "按深度遍历有向图:" << endl;
		g.DFSTraverse(Visit);
		cout << endl << endl;

		AdjMatrixDirGraph<char> g1(g);	// 复制构造函数	
		cout << "复制构造图:" << endl;
		g1.Display();
		cout << endl;

		g1 = g;							// 赋值语句重载 
		cout << "赋值语句重载构造图:" << endl;
		g1.Display();
		cout << endl;

		g1.DeleteEdge(2, 3);			// 删除边<2, 3>
		cout << "g1.DeleteEdge(2, 3)执行后图为：" << endl;
		g1.Display();
		cout << endl;

		int v = 0;
		char e;
		g1.GetElem(v, e);				// 取出顶点v的元素值
		cout << "顶点" << e << "的邻接点为:";
		for (int u = g1.FirstAdjVex(v); u != -1; u = g1.NextAdjVex(v, u)){// 显示v的邻接点信息
			g1.GetElem(u, e);
			cout << e << " ";
		}
		cout << endl << endl;
	}
	catch (char* e){
		cout<<e<<endl;
	}

//////////////////////////////////////////////////////////////////////////

	try{
		char vexs[] = {'A', 'B', 'C', 'D'};
		int n = sizeof(vexs)/sizeof(vexs[0]);
		int m[][4] = {
			{0, 1, 0, 1},
			{1, 0, 1, 1},
			{0, 1, 0, 1},
			{1, 1, 1, 0}
		};

		AdjListDirGraph<char> g(vexs, n);

		int u;
		for (u = 0; u < n; u++){
			for (int v = 0; v < n; v++){
				if (m[u][v] == 1) g.InsertEdge(u, v);
			}
		}

		cout << "原有向图:" << endl;
		g.Display();
		cout << endl;

		cout << "按广度遍历有向图:" << endl;
		g.BFSTraverse(Visit);
		cout << endl << endl;

		AdjListDirGraph<char> g1(g);	// 复制构造函数	
		cout << "复制构造图:" << endl;
		g1.Display();
		cout << endl;

		g1 = g;							// 赋值语句重载 
		cout << "赋值语句重载构造图:" << endl;
		g1.Display();
		cout << endl;

		g1.DeleteEdge(2, 3);			// 删除边<2, 3>
		cout << "g1.DeleteEdge(2, 3)执行后图为：" << endl;
		g1.Display();
		cout << endl;

		g1.InsertEdge(2, 3);			// 插入边<2, 3>
		cout << "g1.InsertEdge(2, 3)执行后图为：" << endl;
		g1.Display();
		cout << endl;

		int v = 0;
		char e;
		g1.GetElem(v, e);				// 取出顶点v的元素值
		cout << "顶点" << e << "的邻接点为:";
		for (u = g1.FirstAdjVex(v); u != -1; u = g1.NextAdjVex(v, u)){
			g1.GetElem(u, e);
			cout << e << " ";
		}
		cout << endl << endl;
	}
	catch (char* err){
		cout<<err;
	}

	system("PAUSE");
}