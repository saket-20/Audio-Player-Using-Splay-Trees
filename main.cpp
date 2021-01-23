#include<QCoreApplication>
#include<iostream>
#include<QtMultimedia/QMediaPlayer>
#include<QtMultimedia/QMediaPlaylist>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<string>
#include<QString>
#include<fstream>
#include<queue>
#include<vector>
using namespace std;
//trie
vector<string> string_level_order;
int l;
// trie node
struct NodeT
{
    struct NodeT *cptrs[26];
    int bool_end;//
};




void insert_a_string(struct NodeT *root,string name)
{
                 l=name.length();
    struct NodeT *ptr= root;
int j;
    for (j=0;j<l;j++)
    {int i=-((int)'a'-(int)name[j]);
        if (ptr->cptrs[i]==NULL)
        {NodeT *n=new NodeT;
            n->bool_end=0;

             for (int i1 = 0; i1 < 26; i1++)
                    n->cptrs[i1] = NULL;
            ptr->cptrs[i] =n;
      }

        ptr=ptr->cptrs[i];
    }


    ptr->bool_end=1;
}

int search(struct NodeT *root,string name)
{
     l=name.length();
    struct NodeT *ptr=root;
    for (int j= 0;j<l;j++)
    {
        int i = -((int)'a'-(int)name[j]);
        if (ptr->cptrs[i]==NULL)
            return 0;

        ptr = ptr->cptrs[i];
    }

    return (ptr!=NULL && ptr->bool_end);
}

int isLastNode(struct NodeT* root)
{
    for (int i = 0; i <26; i++)
        if (root->cptrs[i])
            return 0;
    return 1;
}


void autocmp(struct NodeT* root,string pre)
{

    if (root->bool_end)
    {
        cout<<pre<<endl;
    }


    if (isLastNode(root))
        return;

    for (int i = 0; i <26; i++)
    {
        if (root->cptrs[i]!=NULL)
        {
            pre+=(char)(97 + i);
    autocmp(root->cptrs[i],pre);
    pre.pop_back();
        }
    }
}

int sugg(NodeT* root,string str1)
{
    struct NodeT* ptr = root;


    int j;
    l = str1.length();
    for (j= 0;j <l;j++)
    {
        int i = -((int)'a'-(int)str1[j]);


        if (ptr->cptrs[i]==NULL)
        {
           return 0;
}
        ptr = ptr->cptrs[i];
    }
    int word;
    if(ptr->bool_end==1)
   word=1;
    else {word=0;}

    bool isLast = isLastNode(ptr);

    if (word && isLast)
    {
        cout<<str1<<endl;
        return -1;
    }
if (isLast==0)
    {
        string prefix=str1;
        autocmp(ptr, prefix);
        return 1;
    }
}
//splay tree code
struct node
{
    string name;
    string file_path;
    node *left;
    node *right;
};


node *LL(node *a)
{
    node *b=a->left;
    a->left=b->right;
    b->right=a;
    return b;
}


node *RR(node *a)
{
    node *b=a->right;
    a->right=b->left;
    b->left=a;
    return b;
}

node *splay(node *root,string name)
{
    if (root==NULL||root->name == name)
    {
        return root;
}

    if (root->name > name)
    {

        if (root->left == NULL) return root;


        if (root->left->name > name)
        {

            root->left->left = splay(root->left->left, name);

            root = LL(root);
        }
        else if (root->left->name < name)
        {
            root->left->right = splay(root->left->right, name);

            if (root->left->right != NULL)
                root->left = RR(root->left);
        }

if(root->left == NULL) return root;
else return LL(root);
    }
    else
    {

        if (root->right == NULL) return root;


        if (root->right->name > name)
        {

            root->right->left = splay(root->right->left, name);

            if (root->right->left != NULL)
                root->right = LL(root->right);
        }
        else if (root->right->name < name)
        {

            root->right->right = splay(root->right->right, name);
            root = RR(root);
        }

if(root->right==NULL) return root;
else return RR(root);
    }
}

node *insert(node *root,string n,string f)
{

    if (root == NULL)
    {
        node* N=new node;
        N->name=n;
        N->file_path=f;
        N->left=N->right = NULL;
        return N;
    }



    root = splay(root,n);


    if (root->name==n) return root;



    node* Node1=new node;
    Node1->name=n;
    Node1->file_path=f;
    Node1->left = Node1->right = NULL;




    if (root->name>n)
    {
        Node1->right=root;
        Node1->left=root->left;
        root->left=NULL;
    }


    else if(root->name<n)
    {
        Node1->left=root;
        Node1->right=root->right;
        root->right=NULL;
    }

    return Node1;
}
struct node* searchbst(struct node* root, string name)
{
    if(root==NULL||root->name==name)
    {
       return root;
    }
    if (root->name<name)
    {
       return searchbst(root->right,name);
}
    return searchbst(root->left,name);
}
node *search_splay(node *root,string key)
{
    return splay(root, key);
}

void preorder(node *p)
{
    if (p)
    {
        cout<<p->name<<endl<<p->file_path<<endl;
        preorder(p->left);
        preorder(p->right);
    }
}

void levelorder(node *root)
{
    if (root == NULL)  return;
    queue<node *> q;
    q.push(root);

    while (q.empty()==false)
    {
        node *n=q.front();
        //cout<<n->name << " ";
        string_level_order.push_back(n->name);
        q.pop();

        if (n->left != NULL)
          {
            q.push(n->left);
 }
        if (n->right != NULL)
        {
            q.push(n->right);
        }
    }
}
int main(int argc, char *argv[])
{
    /*QMediaPlayer *player;
    QMediaPlaylist *playlist1;
    QCoreApplication a(argc, argv);
    player = new QMediaPlayer;
    playlist1 = new QMediaPlaylist(player);

    QString qstr = QString::fromStdString(str);
     playlist1->addMedia(QUrl::fromLocalFile(qstr));
    //playlist1->setCurrentIndex(1);

    player->setPlaylist(playlist1);

    player->setVolume(50);

    player->play();
return a.exec();*/
    QMediaPlayer *player;
        QMediaPlaylist *playlist1;
        player = new QMediaPlayer;
        playlist1 = new QMediaPlaylist(player);
    QCoreApplication a(argc, argv);
    struct NodeT* root;
    struct NodeT *N= new NodeT;
    N->bool_end = false;

    for (int i = 0;i<26; i++)
    {
        N->cptrs[i] = NULL;
}
    root=N;
    fstream in;
    char str[255];
    in.open("/Users/saket/Desktop/DS_Splay_pack/songs.txt", ios::in);
    while(in)
       {
           in.getline(str,255);
           for(int i=0;i<strlen(str);i++)
           {
               if(str[i]==' '||str[i]=='-') str[i]='Z';
           }
           cout<<str<<endl;
           if(in) insert_a_string(root,str);
       }
    node *root_splay=NULL;
        fstream in1;
       in1.open("/Users/saket/Desktop/DS_Splay_pack/songs.txt", ios::in);
        char string1[255];
        char string2[255];
        fstream in2;
        // QCoreApplication a(argc, argv);
        in2.open("/Users/saket/Desktop/DS_Splay_pack/songs2.txt",ios::in);


        while(in1&&in2)
        {
            in1.getline(string1,255);
             in2.getline(string2,255);
            root_splay=insert(root_splay,string1,string2);
        }
\
        in1.close();
        in2.close();
        cout<<"Preorder Traversal \n";
        //perform a level order traversal

        preorder(root_splay);
        cout<<"Enter the number of songs desired in the playlist\n";
        int n;
        cin>>n;
        int iter;
        string s;
        string songname;
        for(iter=0;iter<n;iter++)
        {
            cout<<"Enter the name of the song or its prefix\n";
            cin>>s;
            cout<<"Songs Currently Available in Memory\n";
            int comp = sugg(root,s);
            if (comp == -1)
                    cout << "No other strings found with this prefix\n";

                else if (comp == 0)
                    cout << "No string found with this prefix\n";
            cout<<"Enter the full song name based on the suggestions given above\n";
            cin>>songname;
            root_splay=search_splay(root_splay,songname);
            cout<<"File location obtained from splay tree\n:";
            cout<<root_splay->file_path<<endl;
            QString qstr = QString::fromStdString(root_splay->file_path);
            playlist1->addMedia(QUrl::fromLocalFile(qstr));
        }
        playlist1->setCurrentIndex(1);
        cout<<"Level Order Traversal with topmost nodes printed first\n";
        levelorder(root_splay);
        int v;
        cout<<"Level Order Traversal with 5 topmost nodes printed(These are the recently accessed ones since they are near the top of the tree\n";
        for(v=0;v<3;v++)
        {
            cout<<string_level_order[v]<<" ";
        }
 cout<<"Currently Playing Audio!!\n";
            player->setPlaylist(playlist1);

            player->setVolume(50);

            player->play();

            return a.exec();
}
