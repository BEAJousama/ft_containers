#include "AvlTree.hpp"
#include "ft_utility.hpp"
#include <iostream>

int main()
{
    ft::AvlTree<ft::pair<int, int>, std::less<int>, std::allocator<std::pair<int, int> > > tree;
    ft::pair<int, int> p1 = ft::make_pair(1, 100);
    ft::pair<int, int> p2 = ft::make_pair(1, 120);
    ft::pair<int, int> p3 = ft::make_pair(3, 180);
    std::cout << "main\n";
    tree.insert(p1);
    tree.insert(p2);
    tree.insert(p3);
    std::cout<< tree.root->right->value.second << std::endl;
    // std::allocator<ft::avl_node<ft::pair<int, int> > > alloc;
    // ft::avl_node<ft::pair<int, int> > *newnode  = alloc.allocate(1);
    // ft::avl_node<ft::pair<int, int> > n;

    // n.height = 12;
    // n.value = ft::make_pair(1, 1);
    // n.right = nullptr;
    // n.left = nullptr;

    // alloc.construct(newnode, ft::avl_node<ft::pair<int, int> >(n.value, newnode, newnode, newnode));
    // std::cout << newnode->value.first << std::endl;
}