#pragma once
#include"../Core.h"

class ChisatoException :std::exception {
private:
	int line;
	std::string file;
protected:
	std::string whatr;

public:
	ChisatoException(int line, const char* file)noexcept:
		line(line),file(file){ }

	constexpr int GetLine() { return line; }
	constexpr std::string& GetFile() { return file; };

	const char* what() const noexcept override;
	
	virtual std::string GetType() const noexcept;
	virtual void GetWhat() noexcept;
	
	std::string GetOriginal() noexcept;
};

class MyException : public ChisatoException {
private:
	std::string information;

public:
	MyException(std::string&& _information,int line,const char* file) : 
		ChisatoException{line,file},
		information{_information} { }
	
	inline std::string GetType() const noexcept override { return""; }
	inline void GetWhat() noexcept override {
		whatr = std::format(
			"[Information]: {}\n {}", 
			information,
			GetOriginal()
		);
	}
};

#define CST_ERROR(s) throw ::Chisato::MyException(s,__LINE__,__FILE__)