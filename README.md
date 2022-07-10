# LoggerClass
asynchronous thread-safe logger class

Implement an asynchronous thread-safe logger class that can be configured and extensible with different log storages.
1. The logger shall not block a calling thread.
2. The logger shall be safe to use from different threads.
3. The logging part shall be configurable to use different log storages (file, console, DB, HTTP, etc.)
4. Only the file storage should be implemented as part of this task.
5. The class shall implement unique ownership.
6. Only C++11 and later standards shall be used.
