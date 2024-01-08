#ifndef _HEAD_
#define _HEAD_
#include "data.h"
#include "menu.h"
#endif

//  从filename.txt文件读取，返回单词总数    
int ReadFromfile(char filename[]);
/*  从filename.in文件读取，返回单词总数  */
int ReadFromIn(char filename[]);
//  载入函数    
void UpLoad(void);
//  排序函数    
void Sort(WORD words[],int cnt);
//  输出单个单词    
void PrintOne(WORD words);
//  输出所有单词    
void PrintAll(WORD words[],int cnt);
//  在libstr文本串中，模糊寻找modstr模式串  
void DarkSerch(char libstr[],char modestr[]);
//  模式串第i位开始长度为len的字串k次失配内能否完成匹配   
int darkcheck(int i,int len,int k);
//  查询区间[left,rigt]的哈希值   
int askhash(int hash[],int left,int rigt);
//  查询分别从S0_H、S1_H位置开始的S0于S1字符串相同部分的长度
int lcp(int S0_H, int S1_H, int rigt);
//  将字符串转化为整形
int TranStrtoInt(char str[]);
//  将word[]插入字典树中
void InsertTrie(char word[]);
//  在字典树中查询word[]，返回1为有，0为无
int FindTrie(char word[]);
//  枚举查找英文(mode:e)/中文(mode:z)，存在则返回单词id，否则返回-1
int FindWord(char str[],char mode);
//  建立链表
void BuiltLine(int cnt);
//  按照条件搜索,mode:1.年级 2.单元 3.上下册
void ConditionSerch(int condition,int mode);
//  单词测试，mode:1.选择中文 2.选择英文，返回正误
int WordTest_Choise(int id,int mode);