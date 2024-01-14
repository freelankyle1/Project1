#include "pch.h"
#include "Headers/d3dexception.h"

parentException::parentException(int line, const char* file) noexcept
	: line(line), file(file)
{}

const char* parentException::what() const noexcept
{
	std::ostringstream oss;
	oss << getType() << std::endl << getOriginSTring();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* parentException::getType() const noexcept
{
	return "My Exception";
}

int parentException::getLine() const noexcept
{
	return line;
}

const std::string& parentException::getFile() const noexcept
{
	return file;
}

std::string parentException::getOriginSTring() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}