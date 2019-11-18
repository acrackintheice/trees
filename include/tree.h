#ifndef TREE_H
#define TREE_H

#include <string>
#include "tree.h"

#include <iostream>

// Element Definitions
namespace Tree_Elements
{
template <typename T>
class Element
{
public:
    Element(int key, T *data) : _left(0), _right(0), _parent(0), _key(key), _data(data) {}

    int key() const { return _key; }

    T *data() const { return const_cast<T *>(_data); }

    Element *left() const { return _left; }

    Element *right() const { return _right; }

    Element *parent() const { return _parent; }

    void left(Element *e) { this->_left = e; }

    void right(Element *e) { this->_right = e; }

    void parent(Element *e) { this->_parent = e; }

    virtual std::string to_string() = 0;

protected:
    Element *_left;
    Element *_right;
    Element *_parent;
    int _key;
    T *_data;
};

template <typename T>
class Red_Black_Element : public Element<T>
{
public:
    enum Color
    {
        BLACK,
        RED
    };

public:
    Red_Black_Element(int key, T *data) : Element<T>(key, data), _color(RED){};

    std::string to_string()
    {
        return std::string("Something");
    }

private:
    Color _color;
};
} // namespace Tree_Elements

// Tree Definitions
template <typename T>
class Tree
{
public:
    typedef Tree_Elements::Element<T> Element;

public:
    Tree() : _root(0) {}

    void root(Element *e) { this->_root = e; }

    virtual Element *search(int key)
    {
        return this->search_recursive(key, this->_root);
    };

    virtual void insert(int key, T * data) = 0;

    virtual Element *remove(int key) = 0;

    std::string to_string()
    {
        return _root->to_string();
    }

protected:
    virtual Element *search_recursive(int key, Element *e)
    {
        if (e->key() == key)
            return e;
        if (e->key() > key)
            return e->left() ? search_recursive(key, e->left()) : 0;
        else
            return e->right() ? search_recursive(key, e->right()) : 0;
    }

    virtual void insert_recursive(Element *e, Element *n)
    {
        // Root is null
        if (e == 0) {
            this->root(n);
        }
        // <n> must be inserted in <e>'s left tree
        else if (e->key() > n->key())
        {
            // <n> must be inserted as <e>'s left child
            if (e->left() == 0)
            {
                e->left(n);
                n->parent(e);
            }
            else
                insert_recursive(e->left(), n);
        }
        // <n> must be inserted in <e>'s right tree
        else
        {
            // <n> must be inserted as <e>'s right child
            if (e->right() == 0)
            {
                e->right(n);
                n->parent(e);
            }
            else
                insert_recursive(e->right(), n);
        }
    }

protected:
    Element *_root;
};

template <typename T,
          typename El = Tree_Elements::Red_Black_Element<T>>
class Red_Black : public Tree<T>
{
public:
    typedef El Element;

public:
    Red_Black() {}

    void insert(int key, T * data)
    {
        this->insert_recursive(this->_root, new Element(key, data));
        // TODO - Balance the tree after insertions
    };

    Element *remove(int key)
    {
        return 0;
    };

private:
    void rotate_left(Element *b)
    {
        Element *a = b->right();
        Element *d = a->left();
        a->parent(b->parent());
        b->parent(a);
        a->left(b);
        b->right(d);
    };
    void rotate_right(Element *a)
    {
        Element *b = a->left();
        Element *d = b->right();
        b->parent(a->parent());
        a->parent(b);
        b->right(a);
        a->left(d);
    };
};

#endif