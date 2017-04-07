#include <iostream>
#include <string>
#include <memory>
#include <list>
#include <vector>

using namespace std;

// Car brands and their descriptive names. Corrections/additions need to be made to the enum and the vector.

enum Car_brand {BMW, Toyota, Honda, Ford, Chrysler, Unknown};
const vector<string> Car_brand_description ({"BMW", "Toyota", "Honda", "Ford", "Chrysler", "Unknown"});

// Class Vehicle. It's the ultimate parent class of the Car hierarchy. Car inherits from Vehicle. SUV and Sedan classes inherit from Car.

class Vehicle {

  string license_plate;
  size_t num_passengers;
  
  protected:

  // Description is needed by subclasses to create a complete description of themselves

  string get_description() const {
    return "License Plate: " + license_plate + ", Capacity: " + to_string(get_num_passengers());
  }

  public:

  // Constructors and Destructor

  Vehicle() : license_plate(""), num_passengers(0) {}

  Vehicle(const string& l, const size_t& n) : license_plate(l), num_passengers(n) {}
  
  Vehicle(const Vehicle& v) : license_plate(v.license_plate), num_passengers(v.num_passengers) {}
  
  virtual ~Vehicle() {}

  // Setters

  void set_license_plate(const string& l) {
    license_plate = l;  
  }

  void set_num_passengers(const int& n) {
    num_passengers = n;
  }
  
  // Getters

  string get_license_plate() const {
    return license_plate;
  }

  // get_num_passengers() is declared virtual as subclasses are expected to override it if necessary

  virtual size_t get_num_passengers() const {
    return num_passengers;
  }

  // Other methods

  virtual void print() const {
    cout << get_description(); 
  }
};

class Car : public Vehicle {

  Car_brand brand;

  // Formatting a Car's brand string is encapsulated as a private method in Car

  string get_brand_description() const { 
    return Car_brand_description[brand];
  }

  protected: 

  // Description is needed by subclasses to provide a complete description of themselves

  string get_description() const {
    return Vehicle::get_description() + ", Brand: " + get_brand_description();
  }

  public:

  // Constructors and Destructor

  Car(): Vehicle(), brand(Car_brand::Unknown) {} 

  Car(const string& l, size_t n, const Car_brand& b) : Vehicle(l, n), brand(b) {} 

  Car(const Car& c) : Vehicle(c.get_license_plate(), c.get_num_passengers()), brand(c.get_brand()) {}  

  virtual ~Car() {} 

  // Setters

  void set_brand(const Car_brand& b) {
    brand = b;
  }

  // Getters

  Car_brand get_brand() const {
    return brand;
  }

  // Other methods

  virtual void print() const {
    cout << get_description();
  }
};

// Class SUV. Overrides Vehicle's get_num_passengers() 

class SUV : public Car {
  
  bool third_row_seat;

  // An SUV's description is encapsulated as a private method in the SUV class

  string get_description() const {
    string temp = Car::get_description() + ", Car Type: SUV, Optional Third Row Seat: ";
    return third_row_seat == true ? temp + "Present\n" : temp + "Absent\n";
  }

  public: 
  
  // Constructors and Destructor

  SUV() : Car(), third_row_seat(false) {}
  
  SUV(const string& l, const int& n, const Car_brand& b, bool has_third_row_seat = false) : Car(l, n, b), third_row_seat(has_third_row_seat) {}
  
  SUV(const SUV& s) : Car(s.get_license_plate(), s.get_num_passengers(), s.get_brand()), third_row_seat(s.get_third_row_seat()) {}
  
  ~SUV() {}
  
  // Setters

  void set_third_row_seat(bool has_third_row_seat) {
    third_row_seat = has_third_row_seat;
  }

  // Getters

  bool get_third_row_seat() const {
    return third_row_seat;
  }

  // An SUV's passenger count increases by three if it has a third row seat

  size_t get_num_passengers() const {
    return Car::get_num_passengers() + (third_row_seat ? 3 : 0);
  }

  // Other methods

  void print() const {
    cout << get_description();
  }
};

// Class Sedan. Utilizes Car's get_num_passengers() rather than overriding it

class Sedan : public Car {

  bool sport_package;

  // A Sedan's description is encapsulated as a private method in the Sedan class

  string get_description() const {
    string temp = Car::get_description() + ", Car Type: Sedan, Sport Package: ";
    return sport_package == true ? temp + "Present\n" : temp + "Absent\n";
  }

  public: 

  // Constructors and Destructor

  Sedan() : Car(), sport_package(false) {}

  Sedan(const string& l, const int& n, const Car_brand& b, bool has_sport_package = false) : Car(l, n, b), sport_package(has_sport_package) {}

  Sedan(const Sedan& s) : Car(s.get_license_plate(), s.get_num_passengers(), s.get_brand()), sport_package(s.get_sport_package()) {}

  ~Sedan() {}

  // Setters

  void set_sport_package(bool has_sport_package) {
    sport_package = has_sport_package;
  }

  // Getters
  
  bool get_sport_package() const {
    return sport_package;
  }

  // Other methods
  
  void print() const {
    cout << get_description();
  }
};

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

  void add_car(shared_ptr<Car> c) { 
    cars.emplace_back(c);    
  }

  void print_inventory() const {
    for(const auto it : cars) it->print(); // Invokes the print() method of the appropriate child class
  }

  // Find Car(s) by license plate

  vector<shared_ptr<Car>> find_cars(const string& license_plate) const {

	vector<shared_ptr<Car>> result;
	
	for(const auto it : cars) if(it->get_license_plate() == license_plate) result.emplace_back(it);
	
	return result;
  }
  
};

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

