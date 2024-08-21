# 实验一：约瑟夫环求解

## PreKnowledge

### sh 脚本的使用

我们在本实验中提供了 `Mac.sh` 和 `Win.bat`，使用 Mac 的同学们可以在命令行中 cd 到文件夹解压之后所在的工作目录（此时 `Mac.sh` 就在工作目录下），运行 `sh Mac.sh` 即可，`Win.bat` 的使用同理，可自行百度

### C++ 简单介绍

C 语言是一门面向过程的语言，而 C++ 是一门面向对象的语言。本次实验只需要用到简单的 C++ 知识

1. 库的不同

   1. C++ 将 C 语言中的标准库`<xxx.h>`换成了 `<cxxx>`，例如 `<stdio.h> -> <cstdio>`

   2. C++ 中常用的输入输出库为 `<iostream>`，读写文件的库为 `<fstream>`
      ```cpp
      #include <iostream>
      
      int main() {
        int a;
       	std::cin >> a;
        std::cout << "The number you've just put in is: " << a << endl;
        return 0;
      }
      ```

      上述文件还可以按照如下方式组织：

      ```cpp
      #include <iostream>
      using namespace std; // 告诉编译器你使用了标准命名空间 std
      
      int main() {
        int a;
        cin >> a;
        cout << a << endl;
        return 0;
      }
      ```

      `cin` 和 `cout` 分别是标准输入输出流，相比于 `scanf` 和 `printf` 的好处在于可以自动识别变量类型。其他区别请自行查阅。

   3. `fstream` 库读写文件请自行查阅

2. **类**
   类是一个面向对象很重要的特性。常用于替代 struct，简单用法如下：

   ```cpp
   class solution {
   private: // 私有变量，只能在类成员函数中访问
     int a;
     int b;
   public: // 公共部分
     solution(int a=0, int b=0) : a(a), b(b) {} // 默认为 0 0
     int mul() {
       return a * b;
     }
     int add() {
       return a + b;
     }
     int minus() {
       return a - b;
     }
   };
   
   int main() {
     solution s(1, 2); // 如果这里不添加括号，a 和 b 就是 0 0
     cout << s.add() << endl;
     cout << s.mul() << endl;
     cout << s.minus() << endl;
     return 0;
   }
   ```

3. 引用
   请看一段示例：

   ```C++
   struct node {
     int val;
     node *next;
     node() : val(0), next(nullptr) {}
     node(int elem, node *nex) : val(elem), next(nex) {}
   };
   
   void initList(node *&head) {
     head = new node();
   }
   
   // 如果是在 C 语言中：
   struct node {
     int val;
   	struct node *next;
   };
   
   void initList(struct node **head) {
     *head = (struct node *)malloc(sizeof(struct node));
     (*head)->next = NULL;
   }
   ```

   引用在创建时产生，创建之后不可更改。省去了频繁取地址的麻烦，也让代码变得更加简洁。

   ```cpp
   int a = 0;
   int &b = a;
   b = 1;
   cout << a << endl; // 输出 1
   ```

   4. `new` and `delete`
      new 出来的空间要用 delete 释放，malloc 的空间要用 free 释放。

      ```cpp
      int *arr = new int[100];
      delete [] arr;
      ```

      

   ## 良好的代码风格

   > 良好的代码风格将会有助于你构建一个代码量更大的文件

   什么是良好的代码风格？

   1. 变量、函数等的命名有意义，常见驼峰命名法或下划线命名，比如 `file_name`, `iPad`, `iPhone`

   2. 注释量适当，代码：注释 $\approx$​ 4 : 1

   3. 多空格，但不能乱空格

      应该空格的地方：

      ​	逗号之后，如 `int a, b`

      ​	最高一级运算符中间：`(a+b) * (c+d)`

      不应该空格的地方：

      ​	链表：`node->val`

      ​	运算符较多时最低级运算法中间：`(a+b) * (c+d)`

​	具体的操作应参照实际情况，空格的目的是为了让代码可读性更强，而不是墨守陈规



## Contents

约瑟夫(Joseph)问题的一种描述是：编号为 $1,2, \ldots, n$ 的 $n$ 个人按顺时针方向围坐一圈, 每人持有一个密码(正整数)。一开始选任一个正整数作为报数上限值 $m$， 从第一个人开始按时针方向自 1 开始顺序报数，报到 $m$ 时停止报数。报 $m$ 的人出列，将它的密码作为新的 $m$ 值，再从下个人开始新一轮报数，如此反复，直到剩下最后一人则为获胜者。试设计一个程序求出出列顺序。

## Requirement

1. 利用单向循环链表存储
2. 请不要在终端人工输入，设计成读取相对路径 `./data/testcase.txt` 中的数据进行运算
3. 输出直接使用 `cout` 即可，自动化脚本做了重定向处理

我们提供的文件结构如下：***请仔细阅读***

```txt
.
├── Mac.sh  # 用于 Mac OS 运行并测试的脚本
├── Win.bat # 用于 Windows 运行并测试的脚本
├── ans.exe # 为 Windows 同学提供的可输出正确答案的程序
├── ans_mac # 为 Mac OS 同学提供的可输出正确答案的程序
├── document
│   └── README.md
├── generate_test_case.py # 生成测试数据
├── judge.py   # 判断你的代码结果是否和助教的结果相同
└── yourcode.cpp # 你要补充的代码
```

其中 `generate.py` 将会产生 `./data/testcase.txt`，此文件为 $3$ 行，第一行为一个数字 $n$，代表人数，第二行为 $n$ 个数据，表示 $n$ 个人的password，彼此之间用**空格**间隔开，第三行是 $m$.

```txt
n
data_1 data_2 data_3 ... data_n
m
```

3. 你需要和助教讲解你的代码，如果不能讲解，可能当成抄袭处理。这时良好的代码风格尤为重要

## Output

输出 $n$ 个数据，即正确的出列顺序，用**空格**间隔

## Example

- Input:
  ```txt
  7
  3 1 7 2 4 8 4
  20
  ```

- Output:
  ```txt
  6 1 4 7 2 3 5
  ```

## Data Range

- $2^{8} \leqslant n < 2^{12}$
- $1 \leqslant$ password[i] $< 2^{10}$
- $1 \leqslant m < 2^{12}$​

## bonus

**如果你在某处时间复杂度上做出了优化，将会获得一个标记，这个标记可能最终对你的总评产生一定的影响，当然检查的时候我们并不会告诉你你是否做出了这个优化**

写的好的同学的代码将有展示的机会

## 注意事项

- 请不要使用 C++ 的 STL 或者面向结果编程，不然将会获得 0 分

> 本实验文档以及所有代码均为助教劳动成果，请勿用于盈利目的
>
> * 来找助教检查实验之前请自行运行脚本测试