cd ac46

C:\JL\dv10\bin\dv10-elf-objcopy -O binary   -j .text   ..\main.or32 sdram.txt
C:\JL\dv10\bin\dv10-elf-objcopy -O binary   -j .data  ..\main.or32 sdram.dat
C:\JL\dv10\bin\dv10-elf-objcopy -O binary   -j .data1  ..\main.or32 sdram.dat1

copy sdram.txt/b + sdram.dat/b sdram.app
copy sdram.app/b + sdram.dat1/b sdram.app

isd_download.exe -f uboot.boot sdram.app ac46btcf.bin eq_cfg.bin AC46_1M\music.mp3 AC46_1M\radio.mp3 AC46_1M\linein.mp3 AC46_1M\wait.mp3 AC46_1M\connect.mp3 AC46_1M\disconnect.mp3 AC46_1M\ring.mp3 AC46_1M\0.mp3 AC46_1M\1.mp3 AC46_1M\2.mp3 AC46_1M\3.mp3 AC46_1M\4.mp3 AC46_1M\5.mp3 AC46_1M\6.mp3 AC46_1M\7.mp3 AC46_1M\8.mp3 AC46_1M\9.mp3 AC46_1M\pc.mp3 AC46_1M\bt.mp3 AC46_1M\conn_hid.mp3 AC46_1M\discon_hid.mp3 AC46_1M\low_power.mp3 AC46_1M\rtc.mp3 AC46_1M\record.mp3 -tonorflash -dev bt15 -div6 -updata -runaddr 0x1000000 -wait 300

del jl_ac46.bin
rename jl_isd.bin jl_ac46.bin
bfumake.exe -fi jl_ac46.bin -ld 0x0000 -rd 0x0000 -fo jl_bt46.bfu

REM del ac46_cfg.bin
REM rename jl_isd.bin ac46_cfg.bin
REM bfumake.exe -fi ac46_cfg.bin -ld 0x0000 -rd 0x0000 -fo jl_bt46.bfu

REM -updata 有这个关键字的时候不擦除配置区
REM -erase  有这个关键字的时候擦除配置区
REM C:\JL\dv10\bin\dv10-elf-objdump -D main.or32 >intermix.lit
REM main.exe -f jl_ac46.bin 1024k
