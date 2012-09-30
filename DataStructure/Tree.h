#ifndef Tree.h

//定义树节点以及树
template <typename T>
class BiTree{
private:
	struct BiNode{
		T k_data;
		struct BiNode *LChild, *RChild;
		BiNode(T element, BiNode *lt, BiNode *rt):k_data(element), LChild(lt), RChild(rt){}
	};
	struct BiNode *root;

	void CreatBiTree(BiNode **root);
	void ReleaseBiTree(BiNode **root);
	void VisitBiTreePreOrder(BiNode *root) const;
	void VisitBiTreeInOrder(BiNode *root) const;
	void VisitBiTreePostOrder(BiNode *root) const;
	void NodeCount1(BiNode *root, int *count) const;
	int NodeCount2(BiNode *root) const;
	int TreeDepth(BiNode *root) const;
public:
	BiTree();
	~BiTree();
	void VisitBiTreePreOrder() const;
	void VisitBiTreeInOrder() const;
	void VisitBiTreePostOrder() const;
	int NodeCount1() const;
	int NodeCount2() const;
	int TreeDepth() const;

};

#endif