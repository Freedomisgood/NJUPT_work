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
/**设置控制台屏幕大小**/
void SetScreenGrid(){
    char sysSetBuf[80];
    sprintf(sysSetBuf, "mode con cols=%d lines=%d", CMD_COLS, CMD_LINES);
    system(sysSetBuf);
}


/**控制台标题**/
void SetSysCaption(){
    system("title 南邮图书馆系统");
}


/**
函数功能: 删除(改名)临时文件
函数参数: 原文件名oldfile,新文件名newfile
函数返回值:无
**/
void renameFilename(string &oldfile,string &newfile){
    remove(newfile.c_str());
    rename(oldfile.c_str(), newfile.c_str());
}


/**
函数功能:返回当前时间
函数参数:无
函数返回值:string currentTime
**/
string getTime(){
    time_t timep;
    time(&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y/%m/%d",localtime(&timep) );
    return tmp;
}


/**计算vec中最大值**/
int vecMAX(vector<string> & vec){
    vector<int> v;
    for(int i=0;i < vec.size();i++){
        v.push_back(atoi(vec.at(i).c_str()));
    }
    return *max_element(v.begin(),v.end());
}

/**计算vec中总和**/
int vecSUM(vector<string> &vec){
        vector<int> v;
    for(int i=0;i < vec.size();i++){
        v.push_back(atoi(vec.at(i).c_str()));
    }
    return accumulate(v.begin(),v.end(),1);
}

/**
根据传入的文件名,获得二维表数据
**/
vector< vector<string> > getTablecontent(string &path ){
    fstream f;
    f.open(path.c_str(),ios::in);
    vector<vector<string> > row;        //记录行数据
    if(f.fail()){
        cout << "信息不存在" <<endl;
        return row;
    }else{

    /**将表数据存入vec中**/
     string lineStr;
     while (getline(f, lineStr) ){     //获取行
        stringstream ss(lineStr);
        string str;
        vector<string> col;                 //记录列数据,必须写在这个循环里
        while (getline(ss, str, ',')) col.push_back(str);
        row.push_back(col);
     }
        return row;
    }   //没有返回值,直接为空
    f.close();
}
