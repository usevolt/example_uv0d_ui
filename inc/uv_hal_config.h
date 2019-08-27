/*
 * uw_hal_config.h
 *
 *  Created on: Mar 22, 2016
 *      Author: usevolt
 */

#ifndef UV_HAL_CONFIG_H_
#define UV_HAL_CONFIG_H_


#include "pin_mappings.h"
#include "can_uv0d.h"

/**** USER CONFIGURATIONS ****/


// the CAN interface revision number. Will be logged to terminal with *dev* command
#define CONFIG_INTERFACE_REVISION					0


// Specifies the target op / microcontroller. Since LPC11C14 and LPC1785 are deprecated,
// only LPC1549, LINUX and WIN are supported.
#define CONFIG_TARGET_LPC11C14						0
#define CONFIG_TARGET_LPC1785						0
#define CONFIG_TARGET_LPC1549						1
#define CONFIG_TARGET_LINUX							0
#define CONFIG_TARGET_WIN							0


// non-volatile settings. Tells the uv_hal library where to find the
// main application structure which has the *data_start* and *data_end*
// variables. Some uv_hal modules have non-volatile settings which
// are stored in those variables, mainly the CANopen stack.
#define CONFIG_NON_VOLATILE_MEMORY					1
#define CONFIG_MAIN_H								"main.h"
#define CONFIG_APP_ST								struct _dev_st dev
#define CONFIG_NON_VOLATILE_START					dev.data_start
#define CONFIG_NON_VOLATILE_END						dev.data_end
// This can be used to set a callback function which is called when the
// non-volatile settings are saved. This example doesn't need to use the callback.
//#define CONFIG_SAVE_CALLBACK						save_callback



// Defines the FreeRTOS settings. Do not change!
#define CONFIG_RTOS									1
#define CONFIG_HAL_TASK_PRIORITY					30
#define CONFIG_UV_BOOTLOADER						1
// Defines the heap memory size for the RTOS. The RTOS allocates
// this amount of memory which it dynamically allocates to the tasks.
// Thus this has to be large enough so that all tasks, queues, mutexes,
// etc. that the user application needs fit into this.
#define CONFIG_RTOS_HEAP_SIZE						6000


// Uncommenting these enables the Watchdog timer to
// reset the device in case of system freezing
//#define CONFIG_WDT									1
//#define CONFIG_WDT_CYCLE_S							10


// I2C is used to communicate with the Real-time clock module on UV0D.
// Hardware related, do not change!
#define CONFIG_I2C									1
#define CONFIG_I2C_MODE								I2C_MASTER
#define CONFIG_I2C_BAUDRATE							100000

// SPI0 is used to communicate with the FT812 LCD driver on UV0D.
// Hardware related, do not change!
#define CONFIG_SPI0									1
#define CONFIG_SPI0_BAUDRATE						17000000
#define CONFIG_SPI0_MISO_PULL_UP					1
#define CONFIG_SPI0_SLAVE_COUNT						1
#define CONFIG_SPI0_MOSI_IO							P0_26
#define CONFIG_SPI0_MISO_IO							P0_27
#define CONFIG_SPI0_SCK_IO							P0_28
#define CONFIG_SPI0_SSEL0_IO						P0_24
#define CONFIG_SPI0_SSEL0_INV						0
#define CONFIG_SPI0_MSB_FIRST						1
#define CONFIG_SPI0_PREDELAY						0
#define CONFIG_SPI0_POSTDELAY						0
#define CONFIG_SPI0_FRAMEDELAY						0
#define CONFIG_SPI0_TRANSFERDELAY					0
#define CONFIG_SPI0_CLOCK_POL						0
#define CONFIG_SPI0_CLOCK_PHASE						0

// Defines the LCD panel settings for the FT812 LCD driver.
// Hardware related, do not change!
#define CONFIG_FT81X								1
#define CONFIG_FT81X_SPI_CHANNEL					SPI0
#define CONFIG_FT81X_SSEL							SPI_SLAVE0
#define CONFIG_FT81X_PD_IO							P1_7
#define CONFIG_FT81X_TYPE							FT812
#define CONFIG_FT81X_PCLK_HZ						9000000
#define CONFIG_FT81X_HCYCLE							525
#define CONFIG_FT81X_HSIZE							480
#define CONFIG_FT81X_HSYNC1							41
#define CONFIG_FT81X_HSYNC0							0
#define CONFIG_FT81X_HOFFSET						43
#define CONFIG_FT81X_VCYCLE							286
#define CONFIG_FT81X_VSIZE							272
#define CONFIG_FT81X_VSYNC1							10
#define CONFIG_FT81X_VSYNC0							0
#define CONFIG_FT81X_VOFFSET						12
#define CONFIG_FT81X_PCLK_POL						FT81X_PCLK_POL_FALLING
#define CONFIG_FT81X_CSPREAD						1
#define CONFIG_FT81X_BACKLIGHT_PWM_FREQ_HZ			10000
#define CONFIG_FT81X_BACKLIGHT_INVERT				0
#define CONFIG_FT81X_SCREEN_COLOR					C(0xFF000000)
#define CONFIG_FT81X_MEDIA_MAXSIZE					65536


// SPI1 is used to communicate with the external flash memory on UV0D.
// Hardware related, do not change!
#define CONFIG_SPI1									1
#define CONFIG_SPI1_BAUDRATE						17000000
#define CONFIG_SPI1_MISO_PULL_UP					1
#define CONFIG_SPI1_SLAVE_COUNT						1
#define CONFIG_SPI1_MOSI_IO							P0_30
#define CONFIG_SPI1_MISO_IO							P0_0
#define CONFIG_SPI1_SCK_IO							P0_31
#define CONFIG_SPI1_SSEL0_IO						P0_29
#define CONFIG_SPI1_SSEL0_INV						0
#define CONFIG_SPI1_MSB_FIRST						1
#define CONFIG_SPI1_PREDELAY						0
#define CONFIG_SPI1_POSTDELAY						0
#define CONFIG_SPI1_FRAMEDELAY						0
#define CONFIG_SPI1_TRANSFERDELAY					0
#define CONFIG_SPI1_CLOCK_POL						0
#define CONFIG_SPI1_CLOCK_PHASE						0


#define CONFIG_W25Q128								1
#define CONFIG_EXMEM_BUFFER_SIZE					128


// The user interface style settings. These can be modified
// to define the look and feel of the uv_hal ui library.
#define CONFIG_UI									1
#define CONFIG_UI_STYLES_COUNT						1
#define CONFIG_UI_STYLE_FG_C_1						C(0xFF684193)
#define CONFIG_UI_STYLE_BG_C_1						C(0xFF232428)
#define CONFIG_UI_STYLE_FONT_1						font16
#define CONFIG_UI_STYLE_WINDOW_C_1					C(0xFF151516)
#define CONFIG_UI_STYLE_TEXT_COLOR_1				C(0xFFDDDDDD)
#define CONFIG_UI_STYLE_DISPLAY_C_1					C(0xFF151516)
#define CONFIG_UI_DISABLED_OBJECT_BRIGHTNESS		-85
#define CONFIG_UI_TOUCHSCREEN						1
#define CONFIG_UI_RADIUS							2
#define CONFIG_UI_WINDOW_SCROLLBAR_WIDTH			6
#define CONFIG_UI_CLICK_THRESHOLD					30
#define CONFIG_UI_SLIDER_WIDTH						40
#define CONFIG_UI_SLIDER_INC_DEC_WIDTH				30
#define CONFIG_UI_LIST_ENTRY_HEIGHT					50
#define CONFIG_UI_TABWINDOW_HEADER_HEIGHT			30
#define CONFIG_UI_TABWINDOW_HEADER_MIN_WIDTH		70
#define CONFIG_UI_PROGRESSBAR_WIDTH					3
#define CONFIG_UI_PROGRESSBAR_SPACE					3
#define CONFIG_UI_PROGRESSBAR_HEIGHT				30
#define CONFIG_UI_TREEVIEW_ITEM_HEIGHT				40
#define CONFIG_UI_TREEVIEW_ARROW_FONT				FONT_15
#define CONFIG_UI_BUTTON_LONGPRESS_DELAY_MS			3000
#define CONFIG_UI_LISTBUTTON_BAR_HEIGHT				4

#define UI_TITLE_FONT								font25


// The PWM modules are not used on UV0D
#define CONFIG_PWM									1
#define CONFIG_PWM0									0
#define CONFIG_PWM0_FREQ							1200
#define CONFIG_PWM0_0								0
#define CONFIG_PWM0_0_IO							0
#define CONFIG_PWM0_1								0
#define CONFIG_PWM0_1_IO							0
#define CONFIG_PWM0_2								0
#define CONFIG_PWM0_2_IO							0
#define CONFIG_PWM0_3								0
#define CONFIG_PWM0_4								0
#define CONFIG_PWM0_5								0
#define CONFIG_PWM0_6								0

#define CONFIG_PWM1									0
#define CONFIG_PWM1_FREQ							CONFIG_PWM0_FREQ
#define CONFIG_PWM1_0								0
#define CONFIG_PWM1_0_IO							0
#define CONFIG_PWM1_1								0
#define CONFIG_PWM1_1_IO							0
#define CONFIG_PWM1_2								0
#define CONFIG_PWM1_2_IO							0
#define CONFIG_PWM1_3								0
#define CONFIG_PWM1_4								1
#define CONFIG_PWM1_5								1
#define CONFIG_PWM1_6								0

#define CONFIG_PWM2									0
#define CONFIG_PWM2_FREQ							CONFIG_PWM0_FREQ
#define CONFIG_PWM2_0								0
#define CONFIG_PWM2_0_IO							0
#define CONFIG_PWM2_1								0
#define CONFIG_PWM2_1_IO							0
#define CONFIG_PWM2_2								0
#define CONFIG_PWM2_2_IO							0
#define CONFIG_PWM2_3								1
#define CONFIG_PWM2_4								0

#define CONFIG_PWM3									0
#define CONFIG_PWM3_FREQ							CONFIG_PWM0_FREQ
#define CONFIG_PWM3_0								0
#define CONFIG_PWM3_0_IO							0
#define CONFIG_PWM3_1								0
#define CONFIG_PWM3_1_IO							0
#define CONFIG_PWM3_2								0
#define CONFIG_PWM3_2_IO							0
#define CONFIG_PWM3_3								0
#define CONFIG_PWM3_4								0




// The command line terminal interface for software development
#define CONFIG_TERMINAL								1
#define CONFIG_TERMINAL_BUFFER_SIZE					200
#define CONFIG_TERMINAL_ARG_COUNT					4
#define CONFIG_TERMINAL_INSTRUCTIONS				1
#define CONFIG_TERMINAL_CAN							1



// The TIMER modules on UV0D. TIMER0 is used as an hour counter
// on this example project.
#define CONFIG_TIMER0								1
#define CONFIG_TIMER1								0
#define CONFIG_TIMER2								0
#define CONFIG_TIMER3								0



// The ADC module is not used on UV0D
#define CONFIG_ADC0									0
#define CONFIG_ADC1									0
#define CONFIG_ADC_MODE								ADC_MODE_SYNC
#define CONFIG_ADC_CONVERSION_FREQ					20000

#define CONFIG_ADC_CHANNEL0_0						1
#define CONFIG_ADC_CHANNEL0_1						0
#define CONFIG_ADC_CHANNEL0_2						0
#define CONFIG_ADC_CHANNEL0_3						0
#define CONFIG_ADC_CHANNEL0_4						0
#define CONFIG_ADC_CHANNEL0_5						0
#define CONFIG_ADC_CHANNEL0_6						0
#define CONFIG_ADC_CHANNEL0_7						0
#define CONFIG_ADC_CHANNEL0_8						0
#define CONFIG_ADC_CHANNEL0_9						0
#define CONFIG_ADC_CHANNEL0_10						0
#define CONFIG_ADC_CHANNEL0_11						0
#define CONFIG_ADC_CHANNEL1_0						0
#define CONFIG_ADC_CHANNEL1_1						0
#define CONFIG_ADC_CHANNEL1_2						0
#define CONFIG_ADC_CHANNEL1_3						0
#define CONFIG_ADC_CHANNEL1_4						0
#define CONFIG_ADC_CHANNEL1_5						0
#define CONFIG_ADC_CHANNEL1_6						0
#define CONFIG_ADC_CHANNEL1_7						0
#define CONFIG_ADC_CHANNEL1_8						0
#define CONFIG_ADC_CHANNEL1_9						0
#define CONFIG_ADC_CHANNEL1_10						0
#define CONFIG_ADC_CHANNEL1_11						0




// The EEPROM memory is used for storing the LCD touchscreen calibration matrix,
// as well as the hour counter value in this example.
#define CONFIG_EEPROM								1
#define CONFIG_EEPROM_RING_BUFFER					0

// RTC should be enabled if the Real-Time clock module is used
#define CONFIG_RTC									1





// CAN bus is used for communicating with UV0D.
// Do not change!
#define CONFIG_CAN									1
#define CONFIG_CAN0									1

// The default baudrate. 250k is recommended, although other
// baudrates can also be used.
#define CONFIG_CAN0_BAUDRATE						250000
#define CONFIG_CAN0_TX_BUFFER_SIZE					16
#define CONFIG_CAN0_RX_BUFFER_SIZE					64
#define CONFIG_CAN0_TX_PIN							P0_25
#define CONFIG_CAN0_RX_PIN							P1_10

#define CONFIG_CAN_LOG								0
#define CONFIG_CAN_ERROR_LOG						1


// The CANopen stack settings. The can_uv0d.json is used
// for fetching the application values, such as object dictionary entries.
// Change only if you know what you are doing!
#define CONFIG_CANOPEN								1
#define CONFIG_CANOPEN_VENDOR_ID					CANOPEN_USEVOLT_VENDOR_ID
#define CONFIG_CANOPEN_PRODUCT_CODE					0xD
#define CONFIG_CANOPEN_REVISION_NUMBER				0
#define CONFIG_CANOPEN_LOG							0
#define CONFIG_CANOPEN_NMT_SLAVE					0
#define CONFIG_CANOPEN_NMT_MASTER					1
#define CONFIG_CANOPEN_AUTO_PREOPERATIONAL			1
#define CONFIG_CANOPEN_RXPDO_COUNT					UV0D_RXPDO_COUNT
#define CONFIG_CANOPEN_TXPDO_COUNT					UV0D_TXPDO_COUNT
#define CONFIG_CANOPEN_PDO_MAPPING_COUNT			8
#define CONFIG_CANOPEN_INITIALIZER					uv0d_canopen_init
#define CONFIG_CANOPEN_SDO_SYNC						1
#define CONFIG_CANOPEN_SDO_SEGMENTED				1
#define CONFIG_CANOPEN_SDO_BLOCK_TRANSFER			0
#define CONFIG_CANOPEN_SDO_TIMEOUT_MS				200
#define CONFIG_CANOPEN_OBJ_DICT_APP_PARAMS			obj_dict
#define CONFIG_CANOPEN_OBJ_DICT_APP_PARAMS_COUNT	obj_dict_len
#define CONFIG_CANOPEN_HEARTBEAT_PRODUCER			1
#define CONFIG_CANOPEN_HEARTBEAT_CONSUMER			0
#define CONFIG_CANOPEN_HEARTBEAT_PRODUCER_COUNT		1
#define CONFIG_CANOPEN_HEARTBEAT_PRODUCER_NODEID1	UV07_NODEID
#define CONFIG_CANOPEN_HEARTBEAT_PRODUCER_TIME1		1000
#define CONFIG_CANOPEN_CHANNEL						CAN0
#define CONFIG_CANOPEN_DEFAULT_NODE_ID				UV0D_NODEID
#define CONFIG_CANOPEN_EMCY_RX_BUFFER_SIZE			3




// The output modules are not used on UV0D
#define CONFIG_OUTPUT								0

#define CONFIG_SOLENOID_OUTPUT						0
#define CONFIG_SOLENOID_MA_P						1000
#define CONFIG_SOLENOID_MA_I						4
#define CONFIG_SOLENOID_MAX_CURRENT_DEF				2200
#define CONFIG_SOLENOID_MIN_CURRENT_DEF				200
#define CONFIG_SOLENOID_MODE_PWM					1
#define CONFIG_SOLENOID_MODE_ONOFF					1
#define CONFIG_SOLENOID_MIN_PERCENT_DEF				20
#define CONFIG_SOLENOID_MAX_PERCENT_DEF				100
#define CONFIG_SOLENOID_ONOFF_MODE_DEF				SOLENOID_OUTPUT_ONOFF_MODE_NORMAL
#define CONFIG_SOLENOID_MIN_PPT_DEF					0
#define CONFIG_SOLENOID_MAX_PPT_DEF					1000
#define CONFIG_PID									1
#define CONFIG_DUAL_SOLENOID_OUTPUT					1
#define CONFIG_DUAL_SOLENOID_ACC_DEF				100
#define CONFIG_DUAL_SOLENOID_DEC_DEF				100



#define CONFIG_HALSENSOR							0

/**** END OF USER CONFIGURATIONS ****/




#endif /* UV_HAL_CONFIG_H_ */
