#include"stdafx.h"
#include<iostream>
#include"zparser_base.h"
#include<iostream>
using namespace std;
namespace zhttp_parser {
	basecoder::basecoder() {
		
	}
	basecoder::~basecoder() {
	}
	void basecoder::init() {
		zhttp_hander::initStrs();
		zhttp_hander::initReMap();
	}
	//将requset转换为map
	basecoder::PMap basecoder::MakeRequestMap(string pack) {
		//按crfl分割字符串
		shared_ptr<map<string, string>> requestMap = make_shared<map<string, string>>();
		auto vl= split(pack, zhttp_hander::CRLF,false);
		auto vlhead = split((*vl)[0], " ",true);
		//http包第一行
		(*requestMap)["Options"] = (*vlhead)[0];
		(*requestMap)["URL"] = (*vlhead)[1];
		//http包requestheader
		auto i = vl->begin() + 1;
		for (; !i->empty(); ++i) {
			position pos = i->find(':');
			//pos+2用来跳过：之后的空格
			(*requestMap)[i->substr(0,pos)] = i->substr(pos+2);
		}
		//requestbody
		//指向requestbody
		i += 1;
		(*requestMap)["RquestBody"] =*i;
		return requestMap;
	}
	//将requestmap 转换到struct
	basecoder::PRequest basecoder::RequestMapToStuct(basecoder::PMap pmap)
	{
		PRequest req = make_shared<zhttp_hander::request>();
		//不需要特殊处理的request属性
		req->Accept_Charset = (*pmap)["Accept-Charset"];
		req->Accept_Encoding = (*pmap)["Accept-Encoding"];
		req->Accept_Language = (*pmap)["Accept-Language"];
		req->Cache_Control = (*pmap)["Cache-Control"];
		req->Connection = (*pmap)["Connection"];
		req->Content_Length = (*pmap)["Content-Length"];
		req->Content_Type = zhttp_hander::GetMIMEByText((*pmap)["Content-Type"]);
		req->Cookie = (*pmap)["Cookie"];
		req->Host= (*pmap)["Host"];
		req->If_Modified_Since= (*pmap)["If-Modified-Since"];
		req->If_None_Match= (*pmap)["If-None-Match"];
		req->Options=zhttp_hander::GetOptionByText( (*pmap)["Options"]);
		req->Pragma= (*pmap)["Pragma"];
		req->Referer= (*pmap)["Referer"];
		req->RquestBody= (*pmap)["RquestBody"];
		req->User_Agent= (*pmap)["User-Agent"];
		//需要特殊处理的request属性

		return req;
	}
	//编码器，将struct转换为string
	//分割字符串
	shared_ptr<std::vector<std::string>>  basecoder::split(std::string  source, string condition,bool needLast) {
		shared_ptr<vector<string>> pvec = make_shared<vector<string>>();
		position pold = 0;
		position p = source.find(condition);
		while (p != string::npos)
		{
			pvec->push_back( source.substr(pold, p-pold));
			pold = p+condition.length();
			p = source.find(condition, pold);
		}
		if (needLast) {
			pvec->push_back(source.substr(pold));
		}
		return pvec;
	}
}

