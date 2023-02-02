/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 16:01:16 by obeaj             #+#    #+#             */
/*   Updated: 2023/02/02 13:17:02 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP__HPP__
#define __MAP__HPP__
#include "../utils/common.hpp"
#include "AvlTree.hpp"

#include <map>
namespace ft
{
    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > > class map
    {
        
            
        public:
            typedef T                                           mapped_type ;
            typedef Key                                         key_type ;
            typedef pair<const key_type,mapped_type>            value_type ;
            typedef Compare                                     key_compare ;
            typedef Alloc                                       allocator_type ;
            typedef typename allocator_type::reference          reference ;
            typedef typename allocator_type::const_reference    const_reference ;
            typedef typename allocator_type::pointer            pointer ;
            typedef typename allocator_type::const_pointer      const_pointer ;
            typedef typename allocator_type::size_type          size_type;
            typedef typename allocator_type::difference_type    difference_type;
            
            // typedef ft::biderectional_iterator<T>               iterator ;
            // typedef ft::biderectional_iterator<const T>         const_iterator ;
            // typedef ft::reverse_iterator<iterator>              reverse_iterator ;
            // typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator ;

            class value_compare : public std::binary_function<value_type, value_type, bool>
            {
                friend class map;
                protected:
                    key_compare comp;
                    value_compare (key_compare c) : comp(c) {}
                public:
                    typedef bool result_type;
                    typedef value_type first_argument_type;
                    typedef value_type second_argument_type;
                bool operator() (const value_type& x, const value_type& y) const
                {
                    return comp(x.first, y.first);
                }
            };
        private:
            // typedef map_value_compare<key_type, value_type, key_compare>        vc;
            typedef AvlTree<value_type, compare_type, allocator_type = allocator_type()>  tree;
            
            allocator_type  m_alloc;
            tree            m_tree;
        public:
            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
            {
                
            };

            template <class InputIterator>  map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
            {
                
            };

            map (const map& x)
            {
                
            };
    };
        
}

#endif  //!__MAP__HPP__