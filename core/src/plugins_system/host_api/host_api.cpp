#include <plugins_system/host_api/host_api.h>
#include <plugins_system/host_api/host_api_log.h>

namespace SPHost {
	static SoliHostAPI host_api;

	void initHostAPI(void) {
		initLogAPI();
		host_api.log = getLogAPI();
	}

	const SoliHostAPI& getHostAPI(void) {
		return host_api;
	}
}