#include <iostream>
using namespace std;

typedef enum{A,B,C,D,E} SchoolName;
typedef enum{Male,Female} SexType;
typedef struct{
	char event[3];
	SchoolName school;
	SexType sex;
	int score;
}Component;
typedef struct{
	int MaleSum;
	int FemaleSum;
	int TotalSum;
}Sum;

Sum GetSum(Component a[], int n,SchoolName sn){
	Sum temp;
	temp.MaleSum=0;
	temp.FemaleSum=0;
	temp.TotalSum=0;
	int i;
	for(i=0;i<n;i++){
		if(a[i].school==sn){
			if(a[i].sex==Male) temp.MaleSum+=a[i].score;
			if(a[i].sex==Female) temp.FemaleSum+=a[i].score;
		}
	}
	temp.TotalSum=temp.MaleSum+temp.FemaleSum;
	return temp;
}

void main(){

}