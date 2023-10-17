## 第七章 函数——C++的编程模块

### 7.1 复习函数的基本知识

* 创建自己的函数包含3个方面——定义、提供原型和调用：

  * 提供函数定义；

  * 提供函数原型；

  * 调用函数。

  * 示例：

    * ```c++
      // ch07_01_calling.cpp -- defining, prototyping, and calling a fuction
      #include <iostream>
      void simple();
      
      int main() {
      	using namespace std;
      	cout << "main() will call the simple() function:\n";
      	simple();
      	cout << "main() is finished with the simple() function.\n";
      
      	return 0;
      }
      
      void simple() {
      	using namespace std;
      	cout << "I'm but a simple function.\n";
      }
      ```

  * 结果：

    * ```c++
      main() will call the simple() function:
      I'm but a simple function.
      main() is finished with the simple() function.
      ```



#### 7.1.1 定义函数

* 函数可分为2类：

  * 1、无返回值函数

    * 通用格式：

      * ```c++
        void functionName(parameterList){
            statement(S)
            return;
        }
        ```

  * 2、有返回值函数：

    * 通用格式：

      * ```c++
        typeName functionName(parameterList){
            statements
            return values;
        }
        ```

    * C++对返回值有一定的限制：不能直接返回数组，但可以将数组作为结构或对象组成部分来返回。



#### 7.1.2 函数原型和函数调用

* 函数原型

  * 示例：

    * ```c++
      // ch07_02_protos.cpp -- using prototypes and function calls
      #include <iostream>
      void cheers(int);
      double cube(double x);
      
      int main() {
      	using namespace std;
      	cheers(5);
      	cout << "Give me a number: ";
      	double side;
      	cin >> side;
      	double volume = cube(side);
      	cout << "A " << side << "-foot cube has a volume of ";
      	cout << volume << " cubic feet.\n";
      	cheers(cube(2));
      
      	return 0;
      }
      
      void cheers(int n) {
      	using namespace std;
      	for (int i = 0; i < n; i++)
      		cout << "Cheers! ";
      	cout << endl;
      }
      
      double cube(double x) {
      	return x * x * x;
      }
      ```

  * 结果：

    * ```c++
      Cheers! Cheers! Cheers! Cheers! Cheers!
      Give me a number: 5
      A 5-foot cube has a volume of 125 cubic feet.
      Cheers! Cheers! Cheers! Cheers! Cheers! Cheers! Cheers! Cheers!
      ```

  * 1、为什么需要原型

    * 原型描述了函数到编译器的接口；
    * 也就是说，它将函数返回值的类型(如果有的话)以及参数的类型和数量告诉编译器。

  * 2、原型的语法

    * 函数原型是一条语句，以分号结束，不要求提供变量名（也可以加上，方便理解）；
    * 即你在main()之前声明的就是函数原型语句，它是复制函数定义的函数头，并删除变量名，留下类型列表，并且加上分号而成的。

  * 3、原型的功能

    * 确保以下3点：
      * 编译器正确处理函数返回值;
      * 编译器检查使用的参数数目是否正确;
      * 编译器检查使用的参数类型是否正确。如果不正确，则转换为正确的类型(如果可能的话)。



### 7.2 函数参数和按值传递

* 用于接收传递值得变量被称为形参（argumernt）；
* 传递给函数得值被称为实参（parameter）。
* ![image](https://github.com/CoderSuHang/Cpp-Primer-Plus-Notes/assets/104765251/d1573343-0a57-473a-b475-0800002a04df)

* ![image](https://github.com/CoderSuHang/Cpp-Primer-Plus-Notes/assets/104765251/0e371b12-d419-4981-8b17-65d74bb132d2)




#### 7.2.1 多个参数

* 函数可以有多个参数。在调用函数时，只需使用逗号将这些参数分开即可：

  * ```c++
    n_chars('R', 25);
    ```

* 函数定义时，也在函数头中使用由逗号分隔的参数声明列表：

  * ```c++
    void n_char(char c, int n){
        ...
    }
    ```

* 函数原型：

  * ```c++
    void n_char(char, int);//某些复杂函数中可以加上变量名方便理解
    ```

* 示例：

  * ```c++
    // ch07_03_twoarg.cpp -- a function with 2 arguments
    #include <iostream>
    using namespace std;
    void n_chars(char, int);
    
    int main() {
    	int times;
    	char ch;
    	cout << "Enter a character: ";
    	cin >> ch;
    	while (ch != 'q') {
    		cout << "Enter an integer: ";
    		cin >> times;
    		n_chars(ch, times);
    		cout << "\nEnter another character or press the"
    			" q-key to quit: ";
    		cin >> ch;
    	}
    	cout << "The value of times is " << times << ".\n";
    	cout << "Bye\n";
    
    	return 0;
    }
    
    void n_chars(char c, int n) {
    	while (n-- > 0)
    		cout << c;
    }
    ```

* 结果：

  * ```c++
    Enter a character: W
    Enter an integer: 50
    WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
    Enter another character or press the q-key to quit: a
    Enter an integer: 20
    aaaaaaaaaaaaaaaaaaaa
    Enter another character or press the q-key to quit: q
    The value of times is 20.
    Bye
    ```

  * 程序清单中的 main() 函数使用一个 while 循环提供重复输入(并让读者温使用循环的技巧) 它使用 cin>>ch（`跳过第二次读取换行符`），而不是 cin.get (ch)或 ch = cinget()来读取一个字符。原因：

    * 这两个cin.get()函数读取所有的输入字符包括空格和换行符，而 cin>> 跳过空格和换行符。当用户对程序提示作出响应时，必须在每行的最后按 Enter 键，以生成换行符。cin>ch 方法可以轻松地跳过这些换行符，但当输入的下一个字符为数字时，cin.get()将读取后面的换行符。可以通过编程来避开这种麻烦，但比较简便的方法是像该程序那样使用 cin。



#### 7.2.2 另外一个接受两个参数的函数

* 演示局部变量的用法：

  * 示例：

    * ```c++
      // ch07_04_lotto.cpp -- probability of winning
      #include <iostream>
      
      long double probability(unsigned numbers, unsigned picks);
      
      int main() {
      	using namespace std;
      	double total, choices;
      	cout << "Enter the total number of choices on the game card and\n"
      			"the number of picks allowed:\n";
      	while ((cin >> total >> choices) && choices <= total) {
      		cout << "You have one chance in ";
      		cout << probability(total, choices);
      		cout << " of wining.\n";
      		cout << "Next two numbers (q to quit): ";
      	}
      	cout << "bye\n";
      
      	return 0;
      }
      
      long double probability(unsigned numbers, unsigned picks) {
      	long double result = 1.0;
      	long double n;
      	unsigned p;
      
      	for (n = numbers, p = picks; p > 0; n--, p--)
      		result = result * n / p;
      	return result;
      }
      ```

  * 结果：

    * ```c++
      Enter the total number of choices on the game card and
      the number of picks allowed:
      49 6
      You have one chance in 1.39838e+07 of wining.
      Next two numbers (q to quit): 51 6
      You have one chance in 1.80095e+07 of wining.
      Next two numbers (q to quit): 38 6
      You have one chance in 2.76068e+06 of wining.
      Next two numbers (q to quit): q
      bye
      ```

    * 形参：number 和 picks；（形参从主函数里调用函数那获得自己的值）

    * 局部变量： result 、n 和 p；（从函数中获得自己的值）



### 7.3 函数和数组

* 示例：

  * ```c++
    // ch07_05_arrfun1.cpp -- functions with an array argument
    #include <iostream>
    const int ArSize = 8;
    int sum_arr(int arr[], int n);
    int main() {
    	using namespace std;
    	int cookies[ArSize] = {1, 2, 4, 8, 16, 32, 64, 128};
    
    	int sum = sum_arr(cookies, ArSize);
    	cout << "Total cookies eaten: " << sum << "\n";
    
    	return 0;
    }
    
    int sum_arr(int arr[], int n) {
    	int total = 0;
    	for (int i = 0; i < n; i++)
    		total = total + arr[i];
    	return total;
    }
    ```

* 结果：

  * ```c++
    Total cookies eaten: 255
    ```

  * 这看起来似乎合理。方括号指出 arr 是一个数组，而方括号为空则表明，可以将任何长度的数组传递给该函数。

  * 但实际情况并非如此: arr 实际上并不是数组，而是一个指针！好消息是，在编写函数的其余部分时，可以将 arr 看作是数组。



#### 7.3.1 函数如何使用指针来处理数组

* C++将数组名视为指针，将数组名解释为其第一个元素的地址：

  * ```c++
    cookies == &cookies[0]
    ```

  * 例外：

    * 数组声明使用数组名来标记存储位置；
    * 对数组名使用 sizeof 将得到整个数组的长度(以字节为单位)；
    * 将地址运算符&用于数组名时，将返回整个数组的地址，例如&cookies 将返回一个32字节内存块的地址(如果int长4字节)。

* 正确的函数头应该是：

  * ```c++
    int sum_arr(int * arr, int n)
    ```

  * 但是前者函数头也是正确，即当且仅当用于函数头或函数原型时， int *arr 和 int arr[ ] 的含义是相同的。

* 记住下面2个恒等式：

  * ```c++
    arr[i] == *(ar + i);
    &arr[i] == ar + i;
    ```

  * 对于遍历数组而言，使用指针加法和数组下标时等效的。



#### 7.3.2 将数组作为参数意味着什么

* 传递常规变量时，函数将使用该变量的拷贝；

* 但传递数组时，函数将使用原来的数组。

* ![image](https://github.com/CoderSuHang/Cpp-Primer-Plus-Notes/assets/104765251/73d79afb-75e8-4c71-835d-5b19891bea4c)


* 示例：

  * ```c++
    // ch07_06_arrfun2.cpp -- functions with an array argument
    #include <iostream>
    const int ArSize = 8;
    int sum_arr(int arr[], int n);
    
    int main() {
    	int cookies[ArSize] = {1, 2, 4, 8, 16, 32, 64, 128};
    	std::cout << cookies << " = array address, ";
    	std::cout << sizeof cookies << " = sizeof cookies\n";
    
    	int sum = sum_arr(cookies, ArSize);
    	std::cout << "Total cookies eaten: " << sum << std::endl;
    
    	sum = sum_arr(cookies, 3);
    	std::cout << "First three eaters ate " << sum << " cookies.\n";
    
    	sum = sum_arr(cookies + 4, 4);
    	std::cout << "Last four eaters ate " << sum << " cookies.\n";
    
    	return 0;
    }
    
    int sum_arr(int arr[], int n) {
    	int total = 0;
    	std::cout << arr << " = arr, ";
    	std::cout << sizeof arr << " = sizeof arr\n";
    	for (int i = 0; i < n; i++)
    		total = total + arr[i];
    	return total;
    }
    ```

* 结果：

  * ```c++
    003FFDB0 = array address, 32 = sizeof cookies
    003FFDB0 = arr, 4 = sizeof arr
    Total cookies eaten: 255
    003FFDB0 = arr, 4 = sizeof arr
    First three eaters ate 7 cookies.
    003FFDC0 = arr, 4 = sizeof arr
    Last four eaters ate 240 cookies.
    ```

  * 为将数组类型和元素数量告诉数组处理函数，请通过两个不同的参数来传递它们：

    * ```c++
      void fillArray(int arr[], int size);
      ```



#### 7.3.3 更多数组函数示例

* 1、填充数组

  * P216
  * 使用循环输入数据，设置限制长度，对问题输入进行判断；

* 2、显示数组及用const保护数组

  * P217
  * 为防止函数无意中修改数组的内容，可在声明形参时使用关键字const

* 3、修改数组

  * P217
  * 对数组进行的第三项操作是将每个元素与同一个重新评估因子相乘。
  * 需要给函数传递3个参数：因子、数组和元素数目。该函数不需要返回值
  * 会修改数组的值

* 4、将上述代码组合起来：

  * 例程：

    * ```c++
      // ch07_07_arrfun3.cpp -- array functions and const
      #include <iostream>
      const int Max = 5;
      
      int fill_array(double ar[], int limit);
      void show_array(const double ar[], int n);
      void revalue(double r, double ar[], int n);
      
      int main() {
      	using namespace std;
      	double properties[Max];
      
      	int size = fill_array(properties, Max);
      	show_array(properties, size);
      	if (size > 0) {
      		cout << "Enter revaluation factor: ";
      		double factor;
      		while (!(cin >> factor)) {
      			cin.clear();
      			while (cin.get() != '\n')
      				continue;
      			cout << "Bad input; Please enter a number: ";
      		}
      		revalue(factor, properties, size);
      		show_array(properties, size);
      	}
      	cout << "Done.\n";
      	cin.get();
      	cin.get();
      
      	return 0;
      }
      
      int fill_array(double ar[], int limit) {
      	using namespace std;
      	double temp;
      	int i;
      	for (i = 0; i < limit; i++) {
      		cout << "Enter value #" << (i + 1) << ": ";
      		cin >> temp;
      		if (!cin) {
      			cin.clear();
      			while (cin.get() != '\n')
      				continue;
      			cout << "Bad input; input process terminated.\n";
      			break;
      		}
      		else if (temp < 0)
      			break;
      		ar[i] = temp;
      	}
      	return i;
      }
      
      void show_array(const double ar[], int n) {
      	using namespace std;
      	for(int i = 0; i < n; i++) {
      		cout << "Property #" << (i + 1) << ": $";
      		cout << ar[i] << endl;
      	}
      }
      
      void revalue(double r, double ar[], int n) {
      	for (int i = 0; i < n; i++)
      		ar[i] *= r;
      }
      ```

  * 结果：

    * ```c++
      Enter value #1: 100000
      Enter value #2: 80000
      Enter value #3: 222000
      Enter value #4: 118000
      Enter value #5: 240000
      Property #1: $100000
      Property #2: $80000
      Property #3: $222000
      Property #4: $118000
      Property #5: $240000
      Enter revaluation factor: 0.8
      Property #1: $80000
      Property #2: $64000
      Property #3: $177600
      Property #4: $94400
      Property #5: $192000
      Done.
      ```

    * ```c++
      Enter value #1: 200000
      Enter value #2: 84000
      Enter value #3: 160000
      Enter value #4: -2
      Property #1: $200000
      Property #2: $84000
      Property #3: $160000
      Enter revaluation factor: 1.20
      Property #1: $240000
      Property #2: $100800
      Property #3: $192000
      Done.
      ```

* 6、数组处理函数的常用编写方式

  * 当处理double数组的函数时，需要修改数组：

    * ```c++
      void f_modify(double ar[], int n);
      ```

  * 如果不修改数组：

    * ```c++
      void _f_no_change(const double ar[], int n);
      ```



#### 7.3.3 更多数组函数示例

* 1、填充数组

  * P216
  * 使用循环输入数据，设置限制长度，对问题输入进行判断；

* 2、显示数组及用const保护数组

  * P217
  * 为防止函数无意中修改数组的内容，可在声明形参时使用关键字const

* 3、修改数组

  * P217
  * 对数组进行的第三项操作是将每个元素与同一个重新评估因子相乘。
  * 需要给函数传递3个参数：因子、数组和元素数目。该函数不需要返回值
  * 会修改数组的值

* 4、将上述代码组合起来：

  * 例程：

    * ```c++
      // ch07_07_arrfun3.cpp -- array functions and const
      #include <iostream>
      const int Max = 5;
      
      int fill_array(double ar[], int limit);
      void show_array(const double ar[], int n);
      void revalue(double r, double ar[], int n);
      
      int main() {
      	using namespace std;
      	double properties[Max];
      
      	int size = fill_array(properties, Max);
      	show_array(properties, size);
      	if (size > 0) {
      		cout << "Enter revaluation factor: ";
      		double factor;
      		while (!(cin >> factor)) {
      			cin.clear();
      			while (cin.get() != '\n')
      				continue;
      			cout << "Bad input; Please enter a number: ";
      		}
      		revalue(factor, properties, size);
      		show_array(properties, size);
      	}
      	cout << "Done.\n";
      	cin.get();
      	cin.get();
      
      	return 0;
      }
      
      int fill_array(double ar[], int limit) {
      	using namespace std;
      	double temp;
      	int i;
      	for (i = 0; i < limit; i++) {
      		cout << "Enter value #" << (i + 1) << ": ";
      		cin >> temp;
      		if (!cin) {
      			cin.clear();
      			while (cin.get() != '\n')
      				continue;
      			cout << "Bad input; input process terminated.\n";
      			break;
      		}
      		else if (temp < 0)
      			break;
      		ar[i] = temp;
      	}
      	return i;
      }
      
      void show_array(const double ar[], int n) {
      	using namespace std;
      	for(int i = 0; i < n; i++) {
      		cout << "Property #" << (i + 1) << ": $";
      		cout << ar[i] << endl;
      	}
      }
      
      void revalue(double r, double ar[], int n) {
      	for (int i = 0; i < n; i++)
      		ar[i] *= r;
      }
      ```

  * 结果：

    * ```c++
      Enter value #1: 100000
      Enter value #2: 80000
      Enter value #3: 222000
      Enter value #4: 118000
      Enter value #5: 240000
      Property #1: $100000
      Property #2: $80000
      Property #3: $222000
      Property #4: $118000
      Property #5: $240000
      Enter revaluation factor: 0.8
      Property #1: $80000
      Property #2: $64000
      Property #3: $177600
      Property #4: $94400
      Property #5: $192000
      Done.
      ```

    * ```c++
      Enter value #1: 200000
      Enter value #2: 84000
      Enter value #3: 160000
      Enter value #4: -2
      Property #1: $200000
      Property #2: $84000
      Property #3: $160000
      Enter revaluation factor: 1.20
      Property #1: $240000
      Property #2: $100800
      Property #3: $192000
      Done.
      ```

* 6、数组处理函数的常用编写方式

  * 当处理double数组的函数时，需要修改数组：

    * ```c++
      void f_modify(double ar[], int n);
      ```

  * 如果不修改数组：

    * ```c++
      void _f_no_change(const double ar[], int n);
      ```



#### 7.3.4 使用数组区间的函数

* 新方法：

  * 即指定元素区间（range），这可以通过传递两个指针来完成：

    * 一个指针标识数组的开头，另一个指针标识数组的尾部：

      * ```c++ 
        double elbuod[20];
        ```

      * 指针 elboud 和 elboud + 20 定义了区间，前者指向第一个元素，表达式 elboud + 19 指向最后一个元素，即 elboud[19] ，因此 elboud + 20 指向数组结尾后面的一个位置。 

  * 示例：

    * ```c++
      // ch07_08_arrfun4.cpp -- functions with an array range
      #include <iostream>
      const int ArSize = 8;
      int sum_arr(const int* begin, const int* end);
      int main() {
      	using namespace std;
      	int cookies[ArSize] = {1, 2, 4, 8, 16, 32, 64, 128};
      
      	int sum = sum_arr(cookies, cookies + ArSize);
      	cout << "Total cookies eaten: " << sum << endl;
      
      	sum = sum_arr(cookies, cookies + 3);
      	cout << "First three eaters ate " << sum << " cookies.\n";
      
      	sum = sum_arr(cookies + 4, cookies + 8);
      	cout << "Last four eaters ate " << sum << " cookies.\n";
      
      	return 0;
      }
      
      int sum_arr(const int* begin, const int* end) {
      	const int * pt;
      	int total = 0;
      
      	for (pt = begin; pt != end; pt++)
      		total = total + *pt;
      	return total;
      }
      ```

  * 结果：

    * ```c++
      Total cookies eaten: 255
      First three eaters ate 7 cookies.
      Last four eaters ate 240 cookies.
      ```



#### 7.3.5 指针和 const

* 可以用两种不同的方式将 const 关键字用于指针：
  * 1、让指针指向一个常量对象，可防止使用该指针来修改所指向的值；
    * c++禁止将 const 的地址赋值给非 const 指针。
  * 2、将指针本身声明为常量，可防止改变指针指向的位置。



### 7.4 函数和二维数组

* 编写将二维数组作为参数的函数，必须将数组名视为其地址。
* 比较难理解，用的时候看P254即可。



### 7.5 函数和C-风格字符串

* C-风格字符串由一系列字符组成，以空值字符结尾；
* 可以使用 const 来禁止对字符串参数进行修改。



#### 7.5.1 将C-风格字符串作为参数的函数

* 将字符串作为参数传递给函数的3种表示方式：
  * char 数组；
  * 用引号括起的字符串常量；
  * 被设置为字符串的地址和char指针。

* 示例：

  * ```C++	
    // ch07_09_strgfun.cpp -- functions with a string argument
    #include <iostream>
    unsigned int c_in_str(const char* str, char ch);
    
    int main() {
    	using namespace std;
    	static char mmm[15] = "minimum";
    	const char* wail = "ululate";
    
    	unsigned int ms = c_in_str(mmm, 'm');
    	unsigned int us = c_in_str(wail, 'u');
    
    	cout << ms << " m characters in " << mmm << endl;
    	cout << us << " u characters in " << wail << endl;
    
    	return 0;
    }
    
    unsigned int c_in_str(const char* str, char ch) {
    	unsigned int count = 0;
    	while (*str) {
    		if (*str == ch)
    			count++;
    		str++;
    	}
    	return count;
    }
    ```

* 结果：

  * ```C++
    3 m characters in minimum
    2 u characters in ululate
    ```

  * 使用指针表示法提醒读者注意，参数不一定必须是数组名，也可以是其他形式的指针。

#### 7.5.2 返回C-风格字符串的函数

* 函数无法返回一个字符串，但可以返回字符串的地址。

* 示例：

  * ```C++
    // ch07_10_strgback.cpp -- a function that returns a pointer to char
    #include <iostream>
    char* buildstr(char c, int n);
    int main() {
    	using namespace std;
    	int times;
    	char ch;
    
    	cout << "Enter a character: ";
    	cin >> ch;
    
    	cout << "Enter an integer: ";
    	cin >> times;
    	char* ps = buildstr(ch, times);
    	cout << ps << endl;
    	delete[] ps;
    	ps = buildstr('+', 20);
    	cout << ps << "-DONE-" << ps << endl;
    	delete[] ps;
    
    	return 0;
    }
    
    char* buildstr(char c, int n) {
    	char* pstr = new char[n + 1];
    	pstr[n] = '\0';
    	while (n-- > 0)
    		pstr[n] = c;
    	return pstr;
    }
    ```

* 结果：

  * ```C++
    Enter a character: V
    Enter an integer: 46
    VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
    ++++++++++++++++++++-DONE-++++++++++++++++++++
    ```

  * 要创建包含 n个字符的字符串，需要能够存储 n+1个字符的空间，以便能够存储空值字符。

  * 注意，变量 pstr 的作用域为 buildstr 函数内，因此该函数结束时，pstr(而不是字符使用的内存将被释放。但由于函数返回了 pstr 的值，因此程序仍可以通过 mai()中的指针 ps 来访问新建的字符串。



### 7.6 函数和结构

#### 7.6.1 传递和返回结构

* 当结构比较小时，按值传递结构最合理。

* 例程：

  * ```C++
    // ch07_11_travel.cpp -- using structures with functions
    #include <iostream>
    struct travel_time {
    	int hours;
    	int mins;
    };
    const int Mins_per_hr = 60;
    
    travel_time sum(travel_time t1, travel_time t2);
    void show_time(travel_time t);
    
    int main() {
    	using namespace std;
    	travel_time day1 = { 5, 45 };
    	travel_time day2 = { 4, 55 };
    
    	travel_time trip = sum(day1, day2);
    	cout << "Two-day total: ";
    	show_time(trip);
    
    	travel_time day3 = { 4, 32 };
    	cout << "Three-day total: ";
    	show_time(sum(trip, day3));
    
    	return 0;
    }
    
    travel_time sum(travel_time t1, travel_time t2) {
    	travel_time total;
    
    	total.mins = (t1.mins + t2.mins) % Mins_per_hr;
    	total.hours = t1.hours + t2.hours +
    		(t1.mins + t2.mins) / Mins_per_hr;
    
    	return total;
    }
    
    void show_time(travel_time t) {
    	using namespace std;
    	cout << t.hours << " hours, "
    		 << t.mins << " minutes\n";
    }
    ```

* 示例：

  * ```c++
    Two-day total: 10 hours, 40 minutes
    Three-day total: 15 hours, 12 minutes
    ```



#### 7.6.2 另一个处理结构的函数示例

* 示例：

  * ```c++
    // ch07_12_atrctfun.cpp -- functions with a structure argument
    #include <iostream>
    #include <cmath>
    
    struct polar {
    	double distance;
    	double angle;
    };
    
    struct rect {
    	double x;
    	double y;
    };
    
    polar rect_to_polar(rect xypos);
    void show_polar(polar dapos);
    
    int main() {
    	using namespace std;
    
    	rect rplace;
    	polar pplace;
    
    	cout << "Enter the x and y values: ";
    	while (cin >> rplace.x >> rplace.y) {
    		pplace = rect_to_polar(rplace);
    		show_polar(pplace);
    		cout << "Next two numbers (q to quit): ";
    	}
    	cout << "Done.\n";
    
    	return 0;
    }
    
    polar rect_to_polar(rect xypos) {
    	using namespace std;
    	polar answer;
    
    	//数学库中的sqrt()使用水平和垂直坐标来计算距离:
    	answer.distance =
    		sqrt(xypos.x * xypos.x + xypos.y * xypos.y);
    	//数学库中的atan2()函数可根据x和y的值计算角度:
    	answer.angle = atan2(xypos.y, xypos.x);
    	return answer;
    }
    
    void show_polar(polar dapos) {
    	using namespace std;
    	//弧度值乘以180/Π，约为57.29577951
    	const double Rad_to_deg = 57.29577951;
    
    	cout << "distance = " << dapos.distance;
    	cout << ", angle = " << dapos.angle * Rad_to_deg;
    	cout << " degrees\n";
    }
    ```

* 结果：

  * ```c++
    Enter the x and y values: 30 40
    distance = 50, angle = 53.1301 degrees
    Next two numbers (q to quit): -100 100
    distance = 141.421, angle = 135 degrees
    Next two numbers (q to quit): q
    Done.
    ```

  * while (cin >> rplace.x >> rplace.y)

    * cin >> 用作测试条件消除了排除特定数值的限制，能够接受任何有效的数字输入，无论正负，详情可看P233。



#### 7.6.3 传递结构的地址

* 传递结构的地址比整个结构节省时间和空间。

* 需要使用指向结构的指针；

* 需要修改的3个地方：

  * 调用函数时，将结构的地址 (&pplace) 而不是结构本身 (pplace) 传递给它；
  * 将形参声明为指向 polar 的指针，即 polar *类型。由于函数不应该修改结构，因此使用了const 修饰符；
  * 由于形参是指针而不是结构，因此应间接成员运算符(->)，而不是成员运算符(点)

* 示例：

  * ```c++
    // ch07_13_strctptr.cpp -- functions with pointer to structure argument
    #include <iostream>
    #include <cmath>
    
    struct polar {
    	double distance;
    	double angle;
    };
    
    struct rect {
    	double x;
    	double y;
    };
    
    void rect_to_polar(const rect * pxy, polar * pda);
    void show_polar(const polar * pda);
    
    int main() {
    	using namespace std;
    
    	rect rplace;
    	polar pplace;
    
    	cout << "Enter the x and y values: ";
    	while (cin >> rplace.x >> rplace.y) {
    		rect_to_polar(&rplace, &pplace);
    		show_polar(&pplace);
    		cout << "Next two numbers (q to quit): ";
    	}
    	cout << "Done.\n";
    
    	return 0;
    }
    
    void rect_to_polar(const rect* pxy, polar* pda) {
    	using namespace std;
    
    	//数学库中的sqrt()使用水平和垂直坐标来计算距离:
    	pda->distance =
    		sqrt(pxy->x * pxy->x + pxy->y * pxy->y);
    	//数学库中的atan2()函数可根据x和y的值计算角度:
    	pda->angle = atan2(pxy->y, pxy->x);
    }
    
    void show_polar(const polar* pda) {
    	using namespace std;
    	//弧度值乘以180/Π，约为57.29577951
    	const double Rad_to_deg = 57.29577951;
    
    	cout << "distance = " << pda->distance;
    	cout << ", angle = " << pda->angle * Rad_to_deg;
    	cout << " degrees\n";
    }
    ```

* 结果：

  * ```c++
    Enter the x and y values: 30 40
    distance = 50, angle = 53.1301 degrees
    Next two numbers (q to quit): -100 100
    distance = 141.421, angle = 135 degrees
    Next two numbers (q to quit): q
    Done.
    ```

  * 该例程使用的是指针，让函数能够对原始树结构进行操作

  * 而前一个例程使用的是结构副本



### 7.7 函数和 string 对象

* 与数组相比，string对象与结构更相似。

* 示例：

  * ```c++
    // ch07_14_topfive.cpp -- handling an array of string objects
    #include <iostream>
    #include <string>
    
    using namespace std;
    const int SIZE = 5;
    void display(const string sa[], int n);
    
    int main() {
    	string list[SIZE];
    	cout << "Enter your " << SIZE << " favorite astronomical sights:\n";
    	for (int i = 0; i < SIZE; i++) {
    		cout << i + 1 << ": ";
    		getline(cin, list[i]);
    	}
    
    	cout << "Your list:\n";
    	display(list, SIZE);
    
    	return 0;
    }
    
    void display(const string sa[], int n) {
    	for (int i = 0; i < n; i++)
    		cout << i + 1 << ": " << sa[i] << endl;
    }
    ```

* 结果：

  * ```c++
    Enter your 5 favorite astronomical sights:
    1: Orion Nebula
    2: M13
    3: Saturn
    4: Jupiter
    5: Moon
    Your list:
    1: Orion Nebula
    2: M13
    3: Saturn
    4: Jupiter
    5: Moon
    ```

  * 形参 sa 是一个指向 string 对象的指针，因此 sa[i] 是一个string对象。



### 7.8 函数与 array 对象
