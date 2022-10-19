#pragma once
#include <Windows.h>
#include <iostream>
#include <Psapi.h>
#include <vector>

#define INRANGE(x, a, b) (x >= a && x <= b)
#define getBits(x) (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte(x) (getBits(x[0]) << 4 | getBits(x[1]))

template<typename T>
class sig_scan
{
	sig_scan() {
		pointer = NULL;
		moduleHandle = nullptr;
	}
	uintptr_t pointer;
	HMODULE moduleHandle;
	int sig_size(const char* signature) {
		int count = 0, i = 0;
		char ch = signature[0];
		while (ch != ' ') {
			ch = signature[i];
			if (isspace(ch))
				count++;
			i++;
		}
		return count;
	}
	uintptr_t find_sig(uintptr_t pStart, uintptr_t pEnd, const char* signature) {
		const char* pattern = signature;
		uintptr_t pFirstMatch = 0;
		for (uintptr_t i = pStart; i < pEnd; i++) {
			if (!*pattern) return pFirstMatch;
			if (*(PBYTE)pattern == '\?' || *(BYTE*)i == getByte(pattern))
			{
				if (!pFirstMatch) pFirstMatch = i;
				if (!pattern[2]) return pFirstMatch;
				if (*(PWORD)pattern == '\?\?' || *(PBYTE)pattern != '\?') pattern += 3;
				else pattern += 2;
			}
			else
			{
				pattern = signature;
				pFirstMatch = 0;
			}
		}
		return 0;
	}
	uintptr_t find_sigs(const char* signature, size_t index) {
		MODULEINFO moduleInfo;
		GetModuleInformation(GetCurrentProcess(), moduleHandle, &moduleInfo, sizeof(MODULEINFO));
		uintptr_t pStart = uintptr_t(moduleInfo.lpBaseOfDll);
		uintptr_t pEnd = pStart + moduleInfo.SizeOfImage;

		std::vector<uintptr_t> results;
		int signatureSize = sig_size(signature);

		while (true) {
			uintptr_t result = find_sig(pStart, pEnd, signature);
			if (result != 0) {
				results.push_back(result);
				pStart = result + signatureSize;
			}
			else
				break;

			if (results.size() > index)
				return results[index];
		}

		return 0;
	}
public:
	sig_scan(const char* signature, size_t index, HMODULE module) {
		moduleHandle = module;
		pointer = find_sigs(signature, index);
	}
	sig_scan(const char* signature, HMODULE module) : sig_scan(signature, 0, module) {}
	operator T () {
		return (T)pointer;
	}
	operator uintptr_t () {
		return pointer;
	}
	sig_scan<T> offset_ptr(int32_t value) {
		sig_scan<T> result;
		if (this->pointer != 0) {
			result.pointer = this->pointer;
			return result.offset(value).resolve_ptr();
		}
		return result;
	}
	sig_scan<T> offset(int32_t value) {
		sig_scan<T> result;
		if (this->pointer != 0) {
			result.pointer = this->pointer + value;
		}
		return result;
	}
	sig_scan<T> resolve_call() {
		sig_scan<T> result;
		if (this->pointer != 0) {
			int32_t pOffset = *(int32_t*)(this->pointer + 0x01);
			result.pointer = this->pointer + pOffset + 0x05;
		}
		return result;
	}
	sig_scan<T> resolve_ptr() {
		sig_scan<T> result;
		if (this->pointer != 0) {
			result.pointer = *(uint32_t*)(this->pointer);
		}
		return result;
	}
};