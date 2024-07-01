@echo off
setlocal

set ENGLISH_TS_OLD=C_testffmpeg_cn.ts
set CHINESE_TS_OLD=C_testffmpeg_en.ts

rem 生成 qm 文件
lrelease %ENGLISH_TS_OLD% -qm C_testffmpeg_en.qm
lrelease %CHINESE_TS_OLD% -qm C_testffmpeg_cn.qm