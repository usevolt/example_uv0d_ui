#include <uv_utilities.h>
#include <uv_canopen.h>
#include "main.h"
#include "can_uv0d.h"


const uv_canopen_non_volatile_st uv0d_canopen_init = {
    .producer_heartbeat_time_ms = 400,
    .rxpdo_coms = {
        {
            .cob_id = CANOPEN_RXPDO1_ID + 0x3,
            .transmission_type = CANOPEN_PDO_TRANSMISSION_ASYNC
        },
        {
            .cob_id = CANOPEN_RXPDO2_ID + 0x3 + CANOPEN_PDO_DISABLED,
            .transmission_type = CANOPEN_PDO_TRANSMISSION_ASYNC
        }
    },
    .rxpdo_maps = {
        {
            .mappings = {
                {
                    .main_index = 0x2022,
                    .sub_index = 1,
                    .length = 1
                },
            }
        },
        {
            .mappings = {
            }
        }
    },
    .txpdo_coms = {
        {
            .cob_id = CANOPEN_TXPDO1_ID + UV0D_NODEID,
            .transmission_type = CANOPEN_PDO_TRANSMISSION_ASYNC,
            .inhibit_time = 20,
            .event_timer = 100
        }
    },
    .txpdo_maps = {
        {
            .mappings = {
                {
                    .main_index = 0x2000,
                    .sub_index = 0,
                    .length = 1
                },
                {
                    .main_index = 0x2005,
                    .sub_index = 0,
                    .length = 4
                },
                {
                    .main_index = 0x2022,
                    .sub_index = 2,
                    .length = 1
                },
            }
        }

    }
};



canopen_object_st obj_dict[] = {
    {
        .main_index = UV0D_DEV_TYPE_INDEX,
        .sub_index = UV0D_DEV_TYPE_SUBINDEX,
        .type = UV0D_DEV_TYPE_TYPE,
        .permissions = UV0D_DEV_TYPE_PERMISSIONS,
        .data_ptr = (void *) &dev.dev_type
    },
    {
        .main_index = UV0D_DEV_NAME_INDEX,
        .string_len = UV0D_DEV_NAME_STRING_LEN,
        .type = UV0D_DEV_NAME_TYPE,
        .permissions = UV0D_DEV_NAME_PERMISSIONS,
        .data_ptr = (void *) dev.dev_name
    },
    {
        .main_index = UV0D_LANG_INDEX,
        .sub_index = UV0D_LANG_SUBINDEX,
        .type = UV0D_LANG_TYPE,
        .permissions = UV0D_LANG_PERMISSIONS,
        .data_ptr = (void *) &dev.lang
    },
    {
        .main_index = UV0D_HOUR_COUNTER_INDEX,
        .sub_index = UV0D_HOUR_COUNTER_SUBINDEX,
        .type = UV0D_HOUR_COUNTER_TYPE,
        .permissions = UV0D_HOUR_COUNTER_PERMISSIONS,
        .data_ptr = (void *) &dev.hours_dh
    },
    {
        .main_index = UV0D_ARRAY_EXAMPLE_INDEX,
        .array_max_size = UV0D_ARRAY_EXAMPLE_ARRAY_MAX_SIZE,
        .type = UV0D_ARRAY_EXAMPLE_TYPE,
        .permissions = UV0D_ARRAY_EXAMPLE_PERMISSIONS,
        .data_ptr = (void *) &dev.array_example
    }
};

uint32_t obj_dict_len(void) {
    return sizeof(obj_dict) / sizeof(canopen_object_st);
}

const uint8_t uv0d_array_example_defaults[3] = {
    UV0D_ARRAY_EXAMPLE_VALUE1_DEFAULT,
    UV0D_ARRAY_EXAMPLE_VALUE2_DEFAULT,
    UV0D_ARRAY_EXAMPLE_VALUE3_DEFAULT
};

