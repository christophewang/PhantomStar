#pragma once

#include "cocos2d.h"
#include "json/document.h"

using namespace cocos2d;

class BodyParser
{
private:
	rapidjson::Document doc;
public:
	static BodyParser* getInstance();
	bool parseJsonFile(const std::string &file);
	bool parse(unsigned char* buffer, long length);
	void clearCache();
	PhysicsBody* bodyFormJson(Node* node, const std::string& name);
};