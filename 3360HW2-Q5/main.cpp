#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <unordered_map>
using namespace std;
/*
	two servers are mirrors of each other (one fails, other keeps going)
	each server has MTBF (Mean Time Between Failure) of 500 hours, follow exponential distribution
	when a server fails, it takes 10 hours to update/restore data from the other server

	a) write a program that generates synthetic data showing the failure and restoration times 
	for each server over a period of 20 years

	b) find how long it takes until both servers fail within the 10 restoration of either or
	need to simulate this various times and compute the average

*/

void function_a() {
	random_device rd;
	mt19937 generator(rd());
	uniform_real_distribution<double> uniform_dist(0.000001, 1.0);

	int MTBF = 500;
	double lambda = 1.0 / MTBF;
	int hours_year = 8760;
	int twenty_years = 20 * hours_year;
	int restore_time = 10;
	double current_time_server_one = 0.0;
	double current_time_server_two = 0.0;

	unordered_map<string, vector<double>> events;
	events["Server1_failures"] = vector<double>();
	events["Server1_restores"] = vector<double>();
	events["Server2_failures"] = vector<double>();
	events["Server2_restores"] = vector<double>();

	while (current_time_server_one < twenty_years || current_time_server_two < twenty_years) {
		if (current_time_server_one < twenty_years) {
			double u_server_one = uniform_dist(generator);
			double fail_hour_server_one = (-1/lambda) * log(u_server_one);
			current_time_server_one += fail_hour_server_one;
			if (current_time_server_one >= twenty_years)
				break;
			events["Server1_failures"].push_back(current_time_server_one);
			current_time_server_one += 10;
			if (current_time_server_one >= twenty_years)
				break;
			events["Server1_restores"].push_back(current_time_server_one);
		}
		if (current_time_server_two < twenty_years) {
			double u_server_two = uniform_dist(generator);
			double fail_hour_server_two = (-1/lambda) * log(u_server_two);
			current_time_server_two += fail_hour_server_two;
			if (current_time_server_two >= twenty_years)
				break;
			events["Server2_failures"].push_back(current_time_server_two);
			current_time_server_two += 10;
			if (current_time_server_two >= twenty_years)
				break;
			events["Server2_restores"].push_back(current_time_server_two);
		}
	}
	size_t max_size = max({ events["Server1_failures"].size(), events["Server1_restores"].size(),
		events["Server2_failures"].size(), events["Server2_restores"].size() });

	cout << "S1 Fail Time" << setw(20) << "S1 Res Time " << setw(20)
		 << "S2 Fail Time " << setw(20) << "S2 Res Time " << endl;
	for (size_t i = 0; i < max_size; i++) {
		if (i < events["Server1_failures"].size()) {
			cout << events["Server1_failures"][i];
		}
		else {
			cout  << "N/A";
		}

		if (i < events["Server1_restores"].size()) {
			cout << std::setw(20) << events["Server1_restores"][i];
		}
		else {
			cout << std::setw(20) << "N/A";
		}

		if (i < events["Server2_failures"].size()) {
			cout << std::setw(20) << events["Server2_failures"][i];
		}
		else {
			cout << std::setw(20) << "N/A";
		}

		if (i < events["Server2_restores"].size()) {
			cout << std::setw(20) << events["Server2_restores"][i];
		}
		else {
			cout << std::setw(20) << "N/A";
		}

		cout << std::endl;
	}


}
void function_b() {
	random_device rd;
	mt19937 generator(rd());
	uniform_real_distribution<double> uniform_dist(0.000001, 1.0);

	int MTBF = 500;
	double lambda = 1.0 / MTBF;
	int hours_year = 8760;
	int twenty_years = 20 * hours_year;
	int restore_time = 10;
	double total_time_to_failures = 0.0;
	int num_simulations = 0;
	bool system_failed = false;

	while (!system_failed && num_simulations < 100) { // Simulate until failure or 100 tries
		num_simulations++;
		double current_time_server_one = 0.0;
		double current_time_server_two = 0.0;

		vector<double> server1_failures, server2_failures;

		while (current_time_server_one < twenty_years || current_time_server_two < twenty_years) {
			if (current_time_server_one < twenty_years) {
				double u_server_one = uniform_dist(generator);
				double fail_hour_server_one = (-1 / lambda) * log(u_server_one);
				current_time_server_one += fail_hour_server_one;
				if (current_time_server_one >= twenty_years) break;
				server1_failures.push_back(current_time_server_one);
				current_time_server_one += restore_time; 
			}
			if (current_time_server_two < twenty_years) {
				double u_server_two = uniform_dist(generator);
				double fail_hour_server_two = (-1 / lambda) * log(u_server_two);
				current_time_server_two += fail_hour_server_two;
				if (current_time_server_two >= twenty_years) break;
				server2_failures.push_back(current_time_server_two);
				current_time_server_two += restore_time;  
			}
		}

		// Check for failures within the 10-hour window
		for (double s1_fail_time : server1_failures) {
			for (double s2_fail_time : server2_failures) {
				if (abs(s1_fail_time - s2_fail_time) <= restore_time) {
					total_time_to_failures += max(s1_fail_time, s2_fail_time);
					system_failed = true;
					break;
				}
			}
			if (system_failed) break;
		}
	}

	if (system_failed) {
		cout << "Systems failed within 10-hour window after " << total_time_to_failures / num_simulations << " hours on average." << endl;
	}
	else {
		cout << "No failures occurred within the time span of 20 years after 100 simulations." << endl;
	}
}
int main() {
	int choice = 0;
	cout << "Enter 1 to answer question 5a" << endl;
	cout << "Enter 2 to answer question 5b" << endl;
	cin >> choice;
	if (choice == 1)
		function_a();
	else if (choice == 2)
		function_b();
	return 0;
}