#include <iostream>

using namespace std;

class Tree;

struct Step{
    int ID;
    int xPos;
    int yPos;
    char mark;
};

class TreeNode{
friend class Tree;
public:
    TreeNode();
    TreeNode(int ID, int xPos, int yPos, char mark);
private:
    Step data;
    TreeNode* leftChild;
    TreeNode* rightChild;
};

class Tree{
public:
    Tree();
    Tree(Tree* leftTree, Step data, Tree* rightTree);
    void insertNode(int ID, int parentID, int xPos, int yPos, char mark);
    void result();
private:
    TreeNode* root;
    bool winOrTie;
    void Tpo(TreeNode* p);
    void visit(TreeNode* p);
    TreeNode* findID(int ID, TreeNode* p);
    char** mapping(char** path, TreeNode* p);
    bool win(char** path);
    void print(char** path);
};

int main()
{
    int n;
    cin >> n;

    int ID;
    int parentID;
    int xPos;
    int yPos;
    char mark;

    Tree* ticTacToe = new Tree();
    for(int i = 0; i < n; i++){
        cin >> ID;
        cin >> parentID;
        cin >> xPos;
        cin >> yPos;
        cin >> mark;

        ticTacToe->insertNode(ID, parentID, xPos, yPos, mark);
    }

    ticTacToe->result();

    return 0;
}

TreeNode::TreeNode(){
    data.ID = 0;
    data.xPos = 0;
    data.yPos = 0;
    data.mark = '_';

    leftChild = 0;
    rightChild = 0;
}

TreeNode::TreeNode(int ID, int xPos, int yPos, char mark){
    data.ID = ID;
    data.xPos = xPos;
    data.yPos = yPos;
    data.mark = mark;

    leftChild = 0;
    rightChild = 0;
}

Tree::Tree(){
    TreeNode* root = new TreeNode();
    winOrTie == false;
}

Tree::Tree(Tree* leftTree, Step data, Tree* rightTree){
    TreeNode* root = new TreeNode();
    root->data = data;
    root->leftChild = leftTree->root;
    root->rightChild = rightTree->root;
    winOrTie == false;
}

void Tree::insertNode(int ID, int parentID, int xPos, int yPos, char mark){
    TreeNode* newNode = new TreeNode(ID, xPos, yPos, mark);

    if(parentID == -1){
        root = newNode;
        return;
    }

    TreeNode* parent = findID(parentID, root);

    if(parent->leftChild == 0)
        parent->leftChild = newNode;
    else if(parent->rightChild == 0)
        parent->rightChild = newNode;
    return;
}

void Tree::result(){
    char** path = new char*[3];
    for(int i = 0; i < 3; i++){
        path[i] = new char[3];
        for(int j = 0; j < 3; j++){
            path[i][j] = '_';
        }
    }

    mapping(path, root);

    if(winOrTie == false){
        cout << "Tie" << endl;
        Tpo(root);
    }

    return;
}

void Tree::Tpo(TreeNode* p){
    if(p->leftChild != 0)
        Tpo(p->leftChild);
    if(p->rightChild != 0)
        Tpo(p->rightChild);
    visit(p);
    return;
}

void Tree::visit(TreeNode* p){
    cout << p->data.xPos << " ";
    cout << p->data.yPos << " ";
    cout << p->data.mark << endl;
    return;
}

TreeNode* Tree::findID(int ID, TreeNode* p){
    TreeNode* temp;

    if(p->data.ID == ID)
        return p;

    if(p->leftChild != 0){
        temp = findID(ID, p->leftChild);
        if(temp)
            return temp;
    }
    if(p->rightChild != 0){
        temp = findID(ID, p->rightChild);
        if(temp)
            return temp;
    }
    return 0;
}

char** Tree::mapping(char** path, TreeNode* p){
    path[p->data.yPos][p->data.xPos] =  p->data.mark;

    if(win(path)) {
        winOrTie = true;
        print(path);
    } else {
        if(p->leftChild != 0)
            path = mapping(path, p->leftChild);
        if(p->rightChild != 0)
            path = mapping(path, p->rightChild);
    }

    path[p->data.yPos][p->data.xPos] = '_';
    return path;
}

bool Tree::win(char** path){
    char mark;

    // column
    for(int i = 0; i < 3; i++){
        mark = path[0][i];
        if(mark != '_'){
            for(int j = 0; j < 3 ; j++){
                if(mark != path[j][i] )
                    break;
                if(j == 2)
                    return true;
            }
        }
    }

    // row
    for(int i = 0; i < 3; i++){
        mark = path[i][0];
        if(mark != '_'){
            for(int j = 0; j < 3 ; j++){
                if(mark != path[i][j] )
                    break;
                if(j == 2)
                    return true;
            }
        }
    }

    mark = path[0][0];
    if(mark != '_'){
        for(int i = 0; i < 3; i++){
            if(mark != path[i][i] )
                break;
            if(i == 2)
                return true;
        }
    }

    mark = path[0][2];
    if(mark != '_'){
        for(int i = 0; i < 3; i++){
            if(mark != path[i][2-i] )
                break;
            if(i == 2)
                return true;
        }
    }
    return false;
}

void Tree::print(char** path){
    cout << "Win" << endl;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            cout << path[i][j];
            if(j == 2)
                cout << endl;
            else
                cout << " ";
        }
    }
    return;
}
