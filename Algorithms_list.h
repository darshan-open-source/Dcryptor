#pragma once
#include<map>
#include<string>
#include<vector>


typedef std::map<std::string, std::vector<std::string>> algorithm_data;

static algorithm_data aes_data = {
	std::pair<std::string,std::vector<std::string>>("bits",{"128","192","256"}),
	std::pair<std::string,std::vector<std::string>>("modes",{"cbc","ccm","cfb1","cfb8","cfb","ctr","ecb","gcm","ocb","ofb","wrap","wrap_pad","xts"})
};


static algorithm_data aria_data = {
	std::pair<std::string,std::vector<std::string>>("bits",{"128","192","256"}),
	std::pair<std::string,std::vector<std::string>>("modes",{"cbc","ccm","cfb1","cfb8","cfb","ecb","gcm","ofb"})
};


static algorithm_data bf_idea_cast5_data = {
	std::pair<std::string,std::vector<std::string>>("bits",{"unusable"}),
	std::pair<std::string,std::vector<std::string>>("modes",{"cbc","cfb","ecb","ofb"})
};


static algorithm_data camilia_data = {
	std::pair<std::string,std::vector<std::string>>("bits",{"128","192","256"}),
	std::pair<std::string,std::vector<std::string>>("modes",{"cbc","ccm","cfb1","cfb8","cfb","ecb","gcm","ofb"})
};


static algorithm_data des_data = {
	std::pair<std::string,std::vector<std::string>>("bits",{"usable"}),
	std::pair<std::string,std::vector<std::string>>("modes", {"cbc","cfb64","cfb1","cfb8","cfb","ecb"})
};


static algorithm_data rc2_data = {
	std::pair<std::string,std::vector<std::string>>("bits",{"unusable"}),
	std::pair<std::string,std::vector<std::string>>("modes",{"cbc","40 cbc","64 cbc","cfb","cfb64","ecb","ofb"})
};

static algorithm_data rc5_data = {
	std::pair<std::string,std::vector<std::string>>("bits",{"unusable"}),
	std::pair<std::string,std::vector<std::string>>("modes",{"rc5_32_12_16_cbc","rc5_32_12_16_cfb","rc5_32_12_16_cfb64","rc5_32_12_16_ecb","rc5_32_12_16_ofb"})
};

static algorithm_data rc4_data = {
	std::pair<std::string,std::vector<std::string>>("bits",{"unusable"}),
	std::pair<std::string,std::vector<std::string>>("modes",{"rc4","rc4 40","rc4 hmac md5"})
};

static algorithm_data sm4_data = {
	std::pair<std::string,std::vector<std::string>>("bits",{"unusable"}),
	std::pair<std::string,std::vector<std::string>>("modes",{"cbc","ctr","cfb","ecb","ofb"})
};

static std::map<std::string, algorithm_data> all_algorithms = {
	std::pair<std::string,algorithm_data>("aes",aes_data),
	std::pair<std::string,algorithm_data>("aria",aria_data),
	std::pair<std::string,algorithm_data>("Blowfish",bf_idea_cast5_data),
	std::pair<std::string,algorithm_data>("camellia",aes_data),
	std::pair<std::string,algorithm_data>("cast5",bf_idea_cast5_data),
	std::pair<std::string,algorithm_data>("Des",des_data),
	std::pair<std::string,algorithm_data>("triple des",des_data),
	std::pair<std::string,algorithm_data>("idea",bf_idea_cast5_data),
	std::pair<std::string,algorithm_data>("rc2",rc2_data),
	std::pair<std::string,algorithm_data>("rc4",rc4_data),
	std::pair<std::string,algorithm_data>("rc5",rc5_data),
	std::pair<std::string,algorithm_data>("sm4",sm4_data)


};