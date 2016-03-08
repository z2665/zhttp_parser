// main_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<string>
#include"../zhttp_parser/zparser_base.h"
#if _DEBUG
#pragma comment(lib,"../Debug/zhttp_parser.lib")
#else
#pragma comment(lib,"../Release/zhttp_parser.lib")
#endif // _DEBUG


using namespace std;
int main()
{
	string http = "GET /index.jsp HTTP/1.1\\r\\n\
Accept-Language: zh-cn\\r\\n\
Connection: Keep-Alive\\r\\n\
Host: 192.168.0.106\\r\\n\
Content-Length: 37\\r\\n\
\\r\\n\
userName=new_andy&password=new_andy\\r\\n";
	//初始化map
	zhttp_parser::basecoder::init();
	zhttp_parser::basecoder base;
	//创建request映射
	auto hmap=base.MakeRequestMap(http);
	//测试逆map是否成功
	zhttp_hander::zhttp_options op= zhttp_hander::zhttp_reoptions_str["POST"];
	//测试mapToStruct
	base.RequestMapToStuct(hmap);
    return 0;
}

