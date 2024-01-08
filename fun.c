/**********************
*  作者：BlindCats     *
*  文件名：fun.c       *
*  说明：调用的函数库   *
*  日期：2023-12-23    *
***********************/

#ifndef _HEAD_
#define _HEAD_
#include "data.h"
#include "fun.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>

int all;
int Unknownwords;

int TranStrtoInt(char str[])
{
    int len = strlen(str), sum = 0, i;
    for(i = 0; i < len; i ++)
    {
        sum = sum*10 + str[i]-'0';
    }
    return sum;
}

int ReadFromIn(char filename[],WORD words[])
{
#ifdef _TEST_
    printf("to:ReadFromIN\n");
    getchar();
#endif
    int i = 1;
    FILE* fp;
    fp = fopen(filename,"r");
    triecnt = 0;
    while(!feof(fp))
    {
        //great 非常好 adj 10 7 A
        char temp[10];
        //  读取英文
        fscanf(fp,"%s",words[i].en);
        //  读取中文
        fscanf(fp," %s",words[i].cn);
        //  读取词性
        fscanf(fp," %s",words[i].spech);
        //  读取单元
        fscanf(fp," %s",temp);
        words[i].unit = TranStrtoInt(temp);
        //  读取年级
        fscanf(fp," %s ",temp);
        words[i].grade = TranStrtoInt(temp);
        //  读取上下册
        words[i].part = fgetc(fp);
        //  建字典树
        InsertTrie(words[i].en);
        i ++;
    }
    fclose(fp);
    return i-2;
}

int ReadFromfile(char filename[])
{
#ifdef _TEST_
    printf("to:ReadFromfile\n");
    getchar();
#endif
    setlocale(LC_ALL, "zh_CN.gb2312");          //  转化为GB2312编码
    int id = 1;                                 //  id用于统计读入单词个数
    FILE* fp1;                                  //  fp1为读入指针
    FILE* fp2;                                  //  fp2为写入指针
    fp1 = fopen(filename,"r");                  //  从filename.txt中读入
    fp2 = fopen("Wordslist.in","w");            //  改变格式后保存到Wordslist.in
    if(fp1 == NULL) 
    {
        fclose(fp1);
        fclose(fp2);
        return 0;
    }
    triecnt = 0;                               //   字典树节点总数
    while(!feof(fp1))
    {
        //  读入英文
        fscanf(fp1,"%s",words[id].en);
        //  读入词性与中文
        char temp[MAX_LEN];                     // 临时存储字符串
        char *ptp, *pwd;                        // ptp:pointtemp pwd:pointWORD
        fscanf(fp1," %s",temp);
        //  分离词性
        ptp = temp; pwd = words[id].spech;      // ptp指向temp pwd指向WORD
        while(*ptp != '.')
        {
            *pwd = *ptp;
            pwd ++; ptp ++;
        } 
        *pwd = '\0'; ++ptp;
        //  分离中文
        pwd = words[id].cn;                     // pwd指向WORD中文
        while(*ptp)
        {
            *pwd = *ptp;
            pwd ++; ptp ++;
        } *pwd = '\0';
        //  读入单元信息:UnitXX
        int len,num;                            // len记录字符串长度，num为转化的int
        fscanf(fp1," %s",temp);
        len = strlen(temp);
        num = 0;                                // num为字符串转化后的unit整型
        ptp = temp + 4;                         // ptp指向unit后数字的第一位
        while(*ptp)
        {
            num = num*10 + (*ptp - '0');
            ptp ++;
        }
        words[id].unit = num;
        //  读取年级信息:xxX(12B)
        fscanf(fp1," %s",temp);
        ptp = temp;
        len = strlen(temp);
        words[id].part = temp[len-1];           // part恒为一位，直接取temp最后一位
        temp[len-1] = '\0';
        num = 0;                                // num为字符串转化后的grade整型
        while(*ptp)
        {
            
            num = num*10 + (*ptp - '0');
            ptp ++;
        }
        words[id].grade = num;
        // 写入操作，写入到Wordslist.in，用于二次打开
        fputs(words[id].en,fp2);
        fputs(" ",fp2);
        fputs(words[id].cn,fp2);
        fputs(" ",fp2);
        fputs(words[id].spech,fp2);
        fputs(" ",fp2);
        fprintf(fp2,"%d",words[id].unit);
        fputs(" ",fp2);
        fprintf(fp2,"%d",words[id].grade);
        fputs(" ",fp2);
        fprintf(fp2,"%c",words[id].part);
        fputs("\n",fp2);
        //  建字典树
        InsertTrie(words[id].en);
        id ++;
    }
    fclose(fp1);
    fclose(fp2);
    return id-1;
}

void PrintOne(WORD word)
{
    printf("%s ",word.en);
    printf("%s.",word.spech);
    printf("%s ",word.cn);
    printf("unit%d:",word.unit);
    printf(" %d%c\n",word.grade,word.part);
}

void PrintAll(WORD words[],int cnt)
{
    system("cls");
    puts("----------------------------------");
    int i;
    for(i = 1; i <= cnt; i ++)
        PrintOne(words[i]);
    puts("----------------------------------");
    printf("已全部加载，按任意键返回...");
    getchar();
}

void UpLoad(void)
{
    system("cls");
    puts("----------------------------------");
    puts("            词库导入               ");
    puts("----------------------------------");
    puts("请输入词库文件名：");
    char filename[20];                                      //  存入输入文件名
    gets(filename);
    int len = strlen(filename);
    if(len <= 4 || strcmp(filename+(len-4),".txt") != 0)    //  输入文件名没有.txt
        strcat(filename,".txt");
    cnt = ReadFromfile(filename);                           //  cnt为总单词数
//    getchar();
    if(!cnt)
    {
        puts("----------------------------------");
        puts("           ！导入失败！            ");
        puts("  请检查文件是否为空或文件名是否正确 ");
        puts("        按任意键返回...            ");
        puts("----------------------------------");
        getchar();
        WelComeMenu();
    }
    else
    {
//        FILE* fp;                                           
//        fp = fopen("infomation.in","w");
//        fprintf(fp,"%d",cnt);
//        fclose(fp);
        puts("----------------------------------");
        printf("读入成功，共读入%d个单词。\n",cnt);
    }
    puts("按任意键继续...");
    getchar();
    MainMenu();
}

void Sort(WORD words[],int cnt)
{
    system("cls");
    int n = cnt;                        //  单词总数
    WORD temp;                          
    int i,j;
	for(i = 1; i <= n-1; i ++)          //  冒泡排序
	{
		for(j = 1; j <= n-1-i; j ++)
		{
			if(strcmp(words[j].en,words[j+1].en)>0)
			{
				temp = words[j];
				words[j] = words[j+1];
				words[j+1] = temp;
			}	
		}
	}
	return;
}

void DarkSerch(char libstr[],char modstr[])
{
#ifdef _TEST_
    printf("to:DarkSerch\n");
    getchar();
#endif
//    scanf("%s",modstr+1);
//    printf("%s",modstr+1);
    system("cls");
    printf("待检索的单词：%s\n",modstr+1);
    puts("检索中...");
    int liblen = strlen(libstr+1);
	int modlen = strlen(modstr+1);
	if(liblen < modlen){
		printf("未找到，按任意键返回。\n");
        getchar();
        return;
	}
    int i, D = 233,k;                               //  k为失配次数
    if(modlen == 1) k = 0;                          //  不同单词长度所允许的失配次数
    else if(modlen <= 4) k = 1;
    else if(modlen <= 10) k = 2;    
	pre[0]=1;                                       //  初始化
	for(i = 1; i < liblen; ++i)
        pre[i] = pre[i-1]*D;                        //  预处理
	for(i = 1; i < liblen; ++i)
        libhash[i] = libhash[i-1]*D + libstr[i];    //  hash计算
	for(i = 1;i <= modlen; ++i)
        modhash[i] = modhash[i-1]*D + modstr[i];    //  hash计算
    int num = 0,id;                                 //  统计匹配结果数
    char temp[50];                                  //  临时变量
	for(i = 1; i+modlen-1 < liblen; i++)            //  枚举待匹配字符串
    {
		if(darkcheck(i,modlen,k))
        {
            int j, z = 0;                           //  枚举变量
            for(j = i; j <= i+modlen-1; j ++)
            {
                if(libstr[j] != ' ')                //  处理掉kmp加入的空格
                {
                    temp[z++] = libstr[j];
                }
            }
            temp[z] = '\0';
            if(FindTrie(temp))                      //  存在该单词
            {
                num ++;
                id = FindWord(temp,'e');
                if(id == -1)
                {
                    num = 0;
                    break;
                }
                printf("您可能寻找的是：\n");
                printf("%s %s.%s\n",words[id].en,words[id].spech,words[id].cn);
            }
        }
    }
    if(num == 0)
        printf("未找到该单词\n");
    getchar();
    return;
}

int darkcheck(int x,int len,int misserror)
{
#ifdef _TEST_
    printf("to:darkcheck\n");
    getchar();
#endif
    int S_H = 1;                        //  S的头
    int i;
    for(i = 0; i < misserror; i ++)     //  至多允许misserro次失配
    {
        int cmplen = lcp(x,S_H,len-S_H+1);   //返回查询匹配的长度
        x += cmplen + 1;                //  跳过该失配位置
        S_H += cmplen + 1;
        if(S_H > len)
            return 1;                   //  匹配成功
    }
    int r = x+len-1;
    //判断是否完全相同
    return askhash(libhash,x,r) == askhash(modhash,1,len);
}

int lcp(int S0_H, int S1_H, int rigt)
{
#ifdef _TEST_
    printf("to:lcp\n");
    getchar();
#endif
    int left = 1, mid;                  //  左端点与中点
    int cmplen = 0;                     //  匹配长度
    while(left <= rigt)                 //  二分查找
    {
        mid = (left + rigt) >> 1;
        if(askhash(libhash,S0_H,S0_H+mid-1) == askhash(modhash,S1_H,S1_H+mid-1))
        {
            //  上一段能匹配上
            cmplen = mid;
            left = mid+1;
        }
        else rigt = mid - 1;
    }
    return cmplen;
}

int askhash(int hash[],int left,int rigt)
{
    return hash[rigt]-hash[left-1]*pre[rigt-left+1];
}

void InsertTrie(char word[])
{
#ifdef _TEST_
    printf("to:InsertTrie\n");
    getchar();
#endif
    int i, nowpoint = 0;                //  nowpoint节点标记
    int len = strlen(word);
    for(i = 0; i < len; i ++)
    {
        word[i] = tolower(word[i]);
        int next = word[i] - 'a';
        if(!trie[nowpoint][next])       //  建立新子节点
            trie[nowpoint][next] = ++triecnt;
        nowpoint = trie[nowpoint][next];
    }
    trieexist[nowpoint] = 1;            //  节点结束标记
    return ;
}

int FindTrie(char word[])
{
#ifdef _TEST_
    printf("to:FindTrie\n");
    getchar();
#endif
    int nowpoint = 0, next, i;          //  nowpoint为当前节点,next下一个节点
    int len = strlen(word);
    for(i = 0; i < len; i ++)
    {
        word[i] = tolower(word[i]);
        next = word[i] - 'a';
//       printf("now:%d next:%d\n",nowpoint,next);
//        getchar();
        if(!trie[nowpoint][next])
            return 0;
        nowpoint = trie[nowpoint][next];
    }
    return trieexist[nowpoint];
}

int FindWord(char str[],char mode)
{
#ifdef _TEST_
    printf("to:FindWord\n");
    getchar();
#endif
    int i;
    if(mode == 'e')                 //  查询英文
    {
        for(i = 1; i <= cnt; i ++)
        {   if(!strcmp(words[i].en,str))
                return i;
        }
    }
    else
    {                               //  查询中文
        for(i = 1; i <= cnt; i ++)
        {   
            if(!strcmp(words[i].cn,str))
                return i;
        }
    }
    return -1;
}

void BuiltLine(int cnt)
{
    int id;                         //  循环变量  
    for(id = 1; id <= cnt; id++)    //  初始化
    {
        GrdHead[id] = 0;
        UniHead[id] = 0;
        ParHead[id] = 0;
    }
    for(id = 1; id <= cnt; id ++)
    {
        int unit = words[id].unit;
        int grade = words[id].grade;
        int part = words[id].part - 'A' + 1;
        //  unit建链
        if(!UniHead[unit])
        {
            UniHead[unit] = id;
            words[id].nexlis.uninext = id;
        }
        else
        {
            words[id].nexlis.uninext = UniHead[unit];
            UniHead[unit] = id;
        }
        //  grade建链
        if(!GrdHead[grade])
        {
            GrdHead[grade] = id;
            words[id].nexlis.grdnext = id;
        }
        else
        {
            words[id].nexlis.grdnext = GrdHead[grade];
            GrdHead[grade] = id;
        }
        //  part建链
        if(!ParHead[part])
        {
            ParHead[part] = id;
            words[id].nexlis.parnext = id;
        }
        else
        {
            words[id].nexlis.parnext = ParHead[part];
            ParHead[part] = id;
        }
    }
}

void ConditionSerch(int condition,int mode)
{
    int id,nex;             //  id为链表块id，nex为当前指向的下一个链表块
    if(mode == 1)                   //  年级
    {
        id = GrdHead[condition];
        if(id == 0) return;
        while(words[id].nexlis.grdnext != id)
        {
            id = words[id].nexlis.grdnext;
            SectionBook[id] ++;     //  染色标记
        }
    }
    else if(mode == 2)              //  单元
    {
        id = UniHead[condition];
        if(id == 0) return;
        while(words[id].nexlis.uninext != id)
        {
            id = words[id].nexlis.uninext;
            SectionBook[id] ++;     //  染色标记
        }
    }
    else if(mode == 3)              //  上下册
    {
        id = ParHead[condition];
        if(id == 0) return;
        while(words[id].nexlis.parnext != id)
        {
            id = words[id].nexlis.uninext;
            SectionBook[id] ++;     //  染色标记
        }
    }
}

int WordTest_Choise(int id,int mode)
{
    system("cls");
    int set[4]={0,0,0,0};           //  set为四个选项对应的id值,
    int ans, i;                     //  ans为正确选项的位置
    srand(time(0));                 //  初始化随机数种子
    ans = rand()%4;                 //  正确答案所在的选项
    set[ans] = id;
    while(1)                        //  生成随机选项
    {
        for(i = 0; i < 4; i ++)
        {
            if(i == ans)
                continue;
            set[i] = rand()%cnt + 1;
        }
        if(set[0]!=set[1]&&set[1]!=set[2]&&set[2]!=set[3])
            break;
    }
    //  选择中文
    int choise;                     //  用户选项
    if(mode == 1)
    {
        puts("----------------------------------");
    	puts("  根据给出的英文选择出正确中文的选项 ");
    	puts("----------------------------------");
        printf("英文：%s 请选择：\n",words[id].en);
        printf("   1.%s\n",words[set[0]].cn);
        printf("   2.%s\n",words[set[1]].cn);
        printf("   3.%s\n",words[set[2]].cn);
        printf("   4.%s\n",words[set[3]].cn);
        scanf("%d",&choise);
        if(choise-1 == ans)
        {
            printf("  天才！正确！\n");
            getchar();
            puts("按任意键继续...");
            getchar();
            return 1;
        }else{
            printf("  笨蛋！错啦！正确答案是：%d.%s\n",ans+1,words[set[ans]].cn);
            getchar();
            puts("按任意键继续...");
            getchar();
            return 0;
        }
    }
    //  选择英文
    else
    {
        puts("----------------------------------");
    	puts("  根据给出的中文选择出正确中文的选项 ");
    	puts("----------------------------------");
        printf("中文：%s 请选择：\n",words[id].cn);
        printf("   1.%s\n",words[set[0]].en);
        printf("   2.%s\n",words[set[1]].en);
        printf("   3.%s\n",words[set[2]].en);
        printf("   4.%s\n",words[set[3]].en);
        scanf("%d",&choise);
        if(choise-1 == ans)
        {
            printf("  天才！正确！\n");
            getchar();
            puts("按任意键继续...");
            getchar();
            return 1;
        }else{
            printf("  错啦，正确答案是%d.%s\n",ans+1,words[set[ans]].en);
            getchar();
            puts("按任意键继续...");
            getchar();
            return 0;
        }
    }
}



// 将memory函数中的0123四个选项顺序打乱 
void r(char *x[], int n) {
    if (n > 1) {
        int i;
        for (i = n - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            char *y = x[j];
            x[j] = x[i];
            x[i] = y;
        }
    }
}
//随机生成四个选项，选择正确选项 
void memory(char filename[],WORD word[],int cnt)
{
	WORD raw[2000];
	int id = ReadFromIn(filename,raw);
	srand(time(0));
	int x,y,z,i,j,choose;
	for(i=0;i<cnt;i++)
	{
	x=rand()%cnt;
	y=rand()%cnt;
	z=rand()%cnt;
	char *option[4];
        option[0] = word[x].cn;
        option[1] = word[y].cn;
        option[2] = word[z].cn;
        option[3] = raw[i].cn;
	int n=sizeof(option)/sizeof(option[0]);
	r(option,n);
	printf("请选出正确的意思:%s \n",raw[i].en);
	for(j=0;j<n;j++)
	{
	printf("%d.%s ", j,option[j]);
	if(strcmp(option[j],raw[i].cn)==0)
	x=j;
	}
	scanf("%d",&choose);
	if(choose==x)
	printf("true\n");
	else
	printf("wrong, answer is %s",raw[i].cn);
	printf("\n");
	
	}
}
//依次默写单词，直至每个单词都默写正确 
void text(char filename[],char filename1[])
{
	WORD wrong[2000];
	FILE *fp;
	FILE *fp1;
	int i,j,line=1;
	char answer[50],filechar[40],str[50];
	int id=ReadFromIn(filename,wrong);
	for(j=0;;j++)
	{
		if(id==0)
		break;
		for(i=0;i<id;i++)
		{
		printf("%s,请写出英文:",wrong[i].cn);
		scanf("%s",answer);
		if(strcmp(answer,wrong[i].en)==0)//如果正确，除去第一行，存入另一文件 
		{
		printf("true");
		fp = fopen(filename,"r");
    fp1 = fopen(filename1,"w");
    while(fgets(filechar,40,fp) != NULL)
    {
    	if(line !=1)
    	fputs(filechar,fp1);
	line++;
	}
	fclose(fp);
	fclose(fp1);
}
	else
	{
		fp = fopen(filename,"r");
    fp1 = fopen(filename1,"w"); 
    while(fgets(filechar,40,fp) != NULL)//除去第一行，存入另一文件，并且第一行存入另一文件的最后 
    {
    	if(line !=1)
    	fputs(filechar,fp1);
	line++;
	}
	fprintf(fp,"%s %s.%s Unit%d %d%c",wrong[i].en,wrong[i].spech,wrong[i].cn,wrong[i].unit,wrong[i].grade,wrong[i].part);
	fclose(fp);
	fclose(fp1);
	}
	}
	text(filename1,filename);//左右文件依次交换，直到所有单词都默写正确 
}
}

void select()
{
    int i=1;
    int t=0;
    int k=1;
    while(k)
    {
        printf("%s",words[i].en);
        printf("这个单词的中文您知道吗？\n知道请按0，不知道请按1。");
        scanf("%d",&t);
        while(t)
        {
            FILE *fp;
            fp=fopen("raw.txt","a");
            fprintf(fp,"%s %s %s %d %d %s",words[i].en,words[i].cn,words[i].spech,words[i].unit,words[i].grade,words[i].part);
            fclose(fp);
            t=0;
        }
        if(i<all) i++;
        printf("请问您需要继续测试单词吗？\n继续请按1，结束请按0。");
        scanf("%d",&k);
    }
}

void readUnknown(WORD wordss[])
{
    int i=0;
    FILE *fp;
    fp=fopen("wordlist.in","r");
    while(!feof(fp))
    {
        fscanf(fp,"%s %s %s %d %d %s",&wordss[i].en,&wordss[i].cn,&wordss[i].spech,&wordss[i].unit,&wordss[i].grade,&wordss[i].part);
        i++;
    }
    Unknownwords=i;
    fclose(fp);
}

void select1()
{
    int i=0;
    int t=0;
    int k=1;
    WORD wordss[2000];
    char filename[50]="raw.txt";
    readUnknown(wordss);
    while(k)
    {
        printf("%s",wordss[i].cn);
        printf("这个单词的英文您知道吗？\n知道请按0，不知道请按1。");
        scanf("%d",&t);
        while(t)
        {
            FILE *fp;
            fp=fopen(filename,"a");
            for(i=0;i<Unknownwords;i++)
            {
                if(!strcmp(words[i].en,wordss[i].en))
                    printf("生词本中已有此单词。");
                else
                    fprintf(fp,"%s %s %s %d %d %s",words[i].en,words[i].cn,words[i].spech,words[i].unit,words[i].grade,words[i].part);
               }
            fclose(fp);
            t=0;
        }
        if(i<all) i++;
        printf("请问您需要继续测试单词吗？\n继续请按1，结束请按0。");
        scanf("%d",&k);
    }
}
