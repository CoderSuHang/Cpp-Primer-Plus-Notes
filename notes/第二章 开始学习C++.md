## 第二章 开始学习C++

### 2.1 创建第一个C++程序

`C++极其强调大小写！`

​	这里书中直接跳转到程序介绍，针对使用的Visual Stdio 2019编译软件如何使用操作，没有具体的介绍。因此我采用**黑马程序员**B站提供的视频进行学习如何新建项目工程文件，链接如下：

​	【黑马程序员匠心之作|C++教程从0到1入门编程,学习编程不再难】 https://www.bilibili.com/video/BV1et411b73Z/?p=2&share_source=copy_web&vd_source=a0dbe312acd17ef7f1fb082726d496a7

​	其次**180斤的华尔兹**UP主的视频用的最新版编译器，并且按照书本知识进行介绍，可以留意一下：

​	【《C++  Primer Plus》第六版 零基础从头学(2023) 持续更新中...】 https://www.bilibili.com/video/BV1sK41127iZ/?share_source=copy_web&vd_source=a0dbe312acd17ef7f1fb082726d496a7

#### 2.1.1 创建步骤

编写一个C++程序的4个步骤：

* 创建项目
* 创建文件
* 编写代码
* 运行程序

##### 2.1.1.1 创建项目

* 1.点击文件创建，选择C++空项目：
  * ![image](https://github.com/CoderSuHang/Cpp-Primer-Plus-Notes/assets/104765251/fb15e5a0-3a50-4816-bf21-7dd3465bb1fb)

* 2.文件命名：
  * ![image](https://github.com/CoderSuHang/Cpp-Primer-Plus-Notes/assets/104765251/993360a3-9893-49a9-92a2-05f0c6a34d7b)


##### 2.1.1.2 创建文件

* 右击“解决方案资源管理器”的“源文件”进行添加“新建项”：
  * ![image](https://github.com/CoderSuHang/Cpp-Primer-Plus-Notes/assets/104765251/4179cf5e-c3f1-41b7-b5e0-5d9a871ae86a)


* 设置文件名：
  * ![image](https://github.com/CoderSuHang/Cpp-Primer-Plus-Notes/assets/104765251/b53a3f28-e41b-4bf6-80d7-6d694bc1a904)



##### 2.1.1.3 编写代码

* ```c++
  //myfirst.cpp -- 使用cout生成字符输出
  
  #include<iostream>
  int main()
  {
  	using namespace std;						//make definitions visible
  	cout << "Come up and C++ me some time.";
  	cout << endl;								//start a new line
  	cout << "You won't regret it!" << endl;		//more output
  
  	return 0;
  }
  ```

##### 2.1.1.4 运行程序

* 点击“本地Windows调试器”
  * ![image](https://github.com/CoderSuHang/Cpp-Primer-Plus-Notes/assets/104765251/d18a31be-3966-40e6-8e35-34b778d96dac)

  * ![image](https://github.com/CoderSuHang/Cpp-Primer-Plus-Notes/assets/104765251/7e4ac5ab-164d-4ffd-9731-e0f306015e7e)


### 2.1.2 程序结构介绍

​	第一个程序使用了C++工具cout生成字符字符：

* ```c++
  //myfirst.cpp -- 使用cout生成字符输出
  
  #include<iostream>
  int main()
  {
  	using namespace std;						//make definitions visible
  	cout << "Come up and C++ me some time.";
  	cout << endl;								//start a new line
  	cout << "You won't regret it!" << endl;		//more output
  
  	return 0;
  }
  ```

​	myfirst.cpp示例包含以下7个元素：

* 注释，由前缀//标识；
* 预处理器编译指令：#include；
* 函数头：int main( )；
* 编译指令：using namespace；
* 函数体，用{和}括起；
* 使用C++的cout工具显示消息的语句；
* 结束main( )函数的return语句。



##### 2.1.2.1 main( )函数

​	1、去掉修饰后的示例如下：

* ``` c++
  int main()
  {
      statements
      return 0;    
  }
  ```

* 这几行表明有一个名为`main()`的函数，并描述了该函数的行为。

* 这几行代码构成了函数定义，该定义由两部分组成：

  * 函数头：int main()
  * 函数体：{和}
  * ![image](https://github.com/CoderSuHang/Cpp-Primer-Plus-Notes/assets/104765251/9228fc19-077c-4a90-b5d1-a1f28128f2f5)


​	2、这里需要注意2点：

* 所有的语句都以分号“;”结束，在C++中不能省略分号；
* main( )中最后一条语句`返回语句`，它结束该函数。

​	3、main( )作为接口的函数头：

* C++语法要求main( )函数的定义以函数头`int main()`开始，该函数头秒速的是main( )和操作系统之间的接口。

* C++函数调用逻辑详细介绍在书本P14页中有所介绍，比较复杂难懂，这里可以先看一遍，后续学习中再继续加深理解；

* 表明main( )函数可以给调用它的函数返回一个整数值，且不从调用它的函数那里获得任何信息：

  * ``` c++
    int main(void)		//与让括号空着等效
    ```

​	4、main( )不能使用其他名称的原因：

* 由于“myfirst.cpp”程序只有一个函数，因此该函数必须担负起main()的责任。
* 在运行C++程序时，通常从main()函数开始执行。
* 因此，如果没有main()，程序将不完整，编译器将指出未定义main()函数。
* 其他特例情况P15有介绍。



##### 2.1.2.2 C++注释

* C++注释用“`//`”，也可以用C的“ /* ”和“ */” ；
* `注意`：应使用注释来说明程序。程序越复杂，注释的价值越大。



##### 2.1.2.3 C++预处理和iostream文件

* 预处理器：

  * 处理名称以#开头的编译指令；

  * 不必执行任何特殊操作来调用该预处理器，它会在编译程序时自动运行。

  * 例如：使用C++输入或输出工具，需要提供这两行代码

    * ``` c++
      #include<iostream>
      using namespace std;
      ```

* iostream：

  * io指的是输入和输出；
  * stream：英文翻译为流，我目前把它理解为数据流
  * 输入输出方案中涉及iostream文件中的多个定义，因此要#include

* `注意`：使用cin和cout进行输入和输出程序必须包含iostream。



##### 2.1.2.4 头文件

* 像iostream这样的文件叫做包含文件，由于被包含在其他文件中，也叫头文件；
* C++风格和C有些许不同，更加简化，有的没有.h扩展名，在这里不再赘述，详情见P16-P17。
* ![image](https://github.com/CoderSuHang/Cpp-Primer-Plus-Notes/assets/104765251/5c43568c-7a3c-438a-a513-fd63a42daba2)




##### 2.1.2.5 名称空间

* 如果使用iostream，而不是iostream.h，则应使用下面的名称空间编译指令来使iostream中的定义对程序可用

  * ``` c++
    using namespace std；
    ```

  * 这叫做using编译指令，以后可以继续深入了解，现在知道怎么用即可

* 也可以只使所需的名称可用，这可以通过使用using声明来实现，便可以使用cin和cout，而不必加上std::来实现：

  * ``` c++
    using std::cout；
    using std::endl；
    using std::cin；
    ```



##### 2.1.2.6 使用cout进行C++输出

* ``` c++
  cout << "Come up and C++ me some time.";
  ```

* 这里具体的解释不再赘述，只是要注意下<<也可以表示左移运算符，这是运算符重载的例子，编译器可以通过上下文来确定运算符的含义。

* 1、控制符endl

  * ``` c++
    cout << endl;
    ```

  * endl：表示重起一行；

  * 这里要`注意`：如果要在两个字符串之间留一个空格，必须将空格包含在字符串中。

* 2、换行符

  * C++还提供了另一种在输出中指示换行的旧式方法：C语言符号\n:

    * 两种符号的应用场景：

      * ①显示字符串时，在字符串中包含换行符，而不是在末尾加上endl，可减少输入量：

        * ``` c++
          cout << "Pluto is a dwarf plant.\n";
          cout << "Pluto is a dwarf plant.\n" << endl;
          ```

      * ①如果要生成一个空行，endl更方便：

        * ``` c++
          cout << "\n";
          cout << endl;
          ```



##### 2.1.2.7 C++源代码的格式化

* 注意：不能把空格、制表符或回车放在元素中间，也不能把回车放在字符串中间。
* C++源代码风格：
  * 每条语句占一行；
  * 每个函数都有一个开始花括号和一个结束花括号，这两个花括号各占一行；
  * 函数中的语句都相对于花括号进行缩进；
  * 与函数名称相关的圆括号周围没有空白。
