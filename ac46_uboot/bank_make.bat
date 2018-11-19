@echo off
SETLOCAL EnableDelayedExpansion
set ldfile=bank.ld

rem FOR /F "eol=; tokens=1,2 delims=:" %%i in (bank.cfg) do if %%i==bankNums set bankNums=%%j

FOR /F "eol=; tokens=1,2* delims=:- " %%i in (bank.cfg) do (
    if %%i==comm_rang (
        set comm_origin=%%j
        set comm_length=%%k
    )
    if %%i==banka_rang (
        set banka_origin=%%j
        set banka_length=%%k
    )
    if %%i==bankb_rang (
        set bankb_origin=%%j
        set bankb_length=%%k
    )
    if %%i==bankc_rang (
        set bankc_origin=%%j
        set bankc_length=%%k
    )
    if %%i==banka_banks (
        set banka_begin=%%j
        set banka_end=%%k
    )
    if %%i==bankb_banks (
        set bankb_begin=%%j
        set bankb_end=%%k
    )
    if %%i==bankc_banks (
        set bankc_begin=%%j
        set bankc_end=%%k
    )
)

if exist %ldfile%  del %ldfile%


echo MEMORY >>%ldfile%
echo { >>%ldfile%
echo     comm : ORIGIN = 0x%comm_origin%, LENGTH = 0x%comm_length% >> %ldfile%


for /L %%i in (%banka_begin%,1,%banka_end%) do (
    set /a b=0x%banka_origin%
    set /a banka_addr = %%i "<<" 18 "|" !b!
    echo     bank%%i : ORIGIN = !banka_addr!, LENGTH = 0x%banka_length% >> %ldfile%
)
for /L %%i in (%bankb_begin%,1,%bankb_end%) do (
    set /a b=0x%bankb_origin%
    set /a bankb_addr = %%i "<<" 18 "|" !b!
    echo     bank%%i : ORIGIN = !bankb_addr!, LENGTH = 0x%bankb_length% >> %ldfile%
)
for /L %%i in (%bankc_begin%,1,%bankc_end%) do (
    set /a b=0x%bankc_origin%
    set /a bankc_addr = %%i "<<" 18 "|" !b!
    echo     bank%%i : ORIGIN = !bankc_addr!, LENGTH = 0x%bankc_length% >> %ldfile%
)

echo } >>%ldfile%


echo. >>%ldfile%

echo SECTIONS >>%ldfile%
echo { >>%ldfile%

set bankNums = %banka_end%
if %banka_end% LSS %bankb_end% set bankNums=%bankb_end%
if %bankNums% LSS %bankc_end% set bankNums=%bankc_end%

for /L %%i in (1,1,%bankNums%) do (
    echo     .bank%%i : >>%ldfile%
    echo     { >>%ldfile%
    echo         *(.bank%%i^) >> %ldfile%

    FOR /F "eol=; tokens=1,2,3 delims= " %%j in (bank.cfg) do (
        if %%j==bank%%i: (
            if %%l==^(*.text^) echo         %%k%%l >>%ldfile%
        )
    )

    echo         *(bank%%i_ram^) >>%ldfile%

    FOR /F "eol=; tokens=1,2,3* delims=: " %%j in (bank.cfg) do (
        if %%j==bank%%i (
            if %%l==^(*.rodata*^) echo         %%k%%l >>%ldfile%
            if %%m==^(*.rodata*^) echo         %%k%%m >>%ldfile%
        )
    )


    echo     } ^> bank%%i >>%ldfile%
    echo. >>%ldfile%
)

echo     .text : >>%ldfile%
echo     { >>%ldfile%
echo        *(.start) >>%ldfile%
echo        *(.text) >>%ldfile%
FOR /F "eol=; tokens=1,2* delims=: " %%i in (bank.cfg) do if %%i==comm_secs echo        *(%%j) >>%ldfile%
echo        *(.rodata*) >>%ldfile%
echo        *(.comm_rodata) >>%ldfile%
echo      } ^> comm >>%ldfile%

echo. >>%ldfile%
echo } >>%ldfile%






