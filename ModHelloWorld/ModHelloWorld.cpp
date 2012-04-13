#include "ModHelloWorld.h"
#include "ScopedLogger.h"
#include "detail/BrefDLL.h"

#include <utility>

const float       ModHelloWorld::ModulePriority = 0.f; // Low priority

extern "C" BREF_DLL
bref::AModule *loadModule(bref::ILogger *logger,
                          const bref::ServerConfig &,
                          const bref::IConfHelper &)
{
  LOG_INFO(logger) << "Load module mod_hello";
  return new ModHelloWorld();
}

ModHelloWorld::ModHelloWorld()
  : AModule("mod_hello", "Retourne un body avec \"Hello world\".", bref::Version(0, 1), bref::Version(0, 3))
{ }

ModHelloWorld::~ModHelloWorld()
{ }

/*
  La m�moire allou�e dans une librairies dynamique par la m�thode
  loadModule(), doit �tre nettoy�e dans cette m�me librairie
  dynamique.
*/
void ModHelloWorld::dispose()
{
  delete this;
}

namespace {

/*
  Un vrai module (utile) utiliserais au moins la "request" mais ce
  n'est pas l'objectif de cette demo.
*/
bref::Pipeline::IContentRequestHandler *
modHelloWorldGenerator(const bref::Environment & /* environment */,
                  const bref::HttpRequest & /* request */,
                  bref::HttpResponse & /* response */,
                  bref::FdType & /* fd */)
{
  return new ModHelloWorldRequestHandler();
}

} // ! unnamed namespace

/*
  Enregistrement des points de hook dans la pipeline.
*/
void ModHelloWorld::registerHooks(bref::Pipeline & pipeline)
{
  pipeline.contentHooks.push_back(std::make_pair(&modHelloWorldGenerator,
                                                 ModHelloWorld::ModulePriority));
}

ModHelloWorldRequestHandler::ModHelloWorldRequestHandler()
{ }

ModHelloWorldRequestHandler::~ModHelloWorldRequestHandler()
{ }

bool ModHelloWorldRequestHandler::inContent(bref::HttpResponse & response,
                                       const bref::Buffer & inBuffer)
{
  // Non utilis�e ici, on s'en fiche de ce que l'utilisateur nous envoie...
  // Du coup on retourne "true" pour ne pas �tre rappel�.
  return true;
}

bool ModHelloWorldRequestHandler::outContent(bref::HttpResponse & response,
                                        bref::Buffer &       outBuffer)
{
  // HTTP/1.1
  response.setVersion(bref::Version(1, 1));

  // On retourne 200 "OK"
  response.setStatus(bref::status_codes::OK);
  response.setReason("OK");

  // On ins�re notre body dans le buffer de sortie
  const std::string hw = "Hello World !";
  outBuffer.insert(outBuffer.end(), hw.begin(), hw.end());

  // On connait la taille de notre body, on l'insert dans le header de r�ponse
  response["Content-Length"] = bref::BrefValue(static_cast<int>(hw.size()));

  // On n'a pas besoin d'�tre rapell� vu qu'on a retourn� l'ensemble
  // de notre corps.
  return true;
}

void ModHelloWorldRequestHandler::dispose()
{
  delete this;
}
