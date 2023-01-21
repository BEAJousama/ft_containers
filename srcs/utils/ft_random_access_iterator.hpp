/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random_access_iterator.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 10:41:25 by obeaj             #+#    #+#             */
/*   Updated: 2023/01/21 14:44:39 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RANDOM_ACCESS_ITERATOR
#define FT_RANDOM_ACCESS_ITERATOR
#include "ft_iterator.hpp"
namespace ft
{
    template <class T>
    class random_acess_iterator : ft::iterator_traits<T*>
    {
        public:
            typedef typename ft::iterator_traits<T*>::difference_type difference_type;
            typedef typename ft::iterator_traits<T*>::iterator_category iterator_category;
            typedef typename ft::iterator_traits<T*>::value_type value_type;
            typedef typename ft::iterator_traits<T*>::pointer pointer;
            typedef typename ft::iterator_traits<T*>::reference reference;
    };
};

#endif