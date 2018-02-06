#ifndef CLASSIFIER_H
#define CLASSIFIER_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
#include <vector>

using namespace std;

class GNB {
public:

	vector<string> possible_labels = {"left","keep","right"};

    vector<double>  left_means;
    vector<double>  left_stddev;
    
    vector<double>  keep_means;
    vector<double>  keep_stddev;
    
    vector<double>  right_means;
    vector<double>  right_stddev;
    
    vector<vector<double>>  feature_data_left;
    vector<vector<double>>  feature_data_keep;
    vector<vector<double>>  feature_data_right;

	/**
  	* Constructor
  	*/
 	GNB();

	/**
 	* Destructor
 	*/
 	virtual ~GNB();

 	void train(vector<vector<double> > data, vector<string>  labels);

  	string predict(vector<double>);

};

#endif



