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
		void addCustomerQueue(customer *Customer);
		void getCustomerInQueue();
		void checkSizeQueue();
		void searchCustomerInQueue(string);
	};

private:
	int size = 0;

public:
	customer *currentChange;
	Queue *customerQueue;
	Queue *CustomerOrder;
	customer *head; // for travel
	int occupied;
	imp_res()
	{
		occupied = 0;
		head = nullptr;
		currentChange = nullptr;
		customerQueue = new Queue();
		CustomerOrder = new Queue();
	};

	void RED(string name, int energy)
	{
		cout << name << " " << energy << endl;
		customerQueue->updateSize(MAXSIZE);
		CustomerOrder->updateSize(MAXSIZE);

		if (energy > 0 || energy < 0)
		{
			customer *newCustomer = new customer(name, energy, nullptr, nullptr);
			if (isNameExist(newCustomer->name) == false)
			{
				// CustomerOrder->addCustomerQueue(newCustomer);
				if (head == nullptr || occupied == 0)
				{
					head = newCustomer;
					currentChange = newCustomer;
					newCustomer->next = head;
					occupied++;
					return;
				}

				if (occupied < (MAXSIZE / 2))
				{
					// if energy new > current energy  -> add right
					if (currentChange->energy < newCustomer->energy)
					{
						addRight(newCustomer);
					}
					// if energy new < current energy -> add left
					else if (currentChange->energy < newCustomer->energy)
					{
						addLeft(newCustomer);
					}
				}
				else if (occupied >= (MAXSIZE / 2) && (occupied < MAXSIZE))
				{
					// set flag > 0 or < 0, and move currentChange to that flag postion
					int flag = countRes(newCustomer->energy);
					if (flag < 0)
					{
						addLeft(newCustomer);
					}
					else if (flag > 0)
					{
						addRight(newCustomer);
					}
				}
				else if (occupied == MAXSIZE)
				{
					if (customerQueue->getFilled() == MAXSIZE)
						return;
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
		cout << "blue " << num << endl;
	}
	void PURPLE()
	{
		cout << "purple" << endl;
	}
	void REVERSAL()
	{
		cout << "reversal" << endl;
	}
	void UNLIMITED_VOID()
	{
		cout << "unlimited_void" << endl;
	}
	void DOMAIN_EXPANSION()
	{
		cout << "domain_expansion" << endl;
	}
	void LIGHT(int num)
	{
		cout << "light " << num << endl;
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

	void addLeft(customer *newCustomer)
	{
		if (occupied == 1)
		{
			newCustomer->next = head;
			newCustomer->prev = head;

			currentChange->next = newCustomer;
			currentChange->prev = newCustomer;

			// update latest change
			currentChange = newCustomer;
		}
		else
		{
			customer *tempCurrentNext = currentChange->next;
			currentChange->next = newCustomer;
			newCustomer->next = tempCurrentNext;

			tempCurrentNext->prev = newCustomer;
			newCustomer->prev = currentChange;

			currentChange = newCustomer;
		}
		occupied++;
	}

	void addRight(customer *newCustomer)
	{
		if (occupied == 1)
		{
			currentChange->next = newCustomer;
			currentChange->prev = newCustomer;

			newCustomer->prev = head;
			newCustomer->next = head;

			currentChange = newCustomer;
		}
		else
		{
			customer *tempCurrentNext = currentChange->next;
			//-> <-
			currentChange->next = newCustomer;
			newCustomer->next = tempCurrentNext;

			tempCurrentNext->prev = newCustomer;
			newCustomer->prev = currentChange;

			// update latest change
			currentChange = newCustomer;
		}
		occupied++;
	}

	// void addCustomerQueue(customer *Customer)
	// {
	// 	if (customerQueue->getFilled() == 0)
	// 	{
	// 		customerQueue->first = Customer;
	// 		customerQueue->last = Customer;
	// 	}
	// 	else
	// 	{
	// 		customerQueue->last->next = Customer;
	// 		Customer->prev = customerQueue->last;
	// 		customerQueue->last = Customer;
	// 	}

	// 	customerQueue->increaseFilled();
	// }
};