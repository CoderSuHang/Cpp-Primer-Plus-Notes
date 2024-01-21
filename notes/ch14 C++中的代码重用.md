## 第十四章 C++中的代码重用
收
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

程序清单：

* 示例：

  * ```c++
    #pragma once
    // ch14_01_student.h --  defining a Student Class using containment
    #ifndef CH14_01_STUDENT_H_
    #define CH14_01_STUDENT_H_
    
    #include <iostream>
    #include <string>
    #include <valarray>
    
    class Student
    {
    private:
    	// 用ArrayDb类型简化表示std::valarray<double>
    	typedef std::valarray<double> ArrayDb;
    	std::string name;
    	ArrayDb scores;
    	// private method for scores output
    	std::ostream& arr_out(std::ostream& os) const;
    public:
    	Student() : name("Null Student"), scores() {}
    	explicit Student(const std::string & s)
    		: name(s), scores() {}
    	explicit Student(int n) : name("Nully"), scores(n) {}
    	Student(const std::string & s, int n)
    		: name(s), scores(n) {}
    	Student(const std::string & s, const ArrayDb & a)
    		: name(s), scores(a) {}
    	Student(const char* str, const double* pd, int n)
    		: name(str), scores(pd, n) {}
    	~Student() {}
    	double Average() const;
    	const std::string& Name() const;
    	double& operator[] (int i);
    	double operator[] (int i) const;
    // friends
    	// input
    	friend std::istream& operator>>(std::istream& is,
    		Student& stu);	// 1 word
    	friend std::istream& getline(std::istream& is,
    		Student& stu);	// 1 line
    	// output
    	friend std::ostream& operator<<(std::ostream& os,
    		const Student& stu);
    };
    
    #endif
    ```

    * typedef了ArrayDb简化类型表示std::valarray<double>，放在私有部分定义意味着可以在Student类的实现中使用它，但在Student类外面不能使用。

    * explicit关键字的用法：

      * ```c++
        explicit Student(const std::string & s)
        		: name(s), scores() {}
        explicit Student(int n) : name("Nully"), scores(n) {}
        ```

      * 可以用一个参数调用的构造函数将用作从参数类型到类类型的隐式转换函数；

        * 但这样通常不好，第二个构造函数中，第一个参数表示数组的元素个数，而不是数组中的值，因此将一个构造函数用作 int 到 Student 的转换函数是没有意义的，所以使用 explicit 关闭隐式转换。

      * 如果省略 explicit ，则可以：

        * ```c++
          Student doh("Homer", 10);	// store "Homer", create array of 10 elements
          doh = 5;	// reset name to "Nully", reset to empty array of 5 elements
          ```

      * C++和约束

        * C++包含的特性——**使用 explicit 防止单参数构造函数的隐式转换**，使用 const 限制方法修改数据，等等。
        * 这样做的根本原因是: 在编译阶段出现错误优于在运行阶段出现错误。

**1、初始化被包含的对象**

* 构造函数初始化内置类型的成员语法：

  * ```C++
    Queue::Queue(int qs) : qsize(qs) {...};
    ```

  * 前面介绍的示例中的构造函数还使用成员初始化列表初始化派生对象的基类部分：

    * ```c++
      hasDMA::hasDMA(const hasDMA & hs) : baseDMA(hs) {...}
      ```

* 对于继承的对象，构造函数在成员初始化列表中使用类名来调用特定的基类构造函数。

* 对于成员对象，构造函数则使用成员名：

  * ```c++
    Student(const char* str, const double* pd, int n)
    		: name(str), scores(pd, n) {}
    ```

    * 因为该构造函数初始化的是成员对象，而不是继承的对象，所以在初始化列表中使用的是成员名，而不是类名。
    * 初始化列表中的每一项都调用与之匹配的构造函数，即：
      * name(str)调用构造函数 string(const char *)；
      * scores(pd, n)调用构造函数ArrayDb(const double *, int)

* 如果不适用初始化列表语法，C++将使用成员对象所属类的默认构造函数。

* 初始化顺序：

  * 当初始化列表包含多个项目时，这些项目被初始化的顺序为它们被声明的顺序，而不是它们在初始化列表中的顺序。
  * 但如果代码使用一个成员的值作为另一个成员的初始化表达式的一部分时，初始化顺序就非常重要。

**2、使用被包含对象的接口**

被包含对象的接口不是公有的，但可以在类方法中使用它:

* 返回学生平均分数的函数：

  * ```C++
    double Student::Average() const
    {
        if (scores.size() > 0)
            return scores.sum()/scores.size();
        else
            return 0;
    }
    ```

  * Student 对象调用 Student 的方法，而后者使用被包含的 valarray 对象来调用 valarray 类的方法。

* 也可以定义一个使用 string 版本的<<运算符的友元函数：

  * ```c++
    // use string version of operator<<()
    ostream & operator<<(ostream & os, const Student & stu)
    {
        os << "Scores for " << stu.name << ":\n";
        ...
    }
    ```

  * stu.name 是一个 string 对象，operator<<(ostream & os, const Student & stu)必须是 Student 类的友元函数，这样才能访问 name 成员。

* 定义了一个私有的辅助方法使用 valarray 的<<实现来进行输出：

  * ```C++
    // private method
    ostream & Student::arr_out(ostream & os) const
    {
        int i;
        int lim = scores.size();
        if (lim > 0)
        {
            for (i = 0; i < lim; i++)
            {
                os << scores[i] << " ";
                if (i % 5 == 4)
                    os << endl;
            }
            if (i % 5 != 0)
                os << endl;
        }
        else
            os << " empty array ";
        return os;
    }
    ```

  * ```c++
    // use string version of operator<<()
    ostream & operator<<(ostream & os, const Student & stu)
    {
    	os << "Scores for " << stu.name << ":\n";
        stu.arr_out(os);
        return os;
    }
    ```

程序清单：

* 示例：

  * ```c++
    // ch14_02_student.cpp -- Student class using containment
    #include "ch14_01_student.h"
    
    using std::ostream;
    using std::endl;
    using std::istream;
    using std::string;
    
    // public methods
    double Student::Average() const
    {
    	if (scores.size() > 0)
    		return scores.sum() / scores.size();
    	else
    		return 0;
    }
    
    const string& Student::Name() const
    {
    	return name;
    }
    
    double & Student::operator[](int i)
    {
    	return scores[i];
    }
    
    double Student::operator[](int i) const
    {
    	return scores[i];
    }
    
    // private method
    ostream& Student::arr_out(ostream& os) const
    {
        int i;
        int lim = scores.size();
        if (lim > 0)
        {
            for (i = 0; i < lim; i++)
            {
                os << scores[i] << " ";
                if (i % 5 == 4)
                    os << endl;
            }
            if (i % 5 != 0)
                os << endl;
        }
        else
            os << " empty array ";
        return os;
    }
    
    // friends
    // use string version of operator>>()
    istream& operator>>(istream& is, Student& stu)
    {
        is >> stu.name;
        return is;
    }
    
    // use string friend getline(ostream &, const string &
    istream& getline(istream& is, Student& stu)
    {
        getline(is, stu.name);
        return is;
    }
    
    // use string version of operator<<()
    ostream& operator<<(ostream& os, const Student& stu)
    {
        os << "Scores for " << stu.name << ":\n";
        stu.arr_out(os);
        return os;
    }
    ```

**3、使用新的 Student 类**

程序清单：

* 示例：

  * ```c++
    // ch14_03_use_stuc.cpp -- using a composite class
    // compile with student.cpp
    #include <iostream>
    #include "ch14_01_student.h"
    
    using std::cin;
    using std::cout;
    using std::endl;
    
    void set(Student& sa, int n);
    const int pupils = 3;
    const int quizzes = 5;
    
    int main()
    {
    	Student ada[pupils] = 
    		{Student(quizzes), Student(quizzes), Student(quizzes)};
    
    	int i;
    	for (i = 0; i < pupils; ++i)
    		set(ada[i], quizzes);
    	cout << "\nStudent List:\n";
    	for (i = 0; i < pupils; ++i)
    		cout << ada[i].Name() << endl;
    	cout << "\nResults:";
    	for (i = 0; i < pupils; ++i)
    	{
    		cout << endl << ada[i];
    		cout << "average: " << ada[i].Average() << endl;
    	}
    	cout << "Done.\n";
    	return 0;
    }
    
    void set(Student& sa, int n)
    {
    	cout << "Please enter the student's name: ";
    	getline(cin, sa);
    	cout << "Please enter " << n << " quiz scores:\n";
    	for (int i = 0; i < n; i++)
    		cin >> sa[i];
    	while (cin.get() != '\n')
    		continue;
    }
    ```

* 结果：

  * ```c++
    Please enter the student's name: Gil Bayts
    Please enter 5 quiz scores:
    92 94 96 93 95
    Please enter the student's name: Pat Roone
    Please enter 5 quiz scores:
    83 89 72 78 95
    Please enter the student's name: Fleur O'Day
    Please enter 5 quiz scores:
    92 89 96 74 64
    
    Student List:
    Gil Bayts
    Pat Roone
    Fleur O'Day
    
    Results:
    Scores for Gil Bayts:
    92 94 96 93 95
    average: 94
    
    Scores for Pat Roone:
    83 89 72 78 95
    average: 83.4
    
    Scores for Fleur O'Day:
    92 89 96 74 64
    average: 83
    Done.
    ```



### 14.2 私有继承

另一种实现 has-a 关系的途径：私有继承

* 使用私有继承，基类的公有成员和保护成员都将称为派生类的私有成员。
* 这意味着基类方法将不会成为派生对象公有接口的一部分，但可以在派生类的成员函数中使用它们。

公有继承与私有继承的区别：

* 使用公有继承，基类的公有办法将成为派生类的公有方法，派生类将继承基类的接口，属于 is-a 关系；
  * 包含将对象作为一个命名的成员对象添加到类中。
* 使用私有继承，基类的公有方法将成为派生类的私有方法，派生类不继承基类的接口，属于 has-a 关系。
  * 私有继承将对象作为一个未被命名的继承对象添加到类中。

因此私有继承提供的特性与包含相同：

* 获得实现，但不获得接口。所以，私有继承也可以用来实现 has-a关系。



#### 14.2.1 Student 类示例（新版本）

* 要使用**私有继承**，需**使用关键字 private** 而不是 public 来**定义类**：

  * ```c++
    class Student : private std::string, private std::valarray<double>
    {
    public:
        ...
    };
    ```

    * Student 类应从两个类派生而来。
    * 使用多个基类的继承被称为多重继承（multiple inheritance，MI）：
      * MI尤其是公有MI将导致一些问题，需要注意。
    * 新的 Student 类不需要私有数据，因为两个基类已经提供了所需的所有数据成员
      * <u>而上一节的包含版本提供了两个被显式命名的对象成员，而私有继承提供了两个无名称的子对象成员</u>【主要区别1】

  **1、初始化基类组件**

* 隐式地继承组件而不是成员对象将影响代码的编写，因为再也不能使用 name 和 scores 来描述对象了而必须使用用于公有继承的技术。例如，对于构造函数，包含将使这样的构造函数：

  * ```c++
    Student(const char* str, const double* pd, int n)
    		: name(str), scores(pd, n) {}
    ```

* <u>对于继承类，新版构造函数将使用成员初始化列表语法，它使用类名而不是成员名来标识构造函数</u>【主要区别2】：

  * ```c++
    Student(const char* str, const double* pd, int n)
    		: std::string(str), ArrayDb(pd, n) {}
    ```

* 示例：

  * ```c++
    #pragma once
    // ch14_04_studenti.h -- defining a Student class using private inheritance
    #ifndef CH14_04_STUDENC_H_
    #define CH14_04_STUDENC_H_
    
    #include <iostream>
    #include <string>
    #include <valarray>
    
    class Student : private std::string, private std::valarray<double>
    {
    private:
    	// 用ArrayDb类型简化表示std::valarray<double>
    	typedef std::valarray<double> ArrayDb;
    	// private method for scores output
    	std::ostream& arr_out(std::ostream& os) const;
    public:
    	Student() : std::string("Null Student"), ArrayDb() {}
    	explicit Student(const std::string& s)
    		: std::string(s), ArrayDb() {}
    	explicit Student(int n) : std::string("Nully"), ArrayDb(n) {}
    	Student(const std::string& s, int n)
    		: std::string(s), ArrayDb(n) {}
    	Student(const std::string& s, const ArrayDb& a)
    		: std::string(s), ArrayDb(a) {}
    	Student(const char* str, const double* pd, int n)
    		: std::string(str), ArrayDb(pd, n) {}
    	~Student() {}
    	double Average() const;
    	double& operator[] (int i);
    	double operator[] (int i) const;
    	const std::string& Name() const;
    	// friends
    		// input
    	friend std::istream& operator>>(std::istream& is,
    		Student& stu);	// 1 word
    	friend std::istream& getline(std::istream& is,
    		Student& stu);	// 1 line
    	// output
    	friend std::ostream& operator<<(std::ostream& os,
    		const Student& stu);
    };
    
    #endif
    ```

**2、访问基类的方法**

* 使用私有继承时，只能在派生类的方法中使用基类的方法。

  * 如果希望基类工具是共有的，可以在公有函数中使用私有私有函数，见P544：

    * ![image](https://github.com/CoderSuHang/Cpp-Primer-Plus-Notes/assets/104765251/b9f8bdbb-9f03-4bf5-af74-b97d575331bc)

    * 包含使用对象来调用方法：

      * ```c++
        double Student::Average() const
        {
            if (scores.size() > 0)
                return scores.sum() / scores.size();
            else
                return 0;
        }
        ```

    * 私有继承能够使用类名和作用域解析运算符来调用基类方法：

      * ```c++
        double Student::Average() const
        {
            if (ArrayDb::size() > 0)
                return ArrayDb::sum() / ArrayDb::size();
            else
                return 0;
        }
        ```

📌总之：

* 使用**包含**时将使用**对象名**来调用方法；
* 使用**私有继承**时将使用**类名**和**作用域解析运算符**来调用方法。

**3、访问基类对象**

使用作用域解析运算符可以访问基类的方法，但如果使用基类对象本身，需要强制类型转换来返回：

* Student 类是从 string 类派生出来的，因此可以通过强制类型转换，将 Student 对象转换为 string 对象。

* 指针 this 指向用来调用方法的对象，因此可以 *this 为用来调用方法的对象。

* 为避免调用构造函数创建新对象，可以使用强制转换类型来创建一个引用：

  * ```c++
    const string & Student::Name() const
    {
        return (const string &) *this;
    }
    ```

**4、访问基类的友元函数**

用类名显式地限定函数名不适合于友元函数，因为友元函数不属于类。然而，可以通过显式转换为基类来调用正确的函数：

* ```c++
  ostream & operator<<(ostream & os, const Student & stu)
  {
      os << "Scores for " < (const String &)stu << ":\n";
      ...
  }
  ```

* 显式地将 stu 转换为 string 对象引用，进而调用函数 operator<<(ostream &, const String &)。

* 引用 stu 不会自动转换为 string 引用，根本原因在于，在私有继承中，在不进行显式类型转换的情况下，**不能将指向派生类的引用或指针赋给基类引用或指针**。

  * 然而，即使这个例子使用的是公有继承，也必须使用显式类型转换。原因之一是，如果不使用类型转换，下述代码将与友元函数原型匹配，从而导致递归调用。
  * 另一个原因是，由于这个类使用的是多重继承，编译器将无法确定应转换成哪个基类，如果两个基类都提供了函数 operator<<()。

程序清单：

* 示例：

  * ```c++
    // ch14_05_studenti.cpp -- Student class using private inheritance
    #include "ch14_04_studenti.h"
    using std::ostream;
    using std::endl;
    using std::istream;
    using std::string;
    
    // public methods
    double Student::Average() const
    {
    	if (ArrayDb::size() > 0)
    		return ArrayDb::sum() / ArrayDb::size();
    	else
    		return 0;
    }
    
    const string& Student::Name() const
    {
    	return (const string&)*this;
    }
    
    double& Student::operator[](int i)
    {
    	return ArrayDb::operator[](i);
    }
    
    double Student::operator[](int i) const
    {
    	return ArrayDb::operator[](i);
    }
    
    // private method
    ostream& Student::arr_out(ostream& os) const
    {
    	int i;
    	int lim = ArrayDb::size();
    	if (lim > 0)
    	{
    		for (i = 0; i < lim; i++)
    		{
    			os << ArrayDb::operator[](i) << " ";
    			if (i % 5 == 4)
    				os << endl;
    		}
    		if (i % 5 != 0)
    			os << endl;
    	}
    	else
    		os << " empty array ";
    	return os;
    }
    
    // friends
    // use String version of operator>>()
    istream& operator>>(istream& is, Student& stu)
    {
    	is >> (string&)stu;
    	return is;
    }
    
    // use String friend getline(ostream &, const string &)
    istream& getline(istream& is, Student& stu)
    {
    	getline(is, (string&)stu);
    	return is;
    }
    
    // use string version of operator<<()
    ostream& operator<<(ostream& os, const Student& stu)
    {
    	os << "Scoreas for " << (const string&)stu << ":\n";
    	stu.arr_out(os);
    	return os;
    }
    ```

**5、使用修改后的 Student 类**

由于上述两个版本的 Student 类的公有接口完全相同，因此可以使用同一个程序测试，唯一不同在于包含的文件有变化：

* 示例：

  * ```c++
    // ch14_06_use_stui.cpp -- using a composite class
    // compile with student.cpp
    #include <iostream>
    #include "ch14_04_studenti.h"
    
    using std::cin;
    using std::cout;
    using std::endl;
    
    void set(Student& sa, int n);
    const int pupils = 3;
    const int quizzes = 5;
    
    int main()
    {
    	Student ada[pupils] =
    	{ Student(quizzes), Student(quizzes), Student(quizzes) };
    
    	int i;
    	for (i = 0; i < pupils; ++i)
    		set(ada[i], quizzes);
    	cout << "\nStudent List:\n";
    	for (i = 0; i < pupils; ++i)
    		cout << ada[i].Name() << endl;
    	cout << "\nResults:";
    	for (i = 0; i < pupils; ++i)
    	{
    		cout << endl << ada[i];
    		cout << "average: " << ada[i].Average() << endl;
    	}
    	cout << "Done.\n";
    	return 0;
    }
    
    void set(Student& sa, int n)
    {
    	cout << "Please enter the student's name: ";
    	getline(cin, sa);
    	cout << "Please enter " << n << " quiz scores:\n";
    	for (int i = 0; i < n; i++)
    		cin >> sa[i];
    	while (cin.get() != '\n')
    		continue;
    }
    ```

* 结果：

  * ```c++
    Please enter the student's name: Gil Bayts
    Please enter 5 quiz scores:
    92 94 96 93 95
    Please enter the student's name: Pat Roone
    Please enter 5 quiz scores:
    83 89 72 78 95
    Please enter the student's name: Fleur O'Day
    Please enter 5 quiz scores:
    92 89 96 74 64
    
    Student List:
    Gil Bayts
    Pat Roone
    Fleur O'Day
    
    Results:
    Scoreas for Gil Bayts:
    92 94 96 93 95
    average: 94
    
    Scoreas for Pat Roone:
    83 89 72 78 95
    average: 83.4
    
    Scoreas for Fleur O'Day:
    92 89 96 74 64
    average: 83
    Done.
    ```



#### 14.2.2 使用包含还是私有继承

建立 has-a 关系：既可以使用**包含**，也可以使用私有**继承**，大多数C++程序员倾向于使用**包含**。

* 原因：
  * 1、易于理解：
    * 类声明中包含表示被包含类的显式命名对象，代码可以通过名称引用这些对象，而使用继承将使关系更抽象。
  * 2、继承会引起很多问题：
    * 尤其从多个基类继承时，可能必须处理很多问题，如包含同名方法的独立的基类或共享祖先的独立基类。
  * 3、包含能够包括多个同类的子对象：
    * 如果某个类需要 3 个 string 对象，可以使用包含声明 3 个独立的 string 成员。而继承只能使用一个这样的对象。

然而，私有继承所提供的特性比包含要多：

* 假设类包含保护成员（可以是数据成员，也可以成员函数），则这样的成员在派生类中是可用的，但在继承层次结构外是不可用的。
  * 如果使用组合将这样的类包含在另一个类中，则后者将不是派生类，而是位于继承层次结构之外，因此不能访问保护成员。
  * 但是通过继承得到的将是派生类，因此它能够访问保护成员。
* 需要重新定义虚函数时。
  * 派生类可以重新定义虚函数，但包含类不能。使用私有继承，重新定义的函数将只能在类中使用，而不是公有的。

总结：通常，应使用**包含**来建立 **has-a** 关系；如果新类需要访问原有类的**保护成员**，或需要重新定义**虚函数**，则应使用**私有继承**。



#### 14.2.3 保护继承

保护继承是私有继承的变体：

* 保护继承在列出基类时使用关键字 **protected**

  * ```c++
    class Student : protected std::string, peotected std::valarray<double>
    {
        ...
    };
    ```

* 使用保护继承时，基类的公有成员和保护成员都将成为派生类的保护成员。

* 和私有继承一样，基类的接口在派生类中也是可用的，但在继承层次结构之外是不可用的。

当从派生类派生出另一个类时，私有继承和保护继承之间的主要区别便呈现出来：

* 使用私有继承时，第三代类将不能使用基类的接口，因为基类的公有方法在派生类中将变成私有方法；
* 使用保护继承时，基类的公有方法在第二代中将变成受保护的，因此第三代派生类便可以使用它们。

![image](https://github.com/CoderSuHang/Cpp-Primer-Plus-Notes/assets/104765251/877f1f45-485c-479c-b3ef-2c7237002e27)



#### 14.2.4 使用 using 重新定义访问权限

使用保护派生或私有派生时，基类的公有成员将成为保护成员或私有成员。如果要让基类的方法在派生类外面可用，有两个方法：

* 方法一：

  * 定义一个使用该基类方法的派生类方法：

    * 假设希望 Student 类能够使用 valarray 类的 sum() 方法，可以在 Student 类的声明中声明一个 sum() 方法，然后像下面这样定义该方法：

      * ```c++
        double Student::sum() const
        {
            return std::valarray<double>::sum();
        }
        ```

* 方法二：

  * 将函数调用包装在另一个函数调用中，即使用一个 using 声明（就像名称空间那样）来指出派生类可以使用特定的基类成员，即使采用的是私有派生。

    * 假设希望通过 Student 类能够使用 valarray 的方法 min() 和 max()，可以在 student.h 的公有部分加入如下 using 声明：

      * ```c++
        class Student : private std::string, private std::valarray<double>
        {
        ...
        public:
            using std::valarray<double>::min;
            using std::valarray<double>::max;
            ...
        };
        ```

      * ❗using 声明只是用成员名——没有圆括号、函数特征标和返回类型。

        * 这将使两个版本（const 和非 const）都可用；
        * using 声明只适用于继承，而不适用于包含。



### 14.3 多重继承

多重继承（multiple inheritance，MI）描述的是有多个直接基类的类。与单继承一样，**公有MI**表示也是 is-a 关系：（**私有 MI** 和**保护 MI** 可以表示 has-a 关系）

* 必须使用关键字 **public** 来限定每一个基类。

  * ```c++
    class SingingWaiter : public Waiter, public Singer {...}
    ```

  * 因为除非特别指出，否则编译器将认为是私有派生:

    * ```c++
      class SingingWaiter : public Waiter, Singer {...} // Singer is a private a base
      ```

MI 会带来的主要问题：

* 从两个不同的基类继承同名方法；
* 从两个或多个相关基类那里继承同一个类的多个实例。

MI 使用方法：

* 首先，定义一个抽象基类 Worker，并使用它派生出 Waiter 类和 Singer 类；

* 然后，使用 MI 从 Waiter 类和 Singer 类派生出 SingingWaiter 类。

  * ![image](https://github.com/CoderSuHang/Cpp-Primer-Plus-Notes/assets/104765251/5ac378b0-e8e4-4541-bd7d-354d5a5bfb72)

* 示例：

  * ```c++
    #pragma once
    // ch14_07_worker0.h -- working classes
    #ifndef CH14_07_WORKER0_H_
    #define CH14_07_WORKER0_H_
    
    #include <string>
    
    class Worker
    {
    private:
    	std::string fullname;
    	long id;
    public:
    	Worker() : fullname("no one"), id(0L) {}
    	Worker(const std::string & s, long n)
    		: fullname(s), id(n) {}
    	virtual ~Worker() = 0;
    	virtual void Set();
    	virtual void Show() const;
    };
    
    class Waiter : public Worker
    {
    private:
    	int panache;
    public:
    	Waiter() : Worker(), panache(0) {}
    	Waiter(const std::string & s, long n, int p = 0)
    		: Worker(s, n), panache(p) {}
    	Waiter(const Worker & wk, int p = 0)
    		: Worker(wk), panache(p) {}
    	void Set();
    	void Show() const;
    };
    
    class Singer : public Worker
    {
    protected:
    	enum {other, alto, contralto, soprano,
    				bass, baritone, tenor};
    	enum {Vtypes = 7};
    private:
    	static char* pv[Vtypes];	// string equivs of voice types
    	int voice;
    public:
    	Singer() : Worker(), voice(other) {}
    	Singer(const std::string & s, long n, int v = other)
    		: Worker(s, n), voice(v) {}
    	Singer(const Worker & wk, int v = other)
    		: Worker(wk), voice(v) {}
    	void Set();
    	void Show() const;
    };
    #endif
    ```

  * ```c++
    // ch14_08_worker0.cpp -- working class methods
    #include "ch14_07_worker0.h"
    #include <iostream>
    
    using std::cout;
    using std::cin;
    using std::endl;
    // worker methods
    
    // must implement virtual destructor, even if pure
    Worker::~Worker() {}
    
    void Worker::Set()
    {
    	cout << "Enter worker's name: ";
    	getline(cin, fullname);
    	cout << "Enter worker's ID: ";
    	cin >> id;
    	while (cin.get() != '\n')
    		continue;
    }
    
    void Worker::Show() const
    {
    	cout << "Name: " << fullname << "\n";
    	cout << "Employee ID: " << id << "\n";
    }
    
    // Waiter methods
    void Waiter::Set()
    {
    	Worker::Set();
    	cout << "Enter waiter's panache rating: ";
    	cin >> panache;
    	while (cin.get() != '\n')
    		continue;
    }
    
    void Waiter::Show() const
    {
    	cout << "Category: waiter\n";
    	Worker::Show();
    	cout << "Panache rating: " << panache << "\n";
    }
    
    // Singer methods
    char* Singer::pv[] = {(char*)"other", (char*)"alto", (char*)"contralto",
    				(char*)"soprano", (char*)"bass", (char*)"baritone", (char*)"tenor"};
    
    void Singer::Set()
    {
    	Worker::Set();
    	cout << "Enter number for singer's vocal range:\n";
    	int i;
    	for (i = 0; i < Vtypes; i++)
    	{
    		cout << i << ": " << pv[i] << "   ";
    		if (i % 4 == 3)
    			cout << endl;
    	}
    	if (i % 4 != 0)
    		cout << endl;
    	while (cin >> voice && (voice < 0 || voice >= Vtypes))
    		cout << "Please enter a value >= 0 and < " << Vtypes << endl;
    
    	while (cin.get() != '\n')
    		continue;
    }
    
    void Singer::Show() const
    {
    	cout << "Category: singer\n";
    	Worker::Show();
    	cout << "Vocal range: " << pv[voice] << endl;
    }
    ```

    * 报错：const char* 类型不能用于初始化char* 类型实体

      * ![image](https://github.com/CoderSuHang/Cpp-Primer-Plus-Notes/assets/104765251/e21a0812-d48f-4b8c-8b7b-497329c3d222)


      * 解决办法：

        * 1、强制类型转换：

          * ```c++
            char* Singer::pv[] = {(char*)"other", (char*)"alto", (char*)"contralto",
            				(char*)"soprano", (char*)"bass", (char*)"baritone", (char*)"tenor"};
            ```

        * 2、更改属性：

          * ```c++
            右键项目->属性->C/C++->语言->符合模式：选择否
            ```

  * ```c++
    // ch14_09_worktest.cpp -- test worker class hierarchy
    #include <iostream>
    #include "ch14_07_worker0.h"
    
    const int LIM = 4;
    int main()
    {
    	Waiter bob("Bob Apple", 314L, 5);
    	Singer bev("Beverly Hills", 522L, 3);
    	Waiter w_temp;
    	Singer s_temp;
    
    	Worker* pw[LIM] = { &bob, &bev, &w_temp, &s_temp };
    
    	int i;
    	for (i = 2; i < LIM; i++)
    		pw[i]->Set();
    	for (i = 0; i < LIM; i++)
    	{
    		pw[i]->Show();
    		std::cout << std::endl;
    	}
    
    	return 0;
    }
    ```

* 结果：

  * ```c++
    Enter worker's name: Waldo Dropmaster
    Enter worker's ID: 442
    Enter waiter's panache rating: 3
    Enter worker's name: Sylvie Sirenne
    Enter worker's ID: 555
    Enter number for singer's vocal range:
    0: other   1: alto   2: contralto   3: soprano
    4: bass   5: baritone   6: tenor
    3
    Category: waiter
    Name: Bob Apple
    Employee ID: 314
    Panache rating: 5
    
    Category: singer
    Name: Beverly Hills
    Employee ID: 522
    Vocal range: soprano
    
    Category: waiter
    Name: Waldo Dropmaster
    Employee ID: 442
    Panache rating: 3
    
    Category: singer
    Name: Sylvie Sirenne
    Employee ID: 555
    Vocal range: soprano
    ```

#### 14.3.1 有多少 Worker

假设先从 Singer 和 Waiter 公有派生出 SingerWaiter：

* ```C++
  class SingerWaiter : public Singer, public Waiter {...};
  ```

  * 由于 Singer 和 Waiter 都继承了一个 Worker 组件，因此 SingerWorker 将包含两个 Worker 组件：

    * ![image-20240110162904709](C:\Users\10482\AppData\Roaming\Typora\typora-user-images\image-20240110162904709.png)

    * 引发问题：二义性

      * ```c++
        SingerWaiter ed;
        Worker * pw = ed;	// ~ambiguous
        ```

      * 通常，这种赋值将把基类指针设置为派生对象中的基类对象的地址。但 ed 中包含两个 Worker 对象，有两个地址可供选择，所以应使用类型转换来指定对象：

        * ```c++
          Worker * pw1 = (Waiter *) &ed;
          Worker * pw2 = (Singer *) &ed;
          ```

包含两个 Worker 对象拷贝还会导致其他的问题，这里引入新技术：虚基类，使 MI 成为可能：

**1、虚基类：**

* **虚基类**使得从**多个类**（它们的基类相同）派生出的对象**只继承一个基类对象**。

  * 通过在类声明中使用关键字 Virtual 使**基类**被用作**多个类**的虚基类：

    * ```c++
      class Singer : virtual public Worker {...};
      class Waiter : public virtual Worker {...};
      ```

  * 然后，将 SingerWorker 类定义为：

    * ```C++
      class SingerWaiter : public Singer, public Waiter {...};
      ```

  * 现在 SingerWaiter 对象只包含 Worker 对象的一个副本。两个对象共享一个 Worker 对象，而不是各自引入自己的 Worker 对象副本：

    * ![image](https://github.com/CoderSuHang/Cpp-Primer-Plus-Notes/assets/104765251/43763373-e297-459f-bf52-f42de290812c)

* 为什么不抛弃将基类声明为虚的这种方式，而使虚行为成为 MI 的准则呢：

  * （1）在一些情况下，可能需要基类的多个拷贝；
  * （2）将基类作为虚的要求程序完成额外的计算，为不需要的工具付出代价是不应当的；
  * （3）有缺点，见下一段。

**2、新的构造函数规则：**

使用虚基类时，需要对类构造函数采用一种新的方法。对于非虚基类，唯一可以出现在初始化列表中的构造函数是**即时基类构造函数**。但这些构造函数可能需要将信息传递给其基类。例如，可能有下面一组构造函数：

* ```c++
  class A
  {
      int a;
  public:
      A(int n = 0) : a(n) {}
      ...
  };
  
  class B : public A
  {
      int b;
  public:
      B(int m = 0, int n = 0) : A(n), b(m) {}
      ...
  };
  
  class C : public B
  {
      int c;
  public:
      C(int q = 0, int m = 0, int n = 0) : B(m, n), c(q) {}
      ...
  };
  ```

  * C类构造函数只能调用B类构造函数，而B类构造函数只能调用A类构造函数；
  * C类构造函数使用值q，并将值m, n传递给B类构造函数；B类构造函数使用值m, 并将n值传递给A类构造函数。

* 如果 Worker 是虚基类，则这种信息自动传递将不起作用：

  * ```c++
    SingingWaiter(const Worker & wk, int p = 0, int v = Singer::other) : 	Waiter(wk, p), Singer(wk, v) {}	//flawed
    ```

*  如果不希望默认构造函数来构造虚基类对象，则需要显式地调用所需的基类构造函数。因此，构造函数应该是这样：

  * ```c++
    SingingWaiter(const Worker & wk, int p = 0; int v = Singer::other) : Worker(wk), Waiter(wk, p), Singer (wk, v) {}
    ```

    * 上述代码将显式地调用构造函数 worker (const Worker &)。请注意，这种用法是合法的，对于虚基类必须这样做；但对于非虚基类，则是非法的。

  * 警告：如果类有间接虚基类，则除非只需使用该虚基类的默认构造函数，否则必须显式地调用该虚基类的某个构造函数。

#### 14.3.2 哪个方法

除了修改类构造函数规则外，MI通常还要求调整其他代码。

假设要在 SingingWaiter 类中扩展 Show( ) 方法的问题：

* 二义性：

  * 对于单继承，如果没有重新定义 Show() ，则将使用最新祖先中的定义；

  * 而在多重继承中，每个直接祖先都有一个 Show() 函数，使得上述调用是二义性。

  * 可以用作用域解析运算符来澄清：

    * ```c++
      SingingWaiter newhire("Elise Hawks", 2005, 6, soprano);
      newhire.Singer::Show();
      ```

* 更好的办法：

  * 在 SingingWaiter 中重新定义 Show()，并指出要使用哪个 Show()：

    * ```c++
      void SingingWaiter::Show()
      {
          Singer::Show();
      }
      ```

    * 然而这种递增的方式对 SingingWaiter 示例无效，因为它忽略了 Waiter 组件；

    * 可以通过同时调用 Waiter 版本的 Show() 来补救：

      * ```c++
        void SingingWaiter::Show()
        {
            Singer::Show();
            Waiter::Show();
        }
        ```

      * 这将显示姓名和ID两次，如何解决？

        * 方法一：使用模块化方式，而不是递增方式，即提供一个只显示 Worker 组件的方法和一个只显示 Waiter 组件或 Singer 组件的方法。然后在 SingingWaiter::Show()  方法中将组件组合起来：

          * ```c++
            void Worker::Data() const
            {
                cout << "Name: " << fullname << "\n";
                cout << "Employee ID: " << id << "\n";
            }
            
            void Waiter::Data() const
            {
                cout << "Panache rating: " << panache << "\n";
            }
            
            void Singer::Data() const
            {
                cout << "Vocal range: " << pv[voice] << "\n";
            }
            
            void SingingWaiter::Data() const
            {
                Singer::Data();
                Waiter::Data();
            }
            
            void SingingWaiter::Show() const
            {
                cout << "Category: Singing waiter\n";
                Worker::Data();
                Data();
            }
            ```

          * 采用这种方式，对象仍可使用 Show() 方法。而 Data() 方法只在类内部可用，作为协助公有接口的辅助方法。

        * 方法二：将所有的数据组件都设置为保护的，而不是私有的，不过使用保护方法将可以更严格地控制对数据地访问。

* 总之，在祖先相同时，使用 MI 必须引入虚基类，并修改构造函数初始化列表地规则。另外，如果在编写这些类时没有考虑到 MI，则还可能需要重新编写它们。

  * 示例：

    * ```c++
      #pragma once
      // ch14_10_workermi.h -- working classes with MI
      #ifndef WORKERMI_H_
      #define WORKERMI_H_
      
      #include <string>
      
      class Worker	// an abstract base class
      {
      private:
      	std::string fullname;
      	long id;
      protected:
      	virtual void Data() const;
      	virtual void Get();
      public:
      	Worker() : fullname("no one"), id(0L) {}
      	Worker(const std::string & s, long n)
      		: fullname(s), id(n) {}
      	virtual ~Worker() = 0;
      	virtual void Set() = 0;
      	virtual void Show() const = 0;
      };
      
      class Waiter : virtual public Worker
      {
      private:
      	int panache;
      protected:
      	void Data() const;
      	void Get();
      public:
      	Waiter() : Worker(), panache(0) {}
      	Waiter(const std::string & s, long n, int p = 0)
      		: Worker(s, n), panache(p) {}
      	Waiter(const Worker & wk, int p = 0)
      		:Worker(wk), panache(p) {}
      	void Set();
      	void Show() const;
      };
      
      class Singer : virtual public Worker
      {
      protected:
      	enum {other, alto, contralto, sorpano, 
      			bass, baritone, tenor};
      	enum {Vtypes = 7};
      	void Data() const;
      	void Get();
      private:
      	static char* pv[Vtypes];
      	int voice;
      public:
      	Singer() : Worker(), voice(other) {}
      	Singer(const std::string & s, long n, int v = other)
      		: Worker(s, n), voice(v) {}
      	Singer(const Worker & wk, int v = other)
      		: Worker(wk), voice(v) {}
      	void Set();
      	void Show() const;
      };
      
      // multiple inheritance
      class SingingWaiter : public Singer, public Waiter
      {
      protected:
      	void Data() const;
      	void Get();
      public:
      	SingingWaiter() {}
      	SingingWaiter(const std::string & s, long n, int p = 0,
      							int v = other)
      		: Worker(s, n), Waiter(s, n, p), Singer(s, n, v) {}
      	SingingWaiter(const Worker & wk, int p = 0, int v = other)
      		: Worker(wk), Waiter(wk, p), Singer(wk, v) {}
      	SingingWaiter(const Waiter& wt, int v = other)
      		: Worker(wt), Waiter(wt), Singer(wt, v) {}
      	SingingWaiter(const Singer& wt, int p = 0)
      		: Worker(wt), Waiter(wt, p), Singer(wt) {}
      	void Set();
      	void Show() const;
      };
      #endif
      ```

    * ```c++
      // ch14_11_workermi.cpp -- working class methods with MI
      #include "ch14_10_workermi.h"
      #include <iostream>
      using std::cout;
      using std::cin;
      using std::endl;
      
      // Worker methods
      Worker::~Worker() {}
      
      // protected methods
      void Worker::Data() const
      {
      	cout << "Name: " << fullname << endl;
      	cout << "Employee ID: " << id << endl;
      }
      
      void Worker::Get()
      {
      	getline(cin, fullname);
      	cout << "Enter worker's ID: ";
      	cin >> id;
      	while (cin.get() != '\n')
      		continue;
      }
      
      // Waiter methods
      void Waiter::Set()
      {
      	cout << "Enter waiter's name: ";
      	Worker::Get();
      	Get();
      }
      
      void Waiter::Show() const
      {
      	cout << "Category: waiter\n";
      	Worker::Data();
      	Data();
      }
      
      // protected methods
      void Waiter::Data() const
      {
      	cout << "Panache rating: " << panache << endl;
      }
      
      void Waiter::Get()
      {
      	cout << "Enter waiter's panache rating: ";
      	cin >> panache;
      	while (cin.get() != '\n')
      		continue;
      }
      
      // Singer methods
      
      char* Singer::pv[Singer::Vtypes] = { (char *)"other", (char*)"alto", (char*)"contralto",
      		(char*)"soprano", (char*)"bass", (char*)"baritone", (char*)"tenor" };
      
      void Singer::Set()
      {
      	cout << "Enter singer's name: ";
      	Worker::Get();
      	Get();
      }
      
      void Singer::Show() const
      {
      	cout << "Category: singer\n";
      	Worker::Data();
      	Data();
      }
      
      // protected methods
      void Singer::Data() const
      {
      	cout << "Vocal range: " << pv[voice] << endl;
      }
      
      void Singer::Get()
      {
      	cout << "Enter number for singer's vocal range:\n";
      	int i;
      	for (i = 0; i < Vtypes; i++)
      	{
      		cout << i << ": " << pv[i] << "    ";
      		if (i % 4 == 3)
      			cout << endl;
      	}
      	if (i % 4 != 0)
      		cout << "\n";
      	cin >> voice;
      	while (cin.get() != '\n')
      		continue;
      }
      
      // SingingWaiter methods
      void SingingWaiter::Data() const
      {
      	Singer::Data();
      	Waiter::Data();
      }
      
      void SingingWaiter::Get()
      {
      	Waiter::Get();
      	Singer::Get();
      }
      
      void SingingWaiter::Set()
      {
      	cout << "Enter singing waiter's name: ";
      	Worker::Get();
      	Get();
      }
      
      void SingingWaiter::Show() const
      {
      	cout << "Category: singing waiter\n";
      	Worker::Data();
      	Data();
      }
      ```

    * ```c++
      // ch14_12_workmi.cpp -- mutiple inheritance
      // compile with workermi.cpp
      
      #include <iostream>
      #include <cstring>
      #include "ch14_10_workermi.h"
      
      const int SIZE = 5;
      
      int main()
      {
      	using std::cin;
      	using std::cout;
      	using std::endl;
      	using std::strchr;
      
      	Worker* lolas[SIZE];
      
      	int ct;
      	for (ct = 0; ct < SIZE; ct++)
      	{
      		char choice;
      		cout << "Enter the employee category:\n"
      			<< "w: waiter  s: singer  "
      			<< "t: singing waiter  q: quit\n";
      		cin >> choice;
      		while (strchr("wstq", choice) == NULL)
      		{
      			cout << "Please enter a w, s t, or q: ";
      			cin >> choice;
      		}
      		if (choice == 'q')
      			break;
      		switch (choice)
      		{
      			case 'w': lolas[ct] = new Waiter;
      					  break;
      			case 's': lolas[ct] = new Singer;
      				break;
      			case 't': lolas[ct] = new SingingWaiter;
      				break;
      		}
      		cin.get();
      		lolas[ct]->Set();
      	}
      
      	cout << "\nHere is your staff:\n";
      	int i;
      	for (i = 0; i < ct; i++)
      	{
      		cout << endl;
      		lolas[i]->Show();
      	}
      	for (i = 0; i < ct; i++)
      	{
      		delete lolas[i];
      	}
      	cout << "Bye.\n";
      	return 0;
      }
      ```

  * 结果：

    * ```c++
      Enter the employee category:
      w: waiter  s: singer  t: singing waiter  q: quit
      w
      Enter waiter's name: Wally Slipshod
      Enter worker's ID: 1040
      Enter waiter's panache rating: 4
      Enter the employee category:
      w: waiter  s: singer  t: singing waiter  q: quit
      s
      Enter singer's name: Sinclair Parma
      Enter worker's ID: 1044
      Enter number for singer's vocal range:
      0: other    1: alto    2: contralto    3: soprano
      4: bass    5: baritone    6: tenor
      5
      Enter the employee category:
      w: waiter  s: singer  t: singing waiter  q: quit
      t
      Enter singing waiter's name: Natasha Gargalova
      Enter worker's ID: 1021
      Enter waiter's panache rating: 6
      Enter number for singer's vocal range:
      0: other    1: alto    2: contralto    3: soprano
      4: bass    5: baritone    6: tenor
      3
      Enter the employee category:
      w: waiter  s: singer  t: singing waiter  q: quit
      q
      
      Here is your staff:
      
      Category: waiter
      Name: Wally Slipshod
      Employee ID: 1040
      Panache rating: 4
      
      Category: singer
      Name: Sinclair Parma
      Employee ID: 1044
      Vocal range: baritone
      
      Category: singing waiter
      Name: Natasha Gargalova
      Employee ID: 1021
      Vocal range: soprano
      Panache rating: 6
      Bye.
      ```

**1、混合使用虚基类和非虚基类**

通过多种途径继承一个基类的派生类的情况：

* 如果基类是虚基类，派生类将包含基类的一个子对象；
* 如果基类不是虚基类，派生类将包含多个子对象。
* 当虚基类和非虚基类混合时：
  * 当类通过多条虚途径和非虚途径继承某个特定的基类时，该类将包含：
    * 一个表示所有的虚途径的基类子对象
    * 和分别表示各条非虚途径的多个基类子对象

**2、虚基类和支配**

使用虚基类将改变 C++ 解析二义性的方式。使用非虚基类时，规则很简单。

* 如果类从不同的类哪里继承了两个或多个同名成员（数据或方法），则使用该成员名时。

  * 如果没有用类名进行限定，将导致二义性。

  * 但如果使用的时虚基类，则这样做不一定会导致二义性。

    * 在这种情况下，如果某个名称优先于其他所有名称，则使用它时，即便不适用限定符，也不会导致二义性。

      * ```c++
        class B
        {
        public:
            short q();
            ...
        };
        
        class C : virtual public B
        {
        public:
            long q();
            int omg();
            ...
        };
        
        class D : public C
        {
          ...  
        };
        
        class E : virtual public B
        {
        private:
            int omg();
            ...
        };
        
        class F : public D, public E
        {
            ...
        }
        ```

      * 类 C 中 q() 定义优先于类 B 中 q() 定义，因为类 C 是从类 B 派生而来的。因此 F 中的方法可以使用 q() 来表示 C::q()。

      * 任何一个 omg() 定义都不优先于其他 omg() 定义，因为 C 和 E 都不是对方的基类。所以在 F 中使用 omg() 将导致二义性。

      * 虚二义性规则与访问规则无关，即使E::omg() 是私有的，不能再F类中直接访问，但使用 omg() 仍将导致二义性。见P567

#### 14.3.3 MI小结

* 不使用虚基类的 MI：

  * 这种 MI 不会引入新的规则。然而，如果一个类从两个不同的类哪里继承了两个同名的成员，则需要再派生类中使用类限定符来区分它们。否则编译器将指出二义性。
  * 如果一个类通过多种途径继承了一个非虚基类，则该类从每种途径分别继承非虚基类的一个实例。

* 使用虚基类的 MI：

  * 当派生类使用关键字 virtual 来指示派生时，基类就成为虚基类：

    * ```c++
      class marketing : public virtual reality {...};
      ```

    * 从虚基类的一个或多个实例派生而来的类将只继承了一个基类对象。（必须满足下面要求）

      * 有间接虚基类的派生类包含直接调用间接基类构造函数的构造函数，这对于间接非虚基类来说是非法的；
      * 通过优先规则解决名称二义性。

  * 需要注意：在必要时对继承的名称进行限定。



### 14.4 类模板

C++的类模板为生成通用的类声明提供了一种更好的方法，模板提供参数化类型，即能够将类型名作为参数传递给接收方来建立类或函数：

* 例如，将类型名 int 传递 Queue 模板，可以让编译器构造一个对 int 进行排队的 Queue 类。

#### 14.4.1 定义类模板

* 采用模板时，将使用模板定义替换类声明，使用模板成员函数替换类的成员函数。和模板函数一样，模板类以下面这样的代码开头：

  * ```c++
    template <class Type>
    ```

    * 尖括号中的内容相当于函数的参数列表。

    * 可以把关键字 class 看作是变量的类型名，该变量接受类型作为其值，把 Type 看作该变量的名称。

      * 这里使用 class 并不意味着 Type 必须是一个类；而只是表明 Type 是一个通用的类型说明符，在使用模板时，将使用实际的类型替换它。

      * ```c++
        template <typename Type>		// newer choice
        ```

      * 可以使用自己的泛型名代替 Type ，其命名规则与其他标识符相同。

  * 在模板定义中，可以使用泛型名称来标识要储存在栈中的类型，即将声明中所有的 typedef 标识符 Item 替换为 Type：

    * ```C++
      Item items[Max];
      // 应改为：
      Type items[max];
      ```

* 可以使用模板成员函数替换原有类的类方法。每个函数头都将以相同的模板声明打头：

  * ```c++
    template <class Type>
    ```

  * 同样应使用泛型名 Type 替换 typedef 标识符 Item。另外还需将类限定符从 Stack::改为 Stack<Type>::。

    * ```c++
      bool Stack::push(const ITEM & item)
      {
          ...
      }
      // 应该为：
      template <class Type>
      bool Stack<Type>::push(const Type & item)
      {
          ...
      }
      ```

* 不能将模板成员函数放在独立的实现文件中。由于模板不是函数，它们不能单独编译。模板必须与特定的模板实例化请求一起使用。

  * 为此最简单的方法是将所有模板信息放在一个头文件中，并在要使用这些模板文件中包含该头文件

  * 示例：

    * ```c++
      #pragma once
      // ch14_13_stacktp.h -- a stack template
      #ifndef CH14_13_STACKTP_H_
      #define CH14_13_STACKTP_H_
      template <class Type>
      class Stack
      {
      private:
      	enum {MAX = 10};
      	Type items[MAX];
      	int top;
      public:
      	Stack();
      	bool isempty();
      	bool isfull();
      	bool push(const Type& item);
      	bool pop(Type& item);
      };
      
      template <class Type>
      Stack<Type>::Stack()
      {
      	top = 0;
      }
      
      template <class Type>
      bool Stack<Type>::isempty()
      {
      	return top == 0;
      }
      
      template <class Type>
      bool Stack<Type>::isfull()
      {
      	return top == MAX;
      }
      
      template <class Type>
      bool Stack<Type>::push(const Type& item)
      {
      	if (top < MAX)
      	{
      		items[top++] = item;
      		return true;
      	}
      	else
      		return false;
      }
      
      template <class Type>
      bool Stack<Type>::pop(Type& item)
      {
      	if (top > 0)
      	{
      		item = items[--top];
      		return true;
      	}
      	else
      		return false;
      }
      #endif
      ```

#### 14.4.2 使用模板类

* 仅在程序包含模板并不能生成模板类，而必须请求实例化。为此需要声明一个类型为模板类的对象，方法是使用所需的具体类型替换泛型名。

  * ```c++
    Stack<int> kernels;		    // create a stack of ints
    Stack<string> colonels;		// create a stack of string objects
    ```

  * 类声明 Stack<int> 将使用 int 替换模板中所有的 Type；string同理。

* 反省标识符：Type（称为类型参数），这意味着它们类似于变量，但附给它们的不能是数字，而只能是类型。

  * 注意❗必须显式地提供所需的类型，这与常规的函数模板是不同的，因为编译器可以根据函数的参数类型来确定要生成那种函数：

    * ```c++
      template <class T>
      void simple(T t) { cout << t << "\n"; }
      ...
      simple(2);		// generate void simple(int)
      simple(two);	// generate void simple(const char *)
      ```

* 示例（修改原来的栈测试程序ch11_12，使用字符串而不是 usigned long 值作为订单ID）

  * ```C++
    // ch14_14_stacktem.cpp -- testing the template stack class
    #include <iostream>
    #include <string>
    #include <cctype>
    #include "ch14_13_stacktp.h"
    using std::cin;
    using std::cout;
    
    int main()
    {
    	Stack<std::string> st;		// create an empty stack
    	char ch;
    	std::string po;
    	cout << "Please enter A to add a purchase order,\n"
    		<< "P to process a PO, or Q to quit.\n";
    	while (cin >> ch && std::toupper(ch) != 'Q')
    	{
    		while (cin.get() != '\n')
    			continue;
    		if (!std::isalpha(ch))
    		{
    			cout << "\a";
    			continue;
    		}
    		switch (ch)
    		{
    			case 'A':
    			case 'a': cout << "Enter a PO number to add: ";
    					  cin >> po;
    					  if (st.isfull())
    						  cout << "Stack already full\n";
    					  else
    						  st.push(po);
    					  break;
    			case 'P':
    			case 'p': if (st.isempty())
    						  cout << "Stack already empty\n";
    					  else
    					  {
    					   	  st.pop(po);
    						  cout << "PO #" << po << "popped\n";
    						  break;
    					  }
    		}
    		cout << "Please enter A to add a purchase order,\n"
    			 << "P to process a PO, or Q to quit.\n";
    	}
    	cout << "Bye\n";
    	return 0;
    }
    ```

* 结果：

  * ```c++
    Please enter A to add a purchase order,
    P to process a PO, or Q to quit.
    A
    Enter a PO number to add: red911porsche
    Please enter A to add a purchase order,
    P to process a PO, or Q to quit.
    A
    Enter a PO number to add: blueR8audi
    Please enter A to add a purchase order,
    P to process a PO, or Q to quit.
    A
    Enter a PO number to add: silver747boeing
    Please enter A to add a purchase order,
    P to process a PO, or Q to quit.
    P
    PO #silver747boeingpopped
    Please enter A to add a purchase order,
    P to process a PO, or Q to quit.
    P
    PO #blueR8audipopped
    Please enter A to add a purchase order,
    P to process a PO, or Q to quit.
    P
    PO #red911porschepopped
    Please enter A to add a purchase order,
    P to process a PO, or Q to quit.
    p
    Stack already empty
    Please enter A to add a purchase order,
    P to process a PO, or Q to quit.
    Q
    Bye
    ```

#### 14.4.3 深入探讨模板类

可以将内置类型或类对象用作类模板 Class<Type> 的类型，也可以创建指针栈，但如果不对程序做重大修改，将无法很好地工作：

**1、不正确地使用指针栈**

3个试图对程序清单CH14_14进行修改，使之使用指针栈的示例（有缺陷），这3个示例都以完全正确的 Stack<Type> 模板为基础：

```c++
Stack<char *> st;	// create a stack for pointers-to-char
```

* 版本1：

  * ```c++
    //将程序清单中的：
    string po;
    //替换为：
    char * po;
    ```

  * 用 char 指针而不是 string 对象来接受键盘输入。

  * 失败❗因为仅仅创建指针，没有创建用于保存输入字符串的空间。

* 版本2：

  * ```c++
    //将程序清单中的：
    string po;
    //替换为：
    char po[40];
    ```

  * 这为输入的字符串分配了空间。另外，po 的类型为 char*，因此可以被放在栈中。

  * 但数组完全与 pop() 方法的假设相冲突：

    * ```c++
      template <class Type>
      bool Stack<Type>::pop(Type& item)
      {
      	if (top > 0)
      	{
      		item = items[--top];
      		return true;
      	}
      	else
      		return false;
      }
      ```

    * 首先，引用变量 item 必须引用某种类型的左值，而不是数组名。

    * 其次，代码假设可以给 item 赋值。即使 item 能够引用数组，也不能为数组名赋值，因此这种方法失败❗

* 版本3：

  * ```c++
    //将程序清单中的：
    string po;
    //替换为：
    char * po = new char[40];
    ```

  * 这为输入的字符串分配了空间。另外，po 是变量，因此与 pop()的代码兼容。

  * 然而，这将会遇到最基本的问题：

    * 只有一个 pop 变量，该变量总是指向相同的内存单元。确实，在每当读取新字符串时，内存的内容都将发生改变，但每次执行压入操作时，加入到栈中的的地址都相同。因此，对栈执行弹出操作时，得到的地址总是相同的，它总是指向读入的最后一个字符串。具体地说，栈并没有保存每一个新字符串，因此没有任何用途。

**2、正确使用指针栈**

* 让调用程序提供一个指针数组，其中每个指针都指向不同的字符串。

  * 注意❗创建不同指针是调用程序的职责，而不是栈的职责。栈的任务是管理指针，而不是创建指针。

* 案例模拟：（用一个指针数组模拟文件收发，见P573）

  * ```C++
    #pragma once
    // ch14_15_stcktp1.h -- modified Stack template
    #ifndef CH14_15_STCKTP1_H_
    #define CH14_15_STCKTP1_H_
    
    template <class Type>
    class Stack
    {
    private:
    	enum {SIZE = 10};
    	int stacksize;
    	Type* items;		// holds stack items
    	int top;			// index for top stack item
    public:
    	explicit Stack(int ss = SIZE);
    	Stack(const Stack& st);
    	~Stack() { delete[] items; }
    	bool isempty() { return top == 0; }
    	bool isfull() { return top == stacksize; }
    	bool push(const Type& item);
    	bool pop(Type& item);
    	Stack& operator=(const Stack& st);
    };
    
    template<class Type>
    Stack<Type>::Stack(int ss) : stacksize(ss), top(0)
    {
    	items = new Type[stacksize];
    }
    
    template<class Type>
    Stack<Type>::Stack(const Stack& st)
    {
    	stacksize = st.stacksize;
    	top = st.top;
    	items = new Type[stacksize];
    	for (int i = 0; i < top; i++)
    		items[i] = st.items[i];
    }
    
    template<class Type>
    bool Stack<Type>::push(const Type& item)
    {
    	if (top < stacksize)
    	{
    		items[top++] = item;
    		return true;
    	}
    	else
    		return false;
    }
    
    template<class Type>
    bool Stack<Type>::pop(Type & item)
    {
    	if (top > 0)
    	{
    		item = items[--top];
    		return true;
    	}
    	else
    		return false;
    }
    
    template<class Type>
    Stack<Type> & Stack<Type>::operator=(const Stack<Type> & st)
    {
    	if (this == &st)
    		return *this;
    	delete[] items;
    	stacksize = st.stacksize;
    	top = st.top;
    	items = new Type[stacksize];
    	for (int i = 0; i < top; i++)
    		items[i] = st.items[i];
    	return *this;
    }
    
    #endif
    ```

  * ```c++
    // ch14_16_stkoptr1.cpp -- testing stack of pointers
    #include <iostream>
    #include <cstdlib>
    #include <ctime>
    #include "ch14_15_stcktp1.h"
    const int Num = 10;
    int main()
    {
    	std::srand(std::time(0));
    	std::cout << "Please enter stack size: ";
    	int stacksize;
    	std::cin >> stacksize;
    // create an empty stack with stacksize slots
    	Stack<const char*> st(stacksize);
    // in basket
    	const char* in[Num] = {
    		" 1: Hank Gilgamesh", " 2: Kiki Ishtar",
    		" 3: Betty Rocker", " 4: Ian Flagranti",
    		" 5: Wolfgang Kibble", " 6: Portia Koop",
    		" 7: Joy Almondo", " 8: Xaverie Paprika",
    		" 9: Juan Moore", " 10: Misha Mache",
    	};
    // out basket
    	const char* out[Num];
    
    	int processed = 0;
    	int nextin = 0;
    	while (processed < Num)
    	{
    		if (st.isempty())
    			st.push(in[nextin++]);
    		else if (st.isfull())
    			st.pop(out[processed++]);
    		else if (std::rand() % 2 && nextin < Num)	// 50-50 chance
    			st.push(in[nextin++]);
    		else
    			st.pop(out[processed++]);
    	}
    	for (int i = 0; i < Num; i++)
    		std::cout << out[i] << std::endl;
    
    	std::cout << "Bye\n";
    	return 0;
    }
    ```

* 结果：

  * ```c++
    Please enter stack size: 5
     2: Kiki Ishtar
     1: Hank Gilgamesh
     3: Betty Rocker
     7: Joy Almondo
     8: Xaverie Paprika
     10: Misha Mache
     9: Juan Moore
     6: Portia Koop
     5: Wolfgang Kibble
     4: Ian Flagranti
    Bye
         
    Please enter stack size: 5
     4: Ian Flagranti
     6: Portia Koop
     5: Wolfgang Kibble
     8: Xaverie Paprika
     7: Joy Almondo
     3: Betty Rocker
     9: Juan Moore
     2: Kiki Ishtar
     1: Hank Gilgamesh
     10: Misha Mache
    Bye
    ```

#### 14.4.4 数组模板示例和非类型参数

模板常用作容器类，这是因为类型参数的概念非常适合于将相同的存储方案用于不同的类型。

下面将探讨一些非类型（或表达式）参数以及如何使用数组来处理继承族：

* 一个允许指定数组大小的简单数组模板：

  * 一种方法是在类中使用动态数组和构造函数参数来提供元素数目，最后一个版本的 Stack 模板采用的就是这种方法。
  * 另一种方法是使用模板参数来提供常规数组的大小，C++11 新增的模板 array 就是这样做的。程序清单 14.17 演示了如何做。

* 示例：

  * ```c++
    #pragma once
    // ch14_17_arraytp.h -- Array Template
    #ifndef CH14_17_ARRAYTP_H_
    #define CH14_17_ARRAYTP_H_
    
    #include <iostream>
    #include <cstdlib>
    
    template <class T, int n>
    class ArrayTP
    {
    private:
    	T ar[n];
    public:
    	ArrayTP() {};
    	explicit ArrayTP(const T& v);
    	virtual T& operator[](int i);
    	virtual T operator[](int i) const;
    };
    
    template <class T, int n>
    ArrayTP<T, n>::ArrayTP(const T& v)
    {
    	for (int i = 0; i < n; i++)
    		ar[i] = v;
    }
    
    template <class T, int n>
    T& ArrayTP<T, n>::operator[](int i)
    {
    	if (i < 0 || i >= n)
    	{
    		std::cerr << "Error in array limits: " << i
    			<< " is out of range\n";
    		std::exit(EXIT_FAILURE);
    	}
    	return ar[i];
    }
    
    template <class T, int n>
    T ArrayTP<T, n>::operator[](int i) const
    {
    	if (i < 0 || i >= n)
    	{
    		std::cerr << "Error in array limits: " << i
    			<< " is out of range\n";
    		std::exit(EXIT_FAILURE);
    	}
    	return ar[i];
    }
    
    #endif
    ```

    * 关键字：

      * class（或在这种上下文中等价的关键字 typename）指出T为类型参数；
      * int 指出 n 的类型为int。
      * 这种参数（指定特殊的类型而不是用作型名）称为非类（non-type）或达式 （expression）参数。

    * 表达式参数限制：

      * 表达式参数可以是整型、枚举、引用或指针。其他非法；
      * 模板代码不能修改参数的值，也不能使用参数的地址；
      * 实例化模板时，用作表达式参数的值必须是常量表达式。

    * 优缺点：

      * 优点：

        * 与 Stack 中使用的构造函数方法相比，这种改变数组大小的方法有一个优点。构造函数方法使用的是通过 new 和 delete 管理的堆内存，而表达式参数方法使用的是为自动变量维护的内存栈。这样，执行速度将更快，尤其是在使用了很多小型数组时。

      * 缺点：

        * 每种数组大小都将生成自己的模板。也就是说，下面的声明将生成两个独立的类声明：

          * ```c++
            Array<double, 12> eggweights;
            Array<double, 13> donuts;
            ```

          * 但下面的声明只生成一个类声明，并将数组大小信息传递给类的构造函数：

            * ```c++
              Stack<int> eggs(12);
              Stack<int> dunkers(13);
              ```

        * 另一个区别是，构造函数方法更通用，这是因为数组大小是作为类成员(而不是硬编码)存储在定义中的。这样可以将一种尺寸的数组赋给另一种尺寸的数组，也可以创建允许数组大小可变的类。

#### 14.4.5 模板多功能性

可以将用于常规类的技术用于模板类。模板类可用作基类，也可用作组件类，还可用作其他模板的类型参数：

* 可以使用数组模板实现栈模板，也可以使用数组模板来构造数组——数组元素是基于栈模板的栈。

  * ```c++
    template <typename T>
    class Array
    {
    private:
        T entry;
        ...
    };
    
    template <typename Type>
    class GrowArray : public Array<Type> {...};	// inheritance
    
    template <typename Tp>
    class Stack
    {
        Array<Tp> ar;			// use an Array<> as a component	
        ...
    };
    ...
    Array < Stack<int> > asi;	// an array of stacks of int
    ```

**1、递归使用模板**

* 可以递归使用模板：

  * 对于前面的数组模板定义，可以这样使用：

    * ```c++
      ArrayTP< ArrayTP<int, 5>, 10> twodee;
      ```

    * 这使得 twodee 是一个包含10个元素的数组，其中每个元素都是一个包含5个int元素的数组。等价于：

      * ```c++
        int twodee[10] [5];
        ```

      * 请注意，在模板语法中，维的顺序与等价的二维数组相反。

  * 示例：

    * ```c++
      // ch14_18_twod.cpp  -- making a 2-d array
      #include <iostream>
      #include "ch14_17_arraytp.h"
      
      int main(void)
      {
      	using std::cout;
      	using std::endl;
      	ArrayTP<int, 10> sums;
      	ArrayTP<double, 10> aves;
      	ArrayTP< ArrayTP<int, 5>, 10> twodee;
      	
      	int i, j;
      	for (i = 0; i < 10; i++)
      	{
      		
      		sums[i] = 0;
      		for (j = 0; j < 5; j++)
      		{
      			twodee[i][j] = (i + 1) * (j + 1);
      			sums[i] += twodee[i][j];
      		}
      		aves[i] = (double)sums[i] / 10;
      	}
      
      	for (i = 0; i < 10; i++)
      	{
      		for (j = 0; j < 5; j++)
      		{
      			cout.width(2);
      			cout << twodee[i][j] << ' ';
      		}
      		cout << ": sum = ";
      		cout.width(3);
      		cout << sums[i] << ", average = " << aves[i] << endl;
      	}
      
      	cout << "Done.\n";
      
      	return 0;
      }
      ```

  * 结果：

    * ```c++
       1  2  3  4  5 : sum =  15, average = 1.5
       2  4  6  8 10 : sum =  30, average = 3
       3  6  9 12 15 : sum =  45, average = 4.5
       4  8 12 16 20 : sum =  60, average = 6
       5 10 15 20 25 : sum =  75, average = 7.5
       6 12 18 24 30 : sum =  90, average = 9
       7 14 21 28 35 : sum = 105, average = 10.5
       8 16 24 32 40 : sum = 120, average = 12
       9 18 27 36 45 : sum = 135, average = 13.5
      10 20 30 40 50 : sum = 150, average = 15
      ```

  **2、使用多个类型参数**

模板可以包含多个类型参数。

* 例如，假设希望类可以保存两种值，则可以创建并使用 Pair 模板来保存两个不同的值：

  * ```C++
    // ch14_19_pairs.cpp -- defining and using a Pair template
    #include <iostream>
    #include <string>
    
    template <class T1, class T2>
    class Pair
    {
    private:
    	T1 a;
    	T2 b;
    public:
    	T1& first();
    	T2& second();
    	T1 first() const { return a; }
    	T2 second() const { return b; }
    	Pair(const T1 & aval, const T2 & bval) : a(aval), b(bval) { }
    	Pair() {}
    };
    
    template<class T1, class T2>
    T1& Pair<T1, T2>::first()
    {
    	return a;
    }
    
    template<class T1, class T2>
    T2& Pair<T1, T2>::second()
    {
    	return b;
    }
    
    int main()
    {
    	using std::cout;
    	using std::endl;
    	using std::string;
    	Pair<string, int> ratings[4] =
    	{
    		Pair<string, int>("The Purpled Duck", 5),
    		Pair<string, int>("Jaquie's Frisco Al Fresco", 4),
    		Pair<string, int>("Cafe souffle", 5),
    		Pair<string, int>("Bertie's Eats", 3)
    	};
    
    	int joints = sizeof(ratings) / sizeof(Pair<string, int>);
    	cout << "Rating:\t Eatery\n";
    	for (int i = 0; i < joints; i++)
    		cout << ratings[i].second() << ":\t"
    			 << ratings[i].first() << endl;
    	cout << "0ops! Revised rating:\n";
    	ratings[3].first() = "Bertie's Fab Eats";
    	ratings[3].second() = 6;
    	cout << ratings[3].second() << ":\t"
    		 << ratings[3].first() << endl;
    	return 0;
    }
    ```

  * ```c++
    Rating:  Eatery
    5:      The Purpled Duck
    4:      Jaquie's Frisco Al Fresco
    5:      Cafe souffle
    3:      Bertie's Eats
    0ops! Revised rating:
    6:      Bertie's Fab Eats
    ```

**3、默认类型模板参数**

类模板的另一项新特性是，可以为类型参数提供默认值：

* ```c++
  template <class T1, class T2 = int> class Topo {...};
  ```

  * 这样，如果省略 T2 的值，编译器将使用 int：

    * ```c++
      Topo<double, double> m1; // T1 is double, T2 is double
      Topo<double> m2;		// T1 is double, T2 is int
      ```

* 虽然可以为类模板类型参数提供默认值，但不能为函数模板参数提供默认值。然而，可以为非类型参数提供默认值，这对于类模板和函数模板都是适用的。

#### 14.4.5 模板多功能性

可以将用于常规类的技术用于模板类。模板类可用作基类，也可用作组件类，还可用作其他模板的类型参数：

* 可以使用数组模板实现栈模板，也可以使用数组模板来构造数组——数组元素是基于栈模板的栈。

  * ```c++
    template <typename T>
    class Array
    {
    private:
        T entry;
        ...
    };
    
    template <typename Type>
    class GrowArray : public Array<Type> {...};	// inheritance
    
    template <typename Tp>
    class Stack
    {
        Array<Tp> ar;			// use an Array<> as a component	
        ...
    };
    ...
    Array < Stack<int> > asi;	// an array of stacks of int
    ```

**1、递归使用模板**

* 可以递归使用模板：

  * 对于前面的数组模板定义，可以这样使用：

    * ```c++
      ArrayTP< ArrayTP<int, 5>, 10> twodee;
      ```

    * 这使得 twodee 是一个包含10个元素的数组，其中每个元素都是一个包含5个int元素的数组。等价于：

      * ```c++
        int twodee[10] [5];
        ```

      * 请注意，在模板语法中，维的顺序与等价的二维数组相反。

  * 示例：

    * ```c++
      // ch14_18_twod.cpp  -- making a 2-d array
      #include <iostream>
      #include "ch14_17_arraytp.h"
      
      int main(void)
      {
      	using std::cout;
      	using std::endl;
      	ArrayTP<int, 10> sums;
      	ArrayTP<double, 10> aves;
      	ArrayTP< ArrayTP<int, 5>, 10> twodee;
      	
      	int i, j;
      	for (i = 0; i < 10; i++)
      	{
      		
      		sums[i] = 0;
      		for (j = 0; j < 5; j++)
      		{
      			twodee[i][j] = (i + 1) * (j + 1);
      			sums[i] += twodee[i][j];
      		}
      		aves[i] = (double)sums[i] / 10;
      	}
      
      	for (i = 0; i < 10; i++)
      	{
      		for (j = 0; j < 5; j++)
      		{
      			cout.width(2);
      			cout << twodee[i][j] << ' ';
      		}
      		cout << ": sum = ";
      		cout.width(3);
      		cout << sums[i] << ", average = " << aves[i] << endl;
      	}
      
      	cout << "Done.\n";
      
      	return 0;
      }
      ```

  * 结果：

    * ```c++
      1  2  3  4  5 : sum =  15, average = 1.5
      2  4  6  8 10 : sum =  30, average = 3
      3  6  9 12 15 : sum =  45, average = 4.5
      4  8 12 16 20 : sum =  60, average = 6
      5 10 15 20 25 : sum =  75, average = 7.5
      6 12 18 24 30 : sum =  90, average = 9
      7 14 21 28 35 : sum = 105, average = 10.5
      8 16 24 32 40 : sum = 120, average = 12
      9 18 27 36 45 : sum = 135, average = 13.5
      10 20 30 40 50 : sum = 150, average = 15
      ```

  **2、使用多个类型参数**

模板可以包含多个类型参数。

* 例如，假设希望类可以保存两种值，则可以创建并使用 Pair 模板来保存两个不同的值：

  * ```C++
    // ch14_19_pairs.cpp -- defining and using a Pair template
    #include <iostream>
    #include <string>
    
    template <class T1, class T2>
    class Pair
    {
    private:
    	T1 a;
    	T2 b;
    public:
    	T1& first();
    	T2& second();
    	T1 first() const { return a; }
    	T2 second() const { return b; }
    	Pair(const T1 & aval, const T2 & bval) : a(aval), b(bval) { }
    	Pair() {}
    };
    
    template<class T1, class T2>
    T1& Pair<T1, T2>::first()
    {
    	return a;
    }
    
    template<class T1, class T2>
    T2& Pair<T1, T2>::second()
    {
    	return b;
    }
    
    int main()
    {
    	using std::cout;
    	using std::endl;
    	using std::string;
    	Pair<string, int> ratings[4] =
    	{
    		Pair<string, int>("The Purpled Duck", 5),
    		Pair<string, int>("Jaquie's Frisco Al Fresco", 4),
    		Pair<string, int>("Cafe souffle", 5),
    		Pair<string, int>("Bertie's Eats", 3)
    	};
    
    	int joints = sizeof(ratings) / sizeof(Pair<string, int>);
    	cout << "Rating:\t Eatery\n";
    	for (int i = 0; i < joints; i++)
    		cout << ratings[i].second() << ":\t"
    			 << ratings[i].first() << endl;
    	cout << "0ops! Revised rating:\n";
    	ratings[3].first() = "Bertie's Fab Eats";
    	ratings[3].second() = 6;
    	cout << ratings[3].second() << ":\t"
    		 << ratings[3].first() << endl;
    	return 0;
    }
    ```

  * ```c++
    Rating:  Eatery
    5:      The Purpled Duck
    4:      Jaquie's Frisco Al Fresco
    5:      Cafe souffle
    3:      Bertie's Eats
    0ops! Revised rating:
    6:      Bertie's Fab Eats
    ```

**3、默认类型模板参数**

类模板的另一项新特性是，可以为类型参数提供默认值：

* ```c++
  template <class T1, class T2 = int> class Topo {...};
  ```

  * 这样，如果省略 T2 的值，编译器将使用 int：

    * ```c++
      Topo<double, double> m1; // T1 is double, T2 is double
      Topo<double> m2;		// T1 is double, T2 is int
      ```

* 虽然可以为类模板类型参数提供默认值，但不能为函数模板参数提供默认值。然而，可以为非类型参数提供默认值，这对于类模板和函数模板都是适用的。

#### 14.4.6 模板的具体化

模板具体化：隐式实例化、显式实例化和显式具体化。模板以泛型的方式描述类，而具体化是使用具体的类型生成类声明。

**1、隐式实例化**

* 目前笔记中所有的模板示例使用的都是隐式实例化：即它们声明一个或多个对象，指出所需的类型，而编译器使用通用模板提供的处方生成具体的定义：

  * ```c++
    ArrayTP<int, 100> stuff;	// implicit instantiation
    ```

* 编译器在需要对象之前，不会生成类的隐式实例化：

  * ```c++
    ArrayTP<double, 30> * pt;	// a pointer, no object needed yet
    pt = new ArrayTP<double, 30>;// now an object is needed
    ```

**2、显式实例化**

* 当使用关键字 template 并指出所需类型来声明类时，编译器将生成类声明的显式实例化。

  * 声明必须位于模板定义所在的名称空间中：

    * ```c++
      template class ArrayTP<string, 100>;	// generate ArrayTP<string, 100> class
      ```

    * 在这种情况下，虽然没有创建或提及类对象，编译器也将生成类声明(包括方法定义)。和隐式实例化样，也将根据通用模板来生成具体化。

**3、显式具体化**

* 显式具体化是特定类型（用于替换模板中的泛型）的定义。

  * 如果需要在为特殊类型实例化时，对模板进行修改，使其行为不同时，可以创建显式具体化：

    * 例如假设已经为用于表示排序后数组的类（元素在加入时被排序）定义了一个模板：

      * ```c++
        template <typename T>
        class SortedArray
        {
            ...// detials omitted
        };
        ```

    * 假设模板使用>运算符来对值进行比较，如果T是由 从 const char * 表示字符串，这将不管用。

      * 字符串将按地址排序。因此要求类定义使用 strcmp() ，而不是 > 来对值进行比较。

      * 这时，可以提供一个显式模板具体化，这将采用为具体类型定义的模板，而不是为泛型定义的模板。

      * 当具体化模板和通用模板都与实例化请求匹配时，编译器将使用具体化版本:

        * ```c++
          templace <> class Classname<specialized-type-name> {...};
          ```

        * 要使用新的表示方法提供一个专攻 const char * 类型使用的 SortedArray 模板，可以使用类似于下面的代码：

          * ```c++
            template <> class SortedArray<const char char *>
            {
                ...	// detials omitted
            };
            ```

          * 其中的实现代码将使用 strcmp() (而不是>) 来比较数组值现在当请求 const char *类型的 SortedArray 模板时，编译器将使用上述专用的定义，而不是通用的模板定义：

            * ```c++
              SortedArray<int> scores;	// use general definition
              SortedArray<const char * > dates;	// use specialized definition
              ```

**4、部分具体化**

部分具体化即部分限制模板的通用性。

* 部分具体化可以给类型参数之一指定具体的类型：

  * ```c++
    // general template
    template <class T1, class T2> class Pair {...};
    // specialization with T2 set to int
    template <class T1> class Pair<T1, int> {...};
    ```

    * 关键字 template 后面的 <> 声明的是没有被具体化的类型参数。

    * 因此，第二个声明将 T2 具体化为 int，但  T1 保持不变。

    * 如果指定所有的类型，则 <> 内将为空，这将导致显式具体化：

      * ```c++
        // specialization with T1 and T2 set to int
        template <> class Pair<int, int> {...};
        ```

* 如果有多个模板可供选择，编译器将使用具体化程度最高的模板。给定上述三个模板，情况如下：

  * ```c++
    Pair<double, double> p1;	// use general Pair template
    Pair<double, int> p2;		// use Pair<T1, int> partial specialization
    Pair<int, int> p3;			// use Pair<int, int> explicit specialization
    ```

* 也可以通过为指针提供特殊版本来部分具体化现有的模板：

  * ```c++
    template<class T>	// general version
    class Feeb {...};
    template<class T*>	// pointer partial specialization
    class Feeb {...};	// modified code
    ```

  * 如果提供的类型不是指针，则编译器将使用通用版本；

  * 如果提供的是指针，则编译器将使用指针具体化版本：

    * ```c++
      Feeb<char> fb1;		// use genetal Feeb template, T is char
      Feeb<char *> fb2;	// use Feeb T* specialization, T is char
      ```

    * 其他见P583

#### 14.4.7 成员模板

模板可用作结构、类或模板类的成员。要完全实现 STL 的设计，必须使用这项特性。

* 示例：

  * ```c++
    // ch14_20_tempmemb.cpp -- template members
    #include <iostream>
    
    using std::cout;
    using std::endl;
    template <typename T>
    class beta
    {
    private:
    	template <typename V>	// nested template class member
    	class hold
    	{
    	private:
    		V val;
    	public:
    		hold(V v = 0) : val(v) {}
    		void show() const { cout << val << endl; }
    		V Value() const { return val; }
    	};
    	hold<T> q;		// q成员是基于T类型（beta模板参数）的hold对象
    	hold<int> n;	// n是基于int类型的hold对象
    public:
    	beta(T t, int i) : q(t), n(i) {}
    	template<typename U>	// template method
    	U blab(U u, T t) { return (n.Value() + q.Value()) * u / t; }
    	void Show() const { q.show(); n.show(); }
    };
    
    int main()
    {
    	beta<double> guy(3.5, 3);
    	cout << "T was set to double\n";
    	guy.Show();
    	cout << "V was set to T, which is double, then V was set to int\n";
    	cout << guy.blab(10, 2.3) << endl;
    	cout << "U was set to int\n";
    	cout << guy.blab(10.0, 2.3) << endl;
    	cout << "U was set to double\n";
    	cout << "Done\n";
    	return 0;
    }
    ```

    * hold 模板是在私有部分声明的，因此只能在 beta 类中访问它。在 main() 中，下述声明使得 T 表示的是 double：

      * ```C++
        beta<double> guy(3.5, 3);
        ```

    * blab() 方法的 U 类型由该方法被调用时的参数值显式确定，T类型由对象的实例化类型确定。

    * 可以在beta模板中声明 hold 类和 blah 方法，并在 beta 模板的外面定义它：

      * ```c++
        template <typename T>
        class beta
        {
        private:
        	template <typename V>
        	class hold；
        	hold<T> q;
        	hold<int> n;
        public:
        	beta(T t, int i) : q(t), n(i) {}
        	template<typename U>
        	U blab(U u, T t);
        	void Show() const { q.show(); n.show(); }
        };
        
        template <typename T>
        	template <typename V>
        		class beta<T>::hold
                {
                    private:
        				V val;
        			public:
        				hold(V v = 0) : val(v) {}
        				void show() const { cout << val << endl; }
        				V Value() const { return val; }
                };
        
        template <typename T>
        	template <typename U>
        		U beta<T>::blab(U u, T t)
        		{
            		return (n.Value() + q.Value()) * u / t;
        		}
        ```

      * 因为模板是嵌套的，所以必须使用下面语法：

        * ```c++
          template <typename T>
          	template <typename V>
          ```

        * 不能：

          * ```c++
            template <typename T, template V>
            ```

      * 定义还必须指出 hold 和 blab 是 beta<T>类的成员，这是通过使用作用域解析运算符来完成的。

#### 14.4.8 将模板用作参数

模板可以包含类型参数 (如 typename T) 和非类型参数 (如int n) 。板还可以包含本身就是模板的参数：

* ```c++
  template <template <teamplate T> class Thing>
  class Crab
  ```

  * 模板参数是：

    * ```c++
      template <teamplate T> class Thing
      ```

      * 类型是：

        * ```c++
          template <teamplate T> class
          ```

      * 参数是：

        * ```c++
          Thing
          ```

* 示例：

  * ```c++
    // ch14_21_tempparm.cpp -- templates as parameters
    #include <iostream>
    #include "ch14_13_stacktp.h"
    
    template <template <typename T> class Thing>
    class Crab
    {
    private:
    	Thing<int> s1;
    	Thing<double> s2;
    public:
    	Crab() {};
    	// assumes the thing class has push() and pop() members
    	bool push(int a, double x) { return s1.push(a) && s2.push(x); }
    	bool pop(int& a, double& x) { return s1.pop(a) && s2.pop(x); }
    };
    
    int main()
    {
    	using std::cout;
    	using std::cin;
    	using std::endl;
    	Crab<Stack> nebula;
    // Stack must match template <typename T> class thing
    	int ni;
    	double nb;
    	cout << "Enter int double pairs, such as 4 3.5 (0 0 to end):\n";
    	while (cin >> ni >> nb && ni > 0 && nb > 0)
    	{
    		if (!nebula.push(ni, nb))
    			break;
    	}
    
    	while (nebula.pop(ni, nb))
    		cout << ni << ", " << nb << endl;
    	cout << "Done.\n";
    
    	return 0;
    }
    ```

* 结果：

  * ```c++
    Enter int double pairs, such as 4 3.5 (0 0 to end):
    50 22.48
    25 33.87
    60 19.12
    0 0
    60, 19.12
    25, 33.87
    50, 22.48
    Done.
    ```

* 可以混合使用模板参数和常规参数，例如，Crab 类的声明可以像下面这样打头：

  * ```c++
    template <template <typename T> class Thing, typename U, typename V>
    class Crab
    {
    private:
    	Thing<u> s1;
    	Thing<v> s2;
    public:
    	...
    };
    ```

  * 现在，成员s1和s2存储的数据型为泛型，而不是用硬编码指定的类型。

  * 这要求程序中的nebula的声明修改为：

    * ```c++
      Crab<Stack, int, double> nebula;	// T=Stack, U=int, V=double
      ```

    * 模板参数T表示一种模板类型，而类型参数U和V表示非模板类型。

**2、模板类的约束模板友元函数**

使友元函数本身称为模板时，即为约束模板友元作准备，要使类的每一个具体化都获得与友元匹配的具体化，主要有3步骤：

* 首先，在类定义的前面声明每个模板函数：

  * ```c++
    template <typename T> void counts();
    template <typename T> void report(T &);
    ```

* 然后，在函数中再次将模板声明为友元，这些语句根据类模板参数的类型声明具体化：

  * ```C++
    template <typename TT>
    class HasFriendT
    {
    ...
        friend void counts<TT>();
        friend void report<>(HasFriendT<TT> &);
        ...
    };
    ```

    * 声明中的<>指出这是模板具体化，对于report() 来说<>可以为空，因为可以从函数参数推断出如下模板类型参数：

      * ```c++
        HasFriendT<TT>
        ```

      * 然而也可以：

        * ```c++
          friend void report<TT>(HasFriendT<TT> &);
          ```

    * 但 counts() 函数没有参数，因此必须使用模板参数语法(<TT>)来指明其具体化。

* 示例：

  * ```c++
    // ch14_23_tmp2tmp.cpp -- template friends to a template class
    #include <iostream>
    using std::cout;
    using std::endl;
    
    // template prototypes
    template <typename T> void counts();
    template <typename T> void report(T&);
    
    // template class
    template <typename TT>
    class HasFriendT
    {
    private:
    	TT item;
    	static int ct;
    public:
    	HasFriendT(const TT& i) : item(i) { ct++; }
    	~HasFriendT() { ct--; }
    	friend void counts<TT>();
    	friend void report<>(HasFriendT<TT>&);
    };
    
    template <typename T>
    int HasFriendT<T>::ct = 0;
    
    // temolate friend functions definitions
    template <typename T>
    void counts()
    {
    	cout << "template size: " << sizeof(HasFriendT<T>) << "; ";
    	cout << "template counts(): " << HasFriendT<T>::ct << endl;
    }
    
    template <typename T>
    void report(T& hf)
    {
    	cout << hf.item << endl;
    }
    
    int main()
    {
    	counts<int>();
    	HasFriendT<int> hfi1(10);
    	HasFriendT<int> hfi2(20);
    	HasFriendT<double> hfdb(10.5);
    	report(hfi1);
    	report(hfi2);
    	report(hfdb);
    	cout << "counts<int>() output:\n";
    	counts<int>();
    	cout << "counts<double>() output:\n";
    	counts<double>();
    
    	return 0;
    }
    ```

* 结果：

  * ```c++
    template size: 4; template counts(): 0
    10
    20
    10.5
    counts<int>() output:
    template size: 4; template counts(): 2
    counts<double>() output:
    template size: 8; template counts(): 1
    ```

**3、模板类的非约束模板友元函数**
20240121
