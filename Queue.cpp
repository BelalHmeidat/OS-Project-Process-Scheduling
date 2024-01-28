#include <iostream>
#include "ProcessUtility.cpp"
template <typename T> class Queue {
	private:

		T *queue;
		int length;
		int top;
		int bottom;
		int count;

		void clear(){
			top = bottom;
			count = 0;
		}

	public:

		Queue(int length=500){
			this->queue = new T[length];
			this->length = length;
			top = 0;
			bottom = 0;
			count = 0;
		}

		~Queue(){
			delete[] queue;
		}

		void push(T item){
			if (isFull()){
				std::cout << "Queue is full!" << std::endl;
			}
			else{
				queue[bottom] = item;
				bottom = (bottom + 1) % length;
				count++;
				// printQueue();
			}
		}

		T pull(){
			if (!isEmpty()){
				T item = queue[top];
				top = (top + 1) % length;
				count--;
				// printQueue();
				return item;
			}
			else {
            	throw std::out_of_range("Queue is empty!");
        	}
		}

		bool isFull(){
			if (count == length){
				return true;
			}
			return false;
		}

		bool isEmpty(){
			if (count == 0){
				return true;
			}
			return false;
		}

		void printQueue(){
			for (int i = 0; i < count; i++){
				std::cout << queue[(top + i) % length] << std::endl;
			}
			std::cout << "top " << top << std::endl;
			std::cout << "bottom " << bottom << std::endl;
			std::cout << "count " << count << std::endl;
		}
};