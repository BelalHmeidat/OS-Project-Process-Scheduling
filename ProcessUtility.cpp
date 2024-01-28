#include<iostream>
// #include <cstdlib>

class ProcessUtility {

private: 
	static void swap(Process& a, Process& b) {
	    Process currentProcess = a;
	    a = b;
	    b = currentProcess;
	}

	static int randomNumber(int min, int max){
		int randNum = rand()%(max-min + 1) + min;
		// std::cout << randNum << std::endl;
		return randNum;
	}

public:

	static Process* generateProcesses(int count){
		Process* processes = new Process[count];
		for (int i = 0; i < count; i++){
			int arrivalTime = randomNumber(0, 300);
			int serviceTime = randomNumber(5, 100);
			Process p(arrivalTime, serviceTime);
			processes[i] = p;
		}
		return processes;
	}

	static void sortProcesses(Process processes[], int n) {
	    for (int i = 0; i < n - 1; ++i) {
	        for (int j = 0; j < n - i - 1; ++j) {
	            if (processes[j].getArrivalTime() > processes[j + 1].getArrivalTime()) {
	                swap(processes[j], processes[j + 1]);
	            }
	        }
	    }
	}

	static bool isProcessFinished(Process* proc){
		if (proc->getLifeTime() == 0){
			return true;
		}
		return false;
	}

	static void printProcesses(Process processes[], int n){
		for (int i =0; i < n; i++){
			processes[i].print();
		}
	}
};