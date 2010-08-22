// ����������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#define MAX 21
#include "Huffman.h"

#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<string.h>
#include<stdlib.h>

using namespace std;



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


int main()
{
    
    Huffman *huffman=new Huffman();
    {
        
    }
}

