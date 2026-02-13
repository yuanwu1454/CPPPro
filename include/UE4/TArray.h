#pragma once
template<typename InElementType, typename InAllocator>
class TArray
{
    // 模板之间实现跨类型友元的方法
    template <typename OtherInElementType, typename OtherAllocator>
    friend class TArray;

    
};
