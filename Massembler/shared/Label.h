#pragma once

namespace Massembler {

	class Label
	{
	private:
		uint32_t m_labelId;

	public:
		Label(uint32_t labelId) : m_labelId(labelId)
		{
		}

		Label(const Label& c) : m_labelId(c.m_labelId)
		{
		}

		Label& operator=(const Label& c)
		{
			m_labelId = c.m_labelId;
			return *this;
		}

		uint32_t getLabelId() const
		{
			return m_labelId;
		}
	};

}