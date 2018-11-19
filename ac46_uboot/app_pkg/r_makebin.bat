@echo off
SETLOCAL EnableDelayedExpansion

set addfile=add.t
set secfile=sec.t
set bankfile=bank_link.bat

FOR /F "eol=# tokens=1,2 delims=:" %%i in (drv.cfg) do (
    if %%i==out_file (
        set headfile=%%j
        goto find_file_over
    )
)
:find_file_over

echo #ifndef DRV_HEAD_H >%headfile%
echo #define DRV_HEAD_H >>%headfile%
echo. >>%headfile%

FOR /F "eol=# tokens=1,2 delims=:" %%i in (bank.cfg) do (
    if %%i==bank_num (
        set /a bankNums=%%j
        goto find_bank_num_over
    )
)
:find_bank_num_over

for /F "eol=# tokens=1,2* delims=:- " %%i in (bank.cfg) do (
    if %%i==out_file set output_file=%%j
    if %%i==comm_rang set comm_org=%%j
	if %%i==bank_rang (
		set bank_org=%%j
		set bank_len=0x%%j
		set /a bank_len += 0x%%k
	)
)


dv10-elf-objcopy.exe -O binary -j .start -j .text -j .data main.or32 bank0.bin


for /L %%i in (1,1,%bankNums%) do dv10-elf-objcopy.exe -O binary -j .bank%%i  main.or32 bank%%i.bin

set /p = .\app_pkg\CD03_Bank_Link.exe -boot 0x%comm_org% < nul >%bankfile%
set /p = -bank 0x%bank_org%-%bank_len% 1-%bankNums% < nul >>%bankfile%


set /a bank_nums=0
set /a drv_bank_num =%bankNums%

if not exist %addfile% goto run_bank_link

FOR /F "eol=# tokens=1,2,* delims=: " %%i in (%addfile%) do (
    FOR /F "eol=# tokens=1,2 delims=: " %%m in (%secfile%) do (
        if %%i == %%m (
            set /a bank_nums = !bank_nums!+1
            set /a drv_bank_num = !drv_bank_num!+1
            dv10-elf-objcopy.exe -O binary -j .%%n  main.or32 bank!drv_bank_num!.bin
            echo #define drv_%%n  !drv_bank_num! >>%headfile%
        )
    )
    set /a bank_beg = !drv_bank_num! - !bank_nums! + 1
    set /p = -bank %%j-%%k !bank_beg!-!drv_bank_num! < nul >>%bankfile%
    set /a bank_nums=0
)

:run_bank_link
set /p = -infile bank.bin -outfile %output_file% <nul >>%bankfile%

echo. >>%headfile%
echo #endif >>%headfile%
echo. >>%headfile%

call %bankfile%


@echo off
for /L %%i in (0,1,%drv_bank_num%) do if exist bank%%i.bin del bank%%i.bin

::del %addfile% %secfile% %bankfile%

@echo on
copy /y .\app_pkg\uboot.boot ..\apps\ac46



