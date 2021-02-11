#pragma once

#include "product.h"

class Truck {
private:
    int avaiable_volume;
    int capacity;

public:
    /**
     * Truck constructor that creates a truck with a given maximum capacity
     * Initially avaiable_volume is equal to capacity because the truck is empty
     * @param avaiable_volume
     */
    Truck (int capacity);

    /**
     * Truck constructor that creates a truck with a given avaiable_volume and capacity ( through reading of files)
     * Initially avaiable_volume is different from capacity because this are already shop's trucks
     * @param avaiable_volume
     */
    Truck(int avaiable_volume, int capacity);
    /**
     * Function that returns the value "avaiable_volume"
     * @param avaiable_volume
     */
    int getAvaiableVolume() const;

    /**
     *
     * @return
     */
    int getCapacity() const;

    void addOrder(int volume);

    /**
     * Operator overloading used for comparing two trucks in function of their avaiable volume
     * @param t
     * @return true if the avaiable_volume is smaller than t's avaiable_volume
     */
    bool operator < (const Truck &t) const;

    friend ostream& operator<<(ostream& out, const Truck &truck);
};



