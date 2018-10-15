#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <iostream>
using namespace std;

HANDLE hMailSlot; //дескриптор пошти
LPCTSTR MailSlotName = "\\\\.\\mailslot\\test";  //iм'я пошти "\\\\.\\mailslot\\test"
char buf [512]; //буфер для передачi даних
DWORD  cbWritten ; //кiлькiість байтiв даних, переданих через MailSlot
 
int main(int argc, const char* argv[])
{	
	setlocale(LC_ALL,"UKR");
		
	//відкриваємо поштову скриньку:
    hMailSlot=CreateFile(MailSlotName,GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);
    //якщо виникла помилка-вихід з програми
    if(hMailSlot==INVALID_HANDLE_VALUE)
    {
        cout<<"Помилка CreateFile!"<<endl;
        getch();
        return 0;
    }
 
    //передача даних через Mailslot
    char d[] = " ";
 	cout << "Введiть повiдомлення: " ;
 	cin >> d;
    strcpy(buf, d);
    if(!WriteFile(hMailSlot,buf,strlen(buf)+1,&cbWritten,NULL))
        printf("Помилка передачi даних\n");
    else printf("Передано %d байтiв : <%s>\n",cbWritten,buf);
    CloseHandle(hMailSlot);
    getch();
    return 0;
}
