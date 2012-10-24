#include <iostream>

/**
 *求一个数组中的第k大数
 *基本思想：
 *以最后一个元素x为轴，把数组分为两部分Sa和Sb。Sa中的元素大于等于X，Sb中元素小于X。这时有两种情况：
 *1.Sa中元素的个数小于k，则Sb中的第k-|Sa|个元素即为第k大数；
 *2.Sa中元素的个数大于等于k，则返回Sa中的第k大数。
 *时间复杂度近似为O(n) 
 */
using namespace std;
void exchange(int &a,int &b)
{
    int temp;
    temp=a;
    a=b;
    b=temp;
}

//快排的partition函数 
int partition(int *a,int l,int r)
{
	int i=l-1;//i是比MidVal大的值集合的边界角标
	int MidVal=a[r];
   
    for(int j=l;j<r;j++)
    {
        if(a[j]>=MidVal)//把比MidVal大的数往前放     
        {
			i++;
            exchange(a[j],a[i]);   
        }        
    }
    exchange(a[r],a[i+1]);
    return i+1;
}

int k_element(int *a, int l, int r, int k)
{
    if(l>=r)
        return a[l];

    int q=partition(a,l,r);
    if(q==k-1)
        return a[q];   
    else if(q>k-1)
        return k_element(a,l,q-1,k); //Sa中元素个数大于等于k   
    else
        return k_element(a,q+1,r,k-(q+1)); //Sa中元素个数小于k    
}

int main(int argc, char *argv[])
{
    int a[100];
    int length,k; 
	cout<<"数组元素个数（100以内）：";
    cin>>length; 
	cout<<endl<<"依次输入元素：\n";
    for(int i=0;i<length;i++)
        cin>>a[i];

	while (1)
	{
		cout<<"要寻找第K大的数：k=";
		cin>>k;
	    cout<<k_element(a,0,length-1,k)<<endl;
	}

    
    system("PAUSE");
    return 1;
}