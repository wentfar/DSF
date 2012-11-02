#include <iostream>
#include <vector>
#include <ctime>
#include <stack>

using namespace std;

//插入排序
template <class T>
void Inser_Sort(vector<T> &v){
	for(int i=1;i<v.size();i++){
		T tmp = v[i];
		int j;
		for(j=i-1;j>=0 && v[j]>tmp;j--){//注意j>=0&&v[j]>tmp的顺序
			v[j+1]=v[j];
		}
		v[j+1]=tmp;//注意是(j+1)
	}
}

//有哨兵的插入排序
template <class T>
void Inser_Sort_Guard(vector<T> &v){
	for(int i=2;i<v.size();i++){
		v[0]=v[i];//v[0]是哨兵
		int j;
		for(j=i-1;v[j]>v[0];j--){
			v[j+1]=v[j]; 
		}
		v[j+1]=v[0];//注意是(j+1)
	}
}

int Delta[]={5,3,2,1};

//一趟希尔排序
template <class T>
void ShellInsert(vector<T> &v, int dk){
	for(int i=dk+1;i<v.size();i++){
		T tmp=v[i];
		int j;
		for(j=i-dk;j>=0 && v[j]>tmp;j-=dk){
			v[j+dk]=v[j];
		}
		v[j+dk]=tmp;
	}
}

//希尔排序,增量序列(delta[0,...,n-1])
template <class T>
void ShellSort(vector<T> &v, int delta[], int n){
	for(int k=0;k<n;k++){ShellInsert(v, delta[k]);}
}

//冒泡排序
template <class T>
void BubbleSort(vector<T> &v){
	bool change;
	for(int i=v.size()-1,change=true;i>=1 && change==true;i--){//i为每一趟比较的次数
		for(int j=0;j<i;j++){
			change=false;
			if(v[j]>v[j+1]){
				int tmp=v[j];
				v[j]=v[j+1];
				v[j+1]=tmp;
				change=true;
			}
		}
	}
}

template <class T>
void exchange(T &a,T &b)
{
	int temp;
	temp=a;
	a=b;
	b=temp;
}

//快排的partition函数(算法导论)
template <class T>
int Partition1(vector<T> &v, int low, int high)
{
	int i=low-1;//i是比MidVal小的值集合的边界角标
	T MidVal=v[high];

	for(int j=low;j<high;j++)
	{
		if(v[j]<=MidVal)//把比MidVal小的数往前放     
		{
			i++;
			exchange(v[j],v[i]);   
		}        
	}
	exchange(v[high],v[i+1]);
	return i+1;
}

//快速排序一次划分(严蔚敏)
template <class T>
int Partition2(vector<T> &v, int low, int high){
	T pivot=v[low];//pivot为枢轴元素记录

	while(low<high){//当相等时终止,返回中间元素的下标
		while(low<high && v[high]>=pivot) high--;
		v[low]=v[high];
		while(low<high && v[low]<=pivot) low++;
		v[high]=v[low];
	}

	v[low]=pivot;
	return low;
}


//递归形式的快速排序
template <class T>
void QSort(vector<T> &v, int low, int high){
	if (low < high)
	{
		int pivotloc=Partition1(v, low, high);
		QSort(v, low, pivotloc-1);
		QSort(v, pivotloc+1, high);
	}
}


struct Boundarys{
	int begin;
	int end;
};

//快速排序的非递归写法(stack)
template <class T>
void QSort_NoRecursive_S(vector<T> &v, int low, int high){
	stack<Boundarys> st;
	int pivot_0=Partition2(v, low, high);

	Boundarys bound_L, bound_R;
	if(low<pivot_0-1){
		bound_L.begin=low; bound_L.end=pivot_0-1; st.push(bound_L);
	}
	if(high>pivot_0+1){
		bound_R.begin=pivot_0+1; bound_R.end=high; st.push(bound_R);
	}

	while(!st.empty()){
		Boundarys bound=st.top();
		st.pop();

		int pivot=Partition2(v, bound.begin, bound.end);
		Boundarys bound_L, bound_R;
		if(bound.begin<pivot-1){
			bound_L.begin=low; bound_L.end=pivot-1; st.push(bound_L);
		}
		if(bound.end>pivot+1){
			bound_R.begin=pivot+1; bound_R.end=high; st.push(bound_R);
		}
	}
}

//选择排序
template <class T>
void SelectSort(vector<T> &v){
	vector<T>::iterator it_out;

	for(it_out=v.begin();it_out<v.end()-1;it_out++){
		vector<T>::iterator it_in;
		vector<T>::iterator it_min=it_out;
		for(it_in=it_out+1;it_in<v.end();it_in++){//it_out为每次比较的起始位置
			if(*it_min>*it_in) it_min=it_in;
		}
		if(it_min!=it_out){
			T tmp=*it_out;
			*it_out=*it_min;
			*it_min=tmp;
		}
	}
}

//一次调整过程,v中的关键字v[s...m],除去v[s]外,其余均满足堆定义,调整v[s...m]重新形成大顶堆
template <class T>
void HeapAdjust(vector<T> &v, int s, int m){
	T tmp=v.at(s);
	for(int i=2*s+1;i<=m;i=2*i+1){//i=2*s+1为第一个孩子结点
		if(i<m && v.at(i)<v.at(i+1)) i++;//右孩子关键字更大
		
		if(tmp>=v.at(i)) break;//根节点已经是最大

		v.at(s)=v.at(i);//更新根节点
		s=i;//更新s
	}
	v.at(s)=tmp;
}

//对顺序表进行堆排序
template <class T>
void HeapSort(vector<T> &v){
	//建立大顶堆
	for(int i=v.size()/2-1;i>=0;i--){//i的范围(vec.size()/2-1~0)(i为下标，按树的节点编号来算应相应加1)
		HeapAdjust(v, i, v.size()-1);//i~vec.size()
	}

	//将堆顶记录和当前未经排序的子序列中的最后一个记录交换，然后将交换后的的子序列重建为大顶堆
	for(int j=v.size()-1;j>0;j--){//j指示未经排序的子序列中的最后一个记录的下标
		T tmp;
		tmp=v.at(j);
		v.at(j)=v.at(0);
		v.at(0)=tmp;

		HeapAdjust(v, 0, j-1);
	}

}

//两路归并排序，归并算法
template <class T>
void Merge(vector<T> &v, int low, int mid, int high){
	vector<T> tmp(high-low+1);
	int i, j, k;
	for (i=low,j=mid+1,k=0;i<=mid&&j<=high;++k){//将有序的v归并到tmp
		if (v[j]<v[i])
			tmp[k]=v[j++];
		else
			tmp[k]=v[i++];
	}

	if (i<=mid)
		while(i<=mid)
			tmp[k++]=v[i++];

	if (j<=high)
		while(j<=high)
			tmp[k++]=v[j++];

	for ( k=low, i=0;k<=high;++k){//将归并排序好序列tmp复制回原序列v
		v[k]=tmp[i++];
	}
}

//两路归并排序
template <class T>
void MSort(vector<T> &v,int low,int high){
	if (low<high){
		int mid=(low+high)/2;
		MSort(v,low,mid);
		MSort(v,mid+1,high);
		Merge(v,low,mid,high);
	}
}


void main()
{
	while (1)
	{
		vector<int> _v;
		int n;
		cout<<"请输入有序顺序表的元素个数n:"<<endl;
		cin>>n;
		srand((unsigned)time(0));
		for (int i=0;i<n;i++)
		{
			_v.push_back(rand()%100);
		}

		for (int i=0;i<_v.size();i++)
		{
			cout<<_v[i]<<" ";
		}
		cout<<endl;

		//Inser_Sort(_v);
		//Inser_Sort_Guard(_v);
		//ShellSort(_v, Delta, 4);
		//BubbleSort(_v);
		//QSort(_v, 0, _v.size() - 1);
		//QSort_NoRecursive_S(_v, 0, _v.size() - 1);
		//SelectSort(_v);
		//HeapSort(_v);
		MSort(_v, 0, _v.size() - 1);

		for (int i=0;i<_v.size();i++)
		{
			cout<<_v[i]<<" ";
		}
		cout<<endl;
		system("pause");
	}
}