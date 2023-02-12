/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 16:01:16 by obeaj             #+#    #+#             */
/*   Updated: 2023/02/13 00:06:15 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP__HPP__
#define __MAP__HPP__
#include "../utils/common.hpp"
#include "../utils/AvlTree.hpp"

#include <map>
namespace ft
{
    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > > class map
    {
        
            
        public:
            typedef T                                                                           mapped_type ;
            typedef Key                                                                         key_type ;
            typedef pair<const key_type, mapped_type>                                           value_type ;
            typedef Compare                                                                     key_compare ;
            typedef Alloc                                                                       allocator_type ;
            typedef typename allocator_type::reference                                          reference ;
            typedef typename allocator_type::const_reference                                    const_reference ;
            typedef typename allocator_type::pointer                                            pointer ;
            typedef typename allocator_type::const_pointer                                      const_pointer ;
            typedef typename allocator_type::size_type                                          size_type;
            typedef typename allocator_type::difference_type                                    difference_type;
            
            
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
            
        public:
        
            typedef AvlTree<value_type, key_compare, allocator_type>::iterator                  iterator;
            typedef AvlTree<value_type, key_compare, allocator_type>::const_iterator            const_iterator;
            typedef AvlTree<value_type, key_compare, allocator_type>::reverse_iterator          reverse_iterator;
            typedef AvlTree<value_type, key_compare, allocator_type>::const_reverse_iterator    const_reverse_iterator;
            
        private:
            typedef AvlTree<value_type, key_compare, allocator_type>  tree;
            tree            m_tree;
            key_compare     m_comp;
            allocator_type  m_alloc;
            
            /*-------------------------------------------- Member Functions ---------------------------------------------*/

        public:

            
            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
            m_comp(comp),
            m_alloc(alloc)
            {
             
            };

            template <class InputIterator>  map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
            m_comp(comp),
            m_alloc(alloc)           
            {
                insert(first, last);
            };

            map (const map& x)
            {
                *this = x;
            };

            ~map()
            {
                _tree.clear();
            };

            map& operator=(const map& x)
            {
                if (*this != x)
                {
                    this->clear();
                    this->m_comp = x.m_comp;
                    this->m_alloc = x.m_alloc;
                    insert(x.begin(), x.end());
                }
                return *this;
            };
            
            /*----------------------------------------------- Iterators -------------------------------------------------*/
            
			iterator begin()
			{
				return m_tree.begin();
			};
			
			iterator end()
			{
				return m_tree.end();
			};

			const_iterator begin() const
			{
				return m_tree.begin();
			};
			
			const_iterator end() const
			{
				return m_tree.end();
			};
			
			reverse_iterator rbegin()
			{
				return m_tree.rbegin();
			};
			
			reverse_iterator rend()
			{
				return m_tree.rend();
			};

			const_reverse_iterator rbegin() const
			{
				return m_tree.rbegin()
			};
			
			const_reverse_iterator rend() const
			{
				return m_tree.rend();
			};
            
            /*------------------------------------------------ Capacity -------------------------------------------------*/
            
            bool empty() const
            {
                m_tree.empty();
            };

            size_type size() const
            {
                return m_tree.size();
            };

            size_type max_size() const
            {
                return m_tree.max_size();
            };

            /*--------------------------------------------- Element Access ----------------------------------------------*/
            
            mapped_type& operator[] (const key_type& k)
            {
                return  (*((this->insert(ft::make_pair(k,mapped_type()))).first));
            };
            
            /*----------------------------------------------- Modifiers -------------------------------------------------*/
            pair<iterator,bool> insert (const value_type& val)
            {
                iterator it = iterator(m_tree.search(val));
                if (it != end())
                    return ft::make_pair((it), true);
                return ft::make_pair(iterator(m_tree.insert(val)), false);
            };

            iterator insert (iterator position, const value_type& val)
            {
                iterator it = iterator(m_tree.search(val));
                if (it != end())
                    return ft::make_pair((it), true);
                return ft::make_pair(iterator(m_tree.insert(val, position)), false);                
            };

            template <class InputIterator>  void insert (InputIterator first, InputIterator last)
            {
				while (first != last)
				{
					this->m_tree.insert(*first);
					first++;
				};
            };
            /*----------------------------------------------- Iterators -------------------------------------------------*/
            /*----------------------------------------------- Iterators -------------------------------------------------*/
            
    };
        
}

#endif  //!__MAP__HPP__