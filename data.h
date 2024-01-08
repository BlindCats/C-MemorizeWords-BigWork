/************************
*  ���ߣ�BlindCats       *
*  �ļ�����data.h        *
*  ˵�������ݽṹ������   *
*  ���ڣ�2023-12-23      *
*************************/

#define MAX_LEN 50              //  Ӣ���������ַ�������󳤶�
#define NORMALNUM 5             //  ���Եȵ���󳤶�
#define MAX_LIST 20             //  ����ͷ�е���󳤶�
#define MAX_N 10000             //  ��󵥴�����
#define MAX_S 100000            //  ����ı���ƥ�䳤��

//#define _TEST_

int UniHead[MAX_LIST];          //  unit������ͷ
int GrdHead[MAX_LIST];          //  grade������ͷ
int ParHead[NORMALNUM];         //  part������ͷ
int SectionBook[MAX_N];         //  ɸѡ���

int sortlist[MAX_N];            //  �洢˳��ṹ��id

//  �������ڰ�Ԫ�ز�ѯ    
typedef struct pointlist
{
    int uninext;                //  ��ͬunit��һ�����ʵ�id   
    int grdnext;                //  ��ͬgrade��һ�����ʵ�id
    int parnext;                //  ��ͬpart��һ�����ʵ�id
}POLT;

//  �洢ÿ�����ʵĽṹ��    
typedef struct word
{
    char en[MAX_LEN];           //  ����Ӣ��
    char cn[MAX_LEN];           //  ���ĺ���
    char spech[NORMALNUM];      //  ����
    int unit;                   //  ���ڵ�Ԫ
    int grade;                  //  �꼶
    char part;                  //  ���²�
    POLT nexlis;                //  ����ṹ��
}WORD;

int pre[MAX_S];                 //  hashԤ����
int libhash[MAX_S];             //  �ı���hash����
int modhash[MAX_S];             //  ģʽ��hash����

int trie[MAX_S][26];            //  �ֵ���
int trieexist[MAX_S] = {0};     //  �ֵ����������
int triecnt = 0;                //  �ֵ����ڵ���

//  ȫ�ֱ���    
static WORD words[MAX_N];       //  ���ʱ�
static int cnt = 0;             //  �ܵ�������