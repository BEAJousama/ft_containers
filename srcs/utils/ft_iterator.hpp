/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 15:51:32 by obeaj             #+#    #+#             */
/*   Updated: 2023/02/19 17:09:35 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ITERATOR_HPP
#define FT_ITERATOR_HPP
# include <cstddef>

namespace ft
{
    /*------------------------------------- Iterator_traits ----------------------------------------*/
    struct input_iterator_tag { };

    ///  Marking output iterators.
    struct output_iterator_tag { };

    /// Forward iterators support a superset of input iterator operations.
    struct forward_iterator_tag : public input_iterator_tag { };

    /// Bidirectional iterators support a superset of forward iterator
    /// operations.
    struct bidirectional_iterator_tag : public forward_iterator_tag { };

    /// Random-access iterators support a superset of bidirectional
    /// iterator operations.
    struct random_access_iterator_tag : public bidirectional_iterator_tag { };
    
    template <class Iterator>
    struct iterator_traits 
    {
        // typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::difference_type   difference_type;
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;
    };

    template <class T>
    struct iterator_traits<T*>
    {
        typedef ft::random_access_iterator_tag  iterator_category;
        typedef T                               value_type;
        typedef ptrdiff_t                       difference_type;
        typedef T*                              pointer;
        typedef T&                              reference;
    };

    template <class T>
    struct iterator_traits<const T*>
    {
        typedef ft::random_access_iterator_tag  iterator_category;
        typedef T                               value_type;
        typedef ptrdiff_t                       difference_type;
        typedef const T*                        pointer;
        typedef const T&                        reference;
    };

    /*----------------------------------------- Iterator -------------------------------------------*/
    
    template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
    struct iterator {
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
    };
    
    /*------------------------------------- reverse_iterator ---------------------------------------*/

    template <class _Iterator> 
    class reverse_iterator: public iterator<
                                            // typename iterator_traits<_Iterator>::iterator_category,
                                            typename iterator_traits<_Iterator>::value_type,
                                            typename iterator_traits<_Iterator>::difference_type,
                                            typename iterator_traits<_Iterator>::pointer,
                                            typename iterator_traits<_Iterator>::reference>
    {
        private:
            _Iterator __t;
        protected:
            _Iterator current;
            typedef iterator_traits<_Iterator> traits_type;
        public:
            typedef          _Iterator                      iterator_type;
            // typedef typename traits_type::iterator_category iterator_category;
            typedef typename traits_type::value_type        value_type;
            typedef typename traits_type::difference_type   difference_type;
            typedef typename traits_type::pointer           pointer;
            typedef typename traits_type::reference         reference;
            
            reverse_iterator() : __t(), current()
            {
            };
            
            explicit reverse_iterator (iterator_type it) : __t(it), current(it)
            {
            };

            template <class Iter>  reverse_iterator (const reverse_iterator<Iter>& rev_it):
            __t(rev_it.base()), current(rev_it.base())
            {
            };

            template <class Iter> reverse_iterator& operator=(const reverse_iterator<Iter>& __u)
            {
                __t = current = __u.base(); 
                return *this; 
            };
            
            iterator_type base() const
            {
                return current;  
            };

            reference operator*() const
            {
                _Iterator _tmp = current;
                return *--_tmp;
            };

            reverse_iterator operator+ (difference_type n) const
            {
                return reverse_iterator(current - n);
            };
            
            reverse_iterator operator- (difference_type n) const
            {
                return reverse_iterator(current + n);
            };
            
            reverse_iterator& operator+= (difference_type n)
            {
                current = current - n;
                return *this;
            };
            
            reverse_iterator& operator-= (difference_type n)
            {
                current = current + n;
                return *this;
            };

            reverse_iterator& operator++()
            {
                current--;
                return *this;
            };
            
            reverse_iterator operator++(int)
            {
                reverse_iterator tmp = *this;
                current--;
                return tmp;
            };
            
            reverse_iterator& operator--()
            {
                current++;
                return *this;
            };
            
            reverse_iterator operator--(int)
            {
                reverse_iterator tmp(*this);
                current++;
                return tmp;
            };

            pointer operator->() const
            {
                 return &(operator*());
            };

            reference operator[] (difference_type n) const
            {
                return *(*this + n);
            };
    };
    
    template <class Iterator>  bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() == rhs.base();
    };

    template <class Iterator>  bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() != rhs.base();
    };

    template <class Iterator>  bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() < rhs.base();
    };

    template <class Iterator>  bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() <= rhs.base();
    };

    template <class Iterator>  bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() > rhs.base();
    };

    template <class Iterator>  bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() >= rhs.base();
    };

    template <class Iterator>  
    reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n,const reverse_iterator<Iterator>& rev_it)
    {
        return reverse_iterator<Iterator>(rev_it.base() - n);
    };
    
    template <class Iterator> 
    typename reverse_iterator<Iterator>::difference_type operator- ( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return rhs.base() - lhs.base();
    };
}

#endif // !FT_ITERATOR_HPP