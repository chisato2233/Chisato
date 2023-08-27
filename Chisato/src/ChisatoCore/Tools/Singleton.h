
namespace cst {
	template<typename T>
	struct Singleton {
	protected:
		static T* handle;
		
		Singleton() { }
	
	public:
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
		
		static T& get() {
			if (!handle) handle = std::make_unique<T>();
			return *handle;
		}
	};
}