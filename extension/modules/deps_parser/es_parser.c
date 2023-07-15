#include <assert.h>

#include <es_parser.h>
#include <parse_thread.h>

typedef struct {
  napi_async_work work;
  napi_threadsafe_function tsfn;
  napi_deferred deferred;
  napi_ref payload;
} AsyncWorkParserData_t;


typedef struct {
  napi_deferred deferred;
  napi_ref payload;
} TsfnPayload_t;


static void
async_native_js_call(napi_env env, napi_value js_callback, gpointer context, gpointer data) {
  STATUS;

  TsfnPayload_t *tsfn_data = (TsfnPayload_t *) data;

  if (env != NULL) {
    napi_value result;

    get_ref_value(env, tsfn_data->payload, &result);

    NAPI_CALL(
      napi_delete_reference(env, tsfn_data->payload));

    NAPI_CALL(
      napi_get_named_property(env, result, "str", &result));

    NAPI_CALL(
      napi_resolve_deferred(env, tsfn_data->deferred, result));
  }

  g_free(tsfn_data);
}

static void
async_work_exec(napi_env env, gpointer data) {
  AsyncWorkParserData_t *arg = (AsyncWorkParserData_t *) data;

  assert(napi_acquire_threadsafe_function(arg->tsfn)
    == napi_ok);

  // create and run real system thread
  parse_thread();

  TsfnPayload_t *tsfn_data = g_new(TsfnPayload_t, 1);

  tsfn_data->deferred = arg->deferred;
  tsfn_data->payload = arg->payload;

  assert(napi_call_threadsafe_function(
    arg->tsfn,
    (gpointer) tsfn_data,
    napi_tsfn_blocking
  ) == napi_ok);

  assert(napi_release_threadsafe_function(arg->tsfn, napi_tsfn_release)
    == napi_ok);
}

static void
async_work_complete(napi_env env, napi_status status, gpointer data) {
  AsyncWorkParserData_t *arg = (AsyncWorkParserData_t *) data;

  NAPI_CALL(
    napi_release_threadsafe_function(arg->tsfn, napi_tsfn_release));

  NAPI_CALL(
    napi_delete_async_work(env, arg->work));

  g_free(data);
}

static void
process_async(napi_env env, napi_value payload, napi_deferred deferred) {
  STATUS;

  AsyncWorkParserData_t *data = g_new(AsyncWorkParserData_t, 1);

  data->deferred = deferred;

  NAPI_CALL(
    napi_create_reference(env, payload, 1, &data->payload));

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

  NAPI_CALL(
    napi_create_async_work(env, NULL, work_name,
      async_work_exec,
      async_work_complete,
      (gpointer) data,
      &data->work
    ));

  NAPI_CALL(
    napi_queue_async_work(env, data->work));
}

napi_value
es_parser(napi_env env, napi_callback_info cb_info) {
  PROLOG(1);

  napi_value payload = argv[0];

  napi_deferred deferred;
  napi_value promise;

  NAPI_CALL(
    napi_create_promise(env, &deferred, &promise));

  process_async(env, payload, deferred);

  return promise;
}
