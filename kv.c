#include <stdlib.h>

#include "kv.h"

kv_t *kv_init(int capacity)
{
  kv_t *kv = malloc(sizeof(kv_t));
  if (kv == NULL)
  {
    return NULL;
  }

  kv->capacity = capacity;
  kv->count = 0;
  kv->data = calloc(capacity, sizeof(kv->data));
  if (kv->data == NULL)
  {
    return NULL;
  }

  return kv;
}
