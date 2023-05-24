#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED

#ifndef ERROR
#define ERROR -1
#endif // ERROR

typedef struct node
    {
        int data;
        struct node* left;
        struct node* right;
    }node_type;

typedef struct tree
    {
        struct node* root;
    }tree_type;


int bst_array[31];

node_type find_base();
char* search_tree(char*);
void traverse_tree();
void sort_tree();
void remove_node();
int depth_check();
void create_array();
void print_array(int* arr, int arr_len);
void sort_array(int* arr, int arr_len);
int get_rand(int i, int* arr, int arr_len);
void build_tree(int* arr, int arr_len, tree_type* bst);
void build_root(int value, tree_type* bst);
void build_node(int value, tree_type* bst);



#endif // BINARYTREE_H_INCLUDED
