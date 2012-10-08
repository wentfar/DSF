#include <iostream>
#include <string>
#include <iomanip>
#include "Definition.h"

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define MAX_FLOAT 32767.0

using namespace std;

typedef char TElemType;

typedef struct BiNode{
	TElemType data;
	struct BiNode *lchild, *rchild;
}BiNode, *Bitree;

//二叉线索存储表示
typedef enum PointerTag{Link, Thread};

typedef struct BiThrNode{
	TElemType data;
	struct BiThrNode *lchild, *rchild;
	PointerTag LTag, RTag;
}BiThrNode,*BiThrTree;

BiThrTree pre=NULL;//全局变量

typedef struct HTNode{
	float weight;
	int parent, lchild, rchild;
}HTNode, *HuffmanTree;//霍夫曼树，具有2n-1个结点的二叉树

typedef char** HuffmanCode;//霍夫曼编码，包括n个字符串

typedef Bitree SElemType;

typedef struct{
	SElemType * base;
	SElemType * top;
	int stacksize;
}SqStack;


//初始化一个空栈（char）
Status InitStack(SqStack &s){
	s.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!s.base) exit(OVERFLOW);
	s.top=s.base;
	s.stacksize=STACK_INIT_SIZE;
	return OK;
}

Status Push(SqStack &s, SElemType e){
	if(s.top-s.base>=s.stacksize){
		s.base=(SElemType*)realloc(s.base, (s.stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!s.base) exit(OVERFLOW);
		s.top=s.base+s.stacksize;
		s.stacksize+=STACKINCREMENT;
	}
	*s.top++=e;//优先级'.'>'*','*'='++'
	return OK;
}

Status Pop(SqStack &s, SElemType &e){
	if(s.top==s.base) return ERROR;
	e=*--s.top;
	return OK;
}

Status StackEmpty(SqStack s){
	if(s.base==NULL) exit(OVERFLOW);
	else if(s.base==s.top) return TRUE;
	else return FALSE;
}

Status GetTop(SqStack s, SElemType &e){
	if(s.base==NULL || s.base==s.top) return ERROR;
	e= *(s.top-1);
	return OK;
}

void Printf_Stack(SqStack s){
	if(s.base==NULL) exit(OVERFLOW);
	SElemType *p=s.top;
	while(s.base!=p){
		cout<<(*(--p))->data<<" ";
	}
}

//先序次序建立二叉树
Status CreatBitree(Bitree &T){
	TElemType  elem;
	elem=getchar();
	if(elem==' ') T=NULL;
	else{
		if(!(T=(Bitree)malloc(sizeof(BiNode)))) exit(OVERFLOW);
		T->data=elem;//生成根节点
		CreatBitree(T->lchild);//左子树
		CreatBitree(T->rchild);//右子树
	}
	return OK;
}

//先序次序建立二叉树(线索类型)
Status CreatBitree(BiThrTree &T){
	TElemType  elem;
	elem=getchar();
	if(elem==' ') T=NULL;
	else{
		if(!(T=(BiThrTree)malloc(sizeof(BiThrNode)))) exit(OVERFLOW);
		T->data=elem;//生成根节点
		T->LTag=T->RTag=Link;
		CreatBitree(T->lchild);//左子树
		CreatBitree(T->rchild);//右子树
	}
	return OK;
}


//前序遍历
Status PreOrderTraverse(Bitree T){
	if(!T) return FALSE;
	else{
		cout<<T->data;
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

Status PrintElement(TElemType elem){
	if (elem!=NULL)
	{
		cout<<elem<<" ";
		return OK;
	} 
	else
	{
		return FALSE;
	}
}

//非递归的中序遍历
Status InOrderTraverse(Bitree T, Status (*visit)(TElemType)){
	SqStack s;
	Bitree lch=new BiNode();
	Bitree back=new BiNode();//指针型变量初始化
	InitStack(s);
	Push(s, T);
	while(!StackEmpty(s)){
		while(GetTop(s, lch) && lch){
			Push(s, lch->lchild);//向左到尽头，最后压入空指针
		}
		Pop(s, back);//将空指针弹出
		if(!StackEmpty(s)){
			Pop(s, back);//
			if(!visit(back->data)){return ERROR;}//访问节点
			Push(s, back->rchild);//此处右孩子有可能为空，为空情况下，下次循环直接将空指针弹出
		}
	}
	return OK;
}


//线索化之前的中序遍历(BiThrTree)
Status InOrderTraverse_Before(BiThrTree T){
	if(!T) return FALSE;
	else{
		InOrderTraverse_Before(T->lchild);
		cout<<T->data<<" "<<T->LTag<<" "<<T->RTag<<endl;
		InOrderTraverse_Before(T->rchild);
	}
}

//将二叉树中序遍历，进行中序线索化
void InThreading(BiThrTree p){
	if(p){
		InThreading(p->lchild);

		if(!pre->rchild){pre->RTag=Thread; pre->rchild=p;}//前驱的后继
		if(!p->lchild){p->LTag=Thread; p->lchild=pre;}//本结点的前驱
		pre=p;//更新pre

		InThreading(p->rchild);
	}
}


//将二叉树中序线索化，Thrt指向头结点
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T){
	Thrt=new BiThrNode();//建头结点
	if(!Thrt) exit(OVERFLOW);

	Thrt->RTag=Thread;
	Thrt->rchild=Thrt;
	Thrt->LTag=Link;
	Thrt->lchild=Thrt;//头结点的左右孩纸均回指
	if(T){
		pre=Thrt;//前驱结点
		pre->lchild=T;
		InThreading(T);//其中T为当前第一个结点
		pre->RTag=Thread;//最后一个节点
		pre->rchild=Thrt;
		Thrt->rchild=pre;
	}
	return OK;	
}

//中序遍历二叉线索树T的非递归算法，T指向头结点
Status InOrderTraverse_Thr(BiThrTree T, Status (*visit)(TElemType)){
	if(!T) return ERROR;//头结点为空
	BiThrTree p=T->lchild;//

	while(p!=T){//空树或者遍历结束
		while(p->LTag == Link){//到最左边
			p=p->lchild;
		}
		if(!visit(p->data)) return ERROR;
		while(p->RTag == Thread && p->rchild != T) {
			p=p->rchild;
			visit(p->data);
		}
		p=p->rchild;//此时右标志为Link，后继应为右子树的最左边
	}
	return OK;
}

//在HT[1...n]选择parent为0，且weight最小的两个节点，其序号分别为s1,s2，另(s1<s2)
void Select(HuffmanTree HT, int n, int &s1, int &s2){
	float min=MAX_FLOAT;
	float sec_min=MAX_FLOAT;
	int temp;
	for(int i=1;i<=n;++i){
		if(HT[i].parent==0){
			if(HT[i].weight<min) {min=HT[i].weight; s1=i;}
		}
	}
	for(int i=1;i<=n;++i){
		if(HT[i].parent==0 && i!=s1){
			if(HT[i].weight<sec_min) {sec_min=HT[i].weight; s2=i;}
		}
	}
	if(s1>s2){s1=s1+s2;s2=s1-s2;s1=s1-s2;}
}

//w存放n个字符的权值，构造霍夫曼树HT，并求n个字符的霍夫曼编码HC，*w均大于0
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, float *w, int n){
	if(n<=1) return;
	int m=2*n-1;//节点总数
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));//0号单元未用
	int i,s1,s2;
	HuffmanTree p;
	for(p=HT+1,i=1; i<=n; ++i,++p,++w)//(1~n，叶子节点)
		{(*p).weight=*w; (*p).parent=(*p).lchild=(*p).rchild=0;}
	for( ; i<=m; ++i,++p)//(n+1~m非叶子节点)
		{(*p).weight=0.0; (*p).parent=(*p).lchild=(*p).rchild=0;}

	//构建霍夫曼树
	for(i=n+1; i<=m; ++i){
		Select(HT, i-1, s1, s2);
		HT[s1].parent=HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}

	//从叶子到根逆向求取每个字符的霍夫曼编码
	HC=(HuffmanCode)malloc((n+1)*sizeof(char*));//n个字符编码的头指针地址，HC[0]不用

	char *cd=(char*)malloc(n*sizeof(char));
	cd[n-1]='\0';

	for(i=1;i<=n;++i){//求每个字符的霍夫曼编码
		int start=n-1;//编码结束符的位置
		for(int c=i,f=HT[i].parent; f!=0; c=f,f=HT[f].parent){//从叶子到根逆向求编码
			if(HT[f].lchild==c) {cd[--start]='0';}
			else cd[--start]='1';
		}
		HC[i]=(char*)malloc((n-start)*sizeof(char));//为第i个字符的编码分配存储空间，为HC的元素HC[i]赋值
		strcpy(HC[i], &cd[start]);//为HC[i]指向的地址赋值
	}
	free(cd);
}

//////////////////////////////////////////////////////////////////////////

typedef Bitree QElemType;

typedef struct QNode{
	QElemType data;
	struct QNode * next;
}QNode, *QueuePtr;

typedef struct{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

//3.28//初始化循环链表表示的队列Q
void InitQueue(LinkQueue &lq){
	lq.front=lq.rear=(QueuePtr)malloc(sizeof(QNode));//只初始化队列头
	if(!lq.front) exit(OVERFLOW);
	lq.front->next=NULL;
}

//删除队列(从队头之前的lq.front开始删除)
Status DetroryQueue(LinkQueue &lq){
	while(lq.front){
		lq.rear=lq.front->next;//暂存
		free(lq.front);
		lq.front=lq.rear;
	}
	return OK;
}

//队尾插入
Status EnQueue(LinkQueue &lq, QElemType e){
	QueuePtr p_qn=(QueuePtr)malloc(sizeof(QNode));
	if(!p_qn) exit(OVERFLOW);
	p_qn->data=e;	p_qn->next=NULL;
	lq.rear->next=p_qn;	lq.rear=p_qn;
	return OK;
}
//对头去除
Status DeQueue(LinkQueue &lq, QElemType &e){
	if(lq.front==lq.rear) return ERROR;
	QueuePtr p_qn=lq.front->next;
	lq.front->next=p_qn->next;
	e=p_qn->data;
	if(lq.rear==p_qn) lq.rear=lq.front;//如果除了lq.front外，只有一个元素，则删除后队列空，需要改变lq.rear的值
	free(p_qn);
}
//队列空
Status QueueEmpty(LinkQueue lq){
	if(lq.rear==lq.front) return 1;//队列空
	else return 0;
}

//遍历
Status QueueTraverse(LinkQueue lq){
	if(lq.front==lq.rear) return ERROR;
	QueuePtr p_qn=lq.front->next;//指向队列头
	while(p_qn){
		cout<<p_qn->data<<' ';
		p_qn=p_qn->next;
	}
	cout<<endl;
	return OK;
}
//////////////////////////////////////////////////////////////////////////

//按层次遍历二叉树
void BFSTraverse(Bitree T, Status (*visit)(TElemType e)){
	LinkQueue lq;
	Bitree bt;
	bool IsEmpty;
	InitQueue(lq);
	if(T) EnQueue(lq, T);
	while(!(IsEmpty=QueueEmpty(lq))){
		DeQueue(lq,bt);
		visit(bt->data);
		if(bt->lchild) EnQueue(lq, bt->lchild);
		if(bt->rchild) EnQueue(lq, bt->rchild);
	}
}

//生成一个树节点
Bitree GenerateTreeNode(TElemType e, Bitree lptr, Bitree rptr){
	Bitree New_Node;
	New_Node=(Bitree)malloc(sizeof(BiNode));
	if(!New_Node) return ERROR;
	New_Node->lchild=lptr;
	New_Node->rchild=rptr;
	New_Node->data=e;
	return New_Node;
}
//复制二叉树(后序遍历)
Bitree CopyTree(Bitree T){
	Bitree new_lptr,new_rptr,new_bt;
	if(!T) return NULL;
	if(T->lchild) new_lptr=CopyTree(T->lchild);
	else new_lptr=NULL;
	if(T->rchild) new_rptr=CopyTree(T->rchild);
	else new_rptr=NULL;
	return new_bt=GenerateTreeNode(T->data, new_lptr, new_rptr);
}

//求二叉树的深度(后序遍历)
int Depth_Bitree(Bitree T){
	int l_dep, r_dep, dep_val;
	if(!T) return dep_val=0;
	l_dep=Depth_Bitree(T->lchild);
	r_dep=Depth_Bitree(T->rchild);
	dep_val=1+(l_dep>r_dep?l_dep:r_dep);
	return dep_val;
}

//求二叉树的叶子节点数（先序遍历）
void Count_Leaf(Bitree T, int &n){
	if(!T) return;
	if(!T->lchild && !T->rchild) n++;
	Count_Leaf(T->lchild, n);
	Count_Leaf(T->rchild, n);
}




	

void main(){
		int n_leaf=0;
		int n_leaf_copy=0;
		Bitree t;
		SqStack sq,sq_copy;
		InitStack(sq);
		InitStack(sq_copy);

		CreatBitree(t);
		cout<<"前序遍历:";
		PreOrderTraverse(t);
		cout<<endl;
		cout<<"中序遍历:";
		InOrderTraverse(t, PrintElement);
		cout<<endl;
		cout<<"层次遍历:";
		BFSTraverse(t, PrintElement);
		cout<<endl<<"树的深度:"<<Depth_Bitree(t);
		Count_Leaf(t, n_leaf);
		cout<<endl<<"叶子的个数:"<<n_leaf;
		cout<<endl;
		AllPath(t, sq);

		Bitree copy_tree;
		copy_tree=CopyTree(t);
		cout<<endl<<"copy_tree:"<<endl;
		cout<<"前序遍历:";
		PreOrderTraverse(copy_tree);
		cout<<endl;
		cout<<"中序遍历:";
		InOrderTraverse(copy_tree, PrintElement);
		cout<<endl;
		cout<<"层次遍历:";
		BFSTraverse(copy_tree, PrintElement);
		cout<<endl<<"树的深度:"<<Depth_Bitree(copy_tree);
		Count_Leaf(copy_tree, n_leaf_copy);
		cout<<endl<<"叶子的个数:"<<n_leaf_copy;
		cout<<endl;
		AllPath(copy_tree, sq_copy);
		system("pause");
		
/*
	BiThrTree t,t_thr;
	CreatBitree(t);//先序建立二叉树
	InOrderTraverse_Before(t);//线索化之前的中序遍历
	cout<<endl;
	InOrderThreading(t_thr, t);//线索化
	InOrderTraverse_Thr(t_thr, PrintElement);//线索化之后的中序遍历
	system("pause");
	*/
/*
	HuffmanTree ht;
	HuffmanCode hc;
	float w[]={5,29,7,8,14,23,3,11};
	int count=sizeof(w)/sizeof(float);
	HuffmanCoding(ht, hc, w, count);

	for(int i=1;i<=2*count-1;i++){
		cout<<setw(4)<<i<<setw(4)<<ht[i].weight<<setw(4)<<ht[i].parent<<setw(4)<<ht[i].lchild<<setw(4)<<ht[i].rchild<<endl;
	}	
	cout<<endl;
	for(int i=1;i<=count;i++){
		cout<<setw(8)<<hc[i]<<endl;
	}
	system("pause");
	*/
}