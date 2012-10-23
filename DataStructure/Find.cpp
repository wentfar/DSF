#include <iostream>
#include <string>
#include <iomanip>
#include "Definition.h"

#define COUNT_CHAR 10
#define SUCCESS 1  
#define UNSUCCESS 0  
#define DUPLICATE -1

#define NULLKEY 0//0为无记录标志
using namespace std;


typedef int KeyType;

typedef struct ElemType{
	KeyType key_value;
	float weight;
/*	char name[COUNT_CHAR];*/
}ElemType;//记录


typedef struct SSTable{
	ElemType *elem;
	int length;
}SSTable;//顺序存储结构

typedef ElemType TElemType;

typedef struct BiNode{
	TElemType data;
	struct BiNode *lchild, *rchild;
}BiNode, *Bitree;


void Creat_Seq(SSTable &st, int n){
	st.elem=(ElemType*)malloc((n+1)*sizeof(ElemType));
	if(!st.elem) exit(1);
	st.length=n;
}

//前序遍历
Status PreOrderTraverse(Bitree T){
	if(!T) return FALSE;
	else{
		cout<<T->data.key_value<<" ";
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

//中序遍历
Status InOrderTraverse(Bitree T){
	if(!T) return FALSE;
	else{
		InOrderTraverse(T->lchild);
		cout<<T->data.key_value<<" ";
		InOrderTraverse(T->rchild);
	}
}

Status Assign_Seq(ElemType &e){
	cout<<"请输入key:";
	cin>>e.key_value;

	cout<<"请输入weight:";
	cin>>e.weight;

/*
	cout<<"请输入name:";
	cin>>e.name;*/


	return OK;
}
Status Printf_Seq(ElemType &e){
	cout<<e.key_value<<" "<<e.weight<<" "/*<<e.name*/<<endl;
	return OK;
}


void Traverse_Seq(SSTable st, Status (*visit)(ElemType&)){
	for(int i=1;i<=st.length;i++){
		if(!visit(st.elem[i]))
			exit(1);
	}
}

void Find_sw(SSTable st, float *sw){
	sw[0]=0.0;
	for(int i=1;i<=st.length;i++){
		sw[i]=sw[i-1]+st.elem[i].weight;
	}
}

//////////////////////////////////////////////////////////////////////////
//顺序表的查找
int Search_Seq(SSTable st, KeyType key){
	//找不到则返回0
	st.elem[0].key_value=key;
	int i=st.length;
	for( ;st.elem[i].key_value!=key;--i);
	return i;
}

//有序表的查找（折半查找）
int Search_Bin(SSTable st, KeyType key){
	int low=1;
	int high=st.length;
	while(low<=high){
		int mid=(low+high)/2;
		if(st.elem[mid].key_value<key){low=mid+1;}
		else if(st.elem[mid].key_value>key){high=mid-1;}
		else return mid;
	}
	return 0;
}

//构造次优查找树
void Second_Optimal(Bitree &T, ElemType R[], float sw[], int low, int high){
	int i=low;
	int _min=abs(sw[high]-sw[low]);//假设取第一个值为最小值

	int dw=sw[high]+sw[low-1];//deltaP的前半部分
	for(int j=low+1;j<=high;j++){
		if(_min>abs(dw-sw[j]-sw[j-1])) {
			_min=abs(dw-sw[j]-sw[j-1]);
			i=j;
		}
	}
	T=(Bitree)malloc(sizeof(BiNode));
	if(!T) exit(1);
	T->data=R[i];

	if(i==low) T->lchild=NULL;	
	else if(i>low) Second_Optimal(T->lchild, R, sw, low, i-1);//构造左子树

	if(i==high) T->rchild=NULL;
	else if(i<high) Second_Optimal(T->rchild, R, sw, i+1, high);//构造右子树
}

typedef Bitree SOSTree;
//由有序表构造次优查找树
Status CreatSOSTree(SOSTree &T, SSTable st){
	float *sw=new float[st.length+1];
	if(st.length<=1){T=NULL;}
	else{
		Find_sw(st, sw);
		Second_Optimal(T, st.elem, sw, 1, st.length);
	}
	return OK;
}

//在根指针所指的二叉排序树中递归的查找某关键字等于key的数据元素，查找成功返回指针，失败则返回空指针
Bitree SearchBST(Bitree T, KeyType key){
	if(!T || T->data.key_value==key) return T;
	else if(T->data.key_value>key) return SearchBST(T->lchild, key);
	else return SearchBST(T->rchild, key);
}
//////////////////////////////////////////////////////////////////////////

//开放定址法哈希表的存储结构
int hashsize[]={11,19,29,37};//哈希表容量递增表（一个合适的素数序列）
int m=0;//哈希表表长（全局变量） 

typedef struct{
	ElemType *elem;//数据元素存储基址 动态分配数组
	int count;//当前数据元素个数 
	int size_index;//hashsize[size_index]为当前容量 
}HashTable;

int InitHashTable(HashTable &ht){
	ht.count=0;
	ht.size_index=0;
	m=hashsize[ht.size_index];//表长为全局变量
	ht.elem=(ElemType*)malloc(m*sizeof(ElemType));
	if(!ht.elem) exit(1);
	for(int i=0;i<m;i++){ht.elem[i].key_value=NULLKEY;}
	return 1;
}

/* 初始条件:哈希表H存在*/  
/* 操作结果:销毁哈希表H*/  
void DestroyHashTable(HashTable &ht)  
{  
	free(ht.elem);  
	ht.elem=NULL;  
	ht.count=0;  
	ht.size_index=0;  
} 

/* 一个简单的哈希函数(m为表长 全局变量)*/  
int Hash(KeyType K)  
{  
	return K%m;//key MOD p(其中p<=m)
} 

/*线性探测再散列*/  
int collision(int p,int d)  
{  
	return (p+d)%m;//开放定址法处理冲突,m为表长 
}

/* 在开放定址哈希表H中查找关键码为K的元素,
若查找成功,以p指示待查数据元素在表中位置,并返回SUCCESS;
否则,以p指示插入位置,并返回UNSUCCESS。
c用以计冲突次数，其初值置零，供建表插入时参考*/
Status SearchHash(HashTable ht, KeyType key, int &p, int &c){
	p=Hash(key);
	int p_original=p;
	while(ht.elem[p].key_value!=NULLKEY && ht.elem[p].key_value!=key){
		if (c<m){
			p=collision(p_original,++c);
		}
		else{
			return UNSUCCESS;
		}
	}//该位置中填有记录,并且关键字不相等,现行探测再散列
	if(ht.elem[p].key_value==key)
		return SUCCESS;
	else
		return UNSUCCESS;
}

void RecreateHashTable(HashTable&);
/* 查找不成功时插入数据元素e到开放定址哈希表H中，并返回1，
若冲突次数过大，则重建哈希表 */  
Status InsertHash(HashTable &ht, ElemType e){
	int p, c=0;
	if(SearchHash(ht, e.key_value, p, c)==SUCCESS){
		return DUPLICATE;
	}
	else if(c<hashsize[ht.size_index]/2){
		ht.elem[p]=e; ht.count++;
		return SUCCESS;
	}//冲突次数c未达到上线,c的阀值可调 
	else {
		RecreateHashTable(ht);

		InsertHash(ht, e);//将因为重构哈希表未插入的元素重新插入
		return UNSUCCESS;
	}
}

void RecreateHashTable(HashTable &ht)//重建哈希表
{
	int count=ht.count;
	ElemType *tmp=(ElemType *)malloc(count*sizeof(ElemType));
	ElemType *p=tmp;
	for(int i=0;i<m;i++){
		if(ht.elem[i].key_value!=NULLKEY)
			*(p++)=ht.elem[i];
	}//暂存原有的数据到tmp
	printf("冲突次数达到上限,增大表长,重建哈希表...\n"); 

	ht.size_index++;
	m=hashsize[ht.size_index];//更新m
	p=(ElemType *)malloc(m*sizeof(ElemType));//增大存储容量,给ht.elem重新分配空间p=new ElemType[m];
	if(!p) exit(1);
	ht.elem=p;

	ht.count=0;
	for(int i=0;i<m;i++)
		ht.elem[i].key_value=NULLKEY;//初始化
	for(p=tmp;p<tmp+count;p++){//将tmp中的原有的数据按照新的表长插入到重建的哈希表中,ht.elem[p]=e; ht.count++; return SUCCESS;
		InsertHash(ht,*p);
	}
	printf("重建哈希表成功!\n"); 
}

/* 按哈希地址的顺序遍历哈希表 */  
void TraverseHash(HashTable ht,void(*Vi)(int ,ElemType)){
	printf("哈希地址:0~%d\n",m-1);
	for(int i=0;i<m;i++){
		if(ht.elem[i].key_value!=NULLKEY) Vi(i,ht.elem[i]);
	}

}

void Printf_Hash(int i, ElemType e){
	cout<<i<<" "<<e.key_value<<" "<<e.weight<<endl;
}

//////////////////////////////////////////////////////////////////////////

typedef struct Node{
	ElemType elem;
	struct Node *next;
}Node;

typedef struct{//用链地址法解决冲突问题
	int h_value;
	struct Node *pointer;
}HashTable_L;

typedef HashTable_L* p_HashTable_L;

void Hash_Init(p_HashTable_L &ht){//哈希表初始化
	ht=new HashTable_L[m];
	for(int i = 0; i < m; i++){
		ht[i].h_value=NULLKEY;
		ht[i].pointer=NULL;
	}
}


Node* Hash_Search(p_HashTable_L ht, KeyType key){
	int p=Hash(key);
	if(ht[p].h_value == NULLKEY)
		return NULL;
	else if(ht[p].h_value == p){
		Node* ptr=ht[p].pointer;
		while(ptr != NULL){
			if(ptr->elem.key_value == key){
				return ptr;
			}
			ptr=ptr->next;
		}
	}
	else
		return NULL;
}

int Hash_Insert(p_HashTable_L &ht, ElemType e){
	int p=Hash(e.key_value);
	Node* node=new Node();
	node->elem=e;
	node->next=NULL;

	if(ht[p].h_value == NULLKEY){
		ht[p].pointer=node;
		ht[p].h_value=p;
		return 1;
	}
	else if(ht[p].h_value == p){
		Node* ptr=ht[p].pointer;
		while(ptr->next){ptr=ptr->next;}
		ptr->next=node;
		return 1;
	}
	return 0;
}


void main(){
	/*
		while (1)
		{
			SSTable st;
			int n;
			cout<<"请输入记录的条数：";
			cin>>n;
			Creat_Seq(st,n);
			Traverse_Seq(st, Assign_Seq);
			Traverse_Seq(st, Printf_Seq);

			int key;
			cout<<"请输入关键字:";
			cin>>key;
			cout<<endl<<"元素位置为:"<<Search_Seq(st, key);
			cout<<endl<<"元素位置为(二分查找):"<<Search_Bin(st, key);

			SOSTree sost;
			cout<<endl<<"正在生成静态查找树:";
			CreatSOSTree(sost, st);

			cout<<endl<<"前序遍历结果如下:";
			PreOrderTraverse(sost);

			cout<<endl<<"中序遍历结果如下:";
			InOrderTraverse(sost);

			KeyType _key;
			cout<<endl<<"请输入要查找的关键字:";
			cin>>_key;
			cout<<endl<<SearchBST(sost, _key)->data.key_value;
			system("pause");
		}
		*/
	//////////////////////////////////////////////////////////////////////////
	/*
	while(1){
		ElemType r[12]={{17,1},{60,2},{29,3},{38,4},{1,5},{2,6},{3,7},{4,8},{5,9},{6,10},{7,11},{8,12}};
		//ElemType r[10]={{17,1},{60,2},{29,3},{38,4},{1,5},{2,6},{3,7},{4,8},{60,9},{13,10}};
		HashTable h;
		InitHashTable(h);
		cout<<"向哈希表中插入记录...";
		for(int i=0;i<sizeof(r)/sizeof(r[0]);i++){
			if(InsertHash(h,r[i]) == DUPLICATE){
				cout<<endl<<"表中已有关键字"<<r[i].key_value<<"的记录,无法再插入该记录!"<<endl;
				system("pause");
				cout<<endl<<"继续插入后续元素..."<<endl;
			}
		}

		printf("按哈希地址的顺序遍历哈希表:\n");
		TraverseHash(h,Printf_Hash);
		printf("销毁哈希表...\n");

		DestroyHashTable(h);
		system("pause");
	}*/

	ElemType r[12]={{17,1},{60,2},{29,3},{38,4},{1,5},{2,6},{3,7},{4,8},{5,9},{6,10},{7,11},{8,12}};
	p_HashTable_L ht=NULL;
	Hash_Init(ht);
	for(int i=0;i<sizeof(r)/sizeof(r[0]);i++){
		Hash_Insert(ht, r[i]);
	}


	while (1)
	{
		int key;
		cout<<"请输入关键字(key):";
		cin>>key;
		Node *p=NULL;
		if(p=Hash_Search(ht, key))
			cout<<Hash(key)<<" "<<p->elem.key_value<<" "<<p->elem.weight<<endl;
		else
			cout<<"无匹配!";
	}



}
