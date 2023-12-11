#ifndef __HTTP_SERVER_H__
#define __HTTP_SERVER_H__

#include <zephyr/kernel.h>
#include "zephyr/net/http/method.h"

struct http_server_ctx;

typedef int (*http_request_cb)(struct http_server_ctx *ctx, const uint8_t *body, int body_length);

int http_server_register_get(char* request, http_request_cb cb);
int http_server_register_post(char* request, http_request_cb cb);
int http_server_register_cb(char* request, enum http_method method, http_request_cb cb);

// int http_server_get_header_param(struct http_server_context *ctx, char* key, char* buf, size_t buf_max_len);

int http_server_send_response(struct http_server_ctx *ctx, int status_code, char* message, int message_size);

#endif