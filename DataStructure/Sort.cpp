#include <iostream>
#include <string>
#include <iomanip>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
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

typedef struct{
	int begin;
	int end;
}Pair;

//////////////////////////////////////////////////////////////////////////

//有哨兵的插入排序
void Inser_Sort(SqList &sl){
	for(int i=2;i<sl.length;i++){
		sl.elem[0]=sl.elem[i];
		int j;
		for(j=i-1;sl.elem[j]>sl.elem[0];j--){
			sl.elem[j+1]=sl.elem[j]; 
		}
		sl.elem[j+1]=sl.elem[0];//注意是(j+1)
	}
}

//有哨兵的折半插入排序
void BInsertSort(SqList &sl){
	for(int i=2;i<sl.length;i++){
		sl.elem[0]=sl.elem[i];
		int low=1;
		int high=i-1;
		int j;
		while(low<=high){
			int mid=(low+high)/2;
			if(sl.elem[0]<sl.elem[mid]){ high=mid-1; }//下标为mid=high+1的元素为最后一个满足该条件的元素
			else low=mid+1;
		}
		for(j=i-1;j>=high+1;j--){
			sl.elem[j+1]=sl.elem[j];
		}
		sl.elem[j+1]=sl.elem[0];
	}
}

//////////////////////////////////////////////////////////////////////////

#define SIZE 100
#define MAX 32768
typedef struct{
	int/*ElemType*/ key;
	int next;
}SLNode;

typedef struct{
	SLNode r[SIZE];//0号单元为头结点
	int length;
}SLinkListType;

//链表插入排序
void LInsertSort(SLinkListType &sl, /*ElemType*/int R[], int n){
	sl.length=n;
	sl.r[0].key=MAX;
	sl.r[0].next=1;
	sl.r[1].key=R[0];//
	sl.r[1].next=0;//循环链表

	for(int i=2;i<=n;i++){//从r[2]开始
		int j, k;
		for(j=0,k=sl.r[0].next;sl.r[k].key<=R[i-1]/*从R[1]开始*/;j=k,k=sl.r[k].next);//将节点i插入到节点j和k;
		sl.r[j].next=i;sl.r[i].next=k;sl.r[i].key=R[i-1];
	}
}

//根据静态链表中的各节点指针调整记录的位置，使得SL中的记录按关键字非递减有序排列
void Arrange(SLinkListType &sl){
	int p=sl.r[0].next;
	for(int i=1;i<sl.length;++i){

		while(p<i){p=sl.r[p].next;}//找到未排序的第i个记录

		int q=sl.r[p].next;
		if(p!=i){
			SLNode tmp;
			tmp=sl.r[p];
			sl.r[p]=sl.r[i];
			sl.r[i]=tmp;

			sl.r[i].next=p;//指向被移走的记录
		}
		p=q;
	}
}
//////////////////////////////////////////////////////////////////////////

int Delta[]={5,3,2,1};
//一趟希尔排序
void ShellInsert(SqList &sl, int dk){
	for(int i=dk+1;i<sl.length;i++){
		sl.elem[0]=sl.elem[i];
		int j;
		for(j=i-dk;j>0 && sl.elem[j]>sl.elem[0];j-=dk){
			sl.elem[j+dk]=sl.elem[j];
		}
		sl.elem[j+dk]=sl.elem[0];
	}
}

//希尔排序,增量序列(delta[0,...,t-1])
void ShellSort(SqList &sl, int delta[], int t){
	for(int k=0;k<t;k++){ShellInsert(sl, delta[k]);}
}

//////////////////////////////////////////////////////////////////////////

void BubbleSort(int a[], int n){
	bool change;
	for(int i=n-1,change=true;i>=1 && change==true;i--){//i为每一趟比较的次数
		for(int j=0;j<i;j++){//i为每一趟比较的次数
			change=false;
			if(a[j]>a[j+1]){
				int tmp=a[j];
				a[j]=a[j+1];
				a[j+1]=tmp;
				change=true;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////

int Patition(int a[], int low, int high){//一次划分，将顺序表分成分区,low,high分别为高低两个指针
	int pivotkey=a[low];//pivot为枢轴元素的关键字
	while(low<high){//当相等时终止,返回中间元素的下标
		while(low<high && a[high]>=pivotkey) high--;

		int tmp=a[high];
		a[high]=a[low];
		a[low]=tmp;

		while(low<high && a[low]<=pivotkey) low++;

		tmp=a[high];
		a[high]=a[low];
		a[low]=tmp;
	}
	return low;
}




int Patition_Simply(vector<int> &vec, int low, int high){//一次划分，将顺序表分成分区,low,high分别为高低两个指针

	int pivotkey=vec[low];//pivot为枢轴元素的关键字
	int pivot=vec[low];//pivot为枢轴元素记录

	while(low<high){//当相等时终止,返回中间元素的下标
		while(low<high && vec[high]>=pivotkey) high--;

		vec[low]=vec[high];

		while(low<high && vec[low]<=pivotkey) low++;

		vec[high]=vec[low];
	}

	vec[low]=pivot;
	return low;
}

int Patition_Simply(int a[], int low, int high){//一次划分，将顺序表分成分区,low,high分别为高低两个指针

	int pivotkey=a[low];//pivot为枢轴元素的关键字
	int pivot=a[low];//pivot为枢轴元素记录

	while(low<high){//当相等时终止,返回中间元素的下标
		while(low<high && a[high]>=pivotkey) high--;

		a[low]=a[high];

		while(low<high && a[low]<=pivotkey) low++;

		a[high]=a[low];
	}

	a[low]=pivot;
	return low;
}

//递归形式的快速排序
void QSort(int a[], int low, int high){
	if(low>=high) return;
	int pivotloc=Patition_Simply(a, low, high);
	QSort(a, low, pivotloc-1);
	QSort(a, pivotloc+1, high);
}

//Patition_Simply和QSort写在一起的形式
void QSort_Union(int a[], int low, int high){
	int l,h;
	l=low;h=high;
	if(l>=h) return;

	int pivotkey=a[l];//pivot为枢轴元素的关键字
	int pivot=a[l];//pivot为枢轴元素记录
	while(l<h){//当相等时终止,返回中间元素的下标
		while(l<h && a[h]>=pivotkey) h--;

		a[l]=a[h];

		while(l<h && a[l]<=pivotkey) l++;

		a[h]=a[l];
	}

	a[l]=pivot;

	QSort_Union(a, low, l-1);
	QSort_Union(a, l+1, high);
}


//快速排序的非递归写法(stack)
void NoRecursiveQSort_S(vector<int> &vec, int low, int high){
	stack<Pair> st;
	Pair pair;

	int pivot=Patition_Simply(vec, low, high);
	if(low<pivot-1){
		pair.begin=low; pair.end=pivot-1;
		st.push(pair);
	}
	if(high>pivot+1){
		pair.begin=pivot+1; pair.end=high;
		st.push(pair);
	}
	while(!st.empty()){
		Pair pair=st.top();
		st.pop();
		int pivot=Patition_Simply(vec, pair.begin, pair.end);

		if(pair.begin<pivot-1){
			pair.begin=low; pair.end=pivot-1;
			st.push(pair);
		}
		if(pair.end>pivot+1){
			pair.begin=pivot+1; pair.end=high;
			st.push(pair);
		}
	}
}

//快速排序的非递归写法(deque)
void NoRecursiveQSort_Q(vector<int> &vec, int low, int high){
	queue<Pair> que;
	Pair pair;

	int pivot=Patition_Simply(vec, low, high);
	if(low<pivot-1){
		pair.begin=low;
		pair.end=pivot-1;
		que.push(pair);
	}
	if(high>pivot+1){
		pair.begin=pivot+1;
		pair.end=high;
		que.push(pair);
	}
	while(!que.empty()){//用栈保存每一个待排序子串的首尾元素下标，下一次while循环时取出这个范围，对这段子序列进行partition操作
		Pair pair=que.front();
		que.pop();
		int pivot=Patition_Simply(vec, pair.begin, pair.end);

		if(pair.begin<pivot-1){
			pair.begin=low;
			pair.end=pivot-1;
			que.push(pair);
		}
		if(pair.end>pivot+1){
			pair.begin=pivot+1;
			pair.end=high;
			que.push(pair);
		}
	}
}




/*

//快速排序的非递归写法
void NoRecursiveQSort(vector<int> &vec, int low, int high){
	stack<int> st;
	if(low<high){
		int mid=Patition_Simply(vec,low,high);
		if(low<mid-1){
			st.push(low);
			st.push(mid-1);
		}
		if(mid+1<high){
			st.push(mid+1);
			st.push(high);
		}
		//其实就是用栈保存每一个待排序子串的首尾元素下标，下一次while循环时取出这个范围，对这段子序列进行partition操作
		while(!st.empty()){
			int q=st.top();
			st.pop();
			int p=st.top();
			st.pop();
			mid=Patition_Simply(vec,p,q);
			if(p<mid-1){
				st.push(p);
				st.push(mid-1);
			}
			if(mid+1<q){
				st.push(mid+1);
				st.push(q);
			}       
		}
	}
}*/

//////////////////////////////////////////////////////////////////////////
//选择排序
void SelectSort(vector<int> &vec){
	vector<int>::iterator it_out;

	for(it_out=vec.begin();it_out<vec.end()-1;it_out++){
		vector<int>::iterator it_in;
		vector<int>::iterator it_min;
		it_min=it_out;
		for(it_in=it_out+1;it_in<vec.end();it_in++){//it_out为每次比较的起始位置
			if(*it_min>*it_in) it_min=it_in;
		}
		if(it_min!=it_out){
			int tmp=*it_out;
			*it_out=*it_min;
			*it_min=tmp;
		}
	}
}

//一次调整过程,vec中的关键字vec[s...m],除去vec[s]外,其余均满足堆定义,调整vec[s...m]重新形成大顶堆
void HeapAdjust(vector<int> &vec, int s, int m){
	int tmp=vec.at(s);
	for(int i=2*s+1;i<=m;i=2*i+1){//指针(2*s~m)，步长为2倍

		if(i<m && vec.at(i)<vec.at(i+1)) i++;//右孩子关键字更大

		if(tmp>=vec.at(i)) break;//根节点已经是最大

		vec.at(s)=vec.at(i);//更新根节点
		s=i;//更新s
	}
	vec.at(s)=tmp;
}

//对顺序表进行堆排序
void HeapSort(vector<int> &vec){
	//建立大顶堆
	for(int i=vec.size()/2-1;i>=0;i--){//i的范围(vec.size()/2-1~0)(i为下标，按树的节点编号来算应相应加1)
		HeapAdjust(vec, i, vec.size()-1);//i~vec.size()
	}


	//将堆顶记录和当前未经排序的子序列中的最后一个记录交换，然后将交换后的的子序列重建为大顶堆
	for(int j=vec.size()-1;j>0;j--){//j指示未经排序的子序列中的最后一个记录的下标
		int tmp;
		tmp=vec.at(j);
		vec.at(j)=vec.at(0);
		vec.at(0)=tmp;

		HeapAdjust(vec, 0, j-1);
	}

}
//////////////////////////////////////////////////////////////////////////

//2-路归并操作,将有序的SR[a...b]和有序的SR[b+1...c]归并为有序的TR[a...c]
void Merge(const int* SR, int* TR, int a, int b, int c){
	int i,j,k;
	for(i=a,j=b+1,k=i;i<=b && j<=c;k++){//注意k=i
		if(SR[i]<=SR[j]) TR[k]=SR[i++];
		else TR[k]=SR[j++];
	}
	if(i<=b)
		for(;i<=b;) TR[k++]=SR[i++];
	else if(j<=c)
		for(;j<=c;) TR[k++]=SR[j++];
}


//将SR[s...t]归并为TR[s...t]
void MSort(const int* SR, int* TR, int s, int t){
	if(s==t)
		TR[s]=SR[s];
	else if(s<t){
		int* tmp=new int[t+1];
		int m=(s+t)/2;
		MSort(SR, tmp, s, m);
		MSort(SR, tmp, m+1, t);
		Merge(tmp, TR, s, m, t);
		int x=0;
	}
}

//////////////////////////////////////////////////////////////////////////
//一个参数的两路归并排序，归并算法SList(low~mid~high)
void Merge(int *SList,int low,int mid,int high)
{
	int *DList=new int[high-low+1];
	int i, j, k;
	//将有序的SList归并到DList
	for (i=low,j=mid+1,k=0;i<=mid&&j<=high;++k){
		if (SList[j]<SList[i]){//
			DList[k]=SList[j++];
		}
		else
			DList[k]=SList[i++];
	}

	if (j<=high){
		while(j<=high){
			DList[k++]=SList[j++];
		}
	}
	if (i<=mid){
		while(i<=mid){
			DList[k++]=SList[i++];
		}
	}

	std::cout<<"已排序  "<<std::endl;
	for ( k=low, i=0;k<=high;++k){//将归并排序好的序列复制回原序列
		SList[k]=DList[i++];
		std::cout<<SList[k]<<" ";
	}
	std::cout<<std::endl;

	delete []DList;//释放动态分配的内存，防止内存泄露
}

//一个参数的两路归并排序
void Sort(int* SList,int low,int high)
{
	if (low<high){
		int mid=(low+high)/2;
		Sort(SList,low,mid);
		Sort(SList,mid+1,high);
		Merge(SList,low,mid,high);
	}
}



void main(){
	/*
	while (1)
	{
	SqList sl;
	InitList_Sq(sl);
	cout<<"请输入有序顺序表的长度(n):"<<endl;
	int n;
	cin>>n;
	if (n>sl.listsize) exit(OVERFLOW);
	sl.length=n;
	cout<<"请输入有序表的元素(因为包含哨兵，其个数小于等于"<<n-1<<"):"<<endl;
	for (int i=1;i<sl.length;i++)
	{
	cin>>sl.elem[i];
	}

	for (int i=1;i<sl.length;i++)
	{
	cout<<sl.elem[i]<<" ";
	}
	cout<<endl;
	
		//Inser_Sort(sl);
		BInsertSort(sl);
	
		for (int i=1;i<sl.length;i++)
		{
			cout<<sl.elem[i]<<" ";
		}
		cout<<endl;
		system("pause");
	}
	*/

/*
	int R[]={49,38,65,97,76,13,27,52};
	SLinkListType sl;
	LInsertSort(sl, R, sizeof(R)/sizeof(R[0]));

	for(int i=0;i<=sizeof(R)/sizeof(R[0]);i++){
		cout<<sl.r[i].key<<" "<<sl.r[i].next<<endl;
	}
	cout<<endl;

	int j, i;
	for(i=sl.r[0].next;i!=0;i=sl.r[i].next){
		cout<<sl.r[i].key<<" "<<sl.r[i].next<<endl;
	}
	cout<<sl.r[i].key<<" "<<sl.r[i].next<<endl;


	cout<<endl;
	Arrange(sl);
	for(int i=0;i<=sizeof(R)/sizeof(R[0]);i++){
		cout<<sl.r[i].key<<" "<<sl.r[i].next<<endl;
	}
	cout<<endl;

	system("pause");*/

	//////////////////////////////////////////////////////////////////////////

/*
		while (1)
		{
			SqList sl;
			InitList_Sq(sl);
			cout<<"请输入有序顺序表的长度(n):"<<endl;
			int n;
			cin>>n;
			if (n>sl.listsize) exit(OVERFLOW);
			sl.length=n;
			cout<<"请输入有序表的元素(因为包含哨兵，其个数小于等于"<<n-1<<"):"<<endl;
			for (int i=1;i<sl.length;i++)
			{
				cin>>sl.elem[i];
			}
		
			for (int i=1;i<sl.length;i++)
			{
				cout<<sl.elem[i]<<" ";
			}
			cout<<endl;
		
			ShellSort(sl, Delta, sizeof(Delta)/sizeof(Delta[0]));
		
			for (int i=1;i<sl.length;i++)
			{
				cout<<sl.elem[i]<<" ";
			}
			cout<<endl;
		
			system("pause");
		}*/
	
	//////////////////////////////////////////////////////////////////////////

/*
	while (1)
	{
		int n;
		cout<<"元素个数:";
		cin>>n;
		int *a=new int[n];
		for (int i=0;i<n;i++){
			cin>>a[i];
		}
		BubbleSort(a, n);
		cout<<endl;
		for (int i=0;i<n;i++){
			cout<<a[i]<<" ";
		}
		cout<<endl;
		system("pause");
	}*/


/*
	while(1){
		int A[]={49,38,65,97,76,13,27,49};
		for(int i=0;i<sizeof(A)/sizeof(A[0]);i++){
			cout<<A[i]<<" ";
		}
		cout<<endl;
		//Patition(A, 0, sizeof(A)/sizeof(A[0])-1);

		QSort(A, 0, sizeof(A)/sizeof(A[0])-1);

		//QSort_Union(A, 0, sizeof(A)/sizeof(A[0])-1);

		for(int i=0;i<sizeof(A)/sizeof(A[0]);i++){
			cout<<A[i]<<" ";
		}
		cout<<endl;


		int len=20;
		vector<int> vec;
		vector<int>::iterator it;
		for(int i=0;i<len;i++)
			vec.push_back(rand());

		for(it=vec.begin();it<vec.end();it++){
			cout<<setw(8)<<*it;
		}
		cout<<endl;

		//NoRecursiveQSort_S(vec, 0, len-1);
		NoRecursiveQSort_Q(vec, 0, len-1);

		for(it=vec.begin();it<vec.end();it++){
				cout<<setw(8)<<*it;
		}

		system("pause");
	}*/

//////////////////////////////////////////////////////////////////////////
/*
	while(1){
		int len=20;
		vector<int> vec;
		vector<int>::iterator it;
		srand((int)time(0));
		for(int i=0;i<len;i++)
			vec.push_back(rand());

		for(it=vec.begin();it<vec.end();it++){
			cout<<setw(8)<<*it;
		}
		cout<<endl;

		SelectSort(vec);

		for(it=vec.begin();it<vec.end();it++){
			cout<<setw(8)<<*it;
		}
		system("pause");
	}*/

/*
	while(1){
		int len=5;
		vector<int> vec;
		vector<int>::iterator it;
		srand((int)time(0));//以时间为变量播撒种子
		for(int i=0;i<len;i++)
			vec.push_back(rand());

		for(it=vec.begin();it<vec.end();it++){
			cout<<setw(8)<<*it;
		}
		cout<<endl;

		//SelectSort(vec);
		HeapSort(vec);

		for(it=vec.begin();it<vec.end();it++){
			cout<<setw(8)<<*it;
		}
		system("pause");
	}*/


	
	while(1){
		int A[]={49,38,65,97,12,15,10,5,26,0};
		for(int i=0;i<sizeof(A)/sizeof(A[0]);i++){
			cout<<A[i]<<" ";
		}
		cout<<endl;

		//MSort(A, A, 0, sizeof(A)/sizeof(A[0])-1);

		Sort(A, 0, sizeof(A)/sizeof(A[0])-1);

		for(int i=0;i<sizeof(A)/sizeof(A[0]);i++){

			cout<<A[i]<<" ";
		}
		cout<<endl;


/*
		FILE* fp;
		int* p=A;
		if((fp=fopen("D:\\a","a+"))!=NULL){
			for(int i=0;i<sizeof(A)/sizeof(A[0]);i++){
				putw(A[i],fp);
			}
			fclose(fp);
		}*/

		
		system("pause");
	}

};