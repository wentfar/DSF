#include <iostream>
using namespace std;


//�Ȳ��ƽ�λ��ӣ�Ȼ�������λ��ӣ����ŵݹ飬��λ���Ϊ0���ݹ������
int Add(int a, int b)
{
	if(b == 0) return a;
	return Add(a^b, (a&b)<<1);
}


int MyDiv(int x,int y)    
{    
	int ans=0;    
	for(int i=31;i>=0;i--)  
	{    
		//�Ƚ�x�Ƿ����y��(1<<i)�η������⽫x��(y<<i)�Ƚϣ���Ϊ��ȷ��y��(1<<i)�η��Ƿ����  
		if((x>>i)>=y)           
		{       
			ans+=(1<<i);      
			x-=(y<<i);        
		}       
	}    
	return ans;    
} 

class A{
public:
	virtual void Func(A a){cout<<"a";}
};

class B:public A{
private:
	virtual void Func(A a){cout<<"b";}
};

void main()
{
	//int a = 100;
	//int b = 9;
	//cout<<Add(a, b)<<endl;

	//cout<<MyDiv(a, b);

	//B b;
	//A* p = &b;
	//p->Func(b);

	int i = 10;
	//printf("%d\n", i++);
	//printf("%d\n", ++i);
	//printf("%d\n", i++);
	i = i + i++;
	//i += i++;
	cout<<i<<endl;
	while(i++){
		cout<<i<<endl;
	}
	system("pause");
}