#pragma once
#include"zhttp_hander.h"
#include<memory>
#include<vector>
#include<string>
namespace zhttp_parser {
	 class  basecoder
	{
	private:
		typedef std::map<std::string, std::string> HttpMap;
		typedef std::shared_ptr<HttpMap> PMap;
		typedef std::shared_ptr<zhttp_hander::request> PRequest;
		typedef std::size_t position;
	public:
		basecoder();
		~basecoder();
		static void init();
		//��http��ӳ�䵽map
		PMap MakeRequestMap(std::string pack);
		//���ɽṹ��
		PRequest RequestMapToStuct(PMap pmap);
		//����string
		std::string RequestMapToString(PMap pmap);
	private:
		//�ַ����ָ�
		std::shared_ptr<std::vector<std::string>> split(std::string  source, std::string condition, bool needLast);	
		//����requestͷ����
		std::string makeRow(decltype(*HttpMap::iterator()) pair);
	
	};
}