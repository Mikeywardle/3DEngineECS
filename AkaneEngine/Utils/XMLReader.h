#pragma once
#define AKANEENGINE_API __declspec(dllexport)

#include <pugixml/pugixml.hpp>
#include <string>

using namespace pugi;

class AKANEENGINE_API XMLReader
{
public:
	static xml_document* parseXml(std::string filePath);
};

