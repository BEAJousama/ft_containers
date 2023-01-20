/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:39:32 by obeaj             #+#    #+#             */
/*   Updated: 2023/01/20 15:49:01 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR__H__
#define __VECTOR__H__

#include <iostream>
#include "ft_iterator.hpp"

namespace ft
{
    template <class T, class Allocator = std::allocator<T> >
    class vector
    {
        public:
            typedef Allocator                                allocator_type;
            typedef T                                        value_type;
            typedef typename allocator_type::reference       reference;
            typedef typename allocator_type::const_reference const_reference;
            // typedef implementation-defined                   iterator;
            // typedef implementation-defined                   const_iterator;
            typedef typename allocator_type::size_type       size_type;
            typedef typename allocator_type::difference_type difference_type;
            typedef typename allocator_type::pointer         pointer;
            typedef typename allocator_type::const_pointer   const_pointer;
            typedef ft::reverse_iterator<iterator>          reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;
        private:
            Allocator   v_alloc;
            T*          v_data = NULL;
            size_t      v_size = 0;
            size_t      v_capacity = 0;
        private:
            void realloc(size_t newcapacity)
            {
                T* new_data = v_alloc.allocate(newcapacity);
                if (newcapacity < v_size)
                    v_size = newcapacity;
                for (size_t i = 0; i < v_size; i++)
                    v_alloc.construct(&new_data[i], v_data[i]);
                v_alloc.destroy(&v_data);
                v_data = new_data;
                v_capacity = newcapacity;
            };
        public:
            explicit vector (const allocator_type& alloc = allocator_type())
            {
                realloc(2);
            };
            explicit vector (size_type n, const value_type& val = value_type(),const allocator_type& alloc = allocator_type())
            {
                v_size = v_capacity = n;
                v_data = realloc(n);
                uninitialized_fill_n(v_data, n, val);
            };
            
            vector (const vector& x)
            {
                v_alloc = x.v_alloc;
                v_capacity = x.v_capacity;
                v_size = x.v_size;
                for(int i = 0 ; i < x.size(); i++)
                {
                    v_data[i] = x[i];
                }
            };
            template <class InputIterator> 
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
            {
                
            };
            ~vector()
            {
                v_alloc.destroy(&v_data);
            };
            
            void push_back(T elem)
            {
                if (v_size >= v_capacity)
                {
                    realloc(2 * v_capacity);
                }
                v_data[v_size] = elem;
                v_size++;
            };
            
            const T& operator[](size_t index) const
            {
                return v_data[index];   
            };
            
            T& operator[](size_t index)
            {
                return v_data[index];   
            };
            
            size_t capacity()
            {
                return v_capacity;
            };
            
            size_t size()
            {
                return v_size;
            }

            void resize(int newsize)
            {
                if (newsize < 0)
                    throw std::length_error("Error : size should be greater than 0 ") ;
                v_size = newsize;
            };

            void reserve(int newcapacity)
            {
                if (newcapacity < 0)
                    throw std::length_error("Error : capacity should be greater than 0 ") ;
                if (newcapacity > v_capacity)
                {
                    realloc(newcapacity);
                }
            }
    };
    
}

#endif