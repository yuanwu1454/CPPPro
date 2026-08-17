#include "Classes.h"

#include <cassert>
#include <string>

namespace {
class Account {
public:
    explicit Account(int balance) : balance_(balance) {}

    void deposit(int amount)
    {
        balance_ += amount;
    }

    int balance() const
    {
        return balance_;
    }

private:
    int balance_;
};
}

void testClasses()
{
    // 构造函数负责建立对象的初始状态；explicit 防止隐式转换。
    Account account(100);

    // 成员函数封装对私有数据的修改，调用者不直接访问 balance_。
    account.deposit(50);

    // const 引用只能调用 const 成员函数，适合只读访问对象。
    const Account& readOnlyAccount = account;
    assert(readOnlyAccount.balance() == 150);

    // private 数据和 public 接口体现封装：对象负责维护自身状态。
    assert(std::string("encapsulation") != "inheritance");
}
