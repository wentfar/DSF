#ifndef Graph_h
#define Graph_h

#include <list>
using namespace std;


//�ڽӾ�������ͼ��C++����
const int DEFAULT_SIZE = 20;
enum StatusCode {SUCCESS, FAIL, UNDER_FLOW, OVER_FLOW,RANGE_ERROR, DUPLICATE_ERROR,	NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND, VISITED, UNVISITED};

template<class ElemType>
class AdjMatrixDirGraph{
protected:
	int vexNum,edgeNum;//�������Լ�����
	int** Matrix;//�ڽӾ���
	ElemType* elems;//����Ԫ��
	mutable StatusCode* tags;//��־�ڵ��Ƿ񱻷��ʹ�

	void DestroyHelp();
	void DFS(int v, void (*visit)(const ElemType&))const;


public:
	AdjMatrixDirGraph(ElemType es[], int vertexNum = DEFAULT_SIZE);// ��������Ԫ��es[],�������ΪvertexNum,����Ϊ0������ͼ
	AdjMatrixDirGraph(int vertexNum = DEFAULT_SIZE);// ���춥�����ΪvertexNum,����Ϊ0������ͼ
	~AdjMatrixDirGraph();
	AdjMatrixDirGraph(const AdjMatrixDirGraph<ElemType> &copy);	//�������캯��
	AdjMatrixDirGraph<ElemType>& operator=(const AdjMatrixDirGraph<ElemType> &copy);//���ظ�ֵ�����

	int GetVexNum() const;						// ���ض������			 
	int GetEdgeNum() const;						// ���ر�������			 
	void InsertEdge(int v1, int v2);			// ���붥��Ϊv1��v2�ı�			 
	void DeleteEdge(int v1, int v2);			// ɾ������Ϊv1��v2�ı�			 
	StatusCode GetElem(int v, ElemType &e) const;// �󶥵��Ԫ��	
	StatusCode SetElem(int v, const ElemType &e);// ���ö����Ԫ��ֵ	 
	int FirstAdjVex(int v) const;				// ���ض���v�ĵ�һ���ڽӵ�			 
	int NextAdjVex(int v1, int v2) const;		// ���ض���v1�������v2����һ���ڽӵ�			
	StatusCode GetTag(int v) const;				// ���ض���v�ı�־		 
	void SetTag(int v, StatusCode val) const;	// ���ö���v�ı�־Ϊval	

	void Display(bool showVexElem = true)const;		//��ʾͼ
	void DFSTraverse(void (*vist)(const ElemType &))const;
};

//////////////////////////////////////////////////////////////////////////

// �ڽӱ�ͼ������ģ��
template <class ElemType>
class AdjListGraphVexNode
{
protected:
	ElemType data;//��������	
	list<int> adjList;

public:
	AdjListGraphVexNode(ElemType e, list<int> adj);
	AdjListGraphVexNode();

	ElemType GetData()const;
	void SetData(ElemType e);

	list<int> GetAdjList()const;
	void SetAdjList(list<int> l);
};

// ����ͼ���ڽӱ���ģ��
template <class ElemType>
class AdjListDirGraph
{
protected:
	int vexNum, edgeNum;						// ��������ͱ���
	AdjListGraphVexNode<ElemType>* vexTable;	// �����
	mutable StatusCode* tags;					// ָ���־�����ָ��				

	void DestroyHelp();							// ��������ͼ,�ͷ�����ͼ���õĿռ�

public:
	AdjListDirGraph(ElemType es[], int vertexNum = DEFAULT_SIZE);// ���춥������Ϊes[],�������ΪvertexNum,����Ϊ0������ͼ
	AdjListDirGraph(int vertexNum = DEFAULT_SIZE);// ���춥�����ΪvertexNum,����Ϊ0������ͼ
	~AdjListDirGraph();							// ��������ģ��
	AdjListDirGraph(const AdjListDirGraph<ElemType> &copy);	// ���ƹ��캯��ģ��
	AdjListDirGraph<ElemType>& operator=(const AdjListDirGraph<ElemType> &copy);// ���ظ�ֵ�����

	StatusCode GetElem(int v, ElemType &e) const;// �󶥵��Ԫ��	
	StatusCode SetElem(int v, const ElemType &e);// ���ö����Ԫ��ֵ
	int GetVexNum() const;						// ���ض������			 
	int GetedgeNum() const;						// ���ر�������			 
	int FirstAdjVex(int v) const;				// ���ض���v�ĵ�һ���ڽӵ�			 
	int NextAdjVex(int v1, int v2) const;		// ���ض���v1�������v2����һ���ڽӵ�			 
	void InsertEdge(int v1, int v2);			// ���붥��Ϊv1��v2�ı�			 
	void DeleteEdge(int v1, int v2);			// ɾ������Ϊv1��v2�ı�			 
	StatusCode GetTag(int v) const;			// ���ض���v�ı�־		 
	void SetTag(int v, StatusCode val) const;	// ���ö���v�ı�־Ϊval		 
	void Display(bool showVexElem = true) const;
	void BFSTraverse(void (*visit)(const ElemType &))const;
};

#endif