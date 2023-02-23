 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random_access_iterator.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 10:41:25 by obeaj             #+#    #+#             */
/*   Updated: 2023/02/19 17:12:24 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RANDOM_ACCESS_ITERATOR
#define FT_RANDOM_ACCESS_ITERATOR
#include "./utils.hpp"
namespace ft
{
    template <class T>
    class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T >
    {
        public:
            typedef          random_access_iterator                         self_type;
            typedef typename ft::iterator_traits<T*>::difference_type       difference_type;
            typedef typename ft::iterator_traits<T*>::iterator_category     iterator_category;
            typedef typename ft::iterator_traits<T*>::value_type            value_type;
            typedef typename ft::iterator_traits<T*>::pointer               pointer;
            typedef typename ft::iterator_traits<T*>::reference             reference;
        private:
            pointer m_ptr;
            
        public:
        // ATTENTION : use t_null ptr : resolve double include
        random_access_iterator() : m_ptr(t_nullptr){};
        
        explicit random_access_iterator(pointer ptr) : m_ptr(ptr){};
                
		random_access_iterator(const random_access_iterator<typename ft::remove_const<value_type>::type > & src) : m_ptr(&(*src)) {};

		self_type & operator=(random_access_iterator<typename ft::remove_const<value_type>::type > & src) {
			m_ptr = &(*src);
			return *this;
		};
        
        ~random_access_iterator() {};
        
        self_type & operator++ ()
        {
            m_ptr++;
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
            m_ptr--;
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
            return *m_ptr;
        };

        reference operator-> () const
        {
            return *m_ptr;
        };

        self_type operator+(difference_type offset) const
        {
            self_type tmp = *this;
            return tmp += offset;
        };
        
        self_type operator-(difference_type offset) const
        {
            self_type tmp = *this;
            return tmp -= offset;
        };
        
        difference_type operator-(self_type const & other) const
        {
            return (m_ptr - other.m_ptr);
        };

        bool operator<(self_type const & other) const
        {
            return m_ptr < other.m_ptr;
        };
        
        bool operator>(self_type const & other) const
        {
            return other < *this;
        };
        
        bool operator<=(self_type const & other) const
        {
            return !(other < *this);
        };
        
        bool operator>=(self_type const & other) const
        {
            return !(*this < other);
        };
        
        self_type & operator+=(difference_type const offset)
        {
            m_ptr += offset;
            return *this;
        };
        
        self_type & operator-=(difference_type const offset)
        {
            return *this += -offset;
        };
        
        value_type & operator[](difference_type const offset)
        {
          return (*(*this + offset));
        };
        
        value_type const & operator[](difference_type const offset) const
        {
            return (*(*this + offset));
        };
    };
};

#endif