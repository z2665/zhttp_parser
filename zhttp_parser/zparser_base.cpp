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
	//��requsetת��Ϊmap
	basecoder::PMap basecoder::MakeRequestMap(string pack) {
		//��crfl�ָ��ַ���
		shared_ptr<map<string, string>> requestMap = make_shared<map<string, string>>();
		auto vl= split(pack, zhttp_hander::CRLF,false);
		auto vlhead = split((*vl)[0], " ",true);
		//http����һ��
		(*requestMap)["Options"] = (*vlhead)[0];
		(*requestMap)["URL"] = (*vlhead)[1];
		//http��requestheader
		auto i = vl->begin() + 1;
		for (; !i->empty(); ++i) {
			position pos = i->find(':');
			//pos+2����������֮��Ŀո�
			(*requestMap)[i->substr(0,pos)] = i->substr(pos+2);
		}
		//requestbody
		//ָ��requestbody
		i += 1;
		(*requestMap)["RquestBody"] =*i;
		return requestMap;
	}
	//��requestmap ת����struct
	basecoder::PRequest basecoder::RequestMapToStuct(basecoder::PMap pmap)
	{
		PRequest req = make_shared<zhttp_hander::request>();
		//����Ҫ���⴦���request����
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
		//��Ҫ���⴦���request����

		return req;
	}
	//����������structת��Ϊstring
	//�ָ��ַ���
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

