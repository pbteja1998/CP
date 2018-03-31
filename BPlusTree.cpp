#include<bits/stdc++.h>
using namespace std;

int n = 3;

struct node {
    vector<int> data;
    vector<struct node*> children;
    bool isLeaf;
    struct node *parent;
    int level;
    node() {
        isLeaf = false;
        parent = NULL;
        level = 0;
    }
};

struct node *root = new node;

void splitInternalNode(struct node *p)
{
    struct node *leftNode = new node;
    struct node *rightNode = new node;
    int x = p->data.size()/2;
    for(int i = 0; i < x; i++) {
        leftNode->data.push_back(p->data[i]);
        leftNode->children.push_back(p->children[i]);
    }
    leftNode->children.push_back(p->children[x]);
    int parent_val = p->data[x];
    for(int i = x + 1; i < p->data.size(); i++) {
        rightNode->data.push_back(p->data[i]);
        rightNode->children.push_back(p->children[i]);
    }
    rightNode->children.push_back(p->children[p->data.size()]);
    struct node *parent = p->parent;
    leftNode->parent = p->parent;
    rightNode->parent = p->parent;
    leftNode->level = p->level;
    rightNode->level = p->level;
    if(parent == NULL) {
        parent = new node;
        parent->data.push_back(parent_val);
        parent->children.push_back(leftNode);
        parent->children.push_back(rightNode);
        leftNode->parent = parent;
        rightNode->parent = parent;
        parent->level = p->level + 1;
        root = parent;        
        return;
    } else {
        vector<struct node*> children; 
        for(int i = 0; i < parent->children.size(); i++) {
            if(parent->children[i] != p) {
                children.push_back(parent->children[i]);                
            } else {
                children.push_back(leftNode);
                children.push_back(rightNode);
            }
        }
        parent->children = children;
        auto it = upper_bound(parent->data.begin(), parent->data.end(), rightNode->data[0]);
        parent->data.insert(it, parent_val);
        if(parent->data.size() <= n)
            return;
        splitInternalNode(parent);
    }
}

void splitLeaf(struct node *p)
{
    struct node *leftNode = new node;
    struct node *rightNode = new node;
    int x = p->data.size() % 2 ? (p->data.size()+1)/2 : p->data.size()/2;    
    leftNode->data.insert(leftNode->data.begin(), p->data.begin(), p->data.begin() + x);
    rightNode->data.insert(rightNode->data.begin(), p->data.begin() + x, p->data.end());
    leftNode->isLeaf = true;
    rightNode->isLeaf = true;
    leftNode->parent = p->parent;
    rightNode->parent = p->parent;
    leftNode->level = p->level;
    rightNode->level = p->level;
    struct node *parent = p->parent;
    if(parent == NULL) {
        parent = new node;
        parent->data.push_back(rightNode->data[0]);
        parent->children.push_back(leftNode);
        parent->children.push_back(rightNode);
        leftNode->parent = parent;
        rightNode->parent = parent;
        parent->level = p->level + 1;
        root = parent;        
        return;        
    } else {
        vector<struct node*> children; 
        for(int i = 0; i < parent->children.size(); i++) {
            if(parent->children[i] != p) {
                children.push_back(parent->children[i]);                
            } else {
                children.push_back(leftNode);
                children.push_back(rightNode);
            }
        }
        parent->children = children;
        auto it = upper_bound(parent->data.begin(), parent->data.end(), rightNode->data[0]);
        parent->data.insert(it, rightNode->data[0]);
        if(parent->data.size() <= n)
            return;
        splitInternalNode(parent);
    }
}

void insert(struct node *p, int val)
{
    if(p->isLeaf) {        
        auto it = upper_bound(p->data.begin(), p->data.end(), val);           
        p->data.insert(it, val);
        if(p->data.size() <= n)
            return;
        splitLeaf(p);
        return;
    }

    for(int i = 0; i < p->data.size(); i++) {
        if(val < p->data[i]){
            insert(p->children[i], val);
            return;
        }            
    }
    insert(p->children[p->data.size()], val);
}

void traverse(struct node *p)
{
    if(p == NULL)
        return;
    cout << endl;
    for(int i = 0; i < p->data.size(); i++) {
        if(!p->isLeaf)
            traverse(p->children[i]);
        cout << " (" << p->data[i] << "," << p->level << ")";
    }
    if(!p->isLeaf)
        traverse(p->children[p->data.size()]);
    cout << endl;
}

bool search(struct node *p, int val)
{   
    if(p == NULL)
        return false;

    if(binary_search(p->data.begin(), p->data.end(), val))
        return true;

    if(p->isLeaf)
        return false;

    for(int i = 0; i <= p->data.size(); i++) {
        if(search(p->children[i], val))
            return true;
    }
    return false;
}

int c = 0;

void count(struct node *p, int val)
{
    if(p->isLeaf) {
        auto it = lower_bound(p->data.begin(), p->data.end(), val);        
        auto it1 = upper_bound(p->data.begin(), p->data.end(), val);
        if(*it == val) {
            c += (it1 - it);
        }
        return;
    }

    bool flag = 0;

    for(int i = 0; i < p->data.size(); i++) {
        if(val < p->data[i]){
            count(p->children[i], val);
            flag = 1;
            break;
        } else if(val == p->data[i]) {
            count(p->children[i], val);
            if(i+1 < p->children.size())
                count(p->children[i+1], val);
            flag = 1;
            break;
        }
    }
    if(flag == 0)
    if(val >= p->data[p->data.size()-1])
        count(p->children[p->data.size()], val);
}

int main()
{    
    root->isLeaf = true;
    int T;
    cin >> T;

    while(T--) {
        string s;
        cin >> s;
        if(s == "INSERT") {
            int x;
            cin >> x;
            insert(root, x);
        } else if(s == "FIND") {
            int x;
            cin >> x;
            if(search(root,x)) {
                cout << "YES" << endl;                
            } else {
                cout << "NO" << endl;
            }
        } else if(s == "COUNT") {
            int x;
            cin >> x;
            c = 0;
            count(root, x);
            cout << c << endl;
        } else if(s == "RANGE") {
            int x, y;
            cin >> x >> y;
            c = 0;
            for(int i = x; i <= y; i++) {
                count(root, i);
            }
            cout << c << endl;
        }
    }

    return 0;
}
