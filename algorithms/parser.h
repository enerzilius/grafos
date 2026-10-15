#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

std::string localName(const std::string &name);
std::string parseTag(const std::string &body,
                     std::map<std::string, std::string> &attrs);
bool toId(const std::string &s, uint16_t &out);