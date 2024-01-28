template <typename T> class PriorityQueue{
private:
	int length;
	T *queue;
	int itemCount;

	T getFirst(){
		return queue[0];
	}

	T getLast(){
		return queue[itemCount - 1];
	}

	void heapifyDown(){
		int location = 0;
		do {
			int leftLocation = 2 * location + 1;
			int rightLocation = 2 * location + 2;
			int smallestLocation = location;

			if (leftLocation < itemCount && queue[leftLocation] < queue[smallestLocation]){
				smallestLocation = leftLocation;
			}
			if (rightLocation < itemCount && queue[rightLocation] < queue[smallestLocation]){
				smallestLocation = rightLocation;
			}
			if (smallestLocation != location){
				std::swap(queue[smallestLocation], queue[location]);
				location = smallestLocation;

			}
			else {
				break;
			}
		} while (true);
	}

	void heapifyUp(){
		int location = itemCount -1;
		do {
			int parentLocation = location/2;

			if (queue[location] < queue[parentLocation]){
				std::swap(queue[location], queue[parentLocation]);
				location = parentLocation;
			}
			else break;
		} while (location > 0);
	}
public:
	PriorityQueue(int length=500){
		this->length = length;
		this->queue = new T[length];
		this->itemCount = 0;
	}

	~PriorityQueue(){
		delete[] queue;
	}

	bool isEmpty(){
		if (itemCount == 0){
			return true;
		}
		return false;
	}

	void insert(T item){
		if (itemCount == length){
            throw std::out_of_range("Heap is full!");
		}
		else {
			queue[itemCount] = item;
			itemCount++;
			heapifyUp();
			// printHeap();
		}
	}

	T pop(){
		if (isEmpty()){
            throw std::out_of_range("Heap is empty!");
		}
		else {
			T target = queue[0];
			queue[0] = getLast();
			itemCount--;
			heapifyDown();
			// printHeap();
			return target;
		}
	}

	int getItemCount(){
		return this->itemCount;
	}

	void printHeap(){
		for (int i = 0; i < itemCount; i++){
			std::cout << queue[i] << " ";
		}
		std::cout << std::endl;
	}

};