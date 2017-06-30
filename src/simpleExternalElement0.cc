
#include <sst/core/sst_config.h>
#include <sst/core/interfaces/stringEvent.h>
#include "simpleExternalElement0.h"

using SST::Interfaces::StringEvent;

SimpleExternalElement0::SimpleExternalElement0( SST::ComponentId_t id, SST::Params& params ) :
	SST::Component(id), repeats(0) {

	output.init("SimpleExternalElement0-" + getName() + "-> ", 1, 0, SST::Output::STDOUT);

	printFreq  = params.find<SST::Cycle_t>("printFrequency", 5);
	maxRepeats = params.find<SST::Cycle_t>("repeats", 10);

	if( ! (printFreq > 0) ) {
		output.fatal(CALL_INFO, -1, "Error: printFrequency must be greater than zero.\n");
	}

	output.verbose(CALL_INFO, 1, 0, "Config: maxRepeats=%" PRIu64 ", printFreq=%" PRIu64 "\n",
		static_cast<uint64_t>(maxRepeats), static_cast<uint64_t>(printFreq));

	// Just register a plain clock for this simple example
    registerClock("100MHz", new SST::Clock::Handler<SimpleExternalElement0>(this, &SimpleExternalElement0::clockTick));
    // Configure our port
    port = configureLink("port",
            new SST::Event::Handler<SimpleExternalElement0>(this, &SimpleExternalElement0::handleEvent));
    if ( !port ) {
        output.fatal(CALL_INFO, -1, "Failed to configure port 'port'\n");
    }

	// Tell SST to wait until we authorize it to exit
    registerAsPrimaryComponent();
    primaryComponentDoNotEndSim();
}

SimpleExternalElement0::~SimpleExternalElement0() {

}

void SimpleExternalElement0::setup() {
	output.verbose(CALL_INFO, 1, 0, "Component is being setup.\n");
}

void SimpleExternalElement0::finish() {
	output.verbose(CALL_INFO, 1, 0, "Component is being finished.\n");
}

bool SimpleExternalElement0::clockTick( SST::Cycle_t currentCycle ) {

	if( currentCycle % printFreq == 0 ) {
		output.verbose(CALL_INFO, 1, 0, "Hello World!\n");
	}

	repeats++;

    port->send(new StringEvent(getName() + " Hello #" + std::to_string(repeats)));

	if( repeats == maxRepeats ) {
		primaryComponentOKToEndSim();
		return true;
	} else {
		return false;
	}
}

void SimpleExternalElement0::handleEvent(SST::Event *ev) {
    StringEvent *se = dynamic_cast<StringEvent*>(ev);
    if ( se != NULL ) {
        output.output("%s recevied an event: \"%s\"\n", getName().c_str(), se->getString().c_str());
    }
    delete ev;
}
