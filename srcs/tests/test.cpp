#include "../utils/AvlTree.hpp"
#include "../utils/ft_utility.hpp"
#include "../vector/vector.hpp"
#include <iostream>
#include <map>
#include <vector>

int main()
{
    ft::AvlTree<ft::pair<int, int>, std::less<int>, std::allocator<std::pair<int, int> > > tree;
    ft::pair<int, int> p1 = ft::make_pair(1, 100);
    ft::pair<int, int> p2 = ft::make_pair(2, 120);
    ft::pair<int, int> p3 = ft::make_pair(3, 130);
    ft::pair<int, int> p4 = ft::make_pair(4, 140);
    ft::pair<int, int> p5 = ft::make_pair(5, 150);

    // std::cout << "main\n";
    tree.insert(p1);
    tree.insert(p2);
    tree.insert(p3);
    tree.insert(p4);
    tree.insert(p5);

    // tree.remove(p4);
    // tree.remove(p5);

    // tree.remove(ft::make_pair(3,130));

    // std::cout<< tree._root->left->left->value.first << std::endl;
    // std::cout << tree.search(p2)->value.second << std::endl;
    // std::cout << tree.search(p3)->value.second << std::endl;
    // std::cout << tree.search(p5)->value.second << std::endl;
    // std::cout << tree.search(p1)->value.second << std::endl;
    // std::cout << tree.search(ft::make_pair(15,177))->value.second << std::endl;
    // std::cout << tree._getSuccessor(tree.search(ft::make_pair(15,177)))->value.second << std::endl;
    std::cout << (*(--(--tree.end()))).first << std::endl;
    std::cout << tree._root->parent->left->value.first << std::endl;
    // std::map<int, int> m;

    // m.insert(std::make_pair(4,140));
    // m.insert(std::make_pair(5,150));
    // m.insert(std::make_pair(6,160));
    // m.insert(std::make_pair(7,170));
    // m.insert(std::make_pair(8,180));
    // m.insert(std::make_pair(9,190));

    // std::cout << m.find(99)->second << std::endl;

    // ft::vector<int> v(5, 15);

    // for (int i = 0 ; i < 500; i++)
    // {
    //     v.insert(v.begin() + 1, 122);
    // }

    // for (int i = 0 ; i < 500; i++)
    // {
    //     std::cout << v[i] << std::endl;
    // }
}