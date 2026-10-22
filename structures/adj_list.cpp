#include "adj_list.h"
#include "../utils/parser.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

AdjListGraph::AdjListGraph(bool Undirected) {
  isUndirected = Undirected;
  list = {};
}

AdjListGraph::~AdjListGraph() { list = {}; }

void AdjListGraph::addVertex(uint16_t vertex) {
  list[vertex] = std::vector<uint16_t>();
}

void AdjListGraph::addEdge(uint16_t vertex, uint16_t adjacentVertex) {
  list[vertex].push_back(adjacentVertex);
  if (isUndirected) {
    if (!list[adjacentVertex].empty())
      list[adjacentVertex].push_back(vertex);
    else
      list[adjacentVertex] = std::vector<uint16_t>();
  }
}

void AdjListGraph::readFromTextFile(const std::string &path, bool undirected) {
  isUndirected = undirected;
  list.clear();
  std::ifstream file(path);

  if (!file) {
    std::cout << " [!] Error reading file: [ " << path << " ]\n";
    return;
  }
  std::string line;

  while (std::getline(file, line)) {
    if (line.empty())
      continue;

    std::istringstream iss(line);

    std::string keyToken;
    if (!std::getline(iss, keyToken, ':'))
      continue;

    uint16_t key;
    try {
      key = static_cast<uint16_t>(std::stoi(keyToken));
    } catch (...) {
      continue;
    }

    std::vector<uint16_t> values;
    int v;
    while (iss >> v) {
      values.push_back(static_cast<uint16_t>(v));
    }

    list[key] = std::move(values);
  }
}

void AdjListGraph::readFromGEXFFile(const std::string &path, bool undirected) {
  isUndirected = undirected;
  list.clear();

  std::cout<<"\nREADING GEXF FILE: "<<path<<"\n";

  std::ifstream file(path, std::ios::binary);
  if (!file) {
    std::cout << " [!] Error reading file: [ " << path << " ]\n";
    return;
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  const std::string xml = buffer.str();

  size_t pos = 0;
  while ((pos = xml.find('<', pos)) != std::string::npos) {
    // Comments
    if (xml.compare(pos, 4, "<!--") == 0) {
      size_t end = xml.find("-->", pos + 4);
      if (end == std::string::npos)
        break;
      pos = end + 3;
      continue;
    }
    // CDATA
    if (xml.compare(pos, 9, "<![CDATA[") == 0) {
      size_t end = xml.find("]]>", pos + 9);
      if (end == std::string::npos)
        break;
      pos = end + 3;
      continue;
    }
    // XML declaration / processing instructions
    if (xml.compare(pos, 2, "<?") == 0) {
      size_t end = xml.find("?>", pos + 2);
      if (end == std::string::npos)
        break;
      pos = end + 2;
      continue;
    }

    // Find the closing '>' while ignoring any '>' inside quoted values
    size_t i = pos + 1;
    char quote = 0;
    while (i < xml.size()) {
      char c = xml[i];
      if (quote) {
        if (c == quote)
          quote = 0;
      } else if (c == '"' || c == '\'') {
        quote = c;
      } else if (c == '>') {
        break;
      }
      ++i;
    }
    if (i >= xml.size())
      break; // malformed: no closing '>'

    std::string body = xml.substr(pos + 1, i - pos - 1);
    pos = i + 1;

    if (body.empty() || body[0] == '/' || body[0] == '!')
      continue; // closing tag or DOCTYPE

    std::map<std::string, std::string> attrs;
    std::string name = parseTag(body, attrs);

    if (name == "node") {
      auto it = attrs.find("id");
      uint16_t id;
      if (it != attrs.end() && toId(it->second, id))
        list[id]; // ensure node exists even with no edges
    } else if (name == "edge") {
      auto s = attrs.find("source");
      auto t = attrs.find("target");
      uint16_t from, to;
      if (s == attrs.end() || t == attrs.end() || !toId(s->second, from) ||
          !toId(t->second, to))
        continue;

      list[from].push_back(to);
      list[to]; // ensure target exists
      if (undirected && from != to)
        list[to].push_back(from);
    }
  }
}

void AdjListGraph::print() {
  std::map<uint16_t, std::vector<uint16_t>>::iterator iterator;
  std::cout<<"\nADJACENCY LIST GRAPH";
  for (iterator = list.begin(); iterator != list.end(); iterator++) {
    std::cout << "\n" << iterator->first << ":";
    if (iterator->second.empty())
      continue;
    for (const uint16_t &vertex : iterator->second) {
      std::cout << " " << vertex;
    }
  }
  std::cout << "\n";
}

void AdjListGraph::reverseGraph() {
  if (isUndirected)
    return;

  std::map<uint16_t, std::vector<uint16_t>> reversed;

  for (auto &[vertex, value] : list) {
    if (reversed[vertex].empty())
      reversed[vertex] = std::vector<uint16_t>();
    for (auto it = value.begin(); it != value.end(); ++it) {
      reversed[*it].push_back(vertex);
    }
  }

  list = std::move(reversed);
}

void AdjListGraph::clearGraph() {
  list.clear();
  isUndirected = false;
}
