/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:39:23 by obeaj             #+#    #+#             */
/*   Updated: 2023/01/30 00:28:01 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __STACK__HPP__
#define __STACK__HPP__

#include "../vector/vector.hpp"

namespace ft
{
    template <class T, class Container = ft::vector<T> > class stack
    {
        public:
            typedef T           value_type;
            typedef Container   container_type;
            typedef size_t      size_type;
        protected:
            container_type c;
        public:
            explicit stack (const container_type& ctnr = container_type())
            {
                c = ctnr;
            };

            stack(const stack& cpy)
            {
                *this = cpy;
            };

            stack& operator=(const stack& cpy)
            {
                c = cpy.c;
                return *this;
            };
            
            ~stack()
            {
            };
            
            bool empty() const
            {
                return (size() == 0);
            };

            size_type size() const
            {
                return (c.size());
            };
            
            value_type& top()
            {
                return c.back();
            };
            
            const value_type& top() const
            {
                return c.back();
            };

            void push (const value_type& val)
            {
                c.push_back(val);
            };

            void pop()
            {
                c.pop_back();
            };
    };
    
    template <class T, class Container>  bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return(lhs.c == rhs.c);
    };

    template <class T, class Container>  bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return(lhs.c != rhs.c);
    };

    template <class T, class Container>  bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return(lhs.c < rhs.c);
    };

    template <class T, class Container>  bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return(lhs.c <= rhs.c);
    };

    template <class T, class Container>  bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return(lhs.c > rhs.c);
    };

    template <class T, class Container>  bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
    {
        return(lhs.c >= rhs.c);
    };
};
#endif  //!__STACK__HPP__
