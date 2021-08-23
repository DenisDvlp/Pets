#pragma once
#include <cstdint>
#include <unordered_map>

enum class DataType : unsigned int
{
	Int8,
	Int16,
	Int32,
	Int64,
	UInt8,
	UInt16,
	UInt32,
	UInt64,
	Float,
	Double,
	LongDouble,
	String,
	Object_1,
	Object_2,
	Object_3,
	Request,
};

struct Packet
{
	DataType type;
	union {
		std::uint64_t size;
		long double ld;
		DataType requestDataType;
	};

	bool isValid();
	bool isTrivial();
	bool isComplex();
	bool isRequest();
};

static std::unordered_map<DataType, const char*> dataTypeStr =
{
	{ DataType::Int8, "Int8" },
	{ DataType::Int16, "Int16" },
	{ DataType::Int32, "Int32" },
	{ DataType::Int64, "Int64" },
	{ DataType::UInt8, "UInt8" },
	{ DataType::UInt16, "UInt16" },
	{ DataType::UInt32, "UInt32" },
	{ DataType::UInt64, "UInt64" },
	{ DataType::Float, "Float" },
	{ DataType::Double, "Double" },
	{ DataType::LongDouble, "LongDouble" },
	{ DataType::String, "String" },
	{ DataType::Object_1, "Object_1" },
	{ DataType::Object_2, "Object_2" },
	{ DataType::Object_3, "Object_3" },
	{ DataType::Request, "Request" },
};

std::vector<char> serialize(DataType type, void* data);
