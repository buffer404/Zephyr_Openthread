//
// Created by mkolchurin on 01.08.23.
//

#ifndef _LMT_SETTINGS_H
#define _LMT_SETTINGS_H

#include <stddef.h>

int lmt_settings_save_key_value(char* key, void* value, size_t value_len);

int lmt_settings_get_key_value(char *key, void *value, size_t value_len);

#endif //_LMT_SETTINGS_H
