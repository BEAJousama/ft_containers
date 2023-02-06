#include "map_example.hpp"
#include <iostream>
#include <map>

int main() {

std::map<int, std::string> mm;
mm.insert(std::make_pair(120, "hell"));
mm.insert(std::make_pair(15, "hell"));
mm.insert(std::make_pair(25, "hell"));
mm.insert(std::make_pair(35, "hell"));
mm.insert(std::make_pair(45, "hell"));
mm.insert(std::make_pair(10, "hell"));
mm.insert(std::make_pair(105, "hell"));
std::map<int, std::string>::iterator it = mm.begin();

while(it != mm.end()) {
 std::cout << it->first << std::endl;
 it++;
}
Map<int, int> map;
map.insert(1, 10);
map.insert(2, 20);
map.insert(3, 30);
map.insert(4, 40);
map.insert(5, 50);
std::cout << "Map after insertion: " << std::endl;
// map.print();

std::cout << map.tree.root->left->left->data.first << std::endl;
// map.remove(2);
// map.remove(4);

std::cout << "Map after removal: " << std::endl;
// map.print();

// std::cout << "Value at key 3: " << map[3] << std::endl;
// map[3] = 35;
// std::cout << "Value at key 3 after update: " << map[3] << std::endl;

// std::cout << "Exists of key 1: " << map.exists(1) << std::endl;
// std::cout << "Exists of key 6: " << map.exists(6) << std::endl;

return 0;

};