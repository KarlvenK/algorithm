#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <queue>
#define alphabet_size 52

namespace Karlven {
    class trieTree {
    public:
        trieTree() : root(new trieNode()) {

        }
        ~trieTree() {
            std::queue<trieNode*> que;
            que.push(root);
            while (!que.empty()) {
                auto cur =  que.front();
                que.pop();
                for (int i = 0; i < alphabet_size; ++i) {
                    if (cur->children[i] == nullptr) continue;
                    que.push(cur->children[i]);
                }
                delete cur;
            }
        }
        std::size_t query(std::string s) {
            auto p = root;
            for (int i = 0; i < s.size(); ++i) {
                auto cur = get_num(s[i]);
                if (p->children[cur] == nullptr) return 0;
                p = p->children[cur];
            }
            return p->size();
        }
        void insert(std::string s) {
            auto p = root;
            for (int i = 0; i < s.size(); ++i) {
                auto cur = get_num(s[i]);
                if (p->children[cur] == nullptr) {
                    p->children[cur] = new trieNode();
                }
                p = p->children[cur];
            }
            p->inc();
        }
    private:
        class trieNode {
        public:
            std::vector<trieNode*> children;
            trieNode() : count(0) {
                children.resize(alphabet_size, nullptr);
            }
            void inc() {
                ++count;
            }
            std::size_t size() {
                return count;
            }
        private:
            std::size_t count;
        };

        trieNode* root;

        inline int get_num(char x) {
            if (x <= 'Z') return x - 'A';
            return x - 'a' + 26;
        }
    };
}