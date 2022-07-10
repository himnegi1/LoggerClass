class Handler
{
	virtual Handler* getHandler()=0;
	virtual void write()=0;
	virtual void freeHandler()=0;
};

class DBHandler : public Handler
{
	DBHandler* getHandler() { return dbHandle ; } 
	void write() {} 
	void freeHandle() { if(this) { free(this) ; } ;
}

class FileHandler : public Handler
{
	FileHandler* getHandler() { return fileHandle ; } 
	void write() {} 
	void freeHandle() { if(this) { free(this) ; } ;
}

class HttpHandler : public Handler
{
	HttpHandler* getHandler() { return httpHandle ; } 
	void write() {} 
	void freeHandle() { if(this) { free(this) ; } ;
}

class ConsoleHandler : public Handler
{
	handle* getHandler() { return consoleHandle ; } 
	void write() {} 
	void freeHandle() { if(this) { free(this) ; } ;
}
