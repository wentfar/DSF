#ifndef Tree.h

//定义树节点以及树
template <typename T>
class BiTree{
public:
	struct BiNode{
		T k_data;
		struct BiNode *LChild, *RChild;
		BiNode(T element, BiNode *lt, BiNode *rt):k_data(element), LChild(lt), RChild(rt){}
	};

	BiTree();
	~BiTree();
	void VisitBiTreePreOrder() const;
	void VisitBiTreeInOrder() const;
	void VisitBiTreePostOrder() const;
	int NodeCount1() const;
	int NodeCount2() const;
	int TreeDepth() const;
	void LevelTravel() const;
	void Convert(BiNode **pFirstNode, BiNode **pLastNode);

private:
	void CreatBiTree(BiNode **root);
	void ReleaseBiTree(BiNode **root);
	void VisitBiTreePreOrder(BiNode *root) const;
	void VisitBiTreeInOrder(BiNode *root) const;
	void VisitBiTreePostOrder(BiNode *root) const;
	void NodeCount1(BiNode *root, int *count) const;
	int NodeCount2(BiNode *root) const;
	int TreeDepth(BiNode *root) const;
	void LevelTravel(BiNode *root) const;
	void Convert(BiNode *root, BiNode *&pre);

	struct BiNode *root;
};

#endif