//
//  Scanner.hpp
//
//  Created by Andre Kalisch on 23.09.16.
//  Copyright © 2016 Andre Kalisch. All rights reserved.
//
//  Edited by Fricker95 on 1/1/20.

#pragma once
#ifndef Scanner_hpp
#define Scanner_hpp

#include "MemMngr.hpp"

#include <sstream>

class Scanner {
public:
    Byte* pRemote = nullptr;
    const char * module = nullptr;
    size_t bufferSize;
    uint64_t moduleStart;
	MemMngr* mem = nullptr;
    
    explicit Scanner(uint64_t dwStart, size_t dwSize, MemMngr* mem = nullptr){
		this->readBuffer(dwStart, dwSize);
		this->mem = mem;
	}
    
    ~Scanner() {
        if (!pRemote) {
            delete[] pRemote;
        }
    }

	void readBuffer(uint64_t dwStart, uint64_t dwSize){
		pRemote = new Byte[dwSize];
		bufferSize = dwSize;
		moduleStart = dwStart;
		pRemote = mem->readData(moduleStart, bufferSize);
	}

	bool MaskCheck(int nOffset, Byte* btPattern, const char* strMask, int sigLength){
		for (int i = 0; i < sigLength; i++){
			if (strMask[i] == '?')
				continue;
			if ((strMask[i] == 'x') && (btPattern[i] != pRemote[nOffset + i]))
				return false;
		}
		return true;
	}

	uint64_t Scan(Byte* pSignature, const char* pMask, int sigLength){
		if (!pRemote)
			return NULL;
		for (int i = 0; i < bufferSize; i++){
			if (MaskCheck(i, pSignature, pMask, sigLength))
				return moduleStart + i;
		}
		return NULL;
	}

	uint32_t getOffset(Byte* pSignature, const char* pMask, uint64_t start){
		uint64_t signatureAddress = this->Scan(pSignature, pMask, (int)strlen(pMask)) + start;
		uint32_t foundOffset = mem->read<uint32_t>(signatureAddress);
		return foundOffset;
	}

	uint32_t getPointer(Byte* pSignature, const char* pMask, uint32_t start){
		uint64_t signatureAddress = this->Scan(pSignature, pMask, (int)strlen(pMask)) + start;
		uint64_t fileOffset = signatureAddress - moduleStart;
		uint32_t foundOffset = mem->read<uint32_t>(signatureAddress) + (uint32_t)fileOffset;
		return foundOffset;
	}
};


#endif
