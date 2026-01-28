
#include "Test.h"

namespace my_namespace
{
    extern int a = 1;
    void testFree()
    {
        int* p = new int;
        int* parr = new int[5];
        void* memory = malloc(sizeof(int));
        int* pi = new(memory) int;
        delete[] parr;
        {
            //指向 8 个 int 的数组的指针
            int (*pa)[8] = new int[5][8];
            // 使用示例：赋值+访问
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 8; j++) {
                    pa[i][j] = i * 8 + j; // 正常赋值
                    cout << pa[i][j] << " ";
                }
                cout << endl;
            }

            delete[] pa;
        }

        {
            //8 个 int 指针组成的数组
            int* pa[8];
            for(int i =0;i< 8;i++)
            {
                pa[i] = new int[5];
            }
            pa[0][0] = 100; 
            cout << pa[0][0] << endl;
            
            for (int i = 0; i < 8; i++) {
                delete[] pa[i];
            }
        }
    }
}

class Vector
{
};