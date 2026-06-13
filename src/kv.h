#ifndef KV_H
#define KV_H

#include <stdlib.h>

typedef struct kv_entry_t kv_entry_t;
struct kv_entry_t
{
  char *key;
  char *value;
};

typedef struct kv_t kv_t;
struct kv_t
{
  kv_entry_t *data;
  size_t capacity;
  size_t count;
};

kv_t *kv_init(size_t capacity);

#endif // KV_H
