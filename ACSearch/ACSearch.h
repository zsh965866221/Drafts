#ifndef __ACSEARCH_H__
#define __ACSEARCH_H__

#define NAMESPACE_BEGIN namespace zsh {
#define NAMESPACE_END }


#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>

NAMESPACE_BEGIN

class Node;

class ACSearchor {
public:
    ACSearchor(std::vector<std::string>& patterns);
    void build();
    std::map<std::string, std::vector<int>> find(std::string& text);
    ~ACSearchor();

private:
    Node* root;
    std::vector<std::string> patterns;
};

NAMESPACE_END

#endif