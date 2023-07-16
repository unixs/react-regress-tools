#include <assert.h>
#include <string.h>

#include <es_parser.h>
#include <pthread_runner.h>


static void
async_native_js_call( napi_env env, napi_value js_callback, gpointer context,
  gpointer data) {

  STATUS;

  ParseThreadData_t *tsfn_data = (ParseThreadData_t *) data;

  if (env != NULL) {
    napi_value result;

    NAPI_CALL(
      napi_create_string_utf8(env, "str", NAPI_AUTO_LENGTH, &result));

    NAPI_CALL(
      napi_resolve_deferred(env, tsfn_data->deferred, result));
  }

  free_native_payload(tsfn_data->payload);
  g_free(tsfn_data);
}

static void
process_async(napi_env env, napi_value payload, napi_deferred deferred) {
  STATUS;

  // TODO: Free me
  ParseThreadData_t *data = g_new(ParseThreadData_t, 1);

  data->deferred = deferred;

  napi_value work_name;
  NAPI_CALL(
    napi_create_string_utf8(
      env,
      "Thread-safe async parser work item",
      NAPI_AUTO_LENGTH,
      &work_name
    ));

  NAPI_CALL(
    napi_create_threadsafe_function(
      env, NULL, NULL, work_name, 1, 1, NULL, NULL, NULL,
      async_native_js_call,
      &data->tsfn
    ));

  data->payload = es_to_native_payload(payload);

  gint err = parse_thread_runner(data);

  assert(napi_release_threadsafe_function(data->tsfn, napi_tsfn_release)
    == napi_ok);

  if (err != 0) {
    NAPI_CALL(
      napi_throw_error(env, NULL, strerror(err)));
  }
}

napi_value
es_pthread_parser(napi_env env, napi_callback_info cb_info) {
  PROLOG(1);

  napi_value payload = argv[0];

  napi_deferred deferred;
  napi_value promise;

  NAPI_CALL(
    napi_create_promise(env, &deferred, &promise));

  process_async(env, payload, deferred);

  return promise;
}
