#ifndef TREE_H
#define TREE_H

#include <string>
#include "tree.h"

#include <iostream>

// Node Definitions
namespace Tree_Nodes
{
template <typename T>
class Red_Black_Node
{
public:
    typedef Red_Black_Node<T> Node;

public:
    enum Color
    {
        BLACK,
        RED
    };

public:
    Red_Black_Node(int key, T *data) : _left(0), _right(0), _key(key), _data(data), _color(RED){};

    void flip_color()
    {
        if (this->_color == RED)
            this->_color = BLACK;
        else
            this->_color = RED;
    }

    void color(Color c) { this->_color = c; }

    Color color() { return this->_color; }

    bool is_red() { return this->_color == RED; }

    int key() const { return _key; }

    T *data() const { return const_cast<T *>(_data); }

    Node *left() const { return _left; }

    Node *right() const { return _right; }

    void data(T *data) { this->_data = data; }

    void left(Node *h) { this->_left = h; }

    void right(Node *h) { this->_right = h; }

    std::string to_string()
    {
        return std::string("[") + (this->_left == 0 ? std::string("[0]") : this->_left->to_string()) +
               std::string(" <- [") + std::to_string(this->_key) + std::string(" - ") + (_color == RED ? std::string("RED") : std::string("BLACK")) + std::string("] -> ") +
               (this->_right == 0 ? std::string("[0]") : this->_right->to_string()) + std::string("]");
    }

private:
    Node *_left;
    Node *_right;
    int _key;
    T *_data;
    Color _color;
};
} // namespace Tree_Nodes

// Tree Definitions
// Left leaning Red-Black-Tree implementation based on: https://www.cs.princeton.edu/~rs/talks/LLRB/LLRB.pdf
template <typename T,
          typename El = Tree_Nodes::Red_Black_Node<T>>
class Red_Black
{
public:
    typedef El Node;

public:
    Red_Black() : _root(0) {}

    void root(Node *h) { this->_root = h; }

    Node *search(int key) { return this->search_recursive(key, this->_root); };

    Node *remove(int key) { return 0; };

    std::string to_string() { return _root->to_string(); }

    void insert(int key, T *data)
    {
        this->_root = this->insert_recursive(this->_root, new Node(key, data));
        this->_root->color(Node::BLACK);
    };

private:
    Node *search_recursive(int key, Node *h)
    {
        if (h->key() == key)
            return h;
        if (h->key() > key)
            return h->left() ? search_recursive(key, h->left()) : 0;
        else
            return h->right() ? search_recursive(key, h->right()) : 0;
    }
    Node *insert_recursive(Node *h, Node *n)
    {
        if (h == 0)
            return n;

        if (is_red(h->left()) && is_red(h->right()))
            this->flip_colors(h);

        if (h->key() == n->key())
            h->data(n->data());

        if (n->key() < h->key())
            h->left(insert_recursive(h->left(), n));
        else
            h->right(insert_recursive(h->right(), n));

        if (is_red(h->right()) && !is_red(h->left()))
            h = rotate_left(h);
        if (is_red(h->left()) && is_red(h->left()->left()))
            h = rotate_right(h);

        return h;
    }

    Node *rotate_left(Node *h)
    {
        Node *x = h->right();
        h->right(x->left());
        x->left(h);
        x->color(h->color());
        h->color(Node::RED);
        return x;
    };

    Node *rotate_right(Node *h)
    {
        Node *x = h->left();
        h->left(x->right());
        x->right(h);
        x->color(h->color());
        h->color(Node::RED);
        return x;
    };
    void flip_colors(Node *h)
    {
        h->flip_color();
        if (h->left())
            h->left()->flip_color();
        if (h->right())
            h->right()->flip_color();

    }
    bool is_red(Node *h)
    {
        return h == 0 ? 0 : h->is_red();
    }

private:
protected:
    Node *_root;
};

#endif