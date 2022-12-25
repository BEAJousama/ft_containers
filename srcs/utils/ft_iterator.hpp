/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 15:51:32 by obeaj             #+#    #+#             */
/*   Updated: 2022/12/25 13:13:07 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ITERATOR_HPP
#define FT_ITERATOR_HPP

namespace ft
{
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
        typedef typename Iterator::iterator_category iterator_category;
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

    template <class Iterator> class reverse_iterator
    {
        protected:
            Iterator current;
            typedef iterator_traits<Iterator> traits_type;
            
        public:
            typedef          Iterator                       iterator_type;
            typedef typename traits_type::iterator_category iterator_category;
            typedef typename traits_type::value_type        value_type;
            typedef typename traits_type::difference_type   difference_type;
            typedef typename traits_type::pointer           pointer;
            typedef typename traits_type::reference         reference;
            iterator_type base() const
            {
                return typeid(iterator_type);    
            }
    };
}

#endif // !FT_ITERATOR_HPP