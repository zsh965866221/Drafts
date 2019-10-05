#include "container.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

#include <vector>
#include <map>
#include <queue>

char* rand_str(const int len) {
    char* ret = (char *)malloc((len + 1) * sizeof(char));
    for (int i=0; i<len; i++) {
        ret[i] = 'A' + rand() % 26;
    }
    ret[len] = '\0';
    return ret;
}

std::clock_t start, end;
double endtime;

int main() {
    // ---------------------------------------------
    std::cout << "Vector" << std::endl;
    start = std::clock();
    for (int it=0; it<1000; it++) {
        std::vector<std::string> cpp_vector;
        for (int i=0; i<10000; i++) {
            char* str = rand_str(10);
            cpp_vector.push_back(str);
        }
    }
    end = std::clock();
    endtime = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "CPP Total time: " << endtime * 1000 << "ms" << std::endl;	//ms为单位
    
    start = std::clock();
    for (int it=0; it<1000; it++) {
        Vector* c_vector = Vector_New();
        for (int i=0; i<10000; i++) {
            char* str = rand_str(10);
            Vector_Push(c_vector, str);
        }
    }
    end = std::clock();
    endtime = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "C Total time: " << endtime * 1000 << "ms" << std::endl;	//ms为单位

    //------------------------------------------
    std::cout << "Map" << std::endl;
    start = std::clock();
    for (int it=0; it<10000; it++) {
        std::map<std::string, std::string> cpp_map;
        for (int i=0; i<1000; i++) {
            char* key = rand_str(10);
            char* value = rand_str(10);
            cpp_map[key] = value;
        }
        for (int i=0; i<1000; i++) {
            char* key = rand_str(10);
            cpp_map.find(key);
        }
    }
    end = std::clock();
    endtime = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "CPP Total time: " << endtime * 1000 << "ms" << std::endl;	//ms为单位

    start = std::clock();
    for (int it=0; it<10000; it++) {
        Map* c_map = Map_New(1000);
        for (int i=0; i<1000; i++) {
            char* key = rand_str(10);
            char* value = rand_str(10);
            Map_Set_String(c_map, key, value);
        }
        for (int i=0; i<1000; i++) {
            char* key = rand_str(10);
            Map_Find_String_(c_map, key);
        }
    }
    end = std::clock();
    endtime = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "C Total time: " << endtime * 1000 << "ms" << std::endl;	//ms为单位

    //------------------------------------------
    std::cout << "Queue" << std::endl;
    start = std::clock();
    for (int it=0; it<1000; it++) {
        std::queue<std::string> cpp_queue;
        for (int i=0; i<10000; i++) {
            char* key = rand_str(10);
            cpp_queue.push(key);
        }
        for (int i=0; i<10000; i++) {
            cpp_queue.pop();
        }
    }
    end = std::clock();
    endtime = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "CPP Total time: " << endtime * 1000 << "ms" << std::endl;	//ms为单位
    
    start = std::clock();
    for (int it=0; it<1000; it++) {
        Queue* c_queue = Queue_New();
        for (int i=0; i<10000; i++) {
            char* key = rand_str(10);
            Queue_Push(c_queue, key);
        }
        for (int i=0; i<10000; i++) {
            Queue_Pop(c_queue);
        }
    }
    end = std::clock();
    endtime = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "C Total time: " << endtime * 1000 << "ms" << std::endl;	//ms为单位
}