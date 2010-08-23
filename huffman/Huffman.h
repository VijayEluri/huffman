#include<iostream>
using namespace std;

#define MAXVALUE 10000  /*Ȩֵ���ֵ*/
#define MAXLEAF 30 /*Ҷ��������*/
#define MAXNODE MAXLEAF*2-1    /* ������ĸ���*/
#define MAXBIT 50        /*��������λ��*/

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

typedef struct 
{
    char data; //���ֵ
    int weight; //
    int parent; //�����
    int left; //����
    int right;//�ҽ��
}HuffNode;

typedef struct  /*������ŵ�����*/
{
    char s;
    int num;
}lable;

typedef struct
{
    char cd[MAX];
    int start;
}HuffCode;

class Huffman
{
private:
	int nodeNum;
	HuffNode *huffNode;
	HuffCode *huffCode;
	int count;
	ofstream fout;
	

public:
	lable data[30];
	Huffman();
	~Huffman();
	void PrintWeight();
	void HuffmanCode();
	void HuffmanTree(HNodeType HuffNode[]);
};

void Huffman::HuffmanTree(HNodeType HuffNode[])
{
  	int i,j,min1,min2,min_index1,min_index2;
  	for (i=0;i<2*count-1;i++)      /*����ʼ��*/
  	{
  	  HuffNode[i].letter=0;
  	  HuffNode[i].weight=0;
  	  HuffNode[i].parent=-1;
  	  HuffNode[i].lchild=-1;
  	  HuffNode[i].rchild=-1;
  	}
  	for (i=0;i<count-1;i++)
		{
  	  for (j=i+1;j<count-1;j++) /*�������ַ���Ȩֵ��С��������*/
  		{  	
  	    if (data[j].num>data[i].num)
  	    {
  	      data[j].num^=data[i].num;
  	      data[i].num^=data[j].num;
  	      data[j].num^=data[i].num;
  	      
  	      data[j].s^=data[i].s;
  	      data[i].s^=data[j].s;
  	      data[j].s^=data[i].s;
  	    }
  	  }
		}
  	for (i=0;i<count;i++)
  	{
  	  HuffNode[i].weight=data[i].num;
  	  HuffNode[i].letter=data[i].s;
  	}
  	for (i=0;i<count-1;i++)        /*����huffman��*/
  	{
  	  min1=min2=MAXVALUE;
  	  min_index1=min_index2=0;
  	  for (j=0;j<count+i;j++)/*Ѱ��Ȩֵ��С���С�Ľ��*/
  	  {
  	    if (HuffNode[j].parent==-1&&HuffNode[j].weight<min1)
  	    {
  	      min2=min1;
  	      min_index2=min_index1;
  	      min1=HuffNode[j].weight;
  	      min_index1=j;
  	    }
  	    else if (HuffNode[j].parent==-1&&HuffNode[j].weight<min2)
  	    {
  	      min2=HuffNode[j].weight;
  	      min_index2=j;
  	    }
  	  }
  	  HuffNode[min_index1].parent=count+i;
  	  HuffNode[min_index2].parent=count+i;         /*Ȩֵ��С���С�Ľ��������*/
  	  HuffNode[count+i].weight=HuffNode[min_index1].weight+HuffNode[min_index2].weight;
  	  HuffNode[count+i].lchild=min_index1;
  	  HuffNode[count+i].rchild=min_index2;
  	}
} 	

void Huffman::HuffmanCode()
{
    HNodeType HuffNode[MAXNODE];
    HCodeType HuffCode[MAXLEAF],cd;
    int i,j,c,p;

    HuffmanTree(HuffNode);

    for (i=0;i<count;i++)     /*�����λ�ý��б���*/
    {
        cd.start=count-1;
        c=i;
        p=HuffNode[c].parent;
        while (p!=-1)
        {
            if (HuffNode[p].lchild==c)
							cd.bit[cd.start]=0;
            else 
            	cd.bit[cd.start]=1;
            cd.start--;
            c=p;
            p=HuffNode[c].parent;
        }
        for (j=cd.start+1;j<count;j++)    /*�������*/
            HuffCode[i].bit[j]=cd.bit[j];
        HuffCode[i].start=cd.start;
    }
    for (i=0;i<count;i++)
    {
        HuffCode[i].letter=HuffNode[i].letter;
        fout<<HuffCode[i].letter<<" ";

        for (j=HuffCode[i].start+1;j<count;j++)
            fout<<HuffCode[i].bit[j];
        fout<<endl;
    }
}

Huffman::~Huffman()
{
	fout.close();
}

Huffman::Huffman()
{
	count=0;
	fout.open("output.txt");
	char *user_input;
	int i;

	char s[100]="feifjakdfjioejfkdsifwfasdfawffawefawefawfafds";
	for (i=0;i<30;i++)
	{
    data[i].s=0;
		data[i].num=0;
	}
	user_input=s;
  while (*user_input)     /*�����ַ���������ִ���(��Ȩֵ)*/
  {
      for (i=0;i<=count+1;i++)
      {
          if (data[i].s==0)
          {
              data[i].s=*user_input;
              data[i].num++;
              count++;
              break;
          }
          else if (data[i].s==*user_input)
          {
              data[i].num++;
              break;
          }
      }
      user_input++;
  }
}

void Huffman::PrintWeight()
{
	fout<<"different letters:"<<count<<endl;
  for (int nav=0;nav<count;nav++)
  {
      fout<<data[nav].s<<" ";
      fout<<"weight:"<<data[nav].num<<endl;
  }
}