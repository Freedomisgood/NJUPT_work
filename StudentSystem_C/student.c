#include <stdio.h>
#include <string.h>

#include "student.h"
int readStu(Student *stu,int n)
{
	int i,j;
	for (i=0;i<n;i++)
	{
		printf("Please input one student\'s information\n");
		printf("num:\n");
		scanf("%ld",&stu[i].num);
		if (stu[i].num ==0)break;
	
		printf("name:\n");
		scanf("%s",stu[i].name);

		printf("sex:\n");
		scanf("%s",stu[i].sex);
		
		stu[i].total = 0;
		printf("Input three courses of the student:\n");
		for(j=0;j<3;j++)
			scanf("%d",&stu[i].score[j]);
		stu[i].rank =0;
	}
	return i;
}

void printStu(Student *stu,int n)
{
	int i,j;
	for (i=0;i<n;i++)
	{
		printf("%8ld",stu[i].num);
		printf("%10s",stu[i].name);
		printf("%8s",stu[i].sex);
		for (j=0;j<3;j++)
		{
			printf("%6d",stu[i].score[j]);
		}
		printf("%6d",stu[i].total);
		printf("%6d\n",stu[i].rank);
	}
}

int equal(Student s1,Student s2,int condition)
{
	if(condition==1)
		return s1.num == s2.num;
	else if (condition ==2)
	{	
		if (strcmp(s1.name,s2.name)==0)
			return 1;
		else
			return 0;
	}
	else if (condition ==3)
		return s1.rank == s2.rank;
	else if (condition ==4)
		return s1.total == s2.total;
	else
		return 1;
}

int larger(Student s1,Student s2,int condition)
{
	if (condition ==1)
		return s1.num>s2.num;
	else if (condition ==2)
		return s1.total > s2.total;
	else return 1;
}

void reverse(Student stu[],int n)
{
	int i;
	Student temp;
	for (i=0;i<n/2;i++)
	{
		temp = stu[i];
		stu[i]=stu[n-i-1];
		stu[n-1-i] = temp;
	}
}

void calcuTotal(Student stu[],int n )
{
	int i,j;
	for (i=0;i<n;i++)
	{
		stu[i].total =0;
		for (j=0;j<3;j++)
			stu[i].total += stu[i].score[j];
	}
}

void calcuRank(Student stu[],int n )
{
	int i;
	sortStu(stu,n,2);
	reverse(stu,n);
	stu[0].rank =1;
	for (i=1;i<n;i++)
	{
		if (equal(stu[i],stu[i-1],4))
			stu[i].rank = stu[i-1].rank;
		else 
			stu[i].rank = i+1;
	}
}

void calcuMark(double m[3][3],Student stu[],int n)
{
	int i,j;
	for (i=0;i<3;i++)				//求最高分
	{
		m[i][0] = stu[0].score[i];
		for(j=1;j<n;j++)
			if (m[i][0]<stu[j].score[i])
				m[i][0]=stu[j].score[i];

	}
	
	for (i=0;i<3;i++)				//求最低分
	{	m[i][1] = stu[0].score[i];
		for(j=1;j<n;j++)
		{
			if (m[i][0]>stu[j].score[i])
				m[i][0]=stu[j].score[i];
		}
	}
	
	for (i=0;i<3;i++)
	{
		m[i][2] = stu[0].score[i];
		for(j=1;j<n;j++)
			m[i][2] += stu[0].score[i];
		m[i][2] /= n;
	}
}   

void sortStu(Student stu[],int n, int condition)
{
	int i,j,minpos;
	Student t;
	for(i=0;i<n-1;i++)
	{
		minpos = i;
		for (j=i+1;j<n;j++)
		{
			if( larger( stu[minpos],stu[j],condition) )
				minpos = j;
		}
		if (i!=minpos)
		{
			t=stu[i];
			stu[i] = stu[minpos];
			stu[minpos] =t;
		}
	}
}

int searchStu(Student stu[],int n,Student s,int condition,int f[])
{
	int i,j=0,find=0;
	for(i=0;i<n;i++)
	{
		if(equal(stu[i],s,condition))
		{
			f[j++]=i;
			find++;
		}
	}
	return find;
}

int insertStu(Student stu[],int n,Student s)
{
	int i;
	sortStu(stu,n,1);
	for (i=0;i<n;i++)
	{
		if (equal(stu[i],s,1))
		{
			printf("this record exist,can not insert again!\n");
			return n;
		}
	}

	for (i=n-1;i>=0;i--)
	{
		if (!larger(stu[i],s,1))
			break;
		stu[i+1]=stu[i];
	}
	stu[i+1]=s;
	n++;
	return n;
}

int deleteStu(Student stu[],int n,Student s)
{
	int i,j;
	for (i=0;i<n;i++)
		if (equal(stu[i],s,1))
			break;
	if (i==n)
	{
		printf("This record does not exist!\n");
		return n;
	}
	for (j=i;j<n-1;j++)
		stu[j]=stu[j+1];
	n--;
	return n;
}
