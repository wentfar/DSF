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
	void GetRoot(BiNode **root) const;
	void VisitBiTreePreOrder() const;
	void VisitBiTreeInOrder() const;
	void VisitBiTreePostOrder() const;
	int NodeCount1() const;
	int NodeCount2() const;
	int TreeDepth() const;
	void LevelTravel() const;
	void Convert1(BiNode **pFirstNode, BiNode **pLastNode);
	void Convert2(BiNode **pFirstNode, BiNode **pLastNode);
	int GetNodeNumKthLevel1(int k) const;
	int GetNodeNumKthLevel2(int k) const;
	int LeafCount() const;
	bool StructureCmp(BiNode *pRoot2) const;
	bool IsBalanceBiTree() const;
	void BiTreeMirror();
	int GetMaxDistance() const;

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
	void Convert1(BiNode *root, BiNode **pre);
	void Convert2(BiNode* root, BiNode **pFirstNode, BiNode **pLastNode);
	int GetNodeNumKthLevel2(BiNode *pRoot, int k) const;
	int LeafCount(BiNode *root) const;
	bool StructureCmp(BiNode *pRoot1, BiNode *pRoot2) const;
	bool IsBalanceBiTree(BiNode *root, int &height) const;
	void BiTreeMirror(BiNode *&root);
	int GetMaxDistance(BiNode *pRoot) const;

	struct BiNode *root;
};

#endif