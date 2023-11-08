#include <iostream>

#include "second_version.h"

bool operator<(const Application& left, const Application& right) {
  return left.cost == right.cost && left.id < right.id ||
    left.cost < right.cost;
}


GlassWithSets::GlassWithSets(int count) {
  if (count < 1) {
    std::cerr << "count of displayed applications must be more than 0";
  }
  best_count_ = count;
}


std::set<Application>* GlassWithSets::get_collection(const Application& app) {
  if (app.is_sale) {
    return &sales_;
  }
  else {
    return &buys_;
  }
}


void GlassWithSets::Add(const Application& app) {
  if (applications_.find(app.id) != applications_.end()) {
    std::cerr << "application was created earlier";
    return;
  }

  std::set<Application>* collection = get_collection(app);
  collection->insert(app);
  applications_[app.id] = app;
}


void GlassWithSets::Change(const Application& app) {
  auto iter = applications_.find(app.id);
  if (iter == applications_.end()) {
    std::cerr << "Cannot change uncreated application";
    return;
  }

  Erase(app);
  Add(app);
}


void GlassWithSets::Erase(const Application& app) {
  auto finder = applications_.find(app.id);
  if (finder == applications_.end()) {
    std::cerr << "Cannot erase uncreated application";
    return;
  }

  std::set<Application>* collection = get_collection((*finder).second);
  collection->erase((*finder).second);
  applications_.erase(app.id);
}


std::vector<Application> GlassWithSets::BestApplications() {
  Sell();
  std::vector<Application> result(20);
  auto sale_iter = sales_.begin();
  auto buy_iter = buys_.rbegin();
  for (int diff = 0; diff < best_count_; diff++) {
    if (sale_iter != sales_.end()) {
      result[best_count_ - diff - 1] = *sale_iter;
      sale_iter++;
    }

    if (buy_iter != buys_.rend()) {
      result[best_count_ + diff] = *buy_iter;
      buy_iter++;
    }
  }
  return result;
}


void GlassWithSets::Sell() {
  while (!sales_.empty() && !buys_.empty() &&
      (*sales_.begin()).cost <= (*buys_.rbegin()).cost) {
    if ((*sales_.begin()).count == (*buys_.rbegin()).count) {
      Erase(*sales_.begin());
      Erase(*buys_.rbegin());
    } else if ((*sales_.begin()).count < (*buys_.rbegin()).count) {
      auto app = *buys_.rbegin();
      app.count -= (*sales_.begin()).count;
      Change(app);
      Erase(*sales_.begin());
    } else {
      auto app = *sales_.begin();
      app.count -= (*buys_.rbegin()).count;
      Change(app);
      Erase(*buys_.rbegin());
    }
  }
}
