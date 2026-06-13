#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "kv.c"

int main(void)
{
  kv_t *db = kv_init(16);
  assert(db != NULL);
  assert(db->capacity == 16);
  assert(db->count == 0);

  int i = kv_put(db, "hello", "world");
  assert(i == 0);
  assert(db->count == 1);

  i = kv_put(db, "foo", "bar");
  assert(i == 0);
  assert(db->count == 2);

  kv_put(db, "yello", "world");
  kv_put(db, "hellp", "world");
  for (int i = 0; i < db->capacity; i += 1)
  {
    if (db->entries[i].key)
    {
      printf("[%d] %s: %s\n", i, db->entries[i].key, db->entries[i].value);
    }
  }

  char *val = 0;
  val = kv_get(db, "hello");
  assert(val != NULL);
  assert(strcmp(val, "world") == 0);

  val = kv_get(db, "yello");
  assert(val != NULL);
  assert(strcmp(val, "world") == 0);

  val = kv_get(db, "foo");
  assert(val != NULL);
  assert(strcmp(val, "bar") == 0);

  val = kv_get(db, "none");
  assert(val == NULL);

  int rv = kv_delete(db, "none");
  assert(rv == -1);

  rv = kv_delete(db, "hello");
  assert(rv == 0);
  val = kv_get(db, "hello");
  assert(val == NULL);
}
