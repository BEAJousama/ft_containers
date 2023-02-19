/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AvlTree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:18:52 by obeaj             #+#    #+#             */
/*   Updated: 2023/02/19 20:03:24 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __AVLTREE__H__
#define __AVLTREE__H__

#include "./utils.hpp"
#include "./AvlIterator.hpp"
#include <iostream>
#include <stddef.h>
#include <limits.h>


namespace ft
{
    template <typename T>
        struct avl_node
    {
        public :

            typedef T   value_type;

            value_type  value;
            int         height;
            avl_node*   parent;
            avl_node*   left;
            avl_node*   right;

 		public:
			avl_node(): value(value_type()) {};
			avl_node(value_type val): value(val){};
    };

    template <class T, class Compare, class Alloc, class Node = avl_node<T> > 
    class AvlTree
    {
        
        public:
            typedef T                                       value_type;
            typedef typename value_type::first_type         key_type;
            typedef typename value_type::second_type        mapped_type;
            typedef Compare                                 compare_type;
            typedef Alloc                                   alloc_type;
        
        public:
            typedef typename alloc_type::pointer            pointer;
            typedef typename alloc_type::const_pointer      const_pointer;
            typedef typename alloc_type::reference          reference;
            typedef typename alloc_type::const_reference    const_reference;
			typedef typename alloc_type::difference_type    difference_type;
			typedef typename alloc_type::size_type			size_type;
        
        private:
            // typedef AllocNode                               alloc_node;
            typedef Node                                                node;
            typedef typename alloc_type::template rebind<node>::other   alloc_node;
            typedef Node*                                               node_pointer;
            typedef const Node*                                         const_node_pointer;
        
        public:
            typedef AvlIterator<value_type, node_pointer>                iterator;
            typedef AvlIterator<const value_type, node_pointer>          const_iterator;
            typedef ft::reverse_iterator<iterator>                       reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>                 const_reverse_iterator;
            
        private:
            node_pointer    _start;
            node_pointer    _root;
            alloc_node      av_alloc;
            compare_type    compare;
            size_type       _size;

        private:

            node_pointer createNode(value_type val)
			{
				node_pointer newnode = av_alloc.allocate(1);
				this->av_alloc.construct(newnode, node(val));
				newnode->height = 1;
				newnode->parent = nullptr;
				newnode->left = nullptr;
				newnode->right = nullptr;
				return (newnode);
			};

            void updateHeight(node_pointer node)
            {
                node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
            };

            int getHeight(node_pointer node) {
                if (node == t_nullptr) {
                    return 0;
                }
                return node->height;
            };

            int getBalance(node_pointer node) {
                if (node == t_nullptr)
                    return 0;
                return getHeight(node->left) - getHeight(node->right);
            };

            node_pointer rightRotate(node_pointer x) {
                node_pointer y = x->left;
                node_pointer tmp = y->right;
                node_pointer ptmp = x->parent;

                y->right = x;
                x->left = tmp;

                if (ptmp != _start && ptmp->left == x)
                    ptmp->left = y;
                else if (ptmp != _start && ptmp->right == x)
                    ptmp->right = y;
                y->parent = x->parent;
                x->parent = y;

                if (tmp != nullptr)
                    tmp->parent = x;
                updateHeight(x);
                updateHeight(y);
                return y;
            };

            node_pointer leftRotate(node_pointer x) 
            {
                node_pointer y = x->right;
                node_pointer tmp = y->left;
                node_pointer ptmp = x->parent;

                y->left = x;
                x->right = tmp;

                if (ptmp->left == x)
                    ptmp->left = y;
                else if (ptmp != _start && ptmp->right == x)
                    ptmp->right = y;
                y->parent = x->parent;
                x->parent = y;
                if (tmp != nullptr)
                    tmp->parent = x;
                updateHeight(x);
                updateHeight(y);
                return y;
            };

            node_pointer RightLeftRotate(node_pointer node)
			{
				node->right = rightRotate(node->right);
				return (leftRotate(node));
			};

			node_pointer LeftRightRotate(node_pointer node)
			{
				node->left = leftRotate(node->left);
				return (rightRotate(node));
			};

			void    destructNode(node_pointer node)
			{
				if (node != nullptr)
				{
                    destructNode(node->left);
                    destructNode(node->right);
					av_alloc.destroy(node);
                    av_alloc.deallocate(node, 1);
				}
			};

            node_pointer balanceNode(node_pointer node)
			{
				int	balanceFactor = getBalance(node);
				if (balanceFactor > 1)
				{
					if (getBalance(node->left) >= 0)
						return (rightRotate(node));
					else
						return (LeftRightRotate(node));
				}
				else if (balanceFactor < -1)
				{
					if (getBalance(node->right) <= 0)
						return (leftRotate(node));
					else
						return (RightLeftRotate(node));
				}
				return (node);
			};

            node_pointer node_insert(node_pointer root, node_pointer newnode)
            {
                if(root == nullptr || root == _start)
                {
                    _size += 1;   
                    return newnode;
                }
                if(compare(newnode->value.first, root->value.first))
                {
                    root->left = node_insert(root->left, newnode);
                    if (root->left == newnode)
                        root->left->parent = root;
                }
                else if (!compare(newnode->value.first, root->value.first))
                {
                    root->right = node_insert(root->right, newnode);
                    if (root->right == newnode)
                        root->right->parent = root;
                }
                else
                {
                    return root;
                }
                updateHeight(root);
                return (balanceNode(root));
            };
            
            node_pointer node_delete(node_pointer root, value_type todelete)
            {
                if (root == nullptr)
                    return root;
                if (root->parent == _start && _size == 1)
                {
				    this->av_alloc.destroy(root);
					this->av_alloc.deallocate(root, 1);
					root = _start;    
                    _size--;                
                    return root;
                }
				else if (this->compare(todelete.first, root->value.first))
					root->left = node_delete(root->left, todelete);
				else if (this->compare(root->value.first, todelete.first))
					root->right = node_delete(root->right, todelete);
                else
                {
					if (root->left == nullptr && root->right == nullptr){
						this->av_alloc.destroy(root);
						this->av_alloc.deallocate(root, 1);
						root = nullptr;
                        _size--;
						return (root);
					}
					else if (root->left == nullptr)
					{
						node_pointer	temp = root;
						root = root->right;
						root->parent = temp->parent;
						this->av_alloc.destroy(temp);
						this->av_alloc.deallocate(temp, 1);
						temp = nullptr;
                        _size--;
						return (root);
					}
					else if (root->right == nullptr)
					{
						node_pointer	temp = root;
						root = root->left;
						root->parent = temp->parent;
						this->av_alloc.destroy(temp);
						this->av_alloc.deallocate(temp, 1);
						temp = nullptr;
                        _size--;
						return (root);
					}
					else
                    {
						node_pointer	temp = _getSuccessor(root->right);
						value_type p = temp->value;
						root->right = node_delete(root->right , temp->value);
						this->av_alloc.construct(root, p);
					}
                };
                updateHeight(root);
                return (balanceNode(root));
            };

            node_pointer node_search(node_pointer root, key_type tofind) const
            {
                if (root == nullptr)
                    return _start;
                else if (compare(tofind, root->value.first))
                    return node_search(root->left, tofind);
                else if (compare(root->value.first, tofind))
                    return node_search(root->right, tofind);
                else
                    return root;
                return nullptr;
            };

            node_pointer node_min(node_pointer root) const
            {
                if (root == nullptr)
                    return _start;
                while(root->left != nullptr)
                    root = root->left;
                return root;
            };
            
            node_pointer node_max(node_pointer root)
            {
               if (root == nullptr)
                    return _start;
                while(root->right != nullptr)
                    root = root->right;
                return root;
            }

            node_pointer node_lower_bound(node_pointer root, key_t value) const
            {
                node_pointer nd = node_min(root);
                while (compare(nd->value.first , value))
                {
                    nd = _getSuccessor(nd);
                    if (nd == _start)
                    {
                        return nd;
                    }
                }
                return nd;
            };

            node_pointer node_upper_bound(node_pointer root, key_type value) const
            {
                node_pointer nd = node_min(root);
                
                while (compare(nd->value.first , value))
                {
                    nd = _getSuccessor(nd);
                    if (nd == _start)
                    {
                        return nd;
                    }
                    else if (nd->value.first == value)
                        return _getSuccessor(nd);
                }
                return nd;
            };
            

            node_pointer _getSuccessor(node_pointer nd) const
            {
                if (nd->right != nullptr)
                {
                    nd = nd->right;
                    while (nd != nullptr && nd->left != nullptr)
                        nd = nd->left;
                }
                else
                {
                    node_pointer tmp = nd->parent;
                    while (nd != nullptr && nd->parent != nullptr)
                    {
                        if (tmp->left == nd)
                        {
                            nd = tmp;
                            break;
                        }
                        else
                        {
                            nd = tmp;
                            tmp = tmp->parent;     
                        }
                    }
                }
                return nd;
            };

            node_pointer _getPredecessor(node_pointer nd) const
            {
                if (nd->left != nullptr)
                {
                    nd = nd->left;
                    while (nd != nullptr && nd->right != nullptr)
                        nd = nd->right;
                }
                else
                {
                    node_pointer tmp = nd->parent;
                    while (nd != nullptr && nd->parent != nullptr)
                    {
                        if (tmp->right == nd)
                        {
                            nd = tmp;
                            break;
                        }
                        else
                        {
                            nd = tmp;
                            tmp = tmp->parent;     
                        }
                    }
                }
                return nd;
            };
            
        /*---------------------------------------------- Iterators ------------------------------------------------*/
        
        public:
        
			iterator begin()
			{
				return iterator(node_min(_root));
			};
			
			iterator end()
			{
				return iterator(_start);
			};

			const_iterator begin() const
			{
				return const_iterator(node_min(_root));
			};
			
			const_iterator end() const
			{
				return const_iterator(_start);
			};
			
			reverse_iterator rbegin()
			{
				return reverse_iterator(end());
			};
			
			reverse_iterator rend()
			{
				return reverse_iterator(begin());
			};

			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(end());
			};
			
			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(begin());
			};
            
        public:
        
            AvlTree(const alloc_node& alloc = alloc_node(), const compare_type& comp = compare_type()):
            av_alloc(alloc),
            compare(comp)
            {
                _start = createNode(value_type());
                _root = _start;
                _size = 0;
            };
            
            ~AvlTree()
            {
            };
        
        /*---------------------------------------------- Capacity -------------------------------------------------*/
        public:

        	bool empty() const 
            { 
                return (this->_size == 0); 
            };
            
			size_type size() const
            { 
                return (this->_size); 
            };
            
			size_type	max_size()	const	
            {
                // return (std::min<size_type>(std::numeric_limits<size_type>::max() / sizeof(node), std::numeric_limits<difference_type>::max())); 
                return av_alloc.max_size();
            };

        /*---------------------------------------------- Modifiers -------------------------------------------------*/

        public:

            void remove(value_type val)
            {
                _root = node_delete(_root,val);
            };

            node_pointer insert(value_type val, node_pointer pos = nullptr)
            {
                node_pointer nd = createNode(val);
                if (pos ==  nullptr)
                {
                    if (_root == _start)
                    {
                        _root = nd;
                        _root->parent = _start;
                        _start->left = _root;
                        _size++;
                    }
                    else
                    {
                        _root = node_insert(_root, nd);
                    }
                }
                else
                {
                    if (pos == _start)
                    {
                        pos = nd;
                        pos->parent = _start;
                        _start->left = pos;
                        _size++;
                    }
                    else
                    {
                        pos = node_insert(pos, nd);
                    }  
                }
                return nd;
            };
            
            void clear()
            {
				if (this->_root != this->_start)
				{
					destructNode(this->_root);
					this->_size = 0;
					this->_root = this->_start;
					this->_start->left = nullptr;
				}
            };
            

            void swap (AvlTree& x)
            {
                node_pointer    _start_tmp = _start;
                node_pointer    _root_tmp = _root;
                alloc_node      av_alloc_tmp = av_alloc;
                compare_type    compare_tmp = compare;
                size_type       _size_tmp = _size;

                _start = x._start;
                _root = x._root;
                av_alloc = x.av_alloc;
                compare = x.compare;
                _size = x._size;;
                
                x._start = _start_tmp;
                x._root = _root_tmp;
                x.av_alloc = av_alloc_tmp;
                x.compare = compare_tmp;
                x._size = _size_tmp;
                
            };

        /*---------------------------------------------- Operations -------------------------------------------------*/

            node_pointer search(key_type val) const
            {
                return node_search(_root, val);
            };

            node_pointer upper_bound(key_type val) const
            {
                return node_upper_bound(_root, val);
            };
            
            node_pointer lower_bound(key_type val) const
            {
                return node_lower_bound(_root, val);
            };
            
    };
};
#endif  //!__AVLTREE__H__