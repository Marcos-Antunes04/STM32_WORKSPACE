#ifndef SRC_COMPONENTS_START_HPP_
#define SRC_COMPONENTS_START_HPP_
#include <main.hpp>

enum type_of_filter{
	fir,
	iir
};

class filter{
private:
	uint8_t filter_length;
	type_of_filter type;
	float *buf;
	uint8_t buf_index = 0;
	float out;
public:
	filter(type_of_filter type, int num);
	float update(float inp, float* impulse_response);
};

#endif /* INC_FILTER_HPP_ */
