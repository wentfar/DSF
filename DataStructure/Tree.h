#ifndef Tree.h

template <typename T>
struct BiNode{
	T k_data;
	BiNode<T> *LChild, *RChild;
	BiNode(T element, BiNode<T> *lt, BiNode<T> *rt):k_data(element), LChild(lt), RChild(rt){}
};

//定义树节点以及树
template <typename T>
class BiTree{
public:
	BiTree();
	~BiTree();
	void GetRoot(BiNode<T> **pRoot) const;
	void PrintNode(BiNode<T> node);
	void VisitBiTreePreOrder(void(*Visit)(BiNode<T>)) const;
	void VisitBiTreeInOrder(void(*Visit)(BiNode<T>)) const;
	void VisitBiTreePostOrder(void(*Visit)(BiNode<T>)) const;
	int NodeCount1() const;
	int NodeCount2() const;
	int TreeDepth() const;
	void LevelTravel() const;
	void Convert1(BiNode<T> **pFirstNode, BiNode<T> **pLastNode);
	void Convert2(BiNode<T> **pFirstNode, BiNode<T> **pLastNode);
	int GetNodeNumKthLevel1(int k) const;
	int GetNodeNumKthLevel2(int k) const;
	int LeafCount() const;
	bool StructureCmp(BiNode<T> *pRoot2) const;
	bool IsBalanceBiTree() const;
	void BiTreeMirror();
	int GetMaxDistance() const;
	bool IsCompleteBinaryTree() const;
	void CreatBiTreeByPre_In(int PreList[], int InList[], int num, BiNode<T> **biNode);

private:
	void CreatBiTree(BiNode<T> **pRoot);
	void ReleaseBiTree(BiNode<T> **pRoot);
	void VisitBiTreePreOrder(BiNode<T> *pRoot, void(*Visit)(BiNode<T>)) const;
	void VisitBiTreeInOrder(BiNode<T> *pRoot, void(*Visit)(BiNode<T>)) const;
	void VisitBiTreePostOrder(BiNode<T> *pRoot, void(*Visit)(BiNode<T>)) const;
	void NodeCount1(BiNode<T> *pRoot, int *count) const;
	int NodeCount2(BiNode<T> *pRoot) const;
	int TreeDepth(BiNode<T> *pRoot) const;
	void LevelTravel(BiNode<T> *pRoot) const;
	void Convert1(BiNode<T> *pRoot, BiNode<T> **pre);
	void Convert2(BiNode<T> *pRoot, BiNode<T> **pFirstNode, BiNode<T> **pLastNode);
	int GetNodeNumKthLevel2(BiNode<T> *pRoot, int k) const;
	int LeafCount(BiNode<T> *pRoot) const;
	bool StructureCmp(BiNode<T> *pRoot1, BiNode<T> *pRoot2) const;
	bool IsBalanceBiTree(BiNode<T> *pRoot, int &height) const;
	void BiTreeMirror(BiNode<T> *&pRoot);
	void GetMaxDistance(BiNode<T> *pRoot, int &Left_max, int &Right_max) const;
	bool IsCompleteBinaryTree(BiNode<T> *pRoot) const;

	BiNode<T> *root;
};

#endif