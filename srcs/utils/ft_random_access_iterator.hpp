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
            typedef typename ft::random_access_iterator_tag                 iterator_category;
            typedef typename ft::iterator_traits<T*>::value_type            value_type;
            typedef typename ft::iterator_traits<T*>::pointer               pointer;
            typedef typename ft::iterator_traits<T*>::reference             reference;
            typedef bool                                                    bool_type;
        private:
            pointer m_ptr;
            
        public:
        // ATTENTION : use t_null ptr : resolve double include
        random_access_iterator() : m_ptr(t_nullptr){};
        
        explicit random_access_iterator(pointer ptr) : m_ptr(ptr){};

		random_access_iterator(random_access_iterator const & src) : m_ptr(src.base())
        {
        };

		self_type &operator=(const random_access_iterator &src){
			m_ptr = src.base();
			return *this;
		};
        
        ~random_access_iterator() {};
        
        pointer	base() const							
        { 
            return (this->m_ptr); 
        };

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

        pointer operator-> () const
        {
            return m_ptr;
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
        
        reference operator[](difference_type const offset)
        {
          return (*(*this + offset));
        };
        
        operator random_access_iterator<const T> () const
        { 
            return (random_access_iterator<const T>(this->m_ptr)); 
        }
    };

    // template <typename T>
    // typename ft::random_access_iterator<T>::bool_type
    // operator==(const ft::random_access_iterator<T> lhs,
    //           const ft::random_access_iterator<T> rhs)
    // {
    //     return (lhs.base() == rhs.base());
    // }

    /* iterator == const_iterator */
    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::bool_type
    operator==(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    // template <typename T>
    // typename ft::random_access_iterator<T>::bool_type
    // operator!=(const ft::random_access_iterator<T> lhs,
    //           const ft::random_access_iterator<T> rhs)
    // {
    //     return (lhs.base() != rhs.base());
    // }

    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::bool_type
    operator!=(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    // template <typename T>
    // typename ft::random_access_iterator<T>::bool_type
    // operator<(const ft::random_access_iterator<T> lhs,
    //           const ft::random_access_iterator<T> rhs)
    // {
    //     return (lhs.base() < rhs.base());
    // }

    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::bool_type
    operator<(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    // template <typename T>
    // typename ft::random_access_iterator<T>::bool_type
    // operator>(const ft::random_access_iterator<T> lhs,
    //           const ft::random_access_iterator<T> rhs)
    // {
    //     return (lhs.base() > rhs.base());
    // }

    template<typename T_L,
             typename T_R>
    typename ft::random_access_iterator<T_L>::bool_type
    operator>(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    // template <typename T>
    // typename ft::random_access_iterator<T>::bool_type
    // operator<=(const ft::random_access_iterator<T> lhs,
    //           const ft::random_access_iterator<T> rhs)
    // {
    //     return (lhs.base() <= rhs.base());
    // }

    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::bool_type
    operator<=(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    // template <typename T>
    // typename ft::random_access_iterator<T>::bool_type
    // operator>=(const ft::random_access_iterator<T> lhs,
    //           const ft::random_access_iterator<T> rhs)
    // {
    //     return (lhs.base() >= rhs.base());
    // }

    template<typename T_L,
             typename T_R>
    typename ft::random_access_iterator<T_L>::bool_type
    operator>=(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template<typename T>
    typename ft::random_access_iterator<T> operator+(
        typename ft::random_access_iterator<T>::difference_type n,
        typename ft::random_access_iterator<T>& src)
        {
            return (ft::random_access_iterator<T>(src.base() + n));
        }
    
    // template <typename T>
    // typename ft::random_access_iterator<T>::difference_type
    // operator-(const ft::random_access_iterator<T> lhs,
    //           const ft::random_access_iterator<T> rhs)
    // {
    //     return (lhs.base() - rhs.base());
    // }

    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator-(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() - rhs.base());
    }
};

#endif