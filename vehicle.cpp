//Michael Lawrence

//These are the base class vehicle functions
//and its derived classes, car, scooter, and bike.

#include "vehicle.h"


vehicle::vehicle()
{
	//0 value constructor.
	street1 = NULL;
	street2 = NULL;
	distance = 0.0;
	id = 0;
	hourly = 0.0;
	out = false;
	repair = false;
}

vehicle::vehicle(int type)
{
	//creates a new vehicle. The type number is used
	//for printing the write print statements.

	//char new takes a char * by reference and fills
	//the array.

	cout << "please enter the first cross street." << endl;
	char_new(street1);
	cout << "please enter the second cross street." << endl;
	char_new(street2);
	cout << "please enter the distance in miles." << endl;
	cin >> distance; cin.clear(); cin.ignore(100, '\n');
	cout << "please enter the id number." << endl;
	cin >> id; cin.clear(); cin.ignore(100, '\n');
	
	//the user indicates which vehicle type they want.
	//then the appropriate hourly rate is selected.
	if(type == 1)
	{
		//the wording is different depending on the
		//vehicle.
		hourly = 20.00;
		cout << "Is the car checked out. yes or no." << endl;
	}
	else if(type == 2)
	{
		hourly = 12.50;
		cout << "Is the scooter checked out. yes or no." << endl;
	}
	else if(type == 3)
	{
		hourly = 7.25;
		cout << "Is the bike checked out. yes or no." << endl;
	}
	
	char * temp; char_new(temp); 
	//determines if the vehicle is out or not.	
	if(temp[0] == 'y' || temp[0] == 'Y')
	{
		out = true;
	}
	else
	{
		out = false;
	}
	delete [] temp;
	if(out == false)
	{
		//if the car is currently being used we do not have
		//information on whether it needs to be repaired or not.
		if(type == 1)
			cout << "Does the car need to be repaired. yes or no." << endl;
		else if(type == 2)
			cout << "Does the scooter need to be repaired. yes or no." << endl;
		else if(type == 3)
			cout << "Does the bike need to be repaired. yes or no." << endl;
		char_new(temp);
		//checks if it needs to be repaired.
		if(temp[0] == 'y' || temp[0] == 'Y')
		{
			repair = true;
		}
		else
		{
			repair = false;
		}
		delete [] temp;
	}
	else
	{
		repair = false;
	}	
	//informs the user of the hourly rate.
	cout << "The hourly rate is " << hourly << "." << endl;

}

vehicle::vehicle(const vehicle & to_copy)
{
	//copies a vehicle.
	//both arrays of character are copied
	//with the help.h function copy_array.
	//this saves the hassle of repetitavely
	//allocating new arrays.
	copy_array(street1, to_copy.street1);
	copy_array(street2, to_copy.street2);
	distance = to_copy.distance;
	id = to_copy.id;
	hourly = to_copy.hourly;
	out = to_copy.out;
	repair = to_copy.repair;	
}

vehicle::~vehicle()
{
	//destroys vehicle.
	//the only dynamic memory is
	//the two arrays.
	delete [] street1;
	street1 = NULL;
	delete [] street2;
	street2 = NULL;
}

bool vehicle::available()
{
	//checks if a vehicle is available.
	if(out || repair)
	{
		//the vehicle is unaivalable if it
		//is out or needs to be repaired.
		return false;
	}
	else
	{
		return true;
	}
}

bool vehicle::broken()
{
	//checks if the vehicle is broken.
	if(!out && repair)
	{
		//checks if it needs to be repaired.
		//used by the repair function.
		return true;
	}
	else
	{
		return false;
	}
}

int vehicle::match(int to_compare)
{
	//checks if the id is a match.
	if(id != to_compare)
	{
		return 0;
	}
	else if(!out)
	{
		//if it is in and the id is a match
		return 1;
	}
	else
	{
		//if it is out and the id is a match.
		return 2;
	}

}

void vehicle::check_out()
{
	//checks if a vehicle out.
	out = true;
	
}

float vehicle::get_distance()
{
	//gets the vehicles distance.
	return distance;
}


car::car()
{
	//car default constructor.
	license = NULL;
	gas_left = 0.0;
}

car::car(int type): vehicle(type)
{	
	//creates a car.
	//this char new function takes a specific size.
	//oregons license plate has six
	cout << "Please enter the 6 digit license number." << endl;
	char_new(license, 6);
	cout << "Please enter the gallons left in the tank." << endl;
	cin >> gas_left; cin.clear(); cin.ignore(100, '\n');
}

car::car(const car & to_copy): vehicle(to_copy)
{
	//copies over the array like above.
	copy_array(license, to_copy.license);
	gas_left = to_copy.gas_left;
}

car::~car()
{
	//destroys a car
	delete [] license;
	license = NULL;
}

void car::display()
{
	//this is a dynamically bound display function
	//that makes sense for a car.
	cout << "The cross streets are " << street1 << " and " << street2 << "." << endl;
	cout << "This car is " << distance << " miles away." << endl;
	cout << "The car's id is " << id << "." << endl;
	cout << "The hourly rate for a car is " << hourly << "." << endl;
	cout << "The license number is " << license << "." << endl;
	cout << "This car has " << gas_left << " gallons of gas left." << endl;	
	if(out)
	{
		cout << "This car is currently being used." << endl;
	}
	else if(repair)
	{
		cout << "This car needs to be repaired." << endl;
	}
	else
	{
		cout << "This car is available." << endl;
	}
	cout << endl;
}

int car::check_in(trip & to_fill)
{
	//dynamically bound function to check the
	//car in
	
	//the passed in struct helps the above
	//function calculate the money earned.
	cout << "How many hours was this vehicle out." << endl;
	cin >> to_fill.hours;
	cin.clear();
	cin.ignore(100, '\n');
	to_fill.fare = hourly;
	to_fill.type = 1;

	cout << "How much gas is left." << endl;
	cin >> gas_left;
	cin.clear();
	cin.ignore(100, '\n');
	//lets the user refill the tank.
	cout << "Would you like to fill the tank." << endl;
	cout << "1 - yes" << endl;
	cout << "2 - no" << endl;
	int user;
	cin >> user;
	cin.clear();
	cin.ignore(100, '\n');
	if(user)
	{
		gas_left = 40.00;
	}

	int random = rand() % 2;
	if(random)
	{
		//there is a one in two chance that the car
		//will be broken.
		repair = true;
		cout << "This car needs to be repaired." << endl;
	}	
	out = false;
	return 1;
}

void car::change_license()
{
	//this function is unique to car and so
	//requires RTTI.
	delete [] license;
	cout << "Enter the new license." << endl;
	char_new(license, 6);
}





scooter::scooter()
{
	battery_level = 0.0;
}

scooter::scooter(int type): vehicle(type)
{
	//reads in the battery level.
	cout << "Please enter the battery level in a percentage." << endl;
	cin >> battery_level; cin.clear(); cin.ignore(100, '\n');
}

void scooter::display()
{
	//a dynamically bound display for scooter.
	cout << "The cross streets are " << street1 << " and " << street2 << "." << endl;
	cout << "This scooter is " << distance << " miles away." << endl;
	cout << "The scooter's id is " << id << "." << endl;
	cout << "The hourly rate for a scooter is " << hourly << "." << endl;
	cout << "This scooter has " << battery_level << " percent battery left." << endl; 
	if(out)
	{
		cout << "This scooter is currently being used." << endl;
	}
	else if(repair)
	{
		cout << "This scooter needs to be repaired." << endl;
	}
	else
	{
		cout << "This scooter is available." << endl;
	}
	cout << endl;
}

int scooter::check_in(trip & to_fill)
{
	//works the same as the car function but with battery,
	//not gas.
	cout << "How many hours was this vehicle out." << endl;
	cin >> to_fill.hours;
	cin.clear();
	cin.ignore(100, '\n');
	to_fill.fare = hourly;
	to_fill.type = 2;
	
	cout << "How much battery is left." << endl;
	cin >> battery_level;
	cin.clear();
	cin.ignore(100, '\n');

	cout << "Would you like to recharge." << endl;
	cout << "1 - yes" << endl;
	cout << "2 - no" << endl;
	int user;
	cin >> user;
	cin.clear();
	cin.ignore(100, '\n');
	if(user)
	{
		battery_level = 100.0;
	}

	int random = rand() % 2;
	if(random)
	{
		repair = true;
		cout << "This scooter needs to be repaired." << endl;
	}	
	out = false;
	return 1;
}





bike::bike(int type): vehicle(type)
{
	//the bike has no new data
	//it only needs new display and check in
	//functions
}

bike::bike()
{
	//the bike has no new data.

}

void bike::display()
{
	//a dynamically bound display for the bike.
	cout << "The cross streets are " << street1 << " and " << street2 << "." << endl;
	cout << "This bike is " << distance << " miles away." << endl;
	cout << "The bike's id is " << id << "." << endl;
	cout << "The hourly rate for a bike is " << hourly << "." << endl;
	if(out)
	{
		cout << "This bike is currently being used." << endl;
	}
	else if(repair)
	{
		cout << "This bike needs to be repaired." << endl;
	}
	else
	{
		cout << "This bike is available." << endl;
	}
	cout << endl;
}

int bike::check_in(trip & to_fill)
{
	//a dynamically bound check in for the bike
	cout << "How many hours was this vehicle out." << endl;
	cin >> to_fill.hours;
	cin.clear();
	cin.ignore(100, '\n');
	to_fill.fare = hourly;
	to_fill.type = 3;
	
	int random = rand() % 2;
	if(random)
	{
		repair = true;
		cout << "This scooter needs to be repaired." << endl;
	}	
	out = false;
	return 1;
}
