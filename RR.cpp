#include <iostream>
#include <algorithm>
#include "Process.cpp"
#include "Queue.cpp"

class RR {
private: 
	const int qTime; //Quantum time
	int processCount;
	Queue<Process> queue; //ready queue of processes
	Process *processes;

	int sumTurnAroundTime;
	int sumWaitingTime;

public:
	RR(int qTime, Process processes[], int processCount): queue(processCount), qTime(qTime){
		this->processCount = processCount;
		this->processes = new Process[processCount];
		for (int i = 0; i < processCount; i++){
			this->processes[i] = processes[i];
		}
		sumWaitingTime = 0;
		sumTurnAroundTime = 0;
	}

	//deconstructor
	~RR(){
		delete[] processes;
	}

	std::pair<float, float> runAlgorithim(){
		ProcessUtility::sortProcesses(processes, processCount);
		queue.push(processes[0]);
		int time = processes[0].getArrivalTime();
		int currentProcessIndex = 1;
		do {
			Process currentProcess;
			currentProcess = queue.pull();
			int burstTime = std::min(qTime, currentProcess.getLifeTime()); //process is interrupted on qTime or when it finishes
			currentProcess.deductLifeTime(burstTime); //deduct life time
			time += burstTime; //adds time passed to current time
			currentProcessIndex = newProcessArrived(currentProcessIndex, time); //checks if new processes arrived in the meantime and adds them to the ready queue
			if (currentProcess.getLifeTime() != 0){ //if process is not finished yet
				queue.push(currentProcess); //push it back to the queue
			}
			else { //life time = 0
				currentProcess.setFinishTime(time); //set finish time and the turn around time and waiting time
				// currentProcess.print();
				sumTurnAroundTime += currentProcess.getTurnaroundTime(); //add to the sum of algorithm times
				sumWaitingTime += currentProcess.getWaitingTime();
			}
			if(queue.isEmpty()) { 
				if (currentProcessIndex < processCount){ //if there are still processes to be added to the queue (late processes)
					time = processes[currentProcessIndex].getArrivalTime(); //skip to the arrival time of the next process
					queue.push(processes[currentProcessIndex]); // add late process to the queue
					currentProcessIndex++; //increment index
				}
				else break; //algorithm is finished (no more processes to be added to the queue)
			}
		}
		while (true);
		// std::cout << "Average Turnaround Time: " << sumTurnAroundTime * 1.0 / processCount << std::endl;
		// std::cout << "Average Waiting Time: " << sumWaitingTime * 1.0 / processCount << std::endl;
		//calculate and return the average turn around time and waiting time
		std::pair<float, float> result;
		result.first = sumTurnAroundTime * 1.0 / processCount;
		result.second = sumWaitingTime * 1.0 / processCount;
		return result;
	}

	//checks if new processes arrived in the meantime and adds them to the ready queue
	int newProcessArrived(int currentProcess, int currentTime){
		for (; currentProcess < processCount; currentProcess++){ //processes are sorted depending on their arrival time
			if (processes[currentProcess].getArrivalTime() <= currentTime){
				queue.push(processes[currentProcess]);
			}
			else break;
		}
		return currentProcess;
	}
};