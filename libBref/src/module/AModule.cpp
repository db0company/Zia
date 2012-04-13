#include "AModule.h"

bref::AModule::AModule(const std::string & name,
            const std::string & description,
            const Version & version,
            const Version & minimumApiVersion)
			: name_(name), description_(description), version_(version), minimumApiVersion_(minimumApiVersion)
{}
const std::string & bref::AModule::name() const { return name_; }
const std::string & bref::AModule::description() const { return description_; }
const bref::Version & bref::AModule::version() const { return version_; }
const bref::Version & bref::AModule::minimumApiVersion() const { return minimumApiVersion_;}
