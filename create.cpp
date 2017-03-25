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
  char *buff = new char[100];
  xml_document<> doc;
  doc.parse<0>(buff);

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

  ofstream file_xml("doc/file2.xml");
  file_xml<<doc;
  file_xml.close();
  doc.clear();
  
  return 0;
}
