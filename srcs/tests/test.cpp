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
    ft::pair<int, std::string> p1 = ft::make_pair(1, "100");
    ft::pair<int, std::string> p2 = ft::make_pair(2, "120");
    ft::pair<int, std::string> p3 = ft::make_pair(3, "130");
    ft::pair<int, std::string> p4 = ft::make_pair(4, "140");
    ft::pair<int, std::string> p5 = ft::make_pair(5, "150");
    // std::map<int, int> m;
    ft::vector<int> vvv(5,10);
    ft::map<int, std::string> map1;
    std::map<int, std::string> map2;


    // std::cout << it->first << std::endl;
    // std::cout << it1->first << std::endl;

    // for (int i = 0; i < 5; i++)
    // {
    //     map1.insert(ft::make_pair(i, "i*2"));
    // }

    // for (int i = 0; i < 5; i++)
    // {
    //     map1.erase(i);
    // }

    // std::cout << map1[2] << std::endl;
    // std::cout << map1.size() << std::endl;

    // for (int i = 0; i < 5; i++)
    // {
    //     map1.insert(ft::make_pair(i, "i*2"));
    // }

    map2.insert(std::make_pair(1, "100"));
    map2.insert(std::make_pair(2, "120"));
    map2.insert(std::make_pair(3, "130"));
    map2.insert(std::make_pair(4, "140"));
    map2.insert(std::make_pair(5, "150"));

    map1.insert(ft::make_pair(1, "100"));
    map1.insert(ft::make_pair(2, "120"));
    map1.insert(ft::make_pair(3, "130"));
    map1.insert(ft::make_pair(4, "140"));
    map1.insert(ft::make_pair(5, "150"));
    map1.insert(ft::make_pair(6, "160"));
    map1.insert(ft::make_pair(7, "170"));
    map1.insert(ft::make_pair(8, "180"));
    map1.insert(ft::make_pair(9, "190"));

    ft::map <int, std::string>::iterator it = map1.begin();
        ft::map <int, std::string>::iterator it11;
    ft::map <int, std::string>::const_iterator it22 = map1.begin();
    ft::map <int, std::string>::reverse_iterator it1 = map1.rbegin();
    ft::map <int, std::string>::reverse_iterator itr = map1.rend();

    ft::vector <int>::reverse_iterator ittt = vvv.rbegin();
    ft::vector <int>::reverse_iterator itttr = vvv.rend();

    map1.erase(2);

    while(it != map1.end())
    {
        std::cout << it->first << " : " << it->second << "\n" ;
        it++;
    }

    std::cout << "--------------------------------\n" << std::endl;
    // it11 = --map1.end();
    // it = map1.begin();
    // it11--;
    // std::cout << it11->first << " : " << it11->second << "\n" ;
    // it++;
    // it++;
    // it++;
    map1.erase(0);
    map1.erase(1);
    map1.erase(2);
    map1.erase(3);
    map1.erase(4);
    map1.erase(5);
    map1.erase(6);
    map1.erase(7);
    map1.erase(8);
    map1.erase(9);
    std::cout << map1.begin()->first << std::endl;
    map1.erase(map1.begin(), map1.end());
    // std::cout << it->first << " : " << it->second << std::endl;
    std::cout << map1.begin()->first << std::endl;
    // map1.erase(map1.begin(), ++(++(++map1.begin())));
    // map1.erase(8);
    // map1.erase(9);
    // while (it != it11)
    if(map1.begin() == map1.end())
        std::cout << "################################\n" << std::endl;
    // {
    //     map1.erase(it);
    //     it++;
    // }
    std::cout <<map1.size() << std::endl;
    it = map1.begin();

    while(it != map1.end())
    {
        std::cout << it->first << " : " << it->second << "\n" ;
        it++;
    }
    // std::cout << (ittt < itttr) << std::endl;

    std::map <int, std::string>::iterator it2 = map2.begin();

    std::cout<< "\n\n\n" << it2->first << "\n\n\n\n" ;
    (*it2).second = "hello";

    std::cout<< "\n\n\n" << it2->second << "\n\n\n\n" ;
    ft::vector<int>::const_iterator iv = vvv.begin();
    ft::vector<int>::iterator ivv = vvv.begin();
    iv = ivv;

    ivv[1] = 5;
    it22 = it;
    while(it1 != map1.rend())
    {
        std::cout << it1->first << std::endl;
        it1++;
    }

    ft::vector <std::string> v;
    v.push_back("hello");
    ft::vector <std::string>::reverse_iterator itt = v.rbegin();
    std::cout << *itt << std::endl;
    ft::vector<int> hi(10,1);

    // for(auto bye : hi)
    //     std::cout << bye << "my test\n";
    // std::cout << map1.erase(3) << std::endl;
    // std::cout << map2.erase(3) << std::endl;
    // std::cout << map1.lower_bound(3)->first << std::endl;
    // std::cout << map2.lower_bound(3)->first << std::endl;
    // std::cout << map2.equal_range(20).second->first << std::endl;
    // std::cout << map1.equal_range(20).second->first << std::endl;
    // std::cout << map2.count(1) << std::endl;
    // std::cout << map1.count(1) << std::endl;
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