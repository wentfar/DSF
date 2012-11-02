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

typedef struct{
	int begin;
	int end;
}Pair;

//////////////////////////////////////////////////////////////////////////

//���ڱ��Ĳ�������
void Inser_Sort(SqList &sl){
	for(int i=2;i<sl.length;i++){
		sl.elem[0]=sl.elem[i];
		int j;
		for(j=i-1;sl.elem[j]>sl.elem[0];j--){
			sl.elem[j+1]=sl.elem[j]; 
		}
		sl.elem[j+1]=sl.elem[0];//ע����(j+1)
	}
}

//���ڱ����۰��������
void BInsertSort(SqList &sl){
	for(int i=2;i<sl.length;i++){
		sl.elem[0]=sl.elem[i];
		int low=1;
		int high=i-1;
		int j;
		while(low<=high){
			int mid=(low+high)/2;
			if(sl.elem[0]<sl.elem[mid]){ high=mid-1; }//�±�Ϊmid=high+1��Ԫ��Ϊ���һ�������������Ԫ��
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
	SLNode r[SIZE];//0�ŵ�ԪΪͷ���
	int length;
}SLinkListType;

//�����������
void LInsertSort(SLinkListType &sl, /*ElemType*/int R[], int n){
	sl.length=n;
	sl.r[0].key=MAX;
	sl.r[0].next=1;
	sl.r[1].key=R[0];//
	sl.r[1].next=0;//ѭ������

	for(int i=2;i<=n;i++){//��r[2]��ʼ
		int j, k;
		for(j=0,k=sl.r[0].next;sl.r[k].key<=R[i-1]/*��R[1]��ʼ*/;j=k,k=sl.r[k].next);//���ڵ�i���뵽�ڵ�j��k;
		sl.r[j].next=i;sl.r[i].next=k;sl.r[i].key=R[i-1];
	}
}

//���ݾ�̬�����еĸ��ڵ�ָ�������¼��λ�ã�ʹ��SL�еļ�¼���ؼ��ַǵݼ���������
void Arrange(SLinkListType &sl){
	int p=sl.r[0].next;
	for(int i=1;i<sl.length;++i){

		while(p<i){p=sl.r[p].next;}//�ҵ�δ����ĵ�i����¼

		int q=sl.r[p].next;
		if(p!=i){
			SLNode tmp;
			tmp=sl.r[p];
			sl.r[p]=sl.r[i];
			sl.r[i]=tmp;

			sl.r[i].next=p;//ָ�����ߵļ�¼
		}
		p=q;
	}
}
//////////////////////////////////////////////////////////////////////////

int Delta[]={5,3,2,1};
//һ��ϣ������
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

//ϣ������,��������(delta[0,...,t-1])
void ShellSort(SqList &sl, int delta[], int t){
	for(int k=0;k<t;k++){ShellInsert(sl, delta[k]);}
}

//////////////////////////////////////////////////////////////////////////

void BubbleSort(int a[], int n){
	bool change;
	for(int i=n-1,change=true;i>=1 && change==true;i--){//iΪÿһ�˱ȽϵĴ���
		for(int j=0;j<i;j++){//iΪÿһ�˱ȽϵĴ���
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
int Patition_Simply(int a[], int low, int high){//һ�λ��֣���˳���ֳɷ���,low,high�ֱ�Ϊ�ߵ�����ָ��

	int pivotkey=a[low];//pivotΪ����Ԫ�صĹؼ���
	int pivot=a[low];//pivotΪ����Ԫ�ؼ�¼

	while(low<high){//�����ʱ��ֹ,�����м�Ԫ�ص��±�
		while(low<high && a[high]>=pivotkey) high--;

		a[low]=a[high];

		while(low<high && a[low]<=pivotkey) low++;

		a[high]=a[low];
	}

	a[low]=pivot;
	return low;
}

//�ݹ���ʽ�Ŀ�������
void QSort(int a[], int low, int high){
	if (low < high)
	{
		int pivotloc=Patition_Simply(a, low, high);
		QSort(a, low, pivotloc-1);
		QSort(a, pivotloc+1, high);
	}
}

//Patition_Simply��QSortд��һ�����ʽ
void QSort_Union(int a[], int low, int high){
	int l,h;
	l=low;h=high;
	if(l>=h) return;

	int pivotkey=a[l];//pivotΪ����Ԫ�صĹؼ���
	int pivot=a[l];//pivotΪ����Ԫ�ؼ�¼
	while(l<h){//�����ʱ��ֹ,�����м�Ԫ�ص��±�
		while(l<h && a[h]>=pivotkey) h--;

		a[l]=a[h];

		while(l<h && a[l]<=pivotkey) l++;

		a[h]=a[l];
	}

	a[l]=pivot;

	QSort_Union(a, low, l-1);
	QSort_Union(a, l+1, high);
}


//��������ķǵݹ�д��(stack)
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
		Pair pair1;
		if(pair.end>pivot+1){
			pair1.begin=pivot+1; pair1.end=high;
			st.push(pair1);
		}
	}
}

//��������ķǵݹ�д��(deque)
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
	while(!que.empty()){//��ջ����ÿһ���������Ӵ�����βԪ���±꣬��һ��whileѭ��ʱȡ�������Χ������������н���partition����
		Pair pair=que.front();
		que.pop();
		int pivot=Patition_Simply(vec, pair.begin, pair.end);

		if(pair.begin<pivot-1){
			pair.begin=low;
			pair.end=pivot-1;
			que.push(pair);
		}
		if(pair.end>pivot+1){
			Pair pair1;
			pair1.begin=pivot+1;
			pair1.end=high;
			que.push(pair1);
		}
	}
}




/*

//��������ķǵݹ�д��
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
		//��ʵ������ջ����ÿһ���������Ӵ�����βԪ���±꣬��һ��whileѭ��ʱȡ�������Χ������������н���partition����
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
//ѡ������
void SelectSort(vector<int> &vec){
	vector<int>::iterator it_out;

	for(it_out=vec.begin();it_out<vec.end()-1;it_out++){
		vector<int>::iterator it_in;
		vector<int>::iterator it_min;
		it_min=it_out;
		for(it_in=it_out+1;it_in<vec.end();it_in++){//it_outΪÿ�αȽϵ���ʼλ��
			if(*it_min>*it_in) it_min=it_in;
		}
		if(it_min!=it_out){
			int tmp=*it_out;
			*it_out=*it_min;
			*it_min=tmp;
		}
	}
}

//һ�ε�������,vec�еĹؼ���vec[s...m],��ȥvec[s]��,���������Ѷ���,����vec[s...m]�����γɴ󶥶�
void HeapAdjust(vector<int> &vec, int s, int m){
	int tmp=vec.at(s);
	for(int i=2*s+1;i<=m;i=2*i+1){//ָ��(2*s~m)������Ϊ2��

		if(i<m && vec.at(i)<vec.at(i+1)) i++;//�Һ��ӹؼ��ָ���

		if(tmp>=vec.at(i)) break;//���ڵ��Ѿ������

		vec.at(s)=vec.at(i);//���¸��ڵ�
		s=i;//����s
	}
	vec.at(s)=tmp;
}

//��˳�����ж�����
void HeapSort(vector<int> &vec){
	//�����󶥶�
	for(int i=vec.size()/2-1;i>=0;i--){//i�ķ�Χ(vec.size()/2-1~0)(iΪ�±꣬�����Ľڵ�������Ӧ��Ӧ��1)
		HeapAdjust(vec, i, vec.size()-1);//i~vec.size()
	}


	//���Ѷ���¼�͵�ǰδ��������������е����һ����¼������Ȼ�󽫽�����ĵ��������ؽ�Ϊ�󶥶�
	for(int j=vec.size()-1;j>0;j--){//jָʾδ��������������е����һ����¼���±�
		int tmp;
		tmp=vec.at(j);
		vec.at(j)=vec.at(0);
		vec.at(0)=tmp;

		HeapAdjust(vec, 0, j-1);
	}

}
//////////////////////////////////////////////////////////////////////////

//2-·�鲢����,�������SR[a...b]�������SR[b+1...c]�鲢Ϊ�����TR[a...c]
void Merge(const int* SR, int* TR, int a, int b, int c){
	int i,j,k;
	for(i=a,j=b+1,k=i;i<=b && j<=c;k++){//ע��k=i
		if(SR[i]<=SR[j]) TR[k]=SR[i++];
		else TR[k]=SR[j++];
	}
	if(i<=b)
		for(;i<=b;) TR[k++]=SR[i++];
	else if(j<=c)
		for(;j<=c;) TR[k++]=SR[j++];
}


//��SR[s...t]�鲢ΪTR[s...t]
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
//һ����������·�鲢���򣬹鲢�㷨SList(low~mid~high)
void Merge(int *SList,int low,int mid,int high)
{
	int *DList=new int[high-low+1];
	int i, j, k;
	//�������SList�鲢��DList
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

	std::cout<<"������  "<<std::endl;
	for ( k=low, i=0;k<=high;++k){//���鲢����õ����и��ƻ�ԭ����
		SList[k]=DList[i++];
		std::cout<<SList[k]<<" ";
	}
	std::cout<<std::endl;

	delete []DList;//�ͷŶ�̬������ڴ棬��ֹ�ڴ�й¶
}

//һ����������·�鲢����
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
	cout<<"����������˳���ĳ���(n):"<<endl;
	int n;
	cin>>n;
	if (n>sl.listsize) exit(OVERFLOW);
	sl.length=n;
	cout<<"������������Ԫ��(��Ϊ�����ڱ��������С�ڵ���"<<n-1<<"):"<<endl;
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
			cout<<"����������˳���ĳ���(n):"<<endl;
			int n;
			cin>>n;
			if (n>sl.listsize) exit(OVERFLOW);
			sl.length=n;
			cout<<"������������Ԫ��(��Ϊ�����ڱ��������С�ڵ���"<<n-1<<"):"<<endl;
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
		cout<<"Ԫ�ظ���:";
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

		NoRecursiveQSort_S(vec, 0, len-1);
		//NoRecursiveQSort_Q(vec, 0, len-1);

		for(it=vec.begin();it<vec.end();it++){
				cout<<setw(8)<<*it;
		}

		system("pause");
	}

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
		srand((int)time(0));//��ʱ��Ϊ������������
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


	
	while(0){
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