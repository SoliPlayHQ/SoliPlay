#include <plugins_system/plugin_type.h>

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

	void ObjectPlugin::hookLoad(void) {
		createInstance_ = (CreateInstanceFunc)getFuncAddress("createInstance");
		destroyInstance_ = (DestroyInstanceFunc)getFuncAddress("destroyInstance");

		hookObjectLoad();
	}

	void ObjectPlugin::hookUnload(void) {
		createInstance_ = nullptr;
		destroyInstance_ = nullptr;

		hookObjectUnload();
	}
}
