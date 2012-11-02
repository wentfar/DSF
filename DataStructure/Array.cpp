#include <iostream>

/**
 *��һ�������еĵ�k����
 *����˼�룺
 *�����һ��Ԫ��xΪ�ᣬ�������Ϊ������Sa��Sb��Sa�е�Ԫ�ش��ڵ���X��Sb��Ԫ��С��X����ʱ�����������
 *1.Sa��Ԫ�صĸ���С��k����Sb�еĵ�k-|Sa|��Ԫ�ؼ�Ϊ��k������
 *2.Sa��Ԫ�صĸ������ڵ���k���򷵻�Sa�еĵ�k������
 *ʱ�临�ӶȽ���ΪO(n) 
 */
using namespace std;
void exchange(int &a,int &b)
{
    int temp;
    temp=a;
    a=b;
    b=temp;
}

//���ŵ�partition���� 
int partition(int *a,int l,int r)
{
	int i=l-1;//i�Ǳ�MidVal���ֵ���ϵı߽�Ǳ�
	int MidVal=a[r];
   
    for(int j=l;j<r;j++)
    {
        if(a[j]>=MidVal)//�ѱ�MidVal�������ǰ��     
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
        return k_element(a,l,q-1,k); //Sa��Ԫ�ظ������ڵ���k   
    else
        return k_element(a,q+1,r,k-(q+1)); //Sa��Ԫ�ظ���С��k    
}

int main(int argc, char *argv[])
{
    int a[100];
    int length,k; 
	cout<<"����Ԫ�ظ�����100���ڣ���";
    cin>>length; 
	cout<<endl<<"��������Ԫ�أ�\n";
    for(int i=0;i<length;i++)
        cin>>a[i];

	while (1)
	{
		cout<<"ҪѰ�ҵ�K�������k=";
		cin>>k;
	    cout<<k_element(a,0,length-1,k)<<endl;
	}

    
    system("PAUSE");
    return 1;
}