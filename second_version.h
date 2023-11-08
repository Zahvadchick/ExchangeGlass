#pragma once

#include <set>
#include <unordered_map>
#include <vector>

#include "application.h"

class GlassWithSets {
 public:
  GlassWithSets(int count);

  void Add(const Application& app);
  void Change(const Application& app);
  void Erase(const Application& app);
  std::vector<Application> BestApplications();

 protected:
  void Sell();
  std::set<Application>* get_collection(const Application& app);

 private:
  std::set<Application> buys_;
  std::set<Application> sales_;
  std::unordered_map<int, Application> applications_;
  int best_count_;
};
