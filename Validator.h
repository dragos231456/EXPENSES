#pragma once

template<typename ClassType>
class Validator
{
public:
	bool isValid(ClassType element);
};

template<typename ClassType>
inline bool Validator<ClassType>::isValid(ClassType element)
{
	return element.isValid();
}
