#include <iostream>

using namespace std;

// List

template<typename SomeType>
class List
{
private:
	template<typename SomeType>
	class Node
	{
	public:						// Если выложить все ячейки по адресам слева на право, то:
		Node* PreviousAddress;  // Это ссылка влево (т.е. ведёт в начало списка)
		Node* NextAddress;		// Это ссылка вправо (т.е. ведёт в конец списка)
		SomeType data;

		Node(SomeType data = SomeType())
		{
			this->data = data;
			this->NextAddress = this->PreviousAddress = nullptr;
		}
	};


	Node<SomeType>* Head;	// Начало
	Node<SomeType>* Tail; // Конец
	int Size;
	void add_first(SomeType data);	// Инициализирует добавление первого элемента

public:

	List();
	~List();

	void add_on_pos_right(int index, SomeType data); // Добавляет значение справа
	void add_on_pos_left(int index, SomeType data);	 // Добавляет значение слева
	void append(SomeType data);						 // Добавляет значение правее последнего элемента (в конец списка)
	void add_front(SomeType data);					 // Добавляет значение левее первого элемента (в начало списка)
	void pop_element(int index);					 // Удаляет элемент по нужному адресу
	void pop_top();									 // Удаляет Начальный (Head) элемент списка
	void pop_low();									 // Удаляет Конечный (Tail) элемент списка
	SomeType& get_low();							 // Передаёт ссылку на поле data Конечного элемента
	SomeType& get_top();							 // Передаёт ссылку на поле data Начального элемента
	int get_size() { return Size; };				 // Возвращает размер списка
	SomeType& operator[](int index);				 // Оператор индексирования для обращения к полю data нужных элементов


};


template<typename SomeType>
List<SomeType>::~List()
{
	if (this->Size != 0)
	{

		Node<SomeType>* Previous = this->Head;
		Node<SomeType>* Current = nullptr;
		while (Current != nullptr)
		{
			Current = Previous->NextAddress;
			delete Previous;
		}
		delete Current;
	}
}

template<typename SomeType>
void List<SomeType>::add_first(SomeType data)
{
	Tail = new Node<SomeType>(data);
	Head = Tail;
	this->Size++;
};

template<typename SomeType>
void List<SomeType>::pop_low()
{
	if (this->get_size() == 0)
	{
		cout << "This list has no elements!\n";
		return;
	}
	if (this->get_size() == 1)
	{
		delete this->Tail;
		this->Size--;
		return;

	}
	Node<SomeType>* Current = Tail;
	Current = Current->PreviousAddress;
	this->Tail = Current;
	delete Current->NextAddress;
	Current->NextAddress = nullptr;
	this->Size--;
};

template<typename SomeType>
void List<SomeType>::pop_top()
{
	if (this->get_size() == 0)
	{
		cout << "This list has no elements!\n";
		return;
	}
	if (this->get_size() == 1)
	{
		delete this->Head;
		this->Size--;
		return;
	}
	Node<SomeType>* Current = Head;
	Current = Current->NextAddress;
	this->Head = Current;
	delete Current->PreviousAddress;
	Current->PreviousAddress = nullptr;
	this->Size--;
};

template<typename SomeType>
List<SomeType>::List()
{
	Size = 0;
	Head = Tail = nullptr;

};

template<typename SomeType>
void List<SomeType>::add_on_pos_right(int index, SomeType data)
{
	if (this->get_size() == 0)
	{
		this->add_first(data);
	}
	else
	{
		if (index == this->Size - 1)
		{
			this->append(data);
		}
		else
		{
			int counter = 0;
			Node<SomeType>* NewNode = new Node<SomeType>(data);
			Node<SomeType>* Current = this->Head;
			while (index != counter)
			{
				Current = Current->NextAddress;
				counter++;
			}
			Node<SomeType>* Previous = Current;
			Node<SomeType>* Next = Current->NextAddress;
			Current = NewNode;
			Previous->NextAddress = Current;
			Current->NextAddress = Next;
			Next->PreviousAddress = Current;
			Current->PreviousAddress = Previous;
			this->Size++;
		}
	}
}

template<typename SomeType>
void List<SomeType>::add_on_pos_left(int index, SomeType data)
{
	if (this->get_size() == 0)
	{
		this->add_first(data);
	}
	else
	{
		if (index == 0)
		{
			this->add_front(data);
		}
		else
		{
			int counter = 0;
			Node<SomeType>* NewNode = new Node<SomeType>(data);
			Node<SomeType>* Current = this->Head;
			while (index != counter)
			{
				Current = Current->NextAddress;
				counter++;
			}
			Node<SomeType>* Next = Current;
			Node<SomeType>* Previous = Current->PreviousAddress;
			Current = NewNode;
			Next->PreviousAddress = Current;
			Current->PreviousAddress = Previous;
			Previous->NextAddress = Current;
			Current->NextAddress = Next;
			this->Size++;
		}
	}
}

template<typename SomeType>
void List<SomeType>::append(SomeType data)
{
	if (this->Tail == nullptr)
	{
		this->add_first(data);
		return;
	}
	else
	{
		this->Tail->NextAddress = new Node<SomeType>(data);
		Node<SomeType>* Buffer = this->Tail;
		this->Tail = this->Tail->NextAddress;
		this->Tail->PreviousAddress = Buffer;
		Size++;
	}

}

template<typename SomeType>
void List<SomeType>::add_front(SomeType data)
{
	if (Head == nullptr)
	{
		this->add_first(data);
		return;
	}
	else
	{
		Node<SomeType>* Next;
		Node<SomeType>* Current = this->Head;
		Current->PreviousAddress = new Node<SomeType>(data);
		Next = Current;
		Current = Current->PreviousAddress;
		Current->NextAddress = Next;
		this->Head = Current;
		Size++;
	}

}

template<typename SomeType>
void List<SomeType>::pop_element(int index)
{

	if (this->get_size() == 0)
	{
		return;
	}
	if (this->get_size() == 1)
	{
		delete this->Head;
		this->Size--;
		return;
	}
	if (index == this->Size - 1)
	{
		Node<SomeType>* Current = Tail;
		Current = Current->PreviousAddress;
		this->Tail = Current;
		delete Current->NextAddress;
		Current->NextAddress = nullptr;
		this->Size--;
		return;
	}
	if (index == 0)
	{
		Node<SomeType>* Current = Head;
		Current = Current->NextAddress;
		this->Head = Current;
		delete Current->PreviousAddress;
		Current->PreviousAddress = nullptr;
		this->Size--;
		return;
	}
	else
	{
		int counter = 0;
		Node<SomeType>* Previous = nullptr;
		Node<SomeType>* Current = Head;
		Node<SomeType>* Next = nullptr;
		while (counter != index)
		{
			Current = Current->NextAddress;
			counter++;
		}
		Previous = Current->PreviousAddress;
		Next = Current->NextAddress;
		if (Previous != nullptr)
		{
			Previous->NextAddress = Next;
		}

		if (Next != nullptr)
		{
			Next->PreviousAddress = Previous;
		}
		delete Current;
		this->Size--;
	}

}

template<typename SomeType>
SomeType& List<SomeType>::get_low()
{
	return this->Tail->data;
};

template<typename SomeType>
SomeType& List<SomeType>::get_top()
{
	return this->Head->data;
};

template<typename SomeType>
SomeType& List<SomeType>::operator[](int index)
{
	if (index == 0)
	{
		return this->Head->data;

	}
	else
	{
		if (index == this->Size - 1)
		{
			return this->Tail->data;
		}
		else
		{
			int counter = 0;
			Node<SomeType>* Current = this->Head;
			while (Current != nullptr)
			{
				if (counter == index)
				{
					return Current->data;
				}
				Current = Current->NextAddress;
				counter++;
			}
		}

	}
};


template<typename SomeType>
class Tree 
{
private:
	template<typename SomeType>
	class Node 
	{
	public:
		List<Node*> NextAddressArray;
		Node<SomeType>* PreviousAddress;
		SomeType Data;
		int RootSum;
		int Descendant_Count;
		int Level;
		Node(SomeType Data = SomeType(), int Vertexes = 2) 
		{
			this->Level = 0;
			this->Data = Data;
			for (int i = 0; i < Vertexes; i++)
			{
				this->NextAddressArray.append(nullptr);
			}
			this->PreviousAddress = nullptr;
		}
	};
public:
	int Vertexes;
	int Hight;
	Node<SomeType>* CurrentNode;
	Node<SomeType>* TreeRoot;
	Tree(int Max_Vertex_Number, SomeType StartData)
	{
		this->Vertexes = Max_Vertex_Number;
		this->TreeRoot = new Node<SomeType>{ StartData , Vertexes};
		this->CurrentNode = TreeRoot;
		this->Hight = 0;
	};
	void add_leaf(int position, SomeType Data);
	void go_next(int position);
	void go_back();
	void Special_Algorythm(Node<SomeType>* RootNode);
	void help();
};

template<typename SomeType>
void Tree<SomeType>::add_leaf(int position, SomeType Data)
{
	if (position < 0 || position > Vertexes-1) 
	{
		cout << "Wrong position, try else." << endl;
		return;
	}
	if (this->CurrentNode->NextAddressArray[position] == nullptr)
	{
		Node<SomeType>* NewNode = new Node<SomeType>{ Data };
		NewNode->Level = this->CurrentNode->Level + 1;
		NewNode->PreviousAddress = CurrentNode;
		if (Hight - 1 < NewNode->Level) 
		{
			Hight = NewNode->Level + 1;
		}
		this->CurrentNode->NextAddressArray[position] = NewNode;
		return;
	}
	else 
	{
		cout << "Denied in this direction, try else." << endl;
		return;
	}
}

template<typename SomeType>
void Tree<SomeType>::go_next(int position)
{
	if (position < 0 || position > Vertexes - 1)
	{
		cout << "Wrong position, try else." << endl;
		return;
	}
	if (CurrentNode->NextAddressArray[position] == nullptr)
	{
		
		cout << "This is an empty place, try else." << endl;
		return;
	}
	else 
	{
		CurrentNode = CurrentNode->NextAddressArray[position];
	}
};


template<typename SomeType>
void Tree<SomeType>::go_back()
{
	if (this->CurrentNode->PreviousAddress == nullptr) 
	{
		cout << "This is a tree root, try else." << endl;
		return;
	}
	else
	{
		this->CurrentNode = CurrentNode->PreviousAddress;
	}
	
};


double Max_Desicion = 0;
double Min_Desicion = 10000; // Two global variables for final purpose



template<typename SomeType>
void Tree<SomeType>::Special_Algorythm(Node<SomeType>* PresTreeRoot)
{
	Node<SomeType>* CurRootNode = PresTreeRoot;
	if (CurRootNode->NextAddressArray[0] == nullptr && CurRootNode->NextAddressArray[1] == nullptr)
	{
		CurRootNode->RootSum = CurRootNode->Data;
		CurRootNode->Descendant_Count = 1;
		double Result = CurRootNode->RootSum / CurRootNode->Descendant_Count;
		if (Max_Desicion < Result) 
		{
			Max_Desicion = Result;
		}

		if (Min_Desicion > Result) 
		{
			Min_Desicion = Result;
		}
		
	}
	else
	{
		if (CurRootNode->NextAddressArray[0] == nullptr) 
		{
			Special_Algorythm(CurRootNode->NextAddressArray[1]);
			Node<SomeType>* RightNode = CurRootNode->NextAddressArray[1];
			CurRootNode->RootSum = RightNode->RootSum + CurRootNode->Data;
			CurRootNode->Descendant_Count = RightNode->Descendant_Count + 1;
			double Result = (double)CurRootNode->RootSum / (double)CurRootNode->Descendant_Count;
			if (Max_Desicion < Result)
			{
				Max_Desicion = Result;
			}

			if (Min_Desicion > Result)
			{
				Min_Desicion = Result;
			}
		}
		else 
		{
			if (CurRootNode->NextAddressArray[1] == nullptr)
			{
				Special_Algorythm(CurRootNode->NextAddressArray[0]);
				Node<SomeType>* LeftNode = CurRootNode->NextAddressArray[0];
				CurRootNode->RootSum = LeftNode->RootSum + CurRootNode->Data;
				CurRootNode->Descendant_Count = LeftNode->Descendant_Count + 1;
				double Result = (double)CurRootNode->RootSum / (double)CurRootNode->Descendant_Count;
				if (Max_Desicion < Result)
				{
					Max_Desicion = Result;
				}

				if (Min_Desicion > Result)
				{
					Min_Desicion = Result;
				}
			}
			else 
			{
				Special_Algorythm(CurRootNode->NextAddressArray[0]);
				Special_Algorythm(CurRootNode->NextAddressArray[1]);
				Node<SomeType>* LeftNode = CurRootNode->NextAddressArray[0];
				Node<SomeType>* RightNode = CurRootNode->NextAddressArray[1];
				CurRootNode->RootSum = LeftNode->RootSum + RightNode->RootSum + CurRootNode->Data;
				CurRootNode->Descendant_Count = LeftNode->Descendant_Count + RightNode->Descendant_Count + 1;
				double Result = (double)CurRootNode->RootSum / (double)CurRootNode->Descendant_Count;
				if (Max_Desicion < Result)
				{
					Max_Desicion = Result;
				}

				if (Min_Desicion > Result)
				{
					Min_Desicion = Result;
				}
			}
		}
		
	}
	
};

template<typename SomeType>
void Tree<SomeType>::help()
{
	cout << "----------------------------------------------------" << endl;
	cout << "This is a Tree, Current_Node statement is:" << endl;
	cout << "Data: " << this->CurrentNode->Data << "; Level: " << this->CurrentNode->Level << "; Vertexes: " << this->Vertexes << ";" << endl;
	cout << "----------------------------------------------------" << endl;
	cout << "Choose what you want:" << endl;
	cout << "If you want to go next leaf: type N" << endl;
	cout << "If you want to go previous leaf: type P" << endl;
	cout << "if you want to add a new leaf to current one: type A" << endl;
	cout << "if you want to execute a special algorythm: type F" << endl;
	cout << "If you want to exit a program, type E" << endl;
	cout << "----------------------------------------------------" << endl;
}

int main()
{
	int data = 0;
	int Vertexes = 0;
	
	cout << "-----------------------------------------------------------------------" << endl;
	cout << "This is a program for editing a binar tree, do you want to start? (y/n)" << endl;
	cout << "-----------------------------------------------------------------------" << endl;
	char command = ' ';
	int pos = 0;
	cin >> command;
	if (command == 'y')
	{
		
		cout << "Enter a Tree root data: ";
		cin >> data;
		cout << endl;
		cout << "Enter a number of vertex maximum: ";
		cin >> Vertexes;
		cout << endl;
		system("cls");
		
		Tree<int> NewTree{ Vertexes , data };
		NewTree.help();
		while (true)
		{	
			cout << "Choose wisely: ";	
			cin >> command;
		
			system("cls");
			NewTree.help();
			cout << endl;
			if ((command != 'N') && (command != 'P') && (command != 'A') && (command != 'E') && (command != 'F'))
			{
				cout << "Invalid command, try else." << endl;
				continue;
			}
			if (command == 'N') 
			{
				cout << "Choose a position where we go: (1->n) ";
				cin >> pos;
				NewTree.go_next(pos);
				system("cls");	// Из-за этого ошибок нет.
				NewTree.help();
			}
			if (command == 'P') 
			{
				NewTree.go_back();
				system("cls");
				NewTree.help();
				
			}
			if (command == 'A') 
			{
				cout << "Choose a position for adding: (1->n) " << endl;
				cin >> pos;
				int data;
				cout << "Enter data: " << endl;			
				cin >> data;
				if (!cin) 
				{
					cin.clear(); 
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
					cout << "Wrong data, try else." << endl;
					continue;
				}
				NewTree.add_leaf(pos, data);
				system("cls");
				NewTree.help();
			}
			if (command == 'F') 
			{
					if (NewTree.Vertexes != 2) 
					{
						cout << "This is non-binar tree, try else." << endl;
						system("cls");
						NewTree.help();
						continue;
					}
					else 
					{
						NewTree.Special_Algorythm(NewTree.TreeRoot);
						cout << "Max: " << Max_Desicion << " Min: " << Min_Desicion << endl;
					}
			}
			if (command == 'E') 
			{
				system("cls");
				cout << "See you later!" << endl;
				cout << endl;
				break;
			}
		}
	
	}
	else 
	{
		system("cls");
		cout << "See you later!" << endl;
	}
	
};