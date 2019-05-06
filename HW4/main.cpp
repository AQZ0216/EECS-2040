#include <iostream>

using namespace std;

class Tree;

struct Step{
    int xPos;
    int yPos;
    char mark;
};

class TreeNode{
friend class Tree;
private:
    Step data;
    TreeNode* leftChild;
    TreeNode* rightChild;
};

class Tree{
public:
    Tree();
private:
    TreeNode* root;
    void postOrder();
    void Tpo(TreeNode* p);
    void visit(TreeNode* p);
};

int main()
{
    return 0;
}

Tree::Tree(){

}

void Tree::postOrder(){
    Tpo(root);
    return;
}

void Tree::Tpo(TreeNode* p){
    cout << p->data;
    return;
}
