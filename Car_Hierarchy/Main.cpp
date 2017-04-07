#include <iostream>
#include <vector>
#include <string>
#include "Car_rental.h"

using namespace std;

int main() {

  Car_rental c; 

  // Add Cars to inventory. Car constructor arguments are: license plate, capacity, brand and whether it has optional features (default is false)

  c.add_car(make_shared<SUV>("SUV1", 2, Car_brand::Honda));		   
  c.add_car(make_shared<SUV>("SUV2", 4, Car_brand::Toyota, true)); // Has optional third row seat, so capacity = 4 + 3
  c.add_car(make_shared<Sedan>("SEDAN1", 4, Car_brand::Honda));
  c.add_car(make_shared<Sedan>("SEDAN2", 4, Car_brand::Toyota, true));
 
  // Print information about all Cars in the inventory
	
  c.print_inventory();
 
  // Add Cars with no license plate	(license plate not assumed to be unique)

  c.add_car(make_shared<Sedan>("", 4, Car_brand::Toyota, true)); 
  c.add_car(make_shared<Sedan>("", 6, Car_brand::Ford, false)); 

  // Query cars based on license plate

  cout << "\nCapacity of cars with license plate SUV2:\n";
 
  vector<shared_ptr<Car>> result = c.find_cars("SUV2");
  for(const auto it : result) cout << it->get_license_plate() + ", Capacity: " + to_string(it->get_num_passengers()) + '\n';

 }