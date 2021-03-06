//
//  ColorText.hpp
//  Wall
//
//  Created by Fricker95 on 1/1/20.
//  Copyright © 2020 Fricker95. All rights reserved.
//

#ifndef COLORTEXT_HPP
#define COLORTEXT_HPP

#include <iostream>
#include <string>

namespace cT {
	namespace {
		static const char* init		= "\x1b[";
		static const char* term 	= "m";
	};
	namespace fG {
		static const char* black 	= "30";
		static const char* red 		= "31";
		static const char* green 	= "32";
		static const char* yellow	= "33";
		static const char* blue 	= "34";
		static const char* magenta 	= "35";
		static const char* cyan 	= "36";
		static const char* white 	= "37";
		static const char* defaultc = "39";
	};
	
	namespace bG {
		static const char* black 	= "40";
		static const char* red 		= "41";
		static const char* green 	= "42";
		static const char* yellow 	= "43";
		static const char* blue 	= "44";
		static const char* magenta 	= "45";
		static const char* cyan 	= "46";
		static const char* white 	= "47";
	};
	
	namespace sT {
		static const char* normal 	= "0";
		static const char* bold 	= "1";
		static const char* dim 		= "2";
	};
	
	inline std::string getColor(const char* forground = fG::defaultc, const char* background = "")
	{
		std::string str;
		str += init;
		str += forground;
		
		bool cmp = strcmp(background, "");
		
		str += (cmp ? ";": "");
		str += (cmp ? background: "");
		
		str += term;
		return str;
	}
	
	inline std::string getStyle(const char* style = sT::normal)
	{
		std::string str;
		str += init;
		str += style;
		str += term;
		
		bool cmp = strcmp(style, sT::normal);
		
		str += (cmp ? init: "");
		str += (cmp ? sT::normal: "");
		str += (cmp ? term: "");
		
		return str;
	}
	
	inline std::string print(const char* text, const char* forground = fG::defaultc, const char* style = sT::normal, const char* background = "")
	{
		std::string str;
		str += getColor(forground, background);
		str += text;
		str += getStyle(style);
		return str;
	}
};

#endif /* COLORTEXT_HPP */
