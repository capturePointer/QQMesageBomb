// PostMsgDemo.cpp : �������̨Ӧ�ó������ڵ㡣
//SendMessage(���ھ���������Ǹ���Ϣ�����Ӳ��������Ӳ���);
//::SendMessage(hSend, WM_CHAR, 49, 0);  ���� 1
//QQ��Ϣ��ը
//1��ģ�ⷢ�� sendmessage ϵͳ��API
//2������ʲô����
//3�����͵�����
//ͨ���س�����һ��QQ����
//#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <WinUser.h>
#include <stdlib.h>

#define  _CRT_SECURE_NO_WARNINGS

static int boom_count = 0;

BOOL SystemReboot()		//��Ȩ
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	/* OpenProcessToken() ��������������Ǵ�һ�����̵ķ�������
	GetCurrentProcess() �����������ǵõ������̵ľ��*/
	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return FALSE;
	// LookupPrivilegeValue() ���������޸Ľ��̵�Ȩ��
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,
		&tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1; // one privilege to set ������������Ȩ
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	// AdjustTokenPrivileges������������֪ͨWindows NT�޸ı����̵�Ȩ��
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
		(PTOKEN_PRIVILEGES)NULL, 0);
	if (GetLastError() != ERROR_SUCCESS) //ʧ��
		return FALSE;
	if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0)) //�������������á�ǿ���˳�WINDOWS��EWX_FORCE����
		return FALSE;
	return TRUE;
}


BOOL CALLBACK EnumWindowProc(HWND hwnd,LPARAM param)
{
	
	//�ж��Ƿ���QQ���촰�� ���� �ͷ���
	char strClassName[MAXBYTE] = { 0 };
	char strWindowsName[MAXBYTE] = { 0 };

	GetClassNameA(hwnd,strClassName,MAXBYTE);
	GetWindowTextA(hwnd, strWindowsName, MAXBYTE);


	//	MessageBoxA(nullptr, strWindowsName, "����QQ���촰��", MB_OK);

	if (0==strcmp("TXGuiFoundation",strClassName) )
	{
		if (0 == strcmp("*****", strWindowsName) ||
				0 == strcmp("1033800341", strWindowsName) ||
				0 == strcmp("**********", strWindowsName) ||
				0 == strcmp(" ����������������������", strWindowsName) 
			)
		{
			//	::PostMessageW(hwnd, WM_PASTE, 0, 0);
			//	::PostMessageW(hwnd, WM_KEYDOWN, VK_RETURN, 0);	//����	
			boom_count++;

			MessageBoxA(nullptr, "\
���󣬲��ܺ�ը���� \n\
���С��Ŷ������Һ�ը����\n\
��ĵ��Իᷢ��ʲô��\n\
�ҾͲ�֪����\n\
ǧ��Ҫ��ը����\n\
�ᱬը�� Boooooooooom\n\
 ","����", MB_OK);

			if (boom_count > 5)
			{
				MessageBoxA(nullptr, "\
˵�˲��ܺ�ը����\n\
��ƫҪ��ը\n\
�������ĺ�����û�ù��ӳԵ�\n\
���������ܳͷ���\n\
", "^-^^-^^-^", MB_OK);

	//			SystemReboot();		//����

			}
		}
		else
		{
			::SendMessage(hwnd, WM_PASTE, 0, 0);
			::SendMessage(hwnd, WM_KEYDOWN, VK_RETURN, 0);	//����
			//�رմ���
			//	::SendMessage(hwnd, WM_CLOSE, 0, 0);
		}
	}
		
	
	
	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	system("title QQ��Ϣ��ը��---һ�Բ��Ͼͺ�ը Beta�� ");
    int number=0,count=0;
	int passkey=0;
	
	//FindWindowA(���������ڱ���)
	//��QQ���ѶԻ��򣬲���ʾ
	HWND hwnd =:: FindWindow(L"TXGuiFoundation",L"QQ");
	ShowWindow(hwnd, SW_SHOW);
	system("Color  a");

	MessageBoxA(nullptr, "\
O(��_��)O������~\n\
�����ʲô��\n\
ǧ�������\n\
�������������\n\
�����Ҫ��Կ������������Ҫ\n\
", "��������", MB_OK);

	if (MessageBoxA(nullptr, "�Ƿ���������Ҫ��Կ", "��������", MB_YESNO) == IDYES)
	{
		system("start tencent://Message/?Uin=1033800341&webssiteName=www.oicqzone.com&Menu=yes");
		system("cls");

		printf("������Կ��");
		scanf_s("%d", &passkey);
		printf("\n���������ԿΪ��%d\n",passkey);
		if (234789==passkey)
		{
			MessageBoxA(nullptr, "��Կ��ȷ\n", "��ϲ��^-^", MB_OK);
		}
		else
		{
			MessageBoxA(nullptr, "��Կ�����ټ���\n", "/(��o��)/~~", MB_OK);
			return 0;
		}
		
		system("cls");
	}
	else
	{
		MessageBoxA(nullptr, "ByeBye^-^~~~~~~~\n", "", MB_OK);
		return 0;
	}
	
again:
	printf("����Ҫ��ը���ѵĸ�����%d\n", &number);
	printf("��ը�ĺ��ѻ���QQȺ����:");
	scanf_s("%d", &number);
	
	printf("ÿ�����ѻ���QQȺ��ը�Ĵ�����");
	scanf_s("%d",&count);

	printf("Ҫ��ը %d �����ѣ�ÿ�����Ѻ�ը %d ��\n", number, count);
	printf("ף����ÿ���^-^\n\n");

	//�ҵ�һ�����Ѻ󰴻س�
	//���¼� ���س�
	while (hwnd)
	{
		while (number--)
		{
		//	::SendMessage(hwnd, WM_KEYDOWN, VK_DOWN, 0);
			::SendMessage(hwnd, WM_KEYDOWN, VK_RETURN, 0);
			//����
			for (int i = 0; i < count;i++)
				EnumWindows(EnumWindowProc, NULL);
			::SendMessage(hwnd, WM_KEYDOWN, VK_DOWN, 0);
			
		}
		break;	
	}
		
	if (MessageBoxA(nullptr, "�Ƿ������ը", "Boooooooom", MB_YESNO) == IDYES)
	{
		MessageBoxA(nullptr, "ף����ÿ���������", "��������", MB_OK);
		system("cls");
		goto again;
	}
	else
	{
		MessageBoxA(nullptr, "лл�������飬����и��õĽ���\n\
���߱�����б��ͼ�����ϵ:\n\
						 						-----1033800341", "", MB_OK);

		if (MessageBoxA(nullptr, "�Ƿ���ϵ����", "��������", MB_YESNO) == IDYES)
		{
			system("start tencent://Message/?Uin=1033800341&websiteName=www.oicqzone.com&Menu=yes");
			system("cls");
		}
		else
			return 0;
	}
	
	
	system("pause");
	return 0;
}

