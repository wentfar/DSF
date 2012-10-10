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

template <typename T>
void BiTree<T>::GetRoot(BiNode **p_root) const
{
	*p_root = root;
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
void BiTree<T>::Convert1(BiNode **pFirstNode, BiNode **pLastNode)
{
	if (root == NULL)
	{
		return;
	}

	BiNode *pre = NULL;
	Convert1(root, &pre);

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
void BiTree<T>::Convert1(BiNode *root, BiNode **pre)//实质为中序遍历二叉查找树，其中设置一个pre指针指向上一个节点。注意pre为引用类型。
{
	if (root != NULL)
	{
		bool flag_pre = false;
		bool flag_p = false;
		Convert1(root->LChild, pre);
		
		//线索化
		if (*pre != NULL && (*pre)->RChild == NULL) {(*pre)->RChild = root; flag_pre = true;}
		if (root->LChild == NULL) {root->LChild = *pre; flag_p = true;}
		
		//修正与线索不一致的指针
		if(flag_pre == true && root->LChild != *pre) root->LChild = *pre;
		if(flag_p == true && *pre && (*pre)->RChild != root) (*pre)->RChild = root;

		*pre = root;//更新pre

		Convert1(root->RChild, pre);
	}
}

//将二叉查找树变为有序的双向链表，要求不能创建新节点，只调整指针。
//递归解法：
//（1）如果二叉树查找树为空，不需要转换，对应双向链表的第一个节点是NULL，最后一个节点是NULL
//（2）如果二叉查找树不为空：
//	如果左子树为空，对应双向有序链表的第一个节点是根节点，左边不需要其他操作；
//	如果左子树不为空，转换左子树，二叉查找树对应双向有序链表的第一个节点就是左子树转换后双向有序链表的第一个节点，同时将根节点和左子树转换后的双向有序链表的最后一个节点连接；
//	如果右子树为空，对应双向有序链表的最后一个节点是根节点，右边不需要其他操作；
//	如果右子树不为空，对应双向有序链表的最后一个节点就是右子树转换后双向有序链表的最后一个节点，同时将根节点和右子树转换后的双向有序链表的第一个节点连接。
template <typename T>
void BiTree<T>::Convert2(BiNode **pFirstNode, BiNode **pLastNode)
{
	Convert2(root, pFirstNode, pLastNode);
}

template <typename T>
void BiTree<T>::Convert2(BiNode* root, BiNode **pFirstNode, BiNode **pLastNode)
{
	if (root == NULL)
	{
		*pFirstNode = NULL;
		*pLastNode = NULL;
	}
	BiNode *pLeftFirst, *pLeftLast, *pRightFirst, *pRightLast;  
	if (root->LChild == NULL)//处理左子树
	{
		*pFirstNode = root;
	}
	else
	{
		Convert2(root->LChild, &pLeftFirst, &pLeftLast);
		*pFirstNode = pLeftFirst;

		pLeftLast->RChild = root;
		root->LChild = pLeftLast;
	}

	if (root->RChild == NULL)//处理右子树
	{
		*pLastNode = root;
	}
	else
	{
		Convert2(root->RChild, &pRightFirst, &pRightLast);
		*pLastNode = pRightLast;

		root->RChild = pRightFirst;
		pRightFirst->LChild = root;
	}
}

//求二叉树第K层的节点个数
template <typename T>
int BiTree<T>::GetNodeNumKthLevel1(int k) const
{
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		queue<BiNode> q;
		q.push(*root);	
		while (--k)//遍历前k-1层
		{
			queue<BiNode> q_NextLayer;//清空暂存队列
			while(!q.empty())//遍历其中一层
			{
				if (q.front().LChild != NULL)
				{
					q_NextLayer.push(*(q.front().LChild));
				}

				if (q.front().RChild != NULL)
				{
					q_NextLayer.push(*(q.front().RChild));
				}
				q.pop();
			}
			q = q_NextLayer;
		}
		return q.size();
	}
}

//求二叉树第K层的节点个数
template <typename T>
int BiTree<T>::GetNodeNumKthLevel2(int k) const
{
	return GetNodeNumKthLevel2(root, k);
}

//求二叉树第K层的节点个数
//	递归解法：
//	（1）如果二叉树为空或者k<1返回0
//	（2）如果二叉树不为空并且k==1，返回1
//	（3）如果二叉树不为空且k>1，返回左子树中k-1层的节点个数与右子树k-1层节点个数之和
//	参考代码如下：
template <typename T>
int BiTree<T>::GetNodeNumKthLevel2(BiNode *pRoot, int k) const
{  
	if(pRoot == NULL || k < 1)
		return 0;
	if(pRoot != NULL && k == 1)
		return 1;
	int numLeft = GetNodeNumKthLevel2(pRoot->LChild, k-1); // 左子树中k-1层的节点个数
	int numRight = GetNodeNumKthLevel2(pRoot->RChild, k-1); // 右子树中k-1层的节点个数
	return (numLeft + numRight);
}

//求二叉树中叶子节点的个数
template <typename T>
int BiTree<T>::LeafCount() const
{
	return LeafCount(root);
}

//求二叉树中叶子节点的个数
template <typename T>
int BiTree<T>::LeafCount(BiNode *root) const
{
	if (root == NULL)
	{
		return 0;
	}
	if (root->LChild == NULL && root->RChild == NULL)
	{
		return 1;
	}
	return LeafCount(root->LChild) + LeafCount(root->RChild);
}


template <typename T>
bool BiTree<T>::StructureCmp(BiNode *pRoot2) const
{
	return StructureCmp(root, pRoot2);
}

//判断两棵二叉树是否结构相同
//	不考虑数据内容。结构相同意味着对应的左子树和对应的右子树都结构相同。
//	递归解法：
//	（1）如果两棵二叉树都为空，返回真
//	（2）如果两棵二叉树一棵为空，另一棵不为空，返回假
//	（3）如果两棵二叉树都不为空，如果对应的左子树和右子树都同构返回真，其他返回假
template <typename T>
bool BiTree<T>::StructureCmp(BiNode *pRoot1, BiNode *pRoot2) const
{
	if (pRoot1 == NULL && pRoot2 == NULL)
	{
		return true;
	}
	if (pRoot1 == NULL && pRoot2 != NULL || pRoot1 != NULL && pRoot2 == NULL)
	{
		return false;
	}
	return StructureCmp(pRoot1->LChild, pRoot2->LChild) && StructureCmp(pRoot1->RChild, pRoot2->RChild);
}

//判断二叉树是不是平衡二叉树
template <typename T>
bool BiTree<T>::IsBalanceBiTree() const
{
	int height = 0;
	return IsBalanceBiTree(root, height);
}

//判断二叉树是不是平衡二叉树
template <typename T>
bool BiTree<T>::IsBalanceBiTree(BiNode *root, int &height) const
{
	if (root == NULL)
	{	
		height = 0;
		return true;
	}
	int LHeight, RHeight;

	bool Lbal = IsBalanceBiTree(root->LChild, LHeight);
	bool Rbal = IsBalanceBiTree(root->RChild, RHeight);
	height = (LHeight > RHeight ? LHeight : RHeight) + 1;

	if (Lbal && Rbal && abs(LHeight - RHeight) <= 1)
	{
		return true;
	}
	return false;
}

//求二叉树的镜像
template <typename T>
void BiTree<T>::BiTreeMirror()
{
	BiTreeMirror(root);
}

//求二叉树的镜像
template <typename T>
void BiTree<T>::BiTreeMirror(BiNode *&root)
{
	if (root == NULL)
	{
		return;
	}

	BiNode *tmp = NULL;
	tmp = root->LChild;
	root->LChild = root->RChild;
	root->RChild = tmp;

	BiTreeMirror(root->LChild);
	BiTreeMirror(root->RChild);
}

//求二叉树中节点的最大距离
//即二叉树中相距最远的两个节点之间的距离。
template <typename T>
int BiTree<T>::GetMaxDistance() const
{
	int Left_max, Right_max;
	GetMaxDistance(root, Left_max, Right_max);
	return Left_max + Right_max;
}

//求二叉树中节点的最大距离
//即二叉树中相距最远的两个节点之间的距离。先求左子树和右子树分别的最大值。
template <typename T>
void BiTree<T>::GetMaxDistance(BiNode *pRoot, int &Left_max, int &Right_max) const
{
	int L_maxLeft, L_maxRight, R_maxLeft, R_maxRight;
	if (pRoot->LChild == NULL && pRoot->RChild == NULL)
	{
		Left_max = Right_max = 0;
	}
	else if (pRoot->LChild == NULL && pRoot->RChild != NULL)
	{
		Left_max = 0;

		GetMaxDistance(pRoot->RChild, R_maxLeft, R_maxRight);
		Right_max = (R_maxLeft>R_maxRight?R_maxLeft:R_maxRight) + 1;
	}
	else if (pRoot->LChild != NULL && pRoot->RChild == NULL)
	{
		GetMaxDistance(pRoot->LChild, L_maxLeft, L_maxRight);
		Left_max = (L_maxLeft>L_maxRight?L_maxLeft:L_maxRight) + 1;

		Right_max = 0;
	}
	else
	{
		GetMaxDistance(pRoot->LChild, L_maxLeft, L_maxRight);
		Left_max = (L_maxLeft>L_maxRight?L_maxLeft:L_maxRight) + 1;

		GetMaxDistance(pRoot->RChild, R_maxLeft, R_maxRight);
		Right_max = (R_maxLeft>R_maxRight?R_maxLeft:R_maxRight) + 1;
	}
}

template <typename T>
bool BiTree<T>::IsCompleteBinaryTree(BiNode * pRoot) const
{

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


	//BiTree<int>::BiNode *pFirst = NULL;
	//BiTree<int>::BiNode *pLast = NULL;
	//p_BiTree->Convert1(&pFirst, &pLast);
	//p_BiTree->Convert2(&pFirst, &pLast);

	//BiTree<int>::BiNode *p = pFirst;
	//while(p != NULL)
	//{
	//	cout<<p->k_data<<" ";p = p->RChild;
	//}
	//cout<<endl;

	//p = pLast;
	//while(p != NULL)
	//{
	//	cout<<p->k_data<<" ";p = p->LChild;
	//}

	while (0)
	{
		cout<<"请输入层数：";
		cin.clear();
		cin.sync();
		int k;
		cin>>k;
		//cout<<"第"<<k<<"层结点个数为："<<p_BiTree->GetNodeNumKthLevel1(k)<<endl;
		cout<<"第"<<k<<"层结点个数为："<<p_BiTree->GetNodeNumKthLevel2(k)<<endl;
	}

	cout<<"叶子节点数为："<<p_BiTree->LeafCount()<<endl;

	while (0)
	{
		cout<<"请输入树2："<<endl;
		BiTree<int> *p_BiTree2 = new BiTree<int>();
		cout<<"前序遍历：";
		p_BiTree2->VisitBiTreePreOrder();
		cout<<endl;
	
		BiTree<int>::BiNode *p_Node = new BiTree<int>::BiNode(0, NULL, NULL);
		p_BiTree2->GetRoot(&p_Node);
		cout<<"两树结构相同吗？"<<p_BiTree->StructureCmp(p_Node)<<endl;
		delete p_BiTree2;
	}

	cout<<"二叉树是否是平衡树："<<p_BiTree->IsBalanceBiTree()<<endl;

	//p_BiTree->BiTreeMirror();

	cout<<"前序遍历：";
	p_BiTree->VisitBiTreePreOrder();
	cout<<endl;

	cout<<"中序遍历：";
	p_BiTree->VisitBiTreeInOrder();
	cout<<endl;

	cout<<"后序遍历：";
	p_BiTree->VisitBiTreePostOrder();
	cout<<endl;

	cout<<"最大距离为："<<p_BiTree->GetMaxDistance()<<endl;

	delete p_BiTree;
	system("pause");
}