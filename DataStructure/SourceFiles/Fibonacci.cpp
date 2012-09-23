/*1.17 试编写求k阶斐波那契序列的第m项值的函数算法，k和m均以值调用的形式在函数参数表中出现。*/

#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

//斐波那契数列第n项---递归
long Fibonacci(int n)
{
	if (n==0)
		return 0;
	else if(n==1)
		return 1;
	else if(n>1)
		return Fibonacci(n-1)+Fibonacci(n-2);
}

//输出斐波那契数列前n项---迭代法
void Fibonacci_iter(int n)
{
	int f_cur=0; 
	int f0=0; 
	int f1=1;
	cout<<setw(15)<<f1<<" ";
	for (int j=2;j<=n;j++)
	{
		f_cur=f0+f1;
		cout<<setw(15)<<f_cur<<" ";
		f0=f1;
		f1=f_cur;
		if (j%5==0)
		{
			cout<<endl;
		}
	}
}

void main()
{
	int n;
	cout<<"请输入需要计算的项数：";
	cin>>n;
	time_t start,middle,end;
	start=clock();
	for (int i=1;i<=n;i++)
	{
		cout<<setw(15)<<Fibonacci(i)<<" ";
		if (i%5==0)
		{
			cout<<endl;
		}
	}

	middle=clock();
	Fibonacci_iter(n);
	end=clock();
	cout<<middle-start<<" "<<end-middle;
}

/*
请输入需要计算的项数：30
	1               1               2               3               5

	8              13              21              34              55

	89             144             233             377             610

	987            1597            2584            4181            6765

	10946           17711           28657           46368           75025

	121393          196418          317811          514229          832040

	1               1               2               3               5

	8              13              21              34              55

	89             144             233             377             610

	987            1597            2584            4181            6765

	10946           17711           28657           46368           75025

	121393          196418          317811          514229          832040

	227 18请按任意键继续. . .*/
