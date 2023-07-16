#include <unistd.h>

#ifdef _POSIX_THREADS
  #include <pthread.h>
#else
  #error "No threading support"
#endif


#include <utils.h>

typedef struct {
  napi_threadsafe_function tsfn;
  napi_deferred deferred;
  GArray *payload;
} ParseThreadData_t;

GArray*
es_to_native_payload(napi_value payload);

void
free_native_payload(GArray *payload);

gint
parse_thread_runner(ParseThreadData_t *data);
