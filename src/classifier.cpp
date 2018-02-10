#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
#include <vector>
#include "classifier.h"

const double LANE_WIDTH = 4.0;
const int NUM_FEATURES = 4;

void add_feature(vector<vector<double>> &feature_data, const std::vector<double> data_input)
{
    vector <double> temp_data = data_input;
    temp_data[1] = data_input[1] / LANE_WIDTH;
    feature_data.push_back(temp_data);
}

vector<double> calculate_mean(vector<vector<double>> feature_data){
    
    vector<double> mean_values(NUM_FEATURES);
    
    std::size_t num_elements = feature_data.size();
    for (std::size_t i=0; i < num_elements; i++){
        vector <double> temp_data =  feature_data[i];
        for (int j = 0; j < NUM_FEATURES; j++){
            mean_values[j] += temp_data[j];
        }
    }
    
    for (int j = 0; j < NUM_FEATURES; j++){
        mean_values[j] /= num_elements;
    }
    
    return mean_values;
}

vector<double> calculate_stddev(vector<vector<double>> feature_data, vector<double> mean_values) {
    
    vector<double> sigma_values(NUM_FEATURES);
    
    std::size_t num_elements = feature_data.size();
    for (std::size_t i=0; i < num_elements; i++){
        vector <double> temp_data =  feature_data[i];
        for (int j = 0; j < NUM_FEATURES; j++){
            sigma_values[j] += pow((temp_data[j] - mean_values[j]),2) / num_elements;
        }
    }
    
    for (int j = 0; j < NUM_FEATURES; j++){
        sigma_values[j] = sqrt(sigma_values[j]);
    }
    
    return sigma_values;
}


double calculate_prob(vector<double> feature_data, vector<double> means, vector<double> stddev) {
    
    double temp_var= 1.0;
    double pdf_gaussian = 1.0;
    // Since this is Naive Bayes, we consider the
    // prob(x1,x2,x3,x4 | class) = p(x1|class) * p(x2|class) * p(x3|lass) * p(x4|class)
    
    for (int i = 0; i < NUM_FEATURES; i++) {
        
        double x = feature_data[i];
        double mean = means[i];
        double sigma = stddev[i];
        
        temp_var = (1 / (sigma * sqrt(2 * M_PI))) * exp(-0.5 * pow(((x - mean) / sigma), 2.0 ));
        pdf_gaussian *= temp_var;
    }
    
    return pdf_gaussian;

}

/**
 * Initializes GNB
 */
GNB::GNB() {

}

GNB::~GNB() {}

void GNB::train(vector<vector<double>> data, vector<string> labels)
{

	/*
		Trains the classifier with N data points and labels.

		INPUTS
		data - array of N observations
		  - Each observation is a tuple with 4 values: s, d, 
		    s_dot and d_dot.
		  - Example : [
			  	[3.5, 0.1, 5.9, -0.02],
			  	[8.0, -0.3, 3.0, 2.2],
			  	...
		  	]

		labels - array of N labels
		  - Each label is one of "left", "keep", or "right".
	*/
    
    vector<vector<double>>  feature_data_left;
    vector<vector<double>>  feature_data_keep;
    vector<vector<double>>  feature_data_right;
    
    for (int i=0; i < labels.size(); i++) {
        cout << labels[i] << endl;
        vector<double> data_input = data[i];
        
        if (labels[i] == "left") add_feature(feature_data_left, data_input);
        else
            if (labels[i] == "keep") add_feature(feature_data_keep, data_input);
            else
                if (labels[i] == "right") add_feature(feature_data_right, data_input);
    }
    
    left_means = calculate_mean(feature_data_left);
    left_stddev = calculate_stddev(feature_data_left, left_means);

    keep_means = calculate_mean(feature_data_keep);
    keep_stddev = calculate_stddev(feature_data_keep, keep_means);

    right_means = calculate_mean(feature_data_right);
    right_stddev = calculate_stddev(feature_data_right, right_means);
    
    std::cout<< "\nTraining Complete...\n"<< std::endl;
}

string GNB::predict(vector<double> sample)
{
	/*
		Once trained, this method is called and expected to return 
		a predicted behavior for the given observation.

		INPUTS

		observation - a 4 tuple with s, d, s_dot, d_dot.
		  - Example: [3.5, 0.1, 8.5, -0.2]

		OUTPUT

		A label representing the best guess of the classifier. Can
		be one of "left", "keep" or "right".
		"""
		# TODO - complete this
	*/
    
    
    vector<double> prob_classes;
    
    prob_classes.push_back(calculate_prob(sample, left_means, left_stddev));
    prob_classes.push_back(calculate_prob(sample, keep_means, keep_stddev));
    prob_classes.push_back(calculate_prob(sample, right_means, right_stddev));
    
    int idx = 0;
    double best_p = 0;
    
    for (int p = 0; p < prob_classes.size(); p++) {
        if (prob_classes[p] > best_p) {
            best_p = prob_classes[p];
            idx = p;
        }
    }
	return possible_labels[idx];

}
