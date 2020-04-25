#pragma once
#define AKANEENGINE_API __declspec(dllexport)

#include <rapidxml-1.13/rapidxml.hpp>
#include <rapidxml-1.13/rapidxml_iterators.hpp>
#include <rapidxml-1.13/rapidxml_print.hpp>
#include <rapidxml-1.13/rapidxml_utils.hpp>
#include <string>

using namespace rapidxml;

class AKANEENGINE_API XMLReader
{
public:
	static xml_document<>* parseXml(std::string filePath);
};

