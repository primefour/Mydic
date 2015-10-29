
Did you remember to remove the libssl library package itself?
openssl = binaries and tools
libssl-dev = development files and headers
libssl0.9.8 = Actual openssl libraries

openssl lib for nginx
./config --prefix=/home/crazyhorse/test/MyServer/Server/local --openssldir=/home/crazyhorse/test/MyServer/Server/local/openssl

zlib
./configure --prefix=/home/crazyhorse/test/MyServer/Server/local

pcre-8.36
./configure --prefix=/home/crazyhorse/test/MyServer/Server/local


libxml2-2.9.2 (sudo apt-get install python-dev, sudo apt-get update --fix-missing,sudo apt-get install python-dev)
./configure --prefix=/home/crazyhorse/test/MyServer/Server/local



nginx server
change below file for libxslt libxml configure 
auto/lib/libxslt/conf
# Copyright (C) Igor Sysoev
# Copyright (C) Nginx, Inc.


    ngx_feature="libxslt"
    ngx_feature_name=
    ngx_feature_run=no
    ngx_feature_incs="#include <libxml/parser.h>
                      #include <libxml/tree.h>
                      #include <libxslt/xslt.h>
                      #include <libxslt/xsltInternals.h>
                      #include <libxslt/transform.h>
                      #include <libxslt/xsltutils.h>"
    ngx_feature_path="/home/crazyhorse/test/MyServer/Server/local/include/libxml2"
    ngx_feature_libs="-lxml2 -lxslt"
    ngx_feature_test="xmlParserCtxtPtr    ctxt = NULL;
                      xsltStylesheetPtr   sheet = NULL;
                      xmlDocPtr           doc;
                      doc = xmlParseChunk(ctxt, NULL, 0, 0);
                      xsltApplyStylesheet(sheet, doc, NULL);"
    . auto/feature


if [ $ngx_found = no ]; then

    # FreeBSD port

    ngx_feature="libxslt in /usr/local/"
    ngx_feature_path="/home/crazyhorse/test/MyServer/Server/local/include/libxml2 /home/crazyhorse/test/MyServer/Server/local/include/"

    if [ $NGX_RPATH = YES ]; then
        ngx_feature_libs="-R/home/crazyhorse/test/MyServer/Server/local/lib -L/home/crazyhorse/test/MyServer/Server/local/lib -lxml2 -lxslt"
    else
        ngx_feature_libs="-L/home/crazyhorse/test/MyServer/Server/local/lib -lxml2 -lxslt"
    fi

    . auto/feature
fi


if [ $ngx_found = no ]; then

    # NetBSD port

    ngx_feature="libxslt in /usr/pkg/"
    ngx_feature_path="/usr/pkg/include/libxml2 /usr/pkg/include"

    if [ $NGX_RPATH = YES ]; then
        ngx_feature_libs="-R/usr/pkg/lib -L/usr/pkg/lib -lxml2 -lxslt"
    else
        ngx_feature_libs="-L/usr/pkg/lib -lxml2 -lxslt"
    fi

    . auto/feature
fi


if [ $ngx_found = no ]; then

    # MacPorts

    ngx_feature="libxslt in /opt/local/"
    ngx_feature_path="/opt/local/include/libxml2 /opt/local/include"

    if [ $NGX_RPATH = YES ]; then
        ngx_feature_libs="-R/opt/local/lib -L/opt/local/lib -lxml2 -lxslt"
    else
        ngx_feature_libs="-L/opt/local/lib -lxml2 -lxslt"
    fi

    . auto/feature
fi


if [ $ngx_found = yes ]; then

    CORE_INCS="$CORE_INCS $ngx_feature_path"
    CORE_LIBS="$CORE_LIBS $ngx_feature_libs"

else

cat << END

$0: error: the HTTP XSLT module requires the libxml2/libxslt
libraries. You can either do not enable the module or install the libraries.

END

    exit 1
fi


    ngx_feature="libexslt"
    ngx_feature_name=NGX_HAVE_EXSLT
    ngx_feature_run=no
    ngx_feature_incs="#include <libexslt/exslt.h>"
    ngx_feature_path="/home/crazyhorse/test/MyServer/Server/local/include/libxml2"
    ngx_feature_libs="-lexslt"
    ngx_feature_test="exsltRegisterAll();"
    . auto/feature

if [ $ngx_found = no ]; then

    # FreeBSD port

    ngx_feature="libexslt in /home/crazyhorse/test/MyServer/Server/local/"
    ngx_feature_path="/home/crazyhorse/test/MyServer/Server/local/include/libxml2 /home/crazyhorse/test/MyServer/Server/local/include"

    if [ $NGX_RPATH = YES ]; then
        ngx_feature_libs="-R/home/crazyhorse/test/MyServer/Server/local/lib -L/home/crazyhorse/test/MyServer/Server/local/lib -lexslt"
    else
        ngx_feature_libs="-L/home/crazyhorse/test/MyServer/Server/local/lib -lexslt"
    fi

    . auto/feature
fi


if [ $ngx_found = no ]; then

    # NetBSD port

    ngx_feature="libexslt in /usr/pkg/"
    ngx_feature_path="/usr/pkg/include/libxml2 /usr/local/include"

    if [ $NGX_RPATH = YES ]; then
        ngx_feature_libs="-R/usr/pkg/lib -L/usr/pkg/lib -lexslt"
    else
        ngx_feature_libs="-L/usr/pkg/lib -lexslt"
    fi

    . auto/feature
fi


if [ $ngx_found = no ]; then

    # MacPorts

    ngx_feature="libexslt in /opt/local/"
    ngx_feature_path="/opt/local/include/libxml2 /opt/local/include"

    if [ $NGX_RPATH = YES ]; then
        ngx_feature_libs="-R/opt/local/lib -L/opt/local/lib -lexslt"
    else
        ngx_feature_libs="-L/opt/local/lib -lexslt"
    fi

    . auto/feature
fi


if [ $ngx_found = yes ]; then
    CORE_LIBS="$CORE_LIBS -lexslt"
fi


./configure --user=www_server --group=www_server --with-http_ssl_module 
--with-http_realip_module --with-http_xslt_module --with-http_image_filter_module  
--with-pcre=/home/crazyhorse/test/MyServer/Server/source/pcre-8.36 --with-openssl=/home/crazyhorse/test/MyServer/Server/source/openssl (source code location)



Configuration summary
  + using PCRE library: ../pcre-8.36
  + using OpenSSL library: ../openssl-1.0.2d/
  + md5: using OpenSSL library
  + sha1: using OpenSSL library
  + using system zlib library

  nginx path prefix: "/home/crazyhorse/test/MyServer/Server/Nginx/"
  nginx binary file: "/home/crazyhorse/test/MyServer/Server/Nginx//sbin/nginx"
  nginx configuration prefix: "/home/crazyhorse/test/MyServer/Server/Nginx//conf"
  nginx configuration file: "/home/crazyhorse/test/MyServer/Server/Nginx//conf/nginx.conf"
  nginx pid file: "/home/crazyhorse/test/MyServer/Server/Nginx//logs/nginx.pid"
  nginx error log file: "/home/crazyhorse/test/MyServer/Server/Nginx//logs/error.log"
  nginx http access log file: "/home/crazyhorse/test/MyServer/Server/Nginx//logs/access.log"
  nginx http client request body temporary files: "client_body_temp"
  nginx http proxy temporary files: "proxy_temp"
  nginx http fastcgi temporary files: "fastcgi_temp"
  nginx http uwsgi temporary files: "uwsgi_temp"
  nginx http scgi temporary files: "scgi_temp"



Command Description
nginx –s stop 
nginx –s quit Stops the daemon gracefully (using the QUIT signal)
nginx –s reopen Reopens the log files
nginx –s reload Reloads the configuration



fastcgi_pass Specifies that the request should be passed to the FastCGI server, by indicating its location:
Context: location, if
• For TCP sockets, the syntax is: fastcgi_pass hostname:port;
• For Unix Domain sockets, the syntax is: fastcgi_pass unix:/path/to/ fastcgi.socket;
• You may also refer to upstream blocks (read the following sections for more information):
  fastcgi_pass myblock;
Examples:
fastcgi_pass localhost:9000;
fastcgi_pass 127.0.0.1:9000;
fastcgi_pass unix:/tmp/fastcgi.socket;
# Using an upstream block
upstream fastcgi {
server 127.0.0.1:9000;
server 127.0.0.1:9001;
}
location ~* \.php$ {
fastcgi_pass fastcgi;
}



fastcgi_param Allows you to configure the request passed to FastCGI. Two parameters are strictly required for all FastCGI requests: SCRIPT_FILENAME and QUERY_STRING.
Context: http, server,
location
Example:
fastcgi_param SCRIPT_FILENAME /home/website.com/www$fastcgi_script_name;
fastcgi_param QUERY_STRING $query_string;
As for POST requests, additional parameters are required: REQUEST_METHOD, CONTENT_TYPE, and CONTENT_LENGTH:
fastcgi_param REQUEST_METHOD $request_method;
fastcgi_param CONTENT_TYPE $content_type;
fastcgi_param CONTENT_LENGTH $content_length;
The fastcgi_params file that you will find in the Nginx configuration folder already includes all the necessary parameter definitions, 
except for the SCRIPT_FILENAME one that you have to specify for each of your FastCGI configurations.
Syntax: fastcgi_param PARAM value;



fastcgi_pass_header
Context: http, server,
location
Specifies additional headers that should be passed to the FastCGI server.
Syntax: fastcgi_pass_header headername;
Example:
fastcgi_pass_header Authorization;



fastcgi_hide_header
Context: http, server,
location
Specifies headers that should be hidden from the FastCGI server (headers that Nginx does not forward).
Syntax: fastcgi_hide_header headername;
Example:
fastcgi_hide_header X-Forwarded-For;




php

 ./configure --prefix=/home/crazyhorse/test/MyServer/Server/Php --enable-fpm



Post-install configuration
Begin by configuring your newly installed PHP, for example, copying the php.ini of
your previous setup over the new one. The next step is to configure PHP-FPM—open
up the php-fpm.conf file, by default, located in /usr/local/etc/.
The file contains some important configuration directives that we will reuse later:
• Edit the users and groups for the Unix socket and the processes
• Address and port on which PHP-FPM will be listening
• Amount of simultaneous requests that will be served
• IP address(es) allowed to connect to PHP-FPM
Running and controlling
Once you made the appropriate changes to the PHP-FPM configuration file, you may
start it with the following command:
[root@website.com ~]# /usr/sbin/php-fpm start
If all goes according to plan, you should be greeted with

php-fpm stop; # Stops PHP-FPM
php-fpm quit; # Gracefully shuts down PHP-FPM
php-fpm restart; # Stops and starts PHP-FPM again
php-fpm reload; # Reloads configuration
php-fpm logrotate; # Performs a rotation of log files

sudo netstat -putln

sudo ./sbin/php-fpm -t -y ./etc/php-fpm.conf.default 
sudo ./sbin/php-fpm -y ./etc/php-fpm.conf.default


