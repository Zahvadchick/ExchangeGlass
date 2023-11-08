#pragma once

#include <unordered_map>
#include <vector>

#include "application.h"

class GlassWithSort {
 public:
  GlassWithSort(int count);

  void Add(const Application& app);
  void Change(const Application& app);
  void Erase(const Application& app);
  std::vector<Application> BestApplications();

 protected:
  void Sell();
  std::vector<Application>* get_collection(const Application& app);
  std::vector<Application>::iterator find_application(
    std::vector<Application>* collection, const Application& app);

 private:
  std::vector<Application> buys_;
  std::vector<Application> sales_;
  std::unordered_map<int, Application> applications_;
  int best_count_;
};
