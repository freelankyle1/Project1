#include "Headers/pch.h"
#include "Headers/asserts.h"

void reportAssertionFailure(HRESULT hr, const char* error, const char* file, int line)
{
	std::ostringstream oss;

	_com_error comError(hr);
	const TCHAR* errorText = comError.ErrorMessage();

	oss << "\n[EXPR]: " << error;
	oss << "\n[FILE NAME]: " << file;
	oss << "\n[LINE]: " << line;
	oss << "\n[ERROR CODE]: " << std::hex << "0x" << hr << "\n" << errorText;

	std::string errorMsg = oss.str();
	const char* pErrorMsg = errorMsg.c_str();

	MessageBox(0, pErrorMsg, "FAILURE", MB_ICONERROR);

}