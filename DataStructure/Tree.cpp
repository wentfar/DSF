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
	else//Ҷ�ӽڵ�
	{
		*pRoot = NULL;
	}
}

template <typename T>
BiTree<T>::~BiTree()
{
	ReleaseBiTree(&root);
}

//�ͷŽ��
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


//����������
template <typename T>
void BiTree<T>::VisitBiTreePreOrder(void(*Visit)(BiNode<T> node)) const
{
	VisitBiTreePreOrder(root, Visit);
}


//����������
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
void BiTree<T>::NodeCount1(BiNode<T> *pRoot, int* count) const
{
	if (pRoot != NULL)
	{
		NodeCount1(pRoot->LChild, count);
		NodeCount1(pRoot->RChild, count);
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

//������������
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

//�ֲ����������
template <typename T>
void BiTree<T>::LevelTravel() const
{
	LevelTravel(root);
}

//�ֲ����������������δ������£��������ң�
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

//�������������Ϊ�����˫������Ҫ���ܴ����½ڵ㣬ֻ����ָ�롣
//pFirstNode: ת����˫����������ĵ�һ���ڵ�ָ��
//pLastNode: ת����˫��������������һ���ڵ�ָ��
template <typename T>
void BiTree<T>::Convert1(BiNode<T> **pFirstNode, BiNode<T> **pLastNode)
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
void BiTree<T>::Convert1(BiNode<T> *pRoot, BiNode<T> **pre)//ʵ��Ϊ��������������������������һ��preָ��ָ����һ���ڵ㡣ע��preΪ�������͡�
{
	if (pRoot != NULL)
	{
		bool flag_pre = false;
		bool flag_p = false;
		Convert1(pRoot->LChild, pre);
		
		//������
		if (*pre != NULL && (*pre)->RChild == NULL) {(*pre)->RChild = pRoot; flag_pre = true;}
		if (pRoot->LChild == NULL) {pRoot->LChild = *pre; flag_p = true;}
		
		//������������һ�µ�ָ��
		if(flag_pre == true && pRoot->LChild != *pre) pRoot->LChild = *pre;
		if(flag_p == true && *pre && (*pre)->RChild != pRoot) (*pre)->RChild = pRoot;

		*pre = pRoot;//����pre

		Convert1(pRoot->RChild, pre);
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
	if (pRoot->LChild == NULL)//����������
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

	if (pRoot->RChild == NULL)//����������
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
int BiTree<T>::GetNodeNumKthLevel2(BiNode<T> *pRoot, int k) const
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

//�ж����ö������Ƿ�ṹ��ͬ
//	�������������ݡ��ṹ��ͬ��ζ�Ŷ�Ӧ���������Ͷ�Ӧ�����������ṹ��ͬ��
//	�ݹ�ⷨ��
//	��1��������ö�������Ϊ�գ�������
//	��2��������ö�����һ��Ϊ�գ���һ�ò�Ϊ�գ����ؼ�
//	��3��������ö���������Ϊ�գ������Ӧ������������������ͬ�������棬�������ؼ�
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

//�ж϶������ǲ���ƽ�������
template <typename T>
bool BiTree<T>::IsBalanceBiTree() const
{
	int height = 0;
	return IsBalanceBiTree(root, height);
}

//�ж϶������ǲ���ƽ�������
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

//��������ľ���
template <typename T>
void BiTree<T>::BiTreeMirror()
{
	BiTreeMirror(root);
}

//��������ľ���
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

//�ж϶������ǲ�����ȫ������
//��������������Ϊh������ h ���⣬�������� (1��h-1) �Ľ�������ﵽ���������� h �����еĽ�㶼��������������ߣ��������ȫ��������
//	�������㷨������Σ����ϵ��£������ң�������������������һ���ڵ��������Ϊ��ʱ����ýڵ�����������Ϊ�գ��Һ�������Ľڵ���������������Ϊ�գ���������ȫ��������
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




//��ǰ��������к�������������ؽ�������
//	������ǰ����������У���һ��Ԫ���������ĸ��ڵ��ֵ��������������У��������Ľڵ��ֵλ�ڸ��ڵ��ֵ����ߣ��������Ľڵ��ֵλ�ڸ��ڵ��ֵ���ұߡ�
template <typename T>
void BiTree<T>::CreatBiTreeByPre_In(int PreList[], int InList[], int num, BiNode<T> **biNode)
{
	int LLen = 0;
	while(InList[LLen] != PreList[0]){LLen++;}//��ǰ��������еĵ�һ���ڵ���������������е�λ��

	//������������ǰ���������
	int LPreList[] = new int[LLen];
	int RPreList[] = new int[num - LLen - 1];
	int i = 1;
	while(i < LLen + 1){LPreList[i] = PreList[i - 1];}
	i = LLen + 1;
	while(i < num - 1){RPreList[i] = PreList[i];}

	//��������ǰ�������������
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
	cout<<"ǰ�������";
	p_BiTree->VisitBiTreePreOrder(PrintNode);
	cout<<endl;

	cout<<"���������";
	p_BiTree->VisitBiTreeInOrder(PrintNode);
	cout<<endl;

	cout<<"���������";
	p_BiTree->VisitBiTreePostOrder(PrintNode);
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
		p_BiTree2->VisitBiTreePreOrder(PrintNode);
		cout<<endl;
	
		BiNode<int> *p_Node = new BiNode<int>(0, NULL, NULL);
		p_BiTree2->GetRoot(&p_Node);
		cout<<"�����ṹ��ͬ��"<<p_BiTree->StructureCmp(p_Node)<<endl;
		delete p_BiTree2;
	}

	cout<<"�������Ƿ���ƽ������"<<p_BiTree->IsBalanceBiTree()<<endl;

	//p_BiTree->BiTreeMirror();

	cout<<"ǰ�������";
	p_BiTree->VisitBiTreePreOrder(PrintNode);
	cout<<endl;

	cout<<"���������";
	p_BiTree->VisitBiTreeInOrder(PrintNode);
	cout<<endl;

	cout<<"���������";
	p_BiTree->VisitBiTreePostOrder(PrintNode);
	cout<<endl;

	cout<<"������Ϊ��"<<p_BiTree->GetMaxDistance()<<endl;

	cout<<"�Ƿ�����ȫ��������"<<p_BiTree->IsCompleteBinaryTree()<<endl;

	//BiNode *BuildedTree;
	//p_BiTree->CreatBiTreeByPre_In();


	delete p_BiTree;


	system("pause");
}