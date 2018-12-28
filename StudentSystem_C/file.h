#include <stdio.h>
#include <stdlib.h>
#include "student.h"

int createFile(Student stu[])
{
	FILE *fp;
	int n;
	if( (fp = fopen("G:\\Cpp\\student_system\\student.dat","wb"))  == NULL )
	{
		printf("can not open file!\n");
		exit(0);
	}
	printf("input student\'s information:\n");
	n = readStu(stu,NUM);
	fwrite(stu,sizeStu,n,fp);
	fclose(fp);
	return n;
}

int readFile(Student stu[])
{
	FILE *fp;
	int i=0;
	if( ( fp = fopen("G:\\Cpp\\student_system\\student.dat","rb") ) == NULL )
	{
		printf("file does not exite,create it first:\n");
		return 0;
	}
	fread(&stu[i],sizeStu,1,fp);
	while(!feof(fp))
	{
		i++;
		fread(&stu[i],sizeStu,1,fp);
	}
	fclose(fp);
	return i;
}

void saveFile(Student stu[],int n )
{
	FILE *fp;
	if( (fp = fopen("G:\\Cpp\\student_system\\student.dat","wb") ) == NULL )
	{
		printf("can not open file!\n");
		exit(0);
	}
	fwrite(stu,sizeStu,n,fp);
	fclose(fp);
}