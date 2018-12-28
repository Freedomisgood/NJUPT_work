#ifndef _STUDENT
#define _STUDENT
#include <string.h>
#define NUM 20

typedef struct Student 
{
	long num;
	char name[20];
	char sex[10];
	int score[3];
	int total;
	int rank;
}Student;
//typedef struct Student Student;

#define sizeStu sizeof(Student)

int readStu(Student sut[],int n);
void printStu(Student *stu,int n);

int equal(Student s1,Student s2,int condition);
int larger(Student s1,Student s2,int condition);
void reverse(Student str[],int n);

void calcuTotal(Student stu[],int n);
void calcuRank(Student stu[],int n );
void calcuMark(double m[3][3],Student stu[],int n); 

void sortStu(Student stu[],int n ,int condition );
int searchStu(Student stu[],int n,Student s,int condition,int f[]);
int insertStu(Student stu[],int n,Student s);
int deleteStu(Student stu[],int n,Student s);
#endif