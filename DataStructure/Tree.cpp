#include <iostream>
#include "Tree.h"
#include <queue>

using namespace std;

template <typename T>
BiTree<T>::BiTree()
{
	CreatBiTree(&root);
}

//创建二叉树
template <typename T>
void BiTree<T>::CreatBiTree(BiNode **root)
{
	T data;
	cin.clear();
	cin.sync();
	if(cin>>data)
	{
		*root = new BiNode(data, NULL, NULL);
		if (*root != NULL)
		{
			CreatBiTree(&((*root)->LChild));
			CreatBiTree(&((*root)->RChild));
		}
		else
		{
			exit(-1);
		}
	}
	else//叶子节点
	{
		*root = NULL;
	}
}

template <typename T>
BiTree<T>::~BiTree()
{
	ReleaseBiTree(&root);
}

//释放结点
template <typename T>
void BiTree<T>::ReleaseBiTree(BiNode **root)
{
	if (*root != NULL)
	{
		ReleaseBiTree(&(*root)->LChild);
		ReleaseBiTree(&(*root)->RChild);
		delete (*root);
	}
}

//遍历二叉树
template <typename T>
void BiTree<T>::VisitBiTreePreOrder() const
{
	VisitBiTreePreOrder(root);
}

//遍历二叉树
template <typename T>
void BiTree<T>::VisitBiTreePreOrder(BiNode *root) const
{
	if (root != NULL)
	{
		cout<<root->k_data<<" ";
		VisitBiTreePreOrder(root->LChild);
		VisitBiTreePreOrder(root->RChild);
	} 
}

template <typename T>
void BiTree<T>::VisitBiTreeInOrder() const
{
	VisitBiTreeInOrder(root);
}

template <typename T>
void BiTree<T>::VisitBiTreeInOrder(BiNode *root) const
{
	if (root != NULL)
	{
		VisitBiTreeInOrder(root->LChild);
		cout<<root->k_data<<" ";
		VisitBiTreeInOrder(root->RChild);
	} 
}

template <typename T>
void BiTree<T>::VisitBiTreePostOrder() const
{
	VisitBiTreePostOrder(root);
}

template <typename T>
void BiTree<T>::VisitBiTreePostOrder(BiNode *root) const
{
	if (root != NULL)
	{
		VisitBiTreePostOrder(root->LChild);
		VisitBiTreePostOrder(root->RChild);
		cout<<root->k_data<<" ";
	} 
}

//二叉树的结点计数(1)
template <typename T>
int BiTree<T>::NodeCount1() const
{
	int n = 0;
	NodeCount1(root, &n);
	return n;
}

//二叉树的结点计数。遍历一遍即可得到。
template <typename T>
void BiTree<T>::NodeCount1(BiNode *root, int* count) const
{
	if (root != NULL)
	{
		NodeCount1(root->LChild, count);
		NodeCount1(root->RChild, count);
		(*count)++;
	} 
}

//二叉树的结点计数(2)
template <typename T>
int BiTree<T>::NodeCount2() const
{
	return NodeCount2(root);
}

//二叉树的结点计数。如果二叉树不为空，二叉树节点个数 = 左子树节点个数 + 右子树节点个数 + 1。
template <typename T>
int BiTree<T>::NodeCount2(BiNode *root) const
{
	if (root != NULL)
	{
		return NodeCount2(root->LChild) + NodeCount2(root->RChild) + 1;
	} 
	else
	{
		return 0;
	}
}

//求二叉树的深度
template <typename T>
int BiTree<T>::TreeDepth() const
{
	return TreeDepth(root);
}

template <typename T>
int BiTree<T>::TreeDepth(BiNode *root) const
{
	if (root != NULL)
	{
		int LDepth = TreeDepth(root->LChild);
		int RDepth = TreeDepth(root->RChild);
		return (LDepth>RDepth?LDepth:RDepth) + 1; 
	} 
	else
	{
		return 0;
	}
}

//分层遍历二叉树
template <typename T>
void BiTree<T>::LevelTravel() const
{
	LevelTravel(root);
}

//分层遍历二叉树（按层次从上往下，从左往右）
template <typename T>
void BiTree<T>::LevelTravel(BiNode *root) const
{
	queue<BiNode> q;
	if(root != NULL) q.push(*root);
	while(!q.empty())
	{
		BiNode biNode = q.front();
		cout<<biNode.k_data<<" ";
		q.pop();
		if (biNode.LChild != NULL)
		{
			q.push(*(biNode.LChild));
		}
		if (biNode.RChild != NULL)
		{
			q.push(*(biNode.RChild));
		}
	}
}

//将二叉查找树变为有序的双向链表，要求不能创建新节点，只调整指针。
//pFirstNode: 转换后双向有序链表的第一个节点指针
//pLastNode: 转换后双向有序链表的最后一个节点指针
template <typename T>
void BiTree<T>::Convert(BiNode **pFirstNode, BiNode **pLastNode)
{
	if (root == NULL)
	{
		return;
	}

	BiNode *pre = NULL;
	Convert(root, pre);

	//定位头结点和尾结点
	BiNode *p = root;
	while(p->LChild != NULL)
	{
		p = p->LChild;
	}
	*pFirstNode = p;

	p = root;
	while(p->RChild != NULL)
	{
		p = p->RChild;
	}
	*pLastNode = p;
}


template <typename T>
void BiTree<T>::Convert(BiNode *root, BiNode *&pre)//实质为中序遍历二叉查找树，其中设置一个pre指针指向上一个节点。注意pre为引用类型。
{
	if (root != NULL)
	{
		bool flag_pre = false;
		bool flag_p = false;
		Convert(root->LChild, pre);
		
		//线索化
		if (pre != NULL && pre->RChild == NULL) {pre->RChild = root; flag_pre = true;}
		if (root->LChild == NULL) {root->LChild = pre; flag_p = true;}
		
		//修正与线索不一致的指针
		if(flag_pre == true && root->LChild != pre) root->LChild = pre;
		if(flag_p == true && pre && pre->RChild != root) pre->RChild = root;

		pre = root;//更新pre

		Convert(root->RChild, pre);
	}
}

void main()
{
	BiTree<int> *p_BiTree = new BiTree<int>();
	cout<<"前序遍历：";
	p_BiTree->VisitBiTreePreOrder();
	cout<<endl;

	cout<<"中序遍历：";
	p_BiTree->VisitBiTreeInOrder();
	cout<<endl;

	cout<<"后序遍历：";
	p_BiTree->VisitBiTreePostOrder();
	cout<<endl;

	cout<<"节点数："<<p_BiTree->NodeCount1();
	cout<<endl;

	cout<<"节点数："<<p_BiTree->NodeCount1();
	cout<<endl;

	cout<<"深度："<<p_BiTree->TreeDepth();
	cout<<endl;

	cout<<"按层次遍历：";
	p_BiTree->LevelTravel();
	cout<<endl;


	BiTree<int>::BiNode *pFirst = NULL;
	BiTree<int>::BiNode *pLast = NULL;
	p_BiTree->Convert(&pFirst, &pLast);

	BiTree<int>::BiNode *p = pFirst;
	while(p != NULL)
	{
		cout<<p->k_data<<" ";p = p->RChild;
	}
	cout<<endl;

	p = pLast;
	while(p != NULL)
	{
		cout<<p->k_data<<" ";p = p->LChild;
	}

	//delete p_BiTree;
	system("pause");
}