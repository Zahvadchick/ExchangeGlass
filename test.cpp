#include <vector>

#include "test_data.h"
#include "first_version.h"
#include "second_version.h"
#include "test.h"
#include "third_version.h"

std::ostream& operator<<(std::ostream& out, const std::vector<Application>& v) {
	for (size_t i = 0; i < v.size(); i++) {
		if (i != 0) {
			out << " ";
		}
		if (v[i].id == 0) {
			out << "-";
		} else {
			out << v[i].id;
		}
	}
	return out;
}


bool operator==(const std::vector<Application>& left,
								const std::vector<Application>& right) {
	if (left.size() != right.size()) {
		return false;
	}

	for (size_t ind = 0; ind < left.size(); ind++) {
		if (left[ind].cost != right[ind].cost ||
			left[ind].count != right[ind].count ||
			left[ind].id != right[ind].id ||
			left[ind].is_sale != right[ind].is_sale) {
			return false;
		}
	}
	return true;
}


template<typename T>
bool Assert(const T& res, const T& ans, const std::string& test_name,
						const std::string& hint) {
	if (res != ans) {
		std::cout << "\nAssertion failed : \n" << res << " != \n" << ans <<
								 "\nhint: " << hint << "\n";
		return true;
	}
	return false;
}


template <typename Glass>
int SimpleTest(Glass glass) {
	int fail_count = 0;

	std::vector<Application> answer = test_data::get_answer_for_simple();
	for (int i = 0; i < 5; i++) {
		glass.Add(test_data::kApplicationsForSimple[i]);
	}
	fail_count += Assert(glass.BestApplications(), answer, "SimpleTest",
											 "add 3 sale and 2 buy applications");

	glass.Erase(test_data::kApplicationsForSimple[3]);
	test_data::reset_answer_for_simple_first(answer);
	fail_count += Assert(glass.BestApplications(), answer, "SimpleTest",
											 "erase application with id = 1");

	glass.Erase(test_data::kApplicationsForSimple[2]);
	test_data::reset_answer_for_simple_second(answer);
	fail_count += Assert(glass.BestApplications(), answer, "SimpleTest",
											 "erase application with id = 4");

	glass.Change(test_data::kApplicationsForSimple[5]);
	test_data::reset_answer_for_simple_third(answer);
	fail_count += Assert(glass.BestApplications(), answer, "SimpleTest",
											 "change application with id = 3, application with id = 2"
											 " and 3 swap position");

	glass.Change(test_data::kApplicationsForSimple[6]);
	test_data::reset_answer_for_simple_fourth(answer);
	fail_count += Assert(glass.BestApplications(), answer, "SimpleTest",
											 "change application with id = 5, this application change"
											 " type from buy to sale");

	return fail_count;
}


template <typename Glass>
int SellTest(Glass glass) {
	int fail_count = 0;

	std::vector<Application> answer = test_data::get_answer_for_sell();
	for (int i = 0; i < 4; i++) {
		glass.Add(test_data::kApplicationsForSell[i]);
	}
	fail_count += Assert(glass.BestApplications(), answer, "SellTest",
											 "add 2 sale and 2 buy applications");

	glass.Add(test_data::kApplicationsForSell[4]);
	test_data::reset_answer_for_sell_first(answer);
	fail_count += Assert(glass.BestApplications(), answer, "SellTest",
											 "add buy application, part of applications from sale had"
											 " to be sold");

	glass.Add(test_data::kApplicationsForSell[5]);
	test_data::reset_answer_for_sell_second(answer);
	fail_count += Assert(glass.BestApplications(), answer, "SellTest",
											 "add sale application,  all applications from buy had to"
											 " be bought");

	return fail_count;
}


template <typename Glass>
int ManyApplicationsTest(Glass glass) {
	int fail_count = 0;

	std::vector<Application> answer =
		  test_data::get_answer_for_many_applications();
	for (int ind : test_data::kQueue) {
		glass.Add(answer[ind]);
	}
	fail_count += Assert(glass.BestApplications(), answer, "ManyApplicationsTest",
											 "add 10 sale and 10 buy applications");

	for (int i = 0; i < 3; i++) {
		glass.Add(test_data::kApplicationsForManyApplications[i]);
	}
	test_data::reset_answer_for_many_applications_first(answer);
	fail_count += Assert(glass.BestApplications(), answer, "ManyApplicationsTest",
											 "add 2 sale and 1 buy applications, best applications"
											 " list must be changed");

	for (int i = 1; i < 4; i++) {
		glass.Erase(test_data::kApplicationsForManyApplications[i]);
	}
	test_data::reset_answer_for_many_applications_second(answer);
	fail_count += Assert(glass.BestApplications(), answer, "ManyApplicationsTest",
		"add 2 sale and 1 buy applications, best applications"
		" list must be changed");

	return fail_count;
}


template <typename Glass>
void SpeedTest(Glass glass) {
	for (int id = 1; id < 10000; id++) {
		glass.Add({ float(id), 1, id, true });
	}

	for (int id = 1; id < 10000; id++) {
		glass.Change({ float(id), 3, id, true });
	}

	for (int id = 10000; id < 30000; id++) {
		glass.Add({ float(id), 2, id, false });
	}

	for (int id = 26700; id < 29000; id++) {
		glass.Erase({ float(id), 2, id, false });
	}

	for (int id = 1; id < 10000; id++) {
		glass.BestApplications();
	}
}


template <typename Glass>
TestRunner::TestRunner(Glass glass, const std::string& test_name) {
	start = std::chrono::steady_clock::now();
	std::cout << test_name << ":";
	fail_count += SimpleTest(glass);
	fail_count += SellTest(glass);
	fail_count += ManyApplicationsTest(glass);
	SpeedTest(glass);
}


TestRunner::~TestRunner() {
	if (fail_count == 0) {
		std::cout << " all tests were successful\n\n";
	} else {
		std::cerr << "\nSummary has " << std::to_string(fail_count) <<
			" wrong answers\n\n";
	}

	auto end = std::chrono::steady_clock::now();
	int duration =
		std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << "Total duration: " << duration << " ms\n";
	std::cout << "-------------------------------------------------------\n\n\n";
}


void test() {
	TestRunner(GlassWithLists(kCount), "First version");
	TestRunner(GlassWithSets(kCount), "Second version");
	TestRunner(GlassWithSort(kCount), "Third version");
}
