#include <iostream>
#include "Definition.h"
#include <stack>
#include <ctype.h>

using namespace std;

typedef struct LNode{
	int data;
	struct LNode *next;
}LNode,*LinkList;

typedef struct LNode_C{
	char data;
	struct LNode_C *next;
}LNode_C,*LinkList_C;

typedef struct LNode_Dul{
	int data;
	struct LNode_Dul *next;
	struct LNode_Dul *prior;
	int freq;
}LNode_Dul,*LinkList_Dul;

//顺序生成一个有头结点单链表，元素类型为char
void CreatList_L(LinkList_C &L){
	L=new LNode_C();
	L->next=NULL;
	LinkList_C q=L;
	char c;
	while((c=getchar())!='\n'){
		LinkList_C p=new LNode_C();
		p->data=c;
		p->next=NULL;

		q->next=p;
		q=p;
	}
}

//顺序生成一个有头结点单链表，元素类型为int
void CreatList(LinkList *ptr_L)
{
	*ptr_L = new LNode();
	(*ptr_L)->next = NULL;
	LinkList p = *ptr_L;

	int data;
	while (cin>>data)
	{
		LinkList temp_L = new LNode();
		temp_L->next = NULL;
		temp_L->data = data;
		p->next = temp_L;
		p = temp_L;
	}
}

//逆序生成一个有头结点单链表，元素类型为int
void CreatList_L(LinkList &L,int n){
	L=(LinkList)malloc(sizeof(LNode));
	L->next=NULL;
	cout<<"请从后到前输入链表内容:"<<endl;
	for (int i=n;i>0;i--)
	{
		LinkList p=(LinkList)malloc(sizeof(LNode));
		cin>>p->data;
		p->next=L->next;
		L->next=p;
	}
}

//逆序生成一个有头结点单链表，元素类型为char
void CreatList_L(LinkList_C &L,int n){
	L=(LinkList_C)malloc(sizeof(LNode_C));
	L->next=NULL;
	cout<<"请从后到前输入链表内容:"<<endl;
	for (int i=n;i>0;i--)
	{
		LinkList_C p=(LinkList_C)malloc(sizeof(LNode_C));
		cin>>p->data;
		p->next=L->next;
		L->next=p;
	}
}

//逆序生成一个有头结点单循环链表，元素类型为int
void CreatList_L_Cir(LinkList &L,int n){
	L=(LinkList)malloc(sizeof(LNode));
	L->next=L;//最后元素指向L
	cout<<"请从后到前输入链表内容:"<<endl;
	for (int i=n;i>0;i--)
	{
		LinkList p=(LinkList)malloc(sizeof(LNode));
		cin>>p->data;
		p->next=L->next;
		L->next=p;
	}
}

//逆序生成一个有头结点单循环链表，元素类型为char
void CreatList_L_Cir(LinkList_C &L,int n){
	L=(LinkList_C)malloc(sizeof(LNode_C));
	L->next=L;//最后元素指向L
	cout<<"请从后到前输入链表内容:"<<endl;
	for (int i=n;i>0;i--)
	{
		LinkList_C p=(LinkList_C)malloc(sizeof(LNode_C));
		cin>>p->data;
		p->next=L->next;
		L->next=p;
	}
}

//逆序生成一个有头结点双循环链表，元素类型为int
void CreatList_L_Cir_Dul(LinkList_Dul &L,int n){
	L=(LinkList_Dul)malloc(sizeof(LNode_Dul));
	L->next=L;//最后元素指向L
	cout<<"请从后到前输入链表内容:"<<endl;
	for (int i=n;i>0;i--)
	{
		LinkList_Dul p=(LinkList_Dul)malloc(sizeof(LNode_Dul));
		if(i==n) L->prior=p;
		p->freq=0;
		cin>>p->data;

		p->prior=L;//前驱
		L->next->prior=p;//前驱

		p->next=L->next;//后继
		L->next=p;//后继，此处L->暂存p以供下次循环使用
	}
}

//顺序生成一个无头结点的链表
void CreatList_L_NoHeader(LinkList &L, int n){
	if (n<=0) cout<<"链表长度错误！";
	if (n>=1)
	{
		LinkList p;
		LinkList p_pre=0;
		L=p=(LinkList)malloc(sizeof(LNode));
		cin>>p->data;
		for(int i=1;i<n;i++){
			p_pre=p;
			p=(LinkList)malloc(sizeof(LNode));
			cin>>p->data;
			p_pre->next=p;
		}
		p->next=NULL;
	}
}

//2.13在带头结点的单链表结构上实现线性表操作Locate(L,x)
int Locate(LinkList L,int x){
	int i=0;
	LinkList p=L;
	while(p&&p->data!=x){
		p=p->next;
		i++;
	}
	if (!p) return 0;
	return i;
}

//2.14在带头结点的单链表结构上实现线性表操作Length(L)
int ListLength_L(LinkList L){
	if (L == NULL)
	{
		throw "error";
	}
	int i=0;
	LinkList p=L->next;
	while (p){
	p=p->next;
	i++;
	}
	return i;
}

//链表反转，遍历，然后前方插入
void InverseList(LinkList *L)
{
	if ((*L) == NULL)
	{
		throw "error";
	}

	if ((*L)->next == NULL || (*L)->next->next ==NULL)
	{
		return;
	}

	LinkList pre = (*L)->next;
	LinkList p = (*L)->next->next;

	LinkList tmpFirst = (*L)->next;

	while(p)
	{
		LinkList tmp = p->next;

		(*L)->next = p;
		p->next = pre;

		pre = p;
		p = tmp;
	}
	tmpFirst->next = NULL; 
}


//查找倒数第K个节点，设立双指针，先让第一个遍历到第k个节点，与此同时，第二个指针开始从头遍历，当第一个节点到尾部时，第二个节点即为倒数第k个节点
LNode* FindReverse(LinkList L, int k)
{
	if (L == NULL || k == 0)
	{
		throw "error";
	}

	LinkList p = L->next;
	LinkList q = L->next;
	int i = 0;
	while(p && i < k)
	{
		i++;
		p = p->next;
	}

	if (i < k)
	{
		return NULL;
	}
	else
	{
		while(p)
		{
			p = p->next;
			q = q->next;
		}
		return q;
	}
}

//查找单链表中间元素，即第（n/2+1）个结点。
LNode* FindMiddle(LinkList L)
{
	if (L == NULL)
	{
		throw "error";
	}
	if (L->next == NULL)
	{
		return NULL;
	}

	LinkList p1 = L;
	LinkList p2 = L;
	
	while(p1 && p2)
	{
		p1 = p1->next;
		p2 = p2->next;
		if (p2)
		{
			p2 = p2->next;
		}
	}
	return p1;
}

// 从尾到头打印单链表，使用栈
void VisitListReverse_Stack(LinkList L)
{
	if (L == NULL)
	{
		throw "error";
	}
	stack<LNode> s;
	LinkList p = L;
	while(p)
	{
		s.push(*p);
		p = p->next;
	}

	while(!s.empty())
	{
		cout<<((s.top()).data)<<' ';
		s.pop();
	}
}

// 从尾到头打印单链表，递归
void VisitListReverse_Recur(LinkList L)
{
	if (L == NULL) 
	{
		return;
	}
	else
	{
		VisitListReverse_Recur(L->next);
		cout<<L->data<<' ';
	}
}

// 已知两个单链表a 和b 各自有序，把它们合并成一个链表依然有序
void MergeSortedList(LinkList a,LinkList b,LinkList &c)
{
	if (a == NULL && b == NULL)
	{
		throw "error";
		return;
	}
	else if (b != NULL && a == NULL)
	{
		c = b;
		return;
	}
	else if (a != NULL  && b == NULL)
	{
		c = a;
		return;
	}
	
	LinkList p1 = a;
	LinkList p2 = b;
	LinkList p = NULL; 
	if (p1->data != NULL && p2->data != NULL && p1->data > p2->data)
	{
		p = c = p2;
	}
	else
	{
		p = c = p1;
	}

	p1 = p1->next;
	p2 = p2->next;

	while(p1 && p2)
	{
		if (p1->data > p2->data)
		{
			p->next = p2;
			p = p2;
			p2 = p2->next;
		}
		else
		{
			p->next = p1;
			p = p1;
			p1 = p1->next;
		}
	}

	//连接未遍历的后续节点
	if (p1)
	{
		p->next = p1;
	}
	else
	{
		p->next = p2;
	}
}

// 已知两个单链表pHead1 和pHead2 各自有序，把它们合并成一个链表依然有序，递归
LNode* MergeSortedList_Recursive(LinkList pHead1,LinkList pHead2)
{
	if(pHead1 == NULL)  
		return pHead2;  
	if(pHead2 == NULL)  
		return pHead1;  
	LinkList pHeadMerged = NULL;  
	if(pHead1->data < pHead2->data)  
	{  
		pHeadMerged = pHead1;  
		pHeadMerged->next = MergeSortedList_Recursive(pHead1->next, pHead2);  
	}  
	else  
	{  
		pHeadMerged = pHead2;  
		pHeadMerged->next = MergeSortedList_Recursive(pHead1, pHead2->next);  
	}  
	return pHeadMerged; 
}

//2.15已知指针ha和hb分别指向两个单链表的头结点，并且已知两个链表的长度分别为m和n。试写一算法将这两个链表连接在一起，假设指针hc指向连接后的链表的头结点，并要求算法以尽可能短的时间完成连接运算。请分析你的算法的时间复杂度
void MergeList_L(LinkList ha,LinkList hb,LinkList &hc){
	LinkList pa=ha;
	LinkList pb=hb;
	while(pa->next&&pb->next){
		pa=pa->next;
		pb=pb->next;
	}
	if (!pa->next){
		hc=hb;
		while(pb->next) pb=pb->next;
		pb->next=ha->next;
	}
	else{
		hc=ha;
		while(pa->next) pa=pa->next;
		pa->next=hb->next;
	}
}

//判断一个单链表中是否有环，设立快慢指针，快指针一定在环内追赶上慢指针。
bool HasCircle(LinkList L)
{
	if (L == NULL)
	{
		throw "error";
	}

	LinkList p1 = L;
	LinkList p2 = L;

	while(p2->next != NULL && p2->next->next != NULL)
	{
		p1 = p1->next;
		p2 = p2->next->next;

		if (p1 == p2)
		{
			return true;
		}
	}
	return false;
}

// 判断两个单链表是否相交
bool Intersect(LinkList L1, LinkList L2)
{
	if (L1 == NULL || L2 == NULL)
	{
		throw "error";
	}

	LinkList p1 = L1;
	while(p1->next != NULL)
	{
		p1 = p1->next;
	}

	LinkList p2 = L2;
	while(p2->next != NULL)
	{
		p2 = p2->next;
	}

	if (p1 == p2)
	{
		return true;
	}
	return false;
}

// 求两个单链表相交的第一个节点，先对齐两个链表的当前结点，使之到尾节点的距离相等
LNode* FindFirsrtIntersect(LinkList L1, LinkList L2)
{
	if (L1 == NULL || L2 == NULL)
	{
		throw "error";
	}

	LinkList p1 = L1;
	int len1 = 0;
	while(p1->next != NULL)
	{
		len1++;
		p1 = p1->next;
	}
	int len2 = 0;
	LinkList p2 = L2;
	while(p2->next != NULL)
	{
		len2++;
		p2 = p2->next;
	}

	//如果相交，则求相交节点
	if (p1 == p2)
	{
		if (len1 < len2)
		{
			int i = len2 - len1;
			p2 = L2;
			while(i--)
			{
				p2 = p2->next;
			}
		}
		else
		{
			int i = len1 - len2;
			p1 = L1;
			while(i--)
			{
				p1 = p1->next;
			}
		}

		while(p1 != p2)
		{
			p1 = p1->next;
			p2 = p2->next;
		}
		return p1;
	}
	return NULL;
}

//已知一个单链表中存在环，求进入环中的第一个节点，先判断是否存在环，找出相遇节点，然后将原链表转换为两个相交的链表，一个为从头结点到相遇节点，另一个为从相遇节点的下一个节点到相遇节点
LNode* FindFirstCircleNode(LinkList L)
{
	if (L == NULL)
	{
		throw "error";
	}

	LinkList p1 = L;
	LinkList p2 = L;

	while(p2->next != NULL && p2->next->next != NULL)
	{
		p1 = p1->next;
		p2 = p2->next->next;

		//先判断是否存在环
		if (p1 == p2)
		{
			LinkList ptr_circle = p1->next;//新链表1的头结点
			int len_circle = 1;
			while(ptr_circle != p1)
			{
				ptr_circle = ptr_circle->next;
				len_circle++;
			}

			LinkList ptr_in = L;//新链表2的头结点
			int len_in = 1;
			while(ptr_in != p1)
			{
				ptr_in = ptr_in->next;
				len_in++;
			}

			//求取1、2两个链表的长度差值
			if (len_circle > len_in)
			{
				int k = len_circle - len_in;
				while (k--)
				{
					ptr_circle = ptr_circle->next;
				}
			}
			else
			{
				int k =len_in - len_circle;
				while (k--)
				{
					ptr_in = ptr_in->next;
				}
			}

			//求取第一个相遇节点
			while(ptr_circle != ptr_in)
			{
				ptr_circle = ptr_circle->next;
				ptr_in = ptr_in->next;
			}
			return ptr_circle;
		}
	}
	return NULL;
}

//给出一单链表头指针pHead和一节点指针pToBeDeleted，O(1)时间复杂度删除节点pToBeDeleted，将待删除节点的下一个节点的内容复制到待删除节点，然后删除待删除节点下一节点
void Delete(LinkList pHead, LNode* pToBeDeleted)
{
	if (pHead == NULL || pToBeDeleted == NULL || pHead == pToBeDeleted)
	{
		throw "error";
	}
	LinkList tmp = pToBeDeleted->next;
	if (tmp != NULL)
	{
		pToBeDeleted->data = pToBeDeleted->next->data;
		pToBeDeleted->next = pToBeDeleted->next->next;
		delete tmp;
	} 
	else//待删除节点为最后一个节点
	{
		tmp = pHead;
		while(tmp->next != NULL && tmp->next->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = NULL;
		delete pToBeDeleted;
	}
}

//2.16已知指针la和lb分别指向两个无头结点单链表中的首元结点。下列算法是从表la中删除自第i个元素起共len个元素，并将提取的那一部分放入result链表中。
Status Extract(LinkList &la, int i, int len, LinkList &result){
	if (i<=0||len<0) return INFEASIBLE;
	if (!la) return INFEASIBLE;
	LinkList p=la;
	LinkList p_pre=NULL;
	int k=1;
	while(p && k<i){
		p_pre=p;
		k++;
		p=p->next;
	}
	if (!p) return INFEASIBLE;//i过大的情况

	int t=1;
	result=p;
	while(p && t<len){
		t++;
		p=p->next;
	}
	if(!p) return INFEASIBLE;//len过大的情况

	if (p_pre)
	{
		p_pre->next=p->next;
	} 
	else
	{
		la=p->next;//i=1的情况，p_pre未初始化
	}
	p->next=NULL;
	return OK;
}

//2.16已知指针la和lb分别指向两个无头结点单链表中的首元结点。下列算法将链表result插入到链表lb第i个元素之前。
Status Insert(LinkList &lb, int i, LinkList &result){
	if (i<=0 || !lb || !result)	return INFEASIBLE;
	LinkList p=lb, p_pre, q=result, q_pre;
	if (i == 1)
	{
		while(q){
			q_pre=q;
			q=q->next;
		}
		q_pre->next=lb;
		lb=result;
	} 
	else
	{
		int k=1;
		while(p && k<i){
			p_pre=p;
			p=p->next;
			k++;
		}
		if (!p) return INFEASIBLE;
		while(q){
			q_pre=q;
			q=q->next;
		}
		q_pre->next=p_pre->next;
		p_pre->next=result;
	}
	return OK;

}

//2.19已知线性表中的元素以值递增有序排列，并以单链表作存储结构。试写一高效的算法，删除表中所有值大于mink且小于maxk的元素（若表中存在这样的元素），同时释放被删结点空间，并分析你的算法的时间复杂度
Status ListDelete_L(LinkList &L,float mink, float maxk){
	if (mink>maxk) return ERROR;
	LinkList p=L->next, p_pre=L, q;
	while(p && p->data<maxk){
		if(p->data<=mink){
			p_pre=p;
			p=p->next;
		}
		else{
			q=p;
			p=p->next;
			free(q);
		}
	}
	p_pre->next=p;
	return OK;
	}

//2.20已知线性表中的元素以值递增有序排列，并以单链表作存储结构。试写一高效的算法删除表中所有值相同多余元素。
void ListDelete_LSameNode(LinkList &L){
	LinkList p=L, p_pre=L, q;
	p=p->next;
	while(p->next){
		p_pre=p;
		p=p->next;
		while(p && p_pre->data==p->data){//可能有多个和pre相同的元素，递增p
			p_pre->next=p->next;
			q=p;
			p=p->next;
			free(q);
		}
		if (!p) break;
	}
}

//2.24假设有两个按元素值递增有序排列的线性表A和B，均以单链表作存储结构，请编写算法将A表和B表归并成一个按元素值递减有序（即非递增有序，允许表中含有值相同的元素）排列的线性表C，并要求利用原表（即A表和B表）的结点空间构造C表。
Status ListMergeOppose_L(LinkList &A,LinkList &B,LinkList &C){
	LinkList pa=A->next, pb=B->next, pc_pre=NULL, pc, q;
	while(pa || pb){
		if (pa && (!pb || pa->data <= pb->data)){//注意if的条件
			pc=pa;
			q=pa->next;
			pa->next=pc_pre;
			pa=q;
		}
		else{
			pc=pb;
			q=pb->next;
			pb->next=pc_pre;
			pb=q;
		}
		pc_pre=pc;
	}
	C=A;A->next=pc;
	return OK;
}

//2.26求元素递增排列的线性表A和B的元素的交集并存入C中
void LinkList_Intersect(LinkList A,LinkList B,LinkList &C){
	LinkList pa=A->next, pb=B->next, pc;
	C=pc=(LNode*)malloc(sizeof(LNode));
	while(pa && pb){
		if (pa->data<pb->data){
			pa=pa->next;			
		}
		else if(pa->data<pb->data){
			pb=pb->next;
		}
		else{
			LinkList pc1=(LNode*)malloc(sizeof(LNode));
			pc->next=pc1;
			pc1->data=pa->data;
			pc1->next=NULL;
			pc=pc1;
			pa=pa->next;
			pb=pb->next;
		}
	}
}

//2.33把单链表L的元素(char)按类型分为三个循环链表.A, B, C为带头结点的单循环链表类型.
Status LinkList_Divide(LinkList_C &L, LinkList_C &A, LinkList_C &B, LinkList_C &C){
	LinkList_C s=L->next, a, b, c;
	A=a=(LinkList_C)malloc(sizeof(LNode_C));
	B=b=(LinkList_C)malloc(sizeof(LNode_C));
	C=c=(LinkList_C)malloc(sizeof(LNode_C));
	while(s){
		if (isalpha(s->data))
		{
			a->next=s;
			a=a->next;
		}
		else if(isdigit(s->data)){
			b->next=s;
			b=b->next;
		}
		else{
			c->next=s;
			c=c->next;
		}
		s=s->next;
	}
	a->next=A;
	b->next=B;
	c->next=C;
	return OK;
}

//2.38带freq域的双向循环链表上的查找
LNode_Dul * Locate_DuList(LinkList_Dul &L,int x){
	LinkList_Dul p=L->next, q=NULL;
	while(p!=L && p->data!=x){
			p=p->next;
		}
		if(p==L) return NULL;
		++(p->freq);
		q=p->prior;
		while(q!=L && q->freq<p->freq){
				q=q->prior;
			}

			//删除p
			p->prior->next=p->next;
			p->next->prior=p->prior;

			//插入p
			p->next=q->next;//先将用到q->next指针处理完
			q->next->prior=p;

			q->next=p;//然后改变q->next值
			p->prior=q;

	return p;
}





void main(){
	LinkList L1, L2;
	CreatList(&L1);
	LinkList p = L1;
	while(p)
	{
		cout<<p->data<<' ';
		p = p->next;
	}
	cout<<endl<<ListLength_L(L1)<<endl;

	cin.clear();
	CreatList(&L2);
	p = L2;
	while(p)
	{
		cout<<p->data<<' ';
		p = p->next;
	}
	cout<<endl<<ListLength_L(L2)<<endl;


	LinkList L3 = NULL;
	//MergeList(L1, L2, L3);
	L3 = MergeSortedList_Recursive(L1, L2);

	p = L3;
	while(p)
	{
		cout<<p->data<<' ';
		p = p->next;
	}
	cout<<endl<<ListLength_L(L3)<<endl;
	system("pause");

/*
	LinkList L;
	CreatList(&L);
	LinkList p = L;
	while(p)
	{
		cout<<p->data<<' ';
		p = p->next;
	}
	cout<<endl<<ListLength_L(L)<<endl;

	VisitListReverse(L);
	cout<<endl;

	VisitListReverse_Recur(L);
	cout<<endl;

	cin.clear();

	int k = 0;
	cout<<"input the location:";
	cin>>k;
	LNode *ptr_node;
	try
	{
		ptr_node = FindReverse(L, k);
		if (ptr_node != NULL)
		{
			cout<<"the data is:"<<ptr_node->data<<endl;
		}
	}
	catch(char*)
	{

	}

	try
	{
		ptr_node = FindMiddle(L);
		if (ptr_node != NULL)
		{
			cout<<"the data is:"<<ptr_node->data<<endl;
		}
	}
	catch(char*)
	{

	}


	InverseList(&L);

	p = L;
	while(p)
	{
		cout<<p->data<<' ';
		p = p->next;
	}
	cout<<endl<<ListLength_L(L)<<endl;
	system("pause");*/

/*
	//2.15
	//2.13
	LinkList L=0;
	cout<<"请输入链表L的长度(n):";
	int n;
	cin>>n;
	CreatList_L(L,n);
	LinkList p=L;
	cout<<"链表L的内容如下:"<<endl;
	while (p)
	{
	cout<<p->data<<endl;
	p=p->next;
	}

	LinkList L1=0;
	cout<<"请输入链表L1的长度(n1):";
	int n1;
	cin>>n1;
	CreatList_L(L1,n1);
	LinkList p1=L1;
	cout<<"链表L1的内容如下:"<<endl;
	while (p1)
	{
	cout<<p1->data<<endl;
	p1=p1->next;
	}

	LinkList Lc;
	MergeList_L(L,L1,Lc);
	cout<<"合并之后的新链表Lc:"<<endl;
	LinkList pc=Lc;
	while (pc)
	{
	cout<<pc->data<<endl;
	pc=pc->next;
	}

	cout<<"请输入你想定位的字符(x):";
	int x;
	cin>>x;
	cout<<Locate(Lc,x)<<endl;
	cout<<"链表的长度(n)"<<ListLength_L(Lc)<<endl;*/

//////////////////////////////////////////////////////////////////////////

	/*
	while (1)
	{
		//初始化链表
		LinkList L_NoHeader=0;
		cout<<"请输入链表L_NoHeader的长度(n_nh):";
		int n_nh;
		cin>>n_nh;
		cout<<"请顺序输入链表L_NoHeader:"<<endl;
		CreatList_L_NoHeader(L_NoHeader, n_nh);
		LinkList p_nh=L_NoHeader;
		cout<<"链表L_NoHeader的内容如下:"<<endl;
		while (p_nh)
		{
			cout<<p_nh->data<<endl;
			p_nh=p_nh->next;
		}

		//2.16取出链表中的一部分
		LinkList Link_result;
		cout<<"请输入你想取出的字符起始位置和个数:"<<endl;
		int start,num;
		cin>>start>>num;
		int status = Extract(L_NoHeader, start, num, Link_result);

		//取出之后的链表
		if (status == 1)
		{
			LinkList p_NoHeader=L_NoHeader;
			cout<<"链表L_NoHeader的内容如下:"<<endl;
			while (p_NoHeader)
			{
				cout<<p_NoHeader->data<<endl;
				p_NoHeader=p_NoHeader->next;
			}

			LinkList p_result=Link_result;
			cout<<"链表Link_result的内容如下:"<<endl;
			while (p_result)
			{
				cout<<p_result->data<<endl;
				p_result=p_result->next;
			}
		}
		else
		{
			cout<<"提取参数有误。"<<endl;
		}

		//2.16将取出的链表插入指定的位置
		cout<<"插入位置:";
		int p_ins, status_ins;
		cin>>p_ins;
		status_ins = Insert(L_NoHeader, p_ins, Link_result);
		if (status_ins == 1)
		{
			LinkList p_ins=L_NoHeader;
			cout<<"链表Link_result的内容如下:"<<endl;
			while (p_ins)
			{
				cout<<p_ins->data<<endl;
				p_ins=p_ins->next;
			}
		}
		else{
			cout<<"参数有误;";
		}
		system("pause");
	}*/

//////////////////////////////////////////////////////////////////////////
	/*
	//2.19
	while (1)
	{
		LinkList L=0;
		cout<<"请输入链表L的长度(n):";
		int n;
		cin>>n;
		CreatList_L(L,n);
		LinkList p=L;
		cout<<"链表L的内容如下:"<<endl;
		while (p)
		{
			cout<<p->data<<endl;
			p=p->next;
		}
		
		cout<<"请输入mink和maxk:";
		float min_num, max_num;
		cin>>min_num>>max_num;
		ListDelete_L(L, min_num, max_num);
		
		LinkList p_new=L;
		cout<<"链表L的内容更新之后如下:"<<endl;
		while (p_new)
		{
			cout<<p_new->data<<endl;
			p_new=p_new->next;
		}
		cout<<system("pause");
	}*/

//////////////////////////////////////////////////////////////////////////
/*
	//2.20删除递增链表的重复元素
	while (1)
	{
		LinkList L=0;
		cout<<"请输入链表L的长度(n):";
		int n;
		cin>>n;
		CreatList_L(L,n);
		LinkList p=L;
		cout<<"链表L的内容如下:"<<endl;
		while (p)
		{
			cout<<p->data<<endl;
			p=p->next;
		}

		ListDelete_LSameNode(L);

		LinkList p_new=L;
		cout<<"链表L的内容更新之后如下:"<<endl;
		while (p_new)
		{
			cout<<p_new->data<<endl;
			p_new=p_new->next;
		}
		cout<<system("pause");
	}
	*/
	//////////////////////////////////////////////////////////////////////////
	//2.22链表就地逆置
/*
	while (1)
	{
		LinkList L=0;
		cout<<"请输入链表L的长度(n):";
		int n;
		cin>>n;
		CreatList_L(L,n);
		LinkList p=L;
		cout<<"链表L的内容如下:"<<endl;
		while (p)
		{
			cout<<p->data<<endl;
			p=p->next;
		}

		ListOppose_L(L);

		LinkList p_new=L;
		cout<<"链表L的内容更新之后如下:"<<endl;
		while (p_new)
		{
			cout<<p_new->data<<endl;
			p_new=p_new->next;
		}
		cout<<system("pause");
	}
	*/

//////////////////////////////////////////////////////////////////////////
/*
	//2.24
	while (1)
	{
		LinkList L=0;
		cout<<"请输入链表L的长度(n):";
		int n;
		cin>>n;
		CreatList_L(L,n);
		LinkList p=L;
		cout<<"链表L的内容如下:"<<endl;
		while (p)
		{
			cout<<p->data<<endl;
			p=p->next;
		}
	
		LinkList L1=0;
		cout<<"请输入链表L1的长度(n1):";
		int n1;
		cin>>n1;
		CreatList_L(L1,n1);
		LinkList p1=L1;
		cout<<"链表L1的内容如下:"<<endl;
		while (p1)
		{
			cout<<p1->data<<endl;
			p1=p1->next;
		}
	
		LinkList Lc;
		ListMergeOppose_L(L,L1,Lc);
		cout<<"合并之后的新链表Lc:"<<endl;
		LinkList pc=Lc;
		while (pc)
		{
			cout<<pc->data<<endl;
			pc=pc->next;
		}
	}
	*/

///////////////////////////////////////////////////////////////////////////////////////
/*	
//2.26求元素递增排列的线性表A和B的元素的交集并存入C中
	while(1){
		LinkList L=0;
		cout<<"请输入链表L的长度(n):";
		int n;
		cin>>n;
		CreatList_L(L,n);
		LinkList p=L;
		cout<<"链表L的内容如下:"<<endl;
		while (p)
		{
			cout<<p->data<<endl;
			p=p->next;
		}

		LinkList L1=0;
		cout<<"请输入链表L1的长度(n1):";
		int n1;
		cin>>n1;
		CreatList_L(L1,n1);
		LinkList p1=L1;
		cout<<"链表L1的内容如下:"<<endl;
		while (p1)
		{
			cout<<p1->data<<endl;
			p1=p1->next;
		}

		LinkList Lc;
		LinkList_Intersect(L,L1,Lc);
		cout<<"元素递增排列的线性表A和B的元素的交集Lc:"<<endl;
		LinkList pc=Lc;
		while (pc)
		{
			cout<<pc->data<<endl;
			pc=pc->next;
		}
	}
	*/
	
//////////////////////////////////////////////////////////////////////////
	
	//2.33
/*
	while(1){
		LinkList_C L=0;
		cout<<"请输入链表L的长度(n):";
		int n;
		cin>>n;
		CreatList_L(L,n);
		LinkList_C p=L;
		cout<<"链表L的内容如下:"<<endl;
		while (p)
		{
			cout<<p->data<<endl;
			p=p->next;
		}

		LinkList_C A, B, C;
		LinkList_Divide(L, A, B, C);

		LinkList_C pa=A->next;
		cout<<"链表A的内容如下:"<<endl;
		while (pa!=A)
		{
			cout<<pa->data<<endl;
			pa=pa->next;
		}
		cout<<endl;

		LinkList_C pb=B->next;
		cout<<"链表B的内容如下:"<<endl;
		while (pb!=B)
		{
			cout<<pb->data<<endl;
			pb=pb->next;
		}
		cout<<endl;

		LinkList_C pc=C->next;
		cout<<"链表C的内容如下:"<<endl;
		while (pc!=C)
		{
		cout<<pc->data<<endl;
		pc=pc->next;
		}
		cout<<endl;
	}
	*/

//////////////////////////////////////////////////////////////////////////
	//2.38
/*
	while(1){
		LinkList_Dul L;
		cout<<"请输入链表长度:"<<endl;
		int n;
		cin>>n;
		CreatList_L_Cir_Dul(L,n);

		LinkList_Dul p=L->next;
		cout<<"链表C的内容顺序输出如下:"<<endl;
		while (p!=L)
		{
			cout<<p->data<<endl;
			p=p->next;
		}
		cout<<endl;

		LinkList_Dul pre=L->prior;
		cout<<"链表C的内容逆序输出如下:"<<endl;
		while (pre!=L)
		{
			cout<<pre->data<<endl;
			pre=pre->prior;
		}
		cout<<endl;

		while (1){
			int x;
			cout<<"请输入定位的元素:";
			cin>>x;

			Locate_DuList(L, x);
	
			LinkList_Dul p1=L->next;
			cout<<"链表C的内容顺序输出如下:"<<endl;
			while (p1!=L)
			{
				cout<<p1->data<<" "<<p1->freq<<endl;
				p1=p1->next;
			}
			cout<<endl;
	
			LinkList_Dul p2=L->prior;
			cout<<"链表C的内容逆序输出如下:"<<endl;
			while (p2!=L)
			{
				cout<<p2->data<<" "<<p2->freq<<endl;
				p2=p2->prior;
			}
			cout<<endl;
		}
	}*/

/*
	LinkList_C L=0;
	CreatList_L(L);
	LinkList_C p=L;
	cout<<"链表L的内容如下:"<<endl;
	while (p)
	{
		cout<<p->data<<endl;
		p=p->next;
	}
	system("pause");*/

}
