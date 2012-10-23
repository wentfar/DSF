#include <iostream>
#define NULLKEY 0//0为无记录标志
#define SUCCESS 1  
#define UNSUCCESS 0  
#define DUPLICATE -1
using namespace std;

int hashsize[]={11,19,29,37};//哈希表容量递增表（一个合适的素数序列）
int Hash_length=0;//哈希表表长

//定义记录
struct ElemType{
	int key_value;
	float weight;
};
//定义哈希表
struct HashTable{
	ElemType *elem;//数据元素存储基址（动态分配数组）
	int count;//当前数据元素个数 
	int size_index;//hashsize[size_index]为当前容量 
};

//初始化哈希表
int InitHashTable(HashTable &ht){
	ht.count=0;
	ht.size_index=0;
	Hash_length=hashsize[ht.size_index];//表长为全局变量
	ht.elem=(ElemType*)malloc(Hash_length*sizeof(ElemType));
	if(!ht.elem) exit(1);
	for(int i=0;i<Hash_length;i++){ht.elem[i].key_value=NULLKEY;}//方便后面判断对应位置是否被占用
	return 1;
}

//销毁哈希表。
//初始条件:哈希表ht存在；操作结果:销毁哈希表ht 
void DestroyHashTable(HashTable &ht)  
{  
	if(ht.elem != NULL) free(ht.elem);  
	ht.elem=0;  
	ht.count=0;  
	ht.size_index=0;  
} 

//一个简单的哈希函数，其中Hash_length为表长
int Hash(int K)  
{  
	return K%Hash_length;//key MOD p(其中p<=Hash_length)
} 

//开放定址法处理冲突,Hash_length为表长，线性探测再散列
int collision(int H_key,int d)  
{  
	return (H_key+d)%Hash_length;
}

//在开放定址哈希表H中查找关键码为K的元素,
//若查找成功,以p指示待查数据元素在表中位置,并返回SUCCESS;
//否则,以p指示插入位置,并返回UNSUCCESS。
//注意：c用以计冲突次数，其初值置零，供建表插入时参考
int SearchHash(HashTable ht, int key, int &p, int &c){
	p=Hash(key);
	int p_original=p;
	while(ht.elem[p].key_value!=NULLKEY && ht.elem[p].key_value!=key){
		c++;
		if (c<hashsize[ht.size_index]){
			p=collision(p_original,c);
		}
		else{
			return UNSUCCESS;
		}
	}//该位置中填有记录,并且关键字不相等,线性探测再散列

	if(ht.elem[p].key_value==key)
		return SUCCESS;
	else
		return UNSUCCESS;
}

void RecreateHashTable(HashTable &ht);
//查找不成功时插入数据元素e到开放定址哈希表ht中，并返回1，若冲突次数过大，则重建哈希表
int InsertHash(HashTable &ht, ElemType e){
	int p, c=0;
	if(SearchHash(ht, e.key_value, p, c)==SUCCESS){//已经存在e
		return DUPLICATE;
	}
	else if(c<hashsize[ht.size_index]/2){//不存在e，冲突次数c未达到上限hashsize[ht.size_index]/2
		ht.elem[p]=e;
		ht.count++;
		return SUCCESS;
	}
	else {//不存在e，冲突次数c达到上限
		RecreateHashTable(ht);

		InsertHash(ht, e);//将因为重构哈希表未插入的元素重新插入
		return UNSUCCESS;
	}
}

void RecreateHashTable(HashTable &ht)//重建哈希表
{
	printf("冲突次数达到上限，增大表长，重建哈希表。。。\n"); 

	ElemType* p_tmp=ht.elem;
	int ini_size_index=ht.size_index;

	//增大存储容量,给ht.elem重新分配空间
	ht.count=0;
	ht.size_index++;
	Hash_length=hashsize[ht.size_index];//更新Hash_length
	ElemType* p_new=(ElemType*)malloc(Hash_length*sizeof(ElemType));
	if(!p_new) exit(1);
	ht.elem=p_new;

	//初始化
	for(int i=0;i<Hash_length;i++)
		ht.elem[i].key_value=NULLKEY;

	//将tmp中的原有的数据按照新的表长插入到重建的哈希表中
	for(int i=0;i<hashsize[ini_size_index];i++){
		if((p_tmp+i)->key_value!=NULLKEY){
			InsertHash(ht,*(p_tmp+i));
		}
	}

	delete[] p_tmp;
	printf("重建哈希表成功！\n"); 
}

/* 按哈希地址的顺序遍历哈希表 */  
void TraverseHash(HashTable ht,void(*Visit)(int, ElemType)){
	printf("哈希地址:0~%d\n",Hash_length-1);
	for(int i=0;i<Hash_length;i++){
		if(ht.elem[i].key_value!=NULLKEY) Visit(i,ht.elem[i]);
	}

}

void Print_Hash(int i, ElemType e){
	cout<<i<<" "<<e.key_value<<endl;
}

//////////////////////////////////////////////////////////////////////////
#define HASH_LENGTH 13

//定义记录
struct ElemType1{
	int key_value;
	float weight;
};

//定义每个子链的结点
struct Node{
	ElemType1 elem;
	struct Node *next;
};

//定义哈希表的结点
struct HashTable_Node{
	int h_value;//除取余数得到的哈希值
	struct Node *pointer;//每个子链的首地址
};

//定义链地址法的哈希表
typedef HashTable_Node* HashTable_L;

//一个简单的哈希函数，其中HASH_LENGTH为表长
int Hash1(int K)  
{  
	return K%HASH_LENGTH;//key MOD p(其中p<=HASH_LENGTH)
} 

void Hash_Init(HashTable_L &ht){//哈希表初始化
	ht=new HashTable_Node[HASH_LENGTH];
	if (!ht) exit(1);
	for(int i = 0; i < HASH_LENGTH; i++){
		ht[i].h_value=NULLKEY;//方便插入和查找
		ht[i].pointer=NULL;
	}
}

void Hash_Insert(HashTable_L &ht, ElemType1 e){
	int p=Hash1(e.key_value);

	Node* node=new Node();
	if (!node) exit(1);
	node->elem=e;
	node->next=NULL;

	if(ht[p].h_value == NULLKEY){//对应该哈希值的子链为空
		ht[p].pointer=node;
		ht[p].h_value=p;
	}
	else if(ht[p].h_value == p){//对应该哈希值的子链不为空
		Node* ptr=ht[p].pointer;
		while(ptr->next){ptr=ptr->next;}
		ptr->next=node;
	}
}

Node* Hash_Search(HashTable_L ht, int key){
	int p=Hash1(key);
	if(ht[p].h_value == NULLKEY)//对应该哈希值的子链为空
		return NULL;
	else if(ht[p].h_value == p){//对应该哈希值的子链不为空
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


void main(){
	//while(1){
	//	//ElemType r[12]={{17,1},{60,2},{29,3},{38,4},{1,5},{2,6},{3,7},{4,8},{5,9},{6,10},{7,11},{8,12}};
	//	ElemType r[12]={{17,1},{60,2},{29,3},{38,4},{1,5},{2,6},{3,7},{4,8},{5,9},{6,10},{60,9},{13,10}};
	//	HashTable h;
	//	InitHashTable(h);

	//	cout<<"向哈希表中插入记录。。。"<<endl;
	//	for(int i=0;i<sizeof(r)/sizeof(r[0]);i++){
	//		if(InsertHash(h,r[i]) == DUPLICATE){
	//			cout<<"表中已有关键字"<<r[i].key_value<<"的记录,无法再插入该记录！"<<endl;
	//			cout<<"继续插入后续元素。。。"<<endl;
	//		}
	//	}

	//	printf("按哈希地址的顺序遍历哈希表：\n");
	//	TraverseHash(h,Print_Hash);

	//	printf("销毁哈希表。。。\n");
	//	DestroyHashTable(h);
	//	system("pause");
	//}


	ElemType1 r[13]={{17,1},{60,2},{29,3},{38,4},{1,5},{2,6},{60,2},{3,7},{4,8},{5,9},{6,10},{7,11},{8,12}};
	//ElemType1 r[13]={{17,1},{60,2},{29,3},{38,4},{1,5},{2,6},{3,7},{4,8},{5,9},{6,10},{7,11},{8,12}};

	HashTable_L ht=NULL;
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
			cout<<"哈希值与关键字的值分别为："<<Hash1(key)<<" "<<p->elem.key_value<<endl;
		else
			cout<<"无匹配!"<<endl;
	}
}