#ifndef __ACSEARCH_H__
#define __ACSEARCH_H__

#include <stdbool.h>
#include "container.h"

/* For Node*/
typedef struct Node {
    char key;
    bool ending;
    int depth;
    struct Node* parent;
    struct Node* failure;
    struct Node* children[256];
} Node;

Node* Node_New();
Node* Node_Get(Node* node, char c);
void Node_Free(Node* node);
/* Node End */

/* For ACSearch */
typedef struct ACSearch {
    Vector* patterns;
    Node* root;
} ACSearch;
ACSearch* ACSearch_New(Vector* patterns);
void ACSearch_Build(ACSearch* search);
Map* ACSearch_FindAll(ACSearch* search, char* text);
/* ACSearch End */
#endif