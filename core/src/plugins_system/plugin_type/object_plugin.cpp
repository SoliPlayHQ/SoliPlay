#include <plugins_system/plugin_type/plugin_type.h>
#include <plugins_system/host_api/host_api.h>
#include <log_system.h>

namespace SPPlugin {
	/*
	class ObjectPlugin : public Plugin {
	public:
		ObjectPlugin();
		~ObjectPlugin() = default;

		SOLI_PLUGIN_INSTANCE createInstance();
		void destroyInstance(SOLI_PLUGIN_INSTANCE instance);
	protected:
		// 来自子类的钩子函数
		void hookLoad(void);
	private:
		CreateInstanceFunc createInstance;
		DestroyInstanceFunc destroyInstance;
	};
	*/

	ObjectPlugin::ObjectPlugin(PluginMeta meta) : Plugin(meta) {
		
	}

	

	SOLI_PLUGIN_INSTANCE ObjectPlugin::createInstance() {
		return createInstance_(SPHost::getHostAPI());
	}

	void ObjectPlugin::destroyInstance(SOLI_PLUGIN_INSTANCE instance) {
		destroyInstance_(instance);
	}

	void ObjectPlugin::hookLoad(void) {
		createInstance_ = (CreateInstanceFunc)getFuncAddress("createInstance");
		SPLog::trace(std::format("{}'s createInstance in {}", getMeta().name, getFuncAddress("createInstance")));
		destroyInstance_ = (DestroyInstanceFunc)getFuncAddress("destroyInstance");
		SPLog::trace(std::format("{}'s destroyInstance in {}", getMeta().name, getFuncAddress("destroyInstance")));
		hookObjectLoad();
	}

	void ObjectPlugin::hookUnload(void) {
		hookObjectUnload();

		createInstance_ = nullptr;
		destroyInstance_ = nullptr;
	}
}
