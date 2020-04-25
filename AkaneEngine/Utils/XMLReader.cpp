#include "XMLReader.h"

xml_document<>* XMLReader::parseXml(std::string filePath)
{
	xml_document<>* doc = new xml_document<>();
	std::ifstream file(filePath);
	std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc->parse<0>(&buffer[0]);
	return doc;
}