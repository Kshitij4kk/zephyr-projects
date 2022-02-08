cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(digital_signature_mangement)

target_sources(app PRIVATE application/src/main.c)

