/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:41:24 by obeaj             #+#    #+#             */
/*   Updated: 2022/12/24 15:57:37 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILITY_HPP
#define FT_UTILITY_HPP

namespace ft
{
    template<class T1, class T2> struct pair
    {
        public:
            T1 first;
            T2 second;
            pair()
            {
            }
            pair& operator=(const pair& obj)
            {
                if (this->first != obj.first && this->second != obj.second)
                {
                    this->first = obj.first;
                    this->second = obj.second;
                }
                return *this;
            }
            
            pair(const pair& obj)
            {
                *this=obj;
            }
            
            pair (const T1& a, const T2& b)
            {
                this->first = a;
                this->second = b;
            }
            ~pair()
            {
            }
    };
    
    template <class T1, class T2>  pair<T1,T2> make_pair (T1 x, T2 y)
    {
        pair<T1, T2> pr(x, y);
        return pr;
    };
}

#endif // !FT_UTILITY_HPP