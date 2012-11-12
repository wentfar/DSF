#include <iostream>
#include "Graph.h"
#include <queue>
using namespace std;

//���춥�����ΪvertexNum,����Ϊ0������ͼ
template <class ElemType>
AdjMatrixDirGraph<ElemType>::AdjMatrixDirGraph(ElemType es[], int vertexNum = DEFAULT_SIZE){
	if(vertexNum < 0) throw "�����������Ϊ����";

	vexNum = vertexNum;
	edgeNum = 0;

	Matrix = new int*[vertexNum];//�����ڽӾ�������һ��ָ�����顣����ÿ��ָ��ָ��ÿһ���׵�ַ
	for(int i = 0; i < vertexNum; i++){
		Matrix[i] = new int[vertexNum];//���ɶ�ά�����ÿһ�С�����ÿһ�о�Ϊ��������
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

//���춥�����ΪvertexNum,����Ϊ0������ͼ
template <class ElemType>
AdjMatrixDirGraph<ElemType>::AdjMatrixDirGraph(int vertexNum = DEFAULT_SIZE){
	if(vertexNum < 0) throw "�����������Ϊ����";
	
	vexNum = vertexNum;
	edgeNum = 0;

	Matrix = new int*[vertexNum];//�����ڽӾ�������һ��ָ�����顣����ÿ��ָ��ָ��ÿһ���׵�ַ
	for(int i = 0; i < vertexNum; i++){
		Matrix[i] = new int[vertexNum];//���ɶ�ά�����ÿһ�С�����ÿһ�о�Ϊ��������
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

//����ͼ
template <class ElemType>
void AdjMatrixDirGraph<ElemType>::DestroyHelp(){
	for(int i = 0; i < vexNum; i++){
		delete[] Matrix[i];//�ͷ��ڽӾ������
	}
	delete[] Matrix;//�ͷ��ڽӾ���

	delete[] elems;

	delete[] tags;
}

template<class ElemType>
AdjMatrixDirGraph<ElemType>::~AdjMatrixDirGraph(){
	this->DestroyHelp();
}

//�������캯��
template <class ElemType>
AdjMatrixDirGraph<ElemType>::AdjMatrixDirGraph(const AdjMatrixDirGraph<ElemType> &copy){
	vexNum = copy.vexNum;
	edgeNum = copy.edgeNum;

	Matrix = new int*[vexNum];//�����ڽӾ�������һ��ָ�����顣����ÿ��ָ��ָ��ÿһ���׵�ַ
	for(int i = 0; i < vexNum; i++){
		Matrix[i] = new int[vexNum];//���ɶ�ά�����ÿһ�С�����ÿһ�о�Ϊ��������
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

// ���������������ͼ���ڽӾ���copy��ֵ����ǰ����ͼ���ڽӾ��󡪡����ظ�ֵ�����
template <class ElemType>
AdjMatrixDirGraph<ElemType>& AdjMatrixDirGraph<ElemType>::operator=(const AdjMatrixDirGraph<ElemType> &copy){
	if(this == &copy)//��������������򷵻�����
		return *this;

	DestroyHelp();//����ԭ����

	vexNum = copy.vexNum;
	edgeNum = copy.edgeNum;

	Matrix = new int*[vexNum];//�����ڽӾ�������һ��ָ�����顣����ÿ��ָ��ָ��ÿһ���׵�ַ
	for(int i = 0; i < vexNum; i++){
		Matrix[i] = new int[vexNum];//���ɶ�ά�����ÿһ�С�����ÿһ�о�Ϊ��������
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

// ������������ض������	
template <class ElemType>
int AdjMatrixDirGraph<ElemType>::GetVexNum() const{
	return vexNum;
}

// ������������ر�������
template <class ElemType>
int AdjMatrixDirGraph<ElemType>::GetEdgeNum() const{
	return edgeNum;
}

// ������������붥��Ϊv1��v2,ȨΪw�ıߡ�v1��v2�Ƕ����š�
template <class ElemType>
void AdjMatrixDirGraph<ElemType>::InsertEdge(int v1, int v2){
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ�!";
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";
	if (v1 == v2) throw "v1���ܵ���v2!";
	
	Matrix[v1][v2] = 1;//����������ͼ

	if (Matrix[v1][v2] == 0)//����������ͼ
		edgeNum++;
}

// ���������ɾ������Ϊv1��v2�ıߡ�v1��v2�Ƕ����š�
template <class ElemType>
void AdjMatrixDirGraph<ElemType>::DeleteEdge(int v1, int v2){
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ�!";
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";
	if (v1 == v2) throw "v1���ܵ���v2!";			

	Matrix[v1][v2] = 0;//����������ͼ

	if (Matrix[v1][v2] != 0)//����������ͼ
		edgeNum--;
}

// ����������󶥵�v��Ԫ��, v��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ����SUCCESS, ���򷵻�RANGE_ERROR
template <class ElemType>
StatusCode AdjMatrixDirGraph<ElemType>::GetElem(int v, ElemType &e) const{
	if (v < 0 || v >= vexNum){//v��Χ��
		return RANGE_ERROR;
	}
	else{//v�Ϸ�
		e = elems[v];
		return SUCCESS;
	}
}

// ������������ö����Ԫ��ֵv��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ����SUCCESS, ���򷵻�RANGE_ERROR
template <class ElemType>
StatusCode AdjMatrixDirGraph<ElemType>::SetElem(int v, const ElemType &e){
	if (v < 0 || v >= vexNum){// v��Χ��
		return RANGE_ERROR;
	}
	else{// v�Ϸ�
		elems[v] = e;
		return SUCCESS;
	}
}

// ������������ض���v�ĵ�1���ڽӵ�			 
template <class ElemType>
int AdjMatrixDirGraph<ElemType>::FirstAdjVex(int v) const{
	if (v < 0 || v >= vexNum) throw "v���Ϸ�!";

	for (int cur = 0; cur < vexNum; cur++){// �����ڽӵ�
		if (Matrix[v][cur] != 0) return cur;
	}
	return -1;// ����-1��ʾ���ڽӵ�
}

// ������������ض���v1�������v2����1���ڽӵ�			 
template <class ElemType>
int AdjMatrixDirGraph<ElemType>::NextAdjVex(int v1, int v2) const{
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ�!";	
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";
	if (v1 == v2) throw "v1���ܵ���v2";

	for (int cur = v2 + 1; cur < vexNum; cur++){// �����ڽӵ�
		if (Matrix[v1][cur] != 0) return cur;
	}
	return -1;// ����-1��ʾ���ڽӵ�
}

// ������������ض���v�ı�־	
template <class ElemType>
StatusCode AdjMatrixDirGraph<ElemType>::GetTag(int v) const{
	if (v < 0 || v >= vexNum) throw "v���Ϸ�!";
	return tag[v];
}

// ������������ö���v�ı�־Ϊval	
template <class ElemType>
void AdjMatrixDirGraph<ElemType>::SetTag(int v, StatusCode val) const{
	if (v < 0 || v >= vexNum) throw "v���Ϸ�!";
	tags[v] = val;
}

// �������: ��ʾ�ڽӾ�������ͼ
template <class ElemType>
void AdjMatrixDirGraph<ElemType>::Display(bool showVexElem = true)const{
	for (int i = 0; i < vexNum; i++){
		if (showVexElem)// ��ʾ����Ԫ��
			cout << elems[i];

		for (int j = 0; j < vexNum; j++)
			cout << "\t" << Matrix[i][j];

		cout << endl;
	}
}

//��ȱ����ڽӾ�������ͼ
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

//��ȱ����ڽӾ�������ͼ�����������ȸ�����
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

// �����������������Ϊitem,ָ���ڽ�����Ϊadj�Ķ���
template <class ElemType>
AdjListGraphVexNode<ElemType>::AdjListGraphVexNode(ElemType e, list<int> adj){	
	data = e;
	adjList = adj;
}

// Ĭ�ϵĹ��캯��
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

// ������������춥����ΪnumVex,��������Ϊes[],����Ϊ0������ͼ
template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(ElemType es[], int vertexNum = DEFAULT_SIZE){
	if(vertexNum < 0) throw "�����������Ϊ����";

	vexNum = vertexNum;
	edgeNum = 0;

	vexTable = new AdjListGraphVexNode<ElemType>[vertexNum];
	for(int i = 0; i < vertexNum; i++)
		vexTable[i].SetData(es[i]);

	tags = new StatusCode[vertexNum];
	for(int i = 0; i < vertexNum; i++)
		tags[i] = UNVISITED;
}

// ������������춥����ΪnumVex,����Ϊ0������ͼ
template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(int vertexNum = DEFAULT_SIZE){
	if(vertexNum < 0) throw "�����������Ϊ����";

	vexNum = vertexNum;
	edgeNum = 0;

	vexTable = new AdjListGraphVexNode<ElemType>[vertexNum];

	tags = new StatusCode[vertexNum];
	for(int i = 0; i < vertexNum; i++)
		tags[i] = UNVISITED;
}

// �����������������ͼ,�ͷ�����ͼ���õĿռ�
template <class ElemType>
void AdjListDirGraph<ElemType>::DestroyHelp(){
	delete[] vexTable;
	delete[] tags;
}

template <class ElemType>
AdjListDirGraph<ElemType>::~AdjListDirGraph(){
	DestroyHelp();
}

//�������캯��
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

// ����������󶥵�v��Ԫ��, v��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ����SUCCESS, ���򷵻�RANGE_ERROR
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

// ������������ö����Ԫ��ֵv��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ����SUCCESS, ���򷵻�RANGE_ERROR
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

// ������������ض���v�ĵ�һ���ڽӵ�	
template <class ElemType>
int AdjListDirGraph<ElemType>::FirstAdjVex(int v) const{
	if (v < 0 || v >= vexNum) throw "v���Ϸ�!";

	list<int> list_v = vexTable[v].GetAdjList();

	if (list_v.empty()){//���ڽ��������ڽӵ�
		return -1; 
	}
	else{
		list<int>::iterator it = list_v.begin();
		return *it;
	}
}

// ������������ض���v1�������v2����һ���ڽӵ�		
template <class ElemType>
int AdjListDirGraph<ElemType>::NextAdjVex(int v1, int v2) const{
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ���";
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";
	if (v1 == v2) throw "v1���ܵ���v2!";

	list<int> list_v1 = vexTable[v1].GetAdjList();

	if (list_v1.empty())// ���ڽ��������ڽӵ�
		return -1;
	else{
		list<int>::iterator it = list_v1.begin();
		for( ; it != list_v1.end() && *it != v2; it++);//����list_v1
		if(*it == v2){//�ҵ��ڽӵ�v2
			it++;
			if(it != list_v1.end())
				return *it;
			else
				return -1;
		}
		else{//δ�ҵ��ڽӵ�v2
			return -1;
		}
	}
}

// ������������붥��Ϊv1��v2�ı�		
template <class ElemType>
void AdjListDirGraph<ElemType>::InsertEdge(int v1, int v2){
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ���";
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";
	if (v1 == v2) throw "v1���ܵ���v2!";

	list<int> list_v1 = vexTable[v1].GetAdjList();

	if(list_v1.empty()){// ���ڽ��������ڽӵ�
		list_v1.push_back(v2);
		vexTable[v1].SetAdjList(list_v1);
		edgeNum++;
	}
	else{//�����Ӧv1�����ڽӱ�Ϊ��
		list<int>::iterator it = list_v1.begin();
		for( ; it != list_v1.end() && *it != v2; it++);//����list_v1
		if(it == list_v1.end()){//�����ڱ�v1-v2
			list_v1.push_back(v2);
			vexTable[v1].SetAdjList(list_v1);
			edgeNum++;
		}
	}
}

// ���������ɾ������Ϊv1��v2�ı�			 
template <class ElemType>
void AdjListDirGraph<ElemType>::DeleteEdge(int v1, int v2){
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ���";
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";
	if (v1 == v2) throw "v1���ܵ���v2!";

	list<int> list_v1 = vexTable[v1].GetAdjList();

	if(!list_v1.empty()){//�����Ӧv1�����ڽӱ�Ϊ��
		list<int>::iterator it = list_v1.begin();
		for( ; it != list_v1.end() && *it != v2; it++);//����list_v1
		if(*it == v2){//�ҵ��ڽӵ�v2
			list_v1.erase(it);
			vexTable[v1].SetAdjList(list_v1);
			edgeNum--;
		}
	}
}
	
template <class ElemType>
StatusCode AdjListDirGraph<ElemType>::GetTag(int v) const{
	if (v < 0 || v >= vexNum) throw "v���Ϸ�!";
	return tags[v];
}

template <class ElemType>
void AdjListDirGraph<ElemType>::SetTag(int v, StatusCode val) const{
	if (v < 0 || v >= vexNum) throw "v���Ϸ�!";
	tags[v] = val;
}

// �������: ��ʾ�ڽӾ�������ͼ
template <class ElemType>
void AdjListDirGraph<ElemType>::Display(bool showVexElem = true) const{
	for(int i = 0; i < vexNum; i++){//����ÿһ������
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

// �����������ͼg���й�����ȱ���
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
		char vexs[] = {'A', 'B', 'C', 'D'};//��������
		int n = sizeof(vexs)/sizeof(vexs[0]);
		int m[][4] = {
			{0, 1, 0, 1},
			{1, 0, 1, 1},
			{0, 1, 0, 1},
			{1, 1, 1, 0}
		};//�ڽӾ���

		AdjMatrixDirGraph<char> g(vexs, n);

		for (int u = 0; u < n; u++){
			for (int v = 0; v < n; v++){// �����ڽӾ���Ԫ�ص�ֵ
				if (m[u][v] == 1) g.InsertEdge(u, v);
			}
		}

		cout << "ԭ����ͼ:" << endl;
		g.Display();
		cout << endl;

		cout << "����ȱ�������ͼ:" << endl;
		g.DFSTraverse(Visit);
		cout << endl << endl;

		AdjMatrixDirGraph<char> g1(g);	// ���ƹ��캯��	
		cout << "���ƹ���ͼ:" << endl;
		g1.Display();
		cout << endl;

		g1 = g;							// ��ֵ������� 
		cout << "��ֵ������ع���ͼ:" << endl;
		g1.Display();
		cout << endl;

		g1.DeleteEdge(2, 3);			// ɾ����<2, 3>
		cout << "g1.DeleteEdge(2, 3)ִ�к�ͼΪ��" << endl;
		g1.Display();
		cout << endl;

		int v = 0;
		char e;
		g1.GetElem(v, e);				// ȡ������v��Ԫ��ֵ
		cout << "����" << e << "���ڽӵ�Ϊ:";
		for (int u = g1.FirstAdjVex(v); u != -1; u = g1.NextAdjVex(v, u)){// ��ʾv���ڽӵ���Ϣ
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

		cout << "ԭ����ͼ:" << endl;
		g.Display();
		cout << endl;

		cout << "����ȱ�������ͼ:" << endl;
		g.BFSTraverse(Visit);
		cout << endl << endl;

		AdjListDirGraph<char> g1(g);	// ���ƹ��캯��	
		cout << "���ƹ���ͼ:" << endl;
		g1.Display();
		cout << endl;

		g1 = g;							// ��ֵ������� 
		cout << "��ֵ������ع���ͼ:" << endl;
		g1.Display();
		cout << endl;

		g1.DeleteEdge(2, 3);			// ɾ����<2, 3>
		cout << "g1.DeleteEdge(2, 3)ִ�к�ͼΪ��" << endl;
		g1.Display();
		cout << endl;

		g1.InsertEdge(2, 3);			// �����<2, 3>
		cout << "g1.InsertEdge(2, 3)ִ�к�ͼΪ��" << endl;
		g1.Display();
		cout << endl;

		int v = 0;
		char e;
		g1.GetElem(v, e);				// ȡ������v��Ԫ��ֵ
		cout << "����" << e << "���ڽӵ�Ϊ:";
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