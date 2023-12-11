//
// Created by mkolchurin on 01.08.23.
//
//#include "device_settings.h"
#include "zephyr/init.h"
#include "zephyr/settings/settings.h"
#include <zephyr/lmt/settings.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(lmt_settings);



#ifdef CONFIG_LMT_SETTINGS_MOUNT_FS
#include <zephyr/device.h>
#include <zephyr/fs/fs.h>
#include <zephyr/fs/littlefs.h>

#define SETTINGS_PARTITION_LABEL settings_partition
#define SETTINGS_PARTITION_ID FIXED_PARTITION_ID(SETTINGS_PARTITION_LABEL)
FS_LITTLEFS_DECLARE_DEFAULT_CONFIG(cstorage);
static struct fs_mount_t littlefs_mnt = {
        .type = FS_LITTLEFS,
        .fs_data = &cstorage,
        .storage_dev = (void*)SETTINGS_PARTITION_ID,
        .mnt_point = "/lfs"
};
#endif

struct direct_immediate_value {
    size_t len;
    void* dest;
    uint8_t fetched;
};

static int direct_loader_immediate_value(const char* name, size_t len,
                                         settings_read_cb read_cb, void* cb_arg,
                                         void* param)
{
    const char* next;
    size_t name_len;
    int rc;
    struct direct_immediate_value* one_value = (struct direct_immediate_value*)param;
    name_len = settings_name_next(name, &next);
    if (name_len == 0) {
        if (len == one_value->len) {
            rc = read_cb(cb_arg, one_value->dest, len);
            if (rc < 0) {
                return rc;
            }
            one_value->fetched = 1;
            return 0;
        }
        return -EINVAL;
    }
    return 0;
}

int load_immediate_value(const char* name, void* dest, size_t len)
{
    int rc;
    struct direct_immediate_value dov;

    dov.fetched = 0;
    dov.len = len;
    dov.dest = dest;

    rc = settings_load_subtree_direct(name, direct_loader_immediate_value,
                                      (void*)&dov);
    if (rc == 0) {
        if (!dov.fetched) {
            rc = -ENOENT;
        }
    }

    return rc;
}


int lmt_settings_save_key_value(char* key, void* value, size_t value_len){
    return settings_save_one(key, value, value_len);
}

int lmt_settings_get_key_value(char *key, void *value, size_t value_len){
    return load_immediate_value(key, value, value_len);
}

static void init_lmt_settings_subsys(){
#ifdef CONFIG_LMT_SETTINGS_MOUNT_FS
    int rc = fs_mount(&littlefs_mnt);
    if (rc < 0) {
        LOG_ERR("Error mounting littlefs [%d]", rc);
    }
    static struct fs_file_t file;
    fs_file_t_init(&file);
    fs_open(&file, CONFIG_SETTINGS_FILE_PATH, FS_O_CREATE);
    fs_close(&file);
#endif

    int ret = settings_subsys_init();
    if (ret) {
        LOG_ERR("settings subsys initialization: fail (err %d)", ret);
        return;
    }
}



SYS_INIT(init_lmt_settings_subsys, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
