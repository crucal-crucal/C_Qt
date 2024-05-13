#pragma once

/*
 * @note: 导出宏定义
 * 在Windows平台下，动态库中的符号默认情况下是不可见的，这意味着在编译动态库时，其内部的函数和类不会被自动导出到外部使用的程序中。这样做的目的是为了避免动态库中的内部实现细节被外部程序访问到，
 * 从而提高了程序的封装性和安全性。为了让其他程序能够使用动态库中的函数和类，需要在导出时显示地使用__declspec(dllexport)来指定符号的可见性。
 * 而在Linux平台下，默认情况下符号是可见的，这种默认情况是由链接器决定的。
 * Linux系统采用的是一种"就近原则"来解析符号，即在链接时会优先选择最先找到的符号。因此，如果在同一程序或者库中存在多个同名的符号，默认情况下，链接器会选择最先找到的符号，这些符号都是可见的。
 * 这样设计简化了程序的开发和链接过程，并符合了Unix/Linux系统的设计哲学。
 */
#if defined(_MSC_VER) || defined(_WIN32) || defined(_WIN64)
#ifdef LOGGER_REDIRECTION_LIB
#define LOGGER_REDIRECTION_EXPORT Q_DECL_EXPORT
#else
#define LOGGER_REDIRECTION_EXPORT Q_DECL_IMPORT
#endif
#elif defined(__unix__)
#define LOGGER_REDIRECTION_EXPORT
#endif

/*
 * @breif 日志文件名称
 */
constexpr static auto logDirectory = "log";
/*
 * @breif 单个log文件最大值
 */
constexpr static auto LOG_MAXSIZE = 5 * 1024 * 1024;
