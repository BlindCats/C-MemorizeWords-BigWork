#ifndef _HEAD_
#define _HEAD_

#include "data.h"
#include "fun.h"
#include "menu.h"
#include "fun.c"

#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


void WelComeMenu()
{
	int selection;						//	选择选项
	while(1)
	{
        system("cls");
		puts("----------------------------------");
		puts("          欢迎首次使用             ");
		puts("----------------------------------");
		puts("       	 1.导入词库             ");
		puts("       	 0.退出                 ");
		puts("----------------------------------");
		puts("选择(0-1):");
		scanf("%d",&selection);
		getchar();
		switch(selection)
		{
			case 1:
				UpLoad();
				break;
			case 0: break;
		}
		if(selection == 0)
		{
			exit(0);
		}
	}
	return ;
}
/*
void RememberMenu(WORD words[],int cnt)
{
    system("cls");
    puts("----------------------------------");
	puts("          单词学习菜单             ");
	puts("----------------------------------");
	puts("         1.按单元学习              "); 
	puts("         2.顺序学习               ");
	puts("         3.乱序学习               ");
	puts("         0.退出                   ");
	puts("----------------------------------");
	puts("选择(0-3):");
    int selection = 0;
	scanf("%d",&selection);
	getchar();
	switch(selection)
	{
		case 1:	page404();
				break;
		case 2: page404();
				break;
		case 3: page404();
				break;
		case 0: break;
	}
}
*/
void TestMenu()
{
	system("cls");
    puts("----------------------------------");
	puts("            单词测试              ");
	puts("----------------------------------");
	int temp;
	puts("        请输入期望测试的单词数      ");
	scanf("%d",&temp);
	getchar();
	srand(time(0));
	int i, id, mode, ture_num = 0;	//	id,mode为传参参数,ture_num为回答正确次数
	for(i = 0; i < temp; i ++)
	{
		id = rand()%cnt + 1;		//	随机抽取的单词
		mode = rand()%2 + 1;		//	随机中文选择还是英文选择
		ture_num += WordTest_Choise(id,mode);
	}
	puts("----------------------------------");
	printf("共计进行%d次测试，正确%d道\n",temp,ture_num);
	printf("正确率：%.2f",(double)ture_num/temp*100);
	puts("%");
	puts("----------------------------------");
	puts("		 按任意键返回           ");
	getchar();
}

void ConditionSection(void)
{
	int condition = 0, i; 					//	记录筛选关键字数量
	BuiltLine(cnt);							//	建立链表
	for(i = 1; i <= cnt; i++)
	{
		SectionBook[i] = 0;					//	染色记录初始化
	}
    system("cls");
	int selction = 0,temp;					//	selction为模式选择，temp储存输入信息
    puts("----------------------------------");
	puts("           筛选条件                ");
    puts("----------------------------------");
	puts("  现支持按照年级、上下册、单元进行筛选 ");
	puts("         1.按照年级筛选           ");
	puts("         2.按照单元筛选           ");
	puts("         3.按照上下册筛选          ");
	puts("         0.返回                   ");
	puts("----------------------------------");
	puts("请输入(0-3):");
    while(1)
	{
		scanf("%d",&selction);
		switch (selction)
		{
			case 1:
				puts("----------------------------------");
	    		puts("         请输入查找的年级           ");
				puts("          （请输入数字）           ");
    			puts("----------------------------------");
				scanf("%d",&temp);
				condition ++;				//	记录筛选关键字+1
				ConditionSerch(temp,1);
				break;
			case 2:
				puts("----------------------------------");
	    		puts("         请输入查找的单元           ");
				puts("          （请输入数字）           ");
    			puts("----------------------------------");
				condition ++;				//	记录筛选关键字+1
				scanf("%d",&temp);
				ConditionSerch(temp,2);
				break;
			case 3:
				puts("----------------------------------");
	    		puts("         请输入查找的上下册         ");
				puts("   （上册输入数字1，下册输入数字2）  ");
    			puts("----------------------------------");
				scanf("%d",&temp);			//	记录筛选关键字+1
				ConditionSerch(temp,3);
				condition ++;
				break;
			case 6:
			//	printf("cod:%d\n",condition);
				for(i = 1; i <= cnt; i++)
				{
					if(SectionBook[i] == condition)
						PrintOne(words[i]);
				}
				puts("----------------------------------");
				puts("           按任意键返回            ");
				getchar();
				getchar();
				SearchMenu(words,cnt);
				break;
			case 0:
				break;		
		}
		puts("----------------------------------");
	    puts("您可继续选择筛选条件，或输入6查看筛选结果");
    	puts("----------------------------------");
        if(selction == 0)
			break;
	}
}

void page404()
{
	system("cls");
	puts("----------------------------------");
	puts("         当前功能还在施工中        ");
	puts("            敬请期待！！！          ");
	puts("                                  ");
	puts("         ---按任意键返回---        ");
    puts("----------------------------------");
	getchar();
	return ;
}

void DarkSearchMenu(WORD words[],int cnt)
{
	system("cls");
	puts("----------------------------------");
	puts("        请输入需要查找的单词        ");
	puts("            以回车结束             ");
	puts("      系统将为您检索可能的单词       ");
	puts("       					        ");
    puts("----------------------------------");
	puts("       您可输入0以返回上级菜单     ");
	puts("----------------------------------");
	char modestr[50],libstr[100000]={"0"};	// modestr为模式串，libstr为文本串
	int i;
	for(i = 1; i <= cnt; i ++)				//	处理文本串
	{
		strcat(libstr,words[i].en);
		strcat(libstr," ");
	}
	while(1)
	{
		scanf("%s",modestr+1);				//	输入模式串
		if(modestr[1] == '0')
			SearchMenu(words,cnt);
		DarkSerch(libstr,modestr);
		printf("您可继续输入，或输入0以退出：\n");
	}
	return;
}

void SearchMenu(WORD words[],int cnt)
{
    system("cls");
    int selection = 0;
    puts("----------------------------------");
	puts("           单词查询               ");
	puts("----------------------------------");
	puts("          1.英文精准查询           "); 
	puts("          2.中文精确查询            ");
	puts("          3.英文模糊查询            ");
	puts("          0.返回                   ");
	puts("----------------------------------");
	puts("选择(0-3):");
	while(1)
	{
		scanf("%d",&selection);
		switch (selection)
    	{
    		case 1:	PreciseSearchMenu_en();
        		break;
    		case 2: PreciseSearchMenu_cn();
        		break;
    		case 3: DarkSearchMenu(words,cnt);
        		break;
    		case 0:
        		break;
    	}
		if(selection == 0)
			MainMenu();
	}
	return ;
}

void PreciseSearchMenu_en(void)
{
	system("cls");
	puts("----------------------------------");
	puts("         请输入需要查找的单词       ");
	puts("            以回车结束             ");
	puts("          系统将为您检索           ");
    puts("----------------------------------");
	puts("         您可输入0以返回上级菜单     ");
	puts("----------------------------------");
	char temp[50];
	while(1)
	{
		scanf("%s",temp);
		if(temp[0] == '0')
			SearchMenu(words,cnt);
		if(temp[0] != ' ' && FindTrie(temp))
		{
			int id = FindWord(temp,'e');
			puts("----------------------------------");
			printf("%s %s.%s\n",words[id].en,words[id].spech,words[id].cn);
			puts("----------------------------------");
		}
		else printf("词库中未找到该单词\n");
		printf("您可继续输入，或输入0以退出：\n");
	}
}

void PreciseSearchMenu_cn(void)
{
	system("cls");
	puts("----------------------------------");
	puts("        请输入需要查找的中文       ");
	puts("            以回车结束             ");
	puts("          系统将为您检索          ");
    puts("----------------------------------");
	puts("         您可输入0以返回上级菜单     ");
	puts("----------------------------------");
	char temp[50];
	while(1)
	{
		scanf("%s",temp);
		if(temp[0] == '0')
			SearchMenu(words,cnt);
		int id = FindWord(temp,'c');
		if(id != -1)
		{
			puts("----------------------------------");
			printf("%s %s.%s\n",words[id].en,words[id].spech,words[id].cn);
			puts("----------------------------------");
		}
		else printf("词库中未找到该单词\n");
		printf("您可继续输入，或输入0以退出：\n");
	}
}

void WordlibMenu(void)
{
	while(1)
	{
		int selection = 0;
        system("cls");
		puts("----------------------------------");
		puts("            词库查看             ");
		puts("----------------------------------");
		puts("         1.查看所有单词            ");
		printf("           (共计%d个)\n",cnt);
		puts("         2.按条件筛选             ");
		puts("         0.退出                   ");
		puts("----------------------------------");
		puts("选择(0-2):");
		scanf("%d",&selection);
		getchar();
		switch(selection)
		{
			case 1: Sort(words,cnt);
					PrintAll(words,cnt);
					break;
			case 2: ConditionSection();
					break;
			case 0: break;
		}
		if(selection == 0)
		{
			break;
		}
	}
}

void MainMenu(void)
{
	while(1)
	{
		int selection = 0;
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
		if(selection == 0)
		{
			exit(0);
		}
	}
}

void Login()
{
	puts("----------------------------------");
	puts("            欢迎使用              ");
	puts("----------------------------------");
}