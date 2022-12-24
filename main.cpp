/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:58:46 by obeaj             #+#    #+#             */
/*   Updated: 2022/12/24 18:14:01 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// # include <iostream>
// # include <vector>
// # include <stack>
// # include <map>
// # include <algorithm>
// int main(int argc, const char** argv) {
//     (void)argc;
//     (void)argv;
//     std::vector<int> v (5,4);
//     v.push_back(5);
//     std::vector<int>::iterator it;

//     for (it = v.begin() ; it != v.end(); it++) 
//     {
//         std::cout << *it << std::endl;
//         if (*it == 5)
//             v.push_back(-1);
//     }
//     // v.push_back(3);
//     // v.push_back(122);
//     // v.push_back(122);
//     // v.push_back(122);
//     // v.push_back(4);
//     // v.pop_back();
//     // v.pop_back();
//     // v.pop_back();
//     // v.push_back(155);
//     // v.push_back(1999);
//     // std::cout << v.size() << std::endl;
//     // std::cout << v.capacity() << std::endl;
//     // std::cout << v[4] << std::endl;
    
    
//     return 0;
// }

#include <utility>      // std::pair, std::make_pair
#include <string>       // std::string
#include <vector>       // std::string
#include <iostream>     // std::cout
#include "srcs/utils/ft_utility.hpp"
#include "srcs/utils/ft_type_traits.hpp"
#include "srcs/utils/ft_iterator.hpp"
#include "srcs/utils/ft_algorithm.hpp"
// #include <iostream>     // std::cout, std::boolalpha
#include <algorithm>    // std::lexicographical_compare
#include <cctype>       // std::tolower


template <class T>
typename ft::enable_if<ft::is_integral<T>::value,bool>::type
  is_odd (T i) {return bool(i%2);}

// 2. the second template argument is only valid if T is an integral type:
template < class T, class = typename ft::enable_if<ft::is_integral<T>::value>::type>
bool is_even (T i) {return !bool(i%2);}

bool mypredicate (int i, int j) {
  return (i==j);
}

bool mycomp (char c1, char c2)
{ return std::tolower(c1)<std::tolower(c2); }

int main () 
{
  ft::pair <std::string,double> product1;                     // default constructor
  ft::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
  ft::pair <std::string,double> product3 (product2);          // copy constructor

  product1 = ft::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)

  product2.first = "shoes";                  // the type of first is string
  product2.second = 39.90;                   // the type of second is double

  std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
  std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
  std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';
    int myints[] = {20,40,60,80,100};               //   myints: 20 40 60 80 100
  std::vector<int>myvector (myints,myints+5);     // myvector: 20 40 60 80 100

  // using default comparison:
  if ( ft::equal (myvector.begin(), myvector.end(), myints) )
    std::cout << "The contents of both sequences are equal.\n";
  else
    std::cout << "The contents of both sequences differ.\n";

  myvector[3]=81;                                 // myvector: 20 40 60 81 100

  // using predicate comparison:
  if ( ft::equal (myvector.begin(), myvector.end(), myints, mypredicate) )
    std::cout << "The contents of both sequences are equal.\n";
  else
    std::cout << "The contents of both sequences differ.\n";

  char foo[]="Apple";
  char bar[]="Apple";

  std::cout << std::boolalpha;

  std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

  std::cout << "Using default comparison (operator<): ";
  std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+5);
  std::cout << '\n';

  std::cout << "Using mycomp as comparison object: ";
  std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+5,mycomp);
  std::cout << '\n';
    std::cout << std::boolalpha;
  std::cout << "is_integral:" << std::endl;
  ft::is_integral<double> c;
  if (!c)
    std::cout << "yeeeeeeeeeeeees !!\n";
  std::cout << "char: " << ft::is_integral<char>::value << std::endl;
  std::cout << "int: " << ft::is_integral<int>::value << std::endl;
  std::cout << "float: " << ft::is_integral<float>::value << std::endl;

  
  short int i = 1;    // code does not compile if type of i is not integral
  std::cout << std::boolalpha;
  std::cout << "i is odd: " << is_odd(i) << std::endl;
  std::cout << "i is even: " << is_even(i) << std::endl;
  return 0;
}