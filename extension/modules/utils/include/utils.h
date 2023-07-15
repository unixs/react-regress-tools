#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdlib.h>
#include <node_api.h>
#include <glib.h>

#define DEF_METHOD(name, func) { \
    name,                   \
    NULL,                   \
    func,                   \
    NULL,                   \
    NULL,                   \
    NULL,                   \
    napi_default,           \
    NULL                    \
  }

#define DEF_METHOD_V_WITH_DATA(name, func, data) { \
    NULL,                   \
    name,                   \
    func,                   \
    NULL,                   \
    NULL,                   \
    NULL,                   \
    napi_default,           \
    data                    \
  }

#define DEF_METHOD_WITH_DATA(name, func, data) { \
    name,                   \
    NULL,                   \
    func,                   \
    NULL,                   \
    NULL,                   \
    NULL,                   \
    napi_default,           \
    data                    \
  }

#define DEF_PROP(name, cb) { \
    name,                   \
    NULL,                   \
    NULL,                   \
    cb,                     \
    NULL,                   \
    NULL,                   \
    napi_default,           \
    NULL                    \
  }

#define MODULE_EXPORT(fun, block)           \
static void                                 \
fun(napi_env env, napi_value exports) block

#define KEY "key"
#define VALUE "value"

#define __NAPI_CALL_ERROR_RETURN(flag) __NAPI_CALL_ERROR_RETURN_##flag
#define __NAPI_CALL_ERROR_RETURN_1 return NULL
#define __NAPI_CALL_ERROR_RETURN_0
#define __NAPI_CALL_ERROR_RETURN_2 return
#define VOID_ON_FAIL 2

#define NAPI_CALL_OUT(ret, call)                                           \
  {                                                                        \
    status = (call);                                                       \
    if (status != napi_ok) {                                               \
      const napi_extended_error_info *error_info = NULL;                   \
      napi_value st = napi_get_last_error_info((env), &error_info);        \
      bool is_pending;                                                     \
      st = napi_is_exception_pending((env), &is_pending);                  \
      if (!is_pending) {                                                   \
        st = napi_throw_error((env), NULL, error_info->error_message);     \
      }                                                                    \
    }                                                                      \
  }

#define NAPI_CALL_DEBUG(call)                                                  \
  {                                                                            \
    status = (call);                                                           \
    g_debug("NAPI_CALL: %s => %s => %d", __FUNCTION__, #call, status);         \
    if (status != napi_ok) {                                                   \
      napi_status call_status = status;                                        \
      g_debug("\t!NAPI_CALL_FAILED in %s: %s", __FUNCTION__, #call);           \
      const napi_extended_error_info *error_info = NULL;                       \
      status = napi_get_last_error_info((env), &error_info);                   \
      g_debug("\t!NAPI_GET_ERROR_INFO: %s => %d",                              \
              "napi_get_last_error_info((env), &error_info)", status);         \
      g_debug("\t!NAPI_ERROR_CODE: %d, MSG: %s",                               \
              error_info->engine_error_code, error_info->error_message);       \
      status = napi_throw_error((env), NULL, error_info->error_message);       \
      g_debug("\t!NAPI_THROW_ERROR: %s => %d",                                 \
              "napi_throw_error((env), NULL, error_info->error_message)",      \
              status);                                                         \
      status = call_status;                                                    \
    }                                                                          \
  }

#define NAPI_CALL(call)                                                        \
  {                                                                            \
    status = (call);                                                           \
    if (status != napi_ok) {                                                   \
      napi_status call_status = status;                                        \
      g_debug("\t!NAPI_CALL_FAILED in %s: %s", __FUNCTION__, #call);           \
      const napi_extended_error_info *error_info = NULL;                       \
      status = napi_get_last_error_info((env), &error_info);                   \
      g_debug("\t!NAPI_ERROR_CODE: %d, MSG: %s",                               \
              error_info->engine_error_code, error_info->error_message);       \
      status = napi_throw_error((env), NULL, error_info->error_message);       \
      status = call_status;                                                    \
    }                                                                          \
  }

#ifdef DEBUG_BUILD
  #undef NAPI_CALL
  #define NAPI_CALL(call) NAPI_CALL_DEBUG(call)
#endif

#define CHECK_ARGC(expected)                                               \
  if (argc < expected) {                                                   \
    NAPI_CALL(env, false,                                                  \
      napi_throw_error(env, NULL, "Too few arguments."));                  \
    return NULL;                                                           \
  }

#define STATUS register napi_status status

#define PROLOG(expected)                                                       \
  STATUS;                                                                      \
  size_t argc = expected;                                                      \
  napi_value es_this, argv[argc];                                              \
  void *data = NULL;                                                           \
  NAPI_CALL(                                                                   \
    napi_get_cb_info(env, cb_info, &argc, argv, &es_this, &data));             \
  if (argc < expected) {                                                       \
    NAPI_CALL(napi_throw_error(env, "EINVAL", "Too few arguments."));          \
    return NULL;                                                               \
  }

/**
 * Get globas ES Symbol
 */
#define NAPI_GLOBAL_SYM(env, name, napiVar)                                         \
  {                                                                                 \
    napi_value global, Symbol;                                                      \
    NAPI_CALL(env, false, napi_get_global(env, &global));                           \
    NAPI_CALL(env, false, napi_get_named_property(env, global, "Symbol", &Symbol)); \
    NAPI_CALL(env, false, napi_get_named_property(env, Symbol, name, &napiVar));    \
  }



// Functions

napi_value
esUndef(napi_env env);

napi_value
esNull(napi_env env);

napi_value
esGlobal(napi_env env);

static inline bool
get_ref_value(napi_env env, napi_ref ref, napi_value *value) {
  STATUS;

  NAPI_CALL(
    napi_get_reference_value(env, ref, value));

  if (*value == NULL) {
    return false;
  }

  return true;
}

#endif // _UTILS_H_
