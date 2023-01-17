/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:39:32 by obeaj             #+#    #+#             */
/*   Updated: 2023/01/15 23:00:40 by obeaj            ###   ########.fr       */
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
            Allocator v_alloc;
            T* v_data = NULL;
            size_t v_size = 0;
            size_t v_capacity = 0;
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
        
            vector()
            {
                realloc(2);
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