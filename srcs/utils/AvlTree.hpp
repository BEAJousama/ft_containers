/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AvlTree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:18:52 by obeaj             #+#    #+#             */
/*   Updated: 2023/02/10 17:58:25 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __AVLTREE__H__
#define __AVLTREE__H__

#include "./utils.hpp"
#include "./ft_type_traits.hpp"
// #include "./AvlIterator.hpp"

#include <iostream>

namespace ft{
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
            // typedef AvlIterator<node_pointer, reference, pointer, compare_type>         iterator;
            // typedef AvlIterator<const_node_pointer, reference, pointer, compare_type>   const_iterator;
            // typedef ft::reverse_iterator<iterator>                                      reverse_iterator;
            // typedef ft::reverse_iterator<const_iterator>                                const_reverse_iterator;
        
        public:
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
                    node = nullptr;
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
                    return newnode;
                if(compare(newnode->value.first, root->value.first))
                {
                    root->left = node_insert(root->left, newnode);
                    root->left == newnode ? newnode->parent = root : root->left;
                }
                else if (!compare(newnode->value.first, root->value.first))
                {
                    root->right = node_insert(root->right, newnode);
                    root->right == newnode ? newnode->parent = root : root->left;  
                }
                else
                    return root;
                updateHeight(root);
                return (balanceNode(root));
            };
            
            node_pointer node_delete(node_pointer root, value_type todelete)
            {
                if (root == nullptr)
                    return root;
				else if (this->compare(todelete.first, root->value.first))
					root->left = node_delete(root->left, todelete);
				else if (this->compare(root->value.first, todelete.first))
					root->right = node_delete(root->right, todelete);
                else
                {
                    if (root->right == nullptr && root->left == nullptr)
                    {
                    	av_alloc.destroy(root);
					    av_alloc.deallocate(root, 1);
                        // root = nullptr;
                        return nullptr;
                    }
                    else if (root->right == nullptr)
                    {
                        node_pointer tmp = root->parent;
                        root->left->parent = root->parent;
                        root->parent->left = root->left;
                        av_alloc.destroy(root);
					    av_alloc.deallocate(root, 1);
                        return tmp->left;
                    }
                    else if(root->left == nullptr)
                    {
                        node_pointer tmp = root->parent;
                        root->right->parent = root->parent;
                        root->parent->right = root->right;
                        av_alloc.destroy(root);
					    av_alloc.deallocate(root, 1);
                        return tmp->right;                        
                    }
                    else
                    {
                        value_type tmp = _getSuccessor(root)->value;
                        root->value = tmp;
                        root->right = node_delete(root -> right, tmp);
                    }
                };

                updateHeight(root);
                return (balanceNode(root));
            };
            
        public:
            AvlTree(const alloc_node& alloc = alloc_node(), const compare_type& comp = compare_type()):
            av_alloc(alloc),
            compare(comp)
            {
                _start = createNode(value_type());
                _root = _start;
                _size = 0;
            }
            ~AvlTree()
            {
                
            }
        public:

            node_pointer _getSuccessor(node_pointer nd)
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

            node_pointer _getPredecessor(node_pointer nd)
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

            void remove(value_type val)
            {
                _root = node_delete(_root,val);
            }

            node_pointer insert(value_type val, node_pointer pos = nullptr)
            {
                node_pointer nd = createNode(val);
                if (pos ==  nullptr)
                {
                    if (_root == _start)
                    {
                        _root = nd;
                        nd->parent = _start;
                        _start->right = nd;
                        _size += 1;
                    }
                    else
                    {
                        _root = node_insert(_root, nd);
                        _size += 1;
                    }
                }
                else
                {
                    if (pos == _start)
                    {
                        pos = nd;
                        nd->parent = _start;
                        _start->right = nd;
                        _size += 1;
                    }
                    else
                    {
                        pos = node_insert(pos, nd);
                        _size += 1;
                    }  
                }
                return nd;
            }

            // node_pointer insert(node_pointer nd, value_type &val) {

            //     if (nd == tree)
            //     {
            //         tree -> value = val;
            //         tree ->left = t_nullptr;
            //         tree ->right = t_nullptr;
            //         return tree;
            //     }
            //     if (nd == t_nullptr)
            //     {
            //         node_pointer newnode;
            //         newnode = av_alloc.allocate(1);
            //         av_alloc.construct(newnode, val);
            //     }
            //     if (val.first < nd->value.first) {
            //         nd->left = insert(nd->left, val);
            //     } else if (val.first > nd->value.first) {
            //         nd->right = insert(nd->right, val);
            //     }
            //     else
            //         return nd;

            //     updateHeight(nd);

            //     int balance = getBalance(nd);

            //     if (balance > 1 && val.first < nd->left->value.first) {
            //         return rightRotate(nd);
            //     }

            //     if (balance < -1 && val.first > nd->right->value.first) {
            //         return leftRotate(nd);
            //     }

            //     if (balance > 1 && val.first > nd->left->value.first) {
            //         nd->left = leftRotate(nd->left);
            //         return rightRotate(nd);
            //     }

            //     if (balance < -1 && val.first < nd->right->value.first) {
            //         nd->right = rightRotate(nd->right);
            //         return leftRotate(nd);
            //     }

            //     return nd;
            // }

            // node_pointer insert(node_pointer _root, node_pointer newnode)
            // {
            //     node_pointer _inode = _root;
            //     if (_inode-> parent == t_nullptr)
            //     {
            //         newnode -> parent = _inode -> parent;
            //         newnode -> right = t_nullptr;
            //         newnode-> left = t_nullptr;
            //         // rebalance(newnode);
            //         return (newnode);
            //     }
            //     else
            //     {
            //         if (newnode->value.first < _root->value.first)
            //         {
            //             return(insert(_inode->left, newnode));
            //         }
            //         else if (newnode->value.first > _root->value.first)
            //         {
            //             return(insert(_inode->right, newnode));
            //         }
            //     }
            // }

            // node_pointer insert(value_type &val)
            // {
            //      node_pointer found ;
            //     if (root != t_nullptr)
            //         found = isexist(root, val);
            //     if(found != t_nullptr)
            //     {
            //         return found;
            //     }
            //     std::cout << "heere\n" << std::endl;
            //     if(_size == 0)
            //     {
            //         tree->value = val;
            //         _size++;
            //         return tree;
            //     }
            //     else
            //     {
            //         node_pointer newnode;
            //         newnode = av_alloc.allocate(1);
            //         av_alloc.construct(newnode, node(val, newnode,newnode,newnode));
            //         return (insert(root, newnode));
            //     }
            // }
    };
};
#endif  //!__AVLTREE__H__