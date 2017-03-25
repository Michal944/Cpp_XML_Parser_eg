#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include <sstream>

using namespace rapidxml;
using namespace std;
int main()
{
 // ofstream fileXML;
 // fileXML.open("doc/new.xml");
  xml_document<> doc;

  xml_node<>* xml_dec = doc.allocate_node(node_declaration);
  xml_dec->append_attribute(doc.allocate_attribute("version","1.0"));
  xml_dec->append_attribute(doc.allocate_attribute("encoding","utf-8"));
  doc.append_node(xml_dec);

  xml_node<>* root = doc.allocate_node(node_element, "rootDate");
  doc.append_node(root);
  
  xml_node<>* child = doc.allocate_node(node_element, "child");
  child->append_attribute(doc.allocate_attribute("name","Martin"));
  root->append_node(child);

  xml_node<>* down = doc.allocate_node(node_element, "down_2");
  down->append_attribute(doc.allocate_attribute("test","12345"));
  child->append_node(down);

  ofstream file_xml("doc/file3.xml");
 // char* buffor;
  //doc
  file_xml<<doc;
  file_xml.close();
  doc.clear();

  //xml_document<> doc;
  ifstream open_file;
  open_file.open("doc/file3.xml");
  open_file.seekg(0, open_file.end);
  uint16_t length = open_file.tellg();
  open_file.seekg(0, open_file.beg);
  char* buffor = new char[length+1];
  open_file.read(buffor, length);

  buffor[length]='\0';

  open_file.close();

  doc.parse<0>(buffor);
  xml_node<>* root_e = doc.first_node("rootDate");
  
  xml_node<>* child_e = root_e->first_node("child");
  xml_attribute<>* atr_child = child_e->first_attribute();
  
  atr_child->value("EXAMPLEx2");
  ofstream save_file("doc/file3_a.xml");
  save_file<<doc;
  save_file.close();
  delete[] buffor;

  
  return 0;
}
