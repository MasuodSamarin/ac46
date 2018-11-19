export shell = cmd
export CPU ?= bt15

export LD=c:/JL/dv10/bin/dv10-elf-ld
export CC=c:/JL/dv10/bin/dv10-elf-gcc
export AR=c:/JL/dv10/bin/dv10-elf-ar
 
ifeq ($(CPU),bt15)
export FLAGS +=  -Wall -Os -fomit-frame-pointer -fno-delete-null-pointer-checks -c \
		-mlong-calls
endif 

ifeq ($(CPU),sh60)
export FLAGS +=  -Wall -Os -fomit-frame-pointer -fno-delete-null-pointer-checks -c 
endif 

export includes += \
-I../btstack/include \
-I../cpu/$(CPU)/include \
-I../cpu/$(CPU)/include/lmp \
-I../include \
-I../include/drv \
-I../include/vm \
-I../include/sd0 \
-I../include/os \
-I../include/tff \
-I../include/decode_mp3 \
-IC:/JL/dv10/include \


LIBS = 	\
libs/lib_cbuf.a \
libs/librtos_$(CPU).a \
libs/lib_mem_$(CPU).a \
libs/libsbcdeocode.a \
libs/libsd_$(CPU).a \
libs/libusb_$(CPU).a \
libs/lib_cache_vm_$(CPU).a \
libs/libtff.a \
libs/lib_mp3_decode.a \
libs/lib_wav_decode.a \
libs/lib_wma_decode.a \
libs/lib_audio_effect.a \
libs/lib_sydf_bt15.a \
C:/JL/dv10/lib/libc.a \
C:/JL/dv10/lib/libgcc.a \
C:/JL/dv10/lib/libgcov.a \
C:/JL/dv10/lib/libiberty.a \
C:/JL/dv10/lib/libm.a \

#libs/lib_cache_vm.a \
#libs/libdrv_lib.a \

export DEFINS = \
-DUSE_RTOS \
-DNOFLOAT \
-D_ADSP_ \
-DEMBEDDED \
-DHAVE_MALLOC \


ifeq ($(CPU),bt15)
DEFINS += -DBT15
endif

ifeq ($(CPU),sh60)
DEFINS += -DSH60
endif

ifeq ($(shell),cmd)

.PHONY:  all clean
all: 
	@if exist main.or32 del main.or32
	@for /f %%i in ('dir /ad/b') do if exist %%i\Makefile make -C %%i 
	@depend-$(CPU).bat ld $(LD) $(LIBS)

clean:
	@for /r %%i in (*.d) do del %%i 
	@for /r %%i in (*.o) do del %%i 

else


LIBS = /home/pan/tools/bfin-elf/lib/libc.a \
	/home/pan/tools/bfin-elf/lib/libgcc.a
subdir = $(shell find -maxdepth 1 -type d)
objs_o = $(shell find -name "*.o")
objs_d = $(shell find -name "*.d")
	
.PHONY:  all clean
all: 
	@-rm main.or32
	@for i in $(subdir); do \
		if [ $$i != "." ] && [ -f $$i/Makefile ]; then \
			make -j4 -C $$i; \
		fi \
	done
	@x=`find ./ -name "*.o"`; \
	$(LD) $$x  $(LIBS)  -o main.or32 -Tram.ld -Map=map.txt; \
	./post.sh
	

clean:
	-rm $(objs_o) $(objs_d)

endif
