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

/*��֤��¼�������Ϣ*/
int confirmStatus(const string &UID,const string &PWD,CUser & user){
//int confirmStatus(const string &UID,const string &PWD){
     ifstream inFile;
     string rUID;
     string rPWD;
     string rstatus;
//     int confirmed = false;
     //�ж��Ƿ���֤�ɹ�
     inFile.open(ACCOUNTFILE, ios::in);
     if (inFile.fail()){        //�����ȡʧ��
         cout << "Cannot open file" << endl;
         return FAIL;
     }

	 string lineStr;
	 while (getline(inFile, lineStr) ){ // ��ȡһ��
	 	stringstream ss(lineStr);
	 	string str;
	 	getline(ss, rUID, ',');	 		// ���ն��ŷָ���csv�ļ�,����ȡ��
	 	if ( rUID == UID){
    	 	getline(ss, rPWD, ',');		// ȡ��������
    	 	if ( rPWD == PWD){			// �����������ͬ,��ƥ��ɹ�
             // ===>ʹ�� strcmp���� , strcmp(rUID.c_str(),UID.c_str()) ���񲢲���  ͷ�ļ�cstring
                getline(ss, rstatus, ',');
                user.UID = rUID;
                user.status = atoi(rstatus.c_str());
                inFile.close();
				return OK;
            }
	 	}else continue; 				//����˺�ID��ƥ������������
	 }
	 inFile.close();
	 return FAIL;						//���������û���򷵻ش���
}



/*****��������Ŀ¼*****/
/**����ID����**/
/**changeValue=='delete'ʱɾ������**/
void update(string &uid,int changefield,string& changeValue){
    string filename = TYPESBOOK;
    vector<vector<string> > row = getTablecontent(filename);        //��¼������
	 for (int i = 0; i < row.size(); ++i){
        if(row.at(i).at(0) == uid){
            if(changeValue == "delete"){    //ɾ������
                row.erase(row.begin()+i); break;
            }
            row.at(i).at(changefield) = changeValue;
            break;
        }
	 }
    ofstream fout;
     fout.open(TPYESTMPFILE,ios::out);
    for (int i = 0; i < row.size() ; i++) {
        for(int j = 0; j < TYPESBOOKCOL; j++) fout << row.at(i).at(j) << "," ;    //���һ��","������
        fout << endl;
    }
    fout.close();
    string oldname = TPYESTMPFILE;
    renameFilename(oldname,filename);
 }

/**
path:".\\sources\\books_s\\"
������������ָ������ֶε�����
**/
void updateDetail(string &bookname,map<int,string> &change){         //ʱ��\����״̬
    string filename = BOOKPATH + bookname + ".csv";
    vector<vector<string> > row = getTablecontent(filename);        //��¼������

	 for (int i = 0; i < row.size(); ++i){
        if(row.at(i).at(1) == bookname){
            for(map<int,string>::iterator iter = change.begin(); iter != change.end(); ++iter) //ɾ��
                row.at(i).at(iter->first) = iter->second;
            break;
        }
	 }

    ofstream fout;
     fout.open(TMPFILE,ios::out);
    for (int i = 0; i < row.size() ; i++) {
        for(int j = 0; j < TYPESBOOKCOL; j++) fout << row.at(i).at(j) << "," ;    //���һ��","������
        fout << endl;
    }
    fout.close();
    string oldname = TMPFILE;
    renameFilename(oldname,filename);
}


/**
path:".\\sources\\books_s\\"
������������ָ�������ֶε�����
���changeValue==delete����ɾ������
**/
void updateDetail(string &bookname,int changefield,string& changeValue){
    string filename = BOOKPATH + bookname + ".csv";
    vector<vector<string> > row = getTablecontent(filename);        //��¼������
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
        for(int j = 0; j < TYPESBOOKCOL; j++) fout << row.at(i).at(j) << "," ;    //���һ��","������
        fout << endl;
    }
    fout.close();
    string oldname = TMPFILE;
    renameFilename(oldname,filename);
 }



/***���������***/
bool addBookdetail(CTypesBook &tmp){

    fstream bookfile;
    string path = BOOKPATH;
    string filename = path + tmp.BookName + ".csv";
    bookfile.open(filename.c_str(),ios::app );

     if (bookfile.fail()){        //�����ȡʧ��
         return false;
     }

    vector< vector<string> > row = getTablecontent(filename);
    if(row.empty()) bookfile << "����ֵ,����,����,���ʱ��,���ʱ��,�黹ʱ��,���Ĵ���,�ɽ�״̬" << endl;
    /**�Ƿ���ӱ�ͷ**/
    for(int i=1;i <= tmp.TotalNumber ;i++){
        stringstream ss;
		ss<< i;
        //string bookid = tmp.BookID + "/" + to_string(1);        //Codeblock��C++��׼��C++11�޷�ʹ��to_string
        string bookid = tmp.BookID + "/" + ss.str();
        string addtime = getTime();
        string borrowTime ="#";
        string returnTime ="#";

    bookfile <<  bookid  << ',' << tmp.BookName  << ',' << tmp.Author << ','<< addtime << ',' <<
    borrowTime << ',' << returnTime << ',' << "0" << ',' << "1" << endl;
    //���ID,����,���ʱ��,���ʱ��,�黹ʱ��,��Լ����,�Ƿ�ɽ�

    }
    bookfile.close();
    return true;
}

