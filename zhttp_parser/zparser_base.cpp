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
	//将struct转换为map
	basecoder::PMap  basecoder::RequestStuctToMap(PRequest req)
	{
		PMap requestMap = make_shared<map<string, string>>();
		//插入无需特殊处理的项
		InsertMapIfNotNull(requestMap, make_pair("Accept-Charset", req->Accept_Charset));
		InsertMapIfNotNull(requestMap, make_pair("Accept-Encoding", req->Accept_Encoding));
		InsertMapIfNotNull(requestMap, make_pair("Accept-Language", req->Accept_Language));
		InsertMapIfNotNull(requestMap, make_pair("Cache-Control", req->Cache_Control));
		InsertMapIfNotNull(requestMap, make_pair("Connection", req->Connection));
		InsertMapIfNotNull(requestMap, make_pair("Content-Length", req->Content_Length));
		InsertMapIfNotNull(requestMap, make_pair("Content-Type", zhttp_hander::GetMIMEText(req->Content_Type)));
		InsertMapIfNotNull(requestMap, make_pair("Cookie", req->Cookie));
		InsertMapIfNotNull(requestMap, make_pair("Host", req->Host));
		InsertMapIfNotNull(requestMap, make_pair("If-Modified-Since", req->If_Modified_Since));
		InsertMapIfNotNull(requestMap, make_pair("If-None-Match", req->If_None_Match));
		InsertMapIfNotNull(requestMap, make_pair("Options", zhttp_hander::GetOptionText(req->Options)));
		InsertMapIfNotNull(requestMap, make_pair("Pragma", req->Pragma));
		InsertMapIfNotNull(requestMap, make_pair("Referer", req->Referer));
		InsertMapIfNotNull(requestMap, make_pair("RquestBody", req->RquestBody));
		InsertMapIfNotNull(requestMap, make_pair("User-Agent", req->User_Agent));
		//处理url并插入
		string tmpurl = req->url.path;
		//第一项
		bool fr = true;
		for (auto &i : req->url.parameters) {
			//如果是第一项则插入参数符号
			if (fr) {
				tmpurl += "?" + (i.first + "=" + i.second);
				fr = false;
			}
			//如果不是第一项则加上连接字符
			tmpurl += "&" + (i.first + "=" + i.second);
		}
		(*requestMap)["URL"] = tmpurl;
		return requestMap;

	}
	//创建Header头的行
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
	void basecoder::InsertMapIfNotNull(PMap pmap, const pair<string,string> src) {
		if (!src.second.empty()) {
			(*pmap)[src.first] = src.second;
			}
	}
		
}

