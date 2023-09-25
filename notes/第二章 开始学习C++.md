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
  * image-20230925153804065

##### 2.1.1.2 创建文件

* 右击“解决方案资源管理器”的“源文件”进行添加“新建项”：
  * ![image](https://github.com/CoderSuHang/Cpp-Primer-Plus-Notes/assets/104765251/4179cf5e-c3f1-41b7-b5e0-5d9a871ae86a)


* 设置文件名：
  * ![image](https://github.com/CoderSuHang/Cpp-Primer-Plus-Notes/assets/104765251/c2c6e443-72ac-4c50-9463-70fd1c272491)


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
