#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <conio.h>      //掩盖密码
#include <cstring>

/*自定义头文件*/
#include "menu.h"
#include "file.h"
#include "main.h"
#include "boostFunction.h"

#include "Classtype.h"


using namespace std;

CUser user ;    //声明一个全局的用户类实例
CTypesBook typesbook ;
CAuth auth ;/**在认证后加**/
CcommonUser commmonuser;
/*
    **********************************
    *  系统环境：Windows10 操作系统  *
    *  项目环境：Code Blocks 17.12   *
    *  作者:陈力                     *
    **********************************
*/

int main(){
    /**窗口设置**/
    SetScreenGrid();
    SetSysCaption();
    /**窗口设置**/
    idMenu();
    return 0;
}


/****菜单模块****/
void AuthMenu() {
    system("cls");
    printf("\n\n\n\n\n\n\n");
    printf("                          \t            ********************************\n\n");
    printf("                          \t             |        ①图书管理          |\n\n");
    printf("                          \t             |        ②开放账号          |\n\n");
    printf("                          \t             |        ③返回上一级        |\n\n");
    printf("                          \t            ********************************\n\n");
    int i;
  printf("请输入选项[1-3]:");
  scanf("%d",&i);
  while(i<1||i>3){
   printf("请重新选择\n");
   scanf("%d",&i);
  }
  switch(i){
  case 1:
    BOOKsMenu();break;
  case 2:
    auth.registeruser();break;
  case 3:
    idMenu();break;
  }
}




void BOOKsMenu()            //图书管理
{
    system("cls");
    printf("\n\n\n\n\n\n\n");
    printf("                          \t            ********************************\n\n");
    printf("                          \t             |        ①增加图书          |\n\n");       //未写
    printf("                          \t             |        ②删减图书          |\n\n");
    printf("                          \t             |        ③查看图书          |\n\n");
    printf("                          \t             |        ④返回上一级        |\n\n");
    printf("                          \t            ********************************\n\n");
   int i;
      do{
       printf("请输入选项[1-4]:\n");
       scanf("%d",&i);
       while(getchar()!='\n') ;
      }while(i<1||i>4);
  switch(i){
  case 1:
      auth.addBook();
      break;
  case 2:
        auth.deleteBook();
        break;
  case 3:
      auth.searchBook();
      break;
  case 4:
      AuthMenu();break;
  }
}
void READERsMenu(){         //读者管理
     system("cls");
     printf("\n\n\n\n\n\n\n");
     printf("                          \t             *********************************\n\n");
     printf("                          \t             |        ①查找图书借阅         |\n\n");
     printf("                          \t             |        ②查看已借图书         |\n\n");
     printf("                          \t             |        ③查看TOP热门图书      |\n\n");
     printf("                          \t             |        ④猜你喜欢             |\n\n");
     printf("                          \t             |        ⑤查看已还图书         |\n\n");
     printf("                          \t             |        ⑥返回上一级           |\n\n");
     printf("                          \t             *********************************\n\n");
     int i;
      do{
       printf("请输入选项[1-6]:\n");
       scanf("%d",&i);
       while(getchar()!='\n') ;
      }while(i<1||i>6);
      switch(i){
      case 1:
            commmonuser.borrowBook();
            break;
      case 2:
          commmonuser.lookBook();       //查看后还书
          break;
      case 3:                           //查看还书功能
          commmonuser.topBooks();
          break;
      case 4:
            commmonuser.guessYoulike();
            break;
      case 5:
            commmonuser.readedBook();
            break;
      case 6:
          idMenu();
          break;
      }
}

/****菜单模块****/



/*****登录模块*****/
/*输入账号*/
void idMenu(){
   int choice=0;
   do{
            system("cls");
           printf("                          \t             *****************************\n");
           printf("                          \t                    南邮图书馆管理系统\n\n");
           printf("                          \t             |        ①读者登陆          |\n\n");
           printf("                          \t             |        ②读者注册          |\n\n");
           printf("                          \t             |        ③管理员登陆        |\n\n");
           printf("                          \t             |        ④注销当前用户      |\n\n");
           printf("                          \t             |        ⑤退出系统          |\n\n");
           printf("                          \t            ********************************\n\n");
        /**考虑到退到主界面的问题,直接将printf全放循环里**/
       printf("请输入你的选项[1-5](Ctrl + c退出):\n");
       scanf("%d",&choice);
       while(getchar()!='\n') ;  //避免有输入 非数值的情况 , 提高程序的鲁棒性和稳定性
       switch(choice){
           case 1:
                 studentMenu();
                break;
           case 2:
                commmonuser.registeruser();
                break;
           case 3:
                administratorMenu();
                break;
           case 4:
                logout();
                break;
           case 5:
                exit(0);
       }
    }while( choice != 1 || choice != 2 || choice != 3 || choice != 4|| choice != 5) ;
}


/*管理员登录*/
void administratorMenu(){
    string UID;
    string PWD;
    int confirmed = false;
    //判断是否认证成功
    if( user.status == AUTH ){     //已认证过
            system("cls");
            AuthMenu();
            return;
        }else if(user.status == COMMONUSER) cout << "当前账号非管理员" <<endl;
    do{
        cout <<"请输入管理员账号ID(输入Q退出):" <<endl;
        cin  >> UID;
//        cout <<"请输入密码:" <<endl;
//        cin  >> PWD;
        if(UID == "Q") break;
        PWD = inputPassword();
        confirmed = confirmStatus(UID,PWD,user);
        if( !confirmed ) cout << "\n账号或密码错误,请尝试.账号ID输入'Q'退出" << endl;
        else{           //数据库里有此账号数据,但不是管理员
            if( user.status != AUTH ) {
                    confirmed = false;
                    cout << "这个不是管理员账号请重新输入!" << endl;
            }
        }
//    }while( !confirmed && UID != "Q");
    }while( !confirmed);    // UID输入Q时用return;重构
    if(confirmed) {
//        user.status = AUTH;
        auth.UID = UID;
        system("cls");
        AuthMenu();
    }
}

/*普通用户登录*/
void studentMenu(){
    string UID;
    string PWD;
    int confirmed = false;
    //while(1){       //循环
        if( user.status == COMMONUSER || user.status == AUTH){        //判断是否认证过
            system("cls");
            READERsMenu();
            return;
        }
        do{
            cout <<"请输入普通账号ID(或管理员账号):" <<endl;
            cin  >> UID;
            if(UID == "Q") return;
//            cout <<"请输入密码:" <<endl;
//            cin  >> PWD;
            PWD = inputPassword();

            confirmed = confirmStatus(UID,PWD,user);
            if( !confirmed ) cout << "\n账号或密码错误,请尝试.账号ID输入'Q'退出\n";
//        }while( !confirmed && UID != "Q");
        }while( !confirmed);    // UID输入Q时用return;重构
            if(confirmed) {
            //cout << "成功认证" << endl;
//            user.status = COMMONUSER; confirmStatus函数里写了
            commmonuser.UID = UID;
            system("cls");
            READERsMenu();          //进入普通用户界面
            }
    //}
}

void logout(){
    user.status = 0;
    cout << "注销成功" <<endl;
    system("pause");
}


/***掩盖密码***/
string inputPassword(){
    int i = 0;
    char ch;
    char passwd[15] = {0};
    printf("请输入密码: ");
    while((ch = getch())!='\r'){
        if(i>10)     //当密码超过10位
        {   fflush(stdin);
            system("cls");
            memset(passwd,0,sizeof(passwd));
            i = 0;
            printf("请输入不超过十位的密码: ");
            continue;
        }
        if(ch == '\b'){         //当键入退格键时
            if(i>0){
                i--;
                printf("\b \b");
                passwd[i] = 0;
                continue;
            }else{
                printf("\a");     //没有内容的时候
                continue;
            }
        }else{
            passwd[i] = ch;
            printf("*");
        }
        i++;
    }
    string PWD =  passwd;
    return PWD;
}
/***掩盖密码***/


/*****登录模块*****/
