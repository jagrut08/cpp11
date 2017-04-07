#include <iostream>
#include <string>
#include "Car.h"

using namespace std;

// Implementation of methods for Vehicle

string Vehicle::get_description() const {
    return "License Plate: " + license_plate + ", Capacity: " + to_string(get_num_passengers());
  }

void Vehicle::set_license_plate(const string& l) {
    license_plate = l;  
  }

void Vehicle::set_num_passengers(const int& n) {
    num_passengers = n;
  }

string Vehicle::get_license_plate() const {
    return license_plate;
  }

size_t Vehicle::get_num_passengers() const {
    return num_passengers;
  }

void Vehicle::print() const {
    cout << get_description(); 
  }

// Implementation of methods for Car
  
 string Car::get_brand_description() const { 
    return Car_brand_description[brand];
  }
 string Car::get_description() const {
    return Vehicle::get_description() + ", Brand: " + get_brand_description();
  }

 void Car::set_brand(const Car_brand& b) {
    brand = b;
 }

 Car_brand Car::get_brand() const {
    return brand;
 }

 void Car::print() const {
    cout << get_description();
 }

// Implementation of methods for SUV

 string SUV::get_description() const {
    string temp = Car::get_description() + ", Car Type: SUV, Optional Third Row Seat: ";
    return third_row_seat == true ? temp + "Present\n" : temp + "Absent\n";
  }

 void SUV::set_third_row_seat(bool has_third_row_seat) {
    third_row_seat = has_third_row_seat;
 }

 bool SUV::get_third_row_seat() const {
    return third_row_seat;
 }

 // An SUV's passenger count increases by three if it has a third row seat

  size_t SUV::get_num_passengers() const {
    return Car::get_num_passengers() + (third_row_seat ? 3 : 0);
  }

  void SUV::print() const {
    cout << get_description();
  }

 // Implementation of methods for Sedan

  string Sedan::get_description() const {
    string temp = Car::get_description() + ", Car Type: Sedan, Sport Package: ";
    return sport_package == true ? temp + "Present\n" : temp + "Absent\n";
  }

  void Sedan::set_sport_package(bool has_sport_package) {
    sport_package = has_sport_package;
  }
  
  bool Sedan::get_sport_package() const {
    return sport_package;
  }
  
  void Sedan::print() const {
    cout << get_description();
  }