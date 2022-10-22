#include<string>
#include<iostream>
#include<vector>

#include"Peripheral.hpp"

const auto Peripheral::listBegin() const
{
	return _portlist.begin();
}

const auto Peripheral::listEnd() const
{
	return _portlist.end();
}
