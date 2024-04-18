#pragma once

/*
 * @breif 重启代码
 */
static const int RETCODE_RESTART = 773;

/*
 * @breif 窗口语言
 * 存储于配置文件中
 */
enum class WINDOWLANAGUAGE {
	Chinese,
	English
};
/*
 * @breif 进度条样式
 */
enum class WINDOWPROGRESSBARSTYLE {
	NORMAL,			// Qt默认样式
	BLOCK,				// 块状显示
    BORDER_RED, 		// 红色边框
    BORDER_RADIUS,		// 圆形边框
	GRADATION			// 渐变色
};
/*
 * @breif 配置文件
 */
static const std::string configDir = "config";
static const std::string configName = configDir + "/config.ini";
/*
 * @breif Label大小
 */
static const int ENGLISH_LABEL_WIDTH = 110;
static const int CHINESE_LABEL_WIDTH = 60;
/*
 * @breif 窗口显示语言，默认中文；进度条样式，默认块状
 */
static WINDOWLANAGUAGE windowLanguage = WINDOWLANAGUAGE::Chinese;
static WINDOWPROGRESSBARSTYLE progressbarstyle = WINDOWPROGRESSBARSTYLE::BLOCK;