#ifndef _HEAD_
#define _HEAD_
#include "data.h"
#include "menu.h"
#endif

//  ��filename.txt�ļ���ȡ�����ص�������    
int ReadFromfile(char filename[]);
/*  ��filename.in�ļ���ȡ�����ص�������  */
int ReadFromIn(char filename[]);
//  ���뺯��    
void UpLoad(void);
//  ������    
void Sort(WORD words[],int cnt);
//  �����������    
void PrintOne(WORD words);
//  ������е���    
void PrintAll(WORD words[],int cnt);
//  ��libstr�ı����У�ģ��Ѱ��modstrģʽ��  
void DarkSerch(char libstr[],char modestr[]);
//  ģʽ����iλ��ʼ����Ϊlen���ִ�k��ʧ�����ܷ����ƥ��   
int darkcheck(int i,int len,int k);
//  ��ѯ����[left,rigt]�Ĺ�ϣֵ   
int askhash(int hash[],int left,int rigt);
//  ��ѯ�ֱ��S0_H��S1_Hλ�ÿ�ʼ��S0��S1�ַ�����ͬ���ֵĳ���
int lcp(int S0_H, int S1_H, int rigt);
//  ���ַ���ת��Ϊ����
int TranStrtoInt(char str[]);
//  ��word[]�����ֵ�����
void InsertTrie(char word[]);
//  ���ֵ����в�ѯword[]������1Ϊ�У�0Ϊ��
int FindTrie(char word[]);
//  ö�ٲ���Ӣ��(mode:e)/����(mode:z)�������򷵻ص���id�����򷵻�-1
int FindWord(char str[],char mode);
//  ��������
void BuiltLine(int cnt);
//  ������������,mode:1.�꼶 2.��Ԫ 3.���²�
void ConditionSerch(int condition,int mode);
//  ���ʲ��ԣ�mode:1.ѡ������ 2.ѡ��Ӣ�ģ���������
int WordTest_Choise(int id,int mode);