#pragma once

#include <list>
#include <unordered_map>
#include <vector>

#include "application.h"

class GlassWithLists {
 public:
  GlassWithLists(int count);

  void Add(const Application& app);
  void Change(const Application& app);
  void Erase(const Application& app);
  std::vector<Application> BestApplications();

 protected:
  void Sell();
  std::list<Application>* get_collection(const Application& app);
  std::list<Application>::iterator get_position(
    std::list<Application>* collection, const Application& app);
  std::list<Application>::iterator find_application(
    std::list<Application>* collection, const Application& app);

 private:
  std::list<Application> buys_;
  std::list<Application> sales_;
  std::unordered_map<int, Application> applications_;
  int best_count_;
};
