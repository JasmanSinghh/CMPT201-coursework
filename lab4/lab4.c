#define _GNU_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void print_out(char *format, void *data, size_t data_size) {
  char buf[128];
  ssize_t len = snprintf(buf, sizeof buf, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data
                                                       : *(void **)data);
  write(STDOUT_FILENO, buf, len);
}

struct header {
  uint64_t size;
  struct header *next;
};

int main(void) {
  size_t space = 256;
  size_t block = 128;
  void *base = sbrk(space);
  struct header *b1 = (struct header *)base;
  struct header *b2 = (struct header *)((char *)base + block);
  b1->size = block;
  b2->size = block;
  b1->next = NULL;
  b2->next = b1;
  size_t header_size = sizeof(struct header);
  size_t data_size = block - header_size;
  char *d1 = (char *)b1 + header_size;
  char *d2 = (char *)b2 + header_size;
  memset(d1, 0x00, data_size);
  memset(d2, 0x01, data_size);

  print_out("first block:      %p\n", (void *[]){(void *)b1}, sizeof(void *));
  print_out("second block:     %p\n", (void *[]){(void *)b2}, sizeof(void *));
  print_out("first block size:   %lu\n", (uint64_t[]){b1->size},
            sizeof(uint64_t));
  print_out("first block next:  %p\n", (void *[]){(void *)b1->next},
            sizeof(void *));
  print_out("second block size: %lu\n", (uint64_t[]){b2->size},
            sizeof(uint64_t));
  print_out("second block next: %p\n", (void *[]){(void *)b2->next},
            sizeof(void *));

  const char Z[] = "0\n";
  const char O[] = "1\n";
  for (size_t i = 0; i < data_size; ++i)
    write(STDOUT_FILENO, d1[i] ? O : Z, 2);
  for (size_t i = 0; i < data_size; ++i)
    write(STDOUT_FILENO, d2[i] ? O : Z, 2);

  return 0;
}
