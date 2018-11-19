
ifeq ($(CPU),bt15)
obj_S = \
   bt15/BINT_MUL_CORE.o \
   bt15/reg.o \
   bt15/startup.o \
 
objs = \
   bt15/os_api.o \
   bt15/irq.o \
   bt15/system_cfg_file.o \
   bt15/board/board_bt15_v0.o \
   bt15/driver/clock.o \
   bt15/driver/dac.o \
   bt15/driver/hwi.o \
   bt15/driver/mmu.o \
   bt15/driver/timer.o \
   bt15/driver/uart.o \
   bt15/driver/baseband/analog.o \
   bt15/driver/baseband/authencation.o \
   bt15/driver/baseband/bigint.o \
   bt15/driver/baseband/Bluetooth_Authentication.o \
   bt15/driver/baseband/Crypto_hash.o \
   bt15/driver/baseband/device_manager.o \
   bt15/driver/baseband/ecdh.o \
   bt15/driver/baseband/endian.o \
   bt15/driver/baseband/hci_bottom.o \
   bt15/driver/baseband/hmac.o \
   bt15/driver/baseband/inquiry_scan.o \
   bt15/driver/baseband/lbuf.o \
   bt15/driver/baseband/link_controller.o \
   bt15/driver/baseband/lmp.o \
   bt15/driver/baseband/lmp_main.o \
   bt15/driver/baseband/mdm.o \
   bt15/driver/baseband/radio.o \
   bt15/driver/baseband/sha256.o \
   bt15/driver/baseband/spi_ctl.o \
   bt15/driver/baseband/sync_word.o \
   bt15/driver/baseband/utile.o \
   bt15/driver/baseband/vsprintf.o \
   bt15/driver/baseband/role_switch_page.o \
   bt15/driver/baseband/lmp_custom.o \
   bt15/driver/baseband/test_master.o \
   bt15/driver/baseband/test_dut.o \

endif

ifeq ($(CPU),sh60)
obj_S = \
   sh60/reg.o \
   sh60/startup.o \
 
objs = \
   sh60/os_api.o \
   sh60/system_cfg_file.o \
   sh60/board/board_sh60_v0.o \
   sh60/driver/clock.o \
   sh60/driver/dac.o \
   sh60/driver/dac_api.o \
   sh60/driver/hwi.o \
   sh60/driver/timer.o \
   sh60/driver/uart.o \

endif
 
includes += \

 
 
CONFIG_LIB=n
-include ../rule.mk
 
