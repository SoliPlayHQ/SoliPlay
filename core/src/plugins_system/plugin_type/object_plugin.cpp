#include <plugins_system/plugin_type/plugin_type.h>
#include <plugins_system/host_api/host_api.h>
#include <log_system.h>

namespace SPPlugin {
	ObjectPlugin::ObjectPlugin(PluginMeta meta) : Plugin(meta) {
		alive_ = false;
	}

	bool ObjectPlugin::isAlive(void) {
		return alive_;
	}
	
	SOLI_PLUGIN_INSTANCE ObjectPlugin::createInstance() {
		if (alive_) {
			std::lock_guard<std::mutex> lock(mtxInstances_);
			instances_.push_back(createInstance_(SPHost::getHostAPI()));
			return *(instances_.end() - 1);
		}
	}

	void ObjectPlugin::destroyInstance(SOLI_PLUGIN_INSTANCE instance) {
		if (alive_) {
			std::lock_guard<std::mutex> lock(mtxInstances_);
			for (auto i = instances_.begin(); i < instances_.end(); ++i)
				if (instance == *i) {
					destroyInstance_(instance);
					instances_.erase(i);

					break;
				}
		}
	}

	void ObjectPlugin::hookLoad(void) {
		alive_ = true;
		createInstance_ = (CreateInstanceFunc)getFuncAddress("createInstance");
		SPLog::trace(std::format("{}'s createInstance in {}", getMeta().name, getFuncAddress("createInstance")));
		destroyInstance_ = (DestroyInstanceFunc)getFuncAddress("destroyInstance");
		SPLog::trace(std::format("{}'s destroyInstance in {}", getMeta().name, getFuncAddress("destroyInstance")));
		hookObjectLoad();
	}

	void ObjectPlugin::hookUnload(void) {
		alive_ = false;
		hookObjectUnload();

		{
			std::lock_guard<std::mutex> lock(mtxInstances_);
			for (auto i : instances_) {
				destroyInstance_(i);
			}
		}

		createInstance_ = nullptr;
		destroyInstance_ = nullptr;
	}
}
