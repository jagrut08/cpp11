#include "Car_rental.h"

using namespace std;

 void Car_rental::add_car(shared_ptr<Car> c) { 
    cars.emplace_back(c);    
  }

 // Invokes the print() method of the appropriate child class

  void Car_rental::print_inventory() const {
    for(const auto it : cars) it->print(); 
  }

  // Find Car(s) by license plate

  vector<shared_ptr<Car>> Car_rental::find_cars(const string& license_plate) const {

	vector<shared_ptr<Car>> result;
	
	for(const auto it : cars) if(it->get_license_plate() == license_plate) result.emplace_back(it);
	
	return result;
  }