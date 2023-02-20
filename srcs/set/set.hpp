/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:48:15 by obeaj             #+#    #+#             */
/*   Updated: 2023/02/20 13:14:20 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
#define SET_HPP

#include "../utils/common.hpp"
#include "../utils/RBTreeIterator.hpp"
    
namespace ft
{
    template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T>    > class set
    {
        public:
            typedef T                                                                           key_type ;
            typedef T                                                                           value_type ;
            typedef Compare                                                                     key_compare ;
            typedef Compare                                                                     value_compare ;
            typedef Alloc                                                                       allocator_type ;
            typedef typename allocator_type::reference                                          reference ;
            typedef typename allocator_type::const_reference                                    const_reference ;
            typedef typename allocator_type::pointer                                            pointer ;
            typedef typename allocator_type::const_pointer                                      const_pointer ;
            typedef typename allocator_type::size_type                                          size_type;
            typedef typename allocator_type::difference_type                                    difference_type;
        /*
        public:
            typedef typename RBTree<value_type, key_compare, allocator_type>::iterator                  iterator;
            typedef typename RBTree<value_type, key_compare, allocator_type>::const_iterator            const_iterator;
            typedef typename RBTree<value_type, key_compare, allocator_type>::reverse_iterator          reverse_iterator;
            typedef typename RBTree<value_type, key_compare, allocator_type>::const_reverse_iterator    const_reverse_iterator;
        */
            
        private:
            /*typedef RBTree<value_type, key_compare, allocator_type>  tree;*/ 
            // tree                s_tree;
            key_compare        s_comp;
            allocator_type      s_alloc;
        public:
            explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
            {
                
            };

            template <class InputIterator>  set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
            {
                
            };

            set (const set& x)
            {
                
            };

            ~set()
            {
                
            };

            set& operator= (const set& x)
            {
                
            };

            
    };
}
#endif
