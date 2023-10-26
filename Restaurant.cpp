#include "main.h"

class imp_res : public Restaurant
{
public:
	class Queue
	{
	private:
		int queueSize;
		int filled;

	public:
		customer *first;
		customer *last;
		Queue()
		{
			first = NULL;
			last = NULL;
			queueSize = 0;
			filled = 0;
		}
		~Queue()
		{
			while (first != nullptr)
			{
				customer *f = first;
				first = first->next;
				delete f;
			}
			first = last = NULL;
			filled = 0;
		}
		int sumPosValue()
		{
			int sum = 0;
			customer *ptr = first;
			while (ptr != NULL)
			{
				if (ptr->energy > 0)
				{
					sum = sum + ptr->energy;
				}

				ptr = ptr->next;
			}
			return sum;
		}
		int sumNegValue()
		{
			int sum = 0;
			customer *ptr = first;
			while (ptr != NULL)
			{
				if (ptr->energy < 0)
				{
					int a = abs(ptr->energy);
					sum = sum + a;
				}
				ptr = ptr->next;
			}
			return sum;
		}
		Queue(int maxsize)
		{
			first = NULL;
			last = NULL;
			queueSize = maxsize;
			filled = 0;
		}
		void updateSize(int size)
		{
			this->queueSize = size;
			return;
		}
		int getFilled()
		{
			return filled;
		}
		void increaseFilled()
		{
			filled++;
		}
		void decreaseFilled()
		{
			filled--;
		}
		void printList(customer *node)
		{
			while (node != nullptr)
			{
				node = node->next;
			}
		}
		customer *getFirst()
		{
			return first;
		}
		customer *getLast()
		{
			return last;
		}
		int customRound(double num)
		{
			if (num < 0)
			{
				return static_cast<int>(num - 0.5);
			}
			else
			{
				return static_cast<int>(num + 0.5);
			}
		}
		Queue *sortQueue(int maxsize)
		{
			customer *travel = first;
			customer *positionOfMax = first;
			Queue *queueBeforeMax = new Queue(maxsize);
			Queue *queueAfterMax = new Queue(maxsize);

			Queue *output = new Queue(maxsize);

			int countStop = 0;
			int max = abs(travel->energy);
			// cout << "filled: " << filled << endl;
			int flag = 0;

			// get the max position
			while (countStop != filled)
			{
				int tmp = abs(travel->energy);
				if (tmp >= max)
				{
					max = abs(travel->energy);
					positionOfMax = travel;
				}
				travel = travel->next;
				countStop++;
			}

			customer *tmp = positionOfMax;
			customer *tmpAfter = positionOfMax->next;

			while (tmp != NULL)
			{
				queueBeforeMax->addCustomerInOrder(tmp->name, tmp->energy);
				tmp = tmp->prev;
			}
			while (tmpAfter != NULL)
			{
				queueAfterMax->addCustomerInOrder(tmpAfter->name, tmpAfter->energy);
				tmpAfter = tmpAfter->next;
			}
			queueBeforeMax->reverse();

			// delete tmp;
			// delete tmpAfter;
			// delete travel;
			// delete positionOfMax;

			customer *travelAddFront = queueBeforeMax->getFirst();
			customer *travelAddAfter = queueAfterMax->getFirst();
			while (travelAddFront != NULL)
			{
				output->addCustomerInOrder(travelAddFront->name, travelAddFront->energy);
				travelAddFront = travelAddFront->next;
			}
			while (travelAddAfter != NULL)
			{
				output->addCustomerInOrder(travelAddAfter->name, travelAddAfter->energy);
				travelAddAfter = travelAddAfter->next;
			}

			return output;
		}
		int nextGap(double gap)
		{
			if (gap < 2)
				return 0;
			return (int)customRound(gap / 2);
		}
		customer *shellSortQueue(customer *head, int &swap)
		{
			if (head == nullptr || head->next == nullptr)
				return head;

			int k = customRound(filled);
			// int count = 0;
			// customer *positionSort = findMaxFromLast();
			for (int gap = k; gap > 0; gap = nextGap(gap))
			{
				customer *i = head, *j = head;
				int count = gap;
				while (count-- > 0)
					j = j->next;

				for (; j != nullptr; i = i->next, j = j->next)
				{
					if (abs(i->energy) > abs(j->energy))
					{
						swap++;
						if (i == head)
							head = j;
						customer *iTemp = i;
						i = j;
						j = iTemp;
						customer *iPrev = i->prev, *iNext = i->next;
						if (iPrev != nullptr)
							iPrev->next = j;
						if (iNext != nullptr)
							iNext->prev = j;
						i->prev = j->prev;
						i->next = j->next;
						if (j->prev != nullptr)
							j->prev->next = i;
						if (j->next != nullptr)
							j->next->prev = i;
						j->prev = iPrev;
						j->next = iNext;
					}
				}
			}
			first = head;
			return head;
		}

		bool checkFilled(int size)
		{
			customer *tmp = first;
			int count = 0;
			while (tmp != NULL)
			{
				count++;
				tmp = tmp->next;
			}
			if (size = count)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		void removeCustomerInOrder(int n)
		{
			while (n > 0)
			{
				customer *temp = first;
				first = first->next;
				n--;
				filled--;
			}

			if (first == NULL)
			{
				last = NULL;
			}
		}
		void deleteQueue()
		{
			if (first == nullptr)
			{
				return; // List is empty
			}

			while (first != nullptr)
			{
				customer *temp = first;
				first = first->next;
				delete temp;
			}
			filled = 0;
		}
		customer *getCustomerFromQueue(int n)
		{

			customer *returnCurrent = first;
			int count = 0;
			while (count != n)
			{
				returnCurrent = returnCurrent->next;
				count++;
			}
			return returnCurrent;
		}

		void getCustomerInQueue();
		void checkSizeQueue();
		void searchCustomerInQueue(string);
		void deleteNode(string name)
		{
			customer *current = first;
			while (current != nullptr)
			{

				if (current->name == name)
				{
					filled--;
					if (current == first)
					{
						first = first->next;
					}
					if (current == last)
					{
						last = last->prev;
					}

					if (current->next != nullptr)
					{
						current->next->prev = current->prev;
					}

					if (current->prev != nullptr)
					{
						current->prev->next = current->next;
					}
					delete current;
					break;
				}
				current = current->next;
			}
		}
		void addCustomerInOrder(string name, int energy)
		{
			if (first == nullptr)
			{
				customer *newNode = new customer(name, energy, nullptr, nullptr);
				first = newNode;
				last = newNode;
			}
			else
			{
				customer *newNode = new customer(name, energy, last, nullptr);
				last->next = newNode; // next address of ending node is linking with new node
				last = newNode;
			}
			filled++;
		}
		void reverse()
		{
			customer *temp = NULL;
			customer *current = first;

			/* swap next and prev for all nodes of
			doubly linked list */
			while (current != NULL)
			{
				temp = current->prev;
				current->prev = current->next;
				current->next = temp;
				current = current->prev;
			}

			if (temp != NULL)
				first = temp->prev;
		}
		void addCustomerQueue(customer *Customer)
		{

			if (filled < queueSize)
			{
				if (first == nullptr)
				{
					Customer->next = nullptr;
					Customer->prev = nullptr;
					first = Customer;
					last = Customer;
				}
				else
				{
					Customer->next = NULL; // set next address field of new node  is NULL
					Customer->prev = last; // previous address of new node is linking with ending node
					last->next = Customer; // next address of ending node is linking with new node
					last = Customer;
				}

				filled++;
			}
		}
		void printQueue()
		{
			customer *current = first;
			int count = filled;
			if (filled == 0)
			{
				return;
			}
			while (current != NULL)
			{
				current->print();
				current = current->next;
				count--;
			}
		}
	};

private:
	int size = 0;

public:
	customer *currentChange;
	Queue *customerQueue;
	Queue *customerOrder;
	customer *head;
	int occupied;
	imp_res()
	{
		occupied = 0;
		head = nullptr;
		currentChange = nullptr;
		customerQueue = new Queue();
		customerOrder = new Queue();
	};

	void RED(string name, int energy)
	{
		customerQueue->updateSize(MAXSIZE);
		customerOrder->updateSize(10000);

		if (energy != 0)
		{
			if (isNameExist(name) == false)
			{
				customer *checkExist = customerOrder->getFirst();
				if (checkExist == nullptr)
				{
					customerOrder->addCustomerInOrder(name, energy);
				}
				else
				{
					bool existed = false;
					while (checkExist != nullptr)
					{
						if (name == checkExist->name)
						{
							existed = true;
						}
						checkExist = checkExist->next;
					}
					if (existed == false)
					{
						customerOrder->addCustomerInOrder(name, energy);
					}
				}

				// customerOrder->addCustomerInOrder(name, energy);

				if (head == nullptr || occupied == 0)
				{
					customer *newCustomer = new customer(name, energy, nullptr, nullptr);
					head = newCustomer;
					currentChange = newCustomer;
					occupied++;
				}
				else if (occupied < (MAXSIZE / 2))
				{
					if (occupied == 2)
					{
						if (currentChange->energy >= head->energy)
						{
							if (currentChange->energy <= energy)
							{
								addRight(name, energy);
							}
							else if (currentChange->energy > energy)

							{
								addLeft(name, energy);
							}
						}
						else
						{
							if (currentChange->energy <= energy)
							{
								customer *newCustomer = new customer(name, energy, currentChange, head);
								currentChange->next = newCustomer;
								head->prev = newCustomer;
								currentChange = newCustomer;
								occupied++;
							}
							else if (currentChange->energy > energy)
							{
								customer *newCustomer = new customer(name, energy, head, currentChange);
								head->next = newCustomer;
								currentChange->prev = newCustomer;

								currentChange = newCustomer;
								occupied++;
							}
						}
					}
					else
					{
						if (currentChange->energy <= energy)
						{
							addRight(name, energy);
						}
						else if (currentChange->energy > energy)

						{
							addLeft(name, energy);
						}
					}
				}
				else if ((occupied >= (MAXSIZE / 2)) && (occupied < MAXSIZE))
				{
					int flag = countRes(energy);
					if (flag < 0)
					{
						addLeft(name, energy);
					}
					else if (flag > 0)
					{
						addRight(name, energy);
					}
				}
				else if (occupied == MAXSIZE)
				{
					if (customerQueue->getFilled() == MAXSIZE)
					{
						return;
					}
					else
					{
						customer *newCustomer = new customer(name, energy, nullptr, nullptr);
						customerQueue->addCustomerQueue(newCustomer);
					}
				}
			}
		}
	}
	void BLUE(int num)
	{
		if (num >= occupied || num >= MAXSIZE)
		{
			int count = occupied;
			while (count > 0)
			{
				customer *temp = head;
				head = head->next;
				delete temp;
				count--;
			}
			customerQueue->deleteQueue();
			customerOrder->deleteQueue();
			occupied = 0;
		}
		else
		{
			int count = 0;
			while (count != num)
			{
				customer *customerDelete = customerOrder->first;
				findAndDeleteCustomer(customerDelete->name);
				customerOrder->deleteNode(customerDelete->name);
				count++;
			}
			count = 0;

			if (customerQueue->getFilled() != 0)
			{

				while (count != num)
				{
					customer *takeCustomerInQueue = customerQueue->first;
					RED(takeCustomerInQueue->name, takeCustomerInQueue->energy);
					customerQueue->deleteNode(takeCustomerInQueue->name);
					count++;
				}
			}
		}
	}
	void PURPLE()
	{
		int countSwap = 0;
		Queue *newQ = customerQueue->sortQueue(MAXSIZE);
		customerQueue = newQ;
	}
	void REVERSAL()
	{
		if (customerQueue->getFilled() == 0)
		{
			return;
		}
		Queue *negativeQueue = new Queue();
		Queue *positiveQueue = new Queue();

		string currNameUnique = currentChange->name;
		customer *firstCustomer = head;
		int count = 0;

		while (count != occupied)
		{

			if (firstCustomer->energy > 0)
			{
				positiveQueue->addCustomerInOrder(firstCustomer->name, firstCustomer->energy);
			}
			else if (firstCustomer->energy < 0)
			{
				negativeQueue->addCustomerInOrder(firstCustomer->name, firstCustomer->energy);
			}
			firstCustomer = firstCustomer->next;
			count++;
		}
		// cout << "\n";
		// cout << "NEGATIVE not reverse" << endl;
		// positiveQueue->printQueue();
		// cout << "\n";

		// cout << "\n";
		// cout << "POSITIVE not reverse" << endl;
		// negativeQueue->printQueue();
		// cout << "\n";

		negativeQueue->reverse();
		positiveQueue->reverse();

		customer *tmpQueueMain = head->next;
		customer *tmpFirstNeg = negativeQueue->getFirst();
		customer *tmpFirstPos = positiveQueue->getFirst();

		while (tmpQueueMain != head)
		{
			if (tmpQueueMain->energy < 0)
			{
				tmpQueueMain->energy = tmpFirstNeg->energy;
				tmpQueueMain->name = tmpFirstNeg->name;
				tmpFirstNeg = tmpFirstNeg->next;
			}
			else if (tmpQueueMain->energy > 0)
			{
				tmpQueueMain->energy = tmpFirstPos->energy;
				tmpQueueMain->name = tmpFirstPos->name;
				tmpFirstPos = tmpFirstPos->next;
			}
			tmpQueueMain = tmpQueueMain->next;
		}
		count = 0;
		customer *tmpQueueMain2 = head;
		while (count != occupied)
		{
			if (tmpQueueMain2->name == currNameUnique)
			{
				currentChange = tmpQueueMain2;
				break;
			}

			tmpQueueMain2 = tmpQueueMain2->next;
			count++;
		}

		// delete tmpFirstNeg;
	}
	void UNLIMITED_VOID()
	{
		// cout << "unlimited_void" << endl;
		if (size < 4)
		{
			return;
		}

		customer *bestStart = nullptr;
		customer *bestEnd = nullptr;

		customer *temp = currentChange;
		customer *temp1 = temp;

		int sum = 0;
		int sumMin = 9999999;
		int flag = 0;

		int j = 0;
		int i = 4;
		while (i < size)
		{
			temp = currentChange;
			temp1 = temp;
			while (temp->next != currentChange)
			{
				j = 0;
				temp1 = temp;
				sum = 0;
				while (temp1->next != currentChange && j < i)
				{

					sum += temp1->energy;
					temp1 = temp1->next;
					j++;
					if (temp1->next == currentChange && j < i - 1)
					{
						flag = 1;
					}
				}

				if (flag == 0 && sum < sumMin)
				{
					sumMin = sum;
					bestStart = temp;
					bestEnd = temp1->prev;
				}

				flag = 0;
				temp = temp->next;
			}
			i++;
		}
		if (bestStart)
		{
			cout << bestEnd->energy << endl;
			while (bestStart != bestEnd)
			{
				bestStart->print();
				bestStart = bestStart->next;
			}
			bestEnd->print();
		}
	}
	void DOMAIN_EXPANSION()
	{
		customer *tmp = head;
		int count = 0;
		int sumPos = 0;
		int sumNeg = 0;
		while (count != occupied)
		{
			if (tmp->energy > 0)
			{
				sumPos = sumPos + tmp->energy;
			}
			else if (tmp->energy < 0)
			{
				sumNeg = sumNeg + abs(tmp->energy);
			}
			tmp = tmp->next;
			count++;
		}
		sumPos = sumPos + customerQueue->sumPosValue();
		sumNeg = sumNeg + customerQueue->sumNegValue();
		if (sumPos >= sumNeg)
		{
			customer *travel = head;
			int countOccupied = occupied;
			while (countOccupied != 0)
			{
				if (travel->energy < 0)
				{
					findAndDeleteCustomer(travel->name);
				}
				countOccupied--;
				travel = travel->next;
			}

			customer *firstTemp = customerQueue->getFirst();

			while (firstTemp != NULL)
			{
				if (firstTemp->energy < 0)
				{
					customerQueue->deleteNode(firstTemp->name);
				}
				firstTemp = firstTemp->next;
			}
		}
		else if (sumPos < sumNeg)
		{
			customer *travel2 = head;
			int countOccupied2 = occupied;
			while (countOccupied2 != 0)
			{
				if (travel2->energy > 0)
				{
					findAndDeleteCustomer(travel2->name);
				}
				countOccupied2--;
				travel2 = travel2->next;
			}
			customer *firstTemp = customerQueue->getFirst();
			while (firstTemp != NULL)
			{
				if (firstTemp->energy > 0)
				{
					customerQueue->deleteNode(firstTemp->name);
				}
				firstTemp = firstTemp->next;
			}
		}

		int testSizeQueue = 0;
		customer *sizeQ = customerQueue->getFirst();
		while (sizeQ != NULL)
		{
			testSizeQueue++;
			sizeQ = sizeQ->next;
		}
		if (occupied < MAXSIZE && testSizeQueue > 0)
		{

			int nCount = MAXSIZE - occupied;

			while (nCount != 0)
			{
				customer *takeCustomer = customerQueue->getFirst();
				if (takeCustomer == NULL)
					break;
				if (takeCustomer != NULL)
				{
					RED(takeCustomer->name, takeCustomer->energy);
					customerQueue->deleteNode(takeCustomer->name);
				}
				nCount--;
			}
			if (sumPos >= sumNeg)
			{
				customer *firstTemp2 = customerOrder->getFirst();
				while (firstTemp2 != NULL)
				{
					if (firstTemp2->energy < 0)
					{
						firstTemp2->print();
						customerOrder->deleteNode(firstTemp2->name);
					}
					firstTemp2 = firstTemp2->next;
				}
			}
			else if (sumPos < sumNeg)
			{
				customer *firstTemp2 = customerOrder->getFirst();
				while (firstTemp2 != NULL)
				{
					if (firstTemp2->energy > 0)
					{
						firstTemp2->print();
						customerOrder->deleteNode(firstTemp2->name);
					}
					firstTemp2 = firstTemp2->next;
				}
			}
		}
	}

	void LIGHT(int num)
	{
		cout << "LIGHT " << num << endl;
		if (occupied == 0)
		{
		}
		else if (num > 0)
		{
			customer *temp = currentChange;
			int count = occupied;
			while (count != 0)
			{
				temp->print();
				temp = temp->next;
				count--;
			}
		}
		else if (num == 0)
		{
			cout << "\n";
			cout << "PRIORITY:" << endl;
			customerOrder->printQueue();
			cout << "\n";
			cout << "Waiting:" << endl;
			customerQueue->printQueue();
		}
		else if (num < 0)
		{
			customer *temp = currentChange;
			int count = occupied;
			while (count > 0)
			{
				temp->print();
				temp = temp->prev;
				count--;
			}
		}
	}
	int countRes(int energy)
	{
		customer *tmp = currentChange;
		int count = occupied;
		int maxRes = 0;
		int output = 0;
		while (count != 0)
		{
			int result = abs(energy - tmp->energy);

			if (result > maxRes)
			{
				maxRes = result;
				output = energy - tmp->energy;
				currentChange = tmp;
			}
			tmp = tmp->next;
			count--;
		}

		return output;
	}

	bool isNameExist(string name)
	{
		customer *ptr = head;
		int count = occupied;
		while (count != 0)
		{
			if (ptr->name == name)
			{
				return true;
			}
			count--;
			ptr = ptr->next;
		}
		return false;
	}
	int checkSize()
	{
		int count = 0;
		customer *ptr = head->next;
		while (ptr != head)
		{
			count++;
		}
		return count;
	}
	void addLeft(string name, int energy)
	{
		if (occupied == 1)
		{
			customer *newCustomer = new customer(name, energy, head, head);
			head->next = newCustomer;
			head->prev = newCustomer;
			currentChange = newCustomer;
		}
		else
		{
			customer *tempCurrentPrev = currentChange->prev;
			customer *newCustomer = new customer(name, energy, tempCurrentPrev, currentChange);
			tempCurrentPrev->next = newCustomer;
			currentChange->prev = newCustomer;

			currentChange = newCustomer;
		}
		occupied++;
	}

	void addRight(string name, int energy)
	{

		if (occupied == 1)
		{
			customer *newCustomer = new customer(name, energy, currentChange, currentChange);

			currentChange->next = newCustomer;
			currentChange->prev = newCustomer;

			// update latest change
			currentChange = newCustomer;
		}
		else
		{
			customer *tempCurrentNext = currentChange->next;
			customer *newCustomer = new customer(name, energy, currentChange, tempCurrentNext);

			currentChange->next = newCustomer;
			tempCurrentNext->prev = newCustomer;
			currentChange = newCustomer;
		}

		occupied++;
	}

	void findAndDeleteCustomer(string name)
	{
		customer *tmp = head;
		int count = 0;
		while (count != occupied)
		{
			if (tmp->name == name)
			{
				break;
			}
			tmp = tmp->next;
			count++;
		}
		customer *prevTemp = tmp->prev;
		customer *nextTemp = tmp->next;

		prevTemp->next = nextTemp;
		nextTemp->prev = prevTemp;
		if (tmp == head)
		{
			head = nextTemp;
		}
		if (tmp->energy > 0)
		{
			currentChange = nextTemp;
		}
		else if (tmp->energy < 0)
		{
			currentChange = prevTemp;
		}

		occupied--;
	}
	void shellSort(customer *start, int &change)
	{
		customer *ptr = start;
		int NoOfElements = 0;
		while (ptr != nullptr)
		{
			NoOfElements++;
			ptr = ptr->prev;
		}

		bool flag = false;
		for (int gap = NoOfElements / 2; gap > 0; gap /= 2)
		{
			for (int i = gap; i < NoOfElements; i++)
			{
				for (int j = i; j >= gap; j -= gap)
				{
					customer *customerAtJ = getCustomerAt(j);
					customer *gapJ = getCustomerAt(j - gap);
					if (abs(customerAtJ->energy) > abs(gapJ->energy))
					{
						flag = true;
						string tempName = customerAtJ->name;
						int tempEnergy = customerAtJ->energy;
						customerAtJ->name = gapJ->name;
						customerAtJ->energy = gapJ->energy;
						gapJ->name = tempName;
						gapJ->energy = tempEnergy;
					}
					else if (abs(customerAtJ->energy) == abs(gapJ->energy))
					{
						customer *ptr = customerOrder->getFirst();
						while (ptr != nullptr)
						{
							if (ptr->name == customerAtJ->name || ptr->name == gapJ->name)
							{
								break;
							}
							ptr = ptr->next;
						}
						if (ptr->name == customerAtJ->name)
						{
							flag = true;
							string tempName = customerAtJ->name;
							int tempEnergy = customerAtJ->energy;
							customerAtJ->name = gapJ->name;
							customerAtJ->energy = gapJ->energy;
							gapJ->name = tempName;
							gapJ->energy = tempEnergy;
						}
					}
				}
				if (flag == true)
				{
					change++;
					flag = false;
				}
			}
		}
	}

	// get customer at index in queue
	customer *getCustomerAt(int index)
	{
		int count = 0;
		customer *ptr = customerQueue->getFirst();
		while (ptr->next != nullptr && count != index)
		{
			count++;
			ptr = ptr->next;
		}
		return ptr;
	}
};