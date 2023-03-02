# ARXMLTransformer
## 如何运行
cmake .

make

./xmltest

## 部分文件说明
PDUClass.h: I_SIGNAL_I_PDU类定义

tinyxml2.h, tinyxml2.cpp: XML解析所需定义与实现，其中XMLDocument在tinyxml基础上增添了遍历函数AcceptTree(), generateMap(), generateMap2(), generateMap3(), 和判断标签对应变量类型及对对象赋值的函数decideClassType()（未实现）

xmltest.cpp: 生成可执行程序的测试文件

xmltest_copy.cpp: 原tinyxml的xmltest.cpp
