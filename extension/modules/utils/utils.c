#include <utils.h>

const char *msgTooFewArguments = "Too few arguments.";

napi_value
esUndef(napi_env env) {
  STATUS;
  napi_value esUndef;

  NAPI_CALL(napi_get_undefined(env, &esUndef));

  return esUndef;
}

napi_value
esNull(napi_env env) {
  STATUS;
  napi_value esNull;

  NAPI_CALL(napi_get_null(env, &esNull));

  return esNull;
}

napi_value
esGlobal(napi_env env) {
  STATUS;
  napi_value result;

  NAPI_CALL(
    napi_get_global(env, &result));

  return result;
}
