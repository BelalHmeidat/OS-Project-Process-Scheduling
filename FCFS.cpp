class FCFS {
private:
	int processCount;
	Queue<Process> queue;
	Process *processes;

	int sumTurnAroundTime;
	int sumWaitingTime;

public:
	FCFS(Process processes[], int processCount): queue(500){
		this->processCount = processCount;
		this->processes = new Process[processCount];
		for (int i = 0; i < processCount; i++){
			this->processes[i] = processes[i];
		}
		this->sumTurnAroundTime = 0;
		this->sumWaitingTime = 0;
	}

	//deconstructor
	~FCFS(){
		delete[] processes;
	}

	std::pair<double, double> runAlgorithim(){
		ProcessUtility::sortProcesses(processes, processCount);
		try{
			queue.push(processes[0]);
		} catch (const std::out_of_range& e){
			std::cerr << e.what() << std::endl;
		}
		int time = processes[0].getArrivalTime();
		int currentProcessIndex = 1;
		do {
			Process currentProcess;
			try {
				currentProcess = queue.pull();
			}
			catch (const std::out_of_range& e) {
				std::cerr << e.what() << std::endl;
			}	
			currentProcess.deductLifeTime(currentProcess.getServiceTime());
			time += currentProcess.getServiceTime();
			currentProcessIndex = newProcessArrived(currentProcessIndex, time);
			currentProcess.setFinishTime(time);
			// currentProcess.print();
			sumTurnAroundTime += currentProcess.getTurnaroundTime();
			sumWaitingTime += currentProcess.getWaitingTime();
			if (queue.isEmpty()){
				if (currentProcessIndex < processCount){
					time = processes[currentProcessIndex].getArrivalTime();
					try{
						queue.push(processes[currentProcessIndex]);
						currentProcessIndex++;
					}
					catch (const std::out_of_range& e){
						std::cerr << e.what() << std::endl;
					}
				}
				else break;

			}
		}
		while (true);
		std::pair<float, float> result;
		result.first = sumTurnAroundTime * 1.0 / processCount;
		result.second = sumWaitingTime * 1.0 / processCount;
		// std::cout << "Average Turnaround Time: " << sumTurnAroundTime * 1.0 / processCount << std::endl;
		// std::cout << "Average Waiting Time: " << sumWaitingTime * 1.0 / processCount << std::endl;
		return result;
	}

	int newProcessArrived(int currentProcess, int currentTime){
		for (; currentProcess < processCount; currentProcess++){
			if (processes[currentProcess].getArrivalTime() <= currentTime){
				try {
					queue.push(processes[currentProcess]);
				} catch (const std::out_of_range& e){
					std::cerr << e.what() << std::endl;
				}
			}
			else break; //because processes are sorted on their arrival time
		}
		return currentProcess;
	}
};