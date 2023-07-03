#include <exports.h>

MODULE_EXPORT(test_exports, {
  napi_value answer;

  NAPI_CALL(env, false,
    napi_create_int64(env, 42, &answer));

  NAPI_CALL(env, false,
    napi_set_named_property(env, exports, "answer", answer));
})
