#include"stdafx.h"
#include"zhttp_hander.h"
namespace zhttp_hander {
	using namespace std;
	//版本号
	const char* zhttp_version = "0.0.2";
	//保存options对应的str
	map<zhttp_options, string> zhttp_options_str;
	//逆str数组
	map<string,zhttp_options> zhttp_reoptions_str;
	//http状态码对应的字符串
	map<zhttp_status, string> zhttp_status_str;
	//mime对应str
	map<MIME, string> MIME_str;

	map<string,MIME> REMIME_str;
	//request项的string集合
	set<string>request_str;
	const string CRLF = "\\r\\n";
	const string Space = " ";
	const string Http_Version = "HTTP/1.0";
	void initStrs() {
		//初始化option对应字符
		zhttp_options_str[zhttp_options::GET] = "GET";
		zhttp_options_str[zhttp_options::POST] = "POST";
		zhttp_options_str[zhttp_options::DELETE] = "DELETE";
		zhttp_options_str[zhttp_options::PUT] = "PUT";
		//初始化status对应字符
		zhttp_status_str[zhttp_status::StatusOK] = "OK";
		zhttp_status_str[zhttp_status::StatusCreated] = "Created";
		zhttp_status_str[zhttp_status::StatusAccepted] = "Accepted";
		//300
		zhttp_status_str[zhttp_status::StatusMultipleChoices] = "Multiple Choices";
		zhttp_status_str[zhttp_status::StatusMovedPermanently] = "Moved Permanently";
		zhttp_status_str[zhttp_status::StatusFound] = "Found";
		zhttp_status_str[zhttp_status::StatusSeeOther] = "See Other";
		zhttp_status_str[zhttp_status::StatusNotModified] = "Not Modified";
		//400
		zhttp_status_str[zhttp_status::StatusBadRequest] = "Bad Request";
		zhttp_status_str[zhttp_status::StatusUnauthorized] = "Unauthorized";
		zhttp_status_str[zhttp_status::StatusPaymentRequired] = "Payment Required";
		zhttp_status_str[zhttp_status::StatusForbidden] = "Forbidden";
		zhttp_status_str[zhttp_status::StatusNotFound] = "Not Found";
		zhttp_status_str[zhttp_status::StatusMethodNotAllowed] = "Method Not Allowed";
		//500
		zhttp_status_str[zhttp_status::StatusInternalServerError] = "Internal Server Error";
		zhttp_status_str[zhttp_status::StatusNotImplemented] = "Not Implemented";
		zhttp_status_str[zhttp_status::StatusBadGateway] = "Bad Gateway";
		zhttp_status_str[zhttp_status::StatusServiceUnavailable] = "Service Unavailable";
		zhttp_status_str[zhttp_status::StatusGatewayTimeout] = "Gateway Timeout";
		//mime对应文字
		MIME_str[MIME::text_css] = "text/css";
		MIME_str[MIME::text_html] = "text/html";
		MIME_str[MIME::text_plain] = "text/plain";
		MIME_str[MIME::text_javascript] = "text/javascript";
		MIME_str[MIME::image_gif] = "image/gif";
		MIME_str[MIME::image_jpeg] = "image/jpeg";
		//request对应文字
		request_str.insert("If-Modified-Since");
		request_str.insert("If-None-Match");
		request_str.insert("Pragma");
		request_str.insert("Cache-Control");
		request_str.insert("Accept");
		request_str.insert("Accept-Encoding");
		request_str.insert("Accept-Language");
		request_str.insert("Accept-Charset");
		request_str.insert("User-Agent");
		request_str.insert("Content-Type");
		request_str.insert("Referer");
		request_str.insert("Connection");
		request_str.insert("Host");
		request_str.insert("Cookie");
		request_str.insert("Content-Length");
	}
	void initReMap() {
		for (auto &v : zhttp_options_str)
		{
			zhttp_reoptions_str.insert(make_pair(v.second,v.first));
		}
		for (auto &v : MIME_str)
		{
			REMIME_str.insert(make_pair(v.second, v.first));
		}
	}
	 string GetStatusText(zhttp_status status) {
		return zhttp_status_str[status];
	}
	 string GetMIMEText(MIME mime) {
		return MIME_str[mime];
	}
	 MIME GetMIMEByText(string src) {
		 return REMIME_str[src];
	 }
	 zhttp_options GetOptionByText(string src) {
		 return zhttp_reoptions_str[src];
	 }
	 string GetOptionText(zhttp_options option) {
		 return zhttp_options_str[option];
	 }
}