#ifndef SD_BLOCK_DEVICE_H
#define SD_BLOCK_DEVICE_H

#include "sdiocard/sdcard.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct block_dev {
    void* _hw;
    uint32_t block_len;
    bool (*read_blocks)(struct block_dev* dev, void* destination, uint32_t block_address, uint32_t length);
    bool (*write_blocks)(struct block_dev* dev, const void* source, uint32_t block_address, uint32_t length);
    bool (*is_ready)(struct block_dev* dev);
} block_device_t;

block_device_t sd_create_block_device(sdcard_t* sdcard);

#ifdef __cplusplus
}
#endif

#endif /* SD_BLOCK_DEVICE_H */