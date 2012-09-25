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

//˳������һ����ͷ��㵥����Ԫ������Ϊchar
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

//˳������һ����ͷ��㵥����Ԫ������Ϊint
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

//��������һ����ͷ��㵥����Ԫ������Ϊint
void CreatList_L(LinkList &L,int n){
	L=(LinkList)malloc(sizeof(LNode));
	L->next=NULL;
	cout<<"��Ӻ�ǰ������������:"<<endl;
	for (int i=n;i>0;i--)
	{
		LinkList p=(LinkList)malloc(sizeof(LNode));
		cin>>p->data;
		p->next=L->next;
		L->next=p;
	}
}

//��������һ����ͷ��㵥����Ԫ������Ϊchar
void CreatList_L(LinkList_C &L,int n){
	L=(LinkList_C)malloc(sizeof(LNode_C));
	L->next=NULL;
	cout<<"��Ӻ�ǰ������������:"<<endl;
	for (int i=n;i>0;i--)
	{
		LinkList_C p=(LinkList_C)malloc(sizeof(LNode_C));
		cin>>p->data;
		p->next=L->next;
		L->next=p;
	}
}

//��������һ����ͷ��㵥ѭ������Ԫ������Ϊint
void CreatList_L_Cir(LinkList &L,int n){
	L=(LinkList)malloc(sizeof(LNode));
	L->next=L;//���Ԫ��ָ��L
	cout<<"��Ӻ�ǰ������������:"<<endl;
	for (int i=n;i>0;i--)
	{
		LinkList p=(LinkList)malloc(sizeof(LNode));
		cin>>p->data;
		p->next=L->next;
		L->next=p;
	}
}

//��������һ����ͷ��㵥ѭ������Ԫ������Ϊchar
void CreatList_L_Cir(LinkList_C &L,int n){
	L=(LinkList_C)malloc(sizeof(LNode_C));
	L->next=L;//���Ԫ��ָ��L
	cout<<"��Ӻ�ǰ������������:"<<endl;
	for (int i=n;i>0;i--)
	{
		LinkList_C p=(LinkList_C)malloc(sizeof(LNode_C));
		cin>>p->data;
		p->next=L->next;
		L->next=p;
	}
}

//��������һ����ͷ���˫ѭ������Ԫ������Ϊint
void CreatList_L_Cir_Dul(LinkList_Dul &L,int n){
	L=(LinkList_Dul)malloc(sizeof(LNode_Dul));
	L->next=L;//���Ԫ��ָ��L
	cout<<"��Ӻ�ǰ������������:"<<endl;
	for (int i=n;i>0;i--)
	{
		LinkList_Dul p=(LinkList_Dul)malloc(sizeof(LNode_Dul));
		if(i==n) L->prior=p;
		p->freq=0;
		cin>>p->data;

		p->prior=L;//ǰ��
		L->next->prior=p;//ǰ��

		p->next=L->next;//���
		L->next=p;//��̣��˴�L->�ݴ�p�Թ��´�ѭ��ʹ��
	}
}

//˳������һ����ͷ��������
void CreatList_L_NoHeader(LinkList &L, int n){
	if (n<=0) cout<<"�����ȴ���";
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

//2.13�ڴ�ͷ���ĵ�����ṹ��ʵ�����Ա����Locate(L,x)
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

//2.14�ڴ�ͷ���ĵ�����ṹ��ʵ�����Ա����Length(L)
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

//����ת��������Ȼ��ǰ������
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


//���ҵ�����K���ڵ㣬����˫ָ�룬���õ�һ����������k���ڵ㣬���ͬʱ���ڶ���ָ�뿪ʼ��ͷ����������һ���ڵ㵽β��ʱ���ڶ����ڵ㼴Ϊ������k���ڵ�
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

//���ҵ������м�Ԫ�أ����ڣ�n/2+1������㡣
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

// ��β��ͷ��ӡ������ʹ��ջ
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

// ��β��ͷ��ӡ�������ݹ�
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

// ��֪����������a ��b �������򣬰����Ǻϲ���һ��������Ȼ����
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

	//����δ�����ĺ����ڵ�
	if (p1)
	{
		p->next = p1;
	}
	else
	{
		p->next = p2;
	}
}

// ��֪����������pHead1 ��pHead2 �������򣬰����Ǻϲ���һ��������Ȼ���򣬵ݹ�
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

//2.15��ָ֪��ha��hb�ֱ�ָ�������������ͷ��㣬������֪��������ĳ��ȷֱ�Ϊm��n����дһ�㷨������������������һ�𣬼���ָ��hcָ�����Ӻ�������ͷ��㣬��Ҫ���㷨�Ծ����̵ܶ�ʱ������������㡣���������㷨��ʱ�临�Ӷ�
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

//�ж�һ�����������Ƿ��л�����������ָ�룬��ָ��һ���ڻ���׷������ָ�롣
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

// �ж������������Ƿ��ཻ
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

// �������������ཻ�ĵ�һ���ڵ㣬�ȶ�����������ĵ�ǰ��㣬ʹ֮��β�ڵ�ľ������
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

	//����ཻ�������ཻ�ڵ�
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

//��֪һ���������д��ڻ�������뻷�еĵ�һ���ڵ㣬���ж��Ƿ���ڻ����ҳ������ڵ㣬Ȼ��ԭ����ת��Ϊ�����ཻ������һ��Ϊ��ͷ��㵽�����ڵ㣬��һ��Ϊ�������ڵ����һ���ڵ㵽�����ڵ�
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

		//���ж��Ƿ���ڻ�
		if (p1 == p2)
		{
			LinkList ptr_circle = p1->next;//������1��ͷ���
			int len_circle = 1;
			while(ptr_circle != p1)
			{
				ptr_circle = ptr_circle->next;
				len_circle++;
			}

			LinkList ptr_in = L;//������2��ͷ���
			int len_in = 1;
			while(ptr_in != p1)
			{
				ptr_in = ptr_in->next;
				len_in++;
			}

			//��ȡ1��2��������ĳ��Ȳ�ֵ
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

			//��ȡ��һ�������ڵ�
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

//����һ������ͷָ��pHead��һ�ڵ�ָ��pToBeDeleted��O(1)ʱ�临�Ӷ�ɾ���ڵ�pToBeDeleted������ɾ���ڵ����һ���ڵ�����ݸ��Ƶ���ɾ���ڵ㣬Ȼ��ɾ����ɾ���ڵ���һ�ڵ�
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
	else//��ɾ���ڵ�Ϊ���һ���ڵ�
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

//2.16��ָ֪��la��lb�ֱ�ָ��������ͷ��㵥�����е���Ԫ��㡣�����㷨�Ǵӱ�la��ɾ���Ե�i��Ԫ����len��Ԫ�أ�������ȡ����һ���ַ���result�����С�
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
	if (!p) return INFEASIBLE;//i��������

	int t=1;
	result=p;
	while(p && t<len){
		t++;
		p=p->next;
	}
	if(!p) return INFEASIBLE;//len��������

	if (p_pre)
	{
		p_pre->next=p->next;
	} 
	else
	{
		la=p->next;//i=1�������p_preδ��ʼ��
	}
	p->next=NULL;
	return OK;
}

//2.16��ָ֪��la��lb�ֱ�ָ��������ͷ��㵥�����е���Ԫ��㡣�����㷨������result���뵽����lb��i��Ԫ��֮ǰ��
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

//2.19��֪���Ա��е�Ԫ����ֵ�����������У����Ե��������洢�ṹ����дһ��Ч���㷨��ɾ����������ֵ����mink��С��maxk��Ԫ�أ������д���������Ԫ�أ���ͬʱ�ͷű�ɾ���ռ䣬����������㷨��ʱ�临�Ӷ�
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

//2.20��֪���Ա��е�Ԫ����ֵ�����������У����Ե��������洢�ṹ����дһ��Ч���㷨ɾ����������ֵ��ͬ����Ԫ�ء�
void ListDelete_LSameNode(LinkList &L){
	LinkList p=L, p_pre=L, q;
	p=p->next;
	while(p->next){
		p_pre=p;
		p=p->next;
		while(p && p_pre->data==p->data){//�����ж����pre��ͬ��Ԫ�أ�����p
			p_pre->next=p->next;
			q=p;
			p=p->next;
			free(q);
		}
		if (!p) break;
	}
}

//2.24������������Ԫ��ֵ�����������е����Ա�A��B�����Ե��������洢�ṹ�����д�㷨��A���B��鲢��һ����Ԫ��ֵ�ݼ����򣨼��ǵ�������������к���ֵ��ͬ��Ԫ�أ����е����Ա�C����Ҫ������ԭ����A���B���Ľ��ռ乹��C��
Status ListMergeOppose_L(LinkList &A,LinkList &B,LinkList &C){
	LinkList pa=A->next, pb=B->next, pc_pre=NULL, pc, q;
	while(pa || pb){
		if (pa && (!pb || pa->data <= pb->data)){//ע��if������
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

//2.26��Ԫ�ص������е����Ա�A��B��Ԫ�صĽ���������C��
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

//2.33�ѵ�����L��Ԫ��(char)�����ͷ�Ϊ����ѭ������.A, B, CΪ��ͷ���ĵ�ѭ����������.
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

//2.38��freq���˫��ѭ�������ϵĲ���
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

			//ɾ��p
			p->prior->next=p->next;
			p->next->prior=p->prior;

			//����p
			p->next=q->next;//�Ƚ��õ�q->nextָ�봦����
			q->next->prior=p;

			q->next=p;//Ȼ��ı�q->nextֵ
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
	cout<<"����������L�ĳ���(n):";
	int n;
	cin>>n;
	CreatList_L(L,n);
	LinkList p=L;
	cout<<"����L����������:"<<endl;
	while (p)
	{
	cout<<p->data<<endl;
	p=p->next;
	}

	LinkList L1=0;
	cout<<"����������L1�ĳ���(n1):";
	int n1;
	cin>>n1;
	CreatList_L(L1,n1);
	LinkList p1=L1;
	cout<<"����L1����������:"<<endl;
	while (p1)
	{
	cout<<p1->data<<endl;
	p1=p1->next;
	}

	LinkList Lc;
	MergeList_L(L,L1,Lc);
	cout<<"�ϲ�֮���������Lc:"<<endl;
	LinkList pc=Lc;
	while (pc)
	{
	cout<<pc->data<<endl;
	pc=pc->next;
	}

	cout<<"���������붨λ���ַ�(x):";
	int x;
	cin>>x;
	cout<<Locate(Lc,x)<<endl;
	cout<<"����ĳ���(n)"<<ListLength_L(Lc)<<endl;*/

//////////////////////////////////////////////////////////////////////////

	/*
	while (1)
	{
		//��ʼ������
		LinkList L_NoHeader=0;
		cout<<"����������L_NoHeader�ĳ���(n_nh):";
		int n_nh;
		cin>>n_nh;
		cout<<"��˳����������L_NoHeader:"<<endl;
		CreatList_L_NoHeader(L_NoHeader, n_nh);
		LinkList p_nh=L_NoHeader;
		cout<<"����L_NoHeader����������:"<<endl;
		while (p_nh)
		{
			cout<<p_nh->data<<endl;
			p_nh=p_nh->next;
		}

		//2.16ȡ�������е�һ����
		LinkList Link_result;
		cout<<"����������ȡ�����ַ���ʼλ�ú͸���:"<<endl;
		int start,num;
		cin>>start>>num;
		int status = Extract(L_NoHeader, start, num, Link_result);

		//ȡ��֮�������
		if (status == 1)
		{
			LinkList p_NoHeader=L_NoHeader;
			cout<<"����L_NoHeader����������:"<<endl;
			while (p_NoHeader)
			{
				cout<<p_NoHeader->data<<endl;
				p_NoHeader=p_NoHeader->next;
			}

			LinkList p_result=Link_result;
			cout<<"����Link_result����������:"<<endl;
			while (p_result)
			{
				cout<<p_result->data<<endl;
				p_result=p_result->next;
			}
		}
		else
		{
			cout<<"��ȡ��������"<<endl;
		}

		//2.16��ȡ�����������ָ����λ��
		cout<<"����λ��:";
		int p_ins, status_ins;
		cin>>p_ins;
		status_ins = Insert(L_NoHeader, p_ins, Link_result);
		if (status_ins == 1)
		{
			LinkList p_ins=L_NoHeader;
			cout<<"����Link_result����������:"<<endl;
			while (p_ins)
			{
				cout<<p_ins->data<<endl;
				p_ins=p_ins->next;
			}
		}
		else{
			cout<<"��������;";
		}
		system("pause");
	}*/

//////////////////////////////////////////////////////////////////////////
	/*
	//2.19
	while (1)
	{
		LinkList L=0;
		cout<<"����������L�ĳ���(n):";
		int n;
		cin>>n;
		CreatList_L(L,n);
		LinkList p=L;
		cout<<"����L����������:"<<endl;
		while (p)
		{
			cout<<p->data<<endl;
			p=p->next;
		}
		
		cout<<"������mink��maxk:";
		float min_num, max_num;
		cin>>min_num>>max_num;
		ListDelete_L(L, min_num, max_num);
		
		LinkList p_new=L;
		cout<<"����L�����ݸ���֮������:"<<endl;
		while (p_new)
		{
			cout<<p_new->data<<endl;
			p_new=p_new->next;
		}
		cout<<system("pause");
	}*/

//////////////////////////////////////////////////////////////////////////
/*
	//2.20ɾ������������ظ�Ԫ��
	while (1)
	{
		LinkList L=0;
		cout<<"����������L�ĳ���(n):";
		int n;
		cin>>n;
		CreatList_L(L,n);
		LinkList p=L;
		cout<<"����L����������:"<<endl;
		while (p)
		{
			cout<<p->data<<endl;
			p=p->next;
		}

		ListDelete_LSameNode(L);

		LinkList p_new=L;
		cout<<"����L�����ݸ���֮������:"<<endl;
		while (p_new)
		{
			cout<<p_new->data<<endl;
			p_new=p_new->next;
		}
		cout<<system("pause");
	}
	*/
	//////////////////////////////////////////////////////////////////////////
	//2.22����͵�����
/*
	while (1)
	{
		LinkList L=0;
		cout<<"����������L�ĳ���(n):";
		int n;
		cin>>n;
		CreatList_L(L,n);
		LinkList p=L;
		cout<<"����L����������:"<<endl;
		while (p)
		{
			cout<<p->data<<endl;
			p=p->next;
		}

		ListOppose_L(L);

		LinkList p_new=L;
		cout<<"����L�����ݸ���֮������:"<<endl;
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
		cout<<"����������L�ĳ���(n):";
		int n;
		cin>>n;
		CreatList_L(L,n);
		LinkList p=L;
		cout<<"����L����������:"<<endl;
		while (p)
		{
			cout<<p->data<<endl;
			p=p->next;
		}
	
		LinkList L1=0;
		cout<<"����������L1�ĳ���(n1):";
		int n1;
		cin>>n1;
		CreatList_L(L1,n1);
		LinkList p1=L1;
		cout<<"����L1����������:"<<endl;
		while (p1)
		{
			cout<<p1->data<<endl;
			p1=p1->next;
		}
	
		LinkList Lc;
		ListMergeOppose_L(L,L1,Lc);
		cout<<"�ϲ�֮���������Lc:"<<endl;
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
//2.26��Ԫ�ص������е����Ա�A��B��Ԫ�صĽ���������C��
	while(1){
		LinkList L=0;
		cout<<"����������L�ĳ���(n):";
		int n;
		cin>>n;
		CreatList_L(L,n);
		LinkList p=L;
		cout<<"����L����������:"<<endl;
		while (p)
		{
			cout<<p->data<<endl;
			p=p->next;
		}

		LinkList L1=0;
		cout<<"����������L1�ĳ���(n1):";
		int n1;
		cin>>n1;
		CreatList_L(L1,n1);
		LinkList p1=L1;
		cout<<"����L1����������:"<<endl;
		while (p1)
		{
			cout<<p1->data<<endl;
			p1=p1->next;
		}

		LinkList Lc;
		LinkList_Intersect(L,L1,Lc);
		cout<<"Ԫ�ص������е����Ա�A��B��Ԫ�صĽ���Lc:"<<endl;
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
		cout<<"����������L�ĳ���(n):";
		int n;
		cin>>n;
		CreatList_L(L,n);
		LinkList_C p=L;
		cout<<"����L����������:"<<endl;
		while (p)
		{
			cout<<p->data<<endl;
			p=p->next;
		}

		LinkList_C A, B, C;
		LinkList_Divide(L, A, B, C);

		LinkList_C pa=A->next;
		cout<<"����A����������:"<<endl;
		while (pa!=A)
		{
			cout<<pa->data<<endl;
			pa=pa->next;
		}
		cout<<endl;

		LinkList_C pb=B->next;
		cout<<"����B����������:"<<endl;
		while (pb!=B)
		{
			cout<<pb->data<<endl;
			pb=pb->next;
		}
		cout<<endl;

		LinkList_C pc=C->next;
		cout<<"����C����������:"<<endl;
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
		cout<<"������������:"<<endl;
		int n;
		cin>>n;
		CreatList_L_Cir_Dul(L,n);

		LinkList_Dul p=L->next;
		cout<<"����C������˳���������:"<<endl;
		while (p!=L)
		{
			cout<<p->data<<endl;
			p=p->next;
		}
		cout<<endl;

		LinkList_Dul pre=L->prior;
		cout<<"����C�����������������:"<<endl;
		while (pre!=L)
		{
			cout<<pre->data<<endl;
			pre=pre->prior;
		}
		cout<<endl;

		while (1){
			int x;
			cout<<"�����붨λ��Ԫ��:";
			cin>>x;

			Locate_DuList(L, x);
	
			LinkList_Dul p1=L->next;
			cout<<"����C������˳���������:"<<endl;
			while (p1!=L)
			{
				cout<<p1->data<<" "<<p1->freq<<endl;
				p1=p1->next;
			}
			cout<<endl;
	
			LinkList_Dul p2=L->prior;
			cout<<"����C�����������������:"<<endl;
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
	cout<<"����L����������:"<<endl;
	while (p)
	{
		cout<<p->data<<endl;
		p=p->next;
	}
	system("pause");*/

}
