//Michael Lawrence

//This file is the header for the base class vehicle
//and its three derived classes, car, scooter and bike.
#include "help.h"

const int OREGON_LICENSE = 6;

struct trip
{
	//used to calculate money made by the client.
	int hours;
	float fare;
	int type;
};


class vehicle
{
	//this is an abstract base class with three
	//children.
	public:
		vehicle();
		//The type is used for specific printed
		//messages.
		vehicle(int type);
		vehicle(const vehicle & to_copy);
		//a virtual destructor
		virtual ~vehicle();
		virtual void display() = 0;	
		virtual int check_in(trip & to_fill) = 0;
		//this function changes out to true.
		void check_out();
		//if it is in and not broken returns true
		bool available();
		//if the id matches and in return 1
		//id match and out return 2
		//id not match return 0
		int match(int to_compare);
		//if it needs to be repaired, return true
		bool broken();
		//returns the distance. This is used
		//to check out the closest vehicle.
		float get_distance();

	protected:
		char * street1;
		char * street2;
		float distance;
		int id;
		float hourly;
		bool out;
		bool repair;

};

class car: public vehicle
{
	public:
		car();
		car(int type);
		car(const car & to_copy);
		~car();
		void display();
		int check_in(trip & to_fill);
		void change_license();

	protected:
		char * license;
		float gas_left;
};

class scooter: public vehicle
{
	public:
		scooter();
		scooter(int type);
		void display();
		int check_in(trip & to_fill);
	
	protected:
		float battery_level;

};

class bike: public vehicle
{
	public:
		bike();
		bike(int type);
		void display();
		int check_in(trip & to_fill);

};

