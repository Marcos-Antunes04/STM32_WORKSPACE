#include "filter.hpp"

filter::filter(type_of_filter type, int num){
	this->buf = new float[num];
	for (uint8_t n = 0; n < this->filter_length; n++){
		this->buf[n] = 0.0f;
	}
	this->type = type;
	this->filter_length = num;
}

float filter::update(float inp, float* impulse_response){
	this->out = 0.0f;

	// THIS SHOULD BE EXECUTED IF THE TYPE OF THE FILTER IS A FIR
	if(this->type == fir){
		this->buf[this->buf_index] = inp;
		this->buf_index++;
		if(this->buf_index == this->filter_length){
			this->buf_index = 0;
		}

		uint8_t sum_index = this->buf_index;

		for (uint8_t n = 0; n < this->filter_length; n++){
			if(sum_index > 0){
				sum_index--;
			}else{
				sum_index = this->filter_length - 1;
			}
			this->out += impulse_response[n] * this->buf[sum_index];
		}
	}

	// THIS SPACE SHOULD BE USED FOR IMPLEMENTING OTHER TYPES OF DIGITAL FILTERS

	// FINALLY THE VALUE RETURNED BY THE FILTER
	return out;

}
