#include "models/Graph.hpp"

std::vector<unsigned> nothing;

void Graph::Add_Comp(std::string &name, unsigned pin_number) {
  if(this->Has_Comp(name)) return;
  this->Comps[name] = nothing;
  std::vector<unsigned> &current = this->Comps[name];
  while(current.size() < pin_number) current.push_back(0);
}

void Graph::Connect(std::string &name, unsigned pin, unsigned net) {
  if(!this->Has_Comp(name)) return;
  if(this->Comps[name][pin]) return;
  if(!this->Has_Net(net)) this->Nets[net] = nothing;
  Target t;
  t.Name = name;
  t.Pin = pin;
  if(this->Nets[net].contains(t)) return;
  this->Nets[net].push_back(t);
  this->Cmps[name][pin] = net;
}

std::vector<std::string> Nbrs(std::string &name) {
  std::vector<std::string> res;
  for(auto &i : this->Comps[name])
    for(auto &j : this->Nets[i]) {
      if(j.Name == name) continue;
      if(res.contains(j.Name)) continue;
      res.push_back(j.Name);
    }
  return res;
}

std::vector<Target> Nbrs(std::string &name, unsigned pin) {
  return this->Nets[this->Comps[name][pin]];
}

bool Graph::Has_Comp(std::string &name) {
  return this->Comps.contains(name);
}

bool Graph::Has_Net(unsigned number) {
  return this->Nets.contains(number);
}
