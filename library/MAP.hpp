/*
 * MAP.hpp
 *
 *  Created on: Apr 15, 2015
 *      Author: constantin
 */

#ifndef INCL_DRIVER_MAP_HPP_
#define INCL_DRIVER_MAP_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "Definitions.hpp"

//! @brief Defines the memory map to the /dev/map
//! Handles all accesses to the memory map.
class MAP
{
public :
	//! @brief constructor
	//! opens /dev/map
	MAP();

	//! @brief destructor
	//! closes /dev/map
	~MAP();

	//! @brief opens map
	void openMap();

	//! @brief closes map
	void closeMap();

	//! @brief returns map
	//! if not mapped it returns 0
	uint32_t* getMap();

private :
	//! indicates whether /dev/map has been accessed successfully
	bool mapped;
	//! pointer to map
	uint32_t* map;
	//! file descriptor
	int fd;
    //! reference counter for safe construction and deconstruction
    int count;
};




#endif /* INCL_DRIVER_MAP_HPP_ */
