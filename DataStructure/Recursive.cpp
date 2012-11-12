#include <iostream>
using namespace std;


//先不计进位相加，然后再与进位相加，随着递归，进位会变为0，递归结束。
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
		//比较x是否大于y的(1<<i)次方，避免将x与(y<<i)比较，因为不确定y的(1<<i)次方是否溢出  
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