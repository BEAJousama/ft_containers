/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AvlTree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:18:52 by obeaj             #+#    #+#             */
/*   Updated: 2023/02/06 10:56:52 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __AVLTREE__H__
#define __AVLTREE__H__

#include "../utils/utils.hpp"

template <typename T>
    struct avl_node
{
    public :

        typedef T   value_type;

        value_type value;
        avl_node* parent;
        avl_node* left;
        avl_node* right;

        avl_node ()
        :
            value(),
            parent(t_nullptr),
            left(t_nullptr),
            right(t_nullptr)
        {}


        avl_node (avl_node* parent = t_nullptr,
                avl_node* left = t_nullptr, avl_node* right = t_nullptr)
        :
            value(),
            parent(parent),
            left(left),
            right(right)
        {}
        
        avl_node (const value_type& val, avl_node* parent = t_nullptr,
                avl_node* left = t_nullptr, avl_node* right = t_nullptr)
        :
            value(val),
            parent(parent),
            left(left),
            right(right)
        {}

        avl_node (const avl_node& nd)
        :
            value(nd.value),
            parent(nd.parent),
            left(nd.left),
            right(nd.right)
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
        typedef T           value_type;
        typedef Compare     compare_type;
        typedef Alloc       alloc_type;
        typedef Node        node;
        typedef Node*       node_pointer;
        typedef AllocNode   alloc_node;
    private:
        node_pointer tree;
        node_alloc av_alloc;

    public:

        AvlTree(const node_alloc& alloc = node_alloc()):av_alloc(alloc)
        {
            tree = av_alloc.allocate(1);
            av_alloc.allocate(tree,node(tree,tree,tree));
        }
        ~AvlTree()
        {
        }
        
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

        
        
};
#endif  //!__AVLTREE__H__