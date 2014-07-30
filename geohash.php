<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('geohash')) {
	dl('php_geotest.' . PHP_SHLIB_SUFFIX);
}
$module = 'geohash';
$functions = get_extension_funcs($module);
echo "Functions available in the test extension:$br\n";
foreach($functions as $func) {
    echo $func."$br\n";
}
echo "$br\n";


//31.045601, 121.399696
$hashcode = geohash_encode(31.045601, 121.399696,20);
echo $hashcode ."\n";
//var_dump(geohash_encode(31.045601, 121.399696,20));
//$hashcode  = substr($hashcode,0,5);
var_dump(geohash_decode($hashcode));
//$hashcode  = substr($hashcode,0,5);
//echo strlen($hashcode);
var_dump(geo_neighbors($hashcode));


//wtw2de8t9zqrd4skf7p
//echo strlen($hashcode);

?>
