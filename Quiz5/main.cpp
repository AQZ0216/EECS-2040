#include <iostream>

using namespace std;

class Tree;

class TreeNode {
friend class Tree;
public:
    TreeNode();
    TreeNode(int frequency, char c);
private:
    int freq;
    char character;
    string encode;
    TreeNode* leftChild;
    TreeNode* rightChild;
};

class Tree {
public:
    Tree();
    Tree(Tree* leftTree, int freq, char character, Tree* rightTree);
    void buildHuffmanTree(int* freq, char* character, int cnt);
    void encode(TreeNode* p);
    void result(string word);
private:
    TreeNode* root;
    void decode(char c, TreeNode* p);
};

void Merge(int* a, char* charA, int first, int m, int last) {
    int idxL = 0;
    int idxR = 0;

    int* left = new int[m+1-first];
    char* charL = new char[m+1-first];
    int* right = new int[last-m];
    char* charR = new char[last-m];

    copy(a+first, a+m+1, left);
    copy(charA+first, charA+m+1, charL);
    copy(a+m+1, a+last+1, right);
    copy(charA+m+1, charA+last+1, charR);

    int i;
    for(i = first; i <= last && idxL != m+1-first && idxR != last-m; i++) {
       if(left[idxL] <= right[idxR]) {
            a[i] = left[idxL];
            charA[i] = charL[idxL];
            idxL++;
        } else {
            a[i] = right[idxR];
            charA[i] = charR[idxR];
            idxR++;
        }
    }

    copy(left+idxL, left+m+1-first, a+i);
    copy(charL+idxL, charL+m+1-first, charA+i);
    copy(right+idxR, right+last-m, a+i);
    copy(charR+idxR, charR+last-m, charA+i);
    return;
}

void MergeSort(int* a, char* charA, int first, int last) {
    if(first < last) {
        int m = (first + last)/2;
        MergeSort(a, charA, first, m);
        MergeSort(a, charA, m+1, last);
        Merge(a, charA, first, m, last);
    }
    return;
}

int check(char c, char* a, int n) {
    for(int i = 1; i <= n; i++) {
        if(c == a[i])
            return i;
    }
    return 0;
}

int main()
{
    int n;
    char comma;
    string word;

    cin >> n;
    cin >> comma;
    getline(cin, word);

    string *text;
    text = new string[n];

    for(int i = 0; i < n; i++) {
        getline(cin, text[i]);
    }

    char character[27];
    int freq[27];
    int cnt = 0;
    int index;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < text[i].length(); j++) {
            if(text[i][j] != ' ') {
                index = check(text[i][j], character, cnt);

                if(index == 0) {
                    cnt++;
                    character[cnt] = text[i][j];
                    freq[cnt] = 1;
                } else {
                    freq[index]++;
                }
            }
        }
    }

    MergeSort(freq, character, 1, cnt);

    for(int i = 1; i <= cnt ; i++) {
        for(int j = 0; j < word.length() ; j++) {
	    if(character[i] == word[j])
		cout << word[j];
	}
    }
    cout << endl;    

    return 0;
}

TreeNode::TreeNode(){
    freq = 0;
    character = ' ';
    encode = "";
    leftChild = 0;
    rightChild = 0;
}

TreeNode::TreeNode(int frequency, char c){
    freq = frequency;
    character = c;
    encode = "";
    leftChild = 0;
    rightChild = 0;
}

Tree::Tree(){
    root = new TreeNode();
}

Tree::Tree(Tree* leftTree, int freq, char character, Tree* rightTree){
    root = new TreeNode(freq, character);
    root->leftChild = leftTree->root;
    root->rightChild = rightTree->root;
}

void Tree::buildHuffmanTree(int* freq, char* character, int cnt) {
    int index = 1;

    int nodeFreq[26];
    Tree* node[26];
    int nodeCnt = 0;
    int nodeIndex = 1;

    while(index != cnt+1 || nodeIndex != nodeCnt) {
        if(nodeCnt == 0 || (index < cnt && freq[index] <= nodeFreq[nodeIndex] && freq[index+1] <= nodeFreq[nodeIndex]) ) {
            Tree* left = new Tree();
            Tree* right = new Tree();;
            left->root = new TreeNode(freq[index], character[index]);
            right->root = new TreeNode(freq[index+1], character[index+1]);

            nodeCnt++;
            nodeFreq[nodeCnt] = freq[index]+freq[index+1];
            node[nodeCnt] = new Tree(left, nodeFreq[nodeCnt], ' ', right);
            index+=2;
        } else if(index == cnt+1 || (nodeIndex < nodeCnt && freq[index] > nodeFreq[nodeIndex] && freq[index] > nodeFreq[nodeIndex+1]) ) {
            nodeCnt++;
            nodeFreq[nodeCnt] = nodeFreq[nodeIndex]+nodeFreq[nodeIndex+1];
            node[nodeCnt] = new Tree(node[nodeIndex], nodeFreq[nodeCnt], ' ', node[nodeIndex+1]);
            nodeIndex+=2;
        } else if(index <= cnt && freq[index] <= nodeFreq[nodeIndex]) {
            Tree* left = new Tree();;
            left->root = new TreeNode(freq[index], character[index]);

            nodeCnt++;
            nodeFreq[nodeCnt] = freq[index]+nodeFreq[nodeIndex];
            node[nodeCnt] = new Tree(left, nodeFreq[nodeCnt], ' ', node[nodeIndex]);
            index++;
            nodeIndex++;
        } else {
            Tree* right = new Tree();;
            right->root = new TreeNode(freq[index], character[index]);

            nodeCnt++;
            nodeFreq[nodeCnt] = freq[index]+nodeFreq[nodeIndex];
            node[nodeCnt] = new Tree(node[nodeIndex], nodeFreq[nodeCnt], ' ', right);
            index++;
            nodeIndex++;
        }
    }

    root = node[nodeCnt]->root;
}

void Tree::encode(TreeNode* p) {
    if(p->leftChild != 0) {
        p->leftChild->encode = p->encode + "0";
        encode(p->leftChild);
    }
    if(p->rightChild != 0) {
        p->rightChild->encode = p->encode + "1";
        encode(p->rightChild);
    }
    return;
}

void Tree::result(string word){
    encode(root);

    for(int i = 0; i < word.length(); i++) {
        decode(word[i], root);
    }
    cout << endl;
    return;
}

void Tree::decode(char c, TreeNode* p) {
    if(c == p->character) {
        cout << p->encode;
    }
    if(p->leftChild != 0) {
        decode(c, p->leftChild);
    }
    if(p->rightChild != 0) {
        decode(c, p->rightChild);
    }

    return;
}

