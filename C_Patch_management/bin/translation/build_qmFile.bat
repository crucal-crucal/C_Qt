@echo off
setlocal

set ENGLISH_TS_OLD=C_Patch_management_en.ts
set CHINESE_TS_OLD=C_Patch_management_cn.ts

rem 生成 qm 文件
lrelease %ENGLISH_TS_OLD% -qm C_Patch_management_en.qm
lrelease %CHINESE_TS_OLD% -qm C_Patch_management_cn.qm