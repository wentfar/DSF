#include <iostream>
#include "Definition.h"

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

using namespace std;

//线性表的顺序存储结构
typedef struct{
	int * elem;//存储空间首地址
	int length;//当前长度
	int listsize;//能容纳的总长度
}SqList;

Status InitList_Sq(SqList &L){
	//构造一个线性表
	L.elem=(int *)malloc(LIST_INIT_SIZE*sizeof(int));
	if (!L.elem) exit(OVERFLOW);
	L.length=0;
	L.listsize=LIST_INIT_SIZE;
	return OK;
}

//2.10从顺序存储结构的线性表L中删除第i个元素起的k个元素,注意i的编号从0开始
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

//2.11在非递减的顺序表L中插入元素elem_ins并使其仍成为顺序表的算法,从后向前遍历
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

//2.12顺序表的比较
Status CompareOrderList(SqList A, SqList B){
	for(int i=0;A.elem[i]||B.elem[i];i++){
		if(i<A.length && i>=B.length) return 1;
		if(i>=A.length && i<B.length) return -1;
		if (A.elem[i]!=B.elem[i])
			return A.elem[i]-B.elem[i]>0?1:-1;
	}
		return 0;
}

//2.21顺序表的就地逆置
Status ListOppose_Sq(SqList &L){
	for(int i=0,j=L.length-1;i<L.length/2;i++,j--){
		int temp=L.elem[i];
		L.elem[i]=L.elem[j];
		L.elem[j]=temp;
	}
	return OK;
}

//2.25求元素递增排列的线性表A和B的元素的交集并存入C中
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
	//初始化
	SqList sqlist;
	InitList_Sq(sqlist);//为后面两个函数做准备，将sqlist初始化为顺序表。
	cout<<"请输入有序顺序表的元素个数(n):"<<endl;
	int n;
	cin>>n;
	if (n>sqlist.listsize) exit(OVERFLOW);
	sqlist.length=n;
	cout<<"请输入有序表的元素(其个数小于等于"<<n<<"):"<<endl;
	for (int i=0;i<sqlist.length;i++)
	{
	cin>>sqlist.elem[i];
	}

	for (int i=0;i<sqlist.length;i++)
	{
		cout<<sqlist.elem[i]<<" ";
	}
	cout<<endl;

	//2.10删除指定位置的元素
	cout<<"请输入待删除的元素起始位置(i=0,1,2...),待删除的元素个数(k)："<<endl;
	int i,k;
	cin>>i>>k;
	DeleteList_Sq_k(sqlist,i,k);

	//2.11插入指定的元素
	cout<<"请输入要插入的元素(elem_ins)：";
	int elem_ins;
	cin>>elem_ins;
	InsertOrderList(sqlist,elem_ins);
	system("Pause");
	*/

	//////////////////////////////////////////////////////////////////////////

	//2.12顺序表的比较
	/*
	while (1)
	{
		SqList a, b;
		InitList_Sq(a);
		InitList_Sq(b);
	
		cout<<"请输入有序顺序表a的元素个数(n1):"<<endl;
		int n1;
		cin>>n1;
		if (n1>a.listsize) exit(OVERFLOW);
		a.length=n1;
		cout<<"请输入有序表的元素(其个数小于等于"<<n1<<"):"<<endl;
		for (int i=0;i<a.length;i++)
		{
			cin>>a.elem[i];
		}
	
		for (int i=0;i<a.length;i++)
		{
			cout<<a.elem[i]<<" ";
		}
		cout<<endl;
	
		cout<<"请输入有序顺序表b的元素个数(n2):"<<endl;
		int n2;
		cin>>n2;
		if (n2>b.listsize) exit(OVERFLOW);
		b.length=n2;
		cout<<"请输入有序表的元素(其个数小于等于"<<n2<<"):"<<endl;
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
		InitList_Sq(sqlist);//为后面两个函数做准备，将sqlist初始化为顺序表。
		cout<<"请输入有序顺序表的元素个数(n):"<<endl;
		int n;
		cin>>n;
		if (n>sqlist.listsize) exit(OVERFLOW);
		sqlist.length=n;
		cout<<"请输入有序表的元素(其个数小于等于"<<n<<"):"<<endl;
		for (int i=0;i<sqlist.length;i++)
		{
			cin>>sqlist.elem[i];
		}
	
		for (int i=0;i<sqlist.length;i++)
		{
			cout<<sqlist.elem[i]<<" ";
		}
		cout<<endl;
		//顺序表就地逆置
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
		//初始化
		SqList A;
		InitList_Sq(A);
		cout<<"请输入有序顺序表的元素个数(n):"<<endl;
		int n;
		cin>>n;
		if (n>A.listsize) exit(OVERFLOW);
		A.length=n;
		cout<<"请输入有序表的元素(其个数小于等于"<<n<<"):"<<endl;
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
		cout<<"请输入有序顺序表的元素个数(n1):"<<endl;
		int n1;
		cin>>n1;
		if (n1>B.listsize) exit(OVERFLOW);
		B.length=n1;
		cout<<"请输入有序表的元素(其个数小于等于"<<n1<<"):"<<endl;
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