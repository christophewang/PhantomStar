#include "BodyParser.h"

BodyParser* BodyParser::getInstance()
{
	static BodyParser* sg_ptr = nullptr;
	if (nullptr == sg_ptr)
	{
		sg_ptr = new BodyParser;
	}
	return sg_ptr;
}

bool BodyParser::parseJsonFile(const std::string& file)
{
	auto content = FileUtils::getInstance()->getDataFromFile(file);
	bool result = parse(content.getBytes(), content.getSize());
	return result;
}

bool BodyParser::parse(unsigned char *buffer, long length)
{
	bool result = false;
	std::string js(reinterpret_cast<const char*>(buffer), length);
	doc.Parse<0>(js.c_str());
	if (!doc.HasParseError())
	{
		result = true;
	}
	return result;
}

void BodyParser::clearCache()
{
	doc.SetNull();
}

PhysicsBody* BodyParser::bodyFormJson(cocos2d::Node *node, const std::string& name)
{
	PhysicsBody* body = nullptr;
	rapidjson::Value &bodies = doc["rigidBodies"];
	if (bodies.IsArray())
	{
		for (unsigned int i = 0; i < bodies.Size(); ++i)
		{
			if (0 == strcmp(name.c_str(), bodies[i]["name"].GetString()))
			{
				rapidjson::Value &bd = bodies[i];
				if (bd.IsObject())
				{
					body = PhysicsBody::create();
					float width = node->getContentSize().width;
					float offx = -node->getAnchorPoint().x*node->getContentSize().width;
					float offy = -node->getAnchorPoint().y*node->getContentSize().height;

					Point origin(bd["origin"]["x"].GetDouble(), bd["origin"]["y"].GetDouble());
					rapidjson::Value &polygons = bd["polygons"];
					for (unsigned int j = 0; j < polygons.Size(); ++j)
					{
						int pcount = polygons[j].Size();
						Point* points = new Point[pcount];
						for (int pi = 0; pi < pcount; ++pi)
						{
							points[pi].x = offx + width * polygons[j][pcount - 1 - pi]["x"].GetDouble();
							points[pi].y = offy + width * polygons[j][pcount - 1 - pi]["y"].GetDouble();
						}
						body->addShape(PhysicsShapePolygon::create(points, pcount, PHYSICSBODY_MATERIAL_DEFAULT));
						delete[] points;
					}
				}
				else
				{
					CCLOG("body: %s not found!", name.c_str());
				}
				break;
			}
		}
	}
	return body;
}