#pragma once

#include "rkLogicalComparisonType.h"

namespace rk
{
  namespace logicalComparisonUtilities
  {
    bool evaluateFloatComparison(
      float leftValue,
      float rightValue,
      logicalComparisonType::Type comparisonType
    )
    {
      switch (comparisonType)
      {
        case logicalComparisonType::Type::Less:
          return leftValue < rightValue;
        case logicalComparisonType::Type::LessEqual:
          return leftValue <= rightValue;
        case logicalComparisonType::Type::Equal:
          return leftValue == rightValue;
        case logicalComparisonType::Type::NotEqual:
          return leftValue != rightValue;
        case logicalComparisonType::Type::GreaterEqual:
          return leftValue >= rightValue;
        case logicalComparisonType::Type::Greater:
          return leftValue > rightValue;
        default:
          throw InvalidArgumentException(
            "Invalid comparison type for float comparison."
          );
      }
    }
  }
}