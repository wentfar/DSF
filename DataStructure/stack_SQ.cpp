#include "stack_SQ.h"
#include <iostream>

using namespace std;

template <class DataType>
sq_stack<DataType>::sq_stack()
{
	base = new DataType[STACK_INIT_SIZE];
	if(!base) exit(1);
	top=base;
	stacksize=STACK_INIT_SIZE;
}

template <class DataType>
void sq_stack<DataType>::Push(DataType e)
{
	if(top-base>=stacksize-1){
		base=(DataType*)realloc(base,(stacksize+STACKINCREMENT)*sizeof(DataType));
		if(!base) exit(1);
		top=base+stacksize-1;
		stacksize+=STACKINCREMENT;
	}
	*top++=e;
}

template <class DataType>
void sq_stack<DataType>::Pop()
{
	if(top==base) exit(1);
	top--;
}


template <class DataType>
DataType sq_stack<DataType>::Top()
{
	if(top==base) return NULL;
	return *(top-1);
}


template <class DataType>
bool sq_stack<DataType>::Empty()
{
	return top==base? 1:0;
}

template <class DataType>
sq_stack<DataType>::~sq_stack()
{
	if(base) free(base);
	top = base = NULL;
	stacksize = 0;
}

int main()
{
	sq_stack<int> st;
	for(int i=1;i<=20;i++)
		st.Push(i);
	for(int i=1;i<=20;i++)
	{
		cout<<st.Top()<<" ";
		st.Pop();
		if (i%5 == 0){cout<<endl;}
	}
	system("pause");
	return 0;
}