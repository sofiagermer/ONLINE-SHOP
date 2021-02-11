//
// Created by sofia on 28/12/20.
//

#include "truck.h"

Truck::Truck(int capacity) {
    avaiable_volume = capacity;
    this->capacity = capacity;
}

Truck::Truck(int avaiable_volume, int capacity) {
    this->avaiable_volume = avaiable_volume;
    this->capacity = capacity;
}

int Truck::getAvaiableVolume() const {
    return avaiable_volume;
}

int Truck::getCapacity() const {
    return capacity;
}
bool Truck::operator<(const Truck &t) const {
    return avaiable_volume < t.getAvaiableVolume();
}

void Truck::addOrder(int volume) {
    avaiable_volume -= volume;
}

ostream &operator<<(ostream &out, const Truck &truck) {
    out << to_string(truck.getAvaiableVolume()) << " ; " << to_string(truck.getCapacity()) << endl;
    return out;
}

