#include "Storage.h"
#include <iostream>


std::vector<char> Storage::construct(DataType type)
{
    std::vector<char> data;

    std::cout << "Constructed " << dataTypeStr[type] << std::endl;

    switch (type)
    {
    case DataType::String:
        m_strings.emplace_back("This is a string.");
        std::cout << "String:" << m_strings.back() << std::endl;
        data.insert(data.end(), m_strings.back().begin(), m_strings.back().end());
        data.push_back(0);
        break;
    case DataType::Object_1:
        m_object_1s.emplace_back();
        m_object_1s.back().x[0] = 1;
        m_object_1s.back().print();
        data = m_object_1s.back().serialize();
        break;
    case DataType::Object_2:
        m_object_2s.emplace_back();
        m_object_2s.back().x[0] = 1;
        m_object_2s.back().x[1] = 2;
        m_object_2s.back().print();
        data = m_object_2s.back().serialize();
        break;
    case DataType::Object_3:
        m_object_3s.emplace_back();
        m_object_3s.back().x[0] = 1;
        m_object_3s.back().x[1] = 2;
        m_object_3s.back().x[2] = 3;
        m_object_3s.back().s = "a string inside Object_3 from the server";
        m_object_3s.back().print();
        data = m_object_3s.back().serialize();
        break;
    }

	return data;
}

void Storage::store(const DataType type, void* data, size_t size)
{
    std::cout << "Stored " << dataTypeStr[type] << ":";

    switch (type)
    {
    case DataType::Int8:
        m_int8s.push_back(*reinterpret_cast<std::int8_t*>(data));
        std::cout << m_int8s.back() << std::endl;
        break;
    case DataType::Int16:
        m_int16s.push_back(*reinterpret_cast<std::int16_t*>(data));
        std::cout << m_int16s.back() << std::endl;
        break;
    case DataType::Int32:
        m_int32s.push_back(*reinterpret_cast<std::int32_t*>(data));
        std::cout << m_int32s.back() << std::endl;
        break;
    case DataType::Int64:
        m_int64s.push_back(*reinterpret_cast<std::int64_t*>(data));
        std::cout << m_int64s.back() << std::endl;
        break;
    case DataType::UInt8:
        m_uint8s.push_back(*reinterpret_cast<std::uint8_t*>(data));
        std::cout << m_uint8s.back() << std::endl;
        break;
    case DataType::UInt16:
        m_uint16s.push_back(*reinterpret_cast<std::uint16_t*>(data));
        std::cout << m_uint16s.back() << std::endl;
        break;
    case DataType::UInt32:
        m_uint32s.push_back(*reinterpret_cast<std::uint32_t*>(data));
        std::cout << m_uint32s.back() << std::endl;
        break;
    case DataType::UInt64:
        m_uint64s.push_back(*reinterpret_cast<std::uint64_t*>(data));
        std::cout << m_uint64s.back() << std::endl;
        break;
    case DataType::Float:
        m_floats.push_back(*reinterpret_cast<float*>(data));
        std::cout << m_floats.back() << std::endl;
        break;
    case DataType::Double:
        m_doubles.push_back(*reinterpret_cast<double*>(data));
        std::cout << m_doubles.back() << std::endl;
        break;
    case DataType::LongDouble:
        m_ldoubles.push_back(*reinterpret_cast<long double*>(data));
        std::cout << m_ldoubles.back() << std::endl;
        break;
    case DataType::String:
        m_strings.emplace_back(reinterpret_cast<char*>(data));
        std::cout << m_strings.back() << std::endl;
        break;
    case DataType::Object_1:
        m_object_1s.emplace_back();
        m_object_1s.back().deserialize(data, size);
        m_object_1s.back().print();
        break;
    case DataType::Object_2:
        m_object_2s.emplace_back();
        m_object_2s.back().deserialize(data, size);
        m_object_2s.back().print();
        break;
    case DataType::Object_3:
        m_object_3s.emplace_back();
        m_object_3s.back().deserialize(data, size);
        m_object_3s.back().print();
        break;
    }
}
