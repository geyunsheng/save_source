/*
*��KMP�㷨ʵ���ַ���ƥ����������
*�ó���ʵ�ֵĹ�����������Ŀ¼�µ������ļ��������Ƿ��������
*�ַ���ƥ�䣬���ƥ�䣬������ļ������������ַ�������
*��������Ŀ�괮����ָ���ƶ�λ�� = ��ƥ����ַ��� - ��Ӧ����ƥ��ֵ
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define KEYWORD_MAX_LENGTH 100      //�趨����������󳤶�

int kmp_table[KEYWORD_MAX_LENGTH];  //Ϊ����������kmp��
char prefix_stack[KEYWORD_MAX_LENGTH]; //ǰ׺���ʽջ
char suffix_stack[KEYWORD_MAX_LENGTH]; //��׺���ʽջ
int keyword_length = 0;  //�������ĳ���
int record_position[KEYWORD_MAX_LENGTH]; //��¼��ؼ��ִ�ƥ��Դ���е�λ��

/*
*GetMatchValue:����ַ���src�Ĳ���ƥ��ֵ
*/
int GetMatchValue(char *src)
{
    int value = 0;
    int src_len = strlen(src);
    char *begin = src;    //��ʼ��ָ���ַ�����һ���ַ�
    char *end = src + (src_len - 1);  //��ʼ��ָ���ַ������һ���ַ�
    int i = 0;
    for(i=0;i<(src_len-1);i++)
    {
        prefix_stack[i] = *begin;
        suffix_stack[i] = *end;
        begin++;
        end--;
    }
    char *p = prefix_stack;
    char *q = suffix_stack + (src_len - 2);  //ָ��ջ�����һ��Ԫ��
    int flag = 0;   //��һ����־λ��ȷ����׺ջ�е����һ��Ԫ�ض���ǰ׺ջ�еķ���ƥ��
    while(q >= suffix_stack)
    {
        if(*p == *q)
        {
            value++;
            p++;
            flag=1;
        }
        else {
            flag = 0;
        }
        q--;
    }
    if(flag == 0) value = 0;
    return value;
}

/*
*���������ַ�����KMP��
*/
int Create_KMP_Table(char *str,int *table)
{
    int i;
    char *dst;
    keyword_length = strlen(str);
    for(i=0;i<keyword_length;i++)
    {
        if(i == 0) {
            table[i] = 0;   //��һ���ַ���ǰ׺�ͺ�׺������Ϊ0
        }
        else {
            dst = (char*)malloc((i+2));
            if(dst == NULL)
            {
                printf("malloc space error!\n");
                return EXIT_FAILURE;
            }
            strncpy(dst,str,(i+1));   //ƥ��str��ǰ(i+1)���ַ�
            dst[i+1] = '\0';    //ע���ַ���Ҫ��'/0'��β
            table[i] = GetMatchValue(dst); 
            free((void*)dst);    
        }
    }
    return EXIT_SUCCESS;
}

//��ӡ�����ַ�����Ӧ��KMP��
void Table_Print(char *str,int *table)
{
    int i;
    char c = *str;
    while(c != '\0')
    {
        printf("%-4c",c);        //�������������ַ����е��ַ�
        c = *++str;
    }
    printf("\n");
    for(i=0;i<keyword_length;i++)
    {
        printf("%-4d",table[i]); //��������ÿ���ַ���Ӧ�Ĳ���ƥ��ֵ
    }
    printf("\n");
}

//��Ŀ�괮dst_str�������ؼ��Ӵ�search_str,��ӡ���ؼ��ִ���λ����Ϣ,������ؼ��ִ�ƥ�����Ŀ
int Search_Keyword(char *dst_str,char *search_str)
{
    char *p = dst_str;
    char *q = search_str;
    char *temp;

    //�����ؼ��ִ���KMP��    
    Create_KMP_Table(search_str,kmp_table);
    
    int count = 0;  //��¼�����Ѿ�ƥ�����Ŀ
    int k = 0;     //��¼��ؼ��ִ�ƥ����ִ�����Ŀ
    int move = 0;  //���ַ�����ƥ��ʱ������ָ���ƶ���λ��    

    while(*p != '\0')   //ֱ��������Ŀ�괮�����һ���ַ�Ϊֹ
    {
        temp = p;
        while(*q != '\0')
        {
            if(*q == *temp)
            {
                count++;
                temp++;
                q++;
            }
            else break;
        }
        
        if(count == 0)
            p++;
        else {
            if(count == keyword_length)
            {
                record_position[k++] = (temp-dst_str)-(keyword_length);
            }
            move = count - kmp_table[count-1];
            p += move;
        }

        count = 0;
        q = search_str;
    }
    return k;
}


int main(int argc,char **argv)
{
    char *search_str = argv[1];
    //char dst_str[] = "hello woshijpf woshijpf woshij woshijp woshijpf";
    char dst_str[] = "BBC ABCDAB ABCDABCDABDE";
    
    printf("Please input serach string and dst_string\n");
    if(search_str == NULL)
    {
        printf("Please input search string\n");
        return EXIT_FAILURE;
    }

    if(dst_str == NULL)
    {
        printf("Please input dst_string\n");
        return EXIT_FAILURE;
    }
    
    int result = Search_Keyword(dst_str,search_str);  //�Ż��������Ľ������Ŀ
    Table_Print(search_str,kmp_table);
    printf("%s\n",dst_str);         //�����������Ŀ�괮
    if(result == 0)
    {
        printf("Sorry!Don't find the string %s\n",search_str);
        return EXIT_SUCCESS;
    }
    else {
        int i,j,num;
        int before = 0;
        for(i=0;i<result;i++)
        {
            num = record_position[i] - before;    //��ӡ��������Ŀ�괮�е�λ��
            before = record_position[i]+1;
            for(j=1;j<=num;j++)
                printf(" ");
            printf("*");
        }
        printf("\n");
    }
    
    return EXIT_SUCCESS;
}