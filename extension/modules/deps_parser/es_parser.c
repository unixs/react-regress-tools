#include <stdio.h>
#include <assert.h>

#include <es_parser.h>
#include <parse_thread.h>

static napi_async_work work;
static napi_threadsafe_function tsfn;
static napi_value work_name;

static void
async_native_js_call(napi_env env, napi_value js_callback, void* context, void* data) {
  STATUS;

  napi_deferred derferred = (napi_deferred) data;
  napi_value result;

  NAPI_CALL(false,
    napi_create_string_utf8(
      env,
      "test",
      NAPI_AUTO_LENGTH,
      &result
    ));

  NAPI_CALL(false,
    napi_resolve_deferred(env, derferred, result));
}

static void
async_work_exec(napi_env env, void *data) {
  napi_deferred deferred = (napi_deferred) data;

  printf("Work executed. \n");

  printf("Run thread.\n");

  // call pthread
  parse_thread();

  printf("Thread completed.\n");

  printf("Acquire.\n");

  assert(napi_acquire_threadsafe_function(tsfn) == napi_ok);

  printf("Call.\n");

  assert(napi_call_threadsafe_function(tsfn, deferred, napi_tsfn_blocking) == napi_ok);

  printf("Release.\n");

  assert(napi_release_threadsafe_function(tsfn, napi_tsfn_release) == napi_ok);
}

static void
async_work_complete(napi_env env, napi_status status, void *data) {
  NAPI_CALL(false,
    napi_release_threadsafe_function(tsfn, napi_tsfn_release));

  NAPI_CALL(false,
    napi_delete_async_work(env, work));

  printf("Work completed. \n");
}

static void
process_async(napi_env env, napi_deferred deferred) {
  STATUS;

  NAPI_CALL(false,
    napi_create_string_utf8(
      env,
      "Thread-safe AsyncParser Work Item",
      NAPI_AUTO_LENGTH,
      &work_name
    ));

  NAPI_CALL(false,
    napi_create_threadsafe_function(
      env, NULL, NULL, work_name, 1, 1, NULL, NULL, NULL,
      async_native_js_call,
      &tsfn
    ));

  NAPI_CALL(false,
    napi_create_async_work(env, NULL, work_name,
      async_work_exec,
      async_work_complete,
      (void *) deferred, // data
      &work
    ));

  NAPI_CALL(false,
    napi_queue_async_work(env, work));
}

napi_value
es_parser(napi_env env, napi_callback_info cb_info) {
  PROLOG(1);

  napi_value str = argv[0];

  napi_deferred deferred;
  napi_value promise;

  NAPI_CALL(false,
    napi_create_promise(env, &deferred, &promise));

  process_async(env, deferred);

  return promise;
}
