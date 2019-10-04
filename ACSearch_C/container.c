#include "container.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>


/* For Vector */
Vector* Vector_New() {
    Vector* vector = (Vector*)malloc(sizeof(Vector));
    vector->size = 0;
    vector->values = NULL;
    return vector;
}
void Vector_Push(Vector* vector, void* value) {
    void** new_values = (void**)malloc((vector->size + 1) * sizeof(void*));
    if (vector->values != NULL) {
        memcpy(new_values, vector->values, vector->size * sizeof(void*));
        free(vector->values);
    }
    vector->values = new_values;
    vector->values[vector->size] = value;
    vector->size++;
}
void Vector_Set_Index(Vector* vector, int index, void* value) {
    vector->values[index] = value;
}
void* Vector_Get_Index(Vector* vector, int index) {
    if (index < vector->size) {
        return vector->values[index];
    } else {
        return NULL;
    }
}

void Vector_Free(Vector* vector) {
    for (int i=0; i<vector->size; i++) {
        void* p = vector->values[i];
        if (p != NULL) {
            free(p);
            p = NULL;
        }
    }
}

void Vector_Push_Int(Vector* vector, int value) {
    int *pv = (int*)malloc(sizeof(int));
    *pv = value;
    Vector_Push(vector, pv);
}

void Vector_Set_Int_Index(Vector* vector, int index, int value) {
    int *pv = (int*)malloc(sizeof(int));
    *pv = value;
    Vector_Set_Index(vector, index, pv);
}
int Vector_Get_Int_Index(Vector* vector, int index) {
    int* pret = Vector_Get_Index(vector, index);
    return *pret;
}
/* Vector End */

/* For Queue */
// tail (left) ----> head (right)
Queue_Node* Queue_Node_New() {
    Queue_Node* node = (Queue_Node*) malloc(sizeof(Queue_Node));
    node->left = NULL;
    node->right = NULL;
    node->value = NULL;
    return node;
}
Queue* Queue_New() {
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    queue->size = 0;
    queue->head = Queue_Node_New();
    queue->tail = Queue_Node_New();
    queue->head->left = queue->tail;
    queue->tail->right = queue->head;
    return queue;
}
bool Queue_Empty(Queue* queue) {
    if (queue->size == 0) {
        return true;
    } else {
        return false;
    }
}
void Queue_Push(Queue* queue, void* value) {
    // push to tail
    Queue_Node* node = Queue_Node_New();
    node->value = value;

    node->right = queue->tail->right;
    queue->tail->right->left = node;
    node->left = queue->tail;
    queue->tail->right = node;
    queue->size++;
}
void* Queue_Get_Head(Queue* queue) {
    return queue->head->left->value;
}
void Queue_Pop(Queue* queue) {
    if (queue->size > 0) {
        Queue_Node* r = queue->head->left;
        r->left->right = queue->head;
        queue->head->left = r->left;
        queue->size--;
        free(r);
    }
}

void Queue_Pop_Free(Queue* queue) {
    if (queue->size > 1) {
        Queue_Node* r = queue->head->left;
        r->left->right = queue->head;
        queue->head->left = r->left;
        queue->size--;
        // free r
        if (r->value != NULL) {
            free(r->value);
            r->value = NULL;
        }
        free(r);
    }
}
/* Queue End*/

/* For Map */
Map_Node* Map_Node_New() {
    Map_Node* node = (Map_Node*) malloc(sizeof(Map_Node));
    node->hashcode = -1;
    node->left = NULL;
    node->right = NULL;
    node->key = NULL;
    node->value = NULL;
    return node;
}
long string_hashcode(char* string) {
    // 所有char相加
    long ret = 0;
    char* p = string;
    while (*p != '\0') {
        ret += *p;
        p++;
    }
    return ret;
}
int string_len(char* string) {
    int ret = 0;
    char* p = string;
    while (*p != '\0') {
        ret++;
        p++;
    }
    return ret;
}
bool string_equal(char* str_A, char* str_B) {
    int len_A = string_len(str_A);
    int len_B = string_len(str_B);
    if (len_A != len_B) {
        return false;
    }
    for (int i=0; i<len_A; i++) {
        if (str_A[i] != str_B[i]) {
            return false;
        }
    }
    return true;
}
// simple hash map
Map* Map_New(int max_size) {
    Map* map = (Map*) malloc(sizeof(Map));
    map->max_size = max_size;
    map->values = (Map_Node**)malloc(sizeof(Map_Node*) * max_size);
    for (int i=0; i<max_size; i++) {
        map->values[i] = Map_Node_New();
    }
    return map;
}
Map_Node* Map_Find_String_(Map* map, char* key) {
    long hashcode = string_hashcode(key);
    int map_hashcode = hashcode % map->max_size;
    Map_Node* base = map->values[map_hashcode];
    // find
    Map_Node* p = base->right;
    while (p != NULL) {
        if (p->hashcode == hashcode) {
            if (string_equal(key, p->key) == true) {
                break;
            }
        }
        p = p->right;
    }
    return p;
}
bool Map_Contains_String(Map* map, char* key) {
    Map_Node* node = Map_Find_String_(map, key);
    if (node == NULL) {
        return false;
    } else {
        return true;
    }
}
void* Map_Get_String(Map* map, char* key) {
    Map_Node* node = Map_Find_String_(map, key);
    if (node == NULL) {
        return NULL;
    } else {
        return node->value;
    }
}
void Map_Set_String(Map* map, char* key, void* value) {
    long hashcode = string_hashcode(key);
    int map_hashcode = hashcode % map->max_size;
    Map_Node* base = map->values[map_hashcode];
    // find
    Map_Node* p = base->right;
    while (p != NULL) {
        if (p->hashcode == hashcode) {
            if (string_equal(key, p->key) == true) {
                break;
            }
        }
        p = p->right;
    }
    if (p == NULL) {
        p = Map_Node_New();
        p->key = key;
        p->hashcode = hashcode;
        p->right = base->right;
        p->left = base;
        if (base->right != NULL) {
            base->right->left = p;
        }
        base->right = p;
        map->size++;
    }
    p->value = value;
}
void Map_Delete_String(Map* map, char* key) {
    Map_Node* node = Map_Find_String_(map, key);
    if (node != NULL) {
        // 肯定有left，不一定有right
        node->left->right = node->right;
        if (node->right != NULL) {
            node->right->left = node->left;
        }
        map->size--;
        free(node);
        node = NULL;
    }
}
void Map_Delete_String_Free(Map* map, char* key) {
    Map_Node* node = Map_Find_String_(map, key);
    if (node != NULL) {
        // 肯定有left，不一定有right
        node->left->right = node->right;
        if (node->right != NULL) {
            node->right->left = node->left;
        }
        map->size--;
        // free
        if (node->value != NULL) {
            free(node->value);
            node->value = NULL;
        }
        free(node);
        node = NULL;
    }
}
void Map_Traversal(Map* map, void (*func)(char*, void*)) {
    for (int i=0; i<map->max_size; i++) {
        Map_Node* base = map->values[i];
        Map_Node* p = base->right;
        while (p != NULL) {
            char* key = p->key;
            void* value = p->value;
            func(key, value);
            p = p->right;
        }
    }
}
/* Map End*/