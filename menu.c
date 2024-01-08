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
	int selection;						//	ѡ��ѡ��
	while(1)
	{
        system("cls");
		puts("----------------------------------");
		puts("          ��ӭ�״�ʹ��             ");
		puts("----------------------------------");
		puts("       	 1.����ʿ�             ");
		puts("       	 0.�˳�                 ");
		puts("----------------------------------");
		puts("ѡ��(0-1):");
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
	puts("          ����ѧϰ�˵�             ");
	puts("----------------------------------");
	puts("         1.����Ԫѧϰ              "); 
	puts("         2.˳��ѧϰ               ");
	puts("         3.����ѧϰ               ");
	puts("         0.�˳�                   ");
	puts("----------------------------------");
	puts("ѡ��(0-3):");
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
	puts("            ���ʲ���              ");
	puts("----------------------------------");
	int temp;
	puts("        �������������Եĵ�����      ");
	scanf("%d",&temp);
	getchar();
	srand(time(0));
	int i, id, mode, ture_num = 0;	//	id,modeΪ���β���,ture_numΪ�ش���ȷ����
	for(i = 0; i < temp; i ++)
	{
		id = rand()%cnt + 1;		//	�����ȡ�ĵ���
		mode = rand()%2 + 1;		//	�������ѡ����Ӣ��ѡ��
		ture_num += WordTest_Choise(id,mode);
	}
	puts("----------------------------------");
	printf("���ƽ���%d�β��ԣ���ȷ%d��\n",temp,ture_num);
	printf("��ȷ�ʣ�%.2f",(double)ture_num/temp*100);
	puts("%");
	puts("----------------------------------");
	puts("		 �����������           ");
	getchar();
}

void ConditionSection(void)
{
	int condition = 0, i; 					//	��¼ɸѡ�ؼ�������
	BuiltLine(cnt);							//	��������
	for(i = 1; i <= cnt; i++)
	{
		SectionBook[i] = 0;					//	Ⱦɫ��¼��ʼ��
	}
    system("cls");
	int selction = 0,temp;					//	selctionΪģʽѡ��temp����������Ϣ
    puts("----------------------------------");
	puts("           ɸѡ����                ");
    puts("----------------------------------");
	puts("  ��֧�ְ����꼶�����²ᡢ��Ԫ����ɸѡ ");
	puts("         1.�����꼶ɸѡ           ");
	puts("         2.���յ�Ԫɸѡ           ");
	puts("         3.�������²�ɸѡ          ");
	puts("         0.����                   ");
	puts("----------------------------------");
	puts("������(0-3):");
    while(1)
	{
		scanf("%d",&selction);
		switch (selction)
		{
			case 1:
				puts("----------------------------------");
	    		puts("         ��������ҵ��꼶           ");
				puts("          �����������֣�           ");
    			puts("----------------------------------");
				scanf("%d",&temp);
				condition ++;				//	��¼ɸѡ�ؼ���+1
				ConditionSerch(temp,1);
				break;
			case 2:
				puts("----------------------------------");
	    		puts("         ��������ҵĵ�Ԫ           ");
				puts("          �����������֣�           ");
    			puts("----------------------------------");
				condition ++;				//	��¼ɸѡ�ؼ���+1
				scanf("%d",&temp);
				ConditionSerch(temp,2);
				break;
			case 3:
				puts("----------------------------------");
	    		puts("         ��������ҵ����²�         ");
				puts("   ���ϲ���������1���²���������2��  ");
    			puts("----------------------------------");
				scanf("%d",&temp);			//	��¼ɸѡ�ؼ���+1
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
				puts("           �����������            ");
				getchar();
				getchar();
				SearchMenu(words,cnt);
				break;
			case 0:
				break;		
		}
		puts("----------------------------------");
	    puts("���ɼ���ѡ��ɸѡ������������6�鿴ɸѡ���");
    	puts("----------------------------------");
        if(selction == 0)
			break;
	}
}

void page404()
{
	system("cls");
	puts("----------------------------------");
	puts("         ��ǰ���ܻ���ʩ����        ");
	puts("            �����ڴ�������          ");
	puts("                                  ");
	puts("         ---�����������---        ");
    puts("----------------------------------");
	getchar();
	return ;
}

void DarkSearchMenu(WORD words[],int cnt)
{
	system("cls");
	puts("----------------------------------");
	puts("        ��������Ҫ���ҵĵ���        ");
	puts("            �Իس�����             ");
	puts("      ϵͳ��Ϊ���������ܵĵ���       ");
	puts("       					        ");
    puts("----------------------------------");
	puts("       ��������0�Է����ϼ��˵�     ");
	puts("----------------------------------");
	char modestr[50],libstr[100000]={"0"};	// modestrΪģʽ����libstrΪ�ı���
	int i;
	for(i = 1; i <= cnt; i ++)				//	�����ı���
	{
		strcat(libstr,words[i].en);
		strcat(libstr," ");
	}
	while(1)
	{
		scanf("%s",modestr+1);				//	����ģʽ��
		if(modestr[1] == '0')
			SearchMenu(words,cnt);
		DarkSerch(libstr,modestr);
		printf("���ɼ������룬������0���˳���\n");
	}
	return;
}

void SearchMenu(WORD words[],int cnt)
{
    system("cls");
    int selection = 0;
    puts("----------------------------------");
	puts("           ���ʲ�ѯ               ");
	puts("----------------------------------");
	puts("          1.Ӣ�ľ�׼��ѯ           "); 
	puts("          2.���ľ�ȷ��ѯ            ");
	puts("          3.Ӣ��ģ����ѯ            ");
	puts("          0.����                   ");
	puts("----------------------------------");
	puts("ѡ��(0-3):");
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
	puts("         ��������Ҫ���ҵĵ���       ");
	puts("            �Իس�����             ");
	puts("          ϵͳ��Ϊ������           ");
    puts("----------------------------------");
	puts("         ��������0�Է����ϼ��˵�     ");
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
		else printf("�ʿ���δ�ҵ��õ���\n");
		printf("���ɼ������룬������0���˳���\n");
	}
}

void PreciseSearchMenu_cn(void)
{
	system("cls");
	puts("----------------------------------");
	puts("        ��������Ҫ���ҵ�����       ");
	puts("            �Իس�����             ");
	puts("          ϵͳ��Ϊ������          ");
    puts("----------------------------------");
	puts("         ��������0�Է����ϼ��˵�     ");
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
		else printf("�ʿ���δ�ҵ��õ���\n");
		printf("���ɼ������룬������0���˳���\n");
	}
}

void WordlibMenu(void)
{
	while(1)
	{
		int selection = 0;
        system("cls");
		puts("----------------------------------");
		puts("            �ʿ�鿴             ");
		puts("----------------------------------");
		puts("         1.�鿴���е���            ");
		printf("           (����%d��)\n",cnt);
		puts("         2.������ɸѡ             ");
		puts("         0.�˳�                   ");
		puts("----------------------------------");
		puts("ѡ��(0-2):");
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
		if(selection == 0)
		{
			exit(0);
		}
	}
}

void Login()
{
	puts("----------------------------------");
	puts("            ��ӭʹ��              ");
	puts("----------------------------------");
}