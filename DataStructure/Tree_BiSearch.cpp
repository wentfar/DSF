#include <iostream>
using namespace std;

template <typename T>
struct BiNode{
	T k_data;
	BiNode<T> *LChild, *RChild;
	BiNode<T> *Parent;
	BiNode(T element, BiNode<T> *lt, BiNode<T> *rt, BiNode<T> *pt):k_data(element), LChild(lt), RChild(rt), Parent(pt){}
};


//��ӡ�ڵ�
template <typename T>
void PrintNode(BiNode<T> node)
{
	cout<<node.k_data<<" ";
}

template <typename T>
class BiSearchTree
{
public:
	BiSearchTree(BiNode<T>* pRoot = NULL)
	{
		root = pRoot;
	}

	~BiSearchTree()
	{
		ReleaseBiTree(&root);
	}

	void ReleaseBiTree(BiNode<T> **pRoot)
	{
		if (*pRoot != NULL)
		{
			ReleaseBiTree(&(*pRoot)->LChild);
			ReleaseBiTree(&(*pRoot)->RChild);
			delete (*pRoot);
		}
	}

	//ǰ�����������
	void VisitBiTreePreOrder(void(*Visit)(BiNode<T>)) const
	{
		VisitBiTreePreOrder(root, Visit);
	}

	//�������������
	void VisitBiTreeInOrder(void(*Visit)(BiNode<T>)) const
	{
		VisitBiTreeInOrder(root, Visit);
	}

	//���ң��ҵ��򷵻ؽڵ㣬���򷵻ؿ�
	BiNode<T>* Search(T key) const
	{
		return Search(root, key);
	}

	//���룬����Ѿ��д˽ڵ㣬�򷵻�false���������ڵ㣬����true
	bool Insert(T key)
	{
		BiNode<T>* p_newNode = new BiNode<T>(key, NULL, NULL, NULL);
		if (root == NULL)//����
		{
			root = p_newNode;
		}
		BiNode<T>* p = root;
		BiNode<T>* location = NULL;//key�Ĳ���λ��
		while(p != NULL)//����key
		{
			location = p;
			if (p->k_data > key)
			{
				p = p->LChild;
			} 
			else if(p->k_data < key)
			{
				p = p->RChild;
			}
			else
			{
				break;
			}
		}

		if (p == NULL)//δ�ҵ�key
		{
			p_newNode->Parent = location;
			if (location->k_data > key)
			{
				location->LChild = p_newNode;
			} 
			else if(location->k_data < key)
			{
				location->RChild = p_newNode;
			}

			return true;
		}
		else//�ҵ�key
		{
			return false;
		}
	}

	//�������������
	void CreatBiSearchTree(T a[], int n)
	{
		for (int i = 0; i < n; i++)
		{
			Insert(a[i]);
		}
	}

	//��һ���ڵ�ĺ�̽ڵ�
	BiNode<T>* bst_successor(BiNode<T> *node)
	{
		if (node->RChild != NULL)//��������Ϊ�գ���̽ڵ㼴Ϊ����������Сֵ�ڵ�
		{
			BiNode<T>* p_node = node->RChild;
			while(p_node->LChild != NULL){p_node = p_node->LChild;}
			return p_node;
		}
		else//������Ϊ�գ�����ônode��ֱ�Ӻ�̽ڵ���Ǵ�node���ϵ�·���е�һ����ת�������Ľڵ㡣
		{
			BiNode<T>* p_node = node->Parent;
			while(p_node != NULL && p_node->RChild == node)
			{
				node = p_node;
				p_node = p_node->Parent;
			}
			return p_node;
		}
	}

	//ɾ���ڵ�
	//1. ���Zû�к��ӽ�㣬��ôֱ��ɾ��Z�����ˡ�
	//2. ���Z��һ�����ӽ�㣬��ôɾ��Z����Z�ĸ������˺��ӽ�㣨�����������Ϳ����ˡ�
	//3. ���Z���������ӽ�㣬ʵ�ַ������ǽ���̴Ӷ�������ɾ�������õ�һ�����������������̵����ݸ��ǵ�Z�С�
	bool Delete(T key)
	{
		if (root == NULL)
		{
			return false;
		}
		BiNode<T>* p = root;
		while(p != NULL)//����key
		{
			if (p->k_data > key)
			{
				p = p->LChild;
			} 
			else if(p->k_data < key)
			{
				p = p->RChild;
			}
			else
			{
				break;
			}
		}

		if (p != NULL)//���ҵ�k
		{
			//��������ɾ���Ľڵ�
			BiNode<T>* p_real;  
			if (p->LChild && p->RChild)  
				p_real = bst_successor(p);//��������ɾ���Ľڵ�һ����������1.��������2.
			else  
				p_real = p;

			BiNode<T>* p_parent = p_real->Parent;
			if (p_real->LChild == NULL && p_real->RChild == NULL)//1.���Ҷ���
			{
				if (p_parent == NULL)//��Ҫɾ�����Ǹ��ڵ�
					root = NULL;
				else 
					if (p_parent->LChild == p_real) {p_parent->LChild = NULL;}
					else {p_parent->RChild = NULL;}
			} 
			else if (p_real->LChild == NULL  && p_real->RChild != NULL)//2.��գ��Ҳ���
			{
				if (p_parent == NULL)//��Ҫɾ�����Ǹ��ڵ�
					{root = p_real->RChild; p_real->RChild->Parent = NULL;}
				else 
					if (p_parent->LChild == p_real) {p_parent->LChild = p_real->RChild; p_real->RChild->Parent = p_parent;}
					else {p_parent->RChild = p_real->RChild; p_real->RChild->Parent = p_parent;}
			}
			else if (p_real->LChild != NULL  && p_real->RChild == NULL)//3.�󲻿գ��ҿ�
			{
				if (p_parent == NULL)//��Ҫɾ�����Ǹ��ڵ�
					{root = p_real->LChild; p_real->LChild->Parent = NULL;}
				else 
					if (p_parent->LChild == p_real) {p_parent->LChild = p_real->LChild; p_real->LChild->Parent = p_parent;}
					else {p_parent->RChild = p_real->LChild; p_real->LChild->Parent = p_parent;}
			}

			if (p_real != p)//�������˫�����Ľڵ㣬�򸲸�ԭӦ��ɾ���ڵ�
			{
				p->k_data = p_real->k_data;
			}

			delete p_real;//ɾ���ڵ�
			return true;
		}
		return false;
	}


protected:
private:
	//���ҽڵ�
	BiNode<T>* Search(BiNode<T>* pRoot, T key) const
	{
		if (pRoot == NULL)
		{
			return NULL;//����ʧ��
		}
		if (pRoot->k_data == key)
		{
			return pRoot;//���ҳɹ�
		}
		else if (pRoot->k_data > key)
		{
			return Search(pRoot->LChild, key);
		} 
		else if(pRoot->k_data < key)
		{
			return Search(pRoot->RChild, key);
		}
	}

	void VisitBiTreePreOrder(BiNode<T> *pRoot, void(*Visit)(BiNode<T>)) const
	{
		if (pRoot != NULL)
		{
			Visit(*pRoot);
			VisitBiTreePreOrder(pRoot->LChild, Visit);
			VisitBiTreePreOrder(pRoot->RChild, Visit);
		} 
	}

	void VisitBiTreeInOrder(BiNode<T> *pRoot, void(*Visit)(BiNode<T>)) const
	{
		if (pRoot != NULL)
		{
			VisitBiTreeInOrder(pRoot->LChild, Visit);
			Visit(*pRoot);
			VisitBiTreeInOrder(pRoot->RChild, Visit);
		} 
	}

	BiNode<T> *root;
};


int main()
{
	int keys[] = {8, 5, 2, 1, 4, 7, 3, 6, 9};
	BiSearchTree<int>* p_BiSearchTree = new BiSearchTree<int>();
	p_BiSearchTree->CreatBiSearchTree(keys, sizeof(keys)/sizeof(keys[0]));
	cout<<"ǰ�������������";
	p_BiSearchTree->VisitBiTreePreOrder(PrintNode);
	cout<<endl<<"���������������";
	p_BiSearchTree->VisitBiTreeInOrder(PrintNode);
	cout<<endl;

	while (0)
	{
		int k;
		cin.clear();
		cin.sync();
		cout<<"������Ҫ���ҵĽڵ�ֵ��";
		cin>>k;
		cout<<p_BiSearchTree->Search(k)->k_data<<endl;
	}

	int i = 4;
	while (i)
	{
		int k;
		cin.clear();
		cin.sync();
		cout<<"������Ҫɾ���Ľڵ�ֵ��";
		cin>>k;
		p_BiSearchTree->Delete(k);
		cout<<"ǰ�������������";
		p_BiSearchTree->VisitBiTreePreOrder(PrintNode);
		cout<<endl<<"���������������";
		p_BiSearchTree->VisitBiTreeInOrder(PrintNode);
		cout<<endl;
		i--;
	}

	delete p_BiSearchTree;
	system("pause");
	return 0;
}