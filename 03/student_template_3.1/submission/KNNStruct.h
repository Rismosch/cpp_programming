// Simon Sutoris 7542170
// Eric Berger 7064584
#include <iostream>
#include <vector>
#include <cmath>


struct DYNPoint {
	std::vector<float> data;

	// We use a static function to return a DYNPoint object (this pattern is sometimes called a "factory method")
	// We can mark functions as nodiscard to indicate that we must use the return value in some way (e.g, it doesn't get discarded as ).
	[[nodiscard]] static DYNPoint createRandomPoint(unsigned int size, int minimum=-5000, int maximum=5000) {
		DYNPoint p;
		if (size > 0 && minimum <= maximum) {			
			// STUDENT TODO: add your code	
			p.data.reserve(size);
			int range = maximum - minimum;
			for (unsigned int i=0; i<size; i++)
			{
				p.data.push_back((std::rand() % (range + 1)) + minimum);
			}
		}
		return p;
	}
};

struct KNN {
	KNN(float(*_function_ptr_Distance)(const DYNPoint &, const DYNPoint &))
		: function_ptr_Distance(_function_ptr_Distance)
	{
	}

	std::vector<std::pair<DYNPoint, unsigned int>> trainingData{}; // default initialize on creation

	float(*function_ptr_Distance)(const DYNPoint &, const DYNPoint &) = 0;

	// just sets the training data (no actual training required)
	void TrainKNN(const std::vector<std::pair<DYNPoint, unsigned int>> &dataset) {
		trainingData.clear();
		trainingData = dataset;
	}

	int classify(const unsigned int k, const DYNPoint &A) const {

		int class_label = -1;

		if (k && function_ptr_Distance && trainingData.size()) {
			// STUDENT TODO: your code
			size_t dataset_size = trainingData.size();
			std::vector<unsigned int> labels(k);
			std::vector<float> distances(dataset_size);

			for (size_t i=0; i<dataset_size; i++)
			{
				distances.at(i) = function_ptr_Distance(trainingData.at(i).first, A);
			}

			for (unsigned int K=0; K<k; K++)
			{
				float min_dist = std::numeric_limits<float>::max();
				size_t min_dist_idx = 0;
				for (size_t i=0; i<dataset_size; i++)
				{
					if (distances.at(i) < min_dist)
					{
						min_dist = distances.at(i);
						min_dist_idx = i;
					}
				}
				labels.at(K) = trainingData.at(min_dist_idx).second;
				distances.at(min_dist_idx) = std::numeric_limits<float>::max();
			}

			unsigned int best_count = 0;
			for (size_t i=0; i<labels.size(); i++)
			{
				unsigned int count = 0;
				for (size_t j=0; j<labels.size(); j++)
				{
					if (labels.at(j) == labels.at(i))
					{
						count += 1;
					}
				}
				if (count > best_count)
				{
					best_count = count;
					class_label = labels.at(i);
				}
			}
		}
		return class_label;
	}
};

float DistanceManhattan(const DYNPoint &A, const DYNPoint &B) {
	// STUDENT TODO: your code
	size_t size = A.data.size();
	float sum = 0.0f;
	for (size_t i=0; i<size; i++)
	{
		sum += std::abs(A.data.at(i) - B.data.at(i));
	}
	return sum / size;
}

float DistanceEuclid(const DYNPoint &A, const DYNPoint &B) {
	// STUDENT TODO: your code
	size_t size = A.data.size();
	float sum = 0.0f;
	for (size_t i=0; i<size; i++)
	{
		float difference = A.data.at(i) - B.data.at(i);
		sum += difference * difference;
	}
	return std::sqrt(sum / size);

}

void createDataset(std::vector<std::pair<DYNPoint, unsigned int>> &dataset, const unsigned int amount, const unsigned int class_label,
				const unsigned int point_size, const int minimum, const int maximum) {
	
	if (amount > 0 && point_size>0 && minimum <= maximum) {
	// STUDENT TODO: your code
	dataset.reserve(dataset.size() + amount);
	for (unsigned int i=0; i<amount; i++)
	{
		DYNPoint point = DYNPoint::createRandomPoint(point_size, minimum, maximum);
        dataset.push_back({point, class_label});
	}

	}
}

void evaluateKNN(const std::vector<std::pair<DYNPoint, unsigned int>> &dataset, const KNN &Classifier, const unsigned int k) {
	if (!dataset.empty()) {
		float acc = 0;
		for (size_t i = 0; i < dataset.size(); i++) {
			if (static_cast<unsigned int>(Classifier.classify(k, dataset[i].first)) == dataset[i].second)
				acc++;
		}
		std::cout << "Accuracy: " << acc / float(dataset.size()) << std::endl;
	}
}









