/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 10:41:43 by obeaj             #+#    #+#             */
/*   Updated: 2023/01/28 14:40:17 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP


namespace ft
{
    const                         /* this is a const object...     */
    struct nullptr_t
    {
    public:
    template<class T>          /* convertible to any type       */
    operator T*() const        /* of null non-member            */
        { return 0; }           /* pointer...                    */

    template<class C, class T> /* or any type of null           */
        operator T C::*() const /* member pointer...             */
        { return 0; }   

    private:
    void operator&() const;    /* Can't take address of nullptr */

    } t_nullptr = {};               /* and whose name is nullptr     */
    
};

#endif //UTILS_HPP