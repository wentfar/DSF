#ifndef Graph_h
#define Graph_h

#include <list>
using namespace std;

//邻接矩阵图的C描述
const int MAX_VERTEX_NUM = 20;//定义最大顶点个数
enum GraphKind{DG,DN,UDG,UDN};//有向图，有向网，无向图，无向网

//定义弧
template <class VRType, class InforType>
struct ARC 
{
	VRType adj;//权值信息。对于无权图用0,1表示；对于有权图则为权值大小
	InforType* info;//弧信息
};

//定义邻接矩阵表示的图
template<class VRType, class InforType, class VertexType>
struct MGraph 
{
	VertexType vexs[MAX_VERTEX_NUM];//顶点向量
	ARC<VRType, InforType> adjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//弧矩阵
	int vexnum, arcnum;//顶点数以及弧数
	GraphKind kind;//图的种类
};


//////////////////////////////////////////////////////////////////////////

//邻接矩阵有向图的C++描述
const int DEFAULT_SIZE = 20;
enum StatusCode {SUCCESS, FAIL, UNDER_FLOW, OVER_FLOW,RANGE_ERROR, DUPLICATE_ERROR,	NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND, VISITED, UNVISITED};

template<class ElemType>
class AdjMatrixDirGraph{
protected:
	int vexNum,edgeNum;//定点数以及弧数
	int** Matrix;//邻接矩阵
	ElemType* elems;//顶点元素
	mutable StatusCode* tags;//标志节点是否被访问过

	void DestroyHelp();
	void DFS(int v, void (*visit)(const ElemType&))const;


public:
	AdjMatrixDirGraph(ElemType es[], int vertexNum = DEFAULT_SIZE);// 构造数据元素es[],顶点个数为vertexNum,边数为0的有向图
	AdjMatrixDirGraph(int vertexNum = DEFAULT_SIZE);// 构造顶点个数为vertexNum,边数为0的有向图
	~AdjMatrixDirGraph();
	AdjMatrixDirGraph(const AdjMatrixDirGraph<ElemType> &copy);	//拷贝构造函数
	AdjMatrixDirGraph<ElemType>& operator=(const AdjMatrixDirGraph<ElemType> &copy);//重载赋值运算符

	int GetVexNum() const;						// 返回顶点个数			 
	int GetEdgeNum() const;						// 返回边数个数			 
	void InsertEdge(int v1, int v2);			// 插入顶点为v1和v2的边			 
	void DeleteEdge(int v1, int v2);			// 删除顶点为v1和v2的边			 
	StatusCode GetElem(int v, ElemType &e) const;// 求顶点的元素	
	StatusCode SetElem(int v, const ElemType &e);// 设置顶点的元素值	 
	int FirstAdjVex(int v) const;				// 返回顶点v的第一个邻接点			 
	int NextAdjVex(int v1, int v2) const;		// 返回顶点v1的相对于v2的下一个邻接点			
	StatusCode GetTag(int v) const;				// 返回顶点v的标志		 
	void SetTag(int v, StatusCode val) const;	// 设置顶点v的标志为val	

	void Display(bool showVexElem = true)const;		//显示图
	void DFSTraverse(void (*vist)(const ElemType &))const;
};

//////////////////////////////////////////////////////////////////////////

// 邻接表图顶点类模板
template <class ElemType>
class AdjListGraphVexNode
{
protected:
	ElemType data;//顶点数据	
	list<int> adjList;

public:
	AdjListGraphVexNode(ElemType e, list<int> adj);
	AdjListGraphVexNode();

	ElemType GetData()const;
	void SetData(ElemType e);

	list<int> GetAdjList()const;
	void SetAdjList(list<int> l);
};

// 有向图的邻接表类模板
template <class ElemType>
class AdjListDirGraph
{
protected:
	int vexNum, edgeNum;						// 顶点个数和边数
	AdjListGraphVexNode<ElemType>* vexTable;	// 顶点表
	mutable StatusCode* tags;					// 指向标志数组的指针				

	void DestroyHelp();							// 销毁有向图,释放有向图点用的空间

public:
	AdjListDirGraph(ElemType es[], int vertexNum = DEFAULT_SIZE);// 构造顶点数据为es[],顶点个数为vertexNum,边数为0的有向图
	AdjListDirGraph(int vertexNum = DEFAULT_SIZE);// 构造顶点个数为vertexNum,边数为0的有向图
	~AdjListDirGraph();							// 析构函数模板
	AdjListDirGraph(const AdjListDirGraph<ElemType> &copy);	// 复制构造函数模板
	AdjListDirGraph<ElemType>& operator=(const AdjListDirGraph<ElemType> &copy);// 重载赋值运算符

	StatusCode GetElem(int v, ElemType &e) const;// 求顶点的元素	
	StatusCode SetElem(int v, const ElemType &e);// 设置顶点的元素值
	int GetVexNum() const;						// 返回顶点个数			 
	int GetedgeNum() const;						// 返回边数个数			 
	int FirstAdjVex(int v) const;				// 返回顶点v的第一个邻接点			 
	int NextAdjVex(int v1, int v2) const;		// 返回顶点v1的相对于v2的下一个邻接点			 
	void InsertEdge(int v1, int v2);			// 插入顶点为v1和v2的边			 
	void DeleteEdge(int v1, int v2);			// 删除顶点为v1和v2的边			 
	StatusCode GetTag(int v) const;			// 返回顶点v的标志		 
	void SetTag(int v, StatusCode val) const;	// 设置顶点v的标志为val		 
	void Display(bool showVexElem = true) const;
	void BFSTraverse(void (*visit)(const ElemType &))const;
};

#endif