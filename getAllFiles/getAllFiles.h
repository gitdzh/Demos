//
// Created by dzh on 18-9-12.
//

#ifndef GETALLFILES_GETALLFILES_H
#define GETALLFILES_GETALLFILES_H

// C++
#include<iostream>
#include<string>
#include<vector>
#include<algorithm> // for sort

#ifndef LINUX
#define LINUX
#endif

#ifdef LINUX
#include<dirent.h>
//#include<unistd.h>
#endif

#ifdef WIN32
#include<dirent.h>
//include<io.h>
#endif

// OpenCV
#include<opencv2/opencv.hpp>

// function
std::vector<std::string> getFiles(std::string cate_dir);

#endif //GETALLFILES_GETALLFILES_H
