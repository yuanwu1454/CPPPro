#include "FriendTest.h"
#include "Common.h"

// 在 C++ 中，友元（Friend）的本质是：编译器层面为特定函数 / 类开放的 “访问权限豁免” 机制
// —— 突破类的访问控制（private/protected）限制，
// 允许被声明为友元的外部实体（函数 / 类）直接访问类的私有 / 保护成员，而无需通过类的公有接口。
// 1. 友元是 “编译期特权”：
// 运行时内存布局无任何变化（私有成员的内存地址、偏移量和无友元时完全一致），只是编译器在编译阶段跳过了对友元的访问权限检查。
// 2. 友元列表的存储：
// 编译器在解析类定义时，会在类的 “符号表” 中记录友元信息（函数 / 类的标识符），后续检查成员访问时，只需查表判断是否在友元列表中即可。
// 3. 为什么友元不能传递：
// 比如 A 是 B 的友元，B 是 C 的友元，但 A 不在 C 的友元列表中 → 编译器检查时，A 访问 C 的私有成员会触发规则 3，直接报错。

// 友元列表

// ✅ 单向性：A 是 B 的友元 ≠ B 是 A 的友元（比如 B 能访问 A 的私有成员，但 A 不能访问 B 的私有成员）；
// ✅ 非传递性：A 是 B 的友元，B 是 C 的友元 ≠ A 是 C 的友元；
// ✅ 非继承性：A 是 B 的友元，B 的子类 D ≠ A 是 D 的友元（除非 D 显式声明 A 为友元）；
// ✅ 友元声明的位置无关性：友元声明写在类的 public/private/protected 区域，效果完全一致（比如写在 private 里和 public 里，授权范围相同）。

// 1. 友元的核心特性（最常考）
// 2. 友元的声明与定义（编程题 / 改错题）
// 3. 友元与封装的关系（面试问答）
// 4. 友元与运算符重载（编程题高频）
// 5. 友元与 const 成员函数（易混淆点）

// 友元不仅能访问私有变量，还能访问私有函数；
// 友元对 protected 成员也有同样的访问权限（不只是 private）。
namespace FriendTest
{

    class Product;
    class ProductPrint {
    public:
        // 声明成员函数（先声明，后实现）
        void Show(const Product& p);

    };
    
    // 第一步：原有的Product类（假设代码不可修改，仅需声明友元）
    class Product {
    private:
        // 私有变量：无任何公有函数访问
        double price;  // 单价
        int stock;     // 库存

        // 本质上授权
        // 类
        friend class ProductAnalyzer;
        // 普通函数
        friend void showPrice(const Product& p);
        // 类成员函数
        friend void ProductPrint::Show(const Product& p);
    public:
        // 仅保留构造函数，无其他公有接口
        Product(double p, int s) : price(p), stock(s) {}
    };

    void showPrice(const Product& p)
    {
        cout <<"price:" << p.price << " stock:" << p.stock <<endl;
    }

    void ProductPrint::Show(const Product& p)
    {
        cout <<"price:" << p.price << " stock:" << p.stock <<endl;        
    }
    
    // 第二步：新增的友元类ProductAnalyzer（无需修改Product的其他代码）
    class ProductAnalyzer {
    public:
        // 直接访问Product的私有变量price和stock
        double calculateTotalValue(const Product& product) {
            return product.price * product.stock;
        }

        // 甚至可以修改私有变量（谨慎使用）
        void adjustPrice(Product& product, double newPrice) {
            // 可添加校验逻辑，避免非法价格
            if (newPrice > 0) {
                product.price = newPrice;
            }
        }
    };

    
    void Test()
    {
        Product phone(2999.99, 50);  // 手机：单价2999.99，库存50
        ProductAnalyzer analyzer;

        // 访问私有变量：计算总价
        double total = analyzer.calculateTotalValue(phone);
        cout << "before adjustPrice total price:total " << total << endl;  // 输出：149999.5

        // 修改私有变量：调整价格
        analyzer.adjustPrice(phone, 2499.99);  // 输出：价格已修改为：2499.99
        // 验证修改结果
        cout << "after adjustPrice total price:" << analyzer.calculateTotalValue(phone) << endl;  // 输出：124999.5

        showPrice(phone);
    }
}