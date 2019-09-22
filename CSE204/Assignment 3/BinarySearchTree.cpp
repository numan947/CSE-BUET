#include<stdio.h>
#include<stdlib.h>
#define dbg(x) printf("PING AT %d\n",x)
#define FALSE_VALUE 0
#define TRUE_VALUE 1

#include<bits/stdc++.h>
using namespace std;

struct treeNode
{
    int item;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
};

struct treeNode * root;


void initializeTree()
{
    root = 0;
}


struct treeNode * searchItem(struct treeNode * node, int item)
{
    if(node==0) return 0;
    if(node->item==item) return node; //found, return node
    struct treeNode * t = 0;
    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree
    return t;
};


struct treeNode * makeTreeNode(int item)
{
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->left = 0;
    node->right = 0;
    return node;
};

struct treeNode * insertItem(struct treeNode * node, int item)
{
    if(node==0) //insert as the root as the tree is empty
    {
        struct treeNode * newNode = makeTreeNode(item);
        root = newNode;
        return newNode;
    }

    if(node->item==item) return 0; //already an item exists, so return NULL

    if(item<node->item && node->left==0) //insert as the left child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        //printf("%d is inserted as left\n",node->item);
        return newNode;
    }

    if(item>node->item && node->right==0) //insert as the right child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        //printf("%d is inserted as right\n",node->item);
        return newNode;
    }

    if(item<node->item)
        return insertItem(node->left, item); //insert at left sub-tree
    else
        return insertItem(node->right, item); //insert at right sub-tree
}



int calcNodeHeight(struct treeNode * node) //return height of a node
{
    if(node==0) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);
    if(l>r) return l+1;
    else return r+1;
}


int calcHeight(int item) //return height of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==0) return -1; //not found
    else return calcNodeHeight(node);
}

int getSize(struct treeNode * node)
{
    if(node==0)return 0;
    int lTree=getSize(node->left);
    int rTree=getSize(node->right);
    return lTree+rTree+1;
}

int calcNodeDepth(struct treeNode * node) //return depth of a node
{
    //write your codes here
    struct treeNode* temp=root;
    int depth=0;

    while(temp->item!=node->item){
        if(temp->item>node->item)temp=temp->left;
        else temp=temp->right;
        depth++;
    }
    return depth;
}


int calcDepth(int item)//return depth of an item in the tree
{
    //write your codes here

    struct treeNode* node=searchItem(root,item);
    if(node==0)return -1;//not found
    return calcNodeDepth(node);
}

struct treeNode* findsuccessor(struct treeNode * node, int item)
{
    //otherwise, go to right child, and then all left children
    struct treeNode * success, * t;
    if( node->right != 0 ){
        success = node->right ;
        while( success->left!=0 )
        success = success->left ;
        return success ;
    }
    else{
        //search the item, during searching, track the successor
        success = 0 ;
        t = root ;
        while( t!= 0 ){
            if (node->item == t->item ) return success ;
            else if (node->item < t->item ){
                success = t ;
                t = t->left ;
            }
            else t = t->right ;
        }
    }
    return 0;
}




/*
struct treeNode* deleteNode(struct treeNode* node, int item)//searching and deleting at the same function
{
    if (node==0) return node;

    if (item<node->item)node->left=deleteNode(node->left, item);

    else if (item>node->item)node->right=deleteNode(node->right, item);

    else{
        if (node->left==0){

            struct treeNode *temp=node->right;
            free(node);
            return temp;

        }
        else if (node->right==0){
            struct treeNode *temp=node->left;
            free(node);
            return temp;
        }

        struct treeNode* temp=findsuccessor(node,item);
        node->item=temp->item;
        node->right=deleteNode(node->right,temp->item);
    }
    return node;
}
*/


int deleteItem(struct treeNode * node, int item)
{
   //code for delete operation
    if(searchItem(root,item)==0)return FALSE_VALUE;

    struct treeNode* prev;
    struct treeNode* now;

    now=root;

    while(now->item!=item){
        prev=now;
        if(item<now->item){
        now=now->left;
    }
        else{
            now=now->right;
        }
    }
    //SPACE FOR ROOT
    if(now==root){

        if(now->left==0&&now->right==0){
            free(now);
            root=0;
        }
        else if(now->left==0){

            struct treeNode* temp;
            temp=root->right;
            free(root);
            root=temp;
        }
        else if(now->right==0){
            struct treeNode* temp;
            temp=root->left;
            free(root);
            root=temp;
        }
        else{
            struct treeNode* succ=findsuccessor(now,item);
            struct treeNode*temp,*prevsucc;
            temp=root;

            while(temp->item!=succ->item){
                prevsucc=temp;
                if(succ->item<temp->item){
                    temp=temp->left;
                }
                else{
                    temp=temp->right;
                }
            }
            int tmp=succ->item;
            succ->item=now->item;
            now->item=tmp;
            //swap(succ->item,now->item);
            if(temp->left==0&&temp->right==0){
                if(prevsucc->left==temp){
                prevsucc->left=0;
                free(temp);
            }
                else{
                    prevsucc->right=0;
                    free(temp);
                }
            }
            else if(temp->left==0){
                struct treeNode* mem;
                if(prevsucc->left==temp){
                    mem=temp->right;
                    free(temp);
                    prevsucc->left=mem;
                }
                else {
                    mem=temp->right;
                    free(temp);
                    prevsucc->right=mem;
                }
            }
            else if(temp->right==0){
                struct treeNode* mem;
                if(prevsucc->left==temp){
                    mem=temp->left;
                    free(temp);
                    prevsucc->left=mem;
                }
                else {
                    mem=temp->left;
                    free(temp);
                    prevsucc->right=mem;
                }
            }
        }
    }

    else if(now->left==0&&now->right==0){
        if(prev->left==now){
            prev->left=0;
            free(now);
        }
        else {
            prev->right=0;
            free(now);
        }
    }
    else if(now->left==0){
        struct treeNode* temp;
        if(prev->left==now){
            temp=now->right;
            free(now);
            prev->left=temp;
        }
        else {
            temp=now->right;
            free(now);
            prev->right=temp;
        }
    }
    else if(now->right==0){
        struct treeNode* temp;
        if(prev->left==now){
            temp=now->left;
            free(now);
            prev->left=temp;
        }
        else {
            temp=now->left;
            free(now);
            prev->right=temp;
        }
    }
    else{
        struct treeNode* succ=findsuccessor(now,item);
        struct treeNode*temp,*prevsucc;
        temp=root;

        cout<<succ->item<<endl;
       // dbg(120);
        while(temp->item!=succ->item){
            prevsucc=temp;
            if(succ->item<temp->item){
                temp=temp->left;
            }
            else{
                temp=temp->right;
            }
            //dbg(1112);
        }
        int tmp=succ->item;
        succ->item=now->item;
        now->item=tmp;
        //dbg(99);
        //swap(succ->item,now->item);
        if(temp->left==0&&temp->right==0){
            if(prevsucc->left==temp){
            prevsucc->left=0;
            free(temp);
        }
            else{
                prevsucc->right=0;
                free(temp);
            }
        }
        else if(temp->left==0){
            struct treeNode* mem;
            if(prevsucc->left==temp){
                mem=temp->right;
                free(temp);
                prevsucc->left=mem;
            }
            else {
                mem=temp->right;
                free(temp);
                prevsucc->right=mem;
            }
        }
        else if(temp->right==0){
            struct treeNode* mem;
            if(prevsucc->left==temp){
                mem=temp->left;
                free(temp);
                prevsucc->left=mem;
            }
            else {
                mem=temp->left;
                free(temp);
                prevsucc->right=mem;
            }
        }
    }
    return TRUE_VALUE;
}



int getMinItem() //returns the minimum item in the tree
{
    //write your codes here
    if(root==NULL){
        cout<<"Tree is empty"<<endl;
        return FALSE_VALUE;
    }
    struct treeNode* node=root;
    int mini=node->item;
    while(node!=0){
        mini=node->item;
        node=node->left;
    }
    return mini;
}

int getMaxItem() //returns the maximum item in the tree
{
    //write your codes here
    if(root==NULL){
        cout<<"Tree is empty"<<endl;
        return FALSE_VALUE;
    }
    struct treeNode* node=root;
    int maxi=node->item;
    while(node!=0){
        maxi=node->item;
        node=node->right;

    }
    return maxi;
}

int rangeSearch(struct treeNode * node, int leftBound, int rightBound) //returns number of items in the
{
    //write your codes here
    if(node==0)return 0;
    int l=0,r=0;
    if(node->item>leftBound)l=rangeSearch(node->left,leftBound,rightBound);
    if(node->item<rightBound)r=rangeSearch(node->right,leftBound,rightBound);
    if(node->item>=leftBound&&node->item<=rightBound)return 1+l+r;
    else return l+r;
}


void printInOrder(struct treeNode * node, int height)
{
    if(node==0) return ;
   // printf("NOW NODE IS %d\n",node->item);
    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0;i<height;i++)printf("   ");
    printf("%03d\n",node->item);

    //print right sub-tree
    printInOrder(node->right, height-1);
}


///ONLINE
int findLCA(struct treeNode* node,int item1,int item2)
{
    struct treeNode* temp=node;
    while(1){
        if(searchItem(temp->left,item1)!=0&&searchItem(temp->right,item2)!=0)break;//THIS IS LCA
        else if(searchItem(temp->left,item1)!=0&&searchItem(temp->left,item2)!=0)temp=temp->left;
        else if(searchItem(temp->right,item1)!=0&&searchItem(temp->right,item2)!=0)temp=temp->right;
    }
    return temp->item;
}

struct treeNode* findParent(int item)
{
    struct treeNode*tmp1,*tmp2,*tmp3;
    tmp1=root;
    while(tmp1->item!=item){
        tmp2=tmp1;
        if(item<tmp1->item)tmp1=tmp1->left;
        else tmp1=tmp1->right;
    }
    return tmp2;
};
int normalDelete(int item)
{
    struct treeNode*tmp1,*tmp2,*tmp3;
    tmp1=searchItem(root,item);
    if(tmp1==0)return FALSE_VALUE;
    tmp2=findParent(item);

    if(tmp1->left!=0&&tmp1->right!=0){
        tmp3=findsuccessor(tmp1,tmp1->item);
        int ttt=tmp3->item;
        normalDelete(ttt);
        tmp1->item=ttt;
        return TRUE_VALUE;
    }
    else if(tmp1->left==0){
        if(tmp2->left==tmp1){
            tmp2->left=tmp1->right;
        }
        else tmp2->right=tmp1->right;

        free(tmp1);
        return TRUE_VALUE;
    }
    else{
        if(tmp2->left==tmp1)tmp2->left=tmp1->left;
        else tmp2->right=tmp1->left;
        free(tmp1);
        return TRUE_VALUE;
    }
}
int rootDelete()
{
    struct treeNode*tmp1,*tmp2,*tmp3;

    if(root->left==0){
        tmp1=root;
        root=root->right;
        free(tmp1);
        return TRUE_VALUE;
    }

    else if(root->right==0){
        tmp1=root;
        root=root->left;
        free(tmp1);
        return TRUE_VALUE;
    }
    else{
        tmp1=findsuccessor(root,root->item);
        int ttt=tmp1->item;
        normalDelete(ttt);
        root->item=ttt;
        return TRUE_VALUE;
    }
}
int DELETE(int item)
{
    struct treeNode*tmp1,*tmp2,*tmp3;
    tmp1=searchItem(root,item);
    if(tmp1==root)rootDelete();
    else normalDelete(item);
}





int main(void)
{
    initializeTree();
    while(1)
    {
        printf("1. Insert item. 2. Delete item. 3. Search item. \n");
        printf("4. Print height of tree. 5. Print height of an item. \n");
        printf("6. PrintInOrder.7.calcDepth of an item 8. getsize of tree. 9.get minimum item 10.get maximum item\n");
        printf("11.range Search[left,right] 12.ONLINE LCA() 13.exit\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(root, item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            //deleteItem(root, item);
            DELETE(item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int height = calcNodeHeight(root);
            printf("Height of tree = %d\n", height);
        }
        else if(ch==5)
        {
            int item;
            scanf("%d", &item);
            int height = calcHeight(item);
            printf("Height of %d = %d\ns", item, height);
        }
        else if(ch==6)
        {
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
        else if(ch==7){
            int item;
            scanf("%d",&item);
            printf("%d\n",calcDepth(item));
        }
        else if(ch==8)
        {
            cout<<getSize(root)<<endl;
        }

        else if(ch==9)
        {
            cout<<getMinItem()<<endl;
        }
        else if(ch==10){
            cout<<getMaxItem()<<endl;
        }
        else if(ch==11){
            int l,r;
            cin>>l>>r;
            cout<<rangeSearch(root,l,r)<<endl;
        }
        else if(ch==12){
            int item1,item2;
            cin>>item1>>item2;
            cout<<findLCA(root,item1,item2)<<endl;
        }
        else if(ch==13)break;
    }
}
