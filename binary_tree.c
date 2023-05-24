#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"
#include <time.h>
#include <string.h>
#include <math.h>

void create_array()
{
    int arr_len = sizeof(bst_array)/sizeof(bst_array[0]);//getting the number of indexes in bst_array
    srand(time(NULL));//setting srand to the time so it is truely random
    int count = 0;
    printf("\narray length:%d", arr_len);

    for(int i = 0; i <= arr_len + 2; i++)
    {
        get_rand(i, bst_array, arr_len);
        count++;
    }
}
int count = 0;  
void get_rand(int i, int* arr, int arr_len)//assigns a unique random integer to the index(i) 
{
    count++;
    int x = 0;
    arr[i] = rand() % (int)sizeof(bst_array); //assigns the random integer the range is proportional to the size of the array for no particular reason

        while(x < i)
        {
            if(arr[i] == arr[x])//checking for uniqueness 
            {
                get_rand(i, arr, arr_len);//if its not uniuqe... RECURSION!
            }else
            {
                x++;
            }
        }
    return;
}

void print_array(int* arr, int arr_len)//prints a formatted version of an array
{
    int count = 0;
    printf("\n[");
    for(int i = 0; i < arr_len - 1; i++)
    {
        if(i >= arr_len -2)//checking for last index for formatings sake
        {
            printf("%d", arr[i]);
        }else
        {
        printf("%d, ", arr[i]);
        }
        count++;
    }
    printf("]%d\n",count);
}

void sort_array(int* arr, int arr_len)
{
    int temp = 0;
    int value = 0;
    int min_index = 0;
    print_array(arr, arr_len);//print before
    for(int i = 0; i < arr_len - 1; i++) //iterate through array
    {
        for(int x = 0; x < arr_len - 1; x++)//iterate each index through the array and test the value
        {
            //this is probably incredebly inefficeint, if you waited to switch the values until you found where the end point for it is
            if(arr[x] > arr[i])//if x > i switch them
            {
                temp = arr[i];
                arr[i] = arr[x];
                arr[x] = temp;
            }
        }
        
    }
    print_array(arr, arr_len);//print after to show difference


}

void build_root(int value, tree_type* bst)
{
    node_type* temp_node = malloc(sizeof(node_type));
    temp_node->data = value;
    bst->root = temp_node;
    bst->root->left = 0L;
    bst->root->right = 0L;
    printf("\nCreated root node, data:%d\n", bst->root->data);
}

void build_node(int value, tree_type* bst)
{
    node_type* on = bst->root;//send pointer into search tree, then edit the data at "on"
    int x = search_tree(value, bst, &on);
    if(x == 1)
    {
        printf("\n%d already exists",value);
    }else if(x == 0)
    {
        node_type* new_node = malloc(sizeof(node_type));
        new_node->data = value;
        if(on->data > value)// values less than parent go to left
        {
            printf("\non data:%d", on->data);
            on->left = new_node;
        }else if(on->data < value)// values greater than parent go to right
        {
            printf("\non data:%d", on->data);
            on->right = new_node;
        }
        new_node->left = 0l;
        new_node->right = 0l;
        printf("\ncreated node with a data value of: %d at %p", new_node->data, new_node);
    }
}

//re-oder starting list based on how far it is from the median value then build tree
void build_tree(int* arr, int arr_len, tree_type* bst)
{
    int denom = 0;
    int temp = 0;
    int count = 0;
    for(int i = 0; i < (sqrt(arr_len))-1; i++)
    {
        printf("\n\ni:%d test:%d\n\n", i, arr_len);
        denom = pow(2, i + 1) ;
        printf("\n\n i = %d denom = %d", i, denom);
        for(int x = 1; x < denom; x = x + 2)//odd numbers only for the numerator so there are no repeating indexes
        {
            if(i == 0)
            {
                printf("\n\n%d/%d building index %d into node %d", x, denom, (arr_len*x)/denom, count);
                build_root(arr[((arr_len/denom)*x)+1], bst); 
                count++;  
            }else
            {
                printf("\n\n%d/%d building index %d into node %d", x, denom, (arr_len*x)/denom, count);
                build_node(arr[((arr_len/denom)*x)-1], bst);
                count++;
                //build node
                //search for node in tree
                //when find null assign left or right to node
                //ASSIGN LEFT AND RIGHT AS NULL YOU NUMB SKULL
                //can iterate through entire tree if you search for each value from 1 to the greatest value which is root->left->left(til null)
            }
        }
        
    }
}

int search_tree(int target_value, tree_type* bst, node_type **output) //searching for a null value where target_value is supposed to be
{
    printf("\n searching tree for %d", target_value);
    node_type *on = bst->root;
    int depth = depth_check(bst);
    for(int i =0; i <= depth; i++)//5 is max depth for this tree change to depth when get depth working
    {
        printf("\non node:%d", on->data);
        if(target_value < on->data)
        {
            //printf("\n %d is less than %d moving left", target_value, on->data);
            if(on->left == 0l)
            {
                printf("\nFound where %d goes, it goes It goes to the left of %d",target_value, on->data);
                printf(" at %p", on);
                return 0;
            }else
            {
                on = on->left;
                *output = on;                
                //printf("\nmoving left");
            }
        }else if(target_value > on->data)
        {
            //printf("\n %d is greater than %d right %p", target_value, on->data, on->right);
            if(on->right == 0l)
            {
                printf("\nFound where %d goes, it goes It goes to the right of %d",target_value, on->data);
                printf(" at %p", on);
                return 0;
            }else
            {
                //printf("\nmoving right");
                on = on->right;
                *output = on;
            }
        } else if(target_value == on->data)
        {
            return 1;//Return 1 when the value is found
        }
    }
}




void remove_node()
{
    //remove a node then call sortTree()
}

int depth_check(tree_type* bst)
{
    int depth = 5;
    int count = 1;
    node_type* on = bst->root;
    int top = find_top(bst);//finds the highest value to search for
    //printf("%p", &on->left);
    //printf("%d", on->data);
    for(int i = 0; i < top; i++)//MAKE IT FIND THE FUCKING VALUE YOU DUMBASS
    {
        //printf("\nsearching for %d", i);
        count = 1;
        on = bst->root;
        //printf("\nDepth:%d", depth);
        for(int x = 0; x < depth; x++)
        {
            if(i < on->data && on->left != 0l)//if on->left is null then it has hit the bottom
            {   
                //printf("\nMoving left, %d nodes deep", count);
                on = on->left;
                count++;
            }else if(i > on->data && on->right != 0l)
            {
                //printf("\nMoving right, %d nodes deep", count);
                on = on->right;
                count++;
            }else if(i  == on->data)
            {
                //printf("\nfound %d at %d nodes deep", i, count);
                break;
            }
        }
        if(count > depth)
        {
            depth = count;
            printf("\nnew deepest:%d", on->data);
        }
    }
    printf("\ndepth:%d", depth);
    return depth;
}

void user_input(tree_type *bst)
{
    int value = 0;
    while(1)
    {
    printf("\nEnter node value:");
    scanf("%d", &value);
    build_node(value, bst);
    }
}

int find_top(tree_type *bst)
{
    int count = 0;
    node_type* on = bst->root;
    while(on->right != 0l)
    {
        count++;
        on = on->right;
    }
    return on->data;
}


int main()
{

    tree_type *bst = malloc(sizeof(tree_type));
    bst->root = 0L;
    printf("\n\n\n\n");
    create_array();
    int arr_len = sizeof(bst_array)/sizeof(bst_array[0]);
    sort_array(bst_array, arr_len);
    build_tree(bst_array, arr_len, bst);

    user_input(bst);
    return 0;
}
