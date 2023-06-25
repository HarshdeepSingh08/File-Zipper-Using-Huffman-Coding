

/* Hi this  is Harshdeep and Here we are going to implement File zipper using huffman coding*/

#include <bits/stdc++.h>

using namespace std;

// structure of node inside Huffman tree
struct Node
{
	char Ch;  // character
	int Freq; // frequency of that character
	Node *Left;
	Node *Right;
	Node(char ch, int freq, Node *left, Node *right) // constructor
	{
		Ch = ch;
		Freq = freq;
		Left = left;
		Right = right;
	}
};

// compare function to implement min heap using priority queue
struct Compare
{
	bool operator()(Node *Left, Node *Right)
	{
		return Left->Freq > Right->Freq;
	}
};

// creating node to insert at tree;
Node *CreateNode(char ch, int freq, Node *left, Node *right)
{
	Node *NewNode = new Node(ch, freq, left, right);
	return NewNode;
}

// This function recursively traverses the Huffman tree and assigns binary codes to each character.
// The binary codes are stored in the HuffmanCode unordered map, where the character is the key and the code is the value.
void Encoding(Node *Root, string Str, unordered_map<char, string> &HuffmanCode)
{
	if (Root == nullptr)
	{
		return;
	}

	if (!Root->Left && !Root->Right)
	{
		HuffmanCode[Root->Ch] = Str;
	}
	Encoding(Root->Left, Str + '0', HuffmanCode);
	Encoding(Root->Right, Str + '1', HuffmanCode);
}

// This function recursively decodes the encoded text using the Huffman tree.
//  It starts from the root of the tree and follows the binary codes in the input string to traverse the tree
//  and print the decoded characters.

void Decoding(Node *Root, int &index, string Str)
{
	if (Root == nullptr)
	{
		return;
	}

	if (!Root->Left && !Root->Right)
	{
		cout << Root->Ch;
		return;
	}

	index++;

	if (Str[index] == '0')
	{
		Decoding(Root->Left, index, Str);
	}
	else
	{
		Decoding(Root->Right, index, Str);
	}
}

// This function builds the Huffman tree based on the input text.
// It calculates the frequencies of each character, creates nodes for each character,
// and constructs the tree by merging nodes with the lowest frequencies until only one node remains as the root of the tree.
// It then calls the Encoding function to generate the Huffman codes, prints the codes, encodes the input text,
// and decodes the encoded text.

void BuildHuffmanTree(string Text)
{

	unordered_map<char, int> FreqOfChars;
	for (char ch : Text)
	{
		FreqOfChars[ch]++;
	}

	priority_queue<Node *, vector<Node *>, Compare> HuffmanTree;
	for (auto pair : FreqOfChars)
	{
		HuffmanTree.push(CreateNode(pair.first, pair.second, nullptr, nullptr));
	}

	while (HuffmanTree.size() != 1)
	{
		Node *Left = HuffmanTree.top();
		HuffmanTree.pop();

		Node *Right = HuffmanTree.top();
		HuffmanTree.pop();

		int SUM = Left->Freq + Right->Freq;
		HuffmanTree.push(CreateNode('\0', SUM, Left, Right));
	}

	Node *Root = HuffmanTree.top();
	unordered_map<char, string> HuffmanCodes;
	Encoding(Root, "", HuffmanCodes);
	cout << endl;
	cout << "Huffman Codes are : " << endl
		 << endl;
	for (auto Pair : HuffmanCodes)
	{
		cout << "\t" << Pair.first << " "
			 << "->"
			 << " " << Pair.second << endl;
	}
	cout << endl;

	string Str = "";
	for (char Ch : Text)
	{
		Str += HuffmanCodes[Ch];
	}

	cout << "Encoded Text is : " << Str << endl
		 << endl;
	int Index = -1;
	cout << "Decoded Text is : ";
	while (Index < int(Str.size()) - 2)
	{
		Decoding(Root, Index, Str);
	}

	cout << endl
		 << endl;
	cout << "Number of bytes in input text"
		 << " "
		 << "="
		 << " " << Text.size() * 8 << endl;
	cout << "Number of bytes in encoded text"
		 << " "
		 << "="
		 << " " << Str.size() << endl;
	cout << "Your files is compressed by"
		 << " " << (((Text.size() * 8) - Str.size()) * 100) / (Text.size() * 8) << "%" << endl
		 << endl;
	cout << "Thank You" << endl;
	cout << "*************************************************************************************************" << endl;
}

int main()
{
	string s = "The quick brown fox jumps over the lazy dog. She sells seashells by the seashore and enjoys eating bananas. Peter Piper picked a peck of pickled peppers. How much wood would a woodchuck chuck if a woodchuck could chuck wood? Betty Botter bought some butter but the butter was bitter. Fuzzy Wuzzy was a bear, Fuzzy Wuzzy had no hair, Fuzzy Wuzzy wasn't very fuzzy, was he? If two witches were watching two watches, which witch would watch which watch? How can a clam cram in a clean cream can?";
	cout << "*************************************************************************************************" << endl
		 << endl;
	cout << "Welcome to file compression" << endl;

	BuildHuffmanTree(s);
	return 0;
}
