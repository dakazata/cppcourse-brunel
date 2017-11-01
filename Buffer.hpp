/*
 * Class Buffer 
 */

#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include <string>
#include "Constants.hpp"

/*
 * 
 */ 

class Buffer
{
	private:
		std::vector<double> buffer_; //!< stores doubles 
		
	public:
		//Constructor
		Buffer();
		
		//Destructor
		~Buffer() = default;
		
		void resetValue(long time);
		
		void addJ(unsigned long, std::string type);			//add a transmission spike
		
		unsigned int getJ(long);
		
		unsigned int index(long time);
	
	
};

#endif

