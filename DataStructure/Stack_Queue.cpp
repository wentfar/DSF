#include <iostream>
#include "Definition.h"
#include <ctype.h>

using namespace std;

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10//站满时增量
#define N 20
#define MAXQSIZE 100

typedef char QElemType;
typedef char SElemType;

typedef struct{
	SElemType * base;//定义栈底指针，指向分配空间首地址
	SElemType * top;
	int stacksize;
}SqStack;

typedef struct{
	float * base;//定义栈底指针，指向分配空间首地址
	float * top;
	int stacksize;
}SqStack_float;


//初始化一个空栈（char）
Status InitStack(SqStack &s){
	s.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!s.base) exit(OVERFLOW);
	s.top=s.base;
	s.stacksize=STACK_INIT_SIZE;
	return OK;
}
//初始化一个空栈（float）
Status InitStack(SqStack_float &s){
	s.base=(float *)malloc(STACK_INIT_SIZE*sizeof(float));
	if(!s.base) exit(OVERFLOW);
	s.top=s.base;
	s.stacksize=STACK_INIT_SIZE;
	return OK;
}


Status Push(SqStack &s, SElemType e){
	if(s.top-s.base>=s.stacksize){
		s.base=(SElemType*)realloc(s.base, (s.stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!s.base) exit(OVERFLOW);
		s.top=s.base+s.stacksize;
		s.stacksize+=STACKINCREMENT;
	}
	*s.top++=e;//优先级'.'>'*','*'='++'
	return OK;
}
Status Push(SqStack_float &s, float e){
	if(s.top-s.base>=s.stacksize){
		s.base=(float*)realloc(s.base, (s.stacksize+STACKINCREMENT)*sizeof(float));
		if(!s.base) exit(OVERFLOW);
		s.top=s.base+s.stacksize;
		s.stacksize+=STACKINCREMENT;
	}
	*s.top++=e;//优先级'.'>'*','*'='++'
	return OK;
}

Status Pop(SqStack &s, SElemType &e){
	if(s.top==s.base) return ERROR;
	e=*--s.top;
	return OK;
}
Status Pop(SqStack_float &s, float &e){
	if(s.top==s.base) return ERROR;
	e=*--s.top;
	return OK;
}

Status Pop(SqStack &s){
	if(s.top==s.base) return ERROR;
	--s.top;
	return OK;
}
Status Pop(SqStack_float &s){
	if(s.top==s.base) return ERROR;
	--s.top;
	return OK;
}

Status StackTraverse(SqStack s){
	if(s.base==NULL) return ERROR;
	SElemType *p=s.base;
	while(p!=s.top){
		cout<<*p<<" ";
		++p;
	}
	cout<<endl;
	return OK;
}

Status StackEmpty(SqStack s){
	if(s.base==NULL) exit(OVERFLOW);
	else if(s.base==s.top) return TRUE;
	else return FALSE;
}
Status StackEmpty(SqStack_float s){
	if(s.base==NULL) exit(OVERFLOW);
	else if(s.base==s.top) return TRUE;
	else return FALSE;
}


SElemType GetTop(SqStack s){
	if(s.base==NULL || s.base==s.top) return ERROR;
	return *(s.top-1);
}
float GetTop(SqStack_float s){
	if(s.base==NULL || s.base==s.top) return ERROR;
	return *(s.top-1);
}


//3.17判断输入的字符串中'&'前和'&'后部分是否为逆串,是则返回1,否则返回0
int IsReverse(){
	SqStack s;
	InitStack(s);
	cout<<"请输入前半部分字符，以&作为结束符:"<<endl;
	char e_l=' ';
	while ((e_l=getchar())!='&'){
		Push(s, e_l);
	}

	while(getchar()!='\n');

	cout<<"请输入后半部分字符，以@作为结束符:"<<endl;
	char e_r=' ', e=' ';
	while((e_r=getchar())!='@'){
		if(StackEmpty(s)) return 0;
		Pop(s, e);
		if(e_r!=e) return 0;
	}
	if(!StackEmpty(s)) return 0;
	return 1;
}

////3.19判别表达式中三种括号是否匹配，尽量使用断言
Status AllBrackets_Test(char *str){
	SqStack s;
	InitStack(s);
	char *p=str, q=' ';
	while(*p){
		if(*p=='{' || *p=='[' || *p=='('){
			Push(s, *p);
		}
		else if(*p=='}' || *p==']' || *p==')'){
			if(StackEmpty(s)) return 0;
			Pop(s,q);
			if(*p=='}' && q!='{') return 0;
			if(*p==']' && q!='[') return 0;
			if(*p==')' && q!='(') return 0;
		}
		p++;
	}
	if(!StackEmpty(s)) return 0;
	return 1;
}

int In(char c)//判断读入的字符是否为操作符，如果是返回1，不是则返回0
{
	if((c>='0'&&c<='9') || c=='.') return 0;
	else if(c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')'||c=='#') return 1;
	else
	{
		printf("ERROR!\n");
		return 2;
	}
}


int Precede(char a,char b)//比较操作符a与b的优先级，a的优先级比b高返回1，a的优先级比b低返回0，a，b同级返回2，不可比较返回3(有先后顺序之分)
{
	switch(a)
	{
	case '+':
		{
			switch(b)
			{
			case '+':return 1;
			case '-':return 1;
			case '*':return 0;
			case '/':return 0;
			case '(':return 0;
			case ')':return 1;
			case '#':return 1;
			}
		}
	case '-':
		{
			switch(b)
			{
			case '+':return 1;
			case '-':return 1;
			case '*':return 0;
			case '/':return 0;
			case '(':return 0;
			case ')':return 1;
			case '#':return 1;
			}
		}
	case '*':
		{
			switch(b)
			{
			case '+':return 1;
			case '-':return 1;
			case '*':return 1;
			case '/':return 1;
			case '(':return 0;
			case ')':return 1;
			case '#':return 1;
			}
		}
	case '/':
		{
			switch(b)
			{
			case '+':return 1;
			case '-':return 1;
			case '*':return 1;
			case '/':return 1;
			case '(':return 0;
			case ')':return 1;
			case '#':return 1;
			}
		}
	case '(':
		{
			switch(b)
			{
			case '+':return 0;
			case '-':return 0;
			case '*':return 0;
			case '/':return 0;
			case '(':return 0;
			case ')':return 2;
			case '#':return 3;
			}
		}
	case ')':
		{
			switch(b)
			{
			case '+':return 1;
			case '-':return 1;
			case '*':return 1;
			case '/':return 1;
			case '(':return 3;
			case ')':return 1;
			case '#':return 1;
			}
		}
	case '#':
		{
			switch(b)
			{
			case '+':return 0;
			case '-':return 0;
			case '*':return 0;
			case '/':return 0;
			case '(':return 0;
			case ')':return 3;
			case '#':return 2;
			}
		}
	}

}

float Operate(float a,char theta,float b)//进行运算。
{
	float c;
	switch(theta)
	{
	case '+':c=a+b;break;
	case '-':c=a-b;break;
	case '*':c=a*b;break;
	case '/':
		{
			if(b==0)
			{
				printf("\n分母为零，运算终止！\n");
				return (b);
			}
			else
			{
				c=a/b;
				break;
			}
		}
	}
	return (c);
}

//把中缀表达式str转换成逆波兰式new
void NiBoLan(char *str, char *new_str){
	SqStack s;
	char temp=' ';
	char *p=str;
	char *q=new_str;
	InitStack(s);//操作符栈，越往栈顶优先级越高的原则
	Push(s, '#');

	while(*p){
		if (In(*p)==0){//如果是数字或者小数点
			*q=*p;
			q++;
			p++;
			if(*p && In(*p)==1) *q++='|';//输出字符串有空格隔开(下同)
		}
		else if(In(*p)==1){//如果是运算符
			switch(Precede(GetTop(s), *p)){
			case 0:	Push(s, *p);//*p的优先级高，则将*p进栈，再取一个字符
					p++;
					break;
			case 1:	do{
						Pop(s, temp);
						*q++=temp;
						*q++='|';
					}while(Precede(GetTop(s), *p)==1);//*p的优先级低，跳出此次循环时，p不变，重新执行while。
					break;
			case 2: Pop(s);//优先级相等（左右括号相遇，将‘（’弹出，注意：‘）’就没有进栈）
					p++;
					break;
			case 3:	
			default: printf("\nERROR!\n");break;
			}
		}
		else{
			printf("\nERROR!\n");break;
		}
	}

	if(*(--p)!=')' && GetTop(s)!='#') *q++='|';

	while(GetTop(s)!='#') {//把栈中剩余的运算符弹出存入工作数组中。
		Pop(s, temp);
		*q++=temp;
		*q++='|';
	}

	//处理末尾字符串
	--q;
	if(*q=='|') *q='\0';
	else *(++q)='\0';

}

//3.22
float GetValue_NiBoLan(char *str)//对逆波兰式求值，逆波兰式各个元素之间以‘|’分隔。
{	
	SqStack_float s;
	InitStack(s);
	char *p=(char*)malloc(2*N*sizeof(char));
	strcpy(p, str);
	const char *delim="|"; 
	char *q;
	float a, b, last;
	q=strtok(p, delim);
	while(q){
		if(In(*q)!=1){
			Push(s, atof(q));
		}
		else if(In(*q)==1){//如果是操作符，出栈，计算，入栈
			Pop(s, a);
			Pop(s, b);
			last=Operate(b, *q, a);//注意顺序
			Push(s, last);
		}
		q=strtok(NULL, delim);
	}
	Pop(s, last);
	return last;
}

//////////////////////////////////////////////////////////////////////////

typedef struct QNode{
	QElemType data;
	struct QNode * next;
}QNode, *QueuePtr;

typedef struct{
	QueuePtr front;//队头
	QueuePtr rear;//队尾
}LinkQueue;

//初始化链式队列Q
void InitQueue(LinkQueue &lq){
	lq.front=lq.rear=(QueuePtr)malloc(sizeof(QNode));//只初始化队列头
	if(!lq.front) exit(OVERFLOW);
	lq.front->next=NULL;
}

//删除队列(从队头之前的lq.front开始删除)
Status DetroryQueue(LinkQueue &lq){
	while(lq.front){
		lq.rear=lq.front->next;//暂存
		free(lq.front);
		lq.front=lq.rear;
	}
	return OK;
}

//队尾插入
Status EnQueue(LinkQueue &lq, QElemType e){
	QueuePtr p_qn=(QueuePtr)malloc(sizeof(QNode));
	if(!p_qn) exit(OVERFLOW);
	p_qn->data=e;	p_qn->next=NULL;
	lq.rear->next=p_qn;	lq.rear=p_qn;
	return OK;
}
//对头去除
Status DeQueue(LinkQueue &lq, QElemType &e){
	if(lq.front==lq.rear) return ERROR;
	QueuePtr p_qn=lq.front->next;
	lq.front->next=p_qn->next;
	e=p_qn->data;
	if(lq.rear==p_qn) lq.rear=lq.front;//如果除了lq.front外，只有一个元素，则删除后队列空，需要改变lq.rear的值
	free(p_qn);
}
//遍历
Status QueueTraverse(LinkQueue lq){
	if(lq.front==lq.rear) return ERROR;
	QueuePtr p_qn=lq.front->next;//指向队列头
	while(p_qn){
		cout<<p_qn->data<<' ';
		p_qn=p_qn->next;
	}
	cout<<endl;
	return OK;
}
//////////////////////////////////////////////////////////////////////////
//顺序循环队列

typedef struct{
	QElemType *base;
	int front;
	int rear;
}SqQueue;

Status InitQueue(SqQueue &sq){
	sq.base=(QElemType*)malloc(sizeof(QElemType)*MAXQSIZE);
	sq.front=sq.rear=0;
	return OK;
}

//队列长度
int QueueLength(SqQueue sq){
	return (sq.rear-sq.front+MAXQSIZE)%MAXQSIZE;
}

//入队列
Status EnQueue(SqQueue &sq, QElemType e){
	if((sq.rear+1)%MAXQSIZE==sq.front) return ERROR;//队列满
	sq.base[sq.rear]=e;
	sq.rear=(sq.rear+1)%MAXQSIZE;
	return OK;
}

//出队列
Status DeQueue(SqQueue &sq, QElemType &e){
	if(sq.rear==sq.front) return ERROR;//队列空
	e=sq.base[sq.front];
	sq.front=(sq.front+1)%MAXQSIZE;
}

//队列空
Status QueueEmpty(SqQueue sq){
	if(sq.rear==sq.front) return 1;//队列空
	else return 0;
}

//遍历
Status QueueTraverse(SqQueue sq){
	if(sq.front==sq.rear) return ERROR;//空队列
	int i=sq.front;
	while(i!=sq.rear){
		cout<<sq.base[i]<<' ';
		i++;
		i=(i+MAXQSIZE)%MAXQSIZE;
	}
	cout<<endl;
	return OK;
}
//3.31
int Palindrome_Test()//判别输入的字符串是否回文序列,是则返回1,否则返回0
{
	SqStack s;
	InitStack(s);
	SqQueue sq;
	InitQueue(sq);
	char e_stack;
	char e_queue;
	char *p=new char;
	while((*p=getchar())!='@'){
		Push(s, *p);
		EnQueue(sq, *p);
	}
	StackTraverse(s);
	QueueTraverse(sq);

	while(!StackEmpty(s)){
		Pop(s, e_stack);
		DeQueue(sq, e_queue);
		if(e_stack!=e_queue) return FALSE;
	}
	StackTraverse(s);
	QueueTraverse(sq);

	if(!QueueEmpty(sq)) return FALSE;
	delete p;
	return OK;
}

int main(){
	/*
	while (1){
		cout<<IsReverse();
		system("pause");
		while(getchar()!='\n');
	}
	*/

//////////////////////////////////////////////////////////////////////////

	/*
	//3.19
	while(1){
		char a[N];
		gets(a);
		cout<<AllBrackets_Test(a);
	}
	*/

//////////////////////////////////////////////////////////////////////////
	/*
	//3.21
	while(1){
		char a[N],b[2*N];
		cout<<"请输入中序表达式a[N]:";
		gets(a);
		NiBoLan(a, b);
		cout<<"转变后的逆波兰式b[N]:";
		cout<<b<<endl;

		cout<<"转变后的逆波兰式b[N]的值为:";
		cout<<GetValue_NiBoLan(b)<<endl;
		system("pause");
	}
	*/

	//////////////////////////////////////////////////////////////////////////
	/*
	LinkQueue lq;
	InitQueue(lq);
	char x=' ';
	while (x!='@')
	{
		cin>>x;
		EnQueue(lq, x);
	}
	cout<<QueueTraverse(lq)<<endl;

	DeQueue(lq, x);
	cout<<QueueTraverse(lq)<<endl;

	while(lq.rear!=lq.front){
		DeQueue(lq, x);
	}
	cout<<QueueTraverse(lq)<<endl;

	system("pause");
	*/

	//////////////////////////////////////////////////////////////////////////
	/*
	while(1){
		cout<<Palindrome_Test()<<endl;
		system("pause");
	}
	*/

}