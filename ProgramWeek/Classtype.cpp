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


/**����ԱCAuth��Ա����**/
/**ע���˺�***/
void CAuth::registeruser(){ //todo
    char tep[20];
    char user[20];
    char password[20];
    char yesorno='Y';
    int i;
    FILE *fp;
    system("cls");
        printf("\t\t\t\tע��\n\n\n");
        printf("\t\t\t�������û�����");
        scanf("%s",user);
        fp=fopen(ACCOUNTFILE,"r");

    do{
       printf("\n\t\t\t���������룺");
       scanf("%s",password);

       printf("\t\t\t��ȷ�����룺");
       scanf("%s",tep);

        while(getchar() != '\n');
        do{
            printf("\t\t\t�˺��Ƿ�Ϊ����Ա(YorN)��");
            scanf("%c",&yesorno);
        }while(yesorno != 'Y' && yesorno != 'N');


       if(strcmp(tep,password)!=0)
        printf("\n\t\t\t�������벻һ������������");
    }while(strcmp(tep,password)!=0);
    fp=fopen(ACCOUNTFILE,"a");
    if(fp==NULL){
          printf("\n\tע��ʧ��\n");
          exit(0);
       }
    else{
       fputs(user,fp);
       fputc(',',fp);
       fputs(password,fp);
       fputc(',',fp);
       if( yesorno=='Y' )fputc('1',fp);
       else fputc('2',fp);
        printf("\n\tע��ɹ�");
    }
    fclose(fp);
    system("pause");
}


void CAuth::addBook(){
    fstream infile;
    CTypesBook tmp;
	infile.open(TYPESBOOK, ios::out| ios::in );
	if(infile.fail()) {
        cout << "���ʧ��" << endl;
        return ;
	}

    vector<string> idcol;       //�ҵ�����ID+1
    vector<string> namecol;     //���ظ�
	string lineStr;

     while (getline(infile, lineStr) ){     //��ȡ��
    stringstream ss(lineStr);
    string bookid;                              //��¼������,����д�����ѭ����
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
            cout << "������ͼ�����ƣ�" << endl;
            cin >> tmp.BookName ;
            first = 0;
        }else{
             cout << "�ظ�,��������������:" << endl;
            cin >> tmp.BookName ;
        }
    }while(find(namecol.begin(),namecol.end(),tmp.BookName) != namecol.end());
    //Ψһ�������ظ�=>����һ��������==>��������
    cout << "������������ߣ�" << endl;
        cin >> tmp.Author ;
    cout << "������ݲص�ַ��" << endl;
        cin >> tmp.Address ;
    cout << "���������" << endl;
        cin >> tmp.Category ;
    do{
        cout << "���������������" << endl;
		scanf("%d",&tmp.TotalNumber);
		while(getchar()!='\n') ;
	}while(  tmp.TotalNumber  == 0  ) ;    //Ĭ��Ϊ0,���������ʱ����

    do{
        cout << "��������ļ۸�" << endl;
		scanf("%lf",&tmp.Price);
		while(getchar() != '\n') ;
	}while( tmp.Price  == 0 ) ;
    infile.clear();
    infile << tmp.BookID << ',' << tmp.BookName << ',' <<
    tmp.Author << ',' << tmp.Address << ','
    << tmp.Category << ',' <<tmp.TotalNumber << ',' << tmp.Price << ',' << "0" << ',' << "1" << endl;

    infile.close();

    if (addBookdetail(tmp)) cout << "������" << endl;
    else cout << "���ʧ�ܣ�����ѯ��̨" << endl;
    system("pause");
        /**��������ж���**/
    //cout << "������������ʱ�䣺" << endl;           //
        //cin >> tmp.BookName ;
    //cout << "��������Ĺ黹ʱ�䣺" << endl;
        //cin >> tmp.BookName ;
        /**��������ж���**/

        /**ͨ������ó�**/
//    cout << "��������Ľ��Ĵ���:" << endl;
//        cin >> tmp.BookName ;
//    cout << "��������Ľ���״̬:" << endl;
//        cin >> tmp.BookName ;
        /**ͨ������ó�**/

}


/*** ��TypesBook��Ŀɽ���״̬�������޸�***/
void  CAuth::deleteBook(){
    vector<vector<string> > row;        //��¼������
    string PATH  = BOOKPATH;
    string searchname;
    string Inputsearchname;
    string id;                          //ɾ����id
        do{                                 //�������
        cout << "����������,��Q�˳���ѯ:\n";

        cin >> Inputsearchname;
        searchname = PATH + Inputsearchname +".csv";
        CTypesBook tmp;
        ifstream infile;

        infile.open(searchname.c_str(),ios::in);
        if(infile.fail()) {
                if(Inputsearchname != "Q")
                    cout << "�����ڸ���,������" <<endl;
        }
        else{
             string lineStr;
             while (getline(infile, lineStr) ){     //��ȡ��
                stringstream ss(lineStr);
                string str;
                vector<string> col;                 //��¼������,����д�����ѭ����
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
                        cout << "������Ҫɾ�����鱾ID:" << endl;
                        cin >> id;
                        if(id == "Q") return;
                        for (int i = 1; i < row.size(); i++){  /*��߲���дint rowSize = row.size();�����Ӱ��ѭ������*/
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
        cout << "ɾ���ɹ�!" << endl;

        stringstream ss(id);
        string bookid;
        getline(ss,bookid,'/');
        if( row.size() !=1 ){          //���һ�������
            int booklef = row.size() - 1;
            stringstream ss;
            ss << booklef;
            string num = ss.str();
            update( bookid,5,num  );
        }else {
            string command = "delete";  //��������ɾ�������¼
            update( bookid,5,command);
        }
    }
    }while(Inputsearchname != "Q");
    system("pause");
}

/*** ����ָ���鱾,�������� ***/
void  CAuth::searchBook(){
    string Inputsearchname;
    do{      //�������
        cout << "����������,��Q�˳���ѯ:\n";

        cin >> Inputsearchname;
        string PATH  = BOOKPATH;
        string searchname = PATH + Inputsearchname +".csv";
        CTypesBook tmp;
        ifstream infile;
        if(Inputsearchname == "Q") return;

        infile.open(searchname.c_str(),ios::in);
        if(infile.fail()) {
                cout << "�����ڸ��ļ�,������������ϼ�" ;
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

/**CcommonUser�ĳ�Ա����ʵ��**/
// ����-->���������Ľ��Ĵ���++
// ����-->������Ĺ黹ʱ��
// ����-->������Ŀɽ���״̬
void CcommonUser::borrowBook(){
     ifstream in;
     string lineStr;

     in.open(TYPESBOOK,ios::in);
     if(in.fail()){
        cout << "�޷�����" <<endl;
        return ;
     }
     while (getline(in, lineStr) ){         //��ȡ��
        stringstream ss(lineStr);
        string str;
        while (getline(ss, str, ',')) {
            printf("%-8s\t",str.c_str());
        }
        cout << endl;
     }
     in.close();


    /**�޸�books_s����csv**/
    vector<vector<string> > row;        //��¼������
     vector<string> canVec;             //���������Ƿ�ɽ�
     vector<string> readtimesVec;

    string Inputsearchname;
        do{                                 //�������
        cout << "����������,��Q�˳���ѯ:\n";

        cin >> Inputsearchname;
        string PATH  = BOOKPATH;
        string searchname = PATH + Inputsearchname +".csv";
        CTypesBook tmp;
        ifstream infile;

        infile.open(searchname.c_str(),ios::in);
        if(infile.fail()) {
                if(Inputsearchname != "Q")
                    cout << "�����ڸ��ļ�" <<endl;
        }
        else{
            //printf("%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t\n",
            //      "����ֵ","��������","���ʱ��","���ʱ��","�黹ʱ��","����","�ɽ�״̬") ;
            //��ͷ
             while (getline(infile, lineStr) ){     //��ȡ��
                stringstream ss(lineStr);
                string str;
                vector<string> col;                 //��¼������,����д�����ѭ����
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
                    cout << "������Ҫ���ĵ��鱾ID(��Q�˳�):" << endl;
                    cin >> id;
                    if(id == "Q") return;
                    for (int i = 1; i < row.size(); i++){
                        canVec.push_back(row.at(i).at(7));    //����״̬
                        readtimesVec.push_back(row.at(i).at(7));    //���Ĵ���

                        if ( row.at(i).at(0) == id ){
                            if( row.at(i).at(7) == "0")
                                cout << "��ǰ�鲻�ɽ�,������ѡ��" << endl;
                           else{                                        //�ɽ�ʱ����
                                row.at(i).at(4) = getTime();

                                CBook cbook;                            //��������ô���
                                cbook.BookID = row.at(i).at(0);         //ID
                                cbook.BookName = row.at(i).at(1);       //����
                                cbook.Author = row.at(i).at(2);         //����
//                                cbook.Category = row.at(i).at(3);
                                cbook.outDate = row.at(i).at(4);        //����ʱ��

                                CData borrowtime;
                                cbook.returnData = borrowtime.getReturntime(row.at(i).at(4));
                                row.at(i).at(5) = cbook.returnData;     //�黹ʱ��

                                int times = atoi(row.at(i).at(6).c_str())+1;
                                stringstream ss;
                                ss << times;
                                row.at(i).at(6) = ss.str();             //���Ĵ���*
                                row.at(i).at(7) = "0";                  //����״̬

                                CcommonUser::createBookfile(cbook);
                                flag = true;
                            }
                        }
                    }
             }
             ofstream out;
             out.open(TMPFILE,ios::out);                //����һ����ʱ���ļ������µ�����д��
             int rowSize = row.size();
            for (int i = 0; i < rowSize ; i++) {
                for(int j = 0; j < BOOKCOL; j++) out << row.at(i).at(j) << "," ;
                out << endl;
            }
        out.close();
        infile.close();
        string oldname =  TMPFILE;
        renameFilename(oldname,searchname);             //����ʱ�ļ��滻Ϊԭ����.csv
        cout << "����ɹ�!" << endl;


        char num[20];
        string readtime = itoa(vecSUM(readtimesVec),num,10 );
        update(id,7,readtime);

        if ( std::find(canVec.begin(), canVec.end(), "1") == canVec.end() )  //û�ҵ����Խ��
            {
            string no = "0";
            update(id,8,no);
            }
        }
    }while(Inputsearchname != "Q");
}


/**�û����Լ������洴�������¼:���Ӻ�ɾ��===>TODO:���Ĺ�����,���һ���ֶ�(Boolreturn)**/
void CcommonUser::createBookfile(CBook &book){
    fstream f;
    string PATH = USERPATH;
    string filename = PATH + this->UID + ".csv";
    f.open(filename.c_str(),ios::app);
    if(f.fail()){
        cout << "�޷�����" <<endl;
        return ;
    }
    f << book.BookID << "," << book.BookName << "," << book.Author <<  ","
        <<book.outDate << "," << book.returnData <<endl;
    f.close();
}


/**
�鿴�������,ָ��ID����
**/
void CcommonUser::lookBook(){
    fstream f;
    string PATH = USERPATH;
    string filename = PATH + this->UID + ".csv";
    string bookname;    //���¾�����ʱ��Ҫ
    f.open(filename.c_str(),ios::in);
    if(f.fail()){
        cout << "û�н�����Ϣ,������������ϼ�" <<endl;
        system("pause");
        READERsMenu();
        return ;
    }
    f.close();

    vector< vector<string> > row = getTablecontent(filename);

     if( row.empty() ){ //Ϊ�����
        cout << "û�н����,���ҵ������" <<endl;
        system("pause");
        return ;
     }else{
            string bookid;
             int rowsize = row.size();
           /*****�������*****/
           printf("%-8s\t%-8s\t%-8s\t%-8s\t%-8s\n", "����ֵ","����","����","����ʱ��","�黹ʱ��");
            for(int i=0;i< rowsize;i++){
                    string shouldReturn = row.at(i).at(4);
                    CData shouldtime(shouldReturn);
                    string now = getTime();
                    int lefttime = shouldtime - now;

                    if( lefttime < 4 ) {
                         if( lefttime > 0) {
                                stringstream ss;
                                ss << lefttime;
                                row.at(i).at(4) = "����" +  ss.str() + "��,��!";
                         }
                        else if(lefttime ==0)  row.at(i).at(4) = "���ڵ���黹,��!";
                        else {
                            double order =  -0.1*lefttime;   //Ƿ���˵�
                            stringstream ss;
                            ss << order;
                            row.at(i).at(4) = "�Ѿ�Ƿ��" + ss.str() +"Ԫ";
                        }
                    }
            }
            //�����������Ϣ
            for (int i = 0; i < rowsize ; ++i){
                int colsize = row.at(i).size();
                for (int j = 0; j < colsize ; ++j)
                    printf("%-8s\t", row.at(i).at(j).c_str());
                cout << endl;
            }

            /*****�������*****/
            bool flag = false;
             while( !flag ){
                cout << "��ѡ��Ҫ�黹����ID(��Q�˳�):"<< endl;
                cin >> bookid;
                if(bookid =="Q") return;
                for (int i = 0; i < row.size(); i++){  /*��߲���дint rowSize = row.size();�����Ӱ��ѭ������*/
                    if ( row.at(i).at(0) == bookid ){
                        /*������д��readed_books�ļ�����*/
                        string returnPath = READEDBOOKPATH;
                        string returnfile = returnPath + this->UID + ".csv";
                        ofstream ff;
                        /**�黹ʱ��������*/
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
            /**д���û�������ʱ�ļ�**/
             ofstream out;
             out.open(USERTMPFILE,ios::out);
             int rowSize = row.size();
             for (int i = 0; i < rowSize ; i++) {
                for(int j = 0; j < RETURNBOOKCOL; j++)
                    out << row.at(i).at(j) << "," ;
                    //out << row.at(i).at(j) << "," ;    //���һ��","������
                out << endl;
            }
            out.close();
            string oldname = USERTMPFILE;
            renameFilename(oldname,filename);
            /**��ʱ�ļ�����**/

            string canread = "1";
            update(bookid,8,canread);

            map<int,string> changefield;
            changefield.insert(pair<int, string>(7, canread));
            changefield.insert(pair<int, string>(5, "#"));
            changefield.insert(pair<int, string>(4, "#"));
            updateDetail(bookname,changefield);

            cout << "����ɹ�!" <<endl;
     }
     cout << "������������ϼ�" << endl;
    //while(getchar()!='\n') ;
    system("pause");


    READERsMenu();
}

/**
����ͼ��,���ݽ��Ĵ�������չʾ
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
    vector<string> bookname;            //�Ķ�������
    map<string,int>classnum ;           //�Ķ��������
    if( row.empty() ){
        printf("\t\t\t\t\t\t\t%s\n", "�Ƽ�����ͼ��");
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

        printf("\t\t\t\t\t\t\t\t%s\n", "����ϲ��");
        printf("%-8s\t%-8s\t%-8s\t%-8s\t%-8s\n", "����ֵ","����","����","����ʱ��","�黹ʱ��");
        for(int i=0;i < booktotal ;i++){
              for(int j=0;j< typesbookrowsize ; j++) {
                if( typesbookrow.at(j).at(1) == bookname.at(i) )        //����ƥ��
                    if( classnum.count( typesbookrow.at(j).at(4)) == 0 ) classnum[typesbookrow.at(j).at(4)]=1;
                    else classnum[typesbookrow.at(j).at(4)]++;
                    // ���=>typesbookrow.at(j).at(4)  : ����
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
                        //�������ظ�
                        printf("%-8s\t",typesbookrow.at(i).at(j).c_str());
                    else;
                }
                printf("\n");
            }else continue;

        }
        ;      //�����������
    }
    system("pause");
 }


 void CcommonUser::readedBook(){
     fstream f;
    string PATH = READEDBOOKPATH;
    string filename = PATH + this->UID + ".csv";
    vector< vector<string> >row = getTablecontent(filename);

    if( row.empty())    cout << "û�н��ļ�¼" <<endl;
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
        printf("\t\t\t\tע��\n\n\n");
        printf("\t\t\t�������û�����");
        scanf("%s",user);
        fp=fopen(ACCOUNTFILE,"r");

    do{
       printf("\n\t\t\t���������룺");
       scanf("%s",password);

       printf("\t\t\t��ȷ�����룺");
       scanf("%s",tep);

       if(strcmp(tep,password)!=0)
        printf("\n\t\t\t�������벻һ������������");
    }while(strcmp(tep,password)!=0);
    fp=fopen(ACCOUNTFILE,"a");
    if(fp==NULL){
          printf("\n\tע��ʧ��\n");
          exit(0);
       }
    else{
       fputs(user,fp);
       fputc(',',fp);
       fputs(password,fp);
       fputc(',',fp);
       fputc('2',fp);
       fputc('\n',fp);
        printf("\n\tע��ɹ�");
    }
    fclose(fp);
}
/**CcommonUser�ĳ�Ա����ʵ��**/


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

/**����ʱ���**/
int CData::operator-(string &timestr){       //��ļ�С��,�����С
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
    //�����������
    const int m_day[12 + 1] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 0 || d == 0) return false;
    if (m > 12) return false;
    //���������,��Ҫ��2�·����⴦��
    if ( CData::is_leap(y) && m == 2 && d > 29) return false;
    if ( CData::is_leap(y) && m != 2 && d > m_day[m]) return false;
    //�����������
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
