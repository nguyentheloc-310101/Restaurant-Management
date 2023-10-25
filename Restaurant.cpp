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
			if (n > filled)
				return NULL;
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
			increaseFilled();
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

			/* Before changing the head, check for the cases like
			   empty list and list with only one node */
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

				increaseFilled();
			}
		}
		void printQueue()
		{
			customer *current = first;
			int count = filled;
			if (filled == 0)
			{
				// cout << "-------------------------------------------------empty-------------------------------------------------" << endl;
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
	customer *head; // for travel
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

				customerOrder->addCustomerInOrder(name, energy);
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
						customerQueue->addCustomerInOrder(name, energy);
					}
				}
			}
			else
			{
				return;
			}
		}
		else
		{
			return;
		}
	}
	void BLUE(int num)
	{
		// cout << "----------------------------------BLUE--------------------------------"
		// 	 << " " << num << " occupied: " << occupied << endl;
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
				customer *customerDelete = customerOrder->getCustomerFromQueue(count);
				findAndDeleteCustomer(customerDelete->name);
				count++;
			}
			count = 0;

			if (customerQueue->getFilled() != 0)
			{
				while (count != num)
				{
					customer *takeCustomerInQueue = customerQueue->getCustomerFromQueue(count);
					RED(takeCustomerInQueue->name, takeCustomerInQueue->energy);
					count++;
				}
				customerQueue->removeCustomerInOrder(num);
				customerOrder->removeCustomerInOrder(num);
			}
		}
	}
	void PURPLE()
	{
		int countSwap = 0;
		// customerQueue->findMaxFromLast();
		Queue *newQ = customerQueue->sortQueue(MAXSIZE);
		customerQueue = newQ;
	}
	void REVERSAL()
	{
		if (customerQueue->getFilled() == 0)
		{
			cout << "empty queue" << endl;
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
		cout << "\n";
		cout << "NEGATIVE not reverse" << endl;
		positiveQueue->printQueue();
		cout << "\n";

		cout << "\n";
		cout << "POSITIVE not reverse" << endl;
		negativeQueue->printQueue();
		cout << "\n";

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
				return;
			}

			tmpQueueMain2 = tmpQueueMain2->next;
			count++;
		}

		// delete tmpFirstNeg;
	}
	void UNLIMITED_VOID()
	{
		// cout << "unlimited_void" << endl;
	}
	void DOMAIN_EXPANSION()
	{
		// cout << "domain_expansion" << endl;
	}

	void LIGHT(int num)
	{
		cout << "LIGHT " << num << endl;
		if (occupied == 0)
		{
			return;
		}
		if (num > 0)
		{
			// if it doesn't back to head -> check this
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
		customer *tmp = head;
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
	void checkSize()
	{
		int count = 0;
		customer *ptr = head->next;
		while (ptr != head)
		{
			count++;
		}
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
				return;
			}
			tmp = tmp->next;
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
		return;
	}
};