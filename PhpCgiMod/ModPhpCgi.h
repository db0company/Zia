#pragma once

#ifndef MODPHPCGI_H__
#define MODPHPCGI_H__

#include "AModule.h"

class ModPhpCgi : public bref::AModule
{
private:
  const float       priority_;

public:
	ModPhpCgi(void);
	virtual ~ModPhpCgi(void);
	virtual void dispose();
	virtual void registerHooks(bref::Pipeline & pipeline);

};

struct ModPhpCgiRequestHandler : public bref::Pipeline::IContentRequestHandler
{
	bref::FdType & fdIn_;
	bref::FdType & fdOut_;

	ModPhpCgiRequestHandler(bref::FdType &, bref::FdType &);
	virtual ~ModPhpCgiRequestHandler();
	virtual bool inContent(bref::HttpResponse &, const bref::Buffer &);
	virtual bool outContent(bref::HttpResponse &, bref::Buffer &);
	virtual void dispose();
};

#endif