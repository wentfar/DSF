#include <iostream>
#include "Definition.h"

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

using namespace std;

//���Ա��˳��洢�ṹ
typedef struct{
	int * elem;//�洢�ռ��׵�ַ
	int length;//��ǰ����
	int listsize;//�����ɵ��ܳ���
}SqList;

Status InitList_Sq(SqList &L){
	//����һ�����Ա�
	L.elem=(int *)malloc(LIST_INIT_SIZE*sizeof(int));
	if (!L.elem) exit(OVERFLOW);
	L.length=0;
	L.listsize=LIST_INIT_SIZE;
	return OK;
}

//2.10��˳��洢�ṹ�����Ա�L��ɾ����i��Ԫ�����k��Ԫ��,ע��i�ı�Ŵ�0��ʼ
Status DeleteList_Sq_k(SqList &L, int i, int k){
	if (i<0||i>L.length-1||k<0||k+i>L.length) return INFEASIBLE;
	for(int j=0;j<L.length-i-k;j++){
		L.elem[i+j]=L.elem[i+j+k];
	}
	L.length=L.length-k;

	for (int m=0;m<L.length;m++)
	{
		cout<<L.elem[m]<<" ";
	}
	cout<<endl;
	return OK;
}

//2.11�ڷǵݼ���˳���L�в���Ԫ��elem_ins��ʹ���Գ�Ϊ˳�����㷨,�Ӻ���ǰ����
Status InsertOrderList(SqList &L, int elem_ins){
	int i;
	for(i=L.length-1;i>=0,elem_ins<L.elem[i];i--){
		L.elem[i+1]=L.elem[i];
	}
	L.elem[i+1]=elem_ins;
	L.length=L.length+1;

	for (int m=0;m<L.length;m++)
	{
		cout<<L.elem[m]<<" ";
	}
	cout<<endl;
	return OK;
}

//2.12˳���ıȽ�
Status CompareOrderList(SqList A, SqList B){
	for(int i=0;A.elem[i]||B.elem[i];i++){
		if(i<A.length && i>=B.length) return 1;
		if(i>=A.length && i<B.length) return -1;
		if (A.elem[i]!=B.elem[i])
			return A.elem[i]-B.elem[i]>0?1:-1;
	}
		return 0;
}

//2.21˳���ľ͵�����
Status ListOppose_Sq(SqList &L){
	for(int i=0,j=L.length-1;i<L.length/2;i++,j--){
		int temp=L.elem[i];
		L.elem[i]=L.elem[j];
		L.elem[j]=temp;
	}
	return OK;
}

//2.25��Ԫ�ص������е����Ա�A��B��Ԫ�صĽ���������C��
void SqList_Intersect(SqList A,SqList B,SqList &C){
	int i=0; int j=0; int k=0;
	while(A.elem[i] && B.elem[j]){
		if (A.elem[i]<B.elem[j]) i++;
		else if (A.elem[i]>B.elem[j]) j++;
		else {C.elem[k++]=A.elem[i];i++;j++;}
	}
	C.length=k;
}


void main(){
	/*
	//��ʼ��
	SqList sqlist;
	InitList_Sq(sqlist);//Ϊ��������������׼������sqlist��ʼ��Ϊ˳���
	cout<<"����������˳����Ԫ�ظ���(n):"<<endl;
	int n;
	cin>>n;
	if (n>sqlist.listsize) exit(OVERFLOW);
	sqlist.length=n;
	cout<<"������������Ԫ��(�����С�ڵ���"<<n<<"):"<<endl;
	for (int i=0;i<sqlist.length;i++)
	{
	cin>>sqlist.elem[i];
	}

	for (int i=0;i<sqlist.length;i++)
	{
		cout<<sqlist.elem[i]<<" ";
	}
	cout<<endl;

	//2.10ɾ��ָ��λ�õ�Ԫ��
	cout<<"�������ɾ����Ԫ����ʼλ��(i=0,1,2...),��ɾ����Ԫ�ظ���(k)��"<<endl;
	int i,k;
	cin>>i>>k;
	DeleteList_Sq_k(sqlist,i,k);

	//2.11����ָ����Ԫ��
	cout<<"������Ҫ�����Ԫ��(elem_ins)��";
	int elem_ins;
	cin>>elem_ins;
	InsertOrderList(sqlist,elem_ins);
	system("Pause");
	*/

	//////////////////////////////////////////////////////////////////////////

	//2.12˳���ıȽ�
	/*
	while (1)
	{
		SqList a, b;
		InitList_Sq(a);
		InitList_Sq(b);
	
		cout<<"����������˳���a��Ԫ�ظ���(n1):"<<endl;
		int n1;
		cin>>n1;
		if (n1>a.listsize) exit(OVERFLOW);
		a.length=n1;
		cout<<"������������Ԫ��(�����С�ڵ���"<<n1<<"):"<<endl;
		for (int i=0;i<a.length;i++)
		{
			cin>>a.elem[i];
		}
	
		for (int i=0;i<a.length;i++)
		{
			cout<<a.elem[i]<<" ";
		}
		cout<<endl;
	
		cout<<"����������˳���b��Ԫ�ظ���(n2):"<<endl;
		int n2;
		cin>>n2;
		if (n2>b.listsize) exit(OVERFLOW);
		b.length=n2;
		cout<<"������������Ԫ��(�����С�ڵ���"<<n2<<"):"<<endl;
		for (int i=0;i<b.length;i++)
		{
			cin>>b.elem[i];
		}
	
		for (int i=0;i<b.length;i++)
		{
			cout<<b.elem[i]<<" ";
		}
		cout<<endl;
		cout<<CompareOrderList(a,b);
		system("Pause");
	}
	*/

	//////////////////////////////////////////////////////////////////////////
	/*
	//2.21
	while (1)
	{
		SqList sqlist;
		InitList_Sq(sqlist);//Ϊ��������������׼������sqlist��ʼ��Ϊ˳���
		cout<<"����������˳����Ԫ�ظ���(n):"<<endl;
		int n;
		cin>>n;
		if (n>sqlist.listsize) exit(OVERFLOW);
		sqlist.length=n;
		cout<<"������������Ԫ��(�����С�ڵ���"<<n<<"):"<<endl;
		for (int i=0;i<sqlist.length;i++)
		{
			cin>>sqlist.elem[i];
		}
	
		for (int i=0;i<sqlist.length;i++)
		{
			cout<<sqlist.elem[i]<<" ";
		}
		cout<<endl;
		//˳���͵�����
		ListOppose_Sq(sqlist);
	
		for (int i=0;i<sqlist.length;i++)
		{
			cout<<sqlist.elem[i]<<" ";
		}
		cout<<endl;
	
		system("Pause");
	}
	*/

//////////////////////////////////////////////////////////////////////////
	while (1)
	{
		//��ʼ��
		SqList A;
		InitList_Sq(A);
		cout<<"����������˳����Ԫ�ظ���(n):"<<endl;
		int n;
		cin>>n;
		if (n>A.listsize) exit(OVERFLOW);
		A.length=n;
		cout<<"������������Ԫ��(�����С�ڵ���"<<n<<"):"<<endl;
		for (int i=0;i<A.length;i++)
		{
			cin>>A.elem[i];
		}
	
		for (int i=0;i<A.length;i++)
		{
			cout<<A.elem[i]<<" ";
		}
		cout<<endl;
	
		SqList B;
		InitList_Sq(B);
		cout<<"����������˳����Ԫ�ظ���(n1):"<<endl;
		int n1;
		cin>>n1;
		if (n1>B.listsize) exit(OVERFLOW);
		B.length=n1;
		cout<<"������������Ԫ��(�����С�ڵ���"<<n1<<"):"<<endl;
		for (int i=0;i<B.length;i++)
		{
			cin>>B.elem[i];
		}
	
		for (int i=0;i<B.length;i++)
		{
			cout<<B.elem[i]<<" ";
		}
		cout<<endl;
	
		SqList C;
		InitList_Sq(C);
		
		SqList_Intersect(A, B, C);
		
		for (int i=0;i<C.length;i++)
		{
			cout<<C.elem[i]<<" ";
		}
		cout<<endl;
		system("pause");
	}
}