
#ifndef INTERPOLATORS_H
#define INTERPOLATORS_H

#include <math.h>
#include <vector>
#include <algorithm>
#include <iterator>

namespace Framework
{
	template<typename ValueType>
	class LinearInterpolator
	{
	public:
		typedef ValueType value_type;

		explicit LinearInterpolator(bool isLoop)
			: m_isLoop(isLoop)
		{}

		template<typename BidirectionalRange>
		void SetValues(const BidirectionalRange &data)
		{
			m_values.clear();
			std::copy(data.begin(), data.end(), std::back_inserter(m_values));
			if(m_isLoop)
				m_values.push_back(*data.begin());
		}

		size_t NumSegments() const {return m_values.empty() ? 0 : m_values.size() - 1;}

		ValueType Interpolate(float fAlpha) const
		{
			if(m_values.empty())
				return ValueType();
			if(m_values.size() == 1)
				return m_values[0];

			fAlpha *= m_values.size() - 1;

			float intPart = 0.0f;
			float sectionAlpha = modf(fAlpha, &intPart);

			size_t iStartIx = (size_t)intPart;

			size_t iNextIx = iStartIx + 1;

			if(iNextIx > NumSegments())
				return m_values.back();

			float invSecAlpha = 1.0f - sectionAlpha;

			return m_values[iStartIx] * invSecAlpha + m_values[iNextIx] * sectionAlpha;
		}

	private:
		std::vector<ValueType> m_values;
		bool m_isLoop;
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
	class ConstVelLinearInterpolator
	{
	public:
		typedef ValueType value_type;

		explicit ConstVelLinearInterpolator(bool isLoop)
			: m_isLoop(isLoop)
			, m_totalDist(0.0f)
		{}

		template<typename BidirectionalRange>
		void SetValues(const BidirectionalRange &data)
		{
			m_values.clear();

			typename BidirectionalRange::const_iterator curr = data.begin();
			typename BidirectionalRange::const_iterator last = data.end();
			for(; curr != last; ++curr)
			{
				Data currData;
				currData.data = *curr;
				currData.weight = 0.0f;
				m_values.push_back(currData);
			}

			if(m_isLoop)
			{
				Data currData;
				currData.data = *data.begin();
				currData.weight = 0.0f;
				m_values.push_back(currData);
			}

			//Compute the distances of each segment.
			m_totalDist = 0.0f;
			for(size_t iLoop = 1; iLoop < m_values.size(); ++iLoop)
			{
				m_totalDist += distance(m_values[iLoop - 1].data, m_values[iLoop].data);
				m_values[iLoop].weight = m_totalDist;
			}

			//Compute the alpha value that represents when to use this segment.
			for(size_t iLoop = 1; iLoop < m_values.size(); ++iLoop)
			{
				m_values[iLoop].weight /= m_totalDist;
			}
		}

		float Distance() const {return m_totalDist;}

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

	private:
		struct Data
		{
			ValueType data;
			float weight;
		};

		std::vector<Data> m_values;
		bool m_isLoop;
		float m_totalDist;
	};
}



#endif //INTERPOLATORS_H
