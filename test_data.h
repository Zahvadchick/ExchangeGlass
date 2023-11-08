#pragma once

#include <vector>

#include "application.h"

const int kCount = 10;

namespace test_data {
const std::vector<Application> kApplicationsForSimple{
  {100, 2, 3, true}, {102.5, 2, 2, true}, {90, 2, 4, false}, {104, 2, 1, true},
  {88, 2, 5, false}, {105, 5, 3, true}, {104, 1, 5, true}};

const std::vector<Application> kApplicationsForSell{
  {100, 2, 2, true}, {88, 2, 4, false}, {90, 2, 3, false}, {102.5, 2, 1, true},
  {105, 3, 5, false}, {80, 5, 6, true}};

const std::vector<Application> kApplicationsForManyApplications{
  {195, 2, 21, true}, {189.5, 2, 22, true}, {107, 2, 23, false},
  {float(188), 2, 6, true}, {float(198), 2, 1, true}, {float(196), 2, 2, true},
  {float(186), 2, 7, true}, {float(102), 2, 20, false}};

const std::vector<int> kQueue = {5, 8, 11, 12, 1, 19, 0, 7, 15, 16,
                                 4, 13, 2, 3, 18, 10, 6, 14, 17, 9};


std::vector<Application> get_answer_for_simple() {
  std::vector<Application> answer(kCount * 2);
  answer[7] = kApplicationsForSimple[3];
  answer[8] = kApplicationsForSimple[1];
  answer[9] = kApplicationsForSimple[0];
  answer[10] = kApplicationsForSimple[2];
  answer[11] = kApplicationsForSimple[4];
  return answer;
}

void reset_answer_for_simple_first(std::vector<Application>& answer) {
  answer[7] = {};
}

void reset_answer_for_simple_second(std::vector<Application>& answer) {
  answer[10] = answer[11];
  answer[11] = {};
}

void reset_answer_for_simple_third(std::vector<Application>& answer) {
  answer[9] = answer[8];
  answer[8] = kApplicationsForSimple[5];
}

void reset_answer_for_simple_fourth(std::vector<Application>& answer) {
  answer[7] = answer[8];
  answer[8] = kApplicationsForSimple[6];
  answer[10] = {};
}


std::vector<Application> get_answer_for_sell() {
  std::vector<Application> answer(kCount * 2);
  answer[8] = kApplicationsForSell[3];
  answer[9] = kApplicationsForSell[0];
  answer[10] = kApplicationsForSell[2];
  answer[11] = kApplicationsForSell[1];
  return answer;
}

void reset_answer_for_sell_first(std::vector<Application>& answer) {
  answer[9] = answer[8], answer[9].count = 1;
  answer[8] = {};
}

void reset_answer_for_sell_second(std::vector<Application>& answer) {
  answer[8] = answer[9];
  answer[9] = kApplicationsForSell[5], answer[9].count = 1;
  answer[10] = {};
  answer[11] = {};
}

std::vector<Application> get_answer_for_many_applications() {
  std::vector<Application> answer(kCount * 2);
  for (int i = 1; i < 11; i++) {
    answer[i - 1] = {float(200 - i * 2), 2, i, true};
    answer[kCount * 2 - i] = {float(100 + i * 2), 2, 21 - i, false};
  }
  return answer;
}

void reset_answer_for_many_applications_first(std::vector<Application>& answer) {
  for (int i = 0; i < 4; i++) {
    answer[i] = answer[i + 1];
  }
  for (int i = 19; i > 17; i--) {
    answer[i] = answer[i - 1];
  }
  answer[0] = kApplicationsForManyApplications[0];
  answer[4] = kApplicationsForManyApplications[1];
  answer[17] = kApplicationsForManyApplications[2];
}

void reset_answer_for_many_applications_second(std::vector<Application>& answer) {
  for (int i = 6; i >= 2; i--) {
    answer[i] = answer[i - 2];
  }
  for (int i = 17; i <= 18; i++) {
    answer[i] = answer[i + 1];
  }
  answer[0] = kApplicationsForManyApplications[4];
  answer[1] = kApplicationsForManyApplications[5];
  answer[6] = kApplicationsForManyApplications[6];
  answer[19] = kApplicationsForManyApplications[7];
}
} // namespace test_data