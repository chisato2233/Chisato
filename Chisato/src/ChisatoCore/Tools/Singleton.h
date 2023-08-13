
namespace Chisato {
	template<typename T>
	struct Singleton {
	protected:
		static std::unique_ptr<T> handle;
		
		Singleton() { }
	
	public:
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
		
		static T& Get() {
			if (!handle) handle = std::make_unique<T>();
			return *handle;
		}
	};
}