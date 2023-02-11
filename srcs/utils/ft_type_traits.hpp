/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_traits.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 15:51:11 by obeaj             #+#    #+#             */
/*   Updated: 2023/02/11 12:57:27 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TYPE_TRAITS_HPP
#define FT_TYPE_TRAITS_HPP

namespace ft
{
    template <class T, T v> struct integral_constant {
        static const T value = v;
        typedef T value_type;
        typedef integral_constant<T,v> type;
        operator T() { return v;}
    };

    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    template <class T>   struct ft_is_integral                     : public ft::false_type {};
    template <>          struct ft_is_integral<bool>               : public ft::true_type {};
    template <>          struct ft_is_integral<char>               : public ft::true_type {};
    template <>          struct ft_is_integral<signed char>        : public ft::true_type {};
    template <>          struct ft_is_integral<unsigned char>      : public ft::true_type {};
    template <>          struct ft_is_integral<wchar_t>            : public ft::true_type {};
    //ATTENTION : check how to use char16_t without compilation errors
    // template <>          struct ft_is_integral<char16_t>           : public ft::true_type {};
    // template <>          struct ft_is_integral<char32_t>           : public ft::true_type {};
    template <>          struct ft_is_integral<short>              : public ft::true_type {};
    template <>          struct ft_is_integral<unsigned short>     : public ft::true_type {};
    template <>          struct ft_is_integral<int>                : public ft::true_type {};
    template <>          struct ft_is_integral<unsigned int>       : public ft::true_type {};
    template <>          struct ft_is_integral<long>               : public ft::true_type {};
    template <>          struct ft_is_integral<unsigned long>      : public ft::true_type {};
    template <>          struct ft_is_integral<long long>          : public ft::true_type {};
    template <>          struct ft_is_integral<unsigned long long> : public ft::true_type {};
    template <>          struct ft_is_integral<__int128_t>         : public ft::true_type {};
    template <>          struct ft_is_integral<__uint128_t>        : public ft::true_type {};
    template <class T>   struct is_integral                        : public ft_is_integral<T>{};

    template<bool Cond, class T = void> struct enable_if {};
    template<class T> struct enable_if<true, T> { typedef T type; };

    template <class T> struct  remove_const            {typedef T type;};
    template <class T> struct  remove_const<const T>   {typedef T type;};
}

#endif // !FT_TYPE_TRAITS_HPP