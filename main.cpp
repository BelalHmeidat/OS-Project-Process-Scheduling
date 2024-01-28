#include <iostream>
#include "RR.cpp"
#include "FCFS.cpp"
#include "PriorityQueue.cpp"
#include "SJF.cpp"
#include "MLFQ.cpp"
#include <iomanip> //used for setw()
#include <ctime> //used for srand() to set generate seed for rand()
#include <cstdlib> //used for rand() to generate random numbers

void freeFloatArrays(std::pair<float*, float*>& arraysPair) {
    delete[] arraysPair.first;
    delete[] arraysPair.second;
}
//returns a pair of float arrays that contain the average turn around time and average waiting time for each algorithm
std::pair<float*, float*> runAlgorithms(int times, int processCount){
    //initialize values
    float RRTotalTurnAroundTime = 0;
    float RRTotalWaitingTime = 0;

    float FCFSTotalTurnAroundTime = 0;
    float FCFSTotalWaitingTime = 0;

    float SJFTotalTurnAroundTime = 0;
    float SJFTotalWaitingTime = 0;

    float MLFQTotalTurnAroundTime = 0;
    float MLFQTotalWaitingTIme = 0;

    float* turnAroundResults = new float[4];
    float* waitingResults = new float[4];

    //run each algorithm x times
    for (int i=0; i < times; i++){

        Process* processes = ProcessUtility::generateProcesses(processCount);

        RR roundRubin(20, processes, processCount);

        FCFS _1stCome1stServ(processes, processCount);

        SJF shortestJob1st(processes, processCount);

        MLFQ multiLvlFeedbackQ(processes, processCount, 10, 50);
        
        std::pair<float, float> RRresult = roundRubin.runAlgorithim();
        RRTotalTurnAroundTime += RRresult.first;
        RRTotalWaitingTime += RRresult.second;

        std::pair<float, float> FCFSresult = _1stCome1stServ.runAlgorithim();
        FCFSTotalTurnAroundTime += FCFSresult.first;
        FCFSTotalWaitingTime += FCFSresult.second;

        std::pair<float, float> SJFresult = shortestJob1st.runAlgorithim();
        SJFTotalTurnAroundTime += SJFresult.first;
        SJFTotalWaitingTime += SJFresult.second;

        std::pair<float, float> MLFQresult = multiLvlFeedbackQ.runAlgorithim();
        MLFQTotalTurnAroundTime += MLFQresult.first;
        MLFQTotalWaitingTIme += MLFQresult.second;
    }

    //calculate average turn around time and average waiting time for each algorithm
    turnAroundResults[0] = RRTotalTurnAroundTime / times;
    turnAroundResults[1] = FCFSTotalTurnAroundTime / times;
    turnAroundResults[2] = SJFTotalTurnAroundTime / times;
    turnAroundResults[3] = MLFQTotalTurnAroundTime / times;

    waitingResults[0] = RRTotalWaitingTime / times;
    waitingResults[1] = FCFSTotalWaitingTime / times;
    waitingResults[2] = SJFTotalWaitingTime / times;
    waitingResults[3] = MLFQTotalWaitingTIme / times;

    //return a pair of float arrays that contain the average turn around time and average waiting time for each algorithm
    std::pair<float*, float*> result;
    result.first = turnAroundResults;
    result.second = waitingResults;
    return result;
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(0))); //setting the seed

    const int PROCESS_COUNT = 8; //number of processes 

    //run each algorithm x times
    std::pair<float*, float*> _100RunResult = runAlgorithms(100, PROCESS_COUNT);
    std::pair<float*, float*> _1000RunResult = runAlgorithms(1000, PROCESS_COUNT);
    std::pair<float*, float*> _10000RunResult = runAlgorithms(10000, PROCESS_COUNT);
    std::pair<float*, float*> _100000RunResult = runAlgorithms(100000, PROCESS_COUNT);

    //creates a formatted table
    std::cout << "Round Rubin" << std::endl;    
    std::cout << std::left << std::setw(10) << "Time" << std::left << std::setw(10) << "x100" << std::left << std::setw(10) << "x1000" << std::left << std::setw(10) << "x10000" << std::left << std::setw(10) << "x100000" << std::endl;
    std::cout << std::left << std::setw(10) << "ATT" << std::left << std::setw(10) << _100RunResult.first[0] << std::left << std::setw(10) << _1000RunResult.first[0] << std::left << std::setw(10) << _10000RunResult.first[0] << std::left << std::setw(10) << _100000RunResult.first[0] << std::endl;
    std::cout << std::left << std::setw(10) << "AWT" << std::left << std::setw(10) << _100RunResult.second[0] << std::left << std::setw(10) << _1000RunResult.second[0] << std::left << std::setw(10) << _10000RunResult.second[0] << std::left << std::setw(10) << _100000RunResult.second[0] << std::endl;
    std::cout << std::endl;

    std::cout << "First Come First Serve" << std::endl;
    std::cout << std::left << std::setw(10) << "Time" << std::left << std::setw(10) << "x100" << std::left << std::setw(10) << "x1000" << std::left << std::setw(10) << "x10000" << std::left << std::setw(10) << "x100000" << std::endl;
    std::cout << std::left << std::setw(10) << "ATT" << std::left << std::setw(10) << _100RunResult.first[1] << std::left << std::setw(10) << _1000RunResult.first[1] << std::left << std::setw(10) << _10000RunResult.first[1] << std::left << std::setw(10) << _100000RunResult.first[1] << std::endl;
    std::cout << std::left << std::setw(10) << "AWT" << std::left << std::setw(10) << _100RunResult.second[1] << std::left << std::setw(10) << _1000RunResult.second[1] << std::left << std::setw(10) << _10000RunResult.second[1] << std::left << std::setw(10) << _100000RunResult.second[1] << std::endl;
    std::cout << std::endl;

    std::cout << "Shortest Job Time First" << std::endl;
    std::cout << std::left << std::setw(10) << "Time" << std::left << std::setw(10) << "x100" << std::left << std::setw(10) << "x1000" << std::left << std::setw(10) << "x10000" << std::left << std::setw(10) << "x100000" << std::endl;
    std::cout << std::left << std::setw(10) << "ATT" << std::left << std::setw(10) << _100RunResult.first[2] << std::left << std::setw(10) << _1000RunResult.first[2] << std::left << std::setw(10) << _10000RunResult.first[2] << std::left << std::setw(10) << _100000RunResult.first[2] << std::endl;
    std::cout << std::left << std::setw(10) << "AWT" << std::left << std::setw(10) << _100RunResult.second[2] << std::left << std::setw(10) << _1000RunResult.second[2] << std::left << std::setw(10) << _10000RunResult.second[2] << std::left << std::setw(10) << _100000RunResult.second[2] << std::endl;
    std::cout << std::endl;

    std::cout << "Non-Preemptive Multi Level Feedback Queues" << std::endl;
    std::cout << std::left << std::setw(10) << "Time" << std::left << std::setw(10) << "x100" << std::left << std::setw(10) << "x1000" << std::left << std::setw(10) << "10000" << std::left << std::setw(10) << "x100000" << std::endl;
    std::cout << std::left << std::setw(10) << "ATT" << std::left << std::setw(10) << _100RunResult.first[3] << std::left << std::setw(10) << _1000RunResult.first[3] << std::left << std::setw(10) << _10000RunResult.first[3] << std::left << std::setw(10) << _100000RunResult.first[3] << std::endl;
    std::cout << std::left << std::setw(10) << "AWT" << std::left << std::setw(10) << _100RunResult.second[3] << std::left << std::setw(10) << _1000RunResult.second[3] << std::left << std::setw(10) << _10000RunResult.second[3] << std::left << std::setw(10) << _100000RunResult.second[3] << std::endl;

    //frees memory
    freeFloatArrays(_100RunResult);
    freeFloatArrays(_1000RunResult);
    freeFloatArrays(_10000RunResult);
    freeFloatArrays(_100000RunResult);
}


