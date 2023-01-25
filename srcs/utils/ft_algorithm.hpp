/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algorithm.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 15:51:36 by obeaj             #+#    #+#             */
/*   Updated: 2023/01/25 13:47:04 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ALGORITHM_HPP
#define FT_ALGORITHM_HPP
#include <iostream>

namespace ft
{
    template <class T1, class T2>
    bool equal ( T1 first1, T1 last1, T2 first2 )
    {
        try
        {
            while (first1 != last1)
            {
                if (!(*first1 == *first2))
                    return false;
                ++first1;
                ++first2;
            }      
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        return true;
    };
    
    template <class T1, class T2, class Pred>  
    bool equal (T1 first1, T1 last1, T2 first2, Pred pred)
    {
        try
        {
            while (first1 != last1) 
            {
                if (!(*first1 == *first2) || !(pred(*first1, *first2)))
                    return false;
                ++first1;
                ++first2;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        return true;
    };
    
    template <class T1, class T2>
    bool lexicographical_compare (T1 first1, T1 last1, T2 first2, T2 last2)
    {
        try
        {
            while (first1 != last1)
            {
                if (first2 == last2 || *first2 < *first1) 
                    return false;
                else if (*first1 < *first2) 
                    return true;
                ++first1; 
                ++first2;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        return (first2 != last2);
    };
    
    template <class T1, class T2, class Compare>
    bool lexicographical_compare (T1 first1, T1 last1, T2 first2, T2 last2, Compare comp)
    {
        try
        {
            while (first1 != last1)
            {
                if (first2 == last2 || !comp(*first1, *first2)) 
                    return false;
                else if (comp(*first1, *first2)) 
                    return true;
                ++first1; 
                ++first2;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        // ATTENTION 
        return (first2 != last2);
    };
}

#endif // !FT_ALGORITHM_HPP