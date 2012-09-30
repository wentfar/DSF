#include <iostream>
#include "Tree.h"

using namespace std;

template <typename T>
BiTree<T>::BiTree()
{
	CreatBiTree(&root);
}

template <typename T>
BiTree<T>::~BiTree()
{
	ReleaseBiTree(&root);
}

//����������
template <typename T>
void BiTree<T>::VisitBiTreePreOrder() const
{
	VisitBiTreePreOrder(root);
}

template <typename T>
void BiTree<T>::VisitBiTreeInOrder() const
{
	VisitBiTreeInOrder(root);
}

template <typename T>
void BiTree<T>::VisitBiTreePostOrder() const
{
	VisitBiTreePostOrder(root);
}

//�������Ľ�����(1)
template <typename T>
int BiTree<T>::NodeCount1() const
{
	int n = 0;
	NodeCount1(root, &n);
	return n;
}

//�������Ľ�����(2)
template <typename T>
int BiTree<T>::NodeCount2() const
{
	return NodeCount2(root);
}

template <typename T>
int BiTree<T>::TreeDepth() const
{
	return TreeDepth(root);
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
void BiTree<T>::VisitBiTreePostOrder(BiNode *root) const
{
	if (root != NULL)
	{
		VisitBiTreePostOrder(root->LChild);
		VisitBiTreePostOrder(root->RChild);
		cout<<root->k_data<<" ";
	} 
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

void main()
{
	BiTree<int> *p_BiTree = new BiTree<int>();
	p_BiTree->VisitBiTreePreOrder();
	cout<<endl;
	p_BiTree->VisitBiTreeInOrder();
	cout<<endl;
	p_BiTree->VisitBiTreePostOrder();
	cout<<endl;

	cout<<"�ڵ�����"<<p_BiTree->NodeCount1();
	cout<<endl;

	cout<<"�ڵ�����"<<p_BiTree->NodeCount1();
	cout<<endl;

	cout<<"��ȣ�"<<p_BiTree->TreeDepth();
	cout<<endl;

	delete p_BiTree;
	system("pause");
}