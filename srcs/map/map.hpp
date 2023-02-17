/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 16:01:16 by obeaj             #+#    #+#             */
/*   Updated: 2023/02/15 22:32:25 by obeaj            ###   ########.fr       */
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
        
            typedef typename AvlTree<value_type, key_compare, allocator_type>::iterator                  iterator;
            typedef typename AvlTree<value_type, key_compare, allocator_type>::const_iterator            const_iterator;
            typedef typename AvlTree<value_type, key_compare, allocator_type>::reverse_iterator          reverse_iterator;
            typedef typename AvlTree<value_type, key_compare, allocator_type>::const_reverse_iterator    const_reverse_iterator;
            
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
                m_tree.clear();
                m_tree.dealloc();
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
				return m_tree.rbegin();
			};
			
			const_reverse_iterator rend() const
			{
				return m_tree.rend();
			};
            
            /*------------------------------------------------ Capacity -------------------------------------------------*/
            
            bool empty() const
            {
                return (m_tree.empty());
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
                return  this->insert(ft::make_pair(k,mapped_type())).first->second;
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
                iterator it = position;
                if(m_comp(it->first, val.first) && m_comp(val.first,(it++)->first))
                {
                    return iterator(m_tree.insert(val, position.base()));
                }
                return insert(val).first;;                
            };

            template <class InputIterator>  void insert (InputIterator first, InputIterator last)
            {
				while (first != last)
				{
					m_tree.insert(*first);
					first++;
				};
            };

            void erase (iterator position)
            {
                m_tree.remove(*position);
            };

            size_type erase (const key_type& k)
            {
                iterator it = find(k);
                m_tree.remove(*it);
                if (it != end())
                    return 1;
                return 0;
            };

            void erase (iterator first, iterator last)
            {
                while (first != last)
                {
                    m_tree.remove(*first);
                    first++;
                }
            };    
            
            void swap (map& x)
            {
                key_compare     m_comp_tmp = m_comp;
                allocator_type  m_alloc_tmp = m_alloc;

                m_comp = x.m_comp;
                m_alloc = x.m_alloc;
                
                x.m_comp = m_comp_tmp;
                x.m_alloc = m_alloc_tmp;
                
                m_tree.swap(x.m_tree);
            };

            void clear()
            {
                m_tree.clear();
            };
            
            /*----------------------------------------------- Observers -------------------------------------------------*/
            
            key_compare key_comp() const
            {
                return m_comp;
            };
            
            value_compare value_comp() const
            {
                value_compare v_comp(m_comp);
                return v_comp;
            };
            
            /*---------------------------------------------- Operations -------------------------------------------------*/
            
            //ATTENTION: It is better if the search function takes key_type instead of value_type 
            iterator find (const key_type& k)
            {
                value_type v = ft::make_pair(k, mapped_type());
                return iterator(m_tree.search(v));
            };
            
            const_iterator find (const key_type& k) const
            {
                const value_type v = ft::make_pair(k, mapped_type());
                return const_iterator(m_tree.search(v));
            };

            iterator lower_bound (const key_type& k)
            {
                value_type v = ft::make_pair(k, mapped_type());
                return iterator(m_tree.lower_bound(v));
            };
            
            const_iterator lower_bound (const key_type& k) const
            {
                value_type v = ft::make_pair(k, mapped_type());
                return const_iterator(m_tree.lower_bound(v));
            };
            
            iterator upper_bound (const key_type& k)
            {
                value_type v = ft::make_pair(k, mapped_type());
                return iterator(m_tree.upper_bound(v));
            };
            
            const_iterator upper_bound (const key_type& k) const
            {
                value_type v = ft::make_pair(k, mapped_type());
                return const_iterator(m_tree.upper_bound(v));
            };
            
            size_type count (const key_type& k) const
            {
                if (find(k) != end())
                    return 1;
                return 0;
            };

            pair<const_iterator,const_iterator> equal_range (const key_type& k) const
            {
                return ft::make_pair(lower_bound(k), upper_bound(k));
            };
            
            pair<iterator,iterator> equal_range (const key_type& k)
            {
                return ft::make_pair(lower_bound(k), upper_bound(k));
            };
            /*----------------------------------------------- Iterators -------------------------------------------------*/
            
    };

    template <class Key, class T, class Compare, class Alloc>  void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
    {
        x.swap(y);
    };
        
}

#endif  //!__MAP__HPP__