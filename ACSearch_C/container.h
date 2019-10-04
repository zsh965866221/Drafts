#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include <stdbool.h>


/* For Vector */
typedef struct Vector {
    int capacity;
    int size;
    void** values;
} Vector;
Vector* Vector_New();
void Vector_Free(Vector* vector);
void Vector_Push(Vector* vector, void* value);
void Vector_Set_Index(Vector* vector, int index, void* value);
void* Vector_Get_Index(Vector* vector, int index);
void Vector_Push_Int(Vector* vector, int value);
void Vector_Set_Int_Index(Vector* vector, int index, int value);
int Vector_Get_Int_Index(Vector* vector, int index);
/* Vector End */

/* For Queue */
// tail (left) ----> head (right)
typedef struct Queue_Node {
    struct Queue_Node* left;
    struct Queue_Node* right;
    void* value;
} Queue_Node;
Queue_Node* Queue_Node_New();
typedef struct Queue {
    int size;
    Queue_Node* head;
    Queue_Node* tail;
} Queue;
Queue* Queue_New();
bool Queue_Empty(Queue* queue);
void Queue_Push(Queue* queue, void* value);
void* Queue_Get_Head(Queue* queue);
void Queue_Pop(Queue* queue);
void Queue_Pop_Free(Queue* queue);
/* Queue End*/

/* For Map */
typedef struct Map_Node {
    long hashcode;
    struct Map_Node* left;
    struct Map_Node* right;
    char* key;
    void* value;
} Map_Node;
Map_Node* Map_Node_New();
long string_hashcode(char* string);
int string_len(char* string);
bool string_equal(char* str_A, char* str_B);
// simple hash map
typedef struct Map {
    int max_size;
    int size;
    Map_Node** values;
} Map;
Map* Map_New(int max_size);
Map_Node* Map_Find_String_(Map* map, char* key);
bool Map_Contains_String(Map* map, char* key);
void* Map_Get_String(Map* map, char* key);
void Map_Set_String(Map* map, char* key, void* value);
void Map_Delete_String(Map* map, char* key);
void Map_Delete_String_Free(Map* map, char* key);
void Map_Traversal(Map* map, void (*func)(char* key, void* value));
/* Map End*/

#endif