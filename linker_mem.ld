/*
 * GENERATED FILE - DO NOT EDIT
 * (c) Code Red Technologies Ltd, 2008-2013
 * (c) NXP Semiconductors 2013-2017
 * Generated linker script file for LPC1549
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.23
 * LPCXpresso v8.2.2 [Build 650] [2016-09-09]  on Jan 8, 2017 11:47:36 AM
 */

MEMORY
{
  /* Define each memory region */
  MFlash256 (rx) : ORIGIN = 0x1000, LENGTH = 0x3f000 /* 256K bytes (alias Flash) minus flash memory used for uv bootloader */  
  Ram0_16 (rwx) : ORIGIN = 0x2000000, LENGTH = 0x9000 /* 16K+16K+4K bytes (alias RAM)  */  
}


  /* Define a symbol for the top of each memory region */
  __base_MFlash256 = 0x0  ; /* MFlash256 */  
  __base_Flash = 0x0 ; /* Flash */  
  __top_MFlash256 = 0x0 + 0x40000 ; /* 256K bytes */  
  __top_Flash = 0x0 + 0x40000 ; /* 256K bytes */  
  __base_Ram0_16 = 0x2000000  ; /* Ram0_16 */  
  __base_RAM = 0x2000020 ; /* RAM */  
  __top_Ram0_16 = 0x2000000 + 0x8FE0 ; /* 36K bytes */  
  __top_RAM = 0x2000000 + 0x8FE0 ; /* 16K bytes */  

  /* Define user stack location */
  __user_stack_top = __top_RAM ;
  
  