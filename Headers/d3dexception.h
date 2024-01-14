#pragma once
#include "../pch.h"
#include <exception>

class parentException : public std::exception
{
public:
	parentException(int line, const char* file) noexcept;
	const char* what() const noexcept override;
	virtual const char* getType() const noexcept;
	int getLine() const noexcept;
	const std::string& getFile() const noexcept;
	std::string getOriginSTring() const noexcept;

private:
	int line;
	std::string file;
	
protected:
	mutable std::string whatBuffer;
};