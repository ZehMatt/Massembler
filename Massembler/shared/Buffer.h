#pragma once

#include <vector>
#include <algorithm>

namespace Massembler {

class Buffer 
{
private:
    uint8_t *m_data = nullptr;
    uint32_t m_capacity = 0;
    uint32_t m_size = 0;
    uint32_t m_offset = 0;

public:
    constexpr Buffer(void *data, uint32_t capacity) :
        m_data(static_cast<uint8_t*>(data)),
        m_capacity(capacity),
        m_size(0),
        m_offset(0)
    {
    }

	template<typename T>
    uint32_t write(const T& val)
	{
        *reinterpret_cast<T*>(const_cast<uint8_t*>(m_data + m_offset)) = val;
        m_offset += sizeof(T);
        m_size = std::max<uint32_t>(m_size, m_offset);
        return sizeof(T);
	}

    uint32_t capacity() const
	{
		return m_capacity;
	}

    uint32_t size() const
    {
        return m_size;
    }

	uint32_t pos() const
	{
		return m_offset;
	}

	int seek(uint32_t offset, int type)
	{
		size_t cur = m_offset;

		if (type == SEEK_SET)
			m_offset = offset;
		else if (type == SEEK_CUR)
			m_offset += offset;
		else if (type == SEEK_END)
			m_offset = m_capacity - offset;

		return 0;
	}

	const void *data() const
	{
		return &m_data[0];
	}

    void clear()
    {
        m_size = 0;
        m_offset = 0;
    }
};

};
