#include <string>
using namespace std;
#ifndef _C_CLASS_H
#define _C_CLASS_H

#include <vector>

/**ʱ��������**/
class CData{
public:
    int year;
    int month;
    int day;
public:
    void formatTime(string &timestr);
    string getReturntime(string &borrowtime);
    bool valid(int y,int m,int d);
    CData(string &timestr);
    CData(){};

    inline bool is_leap(int y) {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    int operator-(string &timestr);
//    string operator+(const CData& d);
};

/***����****/
class CTypesBook{
    public:
        string BookID;      //��ID
        string BookName;    //����
        string Author;      //����
        string Address;     //�洢λ��
        string Category;    //���
        double  Price;      //�۸�
        int  TotalNumber;   // ����
        int  readNumber;    // �Ķ�����
        int  state;         // ����״̬
    public:
        void update(string &uid,int changefield,string& changeValue);
};


/***����ĳ�������Ϣ****/
class CBook{
    public:
        string BookID;          //����BOOKID��ȷ���򿪵ı�
        string BookName;        //����
        string Author;          //����
        string Category;        //���
        string outDate;         //���ʱ��
        string returnData;      //�黹ʱ��
        //int readTimes;          //���Ĵ���
        //int readState;          //�ɽ�״̬
};



/****�û�Ȩ��*****/
class CUser{
    public:
        string UID;
        int status;
    public:
        CUser():UID("0"),status(0){}
        CUser(string id,int _status):UID(id),status(_status){}
};

class CcommonUser:public CUser{
    public:
        string UID;
    public:
        void borrowBook(); //��ʾ����ͼ���
        /****TODO:��һҳ����===>��vector��ά��,һ����ʾһ��***/

        void createBookfile(CBook& book);  //���û�ID�����ļ�
        void returnBook();  //����,��ʾ�Լ����ͼ��
        void lookBook();    //�鿴��������Щ��      ==>����ʱ���ע

        void addReadedBook(vector<string> line);
        void guessYoulike();
        void readedBook();

        void  registeruser();
        void  topBooks();
};

/****����ԱȨ��*****/
class CAuth: public CcommonUser{
    public:
        string UID;
    public:
        void addBook();
        void deleteBook();
        void searchBook();
        void modifyBook();

        void  registeruser();
};

#endif // _C_CLASS_H

