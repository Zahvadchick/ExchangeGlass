#include <algorithm>
#include <iostream>

#include "first_version.h"

GlassWithLists::GlassWithLists(int count) {
  if (count < 1) {
    std::cerr << "count of displayed applications must be more than 0";
  }
  best_count_ = count;
}


std::list<Application>* GlassWithLists::get_collection(const Application& app) {
  if (app.is_sale) {
    return &sales_;
  } else {
    return &buys_;
  }
}


std::list<Application>::iterator GlassWithLists::get_position(
    std::list<Application>* collection, const Application& app) {
  return std::upper_bound(collection->begin(), collection->end(), app.cost,
    [](int value, const Application& cur) {
      return value < cur.cost;
    });
}


std::list<Application>::iterator GlassWithLists::find_application(
    std::list<Application>* collection, const Application& app) {
  return std::find_if(collection->begin(), collection->end(),
    [app](const Application& cur)
    {
      return app.id == cur.id;
    });
}


void GlassWithLists::Add(const Application& app) {
  if (applications_.find(app.id) != applications_.end()) {
    std::cerr << "application was created earlier";
    return;
  }

  std::list<Application>* collection = get_collection(app);
  auto iter = get_position(collection, app);
  collection->insert(iter, app);
  applications_[app.id] = app;
  Sell();
}


void GlassWithLists::Change(const Application& app) {
  auto iter = applications_.find(app.id);
  if (iter == applications_.end()) {
    std::cerr << "Cannot change uncreated application";
    return;
  }
    
  if (app.is_sale == (*iter).second.is_sale &&
      (*iter).second.cost == app.cost) {
    std::list<Application>* collection = get_collection(app);
    auto iter = find_application(collection, app);
    *iter = app;
  } else {
    Erase(app);
    Add(app);
  }
  applications_[app.id] = app;
}


void GlassWithLists::Erase(const Application& app) {
  auto finder = applications_.find(app.id);
  if (finder == applications_.end()) {
    std::cerr << "Cannot erase uncreated application";
    return;
  }

  std::list<Application>* collection = get_collection((*finder).second);
  auto iter = find_application(collection, (*finder).second);
  collection->erase(iter);
  applications_.erase(app.id);
}


std::vector<Application> GlassWithLists::BestApplications() {
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


void GlassWithLists::Sell() {
  while (!sales_.empty() && !buys_.empty() &&
         sales_.front().cost <= buys_.back().cost) {
    if (sales_.front().count == buys_.back().count) {
      sales_.pop_front();
      buys_.pop_back();
    } else if (sales_.front().count < buys_.back().count) {
      buys_.back().count -= sales_.front().count;
      sales_.pop_front();
    } else {
      sales_.front().count -= buys_.back().count;
      buys_.pop_back();
    }
  }
}
