#include <string>
using namespace std;
#ifndef _C_CLASS_H
#define _C_CLASS_H

#include <vector>

/**时间日期类**/
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

/***书种****/
class CTypesBook{
    public:
        string BookID;      //书ID
        string BookName;    //书名
        string Author;      //作者
        string Address;     //存储位置
        string Category;    //类别
        double  Price;      //价格
        int  TotalNumber;   // 总数
        int  readNumber;    // 阅读次数
        int  state;         // 借阅状态
    public:
        void update(string &uid,int changefield,string& changeValue);
};


/***具体某种书的信息****/
class CBook{
    public:
        string BookID;          //根据BOOKID来确定打开的表
        string BookName;        //书名
        string Author;          //作者
        string Category;        //类别
        string outDate;         //借出时间
        string returnData;      //归还时间
        //int readTimes;          //借阅次数
        //int readState;          //可借状态
};



/****用户权限*****/
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
        void borrowBook(); //显示所有图书的
        /****TODO:下一页功能===>存vector二维表,一次显示一点***/

        void createBookfile(CBook& book);  //以用户ID创建文件
        void returnBook();  //还书,显示自己借的图书
        void lookBook();    //查看借阅了哪些书      ==>到期时间标注

        void addReadedBook(vector<string> line);
        void guessYoulike();
        void readedBook();

        void  registeruser();
        void  topBooks();
};

/****管理员权限*****/
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

