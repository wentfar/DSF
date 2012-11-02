#ifndef sq_stack_h
#define sq_stack_h

#define STACK_INIT_SIZE 10 //初始栈的最大长度
#define STACKINCREMENT 10 //每次新增的栈的长度

template <class DataType>
class sq_stack{
public:
	sq_stack();
	void Push(DataType e); //插入为e的新栈顶元素
	void Pop(); //删除栈顶元素
	DataType Top(); //取出栈顶元素
	bool Empty(); //判断栈是否为空：空返回1
	~sq_stack(); //栈被销毁

private:
	DataType *base; //栈尾
	DataType *top; //栈顶
	int stacksize;
};
#endif