#include <iostream>
#include <fstream>
#include "rapidxml.hpp"
#include <cstdlib>
#include <cstring>

using namespace rapidxml;
using namespace std;

class Parser
{
protected:
  ifstream   xml_file;
  char      *buffor;
  uint32_t   length;
public:
  xml_document<> doc;
  Parser();
  virtual ~Parser();
  Parser(const Parser&);
  virtual void SetOrGet() = 0;
};

Parser::Parser()
{
  xml_file.open("doc/date.xml");
  xml_file.seekg(0, xml_file.end);
  length = xml_file.tellg();
  xml_file.seekg(0, xml_file.beg);

  buffor = new char[length+1];
  xml_file.read(buffor, length);
  buffor[length] = '\0';
  doc.parse<0>(buffor);
  xml_file.close();
}

Parser::Parser(const Parser& copy)
{
  buffor = new char[length+1];
  strcpy(buffor, copy.buffor);
}

Parser::~Parser()
{
  delete[] buffor;
}

class Parser_read : virtual public Parser
{
public:
  Parser_read() : Parser() {};
  void SetOrGet();
};

void Parser_read::SetOrGet()
{
  xml_node<>* root_node = doc.first_node("Date");

  for(xml_node<>* Person_node = root_node->first_node("Person");
      Person_node;
      Person_node = Person_node->next_sibling())
  {
    for(xml_attribute<>* Person_attribute = Person_node->first_attribute("who");
       Person_attribute;
       Person_attribute = Person_attribute->next_attribute())
   {
     cout<<Person_attribute->value()<<"     ";
   }
    cout<<endl;
    xml_node<>* ability_node = Person_node->first_node("ability");
    for(xml_attribute<>* Abi_attr = ability_node->first_attribute();
        Abi_attr;
        Abi_attr = Abi_attr->next_attribute())
    {
      cout<<Abi_attr->value()<<"    ";
    }
    cout<<endl;
    ability_node = ability_node->next_sibling();
    for(xml_attribute<>* sol_attr = ability_node->first_attribute();
        sol_attr;
        sol_attr = sol_attr->next_attribute())
    {
      cout<<sol_attr->value()<<"     ";
    }
    cout<<endl;
    ability_node = ability_node->next_sibling();
    for(xml_attribute<>* cont_attr = ability_node->first_attribute();
        cont_attr;
        cont_attr = cont_attr->next_attribute())
    {
      cout<<cont_attr->value()<<"    ";
    }
    cout<<endl;
  }
}


int main()
{
  Parser *OBJ;
  OBJ = new Parser_read;
  OBJ->SetOrGet();
  return 0;
}
