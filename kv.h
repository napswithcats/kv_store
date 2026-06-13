#ifndef KV_H
#define KV_H

typedef struct kv_t kv_t;
struct kv_t
{
  int *data;
  int capacity;
  int count;
};

kv_t *kv_init(int capacity);

#endif // kV_H
