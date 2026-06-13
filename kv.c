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
  kv->data = malloc(sizeof(kv->data) * capacity);
  if (kv->data == NULL)
  {
    return NULL;
  }

  return kv;
}
