
#include <algorithm>

class MLFQ {
private:
	Process *processes;
	int processCount;
	int q1Time;
	int q2Time;

	Queue<Process> queue1;
	Queue<Process> queue2;
	Queue<Process> queue3;

	int sumTurnAroundTime;
	int sumWaitingTime; //used to calculate average waiting time and turnaround time in runAlgorithim()

public:
	MLFQ(Process processes[], int processCount, int q1, int q2): queue1(processCount), queue2(processCount), queue3(processCount) {
		this->processCount = processCount;
		this->processes = new Process[processCount];
		// this is how arrays are copied in c++
		for (int i = 0; i < processCount; i++){
			this->processes[i] = processes[i];
		}
		this->q1Time = q1;
		this->q2Time = q2;
		this->sumWaitingTime = 0;
		this->sumTurnAroundTime = 0;
	}

	//deconstructor
	~MLFQ(){
		delete[] processes;
	}

	std::pair<float, float> runAlgorithim(){
		ProcessUtility::sortProcesses(processes, processCount);
		try{
			queue1.push(processes[0]);
		} catch(std::out_of_range& e){
			std::cerr << e.what() << std::endl;
		}
		int time = processes[0].getArrivalTime();
		int currentProcessIndex = 1;
		Process currentProcess;
		//processes start at queue1 and leave to queue2 if they are not finished
		//their lifetime is deducted by q1Time
		//time is moved forward as well
		toQueue1: while(!queue1.isEmpty()) {
			try {
				currentProcess = queue1.pull();
			} catch(std::out_of_range& e){
				std::cerr << e.what() <<std::endl;
			}
			int burstTime = std::min(q1Time, currentProcess.getLifeTime());
			currentProcess.deductLifeTime(burstTime);
			time += burstTime;
			currentProcessIndex = newProcessArrived(currentProcessIndex, time);
			if (ProcessUtility::isProcessFinished(&currentProcess)){
				currentProcess.setFinishTime(time);
				// currentProcess.print();
				sumTurnAroundTime += currentProcess.getTurnaroundTime();
				sumWaitingTime += currentProcess.getWaitingTime();
			}
			else {
				try {
					queue2.push(currentProcess);
				} catch (std::out_of_range& e){
					std::cerr << e.what() << std::endl;
				}
			}
		} 
		//processes deployed here get q2Time deducted from their lifetime and moved to queue3 (FCFS)
		while(!queue2.isEmpty()) {
			// std::cout << "Queue2" << std::endl;
			currentProcess = queue2.pull();
			int burstTime = std::min(q2Time, currentProcess.getLifeTime());
			currentProcess.deductLifeTime(burstTime);
			time += burstTime;
			int indexHolder = currentProcessIndex;
			currentProcessIndex = newProcessArrived(currentProcessIndex, time);
			if (ProcessUtility::isProcessFinished(&currentProcess)){
				currentProcess.setFinishTime(time);
				// currentProcess.print();
				sumTurnAroundTime += currentProcess.getTurnaroundTime();
				sumWaitingTime += currentProcess.getWaitingTime();
			}
			else {
				queue3.push(currentProcess);
			}
			if (currentProcessIndex != indexHolder){
				// std::cout << "Back to Queue1" << std::endl;
				goto toQueue1;
			}
		} 
		//FCFS queue processes that start executing here do so till finished
		while(!queue3.isEmpty()) {
			// std::cout << "Queue3" << std::endl;
			currentProcess = queue3.pull();
			int burstTime = currentProcess.getLifeTime();
			currentProcess.deductLifeTime(burstTime);
			time += burstTime;
			currentProcess.setFinishTime(time);
			// currentProcess.print();
			sumTurnAroundTime += currentProcess.getTurnaroundTime();
			sumWaitingTime += currentProcess.getWaitingTime();
			int indexHolder = currentProcessIndex;
			currentProcessIndex = newProcessArrived(currentProcessIndex, time);
			if (currentProcessIndex != indexHolder){
				// std::cout << "Back to Queue1" << std::endl;
				goto toQueue1;
			}
		}
		//if there are late processes that haven't been added to the queue yet
		if (queue1.isEmpty() && queue2.isEmpty() && queue3.isEmpty() && currentProcessIndex < processCount){
			time = processes[currentProcessIndex].getArrivalTime();
			queue1.push(processes[currentProcessIndex]);
			currentProcessIndex++;
			// std::cout << "Back to Queue1" << std::endl;
			goto toQueue1;
		}
		// std::cout << "Average Turnaround Time: " << sumTurnAroundTime * 1.0 / processCount << std::endl;
		// std::cout << "Average Waiting Time: " << sumWaitingTime * 1.0 / processCount << std::endl;
		std::pair<float, float> result;
		result.first = sumTurnAroundTime * 1.0 / processCount;
		result.second = sumWaitingTime * 1.0 / processCount;
		return result;
	}

	int newProcessArrived(int currentProcess, int currentTime){
		for (; currentProcess < processCount; currentProcess++){
			if (processes[currentProcess].getArrivalTime() <= currentTime){
				queue1.push(processes[currentProcess]);
			}
			else break; //because processes are sorted on their arrival time
		}
		return currentProcess;
	}

};