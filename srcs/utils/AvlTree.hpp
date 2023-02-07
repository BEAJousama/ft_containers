/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AvlTree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:18:52 by obeaj             #+#    #+#             */
/*   Updated: 2023/02/07 18:24:55 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __AVLTREE__H__
#define __AVLTREE__H__

#include "./utils.hpp"
#include "./AvlIterator.hpp"
#include <iostream>

namespace ft{
    template <typename T>
        struct avl_node
    {
        public :

            typedef T   value_type;

            value_type  value;
            size_t      bf;
            avl_node*   parent;
            avl_node*   left;
            avl_node*   right;

            avl_node ()
            :
                value(),
                parent(t_nullptr),
                left(t_nullptr),
                right(t_nullptr),
                bf(0)
            {}


            avl_node (avl_node* parent = t_nullptr,
                    avl_node* left = t_nullptr, avl_node* right = t_nullptr)
            :
                value(),
                parent(parent),
                left(left),
                right(right),
                bf(0)
            {}
            
            avl_node (const value_type& val, avl_node* parent = t_nullptr,
                    avl_node* left = t_nullptr, avl_node* right = t_nullptr)
            :
                value(val),
                parent(parent),
                left(left),
                right(right),
                bf(0)
            {}

            avl_node (const avl_node& nd)
            :
                value(nd.value),
                parent(nd.parent),
                left(nd.left),
                right(nd.right)
                bf(nd.bf)
            {}

            virtual ~avl_node() {}
            
            avl_node &operator=(const avl_node& nd)
            {
                if (nd == *this)
                    return (*this);
                
                this->value = nd.value;
                this->parent = nd.parent;
                this->left = nd.left;
                this->right = nd.right;
                this->bf = nd.bf;
                
                return (*this);
            }

            bool operator==(const avl_node& nd)
            {
                if (value == nd.value)
                    return (true);
                return (false);
            }
    };

    template <class T, class Compare, class Alloc, class Node = avl_node<T>, typename AllocNode = std::allocator<Node> > class AvlTree
    {
        
        public:
            typedef T                                       value_type;
            typedef Compare                                 compare_type;
            typedef Alloc                                   alloc_type;
        
        public:
            typedef typename alloc_type::pointer            pointer;
            typedef typename alloc_type::const_pointer      const_pointer;
            typedef typename alloc_type::reference          reference;
            typedef typename alloc_type::const_reference    const_reference;
            typedef size_t                                  size_type;
        
        public:
            typedef Node                                    node;
            typedef AllocNode                               alloc_node;
            typedef Node*                                   node_pointer;
            typedef const Node*                             const_node_pointer;
        
        public:
            typedef AvlIterator<node_pointer, reference, pointer, compare_type>         iterator;
            typedef AvlIterator<const_node_pointer, reference, pointer, compare_type>   const_iterator;
            typedef ft::reverse_iterator<iterator>                                      reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>                                const_reverse_iterator;
        
        private:
            node_pointer    tree;
            node_pointer    root;
            alloc_node      av_alloc;
            size_type       _size;        
        public:
            AvlTree(const node_alloc& alloc = node_alloc()):av_alloc(alloc)
            {
                tree = av_alloc.allocate(1);
                av_alloc.allocate(tree,node(tree,tree,tree));
                root = tree;
            }
            ~AvlTree()
            {
                
            }
        public:
            node_pointer rrrotation(node_pointer torotate)
            {
                node_pointer p;
                node_pointer tp;
                p = torotate;
                tp = p->right;

                p->right = tp->left;
                tp->left = p;

                return tp; 
            }
            
            node_pointer llrotation(node_pointer torotate)
            {
                node_pointer p;
                node_pointer tp;
                p = torotate;
                tp = p->left;

                p->left = tp->right;
                tp->right = p;

                return tp; 
            }
            
            node_pointer lrrotation(node_pointer torotate)
            {
                node_pointer p;
                node_pointer tp;
                p = torotate;
                tp = p->left;
                
                p->left = tp->right;
                tp->right->left = tp->parent;
                p = llrotate(p);
            }

            node_pointer rlrotation(node_pointer torotate)
            {
                node_pointer p;
                node_pointer tp;
                p = torotate;
                tp = p->right;
                
                p->right = tp->left;
                tp->left->right = tp->parent;
                p = rrrotate(p);
            }

            node_pointer isexist(node_pointer _first, value_type &val)
            {
                node_pointer _inode;
                _inode = _first;
                if (val.first < _inode->value.first)
                    return(isexist(_inode->left, val));
                else if (val.first > _inode->value.first)
                    return(isexist(_inode->right, val));
                else if (val.first == _inode->value.first)
                    return _inode;
                return t_nullptr;
            }

            ft::pair<iterator, bool> insert(node_pointer _root, node_pointer newnode)
            {
                node_pointer _inode = _root;
                if (_inode == t_nullptr)
                {
                    newnode -> parent = _inode -> parent;
                    newnode -> right = t_nullptr;
                    newnode-> left = t_nullptr;
                    rebalance(newnode);
                    return (ft::make_pair(pointer(newnode), true))
                }
                else
                {
                    if (newnode->value.first < _root->value.first)
                    {
                        _inode->bf += 1;
                        return(insert(_inode->left, newnode));
                    }
                    else if (newnode->value.first > _root->value.first)
                    {
                        _inode->bf -= 1;   
                        return(insert(_inode->right, newnode));
                    }
                }
                  
            }

            ft::pair<iterator, bool> insert(value_type &val)
            {
                node_pointer found = isexists(root, val);
                if(found != t_nullptr)
                    return ft:make_pair(iterator(found), false);
                if(_size == 0)
                {
                    tree->value = val;
                    _size++;
                    return ft:make_pair(iterator(tree), true);
                }
                else
                {
                    node_pointer newnode;
                    newnode = av_alloc.allocate(1);
                    av_alloc.construct(newnode, node(val, newnode,newnode,newnode));
                    return (insert_node(root, newnode));
                }
            }

            

            
            
    };
};
#endif  //!__AVLTREE__H__