#include <string>
#include <map>

using namespace std;
#include "Classtype.h"

int confirmStatus(const string &UID,const string &PWD,CUser & user);
int readFromcsv(string filename);


bool addBookdetail(CTypesBook &tmp);
void update(string &uid,int changefield,string& changeValue);       //����
void updateDetail(string &bookname,int changefield,string& changeValue);    //ɾ��������
void updateDetail(string &bookname,map<int,string> &change) ;        //���������==>����
