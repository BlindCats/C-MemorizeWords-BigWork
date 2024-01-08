/**********************
*  ���ߣ�BlindCats     *
*  �ļ�����fun.c       *
*  ˵�������õĺ�����   *
*  ���ڣ�2023-12-23    *
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
        //great �ǳ��� adj 10 7 A
        char temp[10];
        //  ��ȡӢ��
        fscanf(fp,"%s",words[i].en);
        //  ��ȡ����
        fscanf(fp," %s",words[i].cn);
        //  ��ȡ����
        fscanf(fp," %s",words[i].spech);
        //  ��ȡ��Ԫ
        fscanf(fp," %s",temp);
        words[i].unit = TranStrtoInt(temp);
        //  ��ȡ�꼶
        fscanf(fp," %s ",temp);
        words[i].grade = TranStrtoInt(temp);
        //  ��ȡ���²�
        words[i].part = fgetc(fp);
        //  ���ֵ���
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
    setlocale(LC_ALL, "zh_CN.gb2312");          //  ת��ΪGB2312����
    int id = 1;                                 //  id����ͳ�ƶ��뵥�ʸ���
    FILE* fp1;                                  //  fp1Ϊ����ָ��
    FILE* fp2;                                  //  fp2Ϊд��ָ��
    fp1 = fopen(filename,"r");                  //  ��filename.txt�ж���
    fp2 = fopen("Wordslist.in","w");            //  �ı��ʽ�󱣴浽Wordslist.in
    if(fp1 == NULL) 
    {
        fclose(fp1);
        fclose(fp2);
        return 0;
    }
    triecnt = 0;                               //   �ֵ����ڵ�����
    while(!feof(fp1))
    {
        //  ����Ӣ��
        fscanf(fp1,"%s",words[id].en);
        //  �������������
        char temp[MAX_LEN];                     // ��ʱ�洢�ַ���
        char *ptp, *pwd;                        // ptp:pointtemp pwd:pointWORD
        fscanf(fp1," %s",temp);
        //  �������
        ptp = temp; pwd = words[id].spech;      // ptpָ��temp pwdָ��WORD
        while(*ptp != '.')
        {
            *pwd = *ptp;
            pwd ++; ptp ++;
        } 
        *pwd = '\0'; ++ptp;
        //  ��������
        pwd = words[id].cn;                     // pwdָ��WORD����
        while(*ptp)
        {
            *pwd = *ptp;
            pwd ++; ptp ++;
        } *pwd = '\0';
        //  ���뵥Ԫ��Ϣ:UnitXX
        int len,num;                            // len��¼�ַ������ȣ�numΪת����int
        fscanf(fp1," %s",temp);
        len = strlen(temp);
        num = 0;                                // numΪ�ַ���ת�����unit����
        ptp = temp + 4;                         // ptpָ��unit�����ֵĵ�һλ
        while(*ptp)
        {
            num = num*10 + (*ptp - '0');
            ptp ++;
        }
        words[id].unit = num;
        //  ��ȡ�꼶��Ϣ:xxX(12B)
        fscanf(fp1," %s",temp);
        ptp = temp;
        len = strlen(temp);
        words[id].part = temp[len-1];           // part��Ϊһλ��ֱ��ȡtemp���һλ
        temp[len-1] = '\0';
        num = 0;                                // numΪ�ַ���ת�����grade����
        while(*ptp)
        {
            
            num = num*10 + (*ptp - '0');
            ptp ++;
        }
        words[id].grade = num;
        // д�������д�뵽Wordslist.in�����ڶ��δ�
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
        //  ���ֵ���
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
    printf("��ȫ�����أ������������...");
    getchar();
}

void UpLoad(void)
{
    system("cls");
    puts("----------------------------------");
    puts("            �ʿ⵼��               ");
    puts("----------------------------------");
    puts("������ʿ��ļ�����");
    char filename[20];                                      //  ���������ļ���
    gets(filename);
    int len = strlen(filename);
    if(len <= 4 || strcmp(filename+(len-4),".txt") != 0)    //  �����ļ���û��.txt
        strcat(filename,".txt");
    cnt = ReadFromfile(filename);                           //  cntΪ�ܵ�����
//    getchar();
    if(!cnt)
    {
        puts("----------------------------------");
        puts("           ������ʧ�ܣ�            ");
        puts("  �����ļ��Ƿ�Ϊ�ջ��ļ����Ƿ���ȷ ");
        puts("        �����������...            ");
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
        printf("����ɹ���������%d�����ʡ�\n",cnt);
    }
    puts("�����������...");
    getchar();
    MainMenu();
}

void Sort(WORD words[],int cnt)
{
    system("cls");
    int n = cnt;                        //  ��������
    WORD temp;                          
    int i,j;
	for(i = 1; i <= n-1; i ++)          //  ð������
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
    printf("�������ĵ��ʣ�%s\n",modstr+1);
    puts("������...");
    int liblen = strlen(libstr+1);
	int modlen = strlen(modstr+1);
	if(liblen < modlen){
		printf("δ�ҵ�������������ء�\n");
        getchar();
        return;
	}
    int i, D = 233,k;                               //  kΪʧ�����
    if(modlen == 1) k = 0;                          //  ��ͬ���ʳ����������ʧ�����
    else if(modlen <= 4) k = 1;
    else if(modlen <= 10) k = 2;    
	pre[0]=1;                                       //  ��ʼ��
	for(i = 1; i < liblen; ++i)
        pre[i] = pre[i-1]*D;                        //  Ԥ����
	for(i = 1; i < liblen; ++i)
        libhash[i] = libhash[i-1]*D + libstr[i];    //  hash����
	for(i = 1;i <= modlen; ++i)
        modhash[i] = modhash[i-1]*D + modstr[i];    //  hash����
    int num = 0,id;                                 //  ͳ��ƥ������
    char temp[50];                                  //  ��ʱ����
	for(i = 1; i+modlen-1 < liblen; i++)            //  ö�ٴ�ƥ���ַ���
    {
		if(darkcheck(i,modlen,k))
        {
            int j, z = 0;                           //  ö�ٱ���
            for(j = i; j <= i+modlen-1; j ++)
            {
                if(libstr[j] != ' ')                //  �����kmp����Ŀո�
                {
                    temp[z++] = libstr[j];
                }
            }
            temp[z] = '\0';
            if(FindTrie(temp))                      //  ���ڸõ���
            {
                num ++;
                id = FindWord(temp,'e');
                if(id == -1)
                {
                    num = 0;
                    break;
                }
                printf("������Ѱ�ҵ��ǣ�\n");
                printf("%s %s.%s\n",words[id].en,words[id].spech,words[id].cn);
            }
        }
    }
    if(num == 0)
        printf("δ�ҵ��õ���\n");
    getchar();
    return;
}

int darkcheck(int x,int len,int misserror)
{
#ifdef _TEST_
    printf("to:darkcheck\n");
    getchar();
#endif
    int S_H = 1;                        //  S��ͷ
    int i;
    for(i = 0; i < misserror; i ++)     //  ��������misserro��ʧ��
    {
        int cmplen = lcp(x,S_H,len-S_H+1);   //���ز�ѯƥ��ĳ���
        x += cmplen + 1;                //  ������ʧ��λ��
        S_H += cmplen + 1;
        if(S_H > len)
            return 1;                   //  ƥ��ɹ�
    }
    int r = x+len-1;
    //�ж��Ƿ���ȫ��ͬ
    return askhash(libhash,x,r) == askhash(modhash,1,len);
}

int lcp(int S0_H, int S1_H, int rigt)
{
#ifdef _TEST_
    printf("to:lcp\n");
    getchar();
#endif
    int left = 1, mid;                  //  ��˵����е�
    int cmplen = 0;                     //  ƥ�䳤��
    while(left <= rigt)                 //  ���ֲ���
    {
        mid = (left + rigt) >> 1;
        if(askhash(libhash,S0_H,S0_H+mid-1) == askhash(modhash,S1_H,S1_H+mid-1))
        {
            //  ��һ����ƥ����
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
    int i, nowpoint = 0;                //  nowpoint�ڵ���
    int len = strlen(word);
    for(i = 0; i < len; i ++)
    {
        word[i] = tolower(word[i]);
        int next = word[i] - 'a';
        if(!trie[nowpoint][next])       //  �������ӽڵ�
            trie[nowpoint][next] = ++triecnt;
        nowpoint = trie[nowpoint][next];
    }
    trieexist[nowpoint] = 1;            //  �ڵ�������
    return ;
}

int FindTrie(char word[])
{
#ifdef _TEST_
    printf("to:FindTrie\n");
    getchar();
#endif
    int nowpoint = 0, next, i;          //  nowpointΪ��ǰ�ڵ�,next��һ���ڵ�
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
    if(mode == 'e')                 //  ��ѯӢ��
    {
        for(i = 1; i <= cnt; i ++)
        {   if(!strcmp(words[i].en,str))
                return i;
        }
    }
    else
    {                               //  ��ѯ����
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
    int id;                         //  ѭ������  
    for(id = 1; id <= cnt; id++)    //  ��ʼ��
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
        //  unit����
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
        //  grade����
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
        //  part����
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
    int id,nex;             //  idΪ�����id��nexΪ��ǰָ�����һ�������
    if(mode == 1)                   //  �꼶
    {
        id = GrdHead[condition];
        if(id == 0) return;
        while(words[id].nexlis.grdnext != id)
        {
            id = words[id].nexlis.grdnext;
            SectionBook[id] ++;     //  Ⱦɫ���
        }
    }
    else if(mode == 2)              //  ��Ԫ
    {
        id = UniHead[condition];
        if(id == 0) return;
        while(words[id].nexlis.uninext != id)
        {
            id = words[id].nexlis.uninext;
            SectionBook[id] ++;     //  Ⱦɫ���
        }
    }
    else if(mode == 3)              //  ���²�
    {
        id = ParHead[condition];
        if(id == 0) return;
        while(words[id].nexlis.parnext != id)
        {
            id = words[id].nexlis.uninext;
            SectionBook[id] ++;     //  Ⱦɫ���
        }
    }
}

int WordTest_Choise(int id,int mode)
{
    system("cls");
    int set[4]={0,0,0,0};           //  setΪ�ĸ�ѡ���Ӧ��idֵ,
    int ans, i;                     //  ansΪ��ȷѡ���λ��
    srand(time(0));                 //  ��ʼ�����������
    ans = rand()%4;                 //  ��ȷ�����ڵ�ѡ��
    set[ans] = id;
    while(1)                        //  �������ѡ��
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
    //  ѡ������
    int choise;                     //  �û�ѡ��
    if(mode == 1)
    {
        puts("----------------------------------");
    	puts("  ���ݸ�����Ӣ��ѡ�����ȷ���ĵ�ѡ�� ");
    	puts("----------------------------------");
        printf("Ӣ�ģ�%s ��ѡ��\n",words[id].en);
        printf("   1.%s\n",words[set[0]].cn);
        printf("   2.%s\n",words[set[1]].cn);
        printf("   3.%s\n",words[set[2]].cn);
        printf("   4.%s\n",words[set[3]].cn);
        scanf("%d",&choise);
        if(choise-1 == ans)
        {
            printf("  ��ţ���ȷ��\n");
            getchar();
            puts("�����������...");
            getchar();
            return 1;
        }else{
            printf("  ��������������ȷ���ǣ�%d.%s\n",ans+1,words[set[ans]].cn);
            getchar();
            puts("�����������...");
            getchar();
            return 0;
        }
    }
    //  ѡ��Ӣ��
    else
    {
        puts("----------------------------------");
    	puts("  ���ݸ���������ѡ�����ȷ���ĵ�ѡ�� ");
    	puts("----------------------------------");
        printf("���ģ�%s ��ѡ��\n",words[id].cn);
        printf("   1.%s\n",words[set[0]].en);
        printf("   2.%s\n",words[set[1]].en);
        printf("   3.%s\n",words[set[2]].en);
        printf("   4.%s\n",words[set[3]].en);
        scanf("%d",&choise);
        if(choise-1 == ans)
        {
            printf("  ��ţ���ȷ��\n");
            getchar();
            puts("�����������...");
            getchar();
            return 1;
        }else{
            printf("  ��������ȷ����%d.%s\n",ans+1,words[set[ans]].en);
            getchar();
            puts("�����������...");
            getchar();
            return 0;
        }
    }
}



// ��memory�����е�0123�ĸ�ѡ��˳����� 
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
//��������ĸ�ѡ�ѡ����ȷѡ�� 
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
	printf("��ѡ����ȷ����˼:%s \n",raw[i].en);
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
//����Ĭд���ʣ�ֱ��ÿ�����ʶ�Ĭд��ȷ 
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
		printf("%s,��д��Ӣ��:",wrong[i].cn);
		scanf("%s",answer);
		if(strcmp(answer,wrong[i].en)==0)//�����ȷ����ȥ��һ�У�������һ�ļ� 
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
    while(fgets(filechar,40,fp) != NULL)//��ȥ��һ�У�������һ�ļ������ҵ�һ�д�����һ�ļ������ 
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
	text(filename1,filename);//�����ļ����ν�����ֱ�����е��ʶ�Ĭд��ȷ 
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
        printf("������ʵ�������֪����\n֪���밴0����֪���밴1��");
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
        printf("��������Ҫ�������Ե�����\n�����밴1�������밴0��");
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
        printf("������ʵ�Ӣ����֪����\n֪���밴0����֪���밴1��");
        scanf("%d",&t);
        while(t)
        {
            FILE *fp;
            fp=fopen(filename,"a");
            for(i=0;i<Unknownwords;i++)
            {
                if(!strcmp(words[i].en,wordss[i].en))
                    printf("���ʱ������д˵��ʡ�");
                else
                    fprintf(fp,"%s %s %s %d %d %s",words[i].en,words[i].cn,words[i].spech,words[i].unit,words[i].grade,words[i].part);
               }
            fclose(fp);
            t=0;
        }
        if(i<all) i++;
        printf("��������Ҫ�������Ե�����\n�����밴1�������밴0��");
        scanf("%d",&k);
    }
}
