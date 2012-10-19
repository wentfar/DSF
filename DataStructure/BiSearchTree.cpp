#include <iostream>
using namespace std;

template <typename T>
struct BiNode{
	T k_data;
	BiNode<T> *LChild, *RChild;
	BiNode<T> *Parent;
	BiNode(T element, BiNode<T> *lt, BiNode<T> *rt, BiNode<T> *pt):k_data(element), LChild(lt), RChild(rt), Parent(pt){}
};

template <typename T>
class BiSearchTree
{
public:
	BiSearchTree(BiNode<T>* pRoot = NULL){root = pRoot;}

	//前序遍历二叉树
	void VisitBiTreePreOrder(void(*Visit)(BiNode<T>)) const
	{
		VisitBiTreePreOrder(root, Visit);
	}

	//后序遍历二叉树
	void VisitBiTreeInOrder(void(*Visit)(BiNode<T>)) const
	{
		VisitBiTreeInOrder(root, Visit);
	}

	//查找，找到则返回节点，否则返回空
	BiNode<T>* Search(T key) const
	{
		return Search(root, key);
	}

	//插入，如果已经有此节点，则返回false，否则插入节点，返回true
	bool Insert(T key)
	{
		BiNode<T>* p_newNode = new BiNode<T>(key, NULL, NULL, NULL);
		if (root == NULL)//空树
		{
			root = p_newNode;
		}
		BiNode<T>* p = root;
		BiNode<T>* location = NULL;//key的插入位置
		while(p != NULL)//查找key
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

		if (p == NULL)//未找到key
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
		else//找到key
		{
			return false;
		}
	}

	//求一个节点的后继节点
	BiNode<T>* bst_successor(BiNode<T> *node)
	{
		if (node->RChild != NULL)//右子树不为空，后继节点即为右子树的最小值节点
		{
			BiNode<T>* p_node = node->RChild;
			while(p_node->LChild != NULL){p_node = p_node->LChild;}
			return p_node;
		}
		else//右子树为空，则那么node的直接后继节点就是从node向上的路径中第一次右转后遇到的节点。
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

	//删除，找到此节点，删除并返回true，否则返回false
	bool Delete(T key)
	{
		return Delete(root, key);
	}
	
	//创建二叉查找树
	void CreatBiSearchTree(T a[], int n)
	{
		for (int i = 0; i < n; i++)
		{
			Insert(a[i]);
		}
	}

protected:
private:
	//查找节点
	BiNode<T>* Search(BiNode<T>* pRoot, T key) const
	{
		if (pRoot == NULL)
		{
			return NULL;//查找失败
		}
		if (pRoot->k_data == key)
		{
			return pRoot;//查找成功
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

	//删除节点
	//1. 结点Z没有孩子结点，那么直接删除Z就行了。
	//2. 结点Z有一个孩子结点，那么删除Z，将Z的父结点与此孩子结点（子树）关联就可以了。
	//3. 结点Z有两个孩子结点，实现方法就是将后继从二叉树中删除（适用第一、二种情况），将后继的数据覆盖到Z中。
	bool Delete(T key)
	{
		if (root == NULL)
		{
			return false;
		}
		BiNode<T>* p = root;
		while(p != NULL)//查找key
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

		if (p != NULL)//查找到k
		{
			//求真正被删除的节点
			BiNode<T>* p_real;  
			if (p->left && p->right)  
				p_real = bst_successor(p);//此真正被删除的节点一定满足条件1.或者条件2.
			else  
				p_real = p;

			BiNode* p_parent = p_real->Parent;
			if (p_real->LChild == NULL && p_real->RChild == NULL)
			{
				if (p_parent == NULL)//只有根节点
					root = NULL;
				else 
				{
					p_parent->LChild == p_real ? p_parent->LChild = NULL : p_parent->RChild = NULL;
				}
			} 
			else if (p_real->LChild == NULL  && p_real->RChild != NULL)
			{
				if (p_parent == NULL)
					root = p_real->RChild;
				else 
					if (p_parent->LChild == p_real) {p_parent->LChild = p_real->RChild; p_real->RChild->Parent = p_parent;}
					else {p_parent->RChild = p_real->RChild; p_real->RChild->Parent = p_parent;}
			}
			else if (p_real->LChild != NULL  && p_real->RChild == NULL)
			{
				if (p_parent == NULL)
					root = p_real->RChild;
				else 
					if (p_parent->LChild == p_real) {p_parent->LChild = p_real->LChild; p_real->LChild->Parent = p_parent;}
					else {p_parent->RChild = p_real->LChild; p_real->LChild->Parent = p_parent;}
			}
			delete p_real;//重要

			return true;
		}
		return false;
	}

	BiNode<T> *root;
};

//打印节点
template <typename T>
void PrintNode(BiNode<T> node)
{
	cout<<node.k_data<<" ";
}


int main()
{
	int keys[] = {1, 4, 7, 2, 5, 8, 3, 6, 9};
	BiSearchTree<int>* p_BiSearchTree = new BiSearchTree<int>();
	p_BiSearchTree->CreatBiSearchTree(keys, sizeof(keys)/sizeof(keys[0]));
	cout<<"前序遍历二叉树：";
	p_BiSearchTree->VisitBiTreePreOrder(PrintNode);
	cout<<endl<<"中序遍历二叉树：";
	p_BiSearchTree->VisitBiTreeInOrder(PrintNode);
	cout<<endl;

	while (0)
	{
		int k;
		cin.clear();
		cin.sync();
		cout<<"请输入要查找的节点值：";
		cin>>k;
		cout<<p_BiSearchTree->Search(k)->k_data<<endl;
	}

	int i = 4;
	while (i)
	{
		int k;
		cin.clear();
		cin.sync();
		cout<<"请输入要删除的节点值：";
		cin>>k;
		p_BiSearchTree->Delete(k);
		cout<<"前序遍历二叉树：";
		p_BiSearchTree->VisitBiTreePreOrder(PrintNode);
		cout<<endl<<"中序遍历二叉树：";
		p_BiSearchTree->VisitBiTreeInOrder(PrintNode);
		cout<<endl;
		i--;
	}

	delete p_BiSearchTree;
	system("pause");
	return 0;
}