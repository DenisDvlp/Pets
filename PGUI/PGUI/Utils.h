#pragma once

#undef max
#undef min

template<typename T>
T max(T value1, T value2);

template<typename T>
T min(T value1, T value2);

template<typename T>
T range(T min, T value, T max);

int random(int min, int max);
float random(float min, float max, int precision);

template<typename T>
void swap(T &value1, T &value2);