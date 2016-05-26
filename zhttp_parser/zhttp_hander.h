#pragma once
#include<string>
#include<map>
#include<set>
#include<vector>
namespace zhttp_hander {
	using namespace std;
	extern const string CRLF;
    extern const string Http_Version;
	extern const string Space;
	extern const char* zhttp_version;
//http动作
	enum class zhttp_options
{
	GET,
	POST,
	PUT,
	DELETE
};
//保存options对应的str
extern map<zhttp_options, string> zhttp_options_str;
//逆str数组
extern map<string,zhttp_options> zhttp_reoptions_str;
//http状态码
enum class zhttp_status
{
	StatusOK = 200,
	StatusCreated ,
	StatusAccepted,
	StatusMultipleChoices=300,
	StatusMovedPermanently,
	StatusFound ,
	StatusSeeOther ,
	StatusNotModified,
	StatusBadRequest = 400,
	StatusUnauthorized,
	StatusPaymentRequired,
	StatusForbidden,
	StatusNotFound,
	StatusMethodNotAllowed,
	StatusInternalServerError = 500,
	StatusNotImplemented,
	StatusBadGateway,
	StatusServiceUnavailable,
	StatusGatewayTimeout,
};
//http状态码对应的字符串
extern map<zhttp_status,string> zhttp_status_str;
//mime类型
enum class MIME
{
	text_css,//css
	text_html,//html
	text_plain,//txt
	text_javascript,//js
	image_gif,//gif
	image_jpeg,//jpg
};
//mime对应str
extern map<MIME, string> MIME_str;
//str对于mime
extern map<string,MIME> REMIME_str;
extern void initStrs();
extern void initReMap();
//获取状态码对应文字
extern string GetStatusText(zhttp_status status);
extern string GetMIMEText(MIME mime);
extern string GetOptionText(zhttp_options option);
//获取文字对应类型
extern MIME GetMIMEByText(string src);
extern zhttp_options GetOptionByText(string src);
//url
struct URL
{
	string path;//路径
	vector<pair<string,string>> parameters;//参数
};
//
//request头
struct request
{
	zhttp_options Options;//请求方式
	string RquestBody;//请求体 一般是post json
	URL url;//统一资源定位器
	string If_Modified_Since;//浏览器端缓存页面的最后修改时间发送到服务器去，服务器会把这个时间与服务器上实际文件的最后修改时间进行对比
	string If_None_Match;//If-None-Match和ETag一起工作.Etag由服务器端生成，客户端通过If-Match或者说If-None-Match这个条件判断请求来验证资源是否修改。
	string Pragma;//是否一定返回新内容.在HTTP/1.0版本中，只实现了Pragema:no-cache, 没有实现Cache-Control
	string Cache_Control;//指定请求和响应遵循的缓存机制。
	vector<MIME> Accept;//浏览器端可以接受的MIME类型。
	string Accept_Encoding; //浏览器申明自己可接收的编码方法
	string Accept_Language; //浏览器申明自己接收的语言。
	string Accept_Charset;//浏览器可接受的字符集
	string User_Agent;//告诉HTTP服务器，客户端使用的操作系统和浏览器的名称和版本。
	MIME Content_Type; //决定浏览器将以什么形式、什么编码读取这个文件.例如：Content - Type: application / x - www - form - urlencoded。
	string Referer;//包含一个URL，用户从该URL代表的页面出发访问当前请求的页面。友情链接可以标出来源
	string Connection; //Connection: keep - alive 当一个网页打开完成后，客户端和服务器之间用于传输HTTP数据的TCP连接不会关闭
	string Host;//主要用于指定被请求资源的Internet主机和端口号，它通常从HTTP URL中提取出来的。HTTP / 1.1请求必须包含主机头域，否则系统会以400状态码返回。
	string Cookie;//最重要的请求头之一, 将cookie的值发送给HTTP服务器。
	string Content_Length;// 表示请求消息正文的长度。例如：Content - Length: 38。
};
//request项的string集合
extern set<string>request_str;
//response头
struct  response
{
	string Allow; //服务器支持哪些请求方法（如GET、POST等）。
	string Date;//表示消息发送的时间，时间的描述格式由rfc822定义。例如，Date:Mon,31Dec200104:25:57GMT。
	string Expires;//指明应该在什么时候认为文档已经过期，从而不再缓存它，重新从服务器获取，会更新缓存。
	string P3P;//用于跨域设置Cookie, 这样可以解决iframe跨域访问cookie的问题
	string Set_Cookie;//非常重要的header, 用于把cookie发送到客户端浏览器，每一个写入cookie都会生成一个Set-Cookie。
	string ETag;//和If-None-Match 配合使用。
	string Last_Modified;//用于指示资源的最后修改日期和时间。
	MIME Content_Type; //WEB服务器告诉浏览器自己响应的对象的类型和字符集。
	string Content_Length;//指明实体正文的长度，以字节方式存储的十进制数字来表示。
	string Content_Encoding;// wEB服务器表明自己使用了什么压缩方法（gzip，deflate）压缩响应中的对象
	string Server;//指明HTTP服务器用来处理请求的软件信息。
	string Connection;//Connection: keep-alive 当一个网页打开完成后，客户端和服务器之间用于传输HTTP数据的TCP连接不会关闭
	string Refresh;//表示浏览器应该在多少时间之后刷新文档

};

}