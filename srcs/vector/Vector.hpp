/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:39:32 by obeaj             #+#    #+#             */
/*   Updated: 2022/12/24 18:35:37 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR__H__
#define __VECTOR__H__

#include <iostream>

namespace ft
{
    template <class T, class Allocator = std::allocator<T> >
    class vector
    {
        private:
            T* data;
        public:
    };
    
}

#endif