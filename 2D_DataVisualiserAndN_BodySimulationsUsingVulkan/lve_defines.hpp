#pragma once


constexpr int DOMAIN_WIDTH = 1500;
constexpr int DOMAIN_HEIGHT = 1000;

//#define USE_DISCRETE_GPU 1 //0 for no otherwise yes
//#define DEPTH_OF_SIERPINSKI_TRIANGLE 1
//uncomment the one you would like to use otherwise it uses Vsync mode 
//#define USE_MAILBOX_MODE  // low latency, not alwys supported, high power consumption
// to use mailbow we need to enable USE_DISCRETE_GPU in lve_device.cpp
//#define USE_IMMEDIATE_MODE  // high power consumption, tearing, low latency, usualy supported
//othervise uses Vsync mode  // always supported, good for mobile, vsync bound, latency