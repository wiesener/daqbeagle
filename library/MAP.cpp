//!
//! @file: MAP.cpp
//!
//! @author: constantin
//!
//! @date: 08-Apr-2015 4:19:47 PM
//!
//! @ingroup: retrainer/MAP
//!
//! @brief Implementation of the map class
//!

//
// Copyright (c) TU Berlin
//
#include "MAP.hpp"

MAP::MAP()
#ifdef WITH_HW
 :
mapped(false), map(0), fd(0), count(0)
#endif
{
};

void MAP::openMap(){
#ifdef WITH_HW
    // increase counter
    count++;
    //printf("Map count = %i\n", count);
	// if already mapped do not again
	if(!mapped) {
		fd = open("/dev/mem", O_RDWR);
		if(fd == -1) {
			perror("Unable to open /dev/mem");
			exit(EXIT_FAILURE);
		}
		map = (uint32_t*) mmap(NULL, MMAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, MMAP_OFFSET);
		if(map == MAP_FAILED) {
			close(fd);
			perror("Unable to map /dev/mem");
			exit(EXIT_FAILURE);
		}
		mapped = true;
	}
#endif
}

void MAP::closeMap(){
#ifdef WITH_HW
    // decrease counter
    count--;
    //printf("Map count = %i\n", count); 
	if (mapped && (count == 0)){
		munmap(map, fd);
		close(fd);
		mapped = false;
	}
#endif
}

MAP::~MAP(){
};

uint32_t* MAP::getMap(){
#ifdef WITH_HW
	if (mapped){
		return map;
	} else {
		return 0;
	}
#endif
}
