#ifndef _HEAD_
#define _HEAD_
#include "data.h"
#endif

//  �״�ʹ�õ�¼ҳ
void WelComeMenu(void);
//  ���������ܵ���ʾҳ
void page404(void);
//  ��������ҳ��
void SearchMenu(WORD words[],int cnt);
//  ��׼����ҳ��
void PreciseSearchMenu_en(void);
void PreciseSearchMenu_cn(void);
//  ģ������ҳ��    
void DarkSearchMenu(WORD words[],int cnt);
//  ����ҳ�����뵥Ԫ���    
void ConditionSection(void);
//  ��ҳ
void MainMenu(void);
//  ��ʾ�ʿ�˵�
void WordlibMenu(void);
//  ���ʲ��Բ˵�
void TestMenu(void);