#include <exports.h>

NAPI_MODULE_INIT() {
  test_exports(env, exports);
  // parse_exports(env, exports);

  NAPI_CALL(env, false,
    napi_object_freeze(env, exports));

  return exports;
}
