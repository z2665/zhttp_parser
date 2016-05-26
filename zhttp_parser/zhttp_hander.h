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
//http����
	enum class zhttp_options
{
	GET,
	POST,
	PUT,
	DELETE
};
//����options��Ӧ��str
extern map<zhttp_options, string> zhttp_options_str;
//��str����
extern map<string,zhttp_options> zhttp_reoptions_str;
//http״̬��
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
//http״̬���Ӧ���ַ���
extern map<zhttp_status,string> zhttp_status_str;
//mime����
enum class MIME
{
	text_css,//css
	text_html,//html
	text_plain,//txt
	text_javascript,//js
	image_gif,//gif
	image_jpeg,//jpg
};
//mime��Ӧstr
extern map<MIME, string> MIME_str;
//str����mime
extern map<string,MIME> REMIME_str;
extern void initStrs();
extern void initReMap();
//��ȡ״̬���Ӧ����
extern string GetStatusText(zhttp_status status);
extern string GetMIMEText(MIME mime);
extern string GetOptionText(zhttp_options option);
//��ȡ���ֶ�Ӧ����
extern MIME GetMIMEByText(string src);
extern zhttp_options GetOptionByText(string src);
//url
struct URL
{
	string path;//·��
	vector<pair<string,string>> parameters;//����
};
//
//requestͷ
struct request
{
	zhttp_options Options;//����ʽ
	string RquestBody;//������ һ����post json
	URL url;//ͳһ��Դ��λ��
	string If_Modified_Since;//������˻���ҳ�������޸�ʱ�䷢�͵�������ȥ��������������ʱ�����������ʵ���ļ�������޸�ʱ����жԱ�
	string If_None_Match;//If-None-Match��ETagһ����.Etag�ɷ����������ɣ��ͻ���ͨ��If-Match����˵If-None-Match��������ж���������֤��Դ�Ƿ��޸ġ�
	string Pragma;//�Ƿ�һ������������.��HTTP/1.0�汾�У�ֻʵ����Pragema:no-cache, û��ʵ��Cache-Control
	string Cache_Control;//ָ���������Ӧ��ѭ�Ļ�����ơ�
	vector<MIME> Accept;//������˿��Խ��ܵ�MIME���͡�
	string Accept_Encoding; //����������Լ��ɽ��յı��뷽��
	string Accept_Language; //����������Լ����յ����ԡ�
	string Accept_Charset;//������ɽ��ܵ��ַ���
	string User_Agent;//����HTTP���������ͻ���ʹ�õĲ���ϵͳ������������ƺͰ汾��
	MIME Content_Type; //�������������ʲô��ʽ��ʲô�����ȡ����ļ�.���磺Content - Type: application / x - www - form - urlencoded��
	string Referer;//����һ��URL���û��Ӹ�URL�����ҳ��������ʵ�ǰ�����ҳ�档�������ӿ��Ա����Դ
	string Connection; //Connection: keep - alive ��һ����ҳ����ɺ󣬿ͻ��˺ͷ�����֮�����ڴ���HTTP���ݵ�TCP���Ӳ���ر�
	string Host;//��Ҫ����ָ����������Դ��Internet�����Ͷ˿ںţ���ͨ����HTTP URL����ȡ�����ġ�HTTP / 1.1��������������ͷ�򣬷���ϵͳ����400״̬�뷵�ء�
	string Cookie;//����Ҫ������ͷ֮һ, ��cookie��ֵ���͸�HTTP��������
	string Content_Length;// ��ʾ������Ϣ���ĵĳ��ȡ����磺Content - Length: 38��
};
//request���string����
extern set<string>request_str;
//responseͷ
struct  response
{
	string Allow; //������֧����Щ���󷽷�����GET��POST�ȣ���
	string Date;//��ʾ��Ϣ���͵�ʱ�䣬ʱ���������ʽ��rfc822���塣���磬Date:Mon,31Dec200104:25:57GMT��
	string Expires;//ָ��Ӧ����ʲôʱ����Ϊ�ĵ��Ѿ����ڣ��Ӷ����ٻ����������´ӷ�������ȡ������»��档
	string P3P;//���ڿ�������Cookie, �������Խ��iframe�������cookie������
	string Set_Cookie;//�ǳ���Ҫ��header, ���ڰ�cookie���͵��ͻ����������ÿһ��д��cookie��������һ��Set-Cookie��
	string ETag;//��If-None-Match ���ʹ�á�
	string Last_Modified;//����ָʾ��Դ������޸����ں�ʱ�䡣
	MIME Content_Type; //WEB����������������Լ���Ӧ�Ķ�������ͺ��ַ�����
	string Content_Length;//ָ��ʵ�����ĵĳ��ȣ����ֽڷ�ʽ�洢��ʮ������������ʾ��
	string Content_Encoding;// wEB�����������Լ�ʹ����ʲôѹ��������gzip��deflate��ѹ����Ӧ�еĶ���
	string Server;//ָ��HTTP������������������������Ϣ��
	string Connection;//Connection: keep-alive ��һ����ҳ����ɺ󣬿ͻ��˺ͷ�����֮�����ڴ���HTTP���ݵ�TCP���Ӳ���ر�
	string Refresh;//��ʾ�����Ӧ���ڶ���ʱ��֮��ˢ���ĵ�

};

}