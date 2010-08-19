// ����������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#define MAX 21
//#include "Huffman.h"

#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<string.h>
#include<stdlib.h>

#define MAXVALUE 10000  /*Ȩֵ���ֵ*/
#define MAXLEAF 30 /*Ҷ��������*/
#define MAXNODE MAXLEAF*2-1    /* ������ĸ���*/
#define MAXBIT 50        /*��������λ��*/
using namespace std;

typedef struct node   /*������Ͷ���*/
{
    char letter;
    int weight;
    int parent;
    int lchild;
    int rchild;
}HNodeType;

typedef struct    /*�������Ͷ���*/
{
    char letter;
    int bit[MAXBIT];
    int start;
}HCodeType;

typedef struct  /*������ŵ�����*/
{
    char s;
    int num;
}lable;

void HuffmanTree(HNodeType HuffNode[],int n,lable a[])
{
    int i,j,m1,m2,x1,x2,temp1;
    char temp2;
    for (i=0;i<2*n-1;i++)      /*����ʼ��*/
    {
        HuffNode[i].letter=0;
        HuffNode[i].weight=0;
        HuffNode[i].parent=-1;
        HuffNode[i].lchild=-1;
        HuffNode[i].rchild=-1;
    }
    for (i=0;i<n-1;i++)

        for (j=i+1;j<n-1;j++) /*�������ַ���Ȩֵ��С��������*/
            if (a[j].num>a[i].num)
            {
                temp1=a[i].num;
                a[i].num=a[j].num;
                a[j].num=temp1;
                temp2=a[i].s;
                a[i].s=a[j].s;
                a[j].s=temp2;
            }

    for (i=0;i<n;i++)
    {
        HuffNode[i].weight=a[i].num;
        HuffNode[i].letter=a[i].s;
    }
    for (i=0;i<n-1;i++)        /*����huffman��*/
    {
        m1=m2=MAXVALUE;
        x1=x2=0;
        for (j=0;j<n+i;j++)/*Ѱ��Ȩֵ��С���С�Ľ��*/
        {
            if (HuffNode[j].parent==-1&&HuffNode[j].weight<m1)
            {
                m2=m1;
                x2=x1;
                m1=HuffNode[j].weight;
                x1=j;
            }
            else if (HuffNode[j].parent==-1&&HuffNode[j].weight<m2)
            {
                m2=HuffNode[j].weight;
                x2=j;
            }
        }
        HuffNode[x1].parent=n+i;
        HuffNode[x2].parent=n+i;         /*Ȩֵ��С���С�Ľ��������*/
        HuffNode[n+i].weight=HuffNode[x1].weight+HuffNode[x2].weight;
        HuffNode[n+i].lchild=x1;
        HuffNode[n+i].rchild=x2;
    }
}

void HuffmanCode(int n,lable a[])
{
    HNodeType HuffNode[MAXNODE];
    HCodeType HuffCode[MAXLEAF],cd;
    int i,j,c,p;

    HuffmanTree(HuffNode,n,a);

    for (i=0;i<n;i++)     /*�����λ�ý��б���*/
    {
        cd.start=n-1;
        c=i;
        p=HuffNode[c].parent;
        while (p!=-1)
        {
            if (HuffNode[p].lchild==c)
                cd.bit[cd.start]=0;
            else cd.bit[cd.start]=1;
            cd.start--;
            c=p;
            p=HuffNode[c].parent;
        }
        for (j=cd.start+1;j<n;j++)    /*�������*/
            HuffCode[i].bit[j]=cd.bit[j];
        HuffCode[i].start=cd.start;
    }
    for (i=0;i<n;i++)
    {
        HuffCode[i].letter=HuffNode[i].letter;
        printf("         %c ",HuffCode[i].letter);

        for (j=HuffCode[i].start+1;j<n;j++)
            printf("%d",HuffCode[i].bit[j]);
        printf("\n");
    }
}

int main()
{
    lable data[30];
    char s[100],*p;
    int i,count=0;
    for (;;)
    {
        cout<<"         /    �����������,ֱ������Ϊend����!            /"<<endl;
        printf("         Input some letters:");
        scanf("%s",s);
        if (!strcmp(s,"end"))
            exit(0);
        for (i=0;i<30;i++)
        {
            data[i].s=0;
            data[i].num=0;
        }
        p=s;
        while (*p)     /*�����ַ���������ִ���(��Ȩֵ)*/
        {
            for (i=0;i<=count+1;i++)
            {
                if (data[i].s==0)
                {
                    data[i].s=*p;
                    data[i].num++;
                    count++;
                    break;
                }
                else if (data[i].s==*p)
                {
                    data[i].num++;
                    break;
                }
            }
            p++;
        }
        printf("\n");
        printf("         different letters:%d\n",count);

        for (i=0;i<count;i++)
        {
            printf("         %c ",data[i].s);
            printf("weight:%d\n",data[i].num);
        }
        HuffmanCode(count,data);
        count=0;
    }
    getch();
}

