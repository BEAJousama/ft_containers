/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:06:44 by obeaj             #+#    #+#             */
/*   Updated: 2023/02/07 13:18:53 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include <iostream>
int main()
{
    std::map<int, int, std::less<int> > m;
    m.insert(std::make_pair(2,122));
    m.insert(std::make_pair(7,16));
    m.insert(std::make_pair(15,50));
    m.insert(std::make_pair(19,20));
    m.insert(std::make_pair(30,12));
    m.insert(std::make_pair(0,11));
    m.insert(std::make_pair(155,1));
    m.insert(std::make_pair(12,1));

    std::map<int, int, std::greater<int> >::iterator it = m.begin();

    while(it != m.end())
    {
        std::cout<< (*it).first << std::endl;
        it++;
    }
}