# 最长成语接龙
此项目源自[知乎问题](https://www.zhihu.com/question/659421716/answer/3539132943)，数据来源于[github项目](https://github.com/crazywhalecc/idiom-database)，包括近3w个4字成语。此项目的目标是求解尽可能长的4字成语接龙。
项目求解部分采用C++（chain.cpp，需要安装json库），验证部分采用Python（validate.py），
# 使用方法
## Linux / MacOS
直接终端执行
```bash
./chain.o
```
或重新编译执行
```bash
bash build_run.sh
```
## Windows
使用C++编译器或IDE重新编译chain.cpp然后再运行
# 各个文件说明
## result.txt
成语接龙输出结果，包括两行：
第一行是长度
第二行是结果
## config.json
配置文件，支持4个模式：
0. 原始模式，包括所有成语（字数>=3）；
1. 四字模式，只包括4字成语；
2. 数字模式，只包括包含数字的成语；
3. 自定义模式，成语包含的字集在freestyle.json中配置；
其他字段参考变量名称与具体代码。
## validate.py
验证脚本，检查result.txt是否是合法的成语接龙，
使用方法（Linux/MaxOS终端下）
```bash
python validate.py result.txt
```
## chain.cpp
求解源文件
## chain.o
编译后的即可执行文件
## cache.txt
太大并未上传至此，不影响项目运行，本地可生成自己的cache.txt
## 174-result-digit.txt
数字模式的一个运行结果
## 9132-result-four.txt
四字模式的一个运行结果
## 9260-result-original.txt
原始模式的一个运行结果
## 9474-result-four.txt
四字模式目前最好结果
# 算法
遗传变异算法、蚁群算法、DFS暴力搜索

