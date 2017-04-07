#if !defined CAR_H
#define CAR_H

#include <string>
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

  string get_description() const;

  public:

  // Constructors and Destructor

  Vehicle() : license_plate(""), num_passengers(0) {}

  Vehicle(const string& l, const size_t& n) : license_plate(l), num_passengers(n) {}
  
  Vehicle(const Vehicle& v) : license_plate(v.license_plate), num_passengers(v.num_passengers) {}
  
  virtual ~Vehicle() {}

  // Setters

  void set_license_plate(const string& l);
 
  void set_num_passengers(const int& n);

  // Getters

  string get_license_plate() const;

  // get_num_passengers() is declared virtual as subclasses are expected to override it if necessary

  virtual size_t get_num_passengers() const;
    
  // Other methods

  virtual void print() const;
};

class Car : public Vehicle {

  Car_brand brand;

  // Formatting a Car's brand string is encapsulated as a private method in Car

  string get_brand_description() const;

  protected: 

  // Description is needed by subclasses to provide a complete description of themselves

  string get_description() const;

  public:

  // Constructors and Destructor

  Car(): Vehicle(), brand(Car_brand::Unknown) {} 

  Car(const string& l, size_t n, const Car_brand& b) : Vehicle(l, n), brand(b) {} 

  Car(const Car& c) : Vehicle(c.get_license_plate(), c.get_num_passengers()), brand(c.get_brand()) {}  

  virtual ~Car() {} 

  // Setters

  void set_brand(const Car_brand& b);

  // Getters

  Car_brand get_brand() const;

  // Other methods

  virtual void print() const;
};

// Class SUV. Overrides Vehicle's get_num_passengers() 

class SUV : public Car {
  
  bool third_row_seat;

  // An SUV's description is encapsulated as a private method in the SUV class

  string get_description() const;

  public: 
  
  // Constructors and Destructor

  SUV() : Car(), third_row_seat(false) {}
  
  SUV(const string& l, const int& n, const Car_brand& b, bool has_third_row_seat = false) : Car(l, n, b), third_row_seat(has_third_row_seat) {}
  
  SUV(const SUV& s) : Car(s.get_license_plate(), s.get_num_passengers(), s.get_brand()), third_row_seat(s.get_third_row_seat()) {}
  
  ~SUV() {}
  
  // Setters

  void set_third_row_seat(bool has_third_row_seat);

  // Getters

  bool get_third_row_seat() const;

  // An SUV's passenger count increases by three if it has a third row seat

  size_t get_num_passengers() const;

  // Other methods

  void print() const;
};

// Class Sedan. Utilizes Car's get_num_passengers() rather than overriding it

class Sedan : public Car {

  bool sport_package;

  // A Sedan's description is encapsulated as a private method in the Sedan class

  string get_description() const;

  public: 

  // Constructors and Destructor

  Sedan() : Car(), sport_package(false) {}

  Sedan(const string& l, const int& n, const Car_brand& b, bool has_sport_package = false) : Car(l, n, b), sport_package(has_sport_package) {}

  Sedan(const Sedan& s) : Car(s.get_license_plate(), s.get_num_passengers(), s.get_brand()), sport_package(s.get_sport_package()) {}

  ~Sedan() {}

  // Setters

  void set_sport_package(bool has_sport_package);

  // Getters
  
  bool get_sport_package() const;

  // Other methods
  
  void print() const;
};

#endif // CAR_H