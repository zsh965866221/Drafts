#include "ACSearch.h"

#include <stdio.h>
#include <stdlib.h>

/* For Node*/
Node* Node_New() {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = ' ';
    node->ending = false;
    node->depth = 0;
    node->parent = NULL;
    node->failure = NULL;
    for (int i=0; i<256; i++) {
        node->children[i] = NULL;
    }
    return node;
}

Node* Node_Get(Node* node, char c) {
    unsigned char index = (unsigned char)c;
    return node->children[index];
}

void Node_Free(Node* node) {
    for (int i=0; i<256; i++) {
        Node* c = node->children[i];
        if (c != NULL) {
            Node_Free(c);
            c = NULL;
        }
    }
    free(node);
}
/* Node End */

/* For ACSearch */
ACSearch* ACSearch_New(Vector* patterns) {
    ACSearch* search = (ACSearch*) malloc(sizeof(ACSearch));
    search->patterns = patterns;
    search->root = Node_New();
    ACSearch_Build(search);
    return search;
}
void ACSearch_Build(ACSearch* search) {
    for (int i=0; i<search->patterns->size; i++) {
        Node* p = search->root;
        char* pattern = (char*)Vector_Get_Index(search->patterns, i);
        char* pchar = pattern;
        int depth = 1;
        while (*pchar != '\0') {
            char c = *pchar;
            unsigned char uc = (unsigned char) c;
            if (p->children[uc] == NULL) {
                Node* n = Node_New();
                n->key = c;
                n->depth = depth;
                n->parent = p;
                p->children[uc] = n;
            }
            pchar++;
            depth++;
            p = p->children[uc];
        }
        p->ending = true;
    }
    // BFS
    Queue* queue = Queue_New();
    for (int i=0; i<256; i++) {
        Node* node = search->root->children[i];
        if (node != NULL) {
            node->failure = search->root;
            Queue_Push(queue, node);
        }
    }
    while (Queue_Empty(queue) != true) {
        Node* p = (Node*)Queue_Get_Head(queue);
        Queue_Pop(queue);
        Node* failure = p->failure;
        for (int i=0; i<256; i++) {
            Node* node = p->children[i];
            if (node != NULL) {
                char key = node->key;
                unsigned char ukey = (unsigned char) key;
                while (failure != search->root && failure->children[ukey] == NULL) {
                    failure = failure->failure;
                }
                if (failure->children[ukey] != NULL) {
                    node->failure = failure->children[ukey];
                } else {
                    node->failure = failure;
                }
                Queue_Push(queue, node);
            }
        }
    }
}
Map* ACSearch_FindAll(ACSearch* search, char* text) {
    Map* map = Map_New(1000);
    for (int i=0; i<search->patterns->size; i++) {
        char* pattern = (char*)Vector_Get_Index(search->patterns, i);
        Vector* idxes = Vector_New();
        Map_Set_String(map, pattern, idxes);
    }
    Node* p = search->root;
    int text_len = string_len(text);
    for (int i=0; i<text_len; i++) {
        char c = text[i];
        unsigned char uc = (unsigned char) c;
        while (p->children[uc] == NULL && p != search->root) {
            p = p->failure;
        }
        if (p->children[uc] != NULL) {
            Node* n = p->children[uc];
            if (n->ending == true) {
                char* s = (char*) malloc(sizeof(char) * (n->depth + 1));
                s[n->depth] = '\0';
                Node* b = n;
                while (b != search->root) {
                    s[b->depth - 1] = b->key;
                    b = b->parent;
                }
                Vector* v = (Vector*)Map_Get_String(map, s);
                Vector_Push_Int(v, i - n->depth + 1);
            }
            p = n;
        }
    }
    return map;
}
/* ACSearch End */