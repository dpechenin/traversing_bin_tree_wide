#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} tree;

typedef struct Node {
    tree* data;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *first;
    Node *last;
} Queue;


tree* addEl(tree *p, int v) {
    if (p == NULL) {
        p = (tree*)malloc(sizeof(tree));
        p->value = v;
        p->right = p->left = NULL;
    }
    else if (v < p->value) {
        p->left = addEl(p->left, v);
    }
    else {
        p->right = addEl(p->right, v);
    }
    return p;
}

void freeTree(tree *p) {
    if(p != NULL) {
        freeTree(p->left);
        freeTree(p->right);
        free(p);
    }
}

Queue *enqueue(Queue *q, tree* point) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = point;
    node->next = NULL;
    if (q == NULL || (q->first == NULL && q->last == NULL)) {
        Queue *q = (Queue*)malloc(sizeof(Queue));
        q->first = node;
        q->last = node;
        return q;
    }
    Node* tmp = q->last;
    tmp->next = node;
    q->last = node;
    return q;
}

tree* dequeue(Queue* q){
    if(q == NULL)
        return NULL;
    if(q->first == q->last) {
        tree* point = q->first->data;
        q->first = NULL;
        q->last = NULL;
        return point;
    }
    tree* point = q->first->data;
    Node* tmp = q->first;
    q->first = q->first->next;
    tmp->next = NULL;
    free(tmp);
    return point;
}

void treeprint(tree *p) {
    if(p != NULL) {
        treeprint(p->left);
        printf("%d\n", p->value);
        treeprint(p->right);
    }
}

int empty(Queue* q){
    if(q->first == NULL)
        return 0;
    return 1;
}

int main(void) {
    tree* root=NULL;
    Queue *q=NULL;
    int a[]={10, 34, 2, 6, 1, 8, 3, 11, 12, 5};
    for (int i = 0; i<10; ++i) {
        root = addEl(root, a[i]);
    }
    printf("tree:\n");
    treeprint(root);
    q = enqueue(q, root);        // корень в очередь
    while (empty(q))
    {
         tree* x = dequeue(q);
         printf("%d ", x->value);              // посетить узел дерева
         if (x->left != NULL)   // левое поддерево
              q = enqueue(q, x->left);
         if (x->right != NULL)  // правое поддерево
              q = enqueue(q, x->right);
    }
    
    freeTree(root);
    return 0;
}
