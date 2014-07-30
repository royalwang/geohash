#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_geohash.h"
#include "geohash.h"

static int le_geohash;
const zend_function_entry geohash_functions[] = {
	PHP_FE(geohash_encode, NULL)
	PHP_FE(geohash_decode, NULL)
	PHP_FE(geo_neighbors, NULL)
	PHP_FE_END	
};

zend_module_entry geohash_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"geohash",
	geohash_functions,
	PHP_MINIT(geohash),
	PHP_MSHUTDOWN(geohash),
	PHP_RINIT(geohash),		
	PHP_RSHUTDOWN(geohash),
	PHP_MINFO(geohash),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_GEOHASH_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_GEOHASH
ZEND_GET_MODULE(geohash)
#endif

PHP_MINIT_FUNCTION(geohash)
{
	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(geohash)
{
	return SUCCESS;
}

PHP_RINIT_FUNCTION(geohash)
{
	return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(geohash)
{
	return SUCCESS;
}

PHP_MINFO_FUNCTION(geohash)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "geohash support", "enabled");
	php_info_print_table_end();
}
//latitude, longitude
PHP_FUNCTION(geohash_encode)
{
	char *arg = NULL;
	int  res, relen, len = 20;
	double latitude, longitude;
	char *strg;
	char geoHash[21];

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd|l", &latitude, &longitude, &len) == FAILURE) {
		return;
	}
	len = len + 1;
	if (len >20)len = 20;
	if ((res = geohash_encode(latitude, longitude, geoHash, len)) == GEOHASH_OK){
		relen = spprintf(&strg, 0, "%s", geoHash);
		RETURN_STRINGL(strg, len, 0);
		return;
	}
	else{
		return;
	}
}

PHP_FUNCTION(geohash_decode)
{
	char *getHash = NULL;
	int getHash_len, res;
	double latitude, longitude;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &getHash, &getHash_len) == FAILURE || getHash_len == 0 || getHash_len > 20) {
		return;
	}
	if ((res = geohash_decode(getHash, getHash_len, &latitude, &longitude)) == GEOHASH_OK){
		array_init(return_value);
		add_assoc_double(return_value, "latitude", latitude);
		add_assoc_double(return_value, "longitude", longitude);
		return;
	}
	else{
		return;
	}

}

PHP_FUNCTION(geo_neighbors)
{
	char *code = NULL;
	int code_len, res;
	char geoHashStr[200];
	char geoHash[21] = { '\0' };
	char codeStr[21] = { '\0' };
	int count, length;
	char *strg;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &code, &code_len) == FAILURE || code_len > 20) {
		int len = spprintf(&strg, 0, "code_len : %d", code_len);
		RETURN_STRINGL(strg, len, 0);
		return;
	}
	memcpy(codeStr, code, code_len);
	length = strlen(codeStr) + 1;
	if ((res = geo_neighbors(codeStr, geoHashStr, sizeof(geoHashStr), &count)) == GEOHASH_OK){
		int  i = 0;
		array_init(return_value);
		while (i<count)
		{
			memcpy(geoHash, geoHashStr + (i*length), length);
			add_next_index_string(return_value, geoHash, 1);
			i++;
		}
		return;
	}
	return;
}