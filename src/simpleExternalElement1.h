
#ifndef _SIMPLE_EXTERNAL_ELEMENT_H
#define _SIMPLE_EXTERNAL_ELEMENT_H

#include <sst/core/component.h>
#include <sst/core/link.h>
#include <sst/core/elementinfo.h>

class SimpleExternalElement1 : public SST::Component {

public:
	SimpleExternalElement1( SST::ComponentId_t id, SST::Params& params );
	~SimpleExternalElement1();

	void setup();
	void finish();

	bool clockTick( SST::Cycle_t currentCycle );

    void handleEvent(SST::Event *ev);

	SST_ELI_REGISTER_COMPONENT(
		SimpleExternalElement1,
		"simpleExternalElement",
		"SimpleExternalElement1",
		SST_ELI_ELEMENT_VERSION( 1, 0, 0 ),
		"Demonstration of an External Element for SST",
		COMPONENT_CATEGORY_PROCESSOR
	)

	SST_ELI_DOCUMENT_PARAMS(
		{ "printFrequency", "How frequently to print a message from the component", "5" },
		{ "repeats", "Number of repetitions to make", "10" }
	)

    SST_ELI_DOCUMENT_PORTS(
        { "port", "Port on which to send/recv messages", {"sst.Interfaces.StringEvent"}}
    )

private:
	SST::Output output;
	SST::Cycle_t printFreq;
	SST::Cycle_t maxRepeats;
	SST::Cycle_t repeats;

    SST::Link *port;
};


#endif
