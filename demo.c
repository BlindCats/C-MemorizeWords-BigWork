#ifndef _HEAD_
#define _HEAD_

#include "data.h"
#include "menu.h"
#include "fun.h"
#include "menu.c"
#include "fun.c"

#endif

#include <stdio.h>
/* !!!特别注意：请统一选择GBK中文编码格式 */

int main()
{
	FILE* fp;
	fp = fopen("Wordslist.in","r");
	int book = 1;						//	标记是否已经导入词库
	int selection = 0;					//	菜单选择选项
	if(fp == NULL)						//	第一次打开程序
	{	
	//	fclose(fp);
		WelComeMenu();					//	首次登录页
		book = 0;						//	标记已经导入词库
	}
	fclose(fp);
	while(1)
	{
		if(book)							//	若已导入词库，则从in文件导入结构体
		cnt = ReadFromIn("Wordslist.in");	//	cnt为全局变量，为单词的总数
        system("cls");
		puts("----------------------------------");
		puts("           背单词主菜单            ");
		puts("----------------------------------");
		puts("           1.显示词库              ");
		puts("           2.单词搜索              ");
		puts("           3.背单词                ");
		puts("           4.单词测试              ");
		puts("           0.退出                  ");
		puts("----------------------------------");
		puts("选择(0-4):");
		scanf("%d",&selection);
		getchar();
		switch(selection)
		{
			//	显示词库
			case 1: WordlibMenu();
					break;
			//	单词搜索
			case 2: SearchMenu(words,cnt);
					break;
			//	背单词		
			case 3: page404();
					break;
			//	单词测试
		    case 4: TestMenu();
		    		break;
			case 0: break;
		}
		if(selection == 0)				//	退出菜单
		{
			break;
		}
	}
    return 0;
}