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
* ![image-20231013104726504](C:\Users\10482\AppData\Roaming\Typora\typora-user-images\image-20231013104726504.png)
* ![image-20231013104951679](C:\Users\10482\AppData\Roaming\Typora\typora-user-images\image-20231013104951679.png)



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
