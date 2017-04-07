#if !defined CAR_RENTAL_H
#define CAR_RENTAL_H

#include <memory>
#include <list>
#include <vector>
#include "Car.h"

using namespace std;

/*
Car_rental encapsulates the rental company's data store. It uses shared_ptr<Car> to store pointers to instances of Cars (SUVs or Sedans). This allows
invoking methods on Car's derived classes via a single interface (base class pointer->method()) and the appropriate method gets called due to 
run time polymorphism.

The benefit of using pointers is that Car objects aren't stored in the Car_rental object. Otherwise the Car_rental object would bloat up
as more data fields are added to the Car class hierarchy. Also, Car objects don't need to be copied while returning the results of a search query. 
  
The drawback of this approach is that a pointer needs to be de-referenced to get a Car's attributes, which slows down run time performance vs. 
having direct access to the object.
*/

class Car_rental {

  /* A list is used to store Car pointers. It allows for efficient updates at the end (e.g, adding a new Car pointer), as well as in the middle 
	 (e.g., deleting a random Car pointer). However, traversing the list is slower than traversing a vector<> due to non-contiguous location of elements
     in memory.
 */
	
  list<shared_ptr<Car>> cars;

  /*
   In case license plate were unique, an unordered_map could be used to store and lookup Cars by license plate.
   unordered_map<string, shared_ptr<Car>> car_map; 
   car_map[license_plate] would return a shared_ptr<Car> corresponding to a given license plate
  */
  
  public:
  
  // Constructors and Destructor

  Car_rental() {}
  
  Car_rental(const list<shared_ptr<Car>>& v) : cars(v) {}
  
  Car_rental(const Car_rental& c) : cars(c.cars) {}
  
  ~Car_rental() {}

  // Other methods

  void add_car(shared_ptr<Car> c);

  void print_inventory() const;

  // Find Car(s) by license plate

  vector<shared_ptr<Car>> find_cars(const string& license_plate) const;
};

#endif // CAR_RENTAL_H