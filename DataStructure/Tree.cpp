#include <iostream>
#include "Tree.h"
#include <queue>

using namespace std;

template <typename T>
BiTree<T>::BiTree()
{
	CreatBiTree(&root);
}

//����������
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
	else//Ҷ�ӽڵ�
	{
		*root = NULL;
	}
}

template <typename T>
BiTree<T>::~BiTree()
{
	ReleaseBiTree(&root);
}

//�ͷŽ��
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

//����������
template <typename T>
void BiTree<T>::VisitBiTreePreOrder() const
{
	VisitBiTreePreOrder(root);
}

//����������
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

//�������Ľ�����(1)
template <typename T>
int BiTree<T>::NodeCount1() const
{
	int n = 0;
	NodeCount1(root, &n);
	return n;
}

//�������Ľ�����������һ�鼴�ɵõ���
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

//�������Ľ�����(2)
template <typename T>
int BiTree<T>::NodeCount2() const
{
	return NodeCount2(root);
}

//�������Ľ������������������Ϊ�գ��������ڵ���� = �������ڵ���� + �������ڵ���� + 1��
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

//������������
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

//�ֲ����������
template <typename T>
void BiTree<T>::LevelTravel() const
{
	LevelTravel(root);
}

//�ֲ����������������δ������£��������ң�
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

//�������������Ϊ�����˫������Ҫ���ܴ����½ڵ㣬ֻ����ָ�롣
//pFirstNode: ת����˫����������ĵ�һ���ڵ�ָ��
//pLastNode: ת����˫��������������һ���ڵ�ָ��
template <typename T>
void BiTree<T>::Convert1(BiNode **pFirstNode, BiNode **pLastNode)
{
	if (root == NULL)
	{
		return;
	}

	BiNode *pre = NULL;
	Convert1(root, &pre);

	//��λͷ����β���
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
void BiTree<T>::Convert1(BiNode *root, BiNode **pre)//ʵ��Ϊ��������������������������һ��preָ��ָ����һ���ڵ㡣ע��preΪ�������͡�
{
	if (root != NULL)
	{
		bool flag_pre = false;
		bool flag_p = false;
		Convert1(root->LChild, pre);
		
		//������
		if (*pre != NULL && (*pre)->RChild == NULL) {(*pre)->RChild = root; flag_pre = true;}
		if (root->LChild == NULL) {root->LChild = *pre; flag_p = true;}
		
		//������������һ�µ�ָ��
		if(flag_pre == true && root->LChild != *pre) root->LChild = *pre;
		if(flag_p == true && *pre && (*pre)->RChild != root) (*pre)->RChild = root;

		*pre = root;//����pre

		Convert1(root->RChild, pre);
	}
}

//�������������Ϊ�����˫������Ҫ���ܴ����½ڵ㣬ֻ����ָ�롣
//�ݹ�ⷨ��
//��1�����������������Ϊ�գ�����Ҫת������Ӧ˫������ĵ�һ���ڵ���NULL�����һ���ڵ���NULL
//��2����������������Ϊ�գ�
//	���������Ϊ�գ���Ӧ˫����������ĵ�һ���ڵ��Ǹ��ڵ㣬��߲���Ҫ����������
//	�����������Ϊ�գ�ת���������������������Ӧ˫����������ĵ�һ���ڵ����������ת����˫����������ĵ�һ���ڵ㣬ͬʱ�����ڵ��������ת�����˫��������������һ���ڵ����ӣ�
//	���������Ϊ�գ���Ӧ˫��������������һ���ڵ��Ǹ��ڵ㣬�ұ߲���Ҫ����������
//	�����������Ϊ�գ���Ӧ˫��������������һ���ڵ����������ת����˫��������������һ���ڵ㣬ͬʱ�����ڵ��������ת�����˫����������ĵ�һ���ڵ����ӡ�
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
	if (root->LChild == NULL)//����������
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

	if (root->RChild == NULL)//����������
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

//���������K��Ľڵ����
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
		while (--k)//����ǰk-1��
		{
			queue<BiNode> q_NextLayer;//����ݴ����
			while(!q.empty())//��������һ��
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

//���������K��Ľڵ����
template <typename T>
int BiTree<T>::GetNodeNumKthLevel2(int k) const
{
	return GetNodeNumKthLevel2(root, k);
}

//���������K��Ľڵ����
//	�ݹ�ⷨ��
//	��1�����������Ϊ�ջ���k<1����0
//	��2�������������Ϊ�ղ���k==1������1
//	��3�������������Ϊ����k>1��������������k-1��Ľڵ������������k-1��ڵ����֮��
//	�ο��������£�
template <typename T>
int BiTree<T>::GetNodeNumKthLevel2(BiNode *pRoot, int k) const
{  
	if(pRoot == NULL || k < 1)
		return 0;
	if(pRoot != NULL && k == 1)
		return 1;
	int numLeft = GetNodeNumKthLevel2(pRoot->LChild, k-1); // ��������k-1��Ľڵ����
	int numRight = GetNodeNumKthLevel2(pRoot->RChild, k-1); // ��������k-1��Ľڵ����
	return (numLeft + numRight);
}

//���������Ҷ�ӽڵ�ĸ���
template <typename T>
int BiTree<T>::LeafCount() const
{
	return LeafCount(root);
}

//���������Ҷ�ӽڵ�ĸ���
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

//�ж����ö������Ƿ�ṹ��ͬ
//	�������������ݡ��ṹ��ͬ��ζ�Ŷ�Ӧ���������Ͷ�Ӧ�����������ṹ��ͬ��
//	�ݹ�ⷨ��
//	��1��������ö�������Ϊ�գ�������
//	��2��������ö�����һ��Ϊ�գ���һ�ò�Ϊ�գ����ؼ�
//	��3��������ö���������Ϊ�գ������Ӧ������������������ͬ�������棬�������ؼ�
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

//�ж϶������ǲ���ƽ�������
template <typename T>
bool BiTree<T>::IsBalanceBiTree() const
{
	int height = 0;
	return IsBalanceBiTree(root, height);
}

//�ж϶������ǲ���ƽ�������
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

//��������ľ���
template <typename T>
void BiTree<T>::BiTreeMirror()
{
	BiTreeMirror(root);
}

//��������ľ���
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

//��������нڵ��������
//���������������Զ�������ڵ�֮��ľ��롣
template <typename T>
int BiTree<T>::GetMaxDistance() const
{
	int Left_max, Right_max;
	GetMaxDistance(root, Left_max, Right_max);
	return Left_max + Right_max;
}

//��������нڵ��������
//���������������Զ�������ڵ�֮��ľ��롣�������������������ֱ�����ֵ��
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
	cout<<"ǰ�������";
	p_BiTree->VisitBiTreePreOrder();
	cout<<endl;

	cout<<"���������";
	p_BiTree->VisitBiTreeInOrder();
	cout<<endl;

	cout<<"���������";
	p_BiTree->VisitBiTreePostOrder();
	cout<<endl;

	cout<<"�ڵ�����"<<p_BiTree->NodeCount1();
	cout<<endl;

	cout<<"�ڵ�����"<<p_BiTree->NodeCount1();
	cout<<endl;

	cout<<"��ȣ�"<<p_BiTree->TreeDepth();
	cout<<endl;

	cout<<"����α�����";
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
		cout<<"�����������";
		cin.clear();
		cin.sync();
		int k;
		cin>>k;
		//cout<<"��"<<k<<"�������Ϊ��"<<p_BiTree->GetNodeNumKthLevel1(k)<<endl;
		cout<<"��"<<k<<"�������Ϊ��"<<p_BiTree->GetNodeNumKthLevel2(k)<<endl;
	}

	cout<<"Ҷ�ӽڵ���Ϊ��"<<p_BiTree->LeafCount()<<endl;

	while (0)
	{
		cout<<"��������2��"<<endl;
		BiTree<int> *p_BiTree2 = new BiTree<int>();
		cout<<"ǰ�������";
		p_BiTree2->VisitBiTreePreOrder();
		cout<<endl;
	
		BiTree<int>::BiNode *p_Node = new BiTree<int>::BiNode(0, NULL, NULL);
		p_BiTree2->GetRoot(&p_Node);
		cout<<"�����ṹ��ͬ��"<<p_BiTree->StructureCmp(p_Node)<<endl;
		delete p_BiTree2;
	}

	cout<<"�������Ƿ���ƽ������"<<p_BiTree->IsBalanceBiTree()<<endl;

	//p_BiTree->BiTreeMirror();

	cout<<"ǰ�������";
	p_BiTree->VisitBiTreePreOrder();
	cout<<endl;

	cout<<"���������";
	p_BiTree->VisitBiTreeInOrder();
	cout<<endl;

	cout<<"���������";
	p_BiTree->VisitBiTreePostOrder();
	cout<<endl;

	cout<<"������Ϊ��"<<p_BiTree->GetMaxDistance()<<endl;

	delete p_BiTree;
	system("pause");
}