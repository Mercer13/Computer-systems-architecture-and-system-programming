#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <iostream>
using namespace std;

HANDLE hMailSlot; //���������� �����
LPCTSTR MailSlotName = "\\\\.\\mailslot\\test";  //i�'� ����� "\\\\.\\mailslot\\test"
char buf [512]; //����� ��� �������i �����
DWORD  cbWritten ; //�i���i���� ����i� �����, ��������� ����� MailSlot
 
int main(int argc, const char* argv[])
{	
	setlocale(LC_ALL,"UKR");
		
	//��������� ������� ��������:
    hMailSlot=CreateFile(MailSlotName,GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);
    //���� ������� �������-����� � ��������
    if(hMailSlot==INVALID_HANDLE_VALUE)
    {
        cout<<"������� CreateFile!"<<endl;
        getch();
        return 0;
    }
 
    //�������� ����� ����� Mailslot
    char d[] = " ";
 	cout << "����i�� ���i��������: " ;
 	cin >> d;
    strcpy(buf, d);
    if(!WriteFile(hMailSlot,buf,strlen(buf)+1,&cbWritten,NULL))
        printf("������� �������i �����\n");
    else printf("�������� %d ����i� : <%s>\n",cbWritten,buf);
    CloseHandle(hMailSlot);
    getch();
    return 0;
}
