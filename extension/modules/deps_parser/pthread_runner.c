#include <assert.h>
#include <pthread_runner.h>

static pthread_t runner_thrd;

static gpointer
runner_thrd_worker(gpointer arg) {
  ParseThreadData_t *data = (ParseThreadData_t *) arg;

  short times = 3;

  for (short i = 1; i <= times; i++) {
    sleep(1);
    g_debug("Parse thread tick: %d\n", i);
  }

  assert(napi_call_threadsafe_function(
    data->tsfn,
    (gpointer) data,
    napi_tsfn_blocking
  ) == napi_ok);

  assert(napi_release_threadsafe_function(data->tsfn, napi_tsfn_release)
    == napi_ok);

  return 0;
}

GArray*
es_to_native_payload(napi_value payload) {
  return g_array_new(FALSE, FALSE, 1); // TODO: Free me
}

void
free_native_payload(GArray* payload) {
  g_array_free(payload, TRUE);
}

gint
parse_thread_runner(ParseThreadData_t *data) {
  assert(napi_acquire_threadsafe_function(data->tsfn) == napi_ok);

  int err = pthread_create(&runner_thrd, NULL, runner_thrd_worker, data);

  if (err != 0) {
    g_error("Unable to start parse thread. %s \n", strerror(err));

    return err;
  }

  g_debug("Parse thread was runned.\n");

  return 0;
}
