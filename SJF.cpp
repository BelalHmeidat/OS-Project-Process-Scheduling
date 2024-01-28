class SJF {
private:
	int processCount;
	PriorityQueue<Process> heap;
	Process *processes;

	int sumTurnAroundTime;
	int sumWaitingTime;

public:
	SJF(Process processes[], int processCount): heap(500){
		this->processCount = processCount;
		this->processes = new Process[processCount];
		for (int i = 0; i < processCount; i++){
			this->processes[i] = processes[i];
		}
		sumTurnAroundTime = 0;
		sumWaitingTime = 0;
	}

	//deconstructor
	~SJF(){
		delete[] processes;
	}

	std::pair<float, float> runAlgorithim(){
		ProcessUtility::sortProcesses(processes, processCount);
		heap.insert(processes[0]);
		int time = processes[0].getArrivalTime();
		int nextStopTime = processes[0].getArrivalTime() + processes[0].getServiceTime(); //time when processes might be added or removed from the heap
		int currentProcessIndex = 1;
		while(time < nextStopTime){			// while there are stoll processes to be excuted
			if (currentProcessIndex < processCount && processes[currentProcessIndex].getArrivalTime() <= nextStopTime){
				// if (processes[currentProcessIndex].getArrivalTime() < nextStopTime){
					nextStopTime = processes[currentProcessIndex].getArrivalTime();
				// }
				excuteTopProcess(nextStopTime - time, nextStopTime); //excute the top process in the heap
				heap.insert(processes[currentProcessIndex]); //insert the new process to the heap
				currentProcessIndex++;
			}
			else {
				excuteTopProcess(nextStopTime - time, nextStopTime);
			}
			//if the heap is empty and there are still processes to be added to the heap
			if (heap.isEmpty()){
				if (currentProcessIndex < processCount){
					nextStopTime = processes[currentProcessIndex].getArrivalTime();
					heap.insert(processes[currentProcessIndex]);
					currentProcessIndex++;
				}
				else break;
			}
			Process currentProcess;
			currentProcess = heap.pop();
			time = nextStopTime;
			nextStopTime += currentProcess.getLifeTime();
			heap.insert(currentProcess);
		}
		// std::cout << "Average Turnaround Time: " << sumTurnAroundTime * 1.0 / processCount << std::endl;
		// std::cout << "Average Waiting Time: " << sumWaitingTime * 1.0 / processCount << std::endl;
		std::pair<float, float> result;
		result.first = sumTurnAroundTime * 1.0 / processCount;
		result.second = sumWaitingTime * 1.0 / processCount;
		return result;
	}

	//decreases the life time of the top process in the heap by time
	void excuteTopProcess(int time, int currentTime){
		Process currentProcess;
		currentProcess = heap.pop();
		currentProcess.deductLifeTime(time);
		if (currentProcess.getLifeTime() > 0){
			heap.insert(currentProcess);
		}
		else{
			currentProcess.setFinishTime(currentTime);
			sumTurnAroundTime += currentProcess.getTurnaroundTime();
			sumWaitingTime += currentProcess.getWaitingTime();
			// currentProcess.print();
		}
	}
};