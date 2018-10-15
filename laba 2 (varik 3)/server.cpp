#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <iostream>
using namespace std;
 
BOOL fReturnCode ; //��� ���������� � �������
DWORD cbMessages ; //����� �����������
DWORD cbMsgNumber ; //������� ���������� � MailSlot
LPCTSTR MailSlotName = "\\\\.\\mailslot\\test"; //��'� �����  "\\\\.\\mailslot\\test" 
HANDLE hMailSlot; //���������� �����

 
char buf [512]; //����� ��� ������� �����
DWORD  cbRead ; //������� ����� �����, ��������� ����� MailSlot
 
int main(int argc, const char* argv[])
{	
	setlocale(LC_ALL,"UKR");
	
	
    //��������� ������� ��������:
    hMailSlot=CreateMailslot(MailSlotName,0,MAILSLOT_WAIT_FOREVER,NULL);
    //���� ������� �������-����� � ��������
    if(hMailSlot==INVALID_HANDLE_VALUE)
    {
        DWORD errorValue = GetLastError();
        cout <<"������� ��������� MailSlot!"<<endl;
        getch();
        return 0;
    }
    while(1)
    {//��������� ���� MailSlot
      fReturnCode=GetMailslotInfo(hMailSlot,NULL,&cbMessages,&cbMsgNumber,NULL);
      if(!fReturnCode)
      {cout<<"������� ��������� MailSlotInfo!"<<endl;
      getch();
      return 0;
      }
 
      //���� � MailSlot � �����������, �� ������ �����
      if(cbMsgNumber!=0)
      {
          if(ReadFile(hMailSlot,buf,512,&cbRead,NULL))
              printf("�������� %d ����i�: <%s>\n",cbRead,buf);
          else printf("������� �������i �����!\n");
          break;
      }
    }
    getch();
    CloseHandle(hMailSlot);
    return 0;
}
