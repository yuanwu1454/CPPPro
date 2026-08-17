#include "Containers.h"

#include <cassert>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

void testContainers()
{
    // vector 是动态数组，支持连续存储、下标访问和尾部追加。
    std::vector<int> scores{90, 80, 95};
    scores.push_back(88);
    assert(scores.size() == 4);
    assert(scores[2] == 95);

    // set 保存唯一且有序的元素，重复插入不会增加元素数量。
    std::set<std::string> tags{"cpp", "primer", "cpp"};
    assert(tags.size() == 2);

    // map 保存有序的键值对，at() 访问不存在的键时会抛出异常。
    std::map<std::string, int> orderedScores;
    orderedScores["Alice"] = 95;
    assert(orderedScores.at("Alice") == 95);

    // unordered_map 基于哈希表，适合按键快速查找，不保证遍历顺序。
    std::unordered_map<std::string, int> counts;
    ++counts["cpp"];
    ++counts["cpp"];
    assert(counts.at("cpp") == 2);
}
