//Michael Lawrence

//The node and doubly linked list functions.

#include "list.h"


node::node()
{
	//0 value constructor.

	data = NULL;
	next = NULL;
	previous = NULL;
}

node::node(int type)
{
	//the user gets to decide the type of vehicle in the node.
	if(type == 1)
	{
		data = new car(1);
	}	
	else if(type == 2)
	{
		data = new scooter(2);
	}
	else if(type == 3)
	{
		data = new bike(3);
	}
	next = NULL;
	previous = NULL;
}

node::node(const node & to_copy)
{
	//copy constructor
	//in order to copy the node we need to
	//do RTTI to find what the node contains.
	next = to_copy.next;
	previous = to_copy.previous;
	if(car * copy_car = dynamic_cast<car*>(to_copy.data))
	{
		data = new car(*copy_car);
	}	
	else if(scooter * copy_scooter = dynamic_cast<scooter*>(to_copy.data))
	{
		data = new scooter(*copy_scooter);
	}
	else if(bike * copy_bike = dynamic_cast<bike*>(to_copy.data))
	{
		data = new bike(*copy_bike);
	}
}

node::~node()
{
	//the arrays in data are deleted by
	//their destructors.
	delete data;
	data = NULL;
	next = NULL;
	previous = NULL;
}

node * & node::go_next()
{
	//used to traverse next.
	return next;
}

node * & node::go_back()
{
	//used to traverse back.
	return previous;
}

//these functions are wrappers for various
//vehicle functions.

void node::display()
{
	//displays the vehicles info.
	data->display();
}

float node::get_distance()
{
	//used to sort vehicles by their distance.
	data->get_distance();
}

int node::get_type()
{
	//returns the type of the vehicle in the node.
	//Used by the check_out function.
	//It is necessary to know which vehicle it is
	//because the user might not want a vehicle
	//of this type. This is why we cannot use
	//simply dynamic binding here.
	if(car * my_car = dynamic_cast<car*>(data))
	{
		return 1;
	}	
	else if(scooter * my_scooter = dynamic_cast<scooter*>(data))
	{
		return 2;
	}
	else if(bike * my_bike = dynamic_cast<bike*>(data))
	{
		return 3;
	}
}

//more wrappers.
bool node::available()
{
	//checks if a vehicle is in and not broken
	return data->available();
}

bool node::repair()
{
	//checks if a vehicle is broken.
	return data->broken();
}

int node::match(int id)
{
	//checks if the id is a match.
	return data->match(id);
}

int node::check_out()
{
	//checks out a vehicle.
	data->check_out();
	return 1;
}

int node::check_in(trip & to_fill)
{
	//checks in a vehicle. Sends in a struct
	//to be filled for profit calculation.
	return data->check_in(to_fill);
}

int node::change_license()
{
	//changes a cars license plate.
	//only cars have license plates so we can only
	//change the plate if it is a car. This function
	//is unique to car.
	if(car * my_car = dynamic_cast<car*>(data))
	{
		my_car->change_license();
		return 1;
	}	
	else if(scooter * my_scooter = dynamic_cast<scooter*>(data))
	{
		return 0;
	}
	else if(bike * my_bike = dynamic_cast<bike*>(data))
	{
		return 0;
	}
}

void node::set_next(node * to_set)
{
	//sets the next pointer
	next = to_set;
}

void node::set_back(node * to_set)
{
	//sets the previous pointer.
	previous = to_set;
}








DLL::DLL()
{
	//0 value constructor.
	head = NULL;
	tail = NULL;

}

DLL::DLL(const DLL & to_copy)
{
	head = NULL;
	tail = NULL;
	//calls recursive copy
	//functions.
	copy(head, to_copy.head);
}

void DLL::copy(node *& head, node * to_copy)
{
	//this function copies a doubly linked list.
	if(!to_copy)
	{
		return;
	}
	head = new node(*to_copy);
	//if the pointers of to_copy are NULL
	//the pointers of head will also be NULL.
	//otherwise the pointers will have to be reset
	//later. A new node will reset the next pointer.
	copy(head->go_next(), to_copy->go_next());
	if(head)
	{
		if(!head->go_next())
		{
			//sets tail.
			tail = head;
		}
		else
		{
			//resets all the previous pointers
			head->go_next()->set_back(head);
		}
	}
	return;
}

DLL::~DLL()
{
	destroy(head);
}

void DLL::destroy(node * head)
{
	//recursive destroy.
	if(!head)
		return;
	destroy(head->go_next());
	delete head;
	return;
}

int DLL::insert()
{
	//inserts a vehicle.
	//this is a wrapper.
	cout << "adding" << endl;
	cout << "1 - car" << endl;
	cout << "2 - scooter" << endl;
	cout << "3 - bike" << endl;
	int user_input;
	cin >> user_input;
	cin.ignore(100, '\n');
	//calls the recursive insert.
	node * temp = new node(user_input);
	return insert(temp, head, head);	
}

int DLL::insert(node * temp, node *& head, node * previous)
{
	//recursive insert.
	if(!head)
	{
		head = temp;
		//head->set_next(NULL);
		if(previous)
		{
			head->set_back(previous);	
			previous->set_next(head);
			//if previous is not NULL then
			//this is not the first item in
			//the list.
		}
		tail = head;
		return 1;
	}
	float sort = head->get_distance();
	float add = temp->get_distance();
	if(sort >= add)
	{
		//sorting by distance, largest to smalles.
		head->set_back(temp);
		temp->set_next(head);
		if(previous != head)
		{
			//if this is not the first item
			//in the list, then we need to
			//set the node behind correctly.
			temp->set_back(previous);
			previous->set_next(temp);
		}
		else
		{
			//if this is the first item in
			//the list we need to reset head.
			temp->set_back(NULL);
			head = temp;
		}
		
	}
	else
	{
		//if an insert didn't happen, recursive call.
		previous = head;
		insert(temp, head->go_next(), previous);
	}
	return 1;
}

void DLL::display()
{
	//display wrapper.
	display(head);
}

void DLL::display(node * head)
{
	//recursive display.
	if(!head)
		return;
	head->display();
	display(head->go_next());
	return;
}


int DLL::check_out(int type)
{
	//check out wrapper.
	return check_out(type, head);	
}

int DLL::check_out(int type, node * head)
{
	//finds the closest vehicle of the given type.
	//checks it out for the user.
	if(!head)
	{
		return 0;
	}
	//the vehicle must be of the same type
	//and available.
	if(head->get_type() == type && head->available())
	{
		if(type == 1)
		{
			cout << "This is the nearest car to you." << endl;
		}
		else if(type == 2)
		{
			cout << "This is the nearest scooter to you." << endl;
		}
		else if(type == 3)
		{
			cout << "This is the nearest bike to you." << endl;
		}
		head->display();
		head->check_out();	
		return 1;
	}
	//otherwise recursive call.
	return check_out(type, head->go_next());
}

int DLL::repair()
{
	//repair wrapper.
	return repair(head);
}

int DLL::repair(node *& head)
{
	//recursively removes all vehicles
	//that need to be repaired.
	int success = 0;
	if(!head)
		return 0;
	if(head->repair())
	{
		//we need to hold onto the node
		//we need to delete.
		node * temp = head;
		if(head->go_next())
		{
			//if this is not the end of the list
			//we need to reset the previous
			//pointer for the next node.
			head->go_next()->go_back() = head->go_back();
		}
		else
		{
			//otherwise me need to move tail.
			tail = head->go_back();
		}
		//traverses head.
		head = head->go_next();
		delete temp;
		success = 1;
	}
	if(head)
	{
		success = repair(head->go_next());
	}
	return success;
}

int DLL::check_in(int id, trip & to_fill)
{
	//check in wrapper.
	return check_in(id, to_fill, head);
}

int DLL::check_in(int id, trip & to_fill, node * head)
{
	//checks in a vehicle with the same id.
	if(!head)
		return 0;
	int compare = head->match(id);
	//if the vehicle is already in, we can't
	//check it in.
	if(compare == 1)
	{
		return 1;
	}
	//if the vehicle is out we check in.
	else if(compare == 2)
	{
		head->check_in(to_fill);
		return 2;
	}
	//if it is not a match we go to the next vehicle.
	return check_in(id, to_fill, head->go_next());
}

int DLL::change_license(int id)
{
	//changes license plate wrapper.
	return change_license(id, head);
}

int DLL::change_license(int id, node * head)
{
	//recursively finds the right vehicle
	//to attempt to change the license plate
	//of.
	if(!head)
		return 0;
	//if the vehicle is a match we change its license
	int compare = head->match(id);
	if(compare)
	{
		return head->change_license();
	}
	return change_license(id, head->go_next());
}





client::client()
{
	total = 0.0;
	total_car = 0.0;
	total_scooter = 0.0;
	total_bike = 0.0;
}

int client::manage()
{
	//this function allows the user to control
	//the program.
	cout << "1 - display" << endl;
	cout << "2 - add new" << endl;
	cout << "3 - check out" << endl;
	cout << "4 - repair" << endl;
	cout << "5 - check in" << endl;
	cout << "6 - change car license plate" << endl;
	cout << "7 - see money" << endl;
	cout << "8 - quit" << endl;
	
	int user;
	cin >> user; 
	cin.clear();
	cin.ignore(100, '\n');

	if(user == 1)
	{
		//displays the whole fleet
		fleet.display();
		cout << endl;
	}
	else if(user == 2)
	{
		//inserts a vehicle.
		fleet.insert();
	}
	else if(user == 3)
	{
		//allows the user to check out a vehicle
		//of a certain type.
		cout << "Would you like to check out a" << endl;
		cout << "1 - car" << endl;
		cout << "2 - scooter" << endl;
		cout << "3 - bike" << endl;
		cin >> user;
		cin.clear();
		cin.ignore(100, '\n');
		int success = fleet.check_out(user);
		if(success)
		{
			if(user == 1)
			{
				cout << "you have checked out the car." << endl;				
			}
			else if(user == 2)
			{
				cout << "you have checked out the scooter." << endl;				
			}
			else if(user == 3)
			{
				cout << "you have checked out the bike." << endl;				
			}
		}
		else
		{
			if(user == 1)
			{
				cout << "you could not check out car." << endl;				
			}
			else if(user == 2)
			{
				cout << "you could not check out a scooter." << endl;				
			}
			else if(user == 3)
			{
				cout << "you could not check out a bike." << endl;				
			}	
		}
	}
	else if(user == 4)
	{
		//removes all broken vehicles
		//for repair.
		fleet.repair();
		cout << "The broken vehicles have been removed for repair." << endl;
	}
	else if(user == 5)
	{
		//checks in a vehicle with a matching id number
		cout << "What is the id number." << endl;
		cin >> user;
		cin.clear();
		cin.ignore(100, '\n');
		//the trip struct is used to calculate
		//money made.
		int success = fleet.check_in(user, a_trip);
		if(success == 0)
		{
			cout << "No vehicles of that id exist." << endl;
		}
		else if(success == 1)
		{
			cout << "That vehicle is already in." << endl;
		}
		else if(success == 2)
		{
			cout << "The vehicle has been check in." << endl;
			//the trip struct calculates money
			//based on user input in the check
			//in functions.
			total += a_trip.hours * a_trip.fare;
			if(a_trip.type == 1)
			{
				total_car += a_trip.hours * a_trip.fare;
			}
			else if(a_trip.type == 2)
			{
				total_scooter += a_trip.hours * a_trip.fare;
			}
			else if(a_trip.type == 3)
			{
				total_bike += a_trip.hours * a_trip.fare;

			}
		}

	}
	else if(user == 6)
	{
		//changes the license plate of a car
		//with a given id.
		cout << "What is the id of the car you would like to change." << endl;
		cin >> user; cin.clear(); cin.ignore(100, '\n');
		int success = fleet.change_license(user);	
		if(success)
		{
			cout << "The license has been changed." << endl;
		}
		else
		{
			cout << "The license could not be changed." << endl;
		}
	}
	else if(user == 7)
	{
		//display money made.
		display_money();
	}
	else
	{
		return 0;
	}
	return 1;
}


void client::display_money()
{
	//displays money made.
	cout << "The money you have earned so far is " << endl;
	cout << "total - " << total << endl;
	cout << "car - " << total_car << endl;
	cout << "scooter - " << total_scooter << endl;
	cout << "bike - " << total_bike << endl;
}

