#include <stdlib.h>
#include <stdio.h>
//#include <WinIoCtl.h>
#include <io.h>
#include <fcntl.h>
#include <errno.h>

#include "ModPhpCgi.h"

#include "ScopedLogger.h"
#include "detail/BrefDLL.h"

#ifdef WIN32
#define CLOSE(x)		CloseHandle(x)
#define WRITE(f,b,s)	WriteFile(f,b,s,NULL,NULL)
#define PIPE(x)			_pipe(x, 512, O_BINARY)
#elif
#define CLOSE(x)		close(x)
#define WRITE(f,b,s)	write(f,b,s)
#define PIPE(x)			pipe(x)
#endif

bref::Pipeline::IContentRequestHandler * ModPhpCgiGenerator(const bref::Environment &,
														const bref::HttpRequest &,
														bref::HttpResponse &,
														bref::FdType &);

extern "C" BREF_DLL
bref::AModule *loadModule(bref::ILogger *logger,
                          const bref::ServerConfig &,
                          const bref::IConfHelper &)
{
  LOG_INFO(logger) << "Load module mod_hello";
  return new ModPhpCgi();
}

ModPhpCgi::ModPhpCgi(void)
	: AModule("mod_phpcgi", "", bref::Version(0, 1), bref::Version(0, 3)), priority_(1.f)
{	}


ModPhpCgi::~ModPhpCgi(void)
{	}

void ModPhpCgi::dispose()
{ 
	delete this;
}

void ModPhpCgi::registerHooks(bref::Pipeline & pipeline)
{
	pipeline.contentHooks.push_back(std::make_pair(&ModPhpCgiGenerator, this->priority_));
}

ModPhpCgiRequestHandler::ModPhpCgiRequestHandler(bref::FdType & fdIn, bref::FdType & fdOut)
	: fdIn_(fdIn), fdOut_(fdOut)
{}

ModPhpCgiRequestHandler::~ModPhpCgiRequestHandler()
{}

bool ModPhpCgiRequestHandler::inContent(bref::HttpResponse & response, const bref::Buffer & inBuffer)
{
	if (inBuffer.size() == 0)
	{
		return true;
	}
	return false;
}
bool ModPhpCgiRequestHandler::outContent(bref::HttpResponse & response, bref::Buffer & outBuffer)
{
	return true;
}

void ModPhpCgiRequestHandler::dispose()
{
	delete this;
}

bref::Pipeline::IContentRequestHandler * ModPhpCgiGenerator(const bref::Environment & env, const bref::HttpRequest & req, bref::HttpResponse & response, bref::FdType & fd)
{
	const std::string phpPath = "C:\\Php\\php-5.4.0-Win32-VC9-x86\\php.exe";

	if (req.getUri().compare(req.getUri().size() - 4, 4, ".php") != 0)
		return NULL;

	int fdOut[2];
	int fdIn[2];
	//pid_t pid;

	if (PIPE(fdOut) == -1 || PIPE(fdIn) == -1)
	{
		LOG_ERROR(env.logger) << "[ModPhpCgi]" << strerror(errno);
		response.setStatus(bref::status_codes::InternalServerError);
		return NULL;
	}
	PROCESS_INFORMATION pi;
    STARTUPINFO si;

    // Set up the start up info struct.
    ZeroMemory(&si,sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_USESTDHANDLES;


    //si.hStdOutput = hChildStdOut;
    //si.hStdInput  = hChildStdIn;
    //si.hStdError  = hChildStdErr;
	return new ModPhpCgiRequestHandler();
}
