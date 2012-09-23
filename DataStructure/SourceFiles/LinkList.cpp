#include <iostream>
#include "Definition.h"
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
	int i=0;
	LinkList p=L;
	if(p) p=p->next;
	while (p){
	p=p->next;
	i++;
	}
	return i;
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

//2.22�Ե�����ʵ�־͵����á�
Status ListOppose_L(LinkList &L){
	LinkList p_pre=L, p=L->next, q;
	p_pre=p_pre->next;
	p=p->next;
	p_pre->next=NULL;
	while(p){
		q=p->next;

		p->next=p_pre;
		L->next=p;

		p_pre=p;
		p=q;
	}
	return OK;
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

	LinkList_C L=0;
	CreatList_L(L);
	LinkList_C p=L;
	cout<<"����L����������:"<<endl;
	while (p)
	{
		cout<<p->data<<endl;
		p=p->next;
	}
	system("pause");
}
