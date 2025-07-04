# 📌 项目简介：
- 项目名称：学生记录管理系统  
- 开发语言：C++  
- 开发工具：Microsoft Visual Studio 2022
- 本项目使用「二元搜寻树（Binary Search Tree, BST）」来储存和管理学生记录。透过 BST 的结构，能够更快速地新增、搜寻学生资料，提高程序的运行效率。<br/><br/>

# 🎯 项目功能：
1. **从文字档案读取学生记录**
   - 使用 `readFile(const char *filename, BST *t1)` 函数将学生资料从文字档案中读取并储存到 BST 里。

2. **使用 BST 储存学生记录**
   - 每一笔学生资料都会根据特定的关键字段（例如学生编号）被插入 BST 中，确保资料按顺序管理。

3. **搜寻特定学生资料**
   - 程式提供搜寻功能，能根据用户输入的学生编号，在 BST 中寻找对应的记录。<br/><br/>

# 🧪 编译与测试方式：
1. 使用 Visual Studio 2022 打开项目。
2. 确保所有源代码（.cpp 和 .h 文件）已正确加入项目。
3. 编译项目（Build Solution）。
4. 执行程序（Start Without Debugging），测试各项功能。<br/><br/>

# 二叉搜索树的一个例子
![image alt](https://github.com/vinsyenloh/Data-Structure2-cpp/blob/3c629fa398de3d949f2b50e05721dad1941de7cb/Example%20of%20BST.jpg)  <br/><br/>

# Tree 1 & Tree 2
![image alt](https://github.com/vinsyenloh/Data-Structure2-cpp/blob/3c629fa398de3d949f2b50e05721dad1941de7cb/Tree1%20%26%20Tree2.jpg)  
