## 第十四章 C++中的代码重用

### 14.1 包含对象成员的类

例子：根据定义开发Student类：姓名+考试分数

* 姓名：使用一个由他人开发好的类的对象来表示：
  * 可以使用一个String类或标准C++ string类的对象来表示姓名。
* 考试分数：
  * 可以在标准C++库中查找一个能够表示这种数据的类。
  * C++库提供了一个表示double数组的库：valarray



#### 14.1.1 valarray 类简介

valarray 类由头文件valarray支持，这个类用于处理数值（或具有类似特性的类），它支持诸如将数组中所有元素的值相加以及在数组中找出最大和最小的值等操作。

* valarray被定义为一个模板类，以便能够处理不同的数据类型。

  * 模板特性：意味着声明对象时，必须指定具体的数据类型。

  * 因此使用 valarry类来声明一个对象时，需要在标识符 valarray 后面加上一对尖括号，并在其中包含所需要的数据类型：

    * ```c++
      valarray<int> q_values;
      valarray<double> weights;
      ```

* valarray类的构造函数和其他类方法使用例子：

  * ```c++
    double gpa[5] = {3.1, 3.5, 3.8, 2.9, 3.3};
    valarray<double> v1;		// an array of double, size 0
    valarray<int> v2(8);		// an array of 8 int elements
    valarray<int> v3(10, 8);	// an array of 8 int elements, each set to 10
    valarray<double> v4(gpa, 4); // an array of 4 elements, initialized to the first 4 elements of gpa
    ```

  * 从中可知，可以创建**长度为零的空数组**、**指定长度的空数组**、**所有元素度被初始化为指定值的数组**、**用常规数组中的值进行初始化的数组**。

  * 在 C++11 中，也可使用初始化列表：

    * ```c++
      valarray<int> v5 = {20, 32, 17, 9};
      ```

* valarray 类的一些方法：

  * ```c++
    operator[]():	//让您能够访问各个元素
    size():		    //返回包含的元素数
    sum():		    //返回所有元素的总和
    max():		    //返回最大的元素
    min():		    //返回最小的元素
    ```





#### 14.1.2 Student 类的设计

已经确定了 Student 类的设计计划：

* 使用一个 string 对象来表示姓名；
* 使用一个 valarray<double>来表示考试分数。

设计方法：

* 方法一【no】以公有的方式从这两个类派生出 Student 类，这将是多重继承，C++允许但不合适。

  * 因为学生与这些类之间的关系不是 is-a 模型。
  * 学生不是姓名，也不是一组考试成绩，这里的关系是has-a，学生有性命，也有一组考试分数。
  * 通常用于建立 has-a 关系的C++技术是组合：
    * 即创建一个包含其他类对象的类。

* 方法二【yes】组合（包含），即创建一个包含其他类对象的类：

  * ```c++
    class Student
    {
    private:
        string name;
        valarray<double> scores;
    };
    ```

  * 上述类将数据成员声明为私有的，即 Student 类的成员函数可以使用 string 和 valarray<double> 类的公有接口来访问和修改 name 和 scores 对象，但在类的外面不能这样做，而只能通过 Student 类的公有接口访问 name 和 score：

    * ![image](https://github.com/CoderSuHang/Cpp-Primer-Plus-Notes/assets/104765251/10f0c01f-f05b-4748-8fd7-4271932184ae)
    * 这种情况通常被描述为Student类获得了其成员对象的实现，但没有继承接口。

接口和实现：

* 使用公有继承时，类可以继承接口，可能还有实现（基类的纯虚函数提供接口，但不提供实现）。
  * 获得接口是 is-a 关系的组成部分。
* 而使用组合，类可以获得实现，但不能获得接口。
  * 不继承接口是 has-a 关系的组成部分。

has-a关系：

* 类对象不能自动获得被包含对象的接口是一件好事见P536



#### 14.1.3 Student 类示例
