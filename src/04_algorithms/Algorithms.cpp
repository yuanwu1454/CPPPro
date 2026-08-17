#include "Algorithms.h"

#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

void testAlgorithms()
{
    // 标准算法通过迭代器操作容器，与具体容器类型解耦。
    std::vector<int> values{3, 1, 4, 2};
    std::sort(values.begin(), values.end());

    // find 返回目标元素的迭代器；未找到时返回 end()。
    const std::vector<int>::iterator found =
        std::find(values.begin(), values.end(), 4);

    // accumulate 从初始值开始累加范围内的元素。
    const int total = std::accumulate(values.begin(), values.end(), 0);

    assert(values == std::vector<int>({1, 2, 3, 4}));
    assert(found != values.end());
    assert(total == 10);

    // remove 只移动元素并返回新的逻辑结尾，erase 才真正缩小容器。
    values.erase(std::remove(values.begin(), values.end(), 2), values.end());
    assert(values == std::vector<int>({1, 3, 4}));
}
