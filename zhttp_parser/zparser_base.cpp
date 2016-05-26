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
		PMap requestMap = make_shared<map<string, string>>();
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
		//URL
		auto urlpart = split((*pmap)["URL"], "?", true);//�ֿ�·�����������
		//���url��Ϊ��
		if (!urlpart->empty()) {
			req->url.path = (*urlpart)[0];//����һ����·������ṹ��
			//������ڵڶ�����
			if (urlpart->size() > 1) {
				//�������ֿ�
				auto parms = split((*urlpart)[1], "&", true);
				for (auto& i : *parms) {
					auto pa = split(i, "=", true);
					req->url.parameters.push_back(make_pair((*pa)[0], (*pa)[1]));
				}
			}
		}
		return req;
	}
	//����������mapת��Ϊstring
	string basecoder::RequestMapToString(PMap pmapsrc)
	{
		string pack;
		//����һ�ݸ���
		PMap pmap= make_shared<map<string, string>>();
		pmap->insert(pmapsrc->begin(), pmapsrc->end());
		//������һ��������
		pack += (*pmap)["Options"] + zhttp_hander::Space + (*pmap)["URL"] + zhttp_hander::Space + zhttp_hander::Http_Version + zhttp_hander::CRLF;
		//����requestBody
		string tmp = (*pmap)["RquestBody"];
		//ɾ������Ԫ��
		pmap->erase(pmap->find("Options"));
		pmap->erase(pmap->find("URL"));
		pmap->erase(pmap->find("RquestBody"));
		//�����������д���
		for (auto& pair : (*pmap))
		{
			pack += makeRow(pair);
		}
		//requestͷ��body����
		pack += zhttp_hander::CRLF;
		//����body
		pack += tmp+zhttp_hander::CRLF;
		return pack;
	}
	//��structת��Ϊmap
	basecoder::PMap  basecoder::RequestStuctToMap(PRequest req)
	{
		PMap requestMap = make_shared<map<string, string>>();
		//�����������⴦�����
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
		//����url������
		string tmpurl = req->url.path;
		//��һ��
		bool fr = true;
		for (auto &i : req->url.parameters) {
			//����ǵ�һ��������������
			if (fr) {
				tmpurl += "?" + (i.first + "=" + i.second);
				fr = false;
			}
			//������ǵ�һ������������ַ�
			tmpurl += "&" + (i.first + "=" + i.second);
		}
		(*requestMap)["URL"] = tmpurl;
		return requestMap;

	}
	//����Headerͷ����
	std::string basecoder::makeRow(decltype(*HttpMap::iterator()) pair)
	{
		return pair.first + ":"+zhttp_hander::Space + pair.second + zhttp_hander::CRLF;
	}
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
	void basecoder::InsertMapIfNotNull(PMap pmap, const pair<string,string> src) {
		if (!src.second.empty()) {
			(*pmap)[src.first] = src.second;
			}
	}
		
}

