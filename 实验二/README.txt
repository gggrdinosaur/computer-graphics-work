实验二 DDA算法生成直线段
时间：2022年3月23日
地点：信息学院2202机房

1、实验内容：
熟悉OPENGL，通过DDA算法生成直线段
2、实验目的：
安装OPENGL，能编写代码运行，参考课本代码
3、实验代码：
本次实验通过DAA增量式算法实现了直线段的生成。
4、实验结果：

5、实验总结
  c语言中有取整函数round(x)，但这个函数是对x进行四舍五入取整，而在DDA算法中取整是只取整数部分，
  不管小数部分的大小，因此不能使用round(x)函数，而应该自己重新编写，并且，编写这个函数时不能再使用round作为函数名，
  应该另取一个函数名，否则会提示冲突。

