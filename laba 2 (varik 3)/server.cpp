#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <iostream>
using namespace std;
 
BOOL fReturnCode ; //код повернення з функцій
DWORD cbMessages ; //розмір повідомлення
DWORD cbMsgNumber ; //кількість повідомлень в MailSlot
LPCTSTR MailSlotName = "\\\\.\\mailslot\\test"; //ім'я пошти  "\\\\.\\mailslot\\test" 
HANDLE hMailSlot; //дескриптор почты

 
char buf [512]; //буфер для прийому даних
DWORD  cbRead ; //кількість байтів даних, прийнятих через MailSlot
 
int main(int argc, const char* argv[])
{	
	setlocale(LC_ALL,"UKR");
	
	
    //створюємо поштову скриньку:
    hMailSlot=CreateMailslot(MailSlotName,0,MAILSLOT_WAIT_FOREVER,NULL);
    //якщо виникла помилка-вихід з програми
    if(hMailSlot==INVALID_HANDLE_VALUE)
    {
        DWORD errorValue = GetLastError();
        cout <<"Помилка створення MailSlot!"<<endl;
        getch();
        return 0;
    }
    while(1)
    {//визначаємо стан MailSlot
      fReturnCode=GetMailslotInfo(hMailSlot,NULL,&cbMessages,&cbMsgNumber,NULL);
      if(!fReturnCode)
      {cout<<"Помилка отримання MailSlotInfo!"<<endl;
      getch();
      return 0;
      }
 
      //якщо в MailSlot є повідомлення, то читаємо перше
      if(cbMsgNumber!=0)
      {
          if(ReadFile(hMailSlot,buf,512,&cbRead,NULL))
              printf("Отримано %d байтiв: <%s>\n",cbRead,buf);
          else printf("Помилка передачi даних!\n");
          break;
      }
    }
    getch();
    CloseHandle(hMailSlot);
    return 0;
}
