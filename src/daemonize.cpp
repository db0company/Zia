/*
 * daemonize.cpp for zia
 * by lenorm_f
 */

#ifndef _WIN32
void daemonize() {
	pid_t pid = ::fork();

	if (pid < 0)
		::exit(EXIT_FAILURE);
	else if (pid > 0)
		::exit(EXIT_SUCCESS);

	::umask(0);

	if (::setsid() < 0)
		::exit(EXIT_FAILURE);

	if ((::chdir("/")) < 0)
		::exit(EXIT_FAILURE);

	::close(STDIN_FILENO);
	::close(STDOUT_FILENO);
	::close(STDERR_FILENO);
}
#else
#warning "The daemonize function has only been implemented for UNIX systems"
void daemonize() {}
#endif
