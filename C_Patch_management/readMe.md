CMake + MSVC构建，补丁合并小工具，将指定目录下的所有文件抛去父目录全部复制到固定目录下，通过更新页面可修改复制后的路径

在Release模式下使用重定向日志输出需要添加宏QT_MESSAGELOGCONTEXT在顶层文件中

例：add_definitions(-DQT_MESSAGELOGCONTEXT)

使用多线程复制加快速度，查看可执行程序下的user.log文件可知是否完全复制成功，如若失败，可调节线程数再次尝试。

CLion编辑器内无法重启程序，原因未知，install后重启正常

在编辑器中完整运行且有翻译+样式需要将bin目录中的所有文件拷贝到可秩序程序目录的上一级目录中

目前 Ubuntu 22.04.3&Windows 运行正常，在 Ubuntu 23.10 版本中点击打开会出现两个选择目录窗口