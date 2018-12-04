#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <cstring>

#include "Classtype.h"
#include "main.h"
#include "boostFunction.h"
#include "file.h"
#include "menu.h"
using namespace std;

extern CcommonUser commmonuser;


/**管理员CAuth成员函数**/
/**注册账号***/
void CAuth::registeruser(){ //todo
    char tep[20];
    char user[20];
    char password[20];
    char yesorno='Y';
    int i;
    FILE *fp;
    system("cls");
        printf("\t\t\t\t注册\n\n\n");
        printf("\t\t\t请设置用户名：");
        scanf("%s",user);
        fp=fopen(ACCOUNTFILE,"r");

    do{
       printf("\n\t\t\t请设置密码：");
       scanf("%s",password);

       printf("\t\t\t请确认密码：");
       scanf("%s",tep);

        while(getchar() != '\n');
        do{
            printf("\t\t\t账号是否为管理员(YorN)：");
            scanf("%c",&yesorno);
        }while(yesorno != 'Y' && yesorno != 'N');


       if(strcmp(tep,password)!=0)
        printf("\n\t\t\t两次密码不一致请重新输入");
    }while(strcmp(tep,password)!=0);
    fp=fopen(ACCOUNTFILE,"a");
    if(fp==NULL){
          printf("\n\t注册失败\n");
          exit(0);
       }
    else{
       fputs(user,fp);
       fputc(',',fp);
       fputs(password,fp);
       fputc(',',fp);
       if( yesorno=='Y' )fputc('1',fp);
       else fputc('2',fp);
        printf("\n\t注册成功");
    }
    fclose(fp);
    system("pause");
}


void CAuth::addBook(){
    fstream infile;
    CTypesBook tmp;
	infile.open(TYPESBOOK, ios::out| ios::in );
	if(infile.fail()) {
        cout << "添加失败" << endl;
        return ;
	}

    vector<string> idcol;       //找到最大的ID+1
    vector<string> namecol;     //不重复
	string lineStr;

     while (getline(infile, lineStr) ){     //获取行
    stringstream ss(lineStr);
    string bookid;                              //记录列数据,必须写在这个循环里
    getline(ss, bookid, ',');
    idcol.push_back(bookid);
    string bookname ;
    getline(ss, bookname, ',');
    namecol.push_back(bookname);
    }

    int addid = vecMAX(idcol)+1;
    stringstream inttostring;
    inttostring << addid;
    tmp.BookID = inttostring.str();

    int first = 1;
    do{
        if(first == 1){
            cout << "请输入图书名称：" << endl;
            cin >> tmp.BookName ;
            first = 0;
        }else{
             cout << "重复,请重新输入书名:" << endl;
            cin >> tmp.BookName ;
        }
    }while(find(namecol.begin(),namecol.end(),tmp.BookName) != namecol.end());
    //唯一书名不重复=>不能一次性增加==>单个增加
    cout << "请输入书的作者：" << endl;
        cin >> tmp.Author ;
    cout << "请输入馆藏地址：" << endl;
        cin >> tmp.Address ;
    cout << "请输入类别：" << endl;
        cin >> tmp.Category ;
    do{
        cout << "请输入书的数量：" << endl;
		scanf("%d",&tmp.TotalNumber);
		while(getchar()!='\n') ;
	}while(  tmp.TotalNumber  == 0  ) ;    //默认为0,非数字情况时不变

    do{
        cout << "请输入书的价格：" << endl;
		scanf("%lf",&tmp.Price);
		while(getchar() != '\n') ;
	}while( tmp.Price  == 0 ) ;
    infile.clear();
    infile << tmp.BookID << ',' << tmp.BookName << ',' <<
    tmp.Author << ',' << tmp.Address << ','
    << tmp.Category << ',' <<tmp.TotalNumber << ',' << tmp.Price << ',' << "0" << ',' << "1" << endl;

    infile.close();

    if (addBookdetail(tmp)) cout << "添加完毕" << endl;
    else cout << "添加失败，请咨询后台" << endl;
    system("pause");
        /**具体的书中定义**/
    //cout << "请输入书的入库时间：" << endl;           //
        //cin >> tmp.BookName ;
    //cout << "请输入书的归还时间：" << endl;
        //cin >> tmp.BookName ;
        /**具体的书中定义**/

        /**通过计算得出**/
//    cout << "请输入书的借阅次数:" << endl;
//        cin >> tmp.BookName ;
//    cout << "请输入书的借阅状态:" << endl;
//        cin >> tmp.BookName ;
        /**通过计算得出**/

}


/*** 将TypesBook里的可借阅状态和数量修改***/
void  CAuth::deleteBook(){
    vector<vector<string> > row;        //记录行数据
    string PATH  = BOOKPATH;
    string searchname;
    string Inputsearchname;
    string id;                          //删除书id
        do{                                 //多次输入
        cout << "请输入书名,按Q退出查询:\n";

        cin >> Inputsearchname;
        searchname = PATH + Inputsearchname +".csv";
        CTypesBook tmp;
        ifstream infile;

        infile.open(searchname.c_str(),ios::in);
        if(infile.fail()) {
                if(Inputsearchname != "Q")
                    cout << "不存在该书,请重试" <<endl;
        }
        else{
             string lineStr;
             while (getline(infile, lineStr) ){     //获取行
                stringstream ss(lineStr);
                string str;
                vector<string> col;                 //记录列数据,必须写在这个循环里
                while (getline(ss, str, ',')) {
                    printf("%-8s\t",str.c_str());
                    col.push_back(str);
                }
                row.push_back(col);
                cout << endl;
             }

            infile.close();
             bool flag = false;
             if( !row.empty() ){
                 while( !flag ){
                        cout << "请输入要删除的书本ID:" << endl;
                        cin >> id;
                        if(id == "Q") return;
                        for (int i = 1; i < row.size(); i++){  /*这边不能写int rowSize = row.size();否则会影响循环遍历*/
                            if ( row.at(i).at(0) == id ){
                                row.erase(row.begin()+i);
                                flag = true;
                            }
                        }
                 }
             }
             ofstream out;
             out.open(TMPFILE,ios::out);
             int rowSize = row.size();
            for (int i = 0; i < rowSize ; i++) {
                for(int j = 0; j < BOOKCOL; j++) out << row.at(i).at(j) << "," ;
                out << endl;
            }
        out.close();
        string oldname = TMPFILE;
        renameFilename( oldname, searchname);
        cout << "删除成功!" << endl;

        stringstream ss(id);
        string bookid;
        getline(ss,bookid,'/');
        if( row.size() !=1 ){          //最后一本的情况
            int booklef = row.size() - 1;
            stringstream ss;
            ss << booklef;
            string num = ss.str();
            update( bookid,5,num  );
        }else {
            string command = "delete";  //在总书里删除该书记录
            update( bookid,5,command);
        }
    }
    }while(Inputsearchname != "Q");
    system("pause");
}

/*** 查找指定书本,根据书名 ***/
void  CAuth::searchBook(){
    string Inputsearchname;
    do{      //多次输入
        cout << "请输入书名,按Q退出查询:\n";

        cin >> Inputsearchname;
        string PATH  = BOOKPATH;
        string searchname = PATH + Inputsearchname +".csv";
        CTypesBook tmp;
        ifstream infile;
        if(Inputsearchname == "Q") return;

        infile.open(searchname.c_str(),ios::in);
        if(infile.fail()) {
                cout << "不存在该文件,按任意键返回上级" ;
                system("pause");
        }
        else{
             string lineStr;
             while (getline(infile, lineStr) ){
                stringstream ss(lineStr);
                string str;
                while (getline(ss, str, ',')) printf("%-8s\t",str.c_str());
                cout << endl;
             }
             system("pause");
             return;
        }
    infile.close();
    }while(Inputsearchname != "Q");
}

/**CcommonUser的成员函数实现**/
// 借书-->具体和总书的借阅次数++
// 借书-->具体书的归还时间
// 借书-->总书里的可借阅状态
void CcommonUser::borrowBook(){
     ifstream in;
     string lineStr;

     in.open(TYPESBOOK,ios::in);
     if(in.fail()){
        cout << "无法借阅" <<endl;
        return ;
     }
     while (getline(in, lineStr) ){         //获取行
        stringstream ss(lineStr);
        string str;
        while (getline(ss, str, ',')) {
            printf("%-8s\t",str.c_str());
        }
        cout << endl;
     }
     in.close();


    /**修改books_s里面csv**/
    vector<vector<string> > row;        //记录行数据
     vector<string> canVec;             //具体书里是否可借
     vector<string> readtimesVec;

    string Inputsearchname;
        do{                                 //多次输入
        cout << "请输入书名,按Q退出查询:\n";

        cin >> Inputsearchname;
        string PATH  = BOOKPATH;
        string searchname = PATH + Inputsearchname +".csv";
        CTypesBook tmp;
        ifstream infile;

        infile.open(searchname.c_str(),ios::in);
        if(infile.fail()) {
                if(Inputsearchname != "Q")
                    cout << "不存在该文件" <<endl;
        }
        else{
            //printf("%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t\n",
            //      "索引值","名称作者","入库时间","借出时间","归还时间","数量","可借状态") ;
            //表头
             while (getline(infile, lineStr) ){     //获取行
                stringstream ss(lineStr);
                string str;
                vector<string> col;                 //记录列数据,必须写在这个循环里
                while (getline(ss, str, ',')) {
                    printf("%-8s\t",str.c_str());
                    col.push_back(str);
                }
                row.push_back(col);
                cout << endl;
             }
             string id;

             bool flag = false;
             while( !flag ){
                    cout << "请输入要借阅的书本ID(按Q退出):" << endl;
                    cin >> id;
                    if(id == "Q") return;
                    for (int i = 1; i < row.size(); i++){
                        canVec.push_back(row.at(i).at(7));    //借阅状态
                        readtimesVec.push_back(row.at(i).at(7));    //借阅次数

                        if ( row.at(i).at(0) == id ){
                            if( row.at(i).at(7) == "0")
                                cout << "当前书不可借,请重新选择" << endl;
                           else{                                        //可借时才能
                                row.at(i).at(4) = getTime();

                                CBook cbook;                            //声明个类好传参
                                cbook.BookID = row.at(i).at(0);         //ID
                                cbook.BookName = row.at(i).at(1);       //书名
                                cbook.Author = row.at(i).at(2);         //作者
//                                cbook.Category = row.at(i).at(3);
                                cbook.outDate = row.at(i).at(4);        //借书时间

                                CData borrowtime;
                                cbook.returnData = borrowtime.getReturntime(row.at(i).at(4));
                                row.at(i).at(5) = cbook.returnData;     //归还时间

                                int times = atoi(row.at(i).at(6).c_str())+1;
                                stringstream ss;
                                ss << times;
                                row.at(i).at(6) = ss.str();             //借阅次数*
                                row.at(i).at(7) = "0";                  //借阅状态

                                CcommonUser::createBookfile(cbook);
                                flag = true;
                            }
                        }
                    }
             }
             ofstream out;
             out.open(TMPFILE,ios::out);                //生成一个临时的文件来将新的数据写入
             int rowSize = row.size();
            for (int i = 0; i < rowSize ; i++) {
                for(int j = 0; j < BOOKCOL; j++) out << row.at(i).at(j) << "," ;
                out << endl;
            }
        out.close();
        infile.close();
        string oldname =  TMPFILE;
        renameFilename(oldname,searchname);             //将临时文件替换为原来的.csv
        cout << "借书成功!" << endl;


        char num[20];
        string readtime = itoa(vecSUM(readtimesVec),num,10 );
        update(id,7,readtime);

        if ( std::find(canVec.begin(), canVec.end(), "1") == canVec.end() )  //没找到可以借的
            {
            string no = "0";
            update(id,8,no);
            }
        }
    }while(Inputsearchname != "Q");
}


/**用户在自己的下面创建借书记录:增加和删除===>TODO:借阅过的书,多加一个字段(Boolreturn)**/
void CcommonUser::createBookfile(CBook &book){
    fstream f;
    string PATH = USERPATH;
    string filename = PATH + this->UID + ".csv";
    f.open(filename.c_str(),ios::app);
    if(f.fail()){
        cout << "无法借阅" <<endl;
        return ;
    }
    f << book.BookID << "," << book.BookName << "," << book.Author <<  ","
        <<book.outDate << "," << book.returnData <<endl;
    f.close();
}


/**
查看借过的书,指定ID还书
**/
void CcommonUser::lookBook(){
    fstream f;
    string PATH = USERPATH;
    string filename = PATH + this->UID + ".csv";
    string bookname;    //更新具体书时需要
    f.open(filename.c_str(),ios::in);
    if(f.fail()){
        cout << "没有借阅信息,按任意键返回上级" <<endl;
        system("pause");
        READERsMenu();
        return ;
    }
    f.close();

    vector< vector<string> > row = getTablecontent(filename);

     if( row.empty() ){ //为空情况
        cout << "没有借过书,请找点书读读" <<endl;
        system("pause");
        return ;
     }else{
            string bookid;
             int rowsize = row.size();
           /*****三天紧急*****/
           printf("%-8s\t%-8s\t%-8s\t%-8s\t%-8s\n", "索引值","书名","作者","借入时间","归还时间");
            for(int i=0;i< rowsize;i++){
                    string shouldReturn = row.at(i).at(4);
                    CData shouldtime(shouldReturn);
                    string now = getTime();
                    int lefttime = shouldtime - now;

                    if( lefttime < 4 ) {
                         if( lefttime > 0) {
                                stringstream ss;
                                ss << lefttime;
                                row.at(i).at(4) = "还有" +  ss.str() + "天,快!";
                         }
                        else if(lefttime ==0)  row.at(i).at(4) = "请在当天归还,快!";
                        else {
                            double order =  -0.1*lefttime;   //欠费账单
                            stringstream ss;
                            ss << order;
                            row.at(i).at(4) = "已经欠费" + ss.str() +"元";
                        }
                    }
            }
            //输出借阅书信息
            for (int i = 0; i < rowsize ; ++i){
                int colsize = row.at(i).size();
                for (int j = 0; j < colsize ; ++j)
                    printf("%-8s\t", row.at(i).at(j).c_str());
                cout << endl;
            }

            /*****三天紧急*****/
            bool flag = false;
             while( !flag ){
                cout << "请选择要归还的书ID(按Q退出):"<< endl;
                cin >> bookid;
                if(bookid =="Q") return;
                for (int i = 0; i < row.size(); i++){  /*这边不能写int rowSize = row.size();否则会影响循环遍历*/
                    if ( row.at(i).at(0) == bookid ){
                        /*将还书写入readed_books文件夹下*/
                        string returnPath = READEDBOOKPATH;
                        string returnfile = returnPath + this->UID + ".csv";
                        ofstream ff;
                        /**归还时间是现在*/
                        string returntime = getTime();
                        row.at(i).at(4)=returntime;
                        ff.open(returnfile.c_str(),ios::app);
                        int colsize = row.at(i).size();
                        for(int j = 0; j < colsize; j++) ff << row.at(i).at(j) << ',';
                        ff << endl;
                        ff.close();

                        bookname = row.at(i).at(1);

                        row.erase(row.begin()+i);
                        flag = true;
                        break;
                    }
                }
            }
            /**写入用户借书临时文件**/
             ofstream out;
             out.open(USERTMPFILE,ios::out);
             int rowSize = row.size();
             for (int i = 0; i < rowSize ; i++) {
                for(int j = 0; j < RETURNBOOKCOL; j++)
                    out << row.at(i).at(j) << "," ;
                    //out << row.at(i).at(j) << "," ;    //最后一个","不妨碍
                out << endl;
            }
            out.close();
            string oldname = USERTMPFILE;
            renameFilename(oldname,filename);
            /**临时文件改名**/

            string canread = "1";
            update(bookid,8,canread);

            map<int,string> changefield;
            changefield.insert(pair<int, string>(7, canread));
            changefield.insert(pair<int, string>(5, "#"));
            changefield.insert(pair<int, string>(4, "#"));
            updateDetail(bookname,changefield);

            cout << "还书成功!" <<endl;
     }
     cout << "按任意键返回上级" << endl;
    //while(getchar()!='\n') ;
    system("pause");


    READERsMenu();
}

/**
热门图书,根据借阅次数降序展示
**/
 void  CcommonUser::topBooks(){
    vector< vector<string> > row;
    string filename = TYPESBOOK;
    row = getTablecontent(filename);
    sort(row.begin()+1,row.end(),cmp);
    for (int i = 0; i < row.size() ; ++i){
        int colsize = row.at(i).size();
        for (int j = 0; j < colsize ; ++j)
             printf("%-8s\t", row.at(i).at(j).c_str());
        cout << endl;
    }
    system("pause");
 }

 void CcommonUser::guessYoulike(){
    fstream f;
    string PATH = READEDBOOKPATH;
    string filename = PATH + this->UID + ".csv";
    vector< vector<string> >row = getTablecontent(filename);
    vector<string> bookname;            //阅读过书名
    map<string,int>classnum ;           //阅读过书类别
    if( row.empty() ){
        printf("\t\t\t\t\t\t\t%s\n", "推荐热门图书");
        this->topBooks();
        return ;
    }
    else{
        int rowsize = row.size();
        for(int i=0; i < rowsize ; i++) bookname.push_back(row.at(i).at(1));
        string typebook =TYPESBOOK;
        vector< vector<string> > typesbookrow = getTablecontent(typebook);
        int typesbookrowsize = typesbookrow.size();
        int booktotal = bookname.size();

        printf("\t\t\t\t\t\t\t\t%s\n", "猜你喜欢");
        printf("%-8s\t%-8s\t%-8s\t%-8s\t%-8s\n", "索引值","书名","作者","借入时间","归还时间");
        for(int i=0;i < booktotal ;i++){
              for(int j=0;j< typesbookrowsize ; j++) {
                if( typesbookrow.at(j).at(1) == bookname.at(i) )        //书名匹配
                    if( classnum.count( typesbookrow.at(j).at(4)) == 0 ) classnum[typesbookrow.at(j).at(4)]=1;
                    else classnum[typesbookrow.at(j).at(4)]++;
                    // 类别=>typesbookrow.at(j).at(4)  : 次数
                else continue;
            }
        }
        vector< pair<string, int> > v(classnum.begin(), classnum.end());
        sort(v.begin(), v.end(),cmpPair);
        for(int i=0;i< typesbookrowsize ; i++) {
            if(typesbookrow.at(i).at(4) == v.at(0).first){
                int colnum = typesbookrow.at(i).size();
                for(int j=0;j<colnum;j++){
                    if( find(bookname.begin(),bookname.end(),typesbookrow.at(i).at(1) )==bookname.end() )
                        //书名不重复
                        printf("%-8s\t",typesbookrow.at(i).at(j).c_str());
                    else;
                }
                printf("\n");
            }else continue;

        }
        ;      //次数最多的类别
    }
    system("pause");
 }


 void CcommonUser::readedBook(){
     fstream f;
    string PATH = READEDBOOKPATH;
    string filename = PATH + this->UID + ".csv";
    vector< vector<string> >row = getTablecontent(filename);

    if( row.empty())    cout << "没有借阅记录" <<endl;
    else{
        int rowsize = row.size();
        for(int i=0; i < rowsize ; i++){
            int colsize = row.at(i).size();
            for(int j=0;j<colsize;j++) printf("%-8s\t",row.at(i).at(j).c_str());
            cout << endl;
        }
    }
    system("pause");
 }



void CcommonUser::registeruser(){
    char tep[20];
    char user[20];
    char password[20];
    FILE *fp;
    system("cls");
        printf("\t\t\t\t注册\n\n\n");
        printf("\t\t\t请设置用户名：");
        scanf("%s",user);
        fp=fopen(ACCOUNTFILE,"r");

    do{
       printf("\n\t\t\t请设置密码：");
       scanf("%s",password);

       printf("\t\t\t请确认密码：");
       scanf("%s",tep);

       if(strcmp(tep,password)!=0)
        printf("\n\t\t\t两次密码不一致请重新输入");
    }while(strcmp(tep,password)!=0);
    fp=fopen(ACCOUNTFILE,"a");
    if(fp==NULL){
          printf("\n\t注册失败\n");
          exit(0);
       }
    else{
       fputs(user,fp);
       fputc(',',fp);
       fputs(password,fp);
       fputc(',',fp);
       fputc('2',fp);
       fputc('\n',fp);
        printf("\n\t注册成功");
    }
    fclose(fp);
}
/**CcommonUser的成员函数实现**/


/**CData**/
CData::CData(string &timestr){
    stringstream ss(timestr);
    string str;
    getline(ss, str, '/');
    	this->year = atoi(str.c_str());
    getline(ss, str, '/');
    	this->month = atoi(str.c_str());
    getline(ss, str, '/');
    	this->day = atoi(str.c_str());
}

/**计算时间差**/
int CData::operator-(string &timestr){       //大的减小的,传入的小
    stringstream ss(timestr);
    string str;
    int y,m,d;

    const int m_day[12 + 1] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    getline(ss, str, '/');
    	y = atoi(str.c_str());
    getline(ss, str, '/');
    	m = atoi(str.c_str());
    getline(ss, str, '/');
    	d = atoi(str.c_str());
    int leap = this->is_leap(y);

    int dely,delm,deld;
    dely = this->year - y;
    delm = this->month - m;
    deld = this->day - d;
    int gap=0;
    if(leap){
        gap += 366*dely ;
        if(m==2) gap += 29*delm + deld;
        else gap += m_day[m]*delm + deld;
    }
    else gap += 365*dely + m_day[m]*delm + deld;
    return gap;
}


bool CData::valid(int y, int m, int d) {
    //不是润年情况
    const int m_day[12 + 1] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 0 || d == 0) return false;
    if (m > 12) return false;
    //润年情况下,需要对2月份特殊处理
    if ( CData::is_leap(y) && m == 2 && d > 29) return false;
    if ( CData::is_leap(y) && m != 2 && d > m_day[m]) return false;
    //不是润年情况
    if (!CData::is_leap(y) && d > m_day[m]) return false;
    return true;
}

string CData::getReturntime(string &borrowtime){
    const int m_day[12 + 1] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    stringstream ss(borrowtime);
    string str;
    int year;
    int month;
    int day;
    getline(ss, str, '/');
    	year = atoi(str.c_str());
    getline(ss, str, '/');
    	month = atoi(str.c_str());
    getline(ss, str, '/');
    	day = atoi(str.c_str());

    if( is_leap(year) && month == 2 ){
             day = day + 30 - 29 ;
             month += 1;
    }else if( is_leap(year) && month != 2 ){
             day = day + 30 -  m_day[month];
             month += 1;
    }else{      // !is_leap(year)
             day = day + 30 -  m_day[month];
             month += 1;
    }
    while( !valid(year,month,day) ){
        year ++;
        month --;
    }

    std::stringstream timess;
    timess<< year << "/" << month << "/" << day ;
    return timess.str();
}
