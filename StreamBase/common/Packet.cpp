#include "Packet.h"
#include "CustomTypes.h"
#include <vector>

bool Packet::isValid()
{
    return type >= DataType::Int8 && type < DataType::Request ||
        type == DataType::Request && requestDataType >= DataType::String &&
        requestDataType < DataType::Request;
}

bool Packet::isTrivial()
{
	return type >= DataType::Int8 && type <= DataType::LongDouble;
}

bool Packet::isComplex()
{
	return type >= DataType::String && type <= DataType::Object_3;
}

bool Packet::isRequest()
{
	return type == DataType::Request;
}

std::vector<char> serialize(DataType type, void* object)
{
    std::vector<char> data;

    switch (type)
    {
    case DataType::String:
        {
            const auto& str = *reinterpret_cast<std::string*>(object);
            if (!str.empty())
            {
                data.assign(str.begin(), str.end());
                data.push_back(0);
            }
        }
        break;
    case DataType::Object_1:
        data = reinterpret_cast<Object_2*>(object)->serialize();
        break;
    case DataType::Object_2:
        data = reinterpret_cast<Object_2*>(object)->serialize();
        break;
    case DataType::Object_3:
        data = reinterpret_cast<Object_3*>(object)->serialize();
        break;
    }

    return data;
}
