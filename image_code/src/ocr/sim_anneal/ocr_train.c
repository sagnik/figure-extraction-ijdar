/*

Training for OCR
WJB 02/07-06/07

based on ->

Fast Artificial Neural Network Library (fann)
Copyright (C) 2003 Steffen Nissen (lukesky@diku.dk)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <stdio.h>
#include <math.h>
#include "fann.h"

int FANN_API test_callback(struct fann *ann, struct fann_train_data *train,
	unsigned int max_epochs, unsigned int epochs_between_reports, 
	float desired_error, unsigned int epochs)
{
	printf("Epochs     %8d. MSE: %.5f. Desired-MSE: %.5f\n", epochs, fann_get_MSE(ann), desired_error);
	return 0;
}

int main()
{
	fann_type *calc_out;
	const unsigned int num_input = 3;
	const unsigned int num_output = 8;
	const unsigned int num_layers = 3;
	const unsigned int num_neurons_hidden = 13;
	const float desired_error = (const float) 0.01;
	const unsigned int max_epochs = 1000000;
	const unsigned int epochs_between_reports = 100;
	struct fann *ann;
	struct fann_train_data *data;

	unsigned int i = 0;
	unsigned int decimal_point;

	printf("Creating network.\n");
	ann = fann_create_standard(num_layers, num_input, num_neurons_hidden, num_output);

	data = fann_read_train_from_file("train.txt");

	fann_set_activation_steepness_hidden(ann, 0.01);
	fann_set_activation_steepness_output(ann, 0.01);

	fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
	fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);

	fann_set_train_stop_function(ann, FANN_STOPFUNC_BIT);
	fann_set_bit_fail_limit(ann, 0.01f);

	fann_init_weights(ann, data);
	
	printf("Training network.\n");
	fann_train_on_data(ann, data, max_epochs, epochs_between_reports, desired_error);

	printf("Testing network. %f\n", fann_test_data(ann, data));

	for(i = 0; i < fann_length_train_data(data); i++)
	{
		calc_out = fann_run(ann, data->input[i]);
		//printf("test (%f,%f,%f) -> %f, should be (%f,%f,%f,%f,%f,%f,%f,%f,%f,%f) difference=%f\n",	   data->input[i][0], data->input[i][1], data->input[i][2], calc_out[i], data->output[i][0], data->output[i][1], data->output[i][2], data->output[i][3], data->output[i][4], data->output[i][5], data->output[i][6], data->output[i][7], data->output[i][8], data->output[i][9], 	   fann_abs(calc_out[i] - data->output[i]));
	}

	printf("Saving network.\n");

	fann_save(ann, "ocr_dat.net");

	decimal_point = fann_save_to_fixed(ann, "ocr_dat2.net");
	fann_save_train_to_fixed(data, "ocr_dat2.data", decimal_point);

	printf("Cleaning up.\n");
	fann_destroy_train(data);
	fann_destroy(ann);

	return 0;
}
