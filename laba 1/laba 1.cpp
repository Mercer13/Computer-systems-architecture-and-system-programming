#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <cstdlib>
#pragma argsused
#define WINVER 0x0502 
#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

double PCFreq = 0.0;

__int64 CounterStart = 0;

using namespace std;

typedef BOOL (WINAPI *P_GDFSE)(LPCTSTR, PULARGE_INTEGER, PULARGE_INTEGER, PULARGE_INTEGER);

void StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
    cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}

void QueryKey(HKEY hKey) 
{ 
    TCHAR    achKey[MAX_KEY_LENGTH];   
    DWORD    cbName;           
    TCHAR    achClass[MAX_PATH] = TEXT("");
    DWORD    cchClassName = MAX_PATH; 
    DWORD    cSubKeys=0;       
    DWORD    cbMaxSubKey;    
    DWORD    cchMaxClass;        
    DWORD    cValues;         
    DWORD    cchMaxValue;       
    DWORD    cbMaxValueData;    
    DWORD    cbSecurityDescriptor; 
    FILETIME ftLastWriteTime;      
 
    DWORD i, retCode; 
 
    TCHAR  achValue[MAX_VALUE_NAME]; 
    DWORD cchValue = MAX_VALUE_NAME; 
 

    retCode = RegQueryInfoKey(
        hKey,                   
        achClass,               
        &cchClassName,          
        NULL,                  
        &cSubKeys,              
        &cbMaxSubKey,             
        &cchMaxClass,          
        &cValues,               
        &cchMaxValue,           
        &cbMaxValueData,       
        &cbSecurityDescriptor,  
        &ftLastWriteTime);      
 
    if (cSubKeys)
    {
		for (i=0; i<cSubKeys; i++) 
        { 
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyEx(hKey, i,
                     achKey, 
                     &cbName, 
                     NULL, 
                     NULL, 
                     NULL, 
                     &ftLastWriteTime); 
            if (retCode == ERROR_SUCCESS) 
            {
                _tprintf(TEXT("(%d) %s\n"), i+1, achKey);
            }
        }
    } 
 
	if (cValues) 
    {

        for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++) 
        { 
            cchValue = MAX_VALUE_NAME; 
            achValue[0] = '\0'; 
            retCode = RegEnumValue(hKey, i, 
                achValue, 
                &cchValue, 
                NULL, 
                NULL,
                NULL,
                NULL);
 
            if (retCode == ERROR_SUCCESS ) 
            { 
                _tprintf(TEXT("(%d) %s\n"), i+1, achValue); 
            } 
        }
    }
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL,"UKR");
	
   //////���������� ��� ����� �� ///////

	OSVERSIONINFO os;
	os.dwOSVersionInfoSize = sizeof(os);
	GetVersionEx(&os);
	cout<<" ��: ";
	if (os.dwPlatformId == 2 && os.dwMajorVersion == 6 && os.dwMinorVersion==2)
	cout<<"Microsoft Windows 10";
	
	else cout<<endl<<os.dwPlatformId<<" / "<<os.dwMajorVersion<<" / "<<os.dwMinorVersion<<endl;
	
  //////��������� �������///////
  
	char sysDir[100];	
	if( GetSystemDirectory(sysDir, sizeof(sysDir)) ); 
	cout <<"\n �������: "<< sysDir << endl;
	
  //////��� ��� ����������� � ����'�����/////////
  
	char buffer[256];
    char buffer1[256];
        unsigned long size = 256;
 
        GetComputerName( buffer, &size );
        GetUserName(buffer1, &size );
 
        printf( " I�'� ����'�����: %s\n ", buffer );                                 
        printf( "I�'� �����������: %s\n ", buffer1 );   
		
   ////// �������������� ���� //////	
   	
    char  lp_str[512]="" ,sz_buff[MAX_PATH][MAX_PATH];
    HANDLE h_handle;
    DWORD dw_ret=0, i=1;
 
    if ( INVALID_HANDLE_VALUE != (h_handle= FindFirstVolume (lp_str, 512) ))      //FindFirstVolume
    {
        do
        {
            GetVolumePathNamesForVolumeNameA (lp_str, sz_buff[i],512, &dw_ret);  //GetVolumePathNamesForVolumeName
            i++;
        }
        while(0!=FindNextVolume( h_handle,lp_str,512));                          //FindNextVolume
        FindVolumeClose(h_handle);                                               //FindVolumeClose
    }
 
    puts("�������i �����:");
    for ( ; i!=0; i--){
        puts(sz_buff[i]);
	}
	BOOLEAN bSuccess;

	DWORD dwSectorsPerCluster;
	DWORD dwBytesPerSector;
	DWORD dwFreeClusters;
	DWORD dwTotalClusters;

	bSuccess = GetDiskFreeSpace(                                                 //GetDiskFreeSpace
		"C:\\",                    //NULL - �� ������������� C:\\    // ������� ��������� ����  //"C:\\", a��  "D:\\"
		&dwSectorsPerCluster, 
		&dwBytesPerSector, 
		&dwFreeClusters, 
		&dwTotalClusters 
		);
		
	if(!bSuccess){
		printf("�� ������� �������� i�������i� ��� ����.\n");
		exit(EXIT_FAILURE);
	}
	printf("��������� ���� C:\\ \n\n");
	printf("����i� �� ������: %d\n", dwBytesPerSector);
	printf("������� � �������i: %d\n", dwSectorsPerCluster);
	printf("�i���i �������i: %d\n", dwFreeClusters);
	printf("������ �������i�: %d\n", dwTotalClusters);

	unsigned int uiKBPerCluster = dwBytesPerSector * dwSectorsPerCluster / 1024;

	printf(" %.2f MB �i������ �i���\n", (double) uiKBPerCluster * dwFreeClusters / 1024);
	printf(" %.2f MB ������ �i���\n", (double) uiKBPerCluster * dwTotalClusters / 1024);
	
	bSuccess = GetDiskFreeSpace(                                                 //GetDiskFreeSpace
		"M:\\",                    //NULL - �� ������������� C:\\    // ������� ��������� ����  //"C:\\", a��  "D:\\"
		&dwSectorsPerCluster, 
		&dwBytesPerSector, 
		&dwFreeClusters, 
		&dwTotalClusters 
		);
		
	if(!bSuccess){
		printf("�� ������� �������� i�������i� ��� ����.\n");
		exit(EXIT_FAILURE);
	}
	printf("\n\n��������� ���� M:\\ \n\n");
	printf("����i� �� ������: %d\n", dwBytesPerSector);
	printf("������� � �������i: %d\n", dwSectorsPerCluster);
	printf("�i���i �������i: %d\n", dwFreeClusters);
	printf("������ �������i�: %d\n", dwTotalClusters);



	printf(" %.2f MB �i������ �i���\n", (double) uiKBPerCluster * dwFreeClusters / 1024);
	printf(" %.2f MB ������ �i���\n", (double) uiKBPerCluster * dwTotalClusters / 1024);
	
  /////������ ������� ��� ����� ///////
  
    printf("\n������ ������� ��i ������������ ��� �����i ��: \n");
	HKEY hTestKey;
	if( RegOpenKeyEx( HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_READ, &hTestKey) == ERROR_SUCCESS)
  		{
      			QueryKey(hTestKey);
   		}
   		
   	RegCloseKey(hTestKey);
  
  ///////���������� ������������� ////////
  
    LARGE_INTEGER lpFrequency;
	QueryPerformanceFrequency(&lpFrequency);
	printf("\n������ ������� ���������: %d", lpFrequency);
	
    return 0;
}
