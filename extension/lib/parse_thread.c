#include <stdio.h>
#include <unistd.h>
#include <glib.h>

#ifdef _POSIX_THREADS
  #include <pthread.h>
#else
  #error "No threading support"
#endif

static pthread_t parser_thread;

static void *
parse_fn(void * data) {
  printf("Parse thread is running.\n");
  sleep(3);

  return NULL;
}

void
parse_thread() {
  int res = pthread_create(&parser_thread, NULL, parse_fn, NULL);
  res = pthread_join(parser_thread, NULL);
  printf("Parsing done.\n");
}
