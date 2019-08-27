


/// @file: UVCAN generated header file describing the object dictionary
/// of this device. DO NOT EDIT DIRECTLY

#ifndef can_uv0d
#define can_uv0d

#include <stdint.h>
#include <string.h>

#define UV0D_NODEID           0xd



#define UV0D_VENDOR_ID    0x49b


#define UV0D_PRODUCT_CODE    0x0


#define UV0D_REVISION_NUMBER    0x0


enum {
    UV0D_EMCY_GENERAL_EMCY_MSG =            0,
    UV0D_EMCY_COUNT =            1
};



#define UV0D_DEV_NAME_LEN            32

enum {
    UV0D_LANG_EN = 0,
    UV0D_LANG_FI,
    UV0D_LANG_COUNT
};
typedef uint8_t uv0d_lang_e;





#define UV0D_RXPDO_COUNT            2
#define UV0D_TXPDO_COUNT            1


#define UV0D_DEV_TYPE_INDEX           0x2000
#define UV0D_DEV_TYPE_SUBINDEX            0
#define UV0D_DEV_TYPE_TYPE            CANOPEN_UNSIGNED8
#define UV0D_DEV_TYPE_PERMISSIONS            CANOPEN_RO
#define UV0D_DEV_TYPE_VALUE            13
#define UV0D_DEV_TYPE_DEFAULT            13
#define UV0D_DEV_TYPE_MIN            13
#define UV0D_DEV_TYPE_MAX            13


#define UV0D_DEV_NAME_INDEX           0x2001
#define UV0D_DEV_NAME_STRING_LEN            32
#define UV0D_DEV_NAME_TYPE            CANOPEN_STRING
#define UV0D_DEV_NAME_PERMISSIONS            CANOPEN_RW


#define UV0D_LANG_INDEX           0x2002
#define UV0D_LANG_SUBINDEX            0
#define UV0D_LANG_TYPE            CANOPEN_UNSIGNED8
#define UV0D_LANG_PERMISSIONS            CANOPEN_RW
#define UV0D_LANG_VALUE            0
#define UV0D_LANG_DEFAULT            0
#define UV0D_LANG_MIN            0
#define UV0D_LANG_MAX            1


#define UV0D_HOUR_COUNTER_INDEX           0x2005
#define UV0D_HOUR_COUNTER_SUBINDEX            0
#define UV0D_HOUR_COUNTER_TYPE            CANOPEN_UNSIGNED32
#define UV0D_HOUR_COUNTER_PERMISSIONS            CANOPEN_RO
#define UV0D_HOUR_COUNTER_VALUE            0
#define UV0D_HOUR_COUNTER_DEFAULT            0
#define UV0D_HOUR_COUNTER_MIN            0
#define UV0D_HOUR_COUNTER_MAX            -1


#define UV0D_ARRAY_EXAMPLE_INDEX           0x2022
#define UV0D_ARRAY_EXAMPLE_ARRAY_MAX_SIZE            3
#define UV0D_ARRAY_EXAMPLE_TYPE            CANOPEN_ARRAY8
#define UV0D_ARRAY_EXAMPLE_PERMISSIONS            CANOPEN_RW
#define UV0D_ARRAY_EXAMPLE_VALUE1_SUBINDEX            1
#define UV0D_ARRAY_EXAMPLE_VALUE1_MIN            0
#define UV0D_ARRAY_EXAMPLE_VALUE1_MAX            127
#define UV0D_ARRAY_EXAMPLE_VALUE1_DEFAULT            0
#define UV0D_ARRAY_EXAMPLE_VALUE2_SUBINDEX            2
#define UV0D_ARRAY_EXAMPLE_VALUE2_MIN            0
#define UV0D_ARRAY_EXAMPLE_VALUE2_MAX            127
#define UV0D_ARRAY_EXAMPLE_VALUE2_DEFAULT            0
#define UV0D_ARRAY_EXAMPLE_VALUE3_SUBINDEX            3
#define UV0D_ARRAY_EXAMPLE_VALUE3_MIN            0
#define UV0D_ARRAY_EXAMPLE_VALUE3_MAX            127
#define UV0D_ARRAY_EXAMPLE_VALUE3_DEFAULT            0
extern const uint8_t uv0d_array_example_defaults[3];



/// @brief: returns the length of object dictionary in objects.
uint32_t obj_dict_len(void);

#endif