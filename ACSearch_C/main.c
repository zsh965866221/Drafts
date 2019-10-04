#include "ACSearch.h"
#include <stdio.h>

void func(char* key, void* value) {
    Vector* vector = (Vector*)value;
    printf("  %s: ", key);
    for (int i=0; i<vector->size; i++) {
        int idx = Vector_Get_Int_Index(vector, i);
        printf("%d, ", idx);
    }
    printf("\n");
}

int main() {
    char* L[] = {"ash", "shex", "bcd", "sha", "ab", "abc", "aba"};
    Vector* patterns = Vector_New();
    for (int i=0; i<7; i++) {
        char* pattern = L[i];
        Vector_Push(patterns, pattern);
    }
    printf("patterns: ");
    for (int i=0; i<7; i++) {
        printf("%s, ", (char*)Vector_Get_Index(patterns, i));
    }
    printf("\n");
    char* text = "secashcvashexbcdashareerwqrqewrababcabacabacc";
    printf("text: %s\n", text);
    ACSearch* search = ACSearch_New(patterns);
    Map* ret = ACSearch_FindAll(search, text);
    printf("ret: \n");
    Map_Traversal(ret, func);
    return 0;
}