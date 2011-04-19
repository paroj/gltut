
#ifndef INTERPOLATORS_H
#define INTERPOLATORS_H

#include <math.h>
#include <vector>

namespace Framework
{
	template<typename ValueType>
	class LinearInterpolator
	{
	public:
		explicit LinearInterpolator(bool isLoop)
			: m_isLoop(isLoop)
			, m_numSegments(0)
		{}

		LinearInterpolator(bool isLoop, int iNumReserve)
			: m_isLoop(isLoop)
			, m_numSegments(0)
		{
			m_values.reserve(iNumReserve);
		}

		void AppendValue(const ValueType &data)
		{
			m_values.push_back(data);
			m_numSegments = m_isLoop ? m_values.size() : (m_values.size() - 1);
			if(m_values.size() < 2)
				m_numSegments = 0;
		}

		ValueType Interpolate(float fAlpha) const
		{
			if(m_numSegments == 0)
				return m_values[0];

			fAlpha *= m_numSegments;

			float intPart = 0.0f;
			float sectionAlpha = modf(fAlpha, &intPart);

			int iStartIx = (int)intPart;

			int iNextIx = iStartIx + 1;
			if(m_isLoop && (iNextIx == m_numSegments))
			{
				iNextIx = 0;
			}

			if((size_t)iNextIx > m_numSegments)
				return m_values.back();


			float invSecAlpha = 1.0f - sectionAlpha;

			return m_values[iStartIx] * invSecAlpha + m_values[iNextIx] * sectionAlpha;
		}

	private:
		std::vector<ValueType> m_values;
		size_t m_numSegments;
		bool m_isLoop;
	};

	template<typename ValueType, typename SplineBasis>
	class CubicInterpolator
	{
	public:
		CubicInterpolator(const SplineBasis &basis, bool isLoop)
			: m_numSegments(0)
			, m_basis(basis)
			, m_isLoop(isLoop)
		{}

		CubicInterpolator(const SplineBasis &basis, bool isLoop, int iNumReserve)
			: m_numSegments(0)
			, m_basis(basis)-
			, m_isLoop(isLoop)
		{
			m_values.reserve(iNumReserve);
		}

		void AppendValue(const ValueType &data)
		{
			m_values.push_back(data);

			size_t numValues = m_values.size();
			if(numValues < 4)
				m_numSegments = 0;
			else
				m_numSegments = SplineBasis::CountSegments(numValues, m_isLoop);
		}

		ValueType Interpolate(float fAlpha) const
		{
			if(m_numSegments == 0)
				return m_values[0];

			fAlpha *= m_numSegments;

			float intPart = 0.0f;
			float sectionAlpha = modf(fAlpha, &intPart);

			int iStartIx = (int)intPart;

			m_basis.Interpolate(m_values, iStartIx, sectionAlpha);
		}

	private:
		std::vector<ValueType> m_values;
		size_t m_numSegments;
		SplineBasis m_basis;
		bool m_isLoop;
	};
}



#endif //INTERPOLATORS_H
