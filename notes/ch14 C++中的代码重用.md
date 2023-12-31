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
