#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

std::string localName(const std::string &name) {
  size_t colon = name.find(':');
  return colon == std::string::npos ? name : name.substr(colon + 1);
}

// Parse the attributes of a tag body like: node id="0" label="Hello" /
// `body` is the text between '<' and '>'. Returns the tag name.
std::string parseTag(const std::string &body,
                     std::map<std::string, std::string> &attrs) {
  size_t i = 0, n = body.size();

  // Tag name
  while (i < n && !std::isspace(static_cast<unsigned char>(body[i])) &&
         body[i] != '/')
    ++i;
  std::string name = localName(body.substr(0, i));

  // Attributes
  while (i < n) {
    while (i < n && (std::isspace(static_cast<unsigned char>(body[i])) ||
                     body[i] == '/'))
      ++i;
    if (i >= n)
      break;

    size_t nameStart = i;
    while (i < n && body[i] != '=' &&
           !std::isspace(static_cast<unsigned char>(body[i])) && body[i] != '/')
      ++i;
    std::string attrName = localName(body.substr(nameStart, i - nameStart));

    while (i < n && std::isspace(static_cast<unsigned char>(body[i])))
      ++i;
    if (i >= n || body[i] != '=')
      continue; // attribute without a value; ignore
    ++i;          // skip '='
    while (i < n && std::isspace(static_cast<unsigned char>(body[i])))
      ++i;
    if (i >= n || (body[i] != '"' && body[i] != '\''))
      continue;

    char quote = body[i++];
    size_t valStart = i;
    while (i < n && body[i] != quote)
      ++i;
    attrs[attrName] = body.substr(valStart, i - valStart);
    if (i < n)
      ++i; // skip closing quote
  }
  return name;
}

// Convert a string to uint16_t; returns false if invalid or out of range
bool toId(const std::string &s, uint16_t &out) {
  try {
    size_t used = 0;
    unsigned long v = std::stoul(s, &used);
    if (used != s.size() || v > UINT16_MAX)
      return false;
    out = static_cast<uint16_t>(v);
    return true;
  } catch (...) {
    return false;
  }
}