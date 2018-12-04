#include "boostFunction.h"
#include "main.h"

#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <sstream>
using namespace std;
/**���ÿ���̨��Ļ��С**/
void SetScreenGrid(){
    char sysSetBuf[80];
    sprintf(sysSetBuf, "mode con cols=%d lines=%d", CMD_COLS, CMD_LINES);
    system(sysSetBuf);
}


/**����̨����**/
void SetSysCaption(){
    system("title ����ͼ���ϵͳ");
}


/**
��������: ɾ��(����)��ʱ�ļ�
��������: ԭ�ļ���oldfile,���ļ���newfile
��������ֵ:��
**/
void renameFilename(string &oldfile,string &newfile){
    remove(newfile.c_str());
    rename(oldfile.c_str(), newfile.c_str());
}


/**
��������:���ص�ǰʱ��
��������:��
��������ֵ:string currentTime
**/
string getTime(){
    time_t timep;
    time(&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y/%m/%d",localtime(&timep) );
    return tmp;
}


/**����vec�����ֵ**/
int vecMAX(vector<string> & vec){
    vector<int> v;
    for(int i=0;i < vec.size();i++){
        v.push_back(atoi(vec.at(i).c_str()));
    }
    return *max_element(v.begin(),v.end());
}

/**����vec���ܺ�**/
int vecSUM(vector<string> &vec){
        vector<int> v;
    for(int i=0;i < vec.size();i++){
        v.push_back(atoi(vec.at(i).c_str()));
    }
    return accumulate(v.begin(),v.end(),1);
}

/**
���ݴ�����ļ���,��ö�ά������
**/
vector< vector<string> > getTablecontent(string &path ){
    fstream f;
    f.open(path.c_str(),ios::in);
    vector<vector<string> > row;        //��¼������
    if(f.fail()){
        cout << "��Ϣ������" <<endl;
        return row;
    }else{

    /**�������ݴ���vec��**/
     string lineStr;
     while (getline(f, lineStr) ){     //��ȡ��
        stringstream ss(lineStr);
        string str;
        vector<string> col;                 //��¼������,����д�����ѭ����
        while (getline(ss, str, ',')) col.push_back(str);
        row.push_back(col);
     }
        return row;
    }   //û�з���ֵ,ֱ��Ϊ��
    f.close();
}
