#include<iostream>
#include<mutex>
#include<deque>

#define LOG_DEBUG(Message, ...) (Logger::Debug(Message, __VA_ARGS__))
#define LOG_INFO(Message, ...) (Logger::Info(Message, __VA_ARGS__))
#define LOG_ERROR(Message, ...) (Logger::Error(Message, __VA_ARGS__))

enum LogPriority
{
	DebugPriority, 
	InfoPriority, 
	ErrorPriority, 
};

class Logger
{
private:
	static isInitialized=false;
	LogPriority priority = InfoPriority;   
	std::mutex log_mutex;
	Handler* handler;
	deque<unique_ptr<string>> dq;
	

public:
	static void SetPriority(LogPriority new_priority)
	{
		get_instance().priority = new_priority;
	}


	static void LoggerInitializer()
	{
		if(!isInitialized)
		{
			isInitialized=true;
			Logger& logger_instance = get_instance();
			 //Based on different log storages (file, console, DB, HTTP, etc.) we can fetch corressponding Handler.
			logger_instance.handler=LogStorage::getHandler();
			startWorkerThread();
		}
		
	}
	


	template<typename... Args>
	static void Debug(const char* message, Args... args)
	{
		get_instance().log("[Debug]\t", DebugPriority, message, args...);
	}

	template<typename... Args>
	static void Info(const char* message, Args... args)
	{
		get_instance().log("[Info]\t", InfoPriority, message, args...);
	}
	
	template<typename... Args>
	static void Error(const char* message, Args... args)
	{
		get_instance().log("[Error]\t", ErrorPriority, message, args...);
	}


private:
	Logger() {}
	Logger(const Logger&) = delete;
	Logger& operator= (const Logger&) = delete;

	~Logger()
	{
		if(handler)
			free_handler();		
	}

	static Logger& get_instance()
	{
		static Logger logger;
		return logger;
	}
	
	void logwriter()
	{
		while(1)
		{
			unique_lock<mutex> ul(mu);
			cv.wait([](){ !dq.empty()});
			handler.write(dq[0]);         // handler.write is write function in handler class which will be extended in every log storage classs(file/db/http/console);
			dq.pop_front();
			ul.unlock();
		}
		
	}
	void startWorkerThread()
	{
		thread t(logWriter);
		
		t.join();
	}

	template<typename... Args>
	void log(const char* message_priority_str, LogPriority message_priority, const char* message, Args... args)
	{
		if (priority <= message_priority)
		{
			sstringstream str;
			str << buffer;
			str << message_priority_str;
			str << message;
			str << args...;
			str << endl;
			{
				lock_guard lock(log_mutex);     //This lock is essiential.
				dq.push_back(new string(str.c_str()));
			}
		}
	}
};


