#include <utils.h>
#include <es_parser.h>

static const char* mod_exports[] = { NAPI_MODULE_C_EXPORTS };


MODULE_EXPORT(parser_exports, {
  STATUS;
  napi_value parser;
  napi_value pthread_parser;

  // parser
  NAPI_CALL(
    napi_create_function(env, NULL, NAPI_AUTO_LENGTH, es_parser, NULL, &parser));

  NAPI_CALL(
    napi_set_named_property(env, exports, "parser", parser));

  // pthread_parser
  NAPI_CALL(
    napi_create_function(env, NULL, NAPI_AUTO_LENGTH, es_pthread_parser, NULL, &pthread_parser));

  NAPI_CALL(
    napi_set_named_property(env, exports, "pthread_parser", pthread_parser));
})

NAPI_MODULE_INIT() {
  STATUS;

  parser_exports(env, exports);

  NAPI_CALL(
    napi_object_freeze(env, exports));

  return exports;
}
