
#ifndef INTERPOLATORS_H
#define INTERPOLATORS_H

#include <math.h>
#include <vector>
#include <algorithm>
#include <iterator>

// forward declare some functions needed by instantiations
// FIXME this is certainly the wrong place for them
typedef std::pair<float, float> MaxIntensityData;
typedef std::vector<MaxIntensityData> MaxIntensityVector;
typedef std::pair<glm::vec4, float> LightVectorData;
typedef std::vector<LightVectorData> LightVector;
float distance(const glm::vec3 &lhs, const glm::vec3 &rhs);
glm::vec4 GetValue(const LightVectorData &data);
float GetTime(const LightVectorData &data);
float GetValue(const MaxIntensityData &data);
float GetTime(const MaxIntensityData &data);

namespace Framework
{
	template<typename ValueType>
	class WeightedLinearInterpolator
	{
	public:
		typedef ValueType value_type;

		size_t NumSegments() const {return m_values.empty() ? 0 : m_values.size() - 1;}

		ValueType Interpolate(float fAlpha) const
		{
			if(m_values.empty())
				return ValueType();
			if(m_values.size() == 1)
				return m_values[0].data;

			//Find which segment we are within.
			size_t segment = 1;
			for(; segment < m_values.size(); ++segment)
			{
				if(fAlpha < m_values[segment].weight)
					break;
			}

			if(segment == m_values.size())
				return m_values.back().data;

			float sectionAlpha = fAlpha - m_values[segment - 1].weight;
			sectionAlpha /= m_values[segment].weight - m_values[segment - 1].weight;

			float invSecAlpha = 1.0f - sectionAlpha;

			return m_values[segment - 1].data * invSecAlpha + m_values[segment].data * sectionAlpha;
		}

	protected:
		WeightedLinearInterpolator() {}

		struct Data
		{
			ValueType data;
			float weight;
		};

		std::vector<Data> m_values;
	};

	template<typename ValueType>
	class TimedLinearInterpolator : public WeightedLinearInterpolator<ValueType>
	{
	public:

		template<typename BidirectionalRange>
		void SetValues(const BidirectionalRange &data, bool isLooping = true)
		{
			this->m_values.clear();
			typename BidirectionalRange::const_iterator curr = data.begin();
			typename BidirectionalRange::const_iterator final = data.end();
			for(; curr != final; ++curr)
			{
				typename WeightedLinearInterpolator<ValueType>::Data currData;
				currData.data = GetValue(*curr);
				currData.weight = GetTime(*curr);

				assert(0.0f <= currData.weight && currData.weight <= 1.0f);
				this->m_values.push_back(currData);
			}

			if(isLooping && !this->m_values.empty())
				this->m_values.push_back(this->m_values[0]);

			//Ensure first is weight 0, and last is weight 1.
			if(!this->m_values.empty())
			{
				this->m_values.front().weight = 0.0f;
				this->m_values.back().weight = 1.0f;
			}
		}
	protected:
	};


	template<typename ValueType>
	class LinearInterpolator : public WeightedLinearInterpolator<ValueType>
	{
	public:
		typedef ValueType value_type;

		template<typename BidirectionalRange>
		void SetValues(const BidirectionalRange &data, bool isLooping = true)
		{
			this->m_values.clear();
			int iNumValues = 0;
			typename BidirectionalRange::const_iterator curr = data.begin();
			typename BidirectionalRange::const_iterator final = data.end();
			for(; curr != final; ++curr)
			{
				typename WeightedLinearInterpolator<ValueType>::Data currData;
				currData.data = *curr;
				currData.weight = 0.0f;
				this->m_values.push_back(currData);

				iNumValues++;
			}

			if(isLooping && !this->m_values.empty())
			{
				this->m_values.push_back(this->m_values.back());
				++iNumValues;
			}

			//Compute weights.
			for(size_t valIx = 0; valIx < this->m_values.size(); ++valIx)
			{
				this->m_values[valIx].weight = valIx / (float)(iNumValues - 1);
			}
		}
	private:
	};

	/**
	\brief Interpolates with a constant velocity between positions.

	This interpolator maps a range of [0, 1) onto a set of values. However, it takes the distance
	between these values. There must be a free function called "distance" which takes two ValueType's and
	returns a float distance between them.

	The idea is that, if you add 0.1 to your alpha value, you will always get a movement of the same distance.
	Not necessarily between the initial and final points, but the object will have moved at the same
	speed along the path.
	**/
	template<typename ValueType>
	class ConstVelLinearInterpolator : public WeightedLinearInterpolator<ValueType>
	{
	public:
		typedef ValueType value_type;

		explicit ConstVelLinearInterpolator()
			: m_totalDist(0.0f)
		{}

		template<typename BidirectionalRange>
		void SetValues(const BidirectionalRange &data, bool isLoop = true)
		{
			this->m_values.clear();

			typename BidirectionalRange::const_iterator curr = data.begin();
			typename BidirectionalRange::const_iterator last = data.end();
			for(; curr != last; ++curr)
			{
				typename WeightedLinearInterpolator<ValueType>::Data currData;
				currData.data = *curr;
				currData.weight = 0.0f;
				this->m_values.push_back(currData);
			}

			if(isLoop)
			{
				typename WeightedLinearInterpolator<ValueType>::Data currData;
				currData.data = *data.begin();
				currData.weight = 0.0f;
				this->m_values.push_back(currData);
			}

			//Compute the distances of each segment.
			m_totalDist = 0.0f;
			for(size_t iLoop = 1; iLoop < this->m_values.size(); ++iLoop)
			{
				m_totalDist += distance(this->m_values[iLoop - 1].data,
				    this->m_values[iLoop].data);
				this->m_values[iLoop].weight = m_totalDist;
			}

			//Compute the alpha value that represents when to use this segment.
			for(size_t iLoop = 1; iLoop < this->m_values.size(); ++iLoop)
			{
				this->m_values[iLoop].weight /= m_totalDist;
			}
		}

		float Distance() const {return m_totalDist;}

	private:
		float m_totalDist;
	};
}



#endif //INTERPOLATORS_H
