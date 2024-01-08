/************************
*  作者：BlindCats       *
*  文件名：data.h        *
*  说明：数据结构与类型   *
*  日期：2023-12-23      *
*************************/

#define MAX_LEN 50              //  英文与中文字符串的最大长度
#define NORMALNUM 5             //  词性等的最大长度
#define MAX_LIST 20             //  链表头中的最大长度
#define MAX_N 10000             //  最大单词数量
#define MAX_S 100000            //  最大文本串匹配长度

//#define _TEST_

int UniHead[MAX_LIST];          //  unit的链表头
int GrdHead[MAX_LIST];          //  grade的链表头
int ParHead[NORMALNUM];         //  part的链表头
int SectionBook[MAX_N];         //  筛选标记

int sortlist[MAX_N];            //  存储顺序结构的id

//  链表，用于按元素查询    
typedef struct pointlist
{
    int uninext;                //  相同unit下一个单词的id   
    int grdnext;                //  相同grade下一个单词的id
    int parnext;                //  相同part下一个单词的id
}POLT;

//  存储每个单词的结构体    
typedef struct word
{
    char en[MAX_LEN];           //  单词英文
    char cn[MAX_LEN];           //  中文含义
    char spech[NORMALNUM];      //  词性
    int unit;                   //  所在单元
    int grade;                  //  年级
    char part;                  //  上下册
    POLT nexlis;                //  链表结构体
}WORD;

int pre[MAX_S];                 //  hash预处理
int libhash[MAX_S];             //  文本串hash数组
int modhash[MAX_S];             //  模式串hash数组

int trie[MAX_S][26];            //  字典树
int trieexist[MAX_S] = {0};     //  字典树结束标记
int triecnt = 0;                //  字典树节点数

//  全局变量    
static WORD words[MAX_N];       //  单词表
static int cnt = 0;             //  总单词数量