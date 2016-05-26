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
		PMap requestMap = make_shared<map<string, string>>();
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
		//URL
		auto urlpart = split((*pmap)["URL"], "?", true);//分开路径与参数部分
		//如果url不为空
		if (!urlpart->empty()) {
			req->url.path = (*urlpart)[0];//将第一部分路径放入结构体
			//如果存在第二部分
			if (urlpart->size() > 1) {
				//将参数分开
				auto parms = split((*urlpart)[1], "&", true);
				for (auto& i : *parms) {
					auto pa = split(i, "=", true);
					req->url.parameters.push_back(make_pair((*pa)[0], (*pa)[1]));
				}
			}
		}
		return req;
	}
	//编码器，将map转换为string
	string basecoder::RequestMapToString(PMap pmapsrc)
	{
		string pack;
		//复制一份副本
		PMap pmap= make_shared<map<string, string>>();
		pmap->insert(pmapsrc->begin(), pmapsrc->end());
		//构建第一行特殊行
		pack += (*pmap)["Options"] + zhttp_hander::Space + (*pmap)["URL"] + zhttp_hander::Space + zhttp_hander::Http_Version + zhttp_hander::CRLF;
		//保存requestBody
		string tmp = (*pmap)["RquestBody"];
		//删除特殊元素
		pmap->erase(pmap->find("Options"));
		pmap->erase(pmap->find("URL"));
		pmap->erase(pmap->find("RquestBody"));
		//遍历容器进行处理
		for (auto& pair : (*pmap))
		{
			pack += makeRow(pair);
		}
		//request头和body分离
		pack += zhttp_hander::CRLF;
		//附加body
		pack += tmp+zhttp_hander::CRLF;
		return pack;
	}
	//创建request头的行
	std::string basecoder::makeRow(decltype(*HttpMap::iterator()) pair)
	{
		return pair.first + ":"+zhttp_hander::Space + pair.second + zhttp_hander::CRLF;
	}
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

