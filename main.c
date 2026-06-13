#include <assert.h>
#include <stdlib.h>

typedef struct kv_t kv_t;
struct kv_t
{
  int *data;
  int capacity;
  int count;
};

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

int main(void)
{
  kv_t *db = kv_init(16);
  assert(db != NULL);
  assert(db->capacity == 16);
  assert(db->count == 0);
}
