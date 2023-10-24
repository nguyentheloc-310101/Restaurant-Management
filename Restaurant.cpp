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
		void removeCustomer(int n)
		{
			while (n > 0)
			{
				customer *temp = first;
				first = first->next;
				temp = nullptr;
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
		void addCustomerQueue(customer *Customer)
		{
			if (filled < queueSize)
			{
				if (filled < queueSize)
				{
					if (first == nullptr)
					{
						Customer->next = nullptr;
						first = Customer;
						last = Customer;
					}
					else
					{
						last->next = Customer;
						last = Customer;
						last->next = nullptr;
						Customer->next = nullptr;
					}
					increaseFilled();
				}
			}
		}
		void printQueue()
		{
			customer *current = first;
			int count = filled;
			cout << "Queue printing - filled: " << filled << endl;
			while (count > 0)
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
		customerOrder->updateSize(MAXSIZE);

		if (energy != 0)
		{

			if (isNameExist(name) == false)
			{
				customer *newCustomer = new customer(name, energy, nullptr, nullptr);
				customerOrder->addCustomerQueue(newCustomer);
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
					if (customerQueue->getFilled() == MAXSIZE)
						return;
					customerQueue->addCustomerQueue(newCustomer);
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
		// CustomerOrder->printQueue();
	}
	void BLUE(int num)
	{
		cout << "occupied: " << occupied << " "
			 << "num:" << num << endl;
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
			customerOrder->removeCustomer(count);
			count++;
		}
	}
	void PURPLE()
	{
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
		customerOrder->printQueue();
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

	void checkHead()
	{
		// cout << "head customer here: " << head->name << " " << head->energy << endl;
		// cout << "head customer next here: " << head->next->name << " " << head->next->energy << endl;
		// cout << "head customer next->next here: " << head->next->next->name << " " << head->next->next->energy << endl;
		// cout << "head customer next->next->next->head here: " << head->next->next->next->name << " " << head->next->next->next->energy << endl;
		customer *tmp = head->next;
	}
};