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
	void CreateHuffman();
	void PrintWeight();
	void HuffmanCode();
	void HuffmanTree(HNodeType HuffNode[],int n,lable a[]);
};

void Huffman::HuffmanTree(HNodeType HuffNode[],int n,lable a[])
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
		{
  	  for (j=i+1;j<n-1;j++) /*�������ַ���Ȩֵ��С��������*/
  		{  	
  	    if (a[j].num>a[i].num)
  	    {
  	      temp1=a[i].num;
  	      a[i].num=a[j].num;
  	      a[j].num=temp1;
  	      temp2=a[i].s;
  	      a[i].s=a[j].s;
  	      a[j].s=temp2;
  	    }
  	  }
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

void Huffman::HuffmanCode()
{
    HNodeType HuffNode[MAXNODE];
    HCodeType HuffCode[MAXLEAF],cd;
    int i,j,c,p;

    HuffmanTree(HuffNode,count,data);

    for (i=0;i<count;i++)     /*�����λ�ý��б���*/
    {
        cd.start=count-1;
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
        for (j=cd.start+1;j<count;j++)    /*�������*/
            HuffCode[i].bit[j]=cd.bit[j];
        HuffCode[i].start=cd.start;
    }
    for (i=0;i<count;i++)
    {
        HuffCode[i].letter=HuffNode[i].letter;
        fout<<"         "<<HuffCode[i].letter<<" ";

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
  HuffmanCode();

}

void Huffman::PrintWeight()
{
	fout<<"different letters:"<<count<<"\n";
  for (int nav=0;nav<count;nav++)
  {
      fout<<"         "<<data[nav].s<<" ";
      fout<<"weight:"<<data[nav].num<<"\n";
  }
}

void Huffman::CreateHuffman()
{
	//�Ȱ������ʼ��
	for(int i=1;i<=2*nodeNum-1;i++)
		huffNode[i].parent=huffNode[i].left=huffNode[i].right=0;
	
	//���²�������huffman������Ӧ�û��иĽ�����ء�
	//�˴�Ϊʲô��2*nodeNum-1?
	for(int i=nodeNum+1;i<=2*nodeNum-1;i++)
	{
		//l�洢���ӽڵ�ı�ţ�r�洢���ӽڵ�ı��
		//�������ӽڵ�ҪС�����ӽڵ�
		//l����С�ڵ�
		int l,r;
		l=r=0;
		//�˴�m1�洢��Сֵ��m2�洢��Сֵ
		int m1,m2;
		m1=m2=20000;
		for(int j=1;j<i;j++)
		{
			if(huffNode[j].weight<m1&&huffNode[j].parent==0)
			{
				m2=m1;
				r=l;
				m1=	huffNode[j].weight;
				l=j;
			}
			else if(huffNode[j].weight<m2&&huffNode[j].parent==0)
			{
				m2=	huffNode[j].weight;
				r=j;
			}
		}
		huffNode[l].parent=huffNode[r].parent=i;
		huffNode[i].left=l;
		huffNode[i].right=r;
		huffNode[i].weight=m1+m2;
	}
}