#pragma once
#include"zhttp_hander.h"
#include<memory>
#include<vector>
#include<string>
namespace zhttp_parser {
	 class  basecoder
	{

	public:
		basecoder();
		~basecoder();
		static void init();
		//´Óhttp°üÓ³Éäµ½map
		std::shared_ptr<std::map<std::string, std::string>> MakeRequestMap(std::string pack);
		std::string PackBuffer();
	private:
		std::shared_ptr<std::vector<std::string>> split(std::string  source, std::string condition, bool needLast);
		typedef std::size_t position;
	};
}