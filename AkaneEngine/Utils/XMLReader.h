#pragma once
#define AKANEENGINE_API __declspec(dllexport)

#include <rapidxml-1.13/rapidxml.hpp>
#include <string>

using namespace rapidxml;

class AKANEENGINE_API XMLReader
{
public:
	static xml_document<>* parseXml(std::string filePath);
};

