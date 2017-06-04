# 波兰表达式

**例子**:中缀表达式转后缀\(波兰\)表达式  
<!-- LaTex $$ [A+B \times (C-D) \div E+F] \rightarrow [A \space B \space C \space D - \times E \div + F +] $$ -->
<img src="http://latex.codecogs.com/gif.latex?[A+B\times(C-D)\divE+F]\rightarrow[ABCD-\times{E}\div+F+]" />

作者：Deep Reader
链接：https://www.zhihu.com/question/26887527/answer/43166739
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
在处理过程中假设表达式是合法的，且仅由`( ) + - * / 整数 空格`构成.

## 中缀表达式转后缀表达式
首先在原表达式前后加`(` `)`,然后开始解析.  
从左往右解析,原表达式中,
1. 数字,直接Push_back进入波兰数组  
2. `(`,直接进入符号栈  
3. `)`,不入栈,Pop栈中元素直到Pop出`(`  
4. `+` `-`,Pop栈中元素,直到符号栈顶为`(`,然后`+` `-`入栈  
5. `*` `/`,Pop栈中元素,直到栈顶为`(`或者优先级较低的`+` `-`,然后`*` `/`入栈.  

Pop出的符号,除了`(`,直接Push_back进入波兰数组.

## 后缀表达式求解
从左往右解析波兰表达式(波兰数组),
1. 数字,直接进入求解栈;
2. `+` `-` `*` `/`,从求解栈中先后Pop出<img src="http://latex.codecogs.com/gif.latex?n_2" /> <!-- LaTex n_2 -->,<img src="http://latex.codecogs.com/gif.latex?n_1" /> <!-- LaTex n_1 -->,然后根据运算符计算\(如<img src="http://latex.codecogs.com/gif.latex?n_1+n_2" /> <!-- LaTex n_1+n_2-->\),结果Push回求解栈.

最后求解栈中会只剩一个数字,即运算结果.
