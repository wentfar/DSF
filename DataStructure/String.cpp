// Interview.cpp : 定义控制台应用程序的入口点。
#include "string.h"
#include <iostream>

using namespace std;

//************************************
// Method:    ItoA
// Description:  Transfer an int to a string
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int n
// Parameter: char * str
//************************************
void ItoA(int n, char *str)
{
	char num[256];
	int k = n, i;
	if (n<0) k = -n;
		
	for(i=0; k>0; i++)
	{
		num[i] = k%10 + '0';
		k /= 10;
	}


	if(n<0) num[i] = '-';
	else --i;

	int j;
	for(j=0;i>=0;j++,i--)
	{
		str[j] = num[i];
	}
	str[j] ='\0';
}

//************************************
// Method:    AtoI
// Description:  Transfer a string to a long integer
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: long * n
// Parameter: char * str
//************************************
void AtoI(long *n, char* str)
{
	if(str == NULL) throw "error";

	bool sign = false;
	if(*str == '-')
	{
		str++;
		sign = true;
	}
	else if (*str == '+')
	{
		str++;
	}

	*n = 0;
	while(*str)
	{
		if(*str >= '0' && *str <='9')
		{
			*n =(*n)*10 + ((*str) - '0') ;
			str++;
		}
		else
		{
			throw "error";
		}
	}
	if(sign == true){(*n) = -(*n);}
}

//************************************
// Method:    LoopMove
// Description:  Move the chars from the string recurrently
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: char * pStr
// Parameter: int steps: The steps to be moved
//************************************
void LoopMove(char* pStr, int steps)
{
	if (pStr == NULL)
	{
		throw "error";
	}

	int len = strlen(pStr);

	if (steps%len != 0)
	{
		char* snippet = new char[len];
		strcpy(snippet, pStr + len - steps%len);
		*(pStr + len - steps%len) = '\0';
		strcpy(snippet + steps%len, pStr);
		strcpy(pStr, snippet);
	}
}


//************************************
// Method:    strCpy
// Description:  Copy string from source to destination
// Access:    public 
// Returns:   char*: Start address of the destination string
// Qualifier:
// Parameter: const char * Src: Source string
// Parameter: char * Dst: Destination string
//************************************
char* strCpy(const char* Src, char* Dst)
{
	if(Src == NULL || Dst == NULL) throw "error";
	char* DstCpy = Dst;
	while((*Dst++ = *Src++) != '\0');
	return DstCpy;
}

//************************************
// Method:    FindSubStr
// FullName:  Locate substring. Returns a pointer to the first occurrence of str2 in str1, or a null pointer if str2 is not part of str1. The matching process does not include the terminating null-characters.
// Access:    public 
// Returns:   const char*: A pointer to the first occurrence in str1 of any of the entire sequence of characters specified in str2, or a null pointer if the sequence is not present in str1.
// Qualifier:
// Parameter: const char * str1: C string to be scanned.
// Parameter: const char * str2: C string containing the sequence of characters to match.
//************************************
const char* FindSubStr(const char* str1, const char*str2)
{
	if (str1 == NULL || str2 == NULL)
	{
		throw "error";
	}
	int len1 = 0;
	int len2 = 0;
	const char*p = str1;
	while(*p++) len1++;
	p = str2;
	while(*p++) len2++;
	if (len1 < len2)
	{
		return NULL;
	}

	int i = 0;
	for (;i <= len1 - len2;i++)
	{
		int j = 0;
		while(*(str2 + j))
		{
			if(*(str1 + i + j) == *(str2 + j))
			{
				j++;
			}
			else
			{
				break;
			}
		}
		if (j == len2)
		{
			return (str1 + i);
		}
	}
	return NULL;
}


//************************************
// Method:    InverseSentence
// FullName:  Inverse a Sentence which is ended with a '.', while keep the order of each word
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: char * str
// Parameter: char * res
//************************************
void InverseSentence(char* str, char* res)
{
	int	len = strlen(str);
	int i = len - 1;

	int cnt = 0;//number of letter which is not space
	int cnt_s = 0;//number of letter which is space
	for (;i >= 0;i--)
	{

		if (*(str + i) != ' ' && *(str + i) != '.')
		{
			cnt++;
			if (i == 0 || *(str + i - 1) == ' ' || *(str + i - 1) == '.')
			{
				memcpy(res + len - i - cnt, str + i, cnt);		
				cnt = 0;
			}
		}
		else
		{
			cnt_s++;
			if (*(str + i - 1) != ' ' && *(str + i - 1) != '.')
			{
				memcpy(res + len - i - cnt_s, str + i, cnt_s);		
				cnt_s = 0;
			}
		}
	}
	*(res + len) = '\0';

	//move the dot to the end
	memcpy(res, res + 1, len - 1);
	*(res + len - 1) = '.';
	*(res + len) = '\0';

}


int main(int argc, char* argv[])
{	
/************************************************************************/
/* Tests for StringOperation.cpp                                         */
/************************************************************************/
	char a[256];
	char b[256];
	cin.getline(a, 256, '\n');
	InverseSentence(a, b);
	cout<<b;
	system("pause");

/*
	char a[256];
	char b[256];
	cin>>a;
	cin>>b;
	const char*p = NULL;
	if ((p = FindSubStr(a, b)) != NULL)
	{
		cout<<p;
	}

	system("pause");*/


/*
	char p[3] = {'a','b','c'};
	char q[] = "Hello!";
	char a[256];
	cin>>a;
	long n = 0;
	AtoI(&n, a);
	cout<<n;
	system("pause");*/

/*
	char a[100] = "Hello";			 
	int steps;
	cout<<"Input the steps:";
	std::cin>>steps;
	LoopMove(a, steps);
	printf(a);
	system("pause");*/


/*
	char a[100] = "Hello, World!";
	char* b = new char[100];
	b = strCpy(a, b);
	printf(b);
	system("pause");*/

/*
	while (1)
	{
		int num;
		char *str = new char[256];
		cin>>num;
		ItoA(num, str);
		cout<<str<<endl;
	
		char *p = str;
		while(*p){
			cout<<*p++;
		}
		cout<<endl;
	
		delete[] str;
		system("pause");
	}*/




/*
	base* cp=new derived;
	cout<<typeid(cp).name()<<endl;
	cout<<typeid(*cp).name()<<endl;
	funcD(cp);
	funcC(cp);
	base *dp=new base;
	funcC(dp);
	funcD(dp);
	system("pause");*/




/*
	int a = printf("%d\n", 5);
	int b = printf("%f\n", 6);
	int c = printf("%d\n", 5.001);
	int d = printf("%f\n", 5.01);


	struct bs
	{
		unsigned a:1;
		unsigned b:3;
		unsigned c:4;
	} bit,*PBit;
	bit.a=1;
	bit.b=7;
	bit.c=15;
	printf("%d,%d,%d\n",bit.a,bit.b,bit.c);
	PBit=&bit;
	PBit->a=0;
	PBit->b&=3;
	PBit->c|=1;
	printf("%d,%d,%d\n",PBit->a,PBit->b,PBit->c);

	system("pause");
	return 0;*/

}