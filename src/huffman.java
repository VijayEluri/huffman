public class huffman {
	Struct	{
	  char data;
	  int weight;
	  int parent;
	  int left;
	  int right;
	}HuffNode;

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

	  public:
	    void CreateHuffman();
	    void HuffmanEncode();//use the created tree to encode Huffman
	    void HuffmanDecode();//use the created tree to decode Huffman
	};

	void Huffman::CreateHuffman()
	{
	  for(int i=1;i<=2*nodeNum-1;i++)
	    huffNode[i].parent=huffNode[i].left=huffNode[i].right=0;

	  for(int i=nodeNum+1;i<=2*nodeNum-1;i++)
	  {
	    int l,r;
	    l=r=0;
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

	void Huffman::HuffmanEncode()
	{
	  for(int i=1;i<=nodeNum;i++)
	  {
	    huffCode[i].start=0;
	    int child=i;
	    int parent=huffNode[child].parent;
	    while(parent!=0)
	    {
	      if(huffNode[parent].left==child)
	        huffCode[i].cd[huffCode[i].start++]='0';
	      else if(huffNode[parent].right==child)
	        huffCode[i].cd[huffCode[i].start++]='1';
	      child=parent;
	      parent=huffNode[child].parent;
	    }
	    for(int j=huffCode[i].start-1;j>=0;j--)
	    {
	      System.out.println(huffCode[i].cd[j]);
	    }
	    System.out.println();
	  }
	}

	void Huffman::HuffmanDecode()
	{
	  //the following are decode the Huffman using the created tree
	  for(int i=1;i<=nodeNum;i++)
	  {
	    huffCode[i].start=0;
	    int child=i;
	    int parent=huffNode[child].parent;
	    while(parent!=0)
	    {
	      if(huffNode[parent].left==child)
	        huffCode[i].cd[huffCode[i].start++]='0';
	      else if(huffNode[parent].right==child)
	        huffCode[i].cd[huffCode[i].start++]='1';
	      child=parent;
	      parent=huffNode[child].parent;
	    }
	    for(int j=huffCode[i].start-1;j>=0;j--)
	    {
	      System.out.println(huffCode[i].cd[j]);
	    }
	    System.out.println();
	  }
	}
	static public void main(String[] args) {
		Huffman huffman;
		  huffman.CreateHuffman();
	}
}