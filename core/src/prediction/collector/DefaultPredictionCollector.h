/*-------------------------------------------------------------------------------
  This file is part of generalized random forest (grf).

  grf is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  grf is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with grf. If not, see <http://www.gnu.org/licenses/>.
 #-------------------------------------------------------------------------------*/

#ifndef GRF_FULLPREDICTOR_H
#define GRF_FULLPREDICTOR_H


#include "forest/Forest.h"
#include "prediction/collector/PredictionCollector.h"
#include "prediction/collector/SampleWeightComputer.h"
#include "prediction/DefaultPredictionStrategy.h"

class DefaultPredictionCollector: public PredictionCollector {
public:
  DefaultPredictionCollector(std::shared_ptr<DefaultPredictionStrategy> strategy,
                              uint ci_group_size);

  std::vector<Prediction> collect_predictions(const Forest& forest,
                                              Data* prediction_data,
                                              const std::vector<std::vector<size_t>>& leaf_nodes_by_tree,
                                              const std::vector<std::vector<bool>>& valid_trees_by_sample,
                                              bool estimate_error);

private:
    void validate_prediction(size_t sample, Prediction prediction);

    void add_prediction_values(size_t node,
                               const PredictionValues& prediction_values,
                               std::vector<double>& combined_average);

  std::shared_ptr<DefaultPredictionStrategy> strategy;
  SampleWeightComputer weight_computer;
  uint ci_group_size;
};


#endif //GRF_FULLPREDICTOR_H
