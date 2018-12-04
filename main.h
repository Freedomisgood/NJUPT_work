#define OK 1
#define FAIL 0

#define PASSER 0
#define AUTH 1
#define COMMONUSER 2

/**********PATH define*************/
/**书种类.csv**/
#define TPYESTMPFILE ".\\sources\\tmp.csv"
#define TYPESBOOK ".\\sources\\books.csv"           //书总目录的位置

/**books_s下临时文件位置**/
#define BOOKPATH ".\\sources\\books_s\\"
#define TMPFILE ".\\sources\\books_s\\tmp.csv"

/**readed_books下文件位置**/
#define READEDBOOKPATH ".\\sources\\readed_books\\"

/**账号信息.csv**/
#define ACCOUNTFILE ".\\sources\\account.csv"
#define USERPATH ".\\sources\\user_s\\"
#define USERTMPFILE ".\\sources\\user_s\\tmp.csv"


/**PATH define*/
#define RETURNBOOKCOL 5 // <
#define BOOKCOL 8       // <
#define TYPESBOOKCOL 9 // <

/*****具体书的每列索引值
BookID = row.at(i).at(0);
BookName = row.at(i).at(1);
Author = row.at(i).at(2);
Category = row.at(i).at(3);
outDate = row.at(i).at(4);
returnData= row.at(i).at(5);
times = row.at(i).at(6);
canborrow = row.at(i).at(7);
****/



/*****types书的每列索引值
BookID = row.at(i).at(0);
BookName = row.at(i).at(1);
Author = row.at(i).at(2);
Category = row.at(i).at(3);
outDate = row.at(i).at(4);
returnData= row.at(i).at(5);
times = row.at(i).at(6);
canborrow = 8
****/


/***正在借的书
100009/1,三体,刘慈欣著,class,2018/11/29,2018/12/29
****/
