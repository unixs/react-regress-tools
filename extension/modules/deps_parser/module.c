#include <utils.h>
#include <es_parser.h>

MODULE_EXPORT(parser_exports, {
  STATUS;
  napi_value parser;

  NAPI_CALL(
    napi_create_function(env, NULL, NAPI_AUTO_LENGTH, es_parser, NULL, &parser));

  NAPI_CALL(
    napi_set_named_property(env, exports, "parser", parser));
})

NAPI_MODULE_INIT() {
  STATUS;

  parser_exports(env, exports);

  NAPI_CALL(
    napi_object_freeze(env, exports));

  return exports;
}
