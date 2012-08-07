//Huffman.java   
import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.Set;

public class Huffman {
	public Huffman(LinkedHashMap<Character, Integer> map) {
		charTable = map;
		charset = map.keySet();
		creatHuffmanTree();
		// creatHuffmanCode();
	}

	public String enCodeString(String inString) {
		StringBuffer temp = new StringBuffer();
		for (int i = 0; i < inString.length(); i++) {
			int ch = inString.charAt(i);
			int j = 1;
			for (; huffmanTree.get(j).charTag != ch && j < charset.size() + 1; j++) {
			}
			if (j <= charset.size()) {
				temp.append(huffmanCode.get(j));
			} else {
				temp.append(ch);
			}
		}
		return temp.toString();
	}

	public String deCodeString(String inString) {
		StringBuffer temp = new StringBuffer();
		int root = charset.size() * 2 - 1;
		for (int i = 0; i < inString.length(); i++) {
			char ch = inString.charAt(i);
			if (ch == '0') {
				root = huffmanTree.get(root).lChild;
			} else if (ch == '1') {
				root = huffmanTree.get(root).rChild;
			} else {
				temp.append(ch);
			}
			if (root <= charset.size()) {
				temp.append(huffmanTree.get(root).charTag);
				root = charset.size() * 2 - 1;
			}
		}
		return temp.toString();
	}

	private void Print() {
		for (int i = 0; i < huffmanTree.size(); i++) {
			System.out.println(i + "," + huffmanTree.get(i).charTag
					+ ",weight->" + huffmanTree.get(i).weight + ",parent->"
					+ huffmanTree.get(i).parent);
		}
	}

	private void creatHuffmanTree() {
		initTree();
		int leftChild;// the min index
		int rightChild;// the second min index
		for (int i = charset.size(); i < 2 * charset.size(); i++) {
			leftChild = -1;
			rightChild = -1;
			for (int j = 0; j <= i; j++) {
				if (huffmanTree.get(j).parent == -1) {
					if (leftChild == -1) {
						leftChild = j;
						rightChild = j;
					}
					if (huffmanTree.get(j).weight < huffmanTree.get(leftChild).weight) {
						rightChild = leftChild;
						leftChild = j;
					} else if (huffmanTree.get(j).weight < huffmanTree
							.get(rightChild).weight) {
						rightChild = j;
					}
				}
			}
			huffmanTree.get(leftChild).parent = i;
			huffmanTree.get(rightChild).parent = i;

			System.out.println(leftChild + "'s parent is " + i);
			System.out.println(rightChild + "'s parent is " + i);
			System.out.println();
			huffmanTree.get(i).lChild = leftChild;
			huffmanTree.get(i).rChild = rightChild;
			huffmanTree.get(i).weight = huffmanTree.get(leftChild).weight
					+ huffmanTree.get(rightChild).weight;
		}
	}

	void LevelOrder(int current, int indent) {
		if (huffmanTree.get(current).rChild != 0) {
			LevelOrder(huffmanTree.get(current).rChild, indent + 1);
		}
		for (int i = 0; i < indent; i++)
			System.out.print("\t");
		System.out.println(huffmanTree.get(current).charTag);

		if (huffmanTree.get(current).lChild != 0) {
			LevelOrder(huffmanTree.get(current).lChild, indent + 1);
		}
	}

	private void creatHuffmanCode() {
		huffmanCode = new ArrayList<String>(charset.size() + 1);
		huffmanCode.add(0, null);
		char[] tempChars = new char[charset.size() + 1];
		for (int i = 1; i < charset.size() + 1; i++) {
			int startIndex = charset.size();
			int parent = huffmanTree.get(i).parent;
			int ch = i;
			while (parent != 0) {
				if (huffmanTree.get(parent).lChild == ch) {
					tempChars[startIndex] = '0';
				} else {
					tempChars[startIndex] = '1';
				}
				startIndex--;
				ch = parent;
				parent = huffmanTree.get(parent).parent;
			}
			System.out.println(String.valueOf(tempChars, startIndex + 1,
					charset.size() - startIndex));
			huffmanCode.add(
					i,
					String.valueOf(tempChars, startIndex + 1, charset.size()
							- startIndex));
		}
	}

	private void initTree() {
		huffmanTree = new ArrayList<Node>();
		Iterator<Character> charIter = charset.iterator();
		int i = 0;
		huffmanTree.add(0, new Node((char) 0, Integer.MAX_VALUE, 0, 0, 0));
		while (charIter.hasNext()) {
			Character ch = charIter.next();
			huffmanTree.add(i, new Node(ch, charTable.get(ch), 0, 0, 0));
			i++;
		}
		for (int j = charset.size(); j < 2 * charset.size(); j++) {
			huffmanTree.add(j, new Node((char) 0, Integer.MAX_VALUE, 0, 0, 0));
		}
	}

	private LinkedHashMap<Character, Integer> charTable;
	private Set<Character> charset;
	private ArrayList<Node> huffmanTree;
	private ArrayList<String> huffmanCode;

	class Node {
		char charTag;
		int weight = 10000;
		int parent = -1;
		int lChild = 0;
		int rChild = 0;

		public Node(char c, int w, int p, int l, int r) {
			charTag = c;
			weight = w;
			lChild = l;
			rChild = r;
		}
	}
}
