#include "../utils/AvlTree.hpp"
#include "../utils/ft_utility.hpp"
#include <iostream>

int main()
{
    ft::AvlTree<ft::pair<int, int>, std::less<int>, std::allocator<std::pair<int, int> > > tree;
    ft::pair<int, int> p1 = ft::make_pair(1, 100);
    ft::pair<int, int> p2 = ft::make_pair(2, 120);
    ft::pair<int, int> p3 = ft::make_pair(3, 130);
    ft::pair<int, int> p4 = ft::make_pair(4, 140);
    ft::pair<int, int> p5 = ft::make_pair(5, 150);

    std::cout << "main\n";
    tree.insert(p1);
    tree.insert(p2);
    tree.insert(p3);
    tree.insert(p4);
    tree.insert(p5);

    tree.remove(p4);
    tree.remove(p5);

    tree.insert(ft::make_pair(0,0));
    tree.remove(ft::make_pair(3,130));

    std::cout<< tree._root->right->left->value.first << std::endl;
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