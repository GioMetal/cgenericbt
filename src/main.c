#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

enum data_type
{
    DT_INT,
    DT_FLOAT,
    DT_CHAR,
    DT_STRING
};

typedef struct btree_node_t
{
    void* value;
    unsigned int size;
    unsigned int dataType;
    struct btree_node_t* left;
    struct btree_node_t* right;
} BNODE, *LPBNODE;

typedef struct memory_arena_t
{
    void** data;
    unsigned int count;
} MEMARENA, *LPMEMARENA;

BNODE NodeCreate(void* value, int size, unsigned int dataType,  LPMEMARENA arena)
{
    BNODE n = 
    {
        .value = malloc(size),
        .size = size,
        .left = 0,
        .right = 0,
        .dataType = dataType
    };

    memset(n.value, 0, size);
    memcpy(n.value, value, size);

    arena->data[arena->count] = n.value;
    arena->count++;

    return n;
}

void NodePrint(LPBNODE node)
{
    switch(node->dataType)
    {
        case DT_INT:
        {
            printf("%d\n", *(int*)node->value);
        }
        break;

        case DT_FLOAT:
        {
            printf("%.4f\n", *(float*)node->value);
        }
        break;

        break;

        case DT_CHAR:
        {
            printf("%c\n", *(char*)node->value);
        }
        break;

        case DT_STRING:
        {
            printf("%s\n", (char*)node->value);
        }
        break;
    }
}

void TreePrint(LPBNODE root, int level)
{
    if(!root)
    {
        return;
    }

    int x = 0;
    printf("VALUE: ");
    NodePrint(root); 

    if(root->left)
    {
        for(x = 0; x < level; x++)
        {
            printf("    ");
        }
        printf("LEFT ");
        TreePrint(root->left, level+1);
    }

    if(root->right)
    {
        for(x = 0; x < level; x++)
        {
            printf("    ");
        }
        printf("RIGHT ");
        TreePrint(root->right, level+1);
    }   
}

void BinaryTreeExample()
{
    int arenaSize = 50;
    MEMARENA arena = 
    {
        .data = malloc(sizeof(long long) * arenaSize),
        .count = 0
    };

    int intVal = 56;
    BNODE n1 = NodeCreate(&intVal, 4, DT_INT, &arena);
    BNODE n2 = NodeCreate("Stellaris", strlen("Stellaris") + 1, DT_STRING, &arena);

    char charVal = 'A';
    BNODE n3 = NodeCreate(&charVal, 1, DT_CHAR, &arena);

    float floatVal = 3.14159265f;
    BNODE n4 = NodeCreate(&floatVal, sizeof(float), DT_FLOAT, &arena);
    BNODE n5 = NodeCreate("Lorem Ipsum ecc. ecc.", strlen("Lorem Ipsum ecc. ecc.") + 1, DT_STRING, &arena);

    intVal = 2048;
    BNODE n6 = NodeCreate(&intVal, 4, DT_INT, &arena);
    BNODE n7 = NodeCreate("Parecchio generico", strlen("Parecchio generico") + 1, DT_STRING, &arena);
    BNODE n8 = NodeCreate("Ciao!", strlen("Ciao!") + 1, DT_STRING, &arena);

    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n4;
    n2.right = &n6;
    n4.left = &n5;
    n3.left = &n7;
    n6.left = &n8;

    TreePrint(&n1, 0);

    int i = 0;
    for(; i < arena.count; i++)
    {
        if(arena.data[i])
        {
            free(arena.data[i]);
        }
    }
    if(arena.data)
    {
        free(arena.data);
    }

    return;
}

int main(int argc, char** argv)
{
    BinaryTreeExample();
    printf("\nOK\n");
    return 0;
}