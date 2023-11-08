#pragma once

#include <chrono>
#include <iostream>
#include <string>

#include "first_version.h"

template <typename Glass>
int SimpleTest(Glass glass);

template <typename Glass>
int SellTest(Glass glass);

template <typename Glass>
int ManyApplicationsTest(Glass glass);

template <typename Glass>
void SpeedTest(Glass glass);

class TestRunner {
 public:
	template <typename Glass>
	TestRunner(Glass glass, const std::string& test_name);
	~TestRunner();

 private:
	int fail_count = 0;
	std::chrono::steady_clock::time_point start;
};

void test();
