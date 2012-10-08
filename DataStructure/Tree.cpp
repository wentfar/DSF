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
void BiTree<T>::Convert(BiNode **pFirstNode, BiNode **pLastNode)
{
	if (root == NULL)
	{
		return;
	}

	BiNode *pre = NULL;
	Convert(root, pre);

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
void BiTree<T>::Convert(BiNode *root, BiNode *&pre)//ʵ��Ϊ��������������������������һ��preָ��ָ����һ���ڵ㡣ע��preΪ�������͡�
{
	if (root != NULL)
	{
		bool flag_pre = false;
		bool flag_p = false;
		Convert(root->LChild, pre);
		
		//������
		if (pre != NULL && pre->RChild == NULL) {pre->RChild = root; flag_pre = true;}
		if (root->LChild == NULL) {root->LChild = pre; flag_p = true;}
		
		//������������һ�µ�ָ��
		if(flag_pre == true && root->LChild != pre) root->LChild = pre;
		if(flag_p == true && pre && pre->RChild != root) pre->RChild = root;

		pre = root;//����pre

		Convert(root->RChild, pre);
	}
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