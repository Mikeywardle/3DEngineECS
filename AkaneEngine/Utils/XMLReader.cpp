#include "XMLReader.h"

xml_document* XMLReader::parseXml(std::string filePath)
{
	xml_document* doc = new xml_document();
	doc->load_file(filePath.c_str());
	return doc;
}