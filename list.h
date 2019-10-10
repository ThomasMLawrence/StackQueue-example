

#include "vehicle.h"


class node
{
	public:
		node();
		//1 is for car, 2 is for scooter, 3 is for bike.
		node(int type);
		node(const node & to_copy);
		~node();
		//returns the next pointer
		node * & go_next();
		//returns the previous pointer.
		node * & go_back();
		//display node
		void display();
		//return distance
		float get_distance();
		//1 is for car, 2 is for scooter, 3 is for bike.
		int get_type();
		//checks out the nearest vehicle. This function
		//allows the user to choose which vehicle.
		int check_out();
		//checks in a vehicle. the to_fill is for
		//calculating profit.
		int check_in(trip & to_fill);
		//returns true if a vehicle can be used.
		bool available();
		//returns true if a vehicle needs to be repaired.
		bool repair();
		//if the id matches and the vehicle is in, returns 		
		//1, if it is out returns 2, if no match returns 0
		int match(int id);
		//sets the next pointer
		void set_next(node * to_set);
		//sets the previous pointer
		void set_back(node * to_set);
		//changes the license plate.
		int change_license();	
	private:
		vehicle * data;
		node * next;
		node * previous;

};

class DLL
{
	public:
		DLL();
		DLL(const DLL & to_copy);
		~DLL();
		//adds a vehicle sorted by distance.
		int insert();
		//displays all the vehicles
		void display();
		//checks out the nearest vehicle of a given type
		//1 for car, 2 for scooter, 3 for bike
		int check_out(int type);
		//checks in the vehicle with the given id.
		int check_in(int id, trip & to_fill);
		//removes all broken vehicles for repair
		int repair();
		//changes the license plate of the vehicle
		//with the given id but only if it is a car.
		int change_license(int id);


	private:
		void copy(node *& head, node * to_copy);
		int change_license(int id, node * head);
		int check_out(int type, node * head);
		int check_in(int id, trip & to_fill, node * head);
		int insert(node * temp, node *& head, node * previous);
		int repair(node *& head);
		void display(node * head);
		void destroy(node * head);
		node * head;
		node * tail;
};

class client
{
	public:
		client();
		//manages the DLL
		int manage();
		//display money made
		void display_money();


	private:
		DLL fleet;
		trip a_trip;
		float total;
		float total_car;
		float total_scooter;
		float total_bike;

};

