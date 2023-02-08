/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AvlIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:33:54 by obeaj             #+#    #+#             */
/*   Updated: 2023/02/08 15:29:09 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __AVLITERATOR__H__
#define __AVLITERATOR__H__
#include "./utils.hpp"
#include "./ft_iterator.hpp"
namespace ft
{
    template <class NodePointer, class Reference, class Pointer, class Compare>
    class AvlIterator : ft::iterator<ft::bidirectional_iterator_tag, NodePointer>
    {
        public:
            typedef          AvlIterator                                    self_type;
            typedef          NodePointer                                    node_pointer;
            typedef          Reference                                      reference;
            typedef          Pointer                                        pointer;
            typedef          Compare                                        compare_type;
        private:
            compare_type compare;
            node_pointer m_ptr;

        public:
        // ATTENTION : use t_nullptr : resolve double include
        AvlIterator() : m_ptr(t_nullptr){};
        
        explicit AvlIterator(pointer ptr) : m_ptr(ptr){};
                
		AvlIterator(const AvlIterator<typename ft::remove_const<node_pointer>::type> & src) : m_ptr(&(*src)) {};

		AvlIterator<value_type> & operator=(AvlIterator<typename ft::remove_const<value_type>::type > const & src) {
			m_ptr = &(*src);
			return *this;
		};
        
        ~AvlIterator() {};
        
        //ATTENTION:  -- and ++ to be updated using compare_type
        self_type & operator++ ()
        {
            if (m_ptr->right != t_nullptr)
            {
                m_ptr = m_ptr->right;
                while (m_ptr->left != t_nullptr))
                    m_ptr = m_ptr->left;
            }
            else
            {
                node_pointer tmp = m_ptr;
                while (m_ptr->parent != t_nullptr && m_ptr->left != tmp && m_ptr != t_nullptr)
                {
                    m_ptr = m_ptr->parent;
                    tmp = m_ptr;
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
            if (m_ptr->left != t_nullptr)
            {
                m_ptr = m_ptr->left;
                while (m_ptr->right != t_nullptr))
                    m_ptr = m_ptr->right;
            }
            else
            {
                node_pointer tmp = m_ptr;
                while (m_ptr->parent != t_nullptr && m_ptr->right != tmp && m_ptr != t_nullptr)
                {
                    m_ptr = m_ptr->parent;
                    tmp = m_ptr;
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