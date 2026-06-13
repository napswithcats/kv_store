#include <stdlib.h>

#include "../inc/kv.h"

kv_t *kv_init(size_t capacity)
{
  if (capacity == 0)
  {
    return NULL;
  }

  kv_t *kv = malloc(sizeof(kv_t));
  if (kv == NULL)
  {
    return NULL;
  }

  kv->capacity = capacity;
  kv->count = 0;
  kv->entries = calloc(capacity, sizeof(*kv->entries));
  if (kv->entries == NULL)
  {
    return NULL;
  }

  return kv;
}
