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
void BiTree<T>::CreatBiTree(BiNode<T> **pRoot)
{
	T data;
	cin.clear();
	cin.sync();
	if(cin>>data)
	{
		*pRoot = new BiNode<T>(data, NULL, NULL);
		if (*pRoot != NULL)
		{
			CreatBiTree(&((*pRoot)->LChild));
			CreatBiTree(&((*pRoot)->RChild));
		}
		else
		{
			exit(-1);
		}
	}
	else//叶子节点
	{
		*pRoot = NULL;
	}
}

template <typename T>
BiTree<T>::~BiTree()
{
	ReleaseBiTree(&root);
}

//释放结点
template <typename T>
void BiTree<T>::ReleaseBiTree(BiNode<T> **pRoot)
{
	if (*pRoot != NULL)
	{
		ReleaseBiTree(&(*pRoot)->LChild);
		ReleaseBiTree(&(*pRoot)->RChild);
		delete (*pRoot);
	}
}

template <typename T>
void BiTree<T>::GetRoot(BiNode<T> **pRoot) const
{
	*pRoot = root;
}

template <typename T>
void PrintNode(BiNode<T> node)
{
	cout<<node.k_data<<" ";
}


//遍历二叉树
template <typename T>
void BiTree<T>::VisitBiTreePreOrder(void(*Visit)(BiNode<T> node)) const
{
	VisitBiTreePreOrder(root, Visit);
}


//遍历二叉树
template <typename T>
void BiTree<T>::VisitBiTreePreOrder(BiNode<T> *pRoot, void(*Visit)(BiNode<T> node)) const
{
	if (pRoot != NULL)
	{
		Visit(*pRoot);
		VisitBiTreePreOrder(pRoot->LChild, Visit);
		VisitBiTreePreOrder(pRoot->RChild, Visit);
	} 
}

template <typename T>
void BiTree<T>::VisitBiTreeInOrder(void(*Visit)(BiNode<T> node)) const
{
	VisitBiTreeInOrder(root, Visit);
}

template <typename T>
void BiTree<T>::VisitBiTreeInOrder(BiNode<T> *pRoot, void(*Visit)(BiNode<T> node)) const
{
	if (pRoot != NULL)
	{
		VisitBiTreeInOrder(pRoot->LChild, Visit);
		Visit(*pRoot);
		VisitBiTreeInOrder(pRoot->RChild, Visit);
	} 
}

template <typename T>
void BiTree<T>::VisitBiTreePostOrder(void(*Visit)(BiNode<T> node)) const
{
	VisitBiTreePostOrder(root, Visit);
}

template <typename T>
void BiTree<T>::VisitBiTreePostOrder(BiNode<T> *pRoot, void(*Visit)(BiNode<T> node)) const
{
	if (pRoot != NULL)
	{
		VisitBiTreePostOrder(pRoot->LChild, Visit);
		VisitBiTreePostOrder(pRoot->RChild, Visit);
		Visit(*pRoot);
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
void BiTree<T>::NodeCount1(BiNode<T> *pRoot, int* count) const
{
	if (pRoot != NULL)
	{
		NodeCount1(pRoot->LChild, count);
		NodeCount1(pRoot->RChild, count);
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
int BiTree<T>::NodeCount2(BiNode<T> *pRoot) const
{
	if (pRoot != NULL)
	{
		return NodeCount2(pRoot->LChild) + NodeCount2(pRoot->RChild) + 1;
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
int BiTree<T>::TreeDepth(BiNode<T> *pRoot) const
{
	if (pRoot != NULL)
	{
		int LDepth = TreeDepth(pRoot->LChild);
		int RDepth = TreeDepth(pRoot->RChild);
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
void BiTree<T>::LevelTravel(BiNode<T> *pRoot) const
{
	queue<BiNode<T>> q;
	if(pRoot != NULL) q.push(*pRoot);
	while(!q.empty())
	{
		BiNode<T> biNode = q.front();
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
void BiTree<T>::Convert1(BiNode<T> **pFirstNode, BiNode<T> **pLastNode)
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
void BiTree<T>::Convert1(BiNode<T> *pRoot, BiNode<T> **pre)//实质为中序遍历二叉查找树，其中设置一个pre指针指向上一个节点。注意pre为引用类型。
{
	if (pRoot != NULL)
	{
		bool flag_pre = false;
		bool flag_p = false;
		Convert1(pRoot->LChild, pre);
		
		//线索化
		if (*pre != NULL && (*pre)->RChild == NULL) {(*pre)->RChild = pRoot; flag_pre = true;}
		if (pRoot->LChild == NULL) {pRoot->LChild = *pre; flag_p = true;}
		
		//修正与线索不一致的指针
		if(flag_pre == true && pRoot->LChild != *pre) pRoot->LChild = *pre;
		if(flag_p == true && *pre && (*pre)->RChild != pRoot) (*pre)->RChild = pRoot;

		*pre = pRoot;//更新pre

		Convert1(pRoot->RChild, pre);
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
void BiTree<T>::Convert2(BiNode<T> **pFirstNode, BiNode<T> **pLastNode)
{
	Convert2(root, pFirstNode, pLastNode);
}

template <typename T>
void BiTree<T>::Convert2(BiNode<T> *pRoot, BiNode<T> **pFirstNode, BiNode<T> **pLastNode)
{
	if (pRoot == NULL)
	{
		*pFirstNode = NULL;
		*pLastNode = NULL;
	}
	BiNode *pLeftFirst, *pLeftLast, *pRightFirst, *pRightLast;  
	if (pRoot->LChild == NULL)//处理左子树
	{
		*pFirstNode = pRoot;
	}
	else
	{
		Convert2(pRoot->LChild, &pLeftFirst, &pLeftLast);
		*pFirstNode = pLeftFirst;

		pLeftLast->RChild = pRoot;
		pRoot->LChild = pLeftLast;
	}

	if (pRoot->RChild == NULL)//处理右子树
	{
		*pLastNode = pRoot;
	}
	else
	{
		Convert2(root->RChild, &pRightFirst, &pRightLast);
		*pLastNode = pRightLast;

		root->RChild = pRightFirst;
		pRightFirst->LChild = pRoot;
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
int BiTree<T>::GetNodeNumKthLevel2(BiNode<T> *pRoot, int k) const
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
int BiTree<T>::LeafCount(BiNode<T> *pRoot) const
{
	if (pRoot == NULL)
	{
		return 0;
	}
	if (pRoot->LChild == NULL && pRoot->RChild == NULL)
	{
		return 1;
	}
	return LeafCount(pRoot->LChild) + LeafCount(pRoot->RChild);
}


template <typename T>
bool BiTree<T>::StructureCmp(BiNode<T> *pRoot2) const
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
bool BiTree<T>::StructureCmp(BiNode<T> *pRoot1, BiNode<T> *pRoot2) const
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
bool BiTree<T>::IsBalanceBiTree(BiNode<T> *pRoot, int &height) const
{
	if (pRoot == NULL)
	{	
		height = 0;
		return true;
	}
	int LHeight, RHeight;

	bool Lbal = IsBalanceBiTree(pRoot->LChild, LHeight);
	bool Rbal = IsBalanceBiTree(pRoot->RChild, RHeight);
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
void BiTree<T>::BiTreeMirror(BiNode<T> *&pRoot)
{
	if (pRoot == NULL)
	{
		return;
	}

	BiNode *tmp = NULL;
	tmp = pRoot->LChild;
	pRootpRootLChild = pRoot->RChild;
	pRoot->RChild = tmp;

	BiTreeMirror(pRoot->LChild);
	BiTreeMirror(pRoot->RChild);
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
void BiTree<T>::GetMaxDistance(BiNode<T> *pRoot, int &Left_max, int &Right_max) const
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
bool BiTree<T>::IsCompleteBinaryTree() const
{
	return IsCompleteBinaryTree(root);
}

//判断二叉树是不是完全二叉树
//若设二叉树的深度为h，除第 h 层外，其它各层 (1～h-1) 的结点数都达到最大个数，第 h 层所有的结点都连续集中在最左边，这就是完全二叉树。
//	有如下算法，按层次（从上到下，从左到右）遍历二叉树，当遇到一个节点的左子树为空时，则该节点右子树必须为空，且后面遍历的节点左右子树都必须为空，否则不是完全二叉树。
template <typename T>
bool BiTree<T>::IsCompleteBinaryTree(BiNode<T> *pRoot) const
{
	if (pRoot == NULL)
	{
		return true;
	}

	bool MustHasNoChild = false;
	queue<BiNode<T>> q;
	q.push(*pRoot);
	while(!q.empty())
	{
		BiNode<T> Cur = q.front();
		q.pop();
		if (MustHasNoChild)
		{
			if (Cur.LChild != NULL || Cur.RChild != NULL)
			{
				return false;
			}
		}
		else
		{
			if (Cur.LChild != NULL && Cur.RChild != NULL)
			{
				q.push(*(Cur.LChild));
				q.push(*(Cur.RChild));
			} 
			else if(Cur.LChild != NULL && Cur.RChild == NULL)
			{
				MustHasNoChild = true;
				q.push(*(Cur.LChild));
			}
			else if (Cur.LChild == NULL && Cur.RChild == NULL)
			{
				MustHasNoChild = true;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}




//由前序遍历序列和中序遍历序列重建二叉树
//	二叉树前序遍历序列中，第一个元素总是树的根节点的值。中序遍历序列中，左子树的节点的值位于根节点的值的左边，右子树的节点的值位于根节点的值的右边。
template <typename T>
void BiTree<T>::CreatBiTreeByPre_In(int PreList[], int InList[], int num, BiNode<T> **biNode)
{
	int LLen = 0;
	while(InList[LLen] != PreList[0]){LLen++;}//求前序遍历序列的第一个节点在中序遍历序列中的位置

	//求左、右子树的前序遍历数组
	int LPreList[] = new int[LLen];
	int RPreList[] = new int[num - LLen - 1];
	int i = 1;
	while(i < LLen + 1){LPreList[i] = PreList[i - 1];}
	i = LLen + 1;
	while(i < num - 1){RPreList[i] = PreList[i];}

	//求右子树前序、中序遍历数组
	int LInList[] = new int[LLen];
	int RInList[] = new int[num - Ln - 1];
	i = 0;
	while(i < LLen){LInList[i] = InList[i];}
	i = LLen + 1;
	while(i < num - 1){RInList[i] = InList[i];}

	BiNode *LChild = NULL;
	BiNode *RChild = NULL;

	BiNode* biNode = new BiNode(0, NULL, NULL);
	biNode->k_data = PreList[0];
	CreatBiTreeByPre_In(LPreList, LInList, LLen, &LChild);
	biNode->LChild = LChild;
	CreatBiTreeByPre_In(RPreList, RInList, num - LLen - 1, &RChild);
	biNode->RChild = RChild;

	delete[] LPreList;
	delete[] RPreList;
	delete[] LInList;
	delete[] RInList;

	return biNode;
}


void main()
{
	BiTree<int> *p_BiTree = new BiTree<int>();
	cout<<"前序遍历：";
	p_BiTree->VisitBiTreePreOrder(PrintNode);
	cout<<endl;

	cout<<"中序遍历：";
	p_BiTree->VisitBiTreeInOrder(PrintNode);
	cout<<endl;

	cout<<"后序遍历：";
	p_BiTree->VisitBiTreePostOrder(PrintNode);
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
		p_BiTree2->VisitBiTreePreOrder(PrintNode);
		cout<<endl;
	
		BiNode<int> *p_Node = new BiNode<int>(0, NULL, NULL);
		p_BiTree2->GetRoot(&p_Node);
		cout<<"两树结构相同吗？"<<p_BiTree->StructureCmp(p_Node)<<endl;
		delete p_BiTree2;
	}

	cout<<"二叉树是否是平衡树："<<p_BiTree->IsBalanceBiTree()<<endl;

	//p_BiTree->BiTreeMirror();

	cout<<"前序遍历：";
	p_BiTree->VisitBiTreePreOrder(PrintNode);
	cout<<endl;

	cout<<"中序遍历：";
	p_BiTree->VisitBiTreeInOrder(PrintNode);
	cout<<endl;

	cout<<"后序遍历：";
	p_BiTree->VisitBiTreePostOrder(PrintNode);
	cout<<endl;

	cout<<"最大距离为："<<p_BiTree->GetMaxDistance()<<endl;

	cout<<"是否是完全二叉树："<<p_BiTree->IsCompleteBinaryTree()<<endl;

	//BiNode *BuildedTree;
	//p_BiTree->CreatBiTreeByPre_In();


	delete p_BiTree;


	system("pause");
}