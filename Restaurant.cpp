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
				cout << node->name << " " << node->energy << endl;
				node = node->next;
			}
		}
		customer *getFirst()
		{
			return first;
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
		int nextGap(double gap)
		{
			if (gap < 2)
				return 0;
			return (int)customRound(gap / 2);
		}
		customer *shellSortQueue(customer *head)
		{

			if (head == nullptr || head->next == nullptr)
				return head;

			int k = customRound(filled);
			int count = 0;
			for (int gap = k; gap > 0; gap = nextGap(gap))
			{
				customer *i = head, *j = head;
				int count = gap;

				// move j pointer k nodes ahead
				while (count-- > 0)
					j = j->next;

				// i and j pointers compare and swap
				for (; j != nullptr; i = i->next, j = j->next)
				{
					if (i->energy > j->energy)
					{
						// if i is head, then replace head with j
						if (i == head)
							head = j;

						// swap i & j pointers
						customer *iTemp = i;
						i = j;
						j = iTemp;

						// i & j pointers are swapped because
						// below code only swaps nodes by
						// swapping their associated
						// pointers(i.e. prev & next pointers)

						// Now, swap both the
						// nodes in linked list
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
			customer *temp = first;
			int count = filled;
			while (count != 0)
			{
				customer *tmpForDelete = temp;
				temp = temp->next;
				delete tmpForDelete;
			}
			last = NULL;
			first = NULL;
			filled = 0;
		}
		customer *getCustomerFromQueue(int n)
		{

			// customer *currentDelete = first;
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
			if (filled < queueSize)
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
			}
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
			cout << "Customer inQueue: " << filled << endl;
			while (current != NULL)
			{
				// Assuming you have a toString() method in the 'customer' class to display customer information
				cout << "Queue printing: " << current->name << " " << current->energy << endl;
				current = current->next;
				count--;
			}
			// cout << last->name << endl;
			return;
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
		// cout << name << " " << energy << endl;
		customerQueue->updateSize(MAXSIZE);
		customerOrder->updateSize(10000);

		if (energy != 0)
		{

			if (isNameExist(name) == false)
			{
				customer *newCustomer = new customer(name, energy, nullptr, nullptr);
				customerOrder->addCustomerInOrder(name, energy);
				if (head == nullptr || occupied == 0)
				{
					head = newCustomer;
					currentChange = newCustomer;
					occupied++;
					return;
				}
				else if (occupied < (MAXSIZE / 2))
				{
					if (currentChange->energy <= newCustomer->energy)
					{

						addRight(name, energy);
					}
					else if (currentChange->energy > newCustomer->energy)

					{
						addLeft(name, energy);
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
					cout << "occupied size: " << occupied << " max size: " << MAXSIZE << " filled: " << customerQueue->getFilled() << "\n"
						 << endl;
					if (customerQueue->getFilled() == MAXSIZE)
					{
						cout << "............." << endl;
						return;
					}
					else
					{
						customerQueue->addCustomerQueue(newCustomer);
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
		// cout << "occupied: " << occupied << " "
		// 	 << "num:" << num << endl;
		if (num >= occupied || num >= MAXSIZE)
		{
			deleteAllCustomer();
			return;
		}

		int count = 0;
		while (count != num)
		{
			customer *customerDelete = customerOrder->getCustomerFromQueue(count);
			findAndDeleteCustomer(customerDelete->name);
			customerOrder->removeCustomerInOrder(count);
			count++;
		}
	}
	void PURPLE()
	{

		int countSwap = 0;
		// customerQueue->sortAKSortedDLL(MAXSIZE, countSwap);
		// customerQueue->printQueue();
		// cout << "count swapped: " << countSwap << endl;
		customer *head = customerQueue->getFirst();
		// int filled = customerQueue->getFilled();
		cout << "before sort: " << endl;
		customerQueue->printQueue();

		customer *srt = customerQueue->shellSortQueue(head);
		cout << endl;
		cout << "after sort: " << endl;
		customerQueue->printQueue();

		// cout << "purple" << endl;
	}
	void REVERSAL()
	{
		// cout << "reversal" << endl;
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
		// customerQueue->printQueue();
		cout << "\n"
			 << "-----------------------all customer at restaurant ---------------------"
			 << "\n"
			 << endl;
		if (occupied == 0)
		{
			return;
		}
		if (num > 0)
		{

			customer *temp = head;
			int count = occupied;
			while (count > 0)
			{
				temp->print();
				temp = temp->next;
				count--;
			}
		}
		else if (num < 0)
		{
			customer *temp = head;
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
			int result = abs(tmp->energy - energy);

			if (result > maxRes)
			{
				maxRes = result;
				output = tmp->energy - energy;
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
			cout << "size of table occupied: " << count << endl;
			count++;
		}
	}
	void addLeft(string name, int energy)
	{
		if (occupied == 1)
		{
			customer *newCustomer = new customer(name, energy, currentChange, currentChange);

			currentChange->next = newCustomer;
			currentChange->prev = newCustomer;

			currentChange = newCustomer;
		}
		else
		{
			customer *tempCurrentNext = currentChange->next;
			// customer *temp = curr->prev;
			customer *newCustomer = new customer(name, energy, tempCurrentNext, currentChange);
			tempCurrentNext->next = newCustomer;
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
	void deleteAllCustomer()
	{
		if (head == NULL)
		{
			return;
		}
		customer *temp, *current;
		current = head->next;
		while (current != head)
		{
			temp = current->next;
			// free(current);
			current = temp;
		}
		// customerQueue->deleteQueue();
		// customerOrder->deleteQueue();

		head = NULL;
		currentChange = NULL;
		occupied = 0;
		return;
	}

	void findAndDeleteCustomer(string name)
	{
		customer *tmp = head;
		int index = occupied;
		while (tmp->name != name)
		{
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
		occupied--;
		return;
	}
};