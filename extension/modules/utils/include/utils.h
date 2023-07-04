#ifndef _UTILS_H_
#define _UTILS_H_

#include <node_api.h>

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
    if (status != napi_ok)                                                 \
    {                                                                      \
      const napi_extended_error_info *error_info = NULL;                   \
      status = napi_get_last_error_info((env), &error_info);               \
      bool is_pending;                                                     \
      status = napi_is_exception_pending((env), &is_pending);              \
      if (!is_pending)                                                     \
      {                                                                    \
        status = napi_throw_error((env), NULL, error_info->error_message); \
        __NAPI_CALL_ERROR_RETURN(ret);                                     \
      }                                                                    \
    }                                                                      \
  }

#define NAPI_CALL(ret, call)                                               \
  {                                                                        \
    status = (call);                                                       \
    if (status != napi_ok) {                                               \
      const napi_extended_error_info *error_info = NULL;                   \
      status = napi_get_last_error_info((env), &error_info);               \
      status = napi_throw_error((env), NULL, error_info->error_message);   \
      __NAPI_CALL_ERROR_RETURN(ret);                                       \
    }                                                                      \
  }

#define CHECK_ARGC(expected)                                               \
  if (argc < expected)                                                     \
  {                                                                        \
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
  NAPI_CALL(false,                                                             \
    napi_get_cb_info(env, cb_info, &argc, argv, &es_this, &data));             \
  if (argc < expected) {                                                       \
    NAPI_CALL(false, napi_throw_error(env, "EINVAL", "Too few arguments."));       \
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

#endif // _UTILS_H_
