#include <iostream>

class Process {
    private: 
        // process attributes
        int id;
        int serviceTime; //might change due to feedback multi queues hopping
        int arrivalTime;

        /// to be calculated
        int finishTime;
        int waitingTime;
        int turnaroundTime;
        int lifeTime;

        void calculateTurnaroundTime(){
            this->turnaroundTime = this->finishTime - this->arrivalTime;
        }

        void calculateWaitingTime(){
            this->waitingTime = this->finishTime - this->arrivalTime - this->serviceTime;
        }

    public:
        static int processCount; //used to assign unique id to each process

        // constructors

        //full constructor
        Process(int arrivalTime, int serviceTime){
            this->id = processCount;
            this->arrivalTime = arrivalTime;
            this->serviceTime = serviceTime;
            this->lifeTime = serviceTime;
            this->finishTime = -1;
            // std::cout << "Process " << this->id << " created" << std::endl;
            processCount++;
        }

        //deconstructor
        ~Process(){
        }

        //copy constructor
        Process(Process &other){
            id = other.id;
            arrivalTime = other.arrivalTime;
            serviceTime = other.serviceTime;
            lifeTime = other.lifeTime;
            finishTime = other.finishTime;
            waitingTime = other.waitingTime;
            turnaroundTime = other.turnaroundTime;
            // std::cout << "Process " << this->id << " created" << std::endl;
        }

        //default constructor
        //used to create placeholder process that will point to an exsiting process later
        Process(){
            this->id = processCount;
            // std::cout << "Process " << this->id << " created" << std::endl;
            processCount++;
        }

        //comparison functions

        // less than operator
        bool operator<(const Process& other) const {
            if (this->lifeTime < other.lifeTime){
                return true;
            }
            return false;
        }

        //print functions
        //prints process attributes
        friend std::ostream& operator<<(std::ostream& os, const Process& obj) {
            if(obj.getFinishTime() == -1){
                os << "ID: " << obj.getID() << " Arrival Time: " << obj.getArrivalTime() << " service Time: " << obj.getServiceTime();
            }
            else { //prints the finish time as well if process is finished
                os << "ID: " << obj.getID() << " Arrival Time: " << obj.getArrivalTime() << " Service Time: " << obj.getServiceTime() << " Finish Time: " << obj.getFinishTime();
            }
            return os;
        }

        //enables swapping two processes
        friend void std::swap(Process& first, Process& second);


        void print(){
            std::cout << *this << std::endl;
        }


        void deductLifeTime(int Q){
            this->lifeTime -= Q;
        }

        /// getters
        int getID() const{
            return this->id;
        }

        int getServiceTime() const{
            return this->serviceTime;
        }

        int getArrivalTime() const{
            return this->arrivalTime;
        }

        int getWaitingTime() const{
            return this->waitingTime;
        }

        int getTurnaroundTime() const{
            return this->turnaroundTime;
        }

        int getLifeTime() const{
            return this->lifeTime;
        }

        int getFinishTime() const{
            return this->finishTime;
        }

        /// setters 

        void setFinishTime(int finishTime){
            this->finishTime = finishTime;
            calculateTurnaroundTime();
            calculateWaitingTime();
        }
};

int Process::processCount = 1; //ID starts from 1

//enable swapping two processes
namespace std {
    template <>
    void swap(Process& first, Process& second) {
        using std::swap;
        swap(first.id, second.id);
        swap(first.arrivalTime, second.arrivalTime);
        swap(first.lifeTime, second.lifeTime);
        swap(first.finishTime, second.finishTime);
        swap(first.serviceTime, second.serviceTime);
        swap(first.waitingTime, second.waitingTime);
        swap(first.turnaroundTime, second.turnaroundTime);
    }
}
