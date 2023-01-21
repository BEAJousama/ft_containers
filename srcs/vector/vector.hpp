/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:39:32 by obeaj             #+#    #+#             */
/*   Updated: 2023/01/21 20:07:23 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR__H__
#define __VECTOR__H__

#include <iostream>
#include "../utils/utils.hpp"

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
            // typedef ft::reverse_iterator<iterator>          reverse_iterator;
            // typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;
        private:
            allocator_type  v_alloc;
            pointer         v_start;
            pointer         v_end ;
            pointer         v_capacity;
        // private:
            // void realloc(size_type newcapacity)
            // {
            //     T* new_data = v_alloc.allocate(newcapacity);
            //     if (newcapacity < v_size)
            //         v_size = newcapacity;
            //     for (size_t i = 0; i < v_size; i++)
            //         v_alloc.construct(&new_data[i], v_start[i]);
            //     v_alloc.destroy(&v_start);
            //     v_alloc.deallocate(&v_start);
            //     v_start = new_data;
            //     v_capacity = newcapacity;
            // };
        public:
        
            explicit vector (const allocator_type& alloc = allocator_type()) :
            v_alloc(alloc),
            v_start(t_nullptr),
            v_end(t_nullptr),
            v_capacity(t_nullptr)
            {
                std::cout << "default constructor";
            };
            
            
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
            v_alloc(alloc),
            v_start(t_nullptr),
            v_end(t_nullptr),
            v_capacity(t_nullptr)
            {
                std::cout << "vector" << std::endl;
                v_start = v_alloc.allocate(n);
                v_end = v_start + n;
                v_capacity = v_start + n;
                std::uninitialized_fill_n(v_start, n, val);
            };

            vector& operator= (const vector& x)
            {
                // if (*this != x)
                // {
                    v_capacity = v_start + x.capacity();
                    v_end = v_start + x.size();
                    v_start = v_alloc.allocate(x.size());
                    for(size_type i = 0 ; i < x.size(); i++)
                    {
                        v_start[i] = x[i];
                    }
                // }
                return *this;
            }
            
            /*TO DO : verify if we need deeep copy here or not ??*/
            vector (const vector& x) :
            v_alloc(x.v_alloc)
            {
                *this = x;
            };

            
            template <class InputIterator> 
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
            {
            };

            
            ~vector()
            {
                this->clear();
                v_alloc.deallocate(v_start, v_capacity - v_start);
            };
            
            
            void push_back(value_type elem)
            {
                size_type capacity = v_capacity - v_start;
                if (v_capacity - v_start == 0)
                    capacity = 1;
                std::cout << capacity << std::endl;
                if (v_end >= v_capacity)
                {
                    pointer new_v_start = v_alloc.allocate(capacity * 2);
                    v_capacity = new_v_start + capacity * 2;
                    for (size_type i = 0; i < size(); i++)
                    {
                        new_v_start[i] = v_start[i];
                        v_end++;
                    }
                    this->~vector();
                    v_start = new_v_start;
                }
                std::cout<< size() << std::endl;
                *(v_start + size()) = elem;
                std::cout<< "helloooooooow!!" << std::endl;
                v_end++;
            };
            
            
            void clear()
            {
                for (size_type i = 0;   i < size(); i++)
                {
                    v_alloc.destroy(&v_start[i]);
                    i++;
                }
            }
            
            
            const T& operator[](size_t index) const
            {
                return v_start[index];   
            };
            
            
            T& operator[](size_t index)
            {
                return v_start[index];   
            };
            
            
            size_type capacity() const
            {
                return v_capacity - v_start;
            };
            
            size_type size() const
            {
                return v_end - v_start;;
            }


            void resize(int newsize)
            {
                if (newsize < 0)
                    throw std::length_error("Error : size should be greater than 0 ") ;
                v_end = v_start + newsize;
            };


            void reserve(int newcapacity)
            {
                if (newcapacity < 0)
                    throw std::length_error("Error : capacity should be greater than 0 ") ;
                if (newcapacity > v_capacity)
                {
                    pointer new_v_start = v_alloc.allocate(newcapacity);
                    v_capacity = new_v_start + newcapacity;
                    for (size_type i = 0; i < size(); i++)
                    {
                        new_v_start[i] = v_start[i];
                        i++;
                    }
                    this->~vector();
                    v_start = new_v_start;
                }
            }
    };
    
}

#endif