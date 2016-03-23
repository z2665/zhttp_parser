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
		//从http包映射到map
		PMap MakeRequestMap(std::string pack);
		//生成结构体
		PRequest RequestMapToStuct(PMap pmap);
		//生成string
		std::string RequestMapToString(PMap pmap);
	private:
		//字符串分割
		std::shared_ptr<std::vector<std::string>> split(std::string  source, std::string condition, bool needLast);	
		//创建request头的行
		std::string makeRow(decltype(*HttpMap::iterator()) pair);
	
	};
}