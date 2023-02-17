/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:41:24 by obeaj             #+#    #+#             */
/*   Updated: 2023/02/17 22:07:50 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILITY_HPP
#define FT_UTILITY_HPP

namespace ft
{

    template<class T1, class T2> struct pair
    {
        public:
        
            typedef T1 first_type;
            typedef T2 second_type;
        public:
            T1 first;
            T2 second;
            pair() : first(), second()
            {
            };
        
      
            pair (T1 const& a, T2 const& b) : first(a), second(b)
            {
            };
            
            pair& operator=(pair const& obj)
            {
                first = obj.first;
                second = obj.second;
                return *this;
            }
            
            template<class _U1, class _U2>
            pair(pair<_U1, _U2> const& obj) : first(obj.first), second(obj.second)
            {
            }
            
            ~pair()
            {
            }
    };
    template <class T1, class T2>
    bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return lhs.first==rhs.first && lhs.second==rhs.second; }

    template <class T1, class T2>
    bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs==rhs); }

    template <class T1, class T2>
    bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

    template <class T1, class T2>
    bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(rhs<lhs); }

    template <class T1, class T2>
    bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return rhs<lhs; }

    template <class T1, class T2>
    bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs<rhs); }
    
    template <class T1, class T2>  pair<T1,T2> make_pair (T1 x, T2 y)
    {
        pair<T1, T2> pr(x, y);
        return pr;
    };
}

#endif // !FT_UTILITY_HPP