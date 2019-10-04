#include "ACSearch.h"

NAMESPACE_BEGIN

struct Node {
    char key;
    bool ending;
    Node* parent;
    Node* failure;
    std::map<char, Node*> children;

    Node(): ending(false), parent(nullptr), failure(nullptr) {}
    ~Node() {
        for (auto pair: children) {
            if (pair.second != nullptr) {
                delete pair.second;
                pair.second = nullptr;
            }
        }
    }
};

ACSearchor::ACSearchor(std::vector<std::string>& patterns):patterns(patterns) {
    root = new Node();
    root->parent = nullptr;
    root->failure = root;
    build();
}

void ACSearchor::build() {
    /**
     * 构建字典树
     */
    // 首先创建字典树
    for (auto pattern: patterns) {
        Node* p = root;
        const int pattern_len = pattern.size();
        for (int i=0; i<pattern_len; i++) {
            char c = pattern[i];
            // 查找p->childern是否存在c
            if (p->children.find(c) == p->children.end()) {
                // 不存在
                Node* n = new Node();
                n->key = c;
                n->parent = p;
                p->children[c] = n;
            }
            p = p->children[c];
        }
        p->ending = true;
    }

    // BFS
    std::queue<Node*> queue;
    // 构建failure指针
    for (auto pair: root->children) {
        pair.second->failure = root;
        queue.push(pair.second);
    }
    while (queue.empty() != true) {
        Node* p = queue.front();
        queue.pop();
        Node* failure = p->failure;
        // 构建p的子节点的failure
        for (auto pair: p->children) {
            // 查找failure是否包含p_iter->first
            char key = pair.first;
            Node* node = pair.second;
            while (failure != root && failure->children.find(key) == failure->children.end()) {
                // 不存在
                failure = failure->failure;
            }
            if (failure->children.find(key) != failure->children.end()) {
                // 存在
                node->failure = failure->children[key];
            } else {
                node->failure = failure;
            }
            queue.push(node);
        }
    }
}


std::map<std::string, std::vector<int>> ACSearchor::find(std::string& text) {
    std::map<std::string, std::vector<int>> ret;
    for (auto pattern: patterns) {
        std::vector<int> v;
        ret[pattern] = v;
    }
    Node* p = root;
    int text_len = text.size();
    for (int i=0; i<text_len; i++) {
        char c = text[i];
        while (p->children.find(c) == p->children.end() && p != root) {
            p = p->failure;
        }
        if (p->children.find(c) != p->children.end()) {
            // 匹配到了，需要判断是否是ending
            Node* n = p->children[c];
            if (n->ending == true) {
                // 匹配到一个pattern，插入结果
                std::string s;
                Node* b = n;
                while (b != root) {
                    s = b->key + s;
                    b = b->parent;
                }
                ret[s].push_back(i - s.size() + 1);
            }
            p = n;
        }
    }
    return ret;
}

ACSearchor::~ACSearchor() {
    delete root;
    root = nullptr;
}

NAMESPACE_END