# State of the Art

| size |  start  |   end   |        file         |     date     | version |
| ---- | ------- | ------- | ------------------- | ------------ | ------- |
| 9729 | 三老五更 | 瓦解土崩 |  9729-solution.json  |   20240817  |    v1    |
| 9693 | 自视甚高 | 德本财末 |  9693-solution.json  |   20240815  |    v1    |
| 9677 | 乐极则忧 | 期期艾艾 | 9677-result-four.txt |   20240726  |    v0    |
| 9627 | 泰极而否 | 邦国殄瘁 | 9627-result-four.txt |   20240713  |    v0    |
| 9474 | 手足异处 | 阵马风樯 | 9474-result-four.txt |   20240707  |    v0    |

The files are located in paths data/output/ and data/v0/

# Background 背景

The [longest path problem](https://en.wikipedia.org/wiki/Longest_path_problem) in TCS is NP-hard, while the decision version is NP-complete, because it can be reduced to the Hamiltonian path problem, which is proved to be NP-complete.  
理论计算机科学中最长路径问题是NP难的，而该问题的判定版本是NP完全的，因为它可以规约到哈密顿回路问题，此问题被证明是NP完全的。

An application of the longest path problem is the game of Chinese idiom chain, which is quite popular in traditional Chinese cultural life.  
最长路径问题的一个应用是成语接龙游戏，这在中国传统文化生活中颇为流行。

# Longest Chinese Idiom Chain 最长成语接龙

成语接龙要求前一个成语的最后一个字与相邻的后一个成语的第一个字相同，并且每个成语至多使用一次。  
Idiom chain requires that the last character of the previous idiom is the same as the first character of the next idiom, and each idiom is used at most once in the chain.

例如：e.g.  
史不绝书 -> 书不尽言 -> 言行不一 -> 一步登天 -> 天外有天 -> 天伦之乐 -> 乐不可支 -> 支支吾吾 -> 吾膝如铁 -> 铁证如山 -> 山穷水尽 -> 尽善尽美 -> 美中不足 -> 足智多谋 -> 谋事在人 -> 人定胜天 -> 天壤之别 -> 别有洞天  

把每个成语看作一个节点，在可以接龙的两个成语之间连接一个有向边，那么最长成语接龙就是求解有向图的最长有向路径。  
Consider each idiom as a node(vertex), and connect an arc(directed edge) between two idioms that can be connected. Then the longest Chinese idiom chain is to find the longest directed path in a directed graph.  

项目数据基于 [Github Data](https://github.com/crazywhalecc/idiom-database)  
原始数据 original (30895 vertices, 798200 arcs)  
四字成语 of length four (29502 vertices, 713426 arcs）  

项目源自 [Zhihu Question](https://www.zhihu.com/question/659421716/answer/3539132943)  
项目求解部分采用速度较快的 C++（chain.cpp，依赖 Json 库）  
验证部分采用 Python（validate.py）  

算法：遗传变异算法、蚁群算法、DFS 暴力搜索  
其他细节参考具体代码...  
Algorithm: Genetic Mutation Algorithm, Ant Colony Algorithm, DFS brute force.  
For more details, refer to the specific code...

# Usage 使用方法

For different operating systems  

## Linux / MacOS

Execute in terminal  

```bash
./chain.o
```

Or rebuild and run  

```bash
bash build_run.sh
```

## Windows

Rebuild and run chain.cpp using a C++ compiler or IDE say Visual Studio  

# Description of Files 各个文件说明

## Output 输出

### data/output/solution.json

output of v1

contains 2 fields:
chain - namely the longest Chinese idiom chain the program has found  
size - the length of the chain  

### data/v0/result.txt

output of v0

Output including 2 lines:  
1th line is the size of the chain  
2th line is the content of the chain  
成语接龙输出结果，包括两行：  
第一行是长度  
第二行是结果  

## Configuration 配置

### data/input/config.json

configuration of v1

explanation of some fields:
solver_naive_iter_num - iterative number of naive solver  
solver_gene_iter_num - iterative number of gene solver  
solver_gene_seeds_capacity - seeds number of gene solver  
solver_gene_recovery_ratio - recovery ratio of gene solver  
solver_gene_search_ratio - search ratio of gene solver  
solver_gene_extension_size - extension size of gene solver  
solver_gene_snippets_energy - snippet size of gene solver  

### data/v0/config.json

configuration of v0

Configuration supporting 4 modes:  
0 - original mode, including all idioms(30895 vertices)  
1 - length four mode, only including all idioms of length four(29502 vertices)  
2 - digit mode, only including all idioms related to digits(small amount of vertices)  
3 - freestyle mode, only including all idioms related to characters configured in file freestyle.json  
配置文件，支持4个模式：  
0 - 原始模式，包括所有成语（30895 个）；  
1 - 四字模式，只包括4字成语；  
2 - 数字模式，只包括包含数字的成语；  
3 - 自定义模式，成语包含的字集在freestyle.json中配置；  

For other fields, refer to the variable names and specific codes.  
其他字段参考变量名称与具体代码。  

## Validate 验证

### script/validate_v1.py

validation of v1

### script/validate_v0.py

validation of v0

Validation script to check whether result.txt is valid or not.  
验证脚本，检查result.txt是否是合法的成语接龙。

For Linux/MacOS, execute in terminal

```bash
python validate.py result.txt
```

## Specification of the Rest File of v1

### src/

source files

### obj/

objective files

### data/

all data files including input, output, cache

## Specification of the Rest Files of v0

### chain.cpp

Source code file in C++  
求解源文件

### chain.o

Execution file after compiling (Linux/MacOS)  
编译后的可执行文件

### cache.txt

Cache file that stores local results, which is large therefore is not uploaded here, but has no influence running the project, because users can generate your own cache.txt locally.  
缓存局部结果的文件，太大并未上传至此，不影响项目运行，本地可生成自己的cache.txt

### 174-result-digit.txt

One result of 2 - digit mode  
数字模式的一个运行结果

### 9132-result-four.txt

One result of 1 - length four mode  
四字模式的一个运行结果

### 9260-result-original.txt

One result of 0 - original mode  
原始模式的一个运行结果

### 9474-result-four.txt

One result of 1 - length four mode  
四字模式的一个运行结果

### 9627-result-four.txt

One result of 1 - lenght four mode  
四字模式的一个运行结果

### 9677-result-four.txt

Best result of 1 - lenght four mode  
四字模式的最好结果