#ifndef PHP_GEOHASH_H
#define PHP_GEOHASH_H

extern zend_module_entry geohash_module_entry;
#define phpext_geohash_ptr &geohash_module_entry

#define PHP_GEOHASH_VERSION "0.1.0"

#ifdef PHP_WIN32
#	define PHP_GEOHASH_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_GEOHASH_API __attribute__ ((visibility("default")))
#else
#	define PHP_GEOHASH_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(geohash);
PHP_MSHUTDOWN_FUNCTION(geohash);
PHP_RINIT_FUNCTION(geohash);
PHP_RSHUTDOWN_FUNCTION(geohash);
PHP_MINFO_FUNCTION(geohash);


PHP_FUNCTION(geohash_encode);
PHP_FUNCTION(geohash_decode);
PHP_FUNCTION(geo_neighbors);
#ifdef ZTS
#define GEOHASH_G(v) TSRMG(geohash_globals_id, zend_geohash_globals *, v)
#else
#define GEOHASH_G(v) (geohash_globals.v)
#endif
#endif