/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:58:46 by obeaj             #+#    #+#             */
/*   Updated: 2023/01/29 21:00:44 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <vector>
# include <stack>
# include <map>
# include <algorithm>
#include "srcs/vector/vector.hpp"

int main(int argc, const char** argv) {
    (void)argc;
    (void)argv;

  //       ft::vector<int> myvector (3,100);
  //       ft::vector<int>::iterator it;

  // it = myvector.begin();
  // it = myvector.insert ( it , 200 );

  // myvector.insert (it,2,300);

  // // "it" no longer valid, get a new one:
  // it = myvector.begin();

  //   ft::vector<int> anothervector (2,400);
  // myvector.insert (it+2,anothervector.begin(),anothervector.end());

  // int myarray [] = { 501,502,503 };
  // myvector.insert (myvector.begin(), myarray, myarray+3);

  // std::cout << "myvector contains:";
  // for (it=myvector.begin(); it<myvector.end(); it++)
  //   std::cout << ' ' << *it;
  // std::cout << '\n';
         ft::vector<int> myvector;

  // set some values (from 1 to 10)
  for (int i=1; i<=10; i++) myvector.push_back(i);

        // erase the 6th element
        myvector.erase (myvector.begin() + 5);

        // erase the first 3 elements:
        ft::vector<int>::iterator ii = myvector.erase (myvector.begin(), myvector.begin() + 3);
        std::cout << *ii << std::endl;
        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); ++i)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';
    ft::vector<std::string> vec2(100, "55");
    ft::vector<int> vec1(100, 10);
    std::cout << vec1.size() << std::endl;
    std::cout << vec1.capacity() << std::endl;
    vec2.at(0) = "888";
    std::cout << vec2[0] << std::endl;
    std::cout << vec2.size() << std::endl;
    vec2.pop_back();
    vec2.pop_back();
    vec2.pop_back();
    vec2.pop_back();
    vec2.pop_back();
    vec2.pop_back();
    vec2.pop_back();
    vec2.pop_back();
    vec2.pop_back();
    vec2.pop_back();
    std::cout << vec2.size() << std::endl;
    std::cout << vec2.capacity() << std::endl;
    std::cout << vec2.max_size() << std::endl;
    ft::vector<int> test(5,3);
    test[4] = 1888;
    ft::vector<int>::const_reverse_iterator itest = test.rend() - 1;
    std::cout << *itest << std::endl;
    ft::vector<int> vec9(5,12);
    ft::vector<int> vec8(3,130);
    
    // vec8.assign(-3, 12);
    // ft::vector<int>::iterator it = vec9.begin();
    // vec9.assign(vec8.begin(), vec8.end());
    vec9.assign(12, 111);
    // while (it != vec9.end())
    // {
    //     std::cout << *it << std::endl;
    //     it++;
    // }
    std::cout << vec9.size() << std::endl;
    std::cout << vec9.capacity() << std::endl;
    vec9.resize(3);
    std::cout << vec9.size() << std::endl;
    std::cout << vec9.capacity() << std::endl;
    for(int i = 0; i < (int)vec9.size(); i++)
        std::cout << vec9[i] << std::endl;
    ft::vector<int> first;
    ft::vector<int> second;
    ft::vector<int> third;

    first.assign (7,100);             // 7 ints with a value of 100

    ft::vector<int>::iterator it;
    it=first.begin() + 1;

    second.assign (it,first.end() - 1); // the 5 central values of first

    int myints[] = {1776,7,4};
    third.assign (myints,myints+3);   // assigning from array.

    std::cout << "Size of first: " << int (first.size()) << '\n';
    std::cout << "Size of second: " << int (second.size()) << '\n';
    std::cout << "Size of third: " << int (third.size()) << '\n';

    ft::vector<int> ob(5, 22);
    
    ft::vector<int>::iterator oit = ob.begin();
    ft::vector<int>::iterator oitt = ob.end();
    ft::vector<int> obb(10, 13);
    obb.reserve(15);
    
    std::cout << obb.size() << '\n';
    std::cout << obb.capacity() << '\n';
    obb.insert(obb.end() - 5, 4, 12);
    std::cout << obb.size() << '\n';
    std::cout << obb.capacity() << '\n';

    for (size_t i = 0; i < obb.size(); i++)
    {
        std::cout << obb[i] << '\n';
    }

    return 0;

    // ft::vector<int> v(vv);
    // vv.resize(0);
    // std::cout << vv.size() << std::endl;
    // std::cout << vv.capacity() << std::endl;
    // // vv.push_back(3);
    // std::cout << vv.size() << std::endl;
    // ft::vector<int> vec;
    // vec.pop_back();
    // std::cout << vec.size() << std::endl;
    // ft::vector<int> vec5;
    // vec5.pop_back();
    // std::cout << vec5.size() << std::endl;

    // std::cout << "********************************\n";
    // vec5.front() = 22;
    // std::cout << vec.size() << std::endl;
    // std::cout << vec.max_size() << std::endl;
    // vec1.reserve(300);
    // std::cout << vec1.size() << std::endl;
    // vec.at(vec.size() - 1) = 5556;
    // std::cout << vec.back() << std::endl;
    // vec1.back() = 333;
    // std::cout << vec1.back() << std::endl;
    // vec1.front() = 100021;
    // std::cout << vec1.front() << std::endl;

    // return 0;
}

// #include <utility>      // std::pair, std::make_pair
// #include <string>       // std::string
// #include <vector>       // std::string
// #include <iostream>     // std::cout
// #include "srcs/utils/ft_utility.hpp"
// #include "srcs/utils/ft_type_traits.hpp"
// #include "srcs/utils/ft_iterator.hpp"
// #include "srcs/utils/ft_algorithm.hpp"
// // #include <iostream>     // std::cout, std::boolalpha
// #include <algorithm>    // std::lexicographical_compare
// #include <cctype>       // std::tolower


// template <class T>
// typename ft::enable_if<ft::is_integral<T>::value,bool>::type
//   is_odd (T i) {return bool(i%2);}

// // 2. the second template argument is only valid if T is an integral type:
// template < class T, class = typename ft::enable_if<ft::is_integral<T>::value>::type>
// bool is_even (T i) {return !bool(i%2);}

// bool mypredicate (int i, int j) {
//   return (i==j);
// }

// bool mycomp (char c1, char c2)
// { return std::tolower(c1)<std::tolower(c2); }

// int main () 
// {
//   ft::pair <std::string,double> product1;                     // default constructor
//   ft::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
//   ft::pair <std::string,double> product3 (product2);          // copy constructor

//   product1 = ft::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)

//   product2.first = "shoes";                  // the type of first is string
//   product2.second = 39.90;                   // the type of second is double

//   std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
//   std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
//   std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';
//     int myints[] = {20,40,60,80,100};               //   myints: 20 40 60 80 100
//   ft::vector<int>myvector (myints,myints+5);     // myvector: 20 40 60 80 100

//   // using default comparison:
//   if ( ft::equal (myvector.begin(), myvector.end(), myints) )
//     std::cout << "The contents of both sequences are equal.\n";
//   else
//     std::cout << "The contents of both sequences differ.\n";

//   myvector[3]=81;                                 // myvector: 20 40 60 81 100

//   // using predicate comparison:
//   if ( ft::equal (myvector.begin(), myvector.end(), myints, mypredicate) )
//     std::cout << "The contents of both sequences are equal.\n";
//   else
//     std::cout << "The contents of both sequences differ.\n";

//   char foo[]="Apple";
//   char bar[]="Apple";

//   std::cout << std::boolalpha;

//   std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

//   std::cout << "Using default comparison (operator<): ";
//   std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+5);
//   std::cout << '\n';

//   std::cout << "Using mycomp as comparison object: ";
//   std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+5,mycomp);
//   std::cout << '\n';
//     std::cout << std::boolalpha;
//   std::cout << "is_integral:" << std::endl;
//   ft::is_integral<double> c;
//   if (!c)
//     std::cout << "yeeeeeeeeeeeees !!\n";
//   std::cout << "char: " << ft::is_integral<char>::value << std::endl;
//   std::cout << "int: " << ft::is_integral<int>::value << std::endl;
//   std::cout << "float: " << ft::is_integral<float>::value << std::endl;

  
//   short int i = 1;    // code does not compile if type of i is not integral
//   std::cout << std::boolalpha;
//   std::cout << "i is odd: " << is_odd(i) << std::endl;
//   std::cout << "i is even: " << is_even(i) << std::endl;

//   typedef ft::iterator_traits<const int*> traits;
//   if (typeid(traits::difference_type)==typeid(ptrdiff_t))
//     std::cout << "const int* is a random-access iterator\n\n";

//   ft::vector<int> vv;
//   for (int i=0; i<10; i++) vv.push_back(i);

//   ft::reverse_iterator<ft::vector<int>::iterator> from,until;
//   from.base();
//   from = until + 100;
//   if (until < from)
//     std::cout << "until inferior than from\n";
//   else if (until > from)
//     std::cout << "until superior than from\n";
//   else if (until == from)
//     std::cout << "until equal from\n";
    
//   std::cout << "myvector has " << (until-from) << " elements.\n";
//   return 0;
// }