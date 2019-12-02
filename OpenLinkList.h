#include <assert.h>
#include <ostream>

using namespace std;

template <class T>
class OpenLinkList
{
protected:
	template <class T>
	struct ListNode
	{
		T data;
		ListNode<T> * pointer = NULL;
	};
	ListNode<T> * first;
	ListNode<T> * curr; //The node currently being accessed, AKA cursor
	ListNode<T> * prev; //The last node
	int size = 0; //The current size of the link list
	int index = 0; //The node index currently being accessed


public:
	OpenLinkList();
	~OpenLinkList();
	void add(T /*data*/); //Add after the current position of the list
	void addToStart(T /*data*/); //Add to the start of the list
	void add(int /*index*/, T/*data*/); //Add after the index location
	void del(); //Delete the current node
	void del(int /*Index*/); //delete the node at a given location
	T get(); //Get the data for the current node
	T get(int /**/); //Get an node by its index
	bool next(); //Get the next link list member, returns false when at the end of the list
	void reset(); //Reset curr to be at the start of the list
	T getCurrentIndex() { return index; }; //gets the current index
	void printList(ostream&); //Output all nodes from the link list 
	void moveTo(int /*Index to move to*/);

};

template <class T>
OpenLinkList<T>::OpenLinkList()
{
	first = new ListNode<T>;
	curr = first;
	assert(first);
	assert(curr);
}

//Delete all data
template <class T>
OpenLinkList<T>::~OpenLinkList()
{
	reset();
	//If there is only one node in the list
	if (size == 1)
	{
		ListNode<T> * delNode = first->pointer;
		delete(delNode);
	}
	else
	{
		ListNode<T> * nextNode = curr;
		while (nextNode != NULL)
		{
			nextNode = nextNode->pointer;
			delete(curr);
			curr = nextNode;
		}
		delete(nextNode);
	}
	delete(first);
	delete(curr);
	delete(prev);
}

//Add a new node at the current position
template <class T>
void OpenLinkList<T>::add(T newData)
{
	ListNode<T> * newNode = new ListNode<T>;
	assert(newNode);
	newNode->data = newData;
	if (curr->pointer != NULL)
		newNode->pointer = curr->pointer;
	curr->pointer = newNode;
	curr = newNode;
	size++;
	index++;
}

//Add a new node to a specific location in a link list
template <class T>
void OpenLinkList<T>::add(int pos, T newData)
{
	if (pos > size)
		throw "out of link list bounds";
	moveTo(pos);
	ListNode<T> * newNode = new ListNode<T>;
	assert(newNode);
	newNode->data = newData;
	prev->pointer = newNode;
	newNode->pointer = curr;
	size++;
	index++;
}

template <class T>
void OpenLinkList<T>::addToStart(T newData)
{
	//If there is data in the list
	if (size > 0)
	{
		ListNode<T> * newNode = new ListNode<T>;
		newNode->data = newData;
		newNode->pointer = first->pointer;
		first->pointer = newNode;
		size++;
	}
	//If the list is empty
	else
		add(newData);
}

// Get the next link list member, returns false when at the end of the list
template <class T>
bool OpenLinkList<T>::next()
{
	if (curr->pointer != NULL)
	{
		prev = curr;
		curr = curr->pointer;
		index++;
		return true;
	}
	else
		return false;
}

//Delete the current node
template <class T>
void OpenLinkList<T>::del()
{
	//If the link list is NOT empty
	if (first->pointer != NULL)
	{
		//If there is only one node in the list
		if (size == 1)
		{
			ListNode<T> * delNode = first->pointer;
			assert(delNode);
			delete(delNode);
			delete(first);
			first = new ListNode<T>;
			curr = first;
			assert(first);
			assert(curr);
			size--;
			
		}
		//When curr is the first node
		else if (curr == first->pointer)
		{
			ListNode<T> * delNode = curr;
			assert(delNode);
			first->pointer = curr->pointer;
			delete(delNode);
			curr = first->pointer;
			size--;
		}
		//When curr is the last node
		else if (curr->pointer == NULL)
		{
			ListNode<T> * delNode = curr;
			assert(delNode);
			delete(delNode);
			curr = prev;
			curr->pointer = NULL;
			size--;
		}
		//Any other position
		else
		{
			ListNode<T> * delNode = curr;
			assert(delNode);
			curr = curr->pointer;
			prev->pointer = curr;
			delete(delNode);
			size--;
		}
	}
}

//Delete a specific index
template <class T>
void OpenLinkList<T>::del(int pos)
{
	//only delete if the pos is within the list
	if (pos < size && pos >= 0)
	{
		moveTo(pos);
		del();
	}
}

//Reset to the start of the list
template <class T>
void OpenLinkList<T>::reset()
{
	curr = first->pointer;
	index = 0;
}

/* Output all nods from the link list
 * Only works with objects that can be output as a string
 */
template <class T>
void OpenLinkList<T>::printList(ostream& out)
{
	//The current position to be used to show the current location of the cursor
	ListNode<T> * nodePos = curr;
	ListNode<T> * nodePosPrev = prev;
	int numPos = index;

	out << "Link List" << endl;
	if (first->pointer != NULL)
	{
		reset();
		if (curr == nodePos)
			out << '(' << get() << ')' << endl;
		else
			out << get() << endl;

		while (next())
		{
			if (curr == nodePos)
				out << '(' << get() << ')' << endl;
			else
				out << get() << endl;
		}
	}

	out << endl << "Length: " << size << endl;
	curr = nodePos;
	prev = nodePosPrev;
	index = numPos;
	nodePos = NULL;		//This will "disconnect" curr and nodePos so that delete dosent delete both
	nodePosPrev = NULL;
	delete(nodePos);
	delete(nodePosPrev);
}

//Get the data at the current node
template <class T>
T OpenLinkList<T>::get()
{
	return curr->data;
}

//Get the data at a specific index
template <class T>
T OpenLinkList<T>::get(int pos)
{
	//Crash if out of bounds
	if (pos > size)
		throw "out of link list bounds";
	if (index > pos)
		reset();
	moveTo(pos);
	return curr->data;
}

//Moves curr to the specified index
template <class T>
void OpenLinkList<T>::moveTo(int pos)
{
	//check if pos is in range
	if (pos < size && pos >= 0)
	{
		if (pos < index)
			reset();

		while (index < pos)
			next();
	}
}
