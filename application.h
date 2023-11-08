#pragma once

struct Application {
  float cost;
  int count, id;
  bool is_sale;
};

bool operator<(const Application& left, const Application& right);
