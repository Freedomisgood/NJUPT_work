#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <conio.h>      //�ڸ�����
#include <cstring>

/*�Զ���ͷ�ļ�*/
#include "menu.h"
#include "file.h"
#include "main.h"
#include "boostFunction.h"

#include "Classtype.h"


using namespace std;

CUser user ;    //����һ��ȫ�ֵ��û���ʵ��
CTypesBook typesbook ;
CAuth auth ;/**����֤���**/
CcommonUser commmonuser;
/*
    **********************************
    *  ϵͳ������Windows10 ����ϵͳ  *
    *  ��Ŀ������Code Blocks 17.12   *
    *  ����:����                     *
    **********************************
*/

int main(){
    /**��������**/
    SetScreenGrid();
    SetSysCaption();
    /**��������**/
    idMenu();
    return 0;
}


/****�˵�ģ��****/
void AuthMenu() {
    system("cls");
    printf("\n\n\n\n\n\n\n");
    printf("                          \t            ********************************\n\n");
    printf("                          \t             |        ��ͼ�����          |\n\n");
    printf("                          \t             |        �ڿ����˺�          |\n\n");
    printf("                          \t             |        �۷�����һ��        |\n\n");
    printf("                          \t            ********************************\n\n");
    int i;
  printf("������ѡ��[1-3]:");
  scanf("%d",&i);
  while(i<1||i>3){
   printf("������ѡ��\n");
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




void BOOKsMenu()            //ͼ�����
{
    system("cls");
    printf("\n\n\n\n\n\n\n");
    printf("                          \t            ********************************\n\n");
    printf("                          \t             |        ������ͼ��          |\n\n");       //δд
    printf("                          \t             |        ��ɾ��ͼ��          |\n\n");
    printf("                          \t             |        �۲鿴ͼ��          |\n\n");
    printf("                          \t             |        �ܷ�����һ��        |\n\n");
    printf("                          \t            ********************************\n\n");
   int i;
      do{
       printf("������ѡ��[1-4]:\n");
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
void READERsMenu(){         //���߹���
     system("cls");
     printf("\n\n\n\n\n\n\n");
     printf("                          \t             *********************************\n\n");
     printf("                          \t             |        �ٲ���ͼ�����         |\n\n");
     printf("                          \t             |        �ڲ鿴�ѽ�ͼ��         |\n\n");
     printf("                          \t             |        �۲鿴TOP����ͼ��      |\n\n");
     printf("                          \t             |        �ܲ���ϲ��             |\n\n");
     printf("                          \t             |        �ݲ鿴�ѻ�ͼ��         |\n\n");
     printf("                          \t             |        �޷�����һ��           |\n\n");
     printf("                          \t             *********************************\n\n");
     int i;
      do{
       printf("������ѡ��[1-6]:\n");
       scanf("%d",&i);
       while(getchar()!='\n') ;
      }while(i<1||i>6);
      switch(i){
      case 1:
            commmonuser.borrowBook();
            break;
      case 2:
          commmonuser.lookBook();       //�鿴����
          break;
      case 3:                           //�鿴���鹦��
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

/****�˵�ģ��****/



/*****��¼ģ��*****/
/*�����˺�*/
void idMenu(){
   int choice=0;
   do{
            system("cls");
           printf("                          \t             *****************************\n");
           printf("                          \t                    ����ͼ��ݹ���ϵͳ\n\n");
           printf("                          \t             |        �ٶ��ߵ�½          |\n\n");
           printf("                          \t             |        �ڶ���ע��          |\n\n");
           printf("                          \t             |        �۹���Ա��½        |\n\n");
           printf("                          \t             |        ��ע����ǰ�û�      |\n\n");
           printf("                          \t             |        ���˳�ϵͳ          |\n\n");
           printf("                          \t            ********************************\n\n");
        /**���ǵ��˵������������,ֱ�ӽ�printfȫ��ѭ����**/
       printf("���������ѡ��[1-5](Ctrl + c�˳�):\n");
       scanf("%d",&choice);
       while(getchar()!='\n') ;  //���������� ����ֵ����� , ��߳����³���Ժ��ȶ���
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


/*����Ա��¼*/
void administratorMenu(){
    string UID;
    string PWD;
    int confirmed = false;
    //�ж��Ƿ���֤�ɹ�
    if( user.status == AUTH ){     //����֤��
            system("cls");
            AuthMenu();
            return;
        }else if(user.status == COMMONUSER) cout << "��ǰ�˺ŷǹ���Ա" <<endl;
    do{
        cout <<"���������Ա�˺�ID(����Q�˳�):" <<endl;
        cin  >> UID;
//        cout <<"����������:" <<endl;
//        cin  >> PWD;
        if(UID == "Q") break;
        PWD = inputPassword();
        confirmed = confirmStatus(UID,PWD,user);
        if( !confirmed ) cout << "\n�˺Ż��������,�볢��.�˺�ID����'Q'�˳�" << endl;
        else{           //���ݿ����д��˺�����,�����ǹ���Ա
            if( user.status != AUTH ) {
                    confirmed = false;
                    cout << "������ǹ���Ա�˺�����������!" << endl;
            }
        }
//    }while( !confirmed && UID != "Q");
    }while( !confirmed);    // UID����Qʱ��return;�ع�
    if(confirmed) {
//        user.status = AUTH;
        auth.UID = UID;
        system("cls");
        AuthMenu();
    }
}

/*��ͨ�û���¼*/
void studentMenu(){
    string UID;
    string PWD;
    int confirmed = false;
    //while(1){       //ѭ��
        if( user.status == COMMONUSER || user.status == AUTH){        //�ж��Ƿ���֤��
            system("cls");
            READERsMenu();
            return;
        }
        do{
            cout <<"��������ͨ�˺�ID(�����Ա�˺�):" <<endl;
            cin  >> UID;
            if(UID == "Q") return;
//            cout <<"����������:" <<endl;
//            cin  >> PWD;
            PWD = inputPassword();

            confirmed = confirmStatus(UID,PWD,user);
            if( !confirmed ) cout << "\n�˺Ż��������,�볢��.�˺�ID����'Q'�˳�\n";
//        }while( !confirmed && UID != "Q");
        }while( !confirmed);    // UID����Qʱ��return;�ع�
            if(confirmed) {
            //cout << "�ɹ���֤" << endl;
//            user.status = COMMONUSER; confirmStatus������д��
            commmonuser.UID = UID;
            system("cls");
            READERsMenu();          //������ͨ�û�����
            }
    //}
}

void logout(){
    user.status = 0;
    cout << "ע���ɹ�" <<endl;
    system("pause");
}


/***�ڸ�����***/
string inputPassword(){
    int i = 0;
    char ch;
    char passwd[15] = {0};
    printf("����������: ");
    while((ch = getch())!='\r'){
        if(i>10)     //�����볬��10λ
        {   fflush(stdin);
            system("cls");
            memset(passwd,0,sizeof(passwd));
            i = 0;
            printf("�����벻����ʮλ������: ");
            continue;
        }
        if(ch == '\b'){         //�������˸��ʱ
            if(i>0){
                i--;
                printf("\b \b");
                passwd[i] = 0;
                continue;
            }else{
                printf("\a");     //û�����ݵ�ʱ��
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
/***�ڸ�����***/


/*****��¼ģ��*****/
