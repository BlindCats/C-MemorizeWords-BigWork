#ifndef _HEAD_
#define _HEAD_
#include "data.h"
#endif

//  首次使用登录页
void WelComeMenu(void);
//  待开发功能的提示页
void page404(void);
//  搜索单词页面
void SearchMenu(WORD words[],int cnt);
//  精准搜索页面
void PreciseSearchMenu_en(void);
void PreciseSearchMenu_cn(void);
//  模糊搜索页面    
void DarkSearchMenu(WORD words[],int cnt);
//  导入页面输入单元序号    
void ConditionSection(void);
//  主页
void MainMenu(void);
//  显示词库菜单
void WordlibMenu(void);
//  单词测试菜单
void TestMenu(void);