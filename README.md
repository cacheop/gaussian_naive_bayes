Implementing Naive Bayes

In this exercise you will implement a Gaussian Naive Bayes classifier to predict the behavior of vehicles on a highway. In the image below you can see the behaviors you'll be looking for on a 3 lane highway (with lanes of 4 meter width). The dots represent the d (y axis) and s (x axis) coordinates of vehicles as they either...

    change lanes left (shown in blue)
    keep lane (shown in black)
    or change lanes right (shown in red)

    Your job is to write a classifier that can predict which of these three maneuvers a vehicle is engaged in given a single coordinate (sampled from the trajectories shown below).

Each coordinate contains 4 features:

    sss
    ddd
    s˙\dot{s}s˙
    d˙\dot{d}d˙

You also know the lane width is 4 meters (this might be helpful in engineering additional features for your algorithm).
Instructions

    Implement the train(self, data, labels) method in the class GNB in classifier.cpp.

    Training a Gaussian Naive Bayes classifier consists of computing and storing the mean and standard deviation from the data for each label/feature pair. For example, given the label "change lanes left” and the feature s˙\dot{s}s˙, it would be necessary to compute and store the mean and standard deviation of s˙\dot{s}s˙ over all data points with the "change lanes left” label.

    Additionally, it will be convenient in this step to compute and store the prior probability p(C_k) for each label C_k. This can be done by keeping track of the number of times each label appears in the training data.

    Implement the predict(self, observation) method in classifier.cpp.

    Given a new data point, prediction requires two steps:
        Compute the conditional probabilities for each feature/label combination. For a feature xxx and label CCC with mean μ\muμ and standard deviation σ\sigmaσ (computed in training), the conditional probability can be computed using the formula here:

p(x=v∣C)=12πσ2exp−(v−μ)22σ2p(x = v | C) = \frac{1}{\sqrt{2\pi\sigma^2}} \exp^{-\frac{(v-\mu)^2}{2\sigma^2}}p(x=v∣C)=2πσ2
​1​exp−2σ2(v−μ)2​

Here vvv is the value of feature xxx in the new data point.

    Use the conditional probabilities in a Naive Bayes classifier. This can be done using the formula here:

    y=argmax_k∈(1,…,K)p(C_k)∏n_i=1p(x_i=v_i∣C_k) y = argmax\_{k\in (1,\ldots, K)} \,\,p(C\_k) \prod^n\_{i=1}p(x\_i = v\_i| C\_k) y=argmax_k∈(1,…,K)p(C_k)∏n​_i=1p(x_i=v_i∣C_k)

    In this formula, the argmax is taken over all possible labels CkC_kCk​ and the product is taken over all features xix_ixi​ with values viv_ivi​.

    When you want to test your classifier, run Test Run and check out the results.

NOTE: You are welcome to use some existing implementation of a Gaussian Naive Bayes classifier. But to get the best results you will still need to put some thought into what features you provide the algorithm when classifying. Though you will only be given the 4 coordinates listed above, you may find that by "engineering" features you may get better performance. For example: the raw value of the ddd coordinate may not be that useful. But d % lane_width might be helpful since it gives the relative position of a vehicle in it's lane regardless of which lane the vehicle is in.



