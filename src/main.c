#include <assert.h>
#include <stdlib.h>

#include "kv.c"

int main(void)
{
  kv_t *db = kv_init(16);
  assert(db != NULL);
  assert(db->capacity == 16);
  assert(db->count == 0);
}
