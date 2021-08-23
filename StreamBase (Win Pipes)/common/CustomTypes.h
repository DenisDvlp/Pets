#pragma once
#include <vector>
#include <string>

class ISerialize
{
public:
	virtual ~ISerialize() {};
	virtual size_t serializedSize() = 0;
	virtual std::vector<char> serialize() = 0;
	virtual void deserialize(void* data, size_t size) = 0;
	virtual void print() = 0;
};

class Object_1 : public ISerialize
{
public:
	int x[1];

	size_t serializedSize() override;
	std::vector<char> serialize() override;
	void deserialize(void* data, size_t size) override;
	void print() override;
};

class Object_2 : public ISerialize
{
public:
	int x[2];

	size_t serializedSize() override;
	std::vector<char> serialize() override;
	void deserialize(void* data, size_t size) override;
	void print() override;
};

class Object_3 : public ISerialize
{
public:
	int x[3];
	std::string s;

	size_t serializedSize() override;
	std::vector<char> serialize() override;
	void deserialize(void* data, size_t size) override;
	void print() override;
};