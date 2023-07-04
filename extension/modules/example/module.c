#include <utils.h>

MODULE_EXPORT(example_exports, {
  STATUS;
  napi_value example;

  NAPI_CALL(false,
    napi_create_int64(env, 42, &example));

  NAPI_CALL(false,
    napi_set_named_property(env, exports, "example", example));
})

NAPI_MODULE_INIT() {
  STATUS;

  example_exports(env, exports);

  NAPI_CALL(false,
    napi_object_freeze(env, exports));

  return exports;
}
