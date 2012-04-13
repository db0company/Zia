#pragma once

#ifndef MODHELLOWORLD_H__
#define MODHELLOWORLD_H__

#include "AModule.h"

class ModHelloWorld : public bref::AModule
{
private:
  static const float       ModulePriority;

public:
  ModHelloWorld();
  virtual ~ModHelloWorld();
  virtual void dispose();
  virtual void registerHooks(bref::Pipeline & pipeline);
};

/*
  Request handler for the ModHello module.
*/
struct ModHelloWorldRequestHandler : public bref::Pipeline::IContentRequestHandler
{
  ModHelloWorldRequestHandler();
  virtual ~ModHelloWorldRequestHandler();
  virtual bool inContent(bref::HttpResponse &, const bref::Buffer &);
  virtual bool outContent(bref::HttpResponse &, bref::Buffer &);
  virtual void dispose();
};

#endif

