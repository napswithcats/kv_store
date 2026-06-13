#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "kv.c"

void verify_put(kv_t *db, int i, char *key, char *val)
{
  assert(i >= 0);
  assert(i < db->capacity);
  assert(db->count == 1);
  assert(strcmp(db->entries[i].key, key) == 0);
  assert(strcmp(db->entries[i].value, val) == 0);
}

int main(void)
{
  kv_t *db = kv_init(16);
  assert(db != NULL);
  assert(db->capacity == 16);
  assert(db->count == 0);

  int i = kv_put(db, "hello", "world");
  assert(i == 0);
  assert(db->count == 1);
  assert(strcmp(db->entries[i].key, "hello") == 0);
  assert(strcmp(db->entries[i].value, "world") == 0);

  i = kv_put(db, "foo", "bar");
  assert(i == 0);
  assert(db->count == 2);
  assert(strcmp(db->entries[i].key, "foo") == 0);
  assert(strcmp(db->entries[i].value, "bar") == 0);

  kv_put(db, "yello", "world");
  kv_put(db, "hellp", "world");
  for (int i = 0; i < db->capacity; i += 1)
  {
    if (db->entries[i].key)
    {
      printf("[%d] %s: %s\n", i, db->entries[i].key, db->entries[i].value);
    }
  }
}
