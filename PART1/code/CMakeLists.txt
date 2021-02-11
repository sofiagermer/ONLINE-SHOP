cmake_minimum_required(VERSION 3.17)
project(BuyNow)

set(CMAKE_CXX_STANDARD 14)

add_executable(BuyNow BuyNow/main.cpp BuyNow/shop.cpp BuyNow/client.h BuyNow/client.cpp BuyNow/shop.h BuyNow/realshops.h BuyNow/realshops.cpp BuyNow/supplier.h BuyNow/supplier.cpp BuyNow/product.h BuyNow/product.cpp BuyNow/transaction.h BuyNow/transaction.cpp BuyNow/payment.h BuyNow/payment.cpp BuyNow/Menu.h BuyNow/Menu.cpp BuyNow/QuickSort.h)