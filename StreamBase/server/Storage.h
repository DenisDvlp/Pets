#pragma once
#include "Packet.h"
#include "CustomTypes.h"
#include <vector>
#include <string>

class Storage
{
public:
	std::vector<char> construct(DataType);
	void store(const DataType type, void* data, size_t size);
private:
	std::vector<std::int8_t>   m_int8s;
	std::vector<std::int16_t>  m_int16s;
	std::vector<std::int32_t>  m_int32s;
	std::vector<std::int64_t>  m_int64s;
	std::vector<std::uint8_t>  m_uint8s;
	std::vector<std::uint16_t> m_uint16s;
	std::vector<std::uint32_t> m_uint32s;
	std::vector<std::uint64_t> m_uint64s;
	std::vector<float>		   m_floats;
	std::vector<double>		   m_doubles;
	std::vector<long double>   m_ldoubles;
	std::vector<std::string>   m_strings;
	std::vector<Object_1>	   m_object_1s;
	std::vector<Object_2>	   m_object_2s;
	std::vector<Object_3>	   m_object_3s;
};

