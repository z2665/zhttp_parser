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
	shared_ptr<map<string, string>> basecoder::MakeRequestMap(string pack) {
		//��crfl�ָ��ַ���
		shared_ptr<map<string, string>> requestMap = make_shared<map<string, string>>();
		auto vl= split(pack, zhttp_hander::CRLF,false);
		auto vlhead = split((*vl)[0], " ",true);
		//http����һ��
		(*requestMap)["Options"] = (*vlhead)[0];
		(*requestMap)["URL"] = (*vlhead)[1];
		//http��requestheader
		for (auto i = vl->begin() + 1; !i->empty(); ++i) {
			position pos = i->find(':');
			//pos+2����������֮��Ŀո�
			(*requestMap)[i->substr(0,pos)] = i->substr(pos+2);
		}
		//requestbody

		return requestMap;
	}
	string basecoder::PackBuffer() {
		return string();
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

