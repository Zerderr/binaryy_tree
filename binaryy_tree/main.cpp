#include <iostream>
#include <string>
using namespace std;
int i = 0;
int maxt[20];
int maxlevel = 0;
int level_mass[20];
int data[16] = { 200, 7,8 ,90, 9, 1000, 311, 12, 13, 14,1500, 52, 33, 4700, 96};
struct node{
        int key;
        node * left;
        node * right;
        int seen;
};
string dec2bin(int num, int level)
{
    string bin = "";int k = 1;
    while (num)
    {
        bin = (char ('0'+ num % 2))+bin;
        num /= 2;
    }
    while (bin.length()< level){
        bin = "0"+bin;
    }
    return bin;
}

node * maketree(int data[], int from, int n){
    node *tree;
    int n1; int n2;
    if(n== 0) return NULL;
    tree = new node;
    tree->key= data[from];
    n1 = n/2;
    n2 = n-n1-1;
    tree->left = maketree(data, from+1, n1);
    tree->right = maketree(data, from+1+n1, n2);
    return tree;
}
void treeprint(node * root, int space ) {
    if (!root)
        return;
    int COUNT = 2 ;
    space += COUNT;
    treeprint(root->right, space);
    for (int i = COUNT; i < space; ++i)
        std::cout << "  ";
    std::cout << root->key << std::endl;
    treeprint(root->left, space);
}
void mirror1(node * root){
    node * tmp = root->left;
    root->left = root->right;
    root->right = tmp;
}
void del(node * root){
    if(!root) return;

    del(root->left);
    delete root;
    return;
    del(root->right);
}
int level1=0;
void walkTree(node* t, int level)
{
    if (t == NULL) return;
    maxlevel += t->key;
    if (t->left == NULL and t->right == NULL ) {
        maxt[i] = maxlevel;
        level_mass[i] = level;

        if(level > level1) level1 = level;
        i++;
    }
    t->seen =1;
    walkTree(t->left, level + 1);
    if(t->left == NULL and t->right == NULL) {maxlevel -= t->key;t->seen = 2;}
    if (t->left!= NULL)if(t->left->seen == 1) maxlevel-=t->left->key;
    if(t->key == 1) maxlevel = 1;
    walkTree(t->right, level + 1);
}
int main() {
    int n = sizeof(data)/sizeof(int)-1;
    int level;
    node * tree;
    tree = maketree(data, 0, n);
    node * t2 = tree;
    treeprint(tree, 0);
    walkTree(t2, 0);
    int amax = maxt[0];
    for(int i = 0; i < 15; i++){
        if (maxt[i] > amax) amax = maxt[i];
    }
    for(int i = 0; i < 20; i++){
        if (maxt[i] == amax) {
            amax = i;
            break;
        }
    }
    string binary = "";
    cout << " Maximalniy put: ";
    level1 = level_mass[amax];
    binary =  dec2bin(amax, level1);
    node * tree1 = tree;
    for(int i = 0; i < level1+1; i++){
        cout << tree->key<< " ";
        if(binary[i] == '1') tree = tree->right;
        else{
            tree = tree->left;
        }
    }
    node * tree2 = tree1;
    for(int i = 0; i < level1; i++){
        mirror1(tree1);
        if(binary[i] == '1') tree1 = tree1->left;
        else{
            tree = tree1->right;
        }
    }
    cout << endl;
    treeprint(tree2, 0);
    cout <<"level " << level1;
    del(tree);
    return 0;
}
