/////////////////////////////////////////�ļ�Ϊbat��ʽ//////////////////////////////////////////////////////////////////////////////////
REM juntham@gmail.com
REM ��������Ŀ¼�е�����C++�ļ���Astyle���д�����������
REM 2009-02-03
REM ����Astyle����λ�úͲ���

set astyle="C:\Keil\C51\AStyle\AStyle.exe"
set mode=ansi -p -w -f -j -m0  -U -S -n

REM ѭ������Ŀ¼

for /r . %%a in (*.cpp;*.c;*.h;) do %astyle% --style=%mode%  "%%a"

REM ɾ�����е�astyle������ʱ�ļ�
for /r . %%a in (*.orig) do del "%%a"

pause