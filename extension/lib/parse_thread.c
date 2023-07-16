#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <glib.h>

#ifdef _POSIX_THREADS
  #include <pthread.h>
#else
  #error "No threading support"
#endif

#include <parse_thread.h>

static pthread_t parser_thread;
static pthread_t parser_thread_2;


static void *
parse_fn(void * data) {

  printf("Parse thread is running.\n");
  sleep(1);

  return NULL;
}

static void *
parse_fn_2(void * data) {
  gushort max = 5;

  for (gushort i = 0; i < max; i++) {
    printf("Parse thread 2 is running. %hu of %hu \n", i, max);
    sleep(1);
  }

  return NULL;
}

void
parse_thread() {
  pthread_create(&parser_thread, NULL, parse_fn, NULL);
  pthread_join(parser_thread, NULL);

  printf("Parsing done.\n");
}

int
parse_thread_2(GArray *payload) {
  int err = pthread_create(&parser_thread_2, NULL, parse_fn_2, NULL);

  if (err != 0) {
    g_error("Unable to start parse thread. %s \n", strerror(err));

    return err;
  }

  printf("Parsing 2 done.\n");

  return 0;
}
