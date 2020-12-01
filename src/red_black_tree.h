#pragma once
#include <iostream>

using namespace std;

#define BLACK false
#define RED true
typedef bool colorType;

namespace Karlven {
    
    template<typename elementType>
    class node {
    public:
        node *left, *right, *parent;
        elementType key;
        colorType color;
        node() : left(nullptr), right(nullptr), parent(nullptr), key(elementType()), color(BLACK) { }
        node(elementType _key, colorType _color, node* l, node* r, node*p) : key(_key), color(_color), left(l), right(r), parent(p) { }
    };  




    template<typename elementType>
    class red_black_tree {
    private:        
        node<elementType>* real_root;

    public:
        red_black_tree();
        ~red_black_tree();
        void destroy();

        void preOrder();
        void postOrder();
        void inOrder();

        node<elementType>* search(elementType key);
        node<elementType>* iterativeSearch(elementType key);

        elementType minimum();
        elementType maximum();

        node<elementType>* successor(node<elementType>* x);
        node<elementType>* predecessor(node<elementType>* x);

        void insert(elementType key);
        void remove(elementType key);
        void print();
    
    private:
        void preOrder(node<elementType>* tree) const;
        void inOrder(node<elementType>* tree) const;
        void postOrder(node<elementType>* tree) const;

        node<elementType>* search(node<elementType>* x, elementType key) const;
        node<elementType>* iterativeSearch(node<elementType>* x, elementType key) const;
        node<elementType>* maximum(node<elementType>* tree) const;
        node<elementType>* minimum(node<elementType>* tree) const;

        void leftRotate(node<elementType>*& root, node<elementType>* x);
        void rightRotate(node<elementType>*& root, node<elementType>* y);
        void insert(node<elementType>*& root, node<elementType>* _node);
        void insertFixUp(node<elementType>*& root, node<elementType>* _node);
        void transplant(node<elementType>*& root, node<elementType>* u, node<elementType>* v);
        void remove(node<elementType>*& root, node<elementType>* _node);
        void removeFixUp(node<elementType>*& root, node<elementType>* _node);

        void destroy(node<elementType>*& tree);
        void print(node<elementType>* tree, elementType key, int direction);
    };






    template<typename elementType>
    red_black_tree<elementType>::red_black_tree() : real_root(nullptr) {}

    template<typename elementType>
    red_black_tree<elementType>::~red_black_tree() {
        destroy();
    }   

    template<typename elementType>
    void red_black_tree<elementType>::destroy(node<elementType>*& tree) {
        if (tree == nullptr) return;
        if (tree->left != nullptr) 
            destroy(tree->left);
        if (tree->right != nullptr)
            destroy(tree->right);
        delete tree;
        tree = nullptr;
    }

    template<typename elementType>
    void red_black_tree<elementType>::destroy() {
        destroy(real_root);
    }

    template<typename elementType>
    void red_black_tree<elementType>::preOrder(node<elementType>* tree) const {
        if (tree !=nullptr) {
            cout << tree->key << " ";
            preOrder(tree->left);
            preOrder(tree->right);
        }
    }

    template<typename elementType>
    void red_black_tree<elementType>::preOrder() {
        preOrder(real_root);
    }

    template<typename elementType>
    void red_black_tree<elementType>::inOrder(node<elementType>* tree) const {
        if (tree != nullptr) {
            inOrder(tree->left);
            cout << tree->key << " ";
            inOrder(tree->right);
        }
    }

    template<typename elementType>
    void red_black_tree<elementType>::inOrder() {
        inOrder(real_root);
    }

    template<typename elementType>
    void red_black_tree<elementType>::postOrder(node<elementType>* tree) const {
        if (tree != nullptr) {
            postOrder(tree->left);
            postOrder(tree->right);
            cout << tree->key << " ";
        }
    }

    template<typename elementType>
    void red_black_tree<elementType>::postOrder() {
        postOrder(real_root);
    }

    template<typename elementType>
    node<elementType>* red_black_tree<elementType>::search(node<elementType>* x, elementType key) const {
        if (x == nullptr || key == x->key) return x;

        if (key < x->key) 
            return search(x->left, key);
        else
            return search(x->right, key);
    }
    
    template<typename elementType>
    node<elementType>* red_black_tree<elementType>::search(elementType key) {
        return search(real_root, key);
    }

    template<typename elementType>
    node<elementType>* red_black_tree<elementType>::iterativeSearch(node<elementType>*x, elementType key) const {
        while ((x != nullptr) && (x->key != key)) {
            if (key < x->key)
                x = x->left;
            else 
                x = x->right;
        }
        return x;
    }

    template<typename elementType>
    node<elementType>* red_black_tree<elementType>::iterativeSearch(elementType key) {
        return iterativeSearch(real_root, key);
    }
    
    template<typename elementType>
    node<elementType>* red_black_tree<elementType>::minimum(node<elementType>* tree) const {
        if (tree == nullptr) return nullptr;

        while (tree->left != nullptr)
            tree = tree->left;
        return tree;
    }

    template<typename elementType>
    elementType red_black_tree<elementType>::minimum() {
        auto p = minimum(real_root);
        if (p != nullptr) return p->key;
        return (elementType)NULL;
    }

    template<typename elementType>
    node<elementType>* red_black_tree<elementType>::maximum(node<elementType>* tree) const {
        if (tree == nullptr) return nullptr;

        while (tree->right != nullptr) 
            tree = tree->right;
        return tree;        
    }

    template<typename elementType>
    elementType red_black_tree<elementType>::maximum() {
        auto p = maximum(real_root);
        if (p != nullptr) return p->key;
        return (elementType)NULL;
    }

    template<typename elementType>
    node<elementType>* red_black_tree<elementType>::successor(node<elementType>* x) {
        if (x->right != nullptr) 
            return minimum(x->right);
        auto p = x->parent;
        while (p != nullptr && p->right == x) {
            x = p;
            p = p->parent;
        }
        return p;
    }

    template<typename elementType>
    node<elementType>* red_black_tree<elementType>::predecessor(node<elementType>* x) {
        if (x->left != nullptr) 
            return maximum(x->left);
        auto p = x->parent;
        while (p != nullptr && p->left == x) {
            x = p;
            p = p->parent;
        }        
        return p;
    }
    
    
    /*                         rotate operation                               */


    template<typename elementType>
    void red_black_tree<elementType>::leftRotate(node<elementType>*& root, node<elementType>* x) {
        auto y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
            y->left->parent = x;
        
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else {
            if (x->parent->left == x)
                x->parent->left = y;
            else
                x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    template<typename elementType>
    void red_black_tree<elementType>::rightRotate(node<elementType>*& root, node<elementType>* y) {
        auto x = y->left;
        y->left = x->right;
        if (x->right != nullptr) 
            x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == nullptr) 
            root = x;
        else {
            if (y == y->parent->left) 
                y->parent->left = x;
            else y->parent->right = x;
        }
        x->right = y;
        y->parent = x;
    }

    /*                           insert operation                                 */

    template<typename elementType>
    void red_black_tree<elementType>::insertFixUp (node<elementType>*& root, node<elementType>* _node) {
        node<elementType> *_parent, *_grandpa, *_uncle;
        
        _parent = _node->parent;
        while (_parent &&  _parent->color == RED) {
            _grandpa = _parent->parent;
            
            if (_parent == _grandpa->left) {
                _uncle = _grandpa->right;
                if (_uncle && _uncle->color == RED) {
                    _parent->color = BLACK;
                    _uncle->color = BLACK;
                    _grandpa->color = RED;
                    _node = _grandpa;
                }
                else 
                    if (_node == _parent->right) {
                        _node = _parent;
                        leftRotate(root, _node);
                    }
                
                _parent->color = BLACK;
                _grandpa->color = RED;
                rightRotate(root, _grandpa);
            }
            else {
                _uncle = _grandpa->left;
                if (_uncle && _uncle->color == RED) {
                    _parent->color = RED;
                    _uncle->color = BLACK;
                    _grandpa->color = RED;
                    _node = _grandpa;
                }
                else
                    if (_node == _parent->left) {
                        _node = _parent;
                        rightRotate(root, _node);
                    }
                _parent->color = BLACK;
                _grandpa->color = RED;
                leftRotate(root, _grandpa);
            }
        }

        root->color = BLACK;
    }

    template<typename elementType>
    void red_black_tree<elementType>::insert (node<elementType>*& root, node<elementType>* _node) {
        node<elementType>* y = nullptr;
        node<elementType>* x = root;
        while (x != nullptr) {
            y = x;
            if (_node->key < x->key) 
                x = x->left;
            else
                if (_node->key == x->key) {
                    delete _node;
                    return;
                }
                else
                    x = x->right;            
        }
        _node->parent = y;
        if (y != nullptr) {
            if (_node->key < y->key)
                y->left = _node;
            else y->right = _node;
        }
        else 
            root = _node;
        _node->color = RED;
        insertFixUp(root, _node);
    }

    template<typename elementType>
    void red_black_tree<elementType>::insert (elementType key) {
        node<elementType>* _node = nullptr;
        if ((_node = new node<elementType>(key, BLACK, nullptr, nullptr, nullptr)) == nullptr) 
            return;
        insert(real_root, _node);
    }

 
    /*         remove operation                    */
    
    template<typename elementType>
    void red_black_tree<elementType>::transplant (node<elementType>*& root, node<elementType>* u, node<elementType>* v) {
        if (u->parent == nullptr) 
            root = v;
        else
            if (u = u->parent->left) {
                u->parent->left = v;
            }        
            else 
                u->parent->right = v;
        v->parent = u->parent;
    }
 
    template<typename elementType>
    void red_black_tree<elementType>::removeFixUp (node<elementType>*& root, node<elementType>* _node) {
        node<elementType>* w = nullptr;

        while (_node != root && _node->color == BLACK) {
            if (_node == _node->parent->left) {
                w = _node->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    _node->parent->color = RED;
                    leftRotate(root, _node->parent);
                    w = _node->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    _node = _node->parent;
                }
                else{
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(root, w);
                        w = _node->parent->right;
                    }
                    w->color = _node->parent->color;
                    _node->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(root, _node->parent);
                    _node = root;
                }
            }
            else {
                w = _node->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    _node->parent->color = RED;
                    rightRotate(root, _node->parent);
                    w = _node->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    _node = _node->parent;
                }
                else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(root, w);
                        w = _node->parent->left;
                        _node = root;
                    }
                }
            }
        }
        if (_node) _node->color = BLACK;
    }

    template<typename elementType>
    void red_black_tree<elementType>::remove (node<elementType>*& root, node<elementType>* _node) {
        node<elementType>* y = _node;
        node<elementType>* x = nullptr;
        colorType _color = y->color;
        if (_node->left == nullptr) {
            x = _node->right;
            transplant(root, _node, _node->right);
        }
        else
            if (_node->right == nullptr) {
                x = _node->left;
                transplant(root, _node, _node->left);
            }
            else {
                y = minimum(_node->right);
                _color = y->color;
                x = y->right;
                if (y->parent == _node) 
                    x->parent = y;
                else {
                    transplant(root, y, y->right);
                    y->right = _node->right;
                    y->right->parent = y;
                } 
                transplant(root, _node, y);
                y->left = _node->left;
                y->left->parent = y;
                y->color = _node->color;
            }
        if (_color == BLACK)
            removeFixUp(root, x);
    }

    template<typename elementType>
    void red_black_tree<elementType>::remove (elementType key) {
        node<elementType>* _node = nullptr;
        if ((_node = search(real_root, key)) != nullptr) 
            remove(real_root, _node);
    }


    /*                   pirnt the whole tree               */

    template<typename elementType>
    void red_black_tree<elementType>::print(node<elementType>* tree, elementType key, int direction) {
        if (tree != nullptr) {
            if (direction == 0) {
                cout << tree->key << " (B) is root" << endl;
            } 
            else {
                cout << tree->key << (tree->color == RED ? "(R) " : "(B) ") << "is " << key << " 's" << (direction == 1 ? " right_child" : " left_child") << endl;
            }
            print(tree->left, tree->key, -1);
            print(tree->right, tree->key, 1);
        }
    }

    template<typename elementType>
    void red_black_tree<elementType>::print() {
        if (real_root != nullptr) {
            print(real_root, real_root->key, 0);
        }
    }
}