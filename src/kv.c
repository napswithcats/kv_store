#include <stdlib.h>
#include <string.h>

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

static size_t hash(char *val, size_t cap)
{
  size_t hash = 0x13371337deadbeef;
  while (*val)
  {
    hash ^= *val;
    hash = hash << 8;
    hash += *val;
    val += 1;
  }

  return hash % cap;
}

int kv_put(kv_t *db, char *key, char *value)
{
  if (db == NULL || key == NULL || value == NULL)
  {
    return -1;
  }

  size_t h = hash((char *)key, db->capacity);

  for (int i = 0; i < db->capacity - 1; i += 1)
  {
    size_t index = (h + i) % db->capacity;
    kv_entry_t *entry = &db->entries[index];

    if (entry->key && entry->key != TOMBSTONE && strcmp(entry->key, key) == 0)
    {
      char *newval = strdup(value);
      if (!newval)
      {
        free(newval);
        return -1;
      }
      entry->value = newval;
      return 0;
    }

    if (entry->key == NULL || entry->key == TOMBSTONE)
    {
      char *newkey = strdup(key);
      char *newval = strdup(value);
      if (!newkey || !newval)
      {
        free(newkey);
        free(newval);
        return -1;
      }
      entry->key = newkey;
      entry->value = newval;
      db->count += 1;
      return 0;
    }
  }

  return -2;
}

char *kv_get(kv_t *db, char *key)
{
  if (db == NULL || key == NULL)
  {
    return NULL;
  }

  size_t h = hash(key, db->capacity);

  for (int i = 0; i < db->capacity - 1; i += 1)
  {
    size_t index = (h + i) % db->capacity;
    kv_entry_t *entry = &db->entries[index];
    if (entry->key == NULL)
    {
      break;
    }
    if (entry->key != TOMBSTONE && strcmp(entry->key, key) == 0)
    {
      return entry->value;
    }
  }

  return NULL;
}

int kv_delete(kv_t *db, char *key)
{
  if (db == NULL || key == NULL)
  {
    return -1;
  }

  size_t h = hash(key, db->capacity);

  for (int i = 0; i < db->capacity - 1; i += 1)
  {
    size_t index = (h + i) % db->capacity;
    kv_entry_t *entry = &db->entries[index];
    if (entry->key == NULL)
    {
      break;
    }
    if (entry->key != TOMBSTONE && strcmp(entry->key, key) == 0)
    {
      free(entry->key);
      free(entry->value);
      entry->key = TOMBSTONE;
      entry->value = NULL;
      return 0;
    }
  }

  return -1;
}
