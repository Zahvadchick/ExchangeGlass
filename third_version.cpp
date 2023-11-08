#include <algorithm>
#include <iostream>

#include "third_version.h"

GlassWithSort::GlassWithSort(int count) {
  if (count < 1) {
    std::cerr << "count of displayed applications must be more than 0";
  }
  best_count_ = count;
}


std::vector<Application>* GlassWithSort::get_collection(const Application& app) {
  if (app.is_sale) {
    return &sales_;
  }
  else {
    return &buys_;
  }
}


void GlassWithSort::Add(const Application& app) {
  if (applications_.find(app.id) != applications_.end()) {
    std::cerr << "application was created earlier";
    return;
  }

  std::vector<Application>* collection = get_collection(app);
  collection->push_back(app);
  applications_[app.id] = app;
}


std::vector<Application>::iterator GlassWithSort::find_application(
  std::vector<Application>* collection, const Application& app) {
  return std::find_if(collection->begin(), collection->end(),
    [app](const Application& cur)
    {
      return app.id == cur.id;
    });
}


void GlassWithSort::Change(const Application& app) {
  auto iter = applications_.find(app.id);
  if (iter == applications_.end()) {
    std::cerr << "Cannot change uncreated application";
    return;
  }

  Erase(app);
  Add(app);
  applications_[app.id] = app;
}


void GlassWithSort::Erase(const Application& app) {
  auto finder = applications_.find(app.id);
  if (finder == applications_.end()) {
    std::cerr << "Cannot erase uncreated application";
    return;
  }

  std::vector<Application>* collection = get_collection((*finder).second);
  auto iter = find_application(collection, (*finder).second);
  collection->erase(iter);
  applications_.erase(app.id);
}


std::vector<Application> GlassWithSort::BestApplications() {
  std::sort(sales_.rbegin(), sales_.rend());
  std::sort(buys_.begin(), buys_.end());
  Sell();
  std::vector<Application> result(20);
  auto sale_iter = sales_.rbegin();
  auto buy_iter = buys_.rbegin();

  for (int diff = 0; diff < best_count_; diff++) {
    if (sale_iter != sales_.rend()) {
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


void GlassWithSort::Sell() {
  while (!sales_.empty() && !buys_.empty() &&
      sales_.back().cost <= buys_.back().cost) {
    if (sales_.back().count == buys_.back().count) {
      sales_.pop_back();
      buys_.pop_back();
    } else if (sales_.back().count < buys_.back().count) {
      buys_.back().count -= sales_.back().count;
      sales_.pop_back();
    } else {
      sales_.back().count -= buys_.back().count;
      buys_.pop_back();
    }
  }
}
