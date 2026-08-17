#include "Resources.h"

#include <cassert>
#include <memory>
#include <string>
#include <utility>

namespace {
// 这个类模拟一个需要手动释放的外部资源，例如文件句柄、锁或 socket。
// 实际项目中，Resource 的构造函数可以负责打开资源，析构函数负责关闭资源。
class Resource {
public:
    explicit Resource(const std::string& name) : name_(name), released_(false) {}

    void release()
    {
        released_ = true;
    }

    const std::string& name() const
    {
        return name_;
    }

    bool released() const
    {
        return released_;
    }

private:
    std::string name_;
    bool released_;
};

// RAII：Resource Acquisition Is Initialization。
// 资源在对象构造时获得，在对象析构时释放；调用者不需要记住释放时机。
class ResourceGuard {
public:
    explicit ResourceGuard(Resource& resource) : resource_(resource) {}

    ~ResourceGuard()
    {
        resource_.release();
    }

    ResourceGuard(const ResourceGuard&) = delete;
    ResourceGuard& operator=(const ResourceGuard&) = delete;

private:
    Resource& resource_;
};

// 返回 unique_ptr：函数把资源的唯一所有权交给调用者。
std::unique_ptr<Resource> createResource()
{
    return std::unique_ptr<Resource>(new Resource("configuration file"));
}

// 需要资源的函数只借用它，不负责释放；引用明确表达“调用期间必须存在”。
void useResource(Resource& resource)
{
    assert(!resource.released());
}
}

void testResources()
{
    // ==================== 1. RAII：异常和多分支退出时仍然自动清理 ====================
    // 适用场景：文件、互斥锁、数据库事务、socket、临时目录等有明确生命周期的资源。
    // 如果这里后续代码 return 或抛出异常，guard 离开作用域时仍会执行析构函数。
    Resource lockedResource("mutex");
    {
        ResourceGuard guard(lockedResource);
        useResource(lockedResource);
    }
    assert(lockedResource.released());

    // ==================== 2. unique_ptr：一个明确的资源拥有者 ====================
    // 适用场景：对象只有一个拥有者，例如工厂创建的对象、树节点、文件封装对象。
    // 离开作用域时自动 delete；不应为了方便而复制所有权。
    std::unique_ptr<Resource> resource = createResource();
    assert(resource->name() == "configuration file");
    useResource(*resource);

    // ==================== 3. 移动语义：转移资源，不复制资源本身 ====================
    // 适用场景：返回大对象、把资源交给另一个对象、容器扩容时转移元素。
    // unique_ptr 不允许拷贝；std::move 表示“我不再使用原对象的所有权”。
    std::unique_ptr<Resource> moved = std::move(resource);
    assert(!resource);             // 移动后的 unique_ptr 为空，但仍然是合法对象。
    assert(moved->name() == "configuration file");

    // ==================== 4. shared_ptr：确实存在多个拥有者时共享生命周期 ====================
    // 适用场景：多个对象共同持有缓存、共享的配置对象或图结构节点。
    // 只要还有一个 shared_ptr 存在，资源就不会被释放。
    std::shared_ptr<Resource> first(new Resource("shared cache"));
    {
        std::shared_ptr<Resource> second = first;
        useResource(*first);
        assert(first->name() == second->name());
        assert(first.use_count() == 2);
    }
    assert(first.use_count() == 1);

    // ==================== 5. 引用计数：shared_ptr 的资源释放依据 ====================
    // use_count() 表示当前 shared_ptr 控制块记录的拥有者数量。
    // second 销毁后计数从 2 变为 1；first 最后销毁时，Resource 才释放。
    // 引用计数只解决“什么时候释放”，不解决循环引用；循环关系应使用 weak_ptr。
    std::shared_ptr<int> owner(new int(42));
    assert(owner.use_count() == 1);
    {
        std::shared_ptr<int> observer = owner;
        assert(owner.use_count() == 2);
        assert(*observer == 42);
    }
    assert(owner.use_count() == 1);
}
