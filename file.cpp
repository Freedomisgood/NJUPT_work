#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

#include "main.h"
#include "file.h"

#include "Classtype.h"
#include "boostFunction.h"

using namespace std;

/*验证登录者身份信息*/
int confirmStatus(const string &UID,const string &PWD,CUser & user){
//int confirmStatus(const string &UID,const string &PWD){
     ifstream inFile;
     string rUID;
     string rPWD;
     string rstatus;
//     int confirmed = false;
     //判断是否认证成功
     inFile.open(ACCOUNTFILE, ios::in);
     if (inFile.fail()){        //如果读取失败
         cout << "Cannot open file" << endl;
         return FAIL;
     }

	 string lineStr;
	 while (getline(inFile, lineStr) ){ // 获取一行
	 	stringstream ss(lineStr);
	 	string str;
	 	getline(ss, rUID, ',');	 		// 按照逗号分隔的csv文件,将列取出
	 	if ( rUID == UID){
    	 	getline(ss, rPWD, ',');		// 取出密码列
    	 	if ( rPWD == PWD){			// 如果密码列相同,则匹配成功
             // ===>使用 strcmp函数 , strcmp(rUID.c_str(),UID.c_str()) 好像并不简单  头文件cstring
                getline(ss, rstatus, ',');
                user.UID = rUID;
                user.status = atoi(rstatus.c_str());
                inFile.close();
				return OK;
            }
	 	}else continue; 				//如果账号ID不匹配则跳过该行
	 }
	 inFile.close();
	 return FAIL;						//如果遍历后都没有则返回错误
}



/*****更新书总目录*****/
/**根据ID更新**/
/**changeValue=='delete'时删除该行**/
void update(string &uid,int changefield,string& changeValue){
    string filename = TYPESBOOK;
    vector<vector<string> > row = getTablecontent(filename);        //记录行数据
	 for (int i = 0; i < row.size(); ++i){
        if(row.at(i).at(0) == uid){
            if(changeValue == "delete"){    //删除该行
                row.erase(row.begin()+i); break;
            }
            row.at(i).at(changefield) = changeValue;
            break;
        }
	 }
    ofstream fout;
     fout.open(TPYESTMPFILE,ios::out);
    for (int i = 0; i < row.size() ; i++) {
        for(int j = 0; j < TYPESBOOKCOL; j++) fout << row.at(i).at(j) << "," ;    //最后一个","不妨碍
        fout << endl;
    }
    fout.close();
    string oldname = TPYESTMPFILE;
    renameFilename(oldname,filename);
 }

/**
path:".\\sources\\books_s\\"
根据书名更新指定多个字段的内容
**/
void updateDetail(string &bookname,map<int,string> &change){         //时间\借阅状态
    string filename = BOOKPATH + bookname + ".csv";
    vector<vector<string> > row = getTablecontent(filename);        //记录行数据

	 for (int i = 0; i < row.size(); ++i){
        if(row.at(i).at(1) == bookname){
            for(map<int,string>::iterator iter = change.begin(); iter != change.end(); ++iter) //删除
                row.at(i).at(iter->first) = iter->second;
            break;
        }
	 }

    ofstream fout;
     fout.open(TMPFILE,ios::out);
    for (int i = 0; i < row.size() ; i++) {
        for(int j = 0; j < TYPESBOOKCOL; j++) fout << row.at(i).at(j) << "," ;    //最后一个","不妨碍
        fout << endl;
    }
    fout.close();
    string oldname = TMPFILE;
    renameFilename(oldname,filename);
}


/**
path:".\\sources\\books_s\\"
根据书名更新指定单个字段的内容
如果changeValue==delete可以删除该行
**/
void updateDetail(string &bookname,int changefield,string& changeValue){
    string filename = BOOKPATH + bookname + ".csv";
    vector<vector<string> > row = getTablecontent(filename);        //记录行数据
    if(row.size() == 1) {
        remove(filename.c_str());
        return ;
    }
	 for (int i = 0; i < row.size(); ++i){
        if(row.at(i).at(0) == bookname){
            if(changeValue == "delete"){
                row.erase(row.begin()+i); break;
            }
            row.at(i).at(changefield) = changeValue;
            break;
        }
	 }
    ofstream fout;
     fout.open(TMPFILE,ios::out);
    for (int i = 0; i < row.size() ; i++) {
        for(int j = 0; j < TYPESBOOKCOL; j++) fout << row.at(i).at(j) << "," ;    //最后一个","不妨碍
        fout << endl;
    }
    fout.close();
    string oldname = TMPFILE;
    renameFilename(oldname,filename);
 }



/***具体书添加***/
bool addBookdetail(CTypesBook &tmp){

    fstream bookfile;
    string path = BOOKPATH;
    string filename = path + tmp.BookName + ".csv";
    bookfile.open(filename.c_str(),ios::app );

     if (bookfile.fail()){        //如果读取失败
         return false;
     }

    vector< vector<string> > row = getTablecontent(filename);
    if(row.empty()) bookfile << "索引值,名称,作者,入库时间,借出时间,归还时间,借阅次数,可借状态" << endl;
    /**是否添加表头**/
    for(int i=1;i <= tmp.TotalNumber ;i++){
        stringstream ss;
		ss<< i;
        //string bookid = tmp.BookID + "/" + to_string(1);        //Codeblock里C++标准非C++11无法使用to_string
        string bookid = tmp.BookID + "/" + ss.str();
        string addtime = getTime();
        string borrowTime ="#";
        string returnTime ="#";

    bookfile <<  bookid  << ',' << tmp.BookName  << ',' << tmp.Author << ','<< addtime << ',' <<
    borrowTime << ',' << returnTime << ',' << "0" << ',' << "1" << endl;
    //书的ID,书名,入库时间,借出时间,归还时间,节约次数,是否可借

    }
    bookfile.close();
    return true;
}

