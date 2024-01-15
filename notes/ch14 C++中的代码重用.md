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
