SET C51INC=C:\Keil\C51\INC\
SET C51LIB=C:\Keil\C51\LIB
SET CPU_TYPE=STC10F12XE
SET CPU_VENDOR=STC
SET UV2_TARGET=YS-V0.7 普通模式工程
SET CPU_XTAL=0x01518000
"C:\Keil\C51\BIN\C51.EXE" @..\obj\main.__i
"C:\Keil\C51\BIN\C51.EXE" @..\obj\LDChip.__i
"C:\Keil\C51\BIN\C51.EXE" @..\obj\Reg_RW.__i
"C:\Keil\C51\BIN\C51.EXE" @..\obj\usart.__i
"C:\Keil\C51\BIN\BL51.EXE" @..\obj\V07B.lnp
"C:\Keil\C51\BIN\OH51.EXE" "..\obj\V07B" 
