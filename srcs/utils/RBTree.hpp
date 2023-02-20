/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:48:05 by obeaj             #+#    #+#             */
/*   Updated: 2023/02/20 15:53:49 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RBTREE__H__
#define __RBTREE__H__

namespace 
{
    typedef enum Node_Color
    {
        RED = 1 << 0,
        BLACK = 1 << 1
    }
    nd_color;
    
    template <typename T>
    struct rbt_node
    {
        public :

            typedef T   value_type;

            value_type  value;
            int         height;
            nd_color    color;
            rbt_node*   parent;
            rbt_node*   left;
            rbt_node*   right;
            

 		public:
			rbt_mode(): value(value_type()) {};
			rbt_mode(value_type val): value(val){};
    };
    
    template <class T, class Compare, class Alloc, class Node = rbt_node<T> > 
    class RBTree
    {
        
    };
} 

#endif  //!__RBTREE__H__