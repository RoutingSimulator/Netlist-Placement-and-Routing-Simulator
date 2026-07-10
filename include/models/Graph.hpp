#ifndef GRAPH
#define GRAPH

#include <string>
#include <vector>
#include <map>

struct Target {
  std::string Name;
  unsigned Pin;
}

class Graph {
public:
  std::map<std::string, std::vector<unsigned>> Comps;
  std::map<unsigned, std::vector<Target>> Nets;
  
  void Add_Comp(std::string &name, unsigned pin_number);
  void Connect(std::string &name, unsigned pin, unsigned net);
  std::vector<std::string> Nbrs(std::string &name);
  std::vector<Target> Nbrs(std::string &name, unsigned pin);
  
  bool Has_Comp(std::string &name);
  bool Has_Net(unsigned number);
}

#endif
