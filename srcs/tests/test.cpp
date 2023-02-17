#include "../utils/AvlTree.hpp"
#include "../utils/ft_utility.hpp"
#include "../vector/vector.hpp"
#include "../map/map.hpp"
#include <iostream>
#include <map>
#include <vector>

int main()
{
    // std::pair<int, int> v;
    // ft::AvlTree<ft::pair<int, int>, std::less<int>, std::allocator<std::pair<int, int> > > tree;
    ft::pair<int, int> p1 = ft::make_pair(1, 100);
    ft::pair<int, int> p2 = ft::make_pair(2, 120);
    ft::pair<int, int> p3 = ft::make_pair(3, 130);
    ft::pair<int, int> p4 = ft::make_pair(4, 140);
    ft::pair<int, int> p5 = ft::make_pair(5, 150);
    // std::map<int, int> m;
    ft::map<int, std::string> map1;
    std::map<int, std::string> map2;

    for (int i = 0; i < 5; i++)
    {
        map2.insert(std::make_pair(i, "i*2"));
    }

    // for (int i = 0; i < 5; i++)
    // {
    //     map1.erase(i);
    // }
    map2.clear();

    std::cout << map2[2] << std::endl;
    std::cout << map2.size() << std::endl;
    // for (int i = 0; i < 5; i++)
    // {
    //     map2.insert(std::make_pair(i, i*2));
    // }

    // map1.insert(p1);
    // map1.insert(p2);
    // map1.insert(p5);
    // map1.insert(p4);
    // map1.insert(p5);

    // map2.insert(std::make_pair(1, 100));
    // map2.insert(std::make_pair(2, 120));
    // map2.insert(std::make_pair(3, 130));
    // map2.insert(std::make_pair(4, 140));
    // map2.insert(std::make_pair(5, 150));

    // std::cout << map1.erase(3) << std::endl;
    // std::cout << map2.erase(3) << std::endl;
    // std::cout << map1.lower_bound(3)->first << std::endl;
    // std::cout << map2.lower_bound(3)->first << std::endl;
    // std::cout << map2.equal_range(20).second->first << std::endl;
    // std::cout << map1.equal_range(20).second->first << std::endl;
    // std::cout << map2.count(22) << std::endl;
    // std::cout << map1.count(22) << std::endl;
    // m[5] = 1;
    // m[6] = 2;
    // m[7] = 3;
    // m[8] = 4;
    // m[9] = 5;
    // std::cout << m.erase(6) << std::endl;
    // std::cout << m.erase(7) << std::endl;
    // std::cout << m.erase(7) << std::endl;
    // std::cout << "main\n";
    // tree.insert(p1);
    // tree.insert(p2);
    // tree.insert(p3);
    // tree.insert(p4);
    // tree.insert(p5);

    // std::cout << tree.size() << std::endl;
    // tree.clear();
    // std::cout << tree.size() << std::endl;
// while (1)
// {
//     /* code */;
// }

    // tree.remove(p5);

    // tree.remove(ft::make_pair(3,130));

    // std::cout<< tree._root->left->left->value.first << std::endl;
    // std::cout << tree.search(p2)->value.second << std::endl;
    // std::cout << tree.search(p3)->value.second << std::endl;
    // std::cout << tree.search(p5)->value.second << std::endl;
    // std::cout << tree.search(p1)->value.second << std::endl;
    // std::cout << tree.search(ft::make_pair(15,177))->value.second << std::endl;
    // std::cout << tree._getSuccessor(tree.search(ft::make_pair(15,177)))->value.second << std::endl;
    // std::cout << (*(--(--tree.end()))).first << std::endl;
    // std::cout << tree._root->parent->left->value.first << std::endl;
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