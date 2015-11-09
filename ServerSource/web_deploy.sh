
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

#fastcgi_param  SCRIPT_FILENAME  /scripts$fastcgi_script_name;
fastcgi_param  SCRIPT_FILENAME  $document_root$fastcgi_script_name;

user  www_server www_server;
error_log logs/error.log;
pid logs/nginx.pid;




nginx.conf Description
mime.types A list of file extensions and their associated MIME types
fastcgi.conf FastCGI-related configuration
proxy.conf Proxy-related configuration
sites.conf Configuration of the websites served by Nginx, also known as virtual hosts. It\'s recommended to create separate files for each domain.



events {
worker_connections 1024;
}
The events block that you can find in the default configuration file is brought in by
the Events module. The directives that the module enables can only be used within
that block—in the preceding example, worker_connections will only make sense
in the context of the events block. There is one important exception though—some
directives may be placed at the root of the configuration file because they have a
global effect on the server. The root of the configuration file is also known as the
main block.







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


./configure --prefix=/home/crazyhorse/test/MyServer/Server/Php --enable-fpm --with-mysqli --with-pdo-mysql --with-mysql




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



<?php
function sanitizeValue($var) {
$var = sanitizeString($var)
$var = stripslashes($var);
$var = htmlentities($var);
return $var;
}
strip_tags($var);
function sanitizeMySQL($connection, $var)
{ // Using the mysqli extension
$var = $connection->real_escape_string($var);
$var = sanitizeString($var);
return $var;
}
?>



mysql 

show databases;

show tables from database_name;

describe table_name;

use mysql ;

select * from user;

delete * from user where host <> "localhost" ;

delete * from user where user == "";

select * from user ;


drop database test;

set password for 'root'@'localhost' = password('mysql');


create user 'www_server'@'localhost' indentified by 'www_server';


SSL模块（SSL）

·摘要
这个模块提供HTTPS支持
支持通过以下两个限制检察客户端证书：
·0.8.7之前的版本无法为过期证书指定列表。
·如果你有一个证书链文件（有时称为一个中级证书），你并不需要像apache那样对每个都进行指定，你只需要将证书链中的信息追加到主证书文件中（通过cat chain.crt >> mysite.com.crt命令），之后可以不适用证书链文件，只需要让nginx指向主证书文件。
默认情况下模块并未被安装，如果要使用该模块则需要在编译时指定--with-http_ssl_module参数，安装模块依赖于OpenSSL库和一些引用文件，通常这些文件并不在同一个软件包中。
下面的例子是一个使用SSL的示例配置，为了减少CPU负载，可以将其指到一个工作进程，并且启用keepalive。

worker_processes 1;
http {
  server {
    listen               443;
    ssl                  on;
    ssl_certificate      /usr/local/nginx/conf/cert.pem;
    ssl_certificate_key  /usr/local/nginx/conf/cert.key;
    keepalive_timeout    70;
  }
}

如果使用证书链文件，只需要将其追加到你的.crt文件（上例中为cret.pem），你自己的证书需要位于文件的顶部，否则密钥无法对其进行匹配。
0.7.14版本以后通常将ssl参数使用到listen指令中：

server {
  listen 443 default ssl;
  ssl_certificate      /usr/local/nginx/conf/cert.pem;
  ssl_certificate_key  /usr/local/nginx/conf/cert.key;  
  ...
}

生成证书
可以通过以下步骤生成一个简单的证书：

$ cd /usr/local/nginx/conf
$ openssl genrsa -des3 -out server.key 1024
$ openssl req -new -key server.key -out server.csr
$ cp server.key server.key.org
$ openssl rsa -in server.key.org -out server.key
$ openssl x509 -req -days 365 -in server.csr -signkey server.key -out server.crt

在nginx.conf中配置这个证书：

server {
    server_name YOUR_DOMAINNAME_HERE;
    listen 443;
    ssl on;
    ssl_certificate /usr/local/nginx/conf/server.crt;
    ssl_certificate_key /usr/local/nginx/conf/server.key;
}

重启nginx。
这样就可以通过以下方式访问：

https://YOUR_DOMAINNAME_HERE

在多个server块中使用通配符证书。
在某些情况下你可能需要在一个非安全验证的域中指定一个或多个安全验证的子域，并且能够在HTTP和HTTPS子域中共享资源，要实现这种功能则需要带通配符的子域，如*.nginx.org，下面的例子中表示如何配置一个标准的www子域，一个安全验证子域，并且两个子域均能访问的共享图片域。
使用这种配置最好http块中指定一个证书文件和密钥用于多个server，这样在每个server中都会继承它的一个工作拷贝。

ssl_certificate      common.crt;
ssl_certificate_key  common.key;
 
server {
  listen           80;
  server_name      www.nginx.org;
  ...
}
 
server {
  listen           443 ssl;
  server_name      secure.nginx.org;
  ...
}
 
server {
  listen           80;
  listen           443;
  server_name      images.nginx.org;
  ...
}

·指令
ssl
语法：ssl [on|off]
默认值：ssl off
使用字段：main, server
开启HTTPS。
ssl_certificate
语法：ssl_certificate file
默认值：ssl_certificate cert.pem
使用字段：main, server
为这个虚拟主机指定PEM格式的证书文件，一个文件可以包含其他的证书，同样，密钥也必须是PEM格式，0.6.7版本以后，这里的路径为相对于nginx.conf的路径，而不是编译时的prefix路径。
ssl_certificate_key
语法：ssl_certificate_key file
默认值：ssl_certificate_key cert.pem
使用字段：main, server
为这个虚拟主机指定PEM格式的密钥，0.6.7版本以后，这里的路径为相对于nginx.conf的路径，而不是编译时的prefix路径。
ssl_client_certificate
语法：ssl_client_certificate file
默认值：none
使用字段：main, server
指出PEM格式的证书认证文件，在检查客户端证书时使用。
ssl_dhparam
语法：ssl_dhparam file
默认值：none
使用字段：main, server
指出PEM格式并带有Diffie-Hellman参数的文件，用于TLS会话。
ssl_ciphers
语法：ssl_ciphers file
默认值：ssl_ciphers ALL:!ADH:RC4+RSA:+HIGH:+MEDIUM:+LOW:+SSLv2:+EXP
使用字段：main, server
指出允许的密码，密码指定为OpenSSL支持的格式，如：

ssl_ciphers  ALL:!ADH:!EXPORT56:RC4+RSA:+HIGH:+MEDIUM:+LOW:+SSLv2:+EXP;

使用下列命令查看完整格式列表：

openssl ciphers

ssl_crl
语法：ssl_crl file
默认值：none
使用字段：http, server
指定一个PEM格式的证书吊销列表文件，用于检查客户端证书（0.8.7以后版本）
ssl_prefer_server_ciphers
语法：ssl_prefer_server_ciphers [on|off]
默认值：ssl_prefer_server_ciphers off
使用字段：main, server
依赖SSLv3和TLSv1协议的服务器密码将优先于客户端密码。
ssl_protocols
语法：ssl_protocols [SSLv2] [SSLv3] [TLSv1]
默认值：ssl_protocols SSLv2 SSLv3 TLSv1
使用字段：main, server
指定要使用的SSL协议。
ssl_verify_client
语法：ssl_verify_client on|off|optional
默认值：ssl_verify_client off
使用字段：main, server
启用客户端证书审核，参数“optional”在客户端主动提出时检查证书(0.8.7与0.7.63版本之前为"ask")。
ssl_verify_depth
语法：ssl_verify_depth number
默认值：ssl_verify_depth 1
使用字段：main, server
设置客户证书认证链的长度。
ssl_session_cache
语法：ssl_session_cache off|none|builtin:size and/or shared:name:size
默认值：ssl_session_cache off
使用字段： main, server
设置储存SSL会话的缓存类型和大小。
缓存类型为：
·off - 强制关闭：nginx告诉客户端这个会话已经不能被再次使用。
·none - 非强制关闭：nginx告诉客户端这个会话可以被再次使用，但是nginx实际上并不使用它们，这是为某些使用ssl_session_cache的邮件客户端提供的一种变通方案，可以使用在邮件代理和HTTP服务器中。
·builtin - 内建OpenSSL缓存，仅能用在一个工作进程中，缓存大小在会话总数中指定，注意：如果要使用这个类型可能会引起内存碎片问题，具体请查看下文中参考文档。
·shared - 缓存在所有的工作进程中共享，缓存大小指定单位为字节，1MB缓存大概保存4000个会话，每个共享的缓存必须有自己的名称，相同名称的缓存可以使用在不同的虚拟主机中。
可以同时使用两个缓存类型，如：

ssl_session_cache  builtin:1000  shared:SSL:10m;

然而，使用共享缓存而不适用内建缓存将更为有效。
0.8.34版本之前如果ssl_verify_client设置为'on'或者'optional'时这里必须设置为none或off。
ssl_session_timeout
语法：ssl_session_timeout time
默认值：ssl_session_timeout 5m
使用字段： main, server
设置客户端能够反复使用储存在缓存中的会话参数时间。
ssl_engine
语法：ssl_engine
指定使用的OpenSSL引擎，如Padlock，需要比较新版本的OpenSSL。
·内置变量
ngx_http_ssl_module模块支持下列内建变量：
·$ssl_cipher - 返回建立的SSL连接中那些使用的密码字段。
·$ssl_client_serial - 返回建立的SSL连接中客户端证书的序列号。
·$ssl_client_s_dn - 返回建立的SSL连接中客户端证书的DN主题字段。
·$ssl_client_i_dn - 返回建立的SSL连接中客户端证书的DN发行者字段。
·$ssl_protocol - 返回建立的SSL连接中使用的协议。
·$ssl_session_id - 需要0.8.20以上版本。
·$ssl_client_cert
·$ssl_client_raw_cert
·$ssl_client_verify - 如果客户端证书审核通过，这个变量为“SUCCESS”。
·非标准错误代码
这个模块支持一些非标准的HTTP错误代码，可以借助error_page指令用于调试：
·495 - 检查客户端证书时发生错误。
·496 - 客户端无法提供必须的证书。
·497 - 传送到HTTPS的普通请求。
在请求完整的废除后调试完成，并取得一些内置变量，如：$request_uri, $uri, $arg等。 
