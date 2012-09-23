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

//���������洢��ʾ
typedef enum PointerTag{Link, Thread};
typedef struct BiThrNode{
	TElemType data;
	struct BiThrNode *lchild, *rchild;
	PointerTag LTag, RTag;
}BiThrNode,*BiThrTree;

BiThrTree pre=NULL;//ȫ�ֱ���

typedef struct HTNode{
	float weight;
	int parent, lchild, rchild;
}HTNode, *HuffmanTree;//��������������2n-1�����Ķ�����
typedef char** HuffmanCode;//���������룬����n���ַ���



typedef Bitree SElemType;

typedef struct{
	SElemType * base;
	SElemType * top;
	int stacksize;
}SqStack;





//��ʼ��һ����ջ��char��
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
	*s.top++=e;//���ȼ�'.'>'*','*'='++'
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

//���������������
Status CreatBitree(Bitree &T){
	TElemType  elem;
	elem=getchar();
	if(elem==' ') T=NULL;
	else{
		if(!(T=(Bitree)malloc(sizeof(BiNode)))) exit(OVERFLOW);
		T->data=elem;//���ɸ��ڵ�
		CreatBitree(T->lchild);//������
		CreatBitree(T->rchild);//������
	}
	return OK;
}

//���������������(��������)
Status CreatBitree(BiThrTree &T){
	TElemType  elem;
	elem=getchar();
	if(elem==' ') T=NULL;
	else{
		if(!(T=(BiThrTree)malloc(sizeof(BiThrNode)))) exit(OVERFLOW);
		T->data=elem;//���ɸ��ڵ�
		T->LTag=T->RTag=Link;
		CreatBitree(T->lchild);//������
		CreatBitree(T->rchild);//������
	}
	return OK;
}


//ǰ�����
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

//�ǵݹ���������
Status InOrderTraverse(Bitree T, Status (*visit)(TElemType)){
	SqStack s;
	Bitree lch=new BiNode();
	Bitree back=new BiNode();//ָ���ͱ�����ʼ��
	InitStack(s);
	Push(s, T);
	while(!StackEmpty(s)){
		while(GetTop(s, lch) && lch){
			Push(s, lch->lchild);//���󵽾�ͷ�����ѹ���ָ��
		}
		Pop(s, back);//����ָ�뵯��
		if(!StackEmpty(s)){
			Pop(s, back);//
			if(!visit(back->data)){return ERROR;}//���ʽڵ�
			Push(s, back->rchild);//�˴��Һ����п���Ϊ�գ�Ϊ������£��´�ѭ��ֱ�ӽ���ָ�뵯��
		}
	}
	return OK;
}


//������֮ǰ���������(BiThrTree)
Status InOrderTraverse_Before(BiThrTree T){
	if(!T) return FALSE;
	else{
		InOrderTraverse_Before(T->lchild);
		cout<<T->data<<" "<<T->LTag<<" "<<T->RTag<<endl;
		InOrderTraverse_Before(T->rchild);
	}
}

//�������������������������������
void InThreading(BiThrTree p){
	if(p){
		InThreading(p->lchild);

		if(!pre->rchild){pre->RTag=Thread; pre->rchild=p;}//ǰ���ĺ��
		if(!p->lchild){p->LTag=Thread; p->lchild=pre;}//������ǰ��
		pre=p;//����pre

		InThreading(p->rchild);
	}
}


//��������������������Thrtָ��ͷ���
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T){
	Thrt=new BiThrNode();//��ͷ���
	if(!Thrt) exit(OVERFLOW);

	Thrt->RTag=Thread;
	Thrt->rchild=Thrt;
	Thrt->LTag=Link;
	Thrt->lchild=Thrt;//ͷ�������Һ�ֽ����ָ
	if(T){
		pre=Thrt;//ǰ�����
		pre->lchild=T;
		InThreading(T);//����TΪ��ǰ��һ�����
		pre->RTag=Thread;//���һ���ڵ�
		pre->rchild=Thrt;
		Thrt->rchild=pre;
	}
	return OK;	
}

//�����������������T�ķǵݹ��㷨��Tָ��ͷ���
Status InOrderTraverse_Thr(BiThrTree T, Status (*visit)(TElemType)){
	if(!T) return ERROR;//ͷ���Ϊ��
	BiThrTree p=T->lchild;//

	while(p!=T){//�������߱�������
		while(p->LTag == Link){//�������
			p=p->lchild;
		}
		if(!visit(p->data)) return ERROR;
		while(p->RTag == Thread && p->rchild != T) {
			p=p->rchild;
			visit(p->data);
		}
		p=p->rchild;//�ұ�־ΪLink�����Ϊ�������������
	}
	return OK;
}

//��HT[1...n]ѡ��parentΪ0����weight��С�������ڵ㣬����ŷֱ�Ϊs1,s2����(s1<s2)
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

//w���n���ַ���Ȩֵ�������������HT������n���ַ��Ļ���������HC��*w������0
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, float *w, int n){
	if(n<=1) return;
	int m=2*n-1;//�ڵ�����
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));//0�ŵ�Ԫδ��
	int i,s1,s2;
	HuffmanTree p;
	for(p=HT+1,i=1; i<=n; ++i,++p,++w)//(1~n��Ҷ�ӽڵ�)
		{(*p).weight=*w; (*p).parent=(*p).lchild=(*p).rchild=0;}
	for( ; i<=m; ++i,++p)//(n+1~m��Ҷ�ӽڵ�)
		{(*p).weight=0.0; (*p).parent=(*p).lchild=(*p).rchild=0;}

	//������������
	for(i=n+1; i<=m; ++i){
		Select(HT, i-1, s1, s2);
		HT[s1].parent=HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}

	//��Ҷ�ӵ���������ȡÿ���ַ��Ļ���������
	HC=(HuffmanCode)malloc((n+1)*sizeof(char*));//n���ַ������ͷָ���ַ��HC[0]����

	char *cd=(char*)malloc(n*sizeof(char));
	cd[n-1]='\0';

	for(i=1;i<=n;++i){//��ÿ���ַ��Ļ���������
		int start=n-1;//�����������λ��
		for(int c=i,f=HT[i].parent; f!=0; c=f,f=HT[f].parent){//��Ҷ�ӵ������������
			if(HT[f].lchild==c) {cd[--start]='0';}
			else cd[--start]='1';
		}
		HC[i]=(char*)malloc((n-start)*sizeof(char));//Ϊ��i���ַ��ı������洢�ռ䣬ΪHC��Ԫ��HC[i]��ֵ
		strcpy(HC[i], &cd[start]);//ΪHC[i]ָ��ĵ�ַ��ֵ
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

//3.28//��ʼ��ѭ�������ʾ�Ķ���Q
void InitQueue(LinkQueue &lq){
	lq.front=lq.rear=(QueuePtr)malloc(sizeof(QNode));//ֻ��ʼ������ͷ
	if(!lq.front) exit(OVERFLOW);
	lq.front->next=NULL;
}

//ɾ������(�Ӷ�ͷ֮ǰ��lq.front��ʼɾ��)
Status DetroryQueue(LinkQueue &lq){
	while(lq.front){
		lq.rear=lq.front->next;//�ݴ�
		free(lq.front);
		lq.front=lq.rear;
	}
	return OK;
}

//��β����
Status EnQueue(LinkQueue &lq, QElemType e){
	QueuePtr p_qn=(QueuePtr)malloc(sizeof(QNode));
	if(!p_qn) exit(OVERFLOW);
	p_qn->data=e;	p_qn->next=NULL;
	lq.rear->next=p_qn;	lq.rear=p_qn;
	return OK;
}
//��ͷȥ��
Status DeQueue(LinkQueue &lq, QElemType &e){
	if(lq.front==lq.rear) return ERROR;
	QueuePtr p_qn=lq.front->next;
	lq.front->next=p_qn->next;
	e=p_qn->data;
	if(lq.rear==p_qn) lq.rear=lq.front;//�������lq.front�⣬ֻ��һ��Ԫ�أ���ɾ������пգ���Ҫ�ı�lq.rear��ֵ
	free(p_qn);
}
//���п�
Status QueueEmpty(LinkQueue lq){
	if(lq.rear==lq.front) return 1;//���п�
	else return 0;
}

//����
Status QueueTraverse(LinkQueue lq){
	if(lq.front==lq.rear) return ERROR;
	QueuePtr p_qn=lq.front->next;//ָ�����ͷ
	while(p_qn){
		cout<<p_qn->data<<' ';
		p_qn=p_qn->next;
	}
	cout<<endl;
	return OK;
}
//////////////////////////////////////////////////////////////////////////

//����α���������
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

//����һ�����ڵ�
Bitree GenerateTreeNode(TElemType e, Bitree lptr, Bitree rptr){
	Bitree New_Node;
	New_Node=(Bitree)malloc(sizeof(BiNode));
	if(!New_Node) return ERROR;
	New_Node->lchild=lptr;
	New_Node->rchild=rptr;
	New_Node->data=e;
	return New_Node;
}
//���ƶ�����(�������)
Bitree CopyTree(Bitree T){
	Bitree new_lptr,new_rptr,new_bt;
	if(!T) return NULL;
	if(T->lchild) new_lptr=CopyTree(T->lchild);
	else new_lptr=NULL;
	if(T->rchild) new_rptr=CopyTree(T->rchild);
	else new_rptr=NULL;
	return new_bt=GenerateTreeNode(T->data, new_lptr, new_rptr);
}

//������������(�������)
int Depth_Bitree(Bitree T){
	int l_dep, r_dep, dep_val;
	if(!T) return dep_val=0;
	l_dep=Depth_Bitree(T->lchild);
	r_dep=Depth_Bitree(T->rchild);
	dep_val=1+(l_dep>r_dep?l_dep:r_dep);
	return dep_val;
}

//���������Ҷ�ӽڵ��������������
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
		cout<<"ǰ�����:";
		PreOrderTraverse(t);
		cout<<endl;
		cout<<"�������:";
		InOrderTraverse(t, PrintElement);
		cout<<endl;
		cout<<"��α���:";
		BFSTraverse(t, PrintElement);
		cout<<endl<<"�������:"<<Depth_Bitree(t);
		Count_Leaf(t, n_leaf);
		cout<<endl<<"Ҷ�ӵĸ���:"<<n_leaf;
		cout<<endl;
		AllPath(t, sq);

		Bitree copy_tree;
		copy_tree=CopyTree(t);
		cout<<endl<<"copy_tree:"<<endl;
		cout<<"ǰ�����:";
		PreOrderTraverse(copy_tree);
		cout<<endl;
		cout<<"�������:";
		InOrderTraverse(copy_tree, PrintElement);
		cout<<endl;
		cout<<"��α���:";
		BFSTraverse(copy_tree, PrintElement);
		cout<<endl<<"�������:"<<Depth_Bitree(copy_tree);
		Count_Leaf(copy_tree, n_leaf_copy);
		cout<<endl<<"Ҷ�ӵĸ���:"<<n_leaf_copy;
		cout<<endl;
		AllPath(copy_tree, sq_copy);
		system("pause");
		
/*
	BiThrTree t,t_thr;
	CreatBitree(t);//������������
	InOrderTraverse_Before(t);//������֮ǰ���������
	cout<<endl;
	InOrderThreading(t_thr, t);//������
	InOrderTraverse_Thr(t_thr, PrintElement);//������֮����������
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