#ifndef _HEAD_
#define _HEAD_

#include "data.h"
#include "menu.h"
#include "fun.h"
#include "menu.c"
#include "fun.c"

#endif

#include <stdio.h>
/* !!!�ر�ע�⣺��ͳһѡ��GBK���ı����ʽ */

int main()
{
	FILE* fp;
	fp = fopen("Wordslist.in","r");
	int book = 1;						//	����Ƿ��Ѿ�����ʿ�
	int selection = 0;					//	�˵�ѡ��ѡ��
	if(fp == NULL)						//	��һ�δ򿪳���
	{	
	//	fclose(fp);
		WelComeMenu();					//	�״ε�¼ҳ
		book = 0;						//	����Ѿ�����ʿ�
	}
	fclose(fp);
	while(1)
	{
		if(book)							//	���ѵ���ʿ⣬���in�ļ�����ṹ��
		cnt = ReadFromIn("Wordslist.in");	//	cntΪȫ�ֱ�����Ϊ���ʵ�����
        system("cls");
		puts("----------------------------------");
		puts("           ���������˵�            ");
		puts("----------------------------------");
		puts("           1.��ʾ�ʿ�              ");
		puts("           2.��������              ");
		puts("           3.������                ");
		puts("           4.���ʲ���              ");
		puts("           0.�˳�                  ");
		puts("----------------------------------");
		puts("ѡ��(0-4):");
		scanf("%d",&selection);
		getchar();
		switch(selection)
		{
			//	��ʾ�ʿ�
			case 1: WordlibMenu();
					break;
			//	��������
			case 2: SearchMenu(words,cnt);
					break;
			//	������		
			case 3: page404();
					break;
			//	���ʲ���
		    case 4: TestMenu();
		    		break;
			case 0: break;
		}
		if(selection == 0)				//	�˳��˵�
		{
			break;
		}
	}
    return 0;
}