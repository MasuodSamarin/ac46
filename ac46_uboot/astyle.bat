/////////////////////////////////////////文件为bat格式//////////////////////////////////////////////////////////////////////////////////
REM juntham@gmail.com
REM 批量将本目录中的所有C++文件用Astyle进行代码美化操作
REM 2009-02-03
REM 设置Astyle命令位置和参数

set astyle="C:\Keil\C51\AStyle\AStyle.exe"
set mode=ansi -p -w -f -j -m0  -U -S -n

REM 循环遍历目录

for /r . %%a in (*.cpp;*.c;*.h;) do %astyle% --style=%mode%  "%%a"

REM 删除所有的astyle生成临时文件
for /r . %%a in (*.orig) do del "%%a"

pause