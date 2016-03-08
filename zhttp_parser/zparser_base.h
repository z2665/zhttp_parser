#pragma once
#include"zhttp_hander.h"
#include<memory>
#include<vector>
#include<string>
namespace zhttp_parser {
	 class  basecoder
	{
	private:
		typedef std::shared_ptr<std::map<std::string, std::string>> PMap;
		typedef std::shared_ptr<zhttp_hander::request> PRequest;
		typedef std::size_t position;
	public:
		basecoder();
		~basecoder();
		static void init();
		//´Óhttp°üÓ³Éäµ½map
		PMap MakeRequestMap(std::string pack);
		PRequest RequestMapToStuct(PMap pmap);
	private:
		std::shared_ptr<std::vector<std::string>> split(std::string  source, std::string condition, bool needLast);	
	};
}