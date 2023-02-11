/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AvlIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:33:54 by obeaj             #+#    #+#             */
/*   Updated: 2023/02/11 17:04:06 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __AVLITERATOR__H__
#define __AVLITERATOR__H__
#include "./utils.hpp"
#include "./ft_type_traits.hpp"
#include "./ft_iterator.hpp"

namespace ft
{
    template <class T, class Node>
    class AvlIterator : ft::iterator<ft::bidirectional_iterator_tag, Node>
    {
        public:
            typedef          AvlIterator                                            self_type;
            typedef          Node                                                   node_pointer;
            typedef          typename ft::iterator_traits<T*>::reference             reference;
            typedef          typename ft::iterator_traits<T*>::pointer               pointer;
            typedef          typename ft::iterator_traits<T*>::value_type            value_type;
            typedef          typename ft::iterator_traits<T*>::difference_type       difference_type;
        private:
            node_pointer m_ptr;

        public:
        // ATTENTION : use t_nullptr : resolve double include
        AvlIterator() : m_ptr(t_nullptr){};
        
        explicit AvlIterator(node_pointer ptr) : m_ptr(ptr){};
                
		AvlIterator(const AvlIterator<typename ft::remove_const<T>::type , typename ft::remove_const<node_pointer>::type > & src) { m_ptr = src.m_ptr;};

		AvlIterator<value_type, node_pointer> & operator=(const AvlIterator<typename ft::remove_const<T>::type, typename ft::remove_const<node_pointer>::type > & src) {
			m_ptr = src.m_ptr;
			return *this;
		};
        
        ~AvlIterator() {};
        
        //ATTENTION:  -- and ++ to be updated using compare_type
        
        // node_pointer base(){return m_ptr;};
        
        self_type & operator++ ()
        {
            if (m_ptr->right != nullptr)
            {
                m_ptr = m_ptr->right;
                while (m_ptr != nullptr && m_ptr->left != nullptr)
                    m_ptr = m_ptr->left;
            }
            else
            {
                node_pointer tmp = m_ptr->parent;
                while (m_ptr != nullptr && m_ptr->parent != nullptr)
                {
                    if (tmp->left == m_ptr)
                    {
                        m_ptr = tmp;
                        break;
                    }
                    else
                    {
                        m_ptr = tmp;
                        tmp = tmp->parent;     
                    }
                }
            }
            return *this;
        };
        
        self_type operator++ (int)
        {
            self_type tmp = *this;
            ++*this;
            return tmp;
        };
        
        self_type & operator-- ()
        {
            if (m_ptr->left != nullptr)
            {
                m_ptr = m_ptr->left;
                while (m_ptr != nullptr && m_ptr->right != nullptr)
                    m_ptr = m_ptr->right;
            }
            else
            {
                node_pointer tmp = m_ptr->parent;
                while (m_ptr != nullptr && m_ptr->parent != nullptr)
                {
                    if (tmp->right == m_ptr)
                    {
                        m_ptr = tmp;
                        break;
                    }
                    else
                    {
                        m_ptr = tmp;
                        tmp = tmp->parent;     
                    }
                }
            }
            return *this;
        };
        
        self_type operator-- (int)
        {
            self_type tmp = *this;
            --*this;
            return tmp;
        };
		
        bool operator== (self_type const & other) const
        {
            return m_ptr == other.m_ptr;
        };
        
        bool operator!= (self_type const & other) const
        {
            return !(*this == other);
        };
        
        reference operator* () const
        {
            return m_ptr->value;
        };

        pointer operator-> () const
        {
            return &(m_ptr->value);
        };
    };
};
#endif  //!__AVLITERATOR__H__