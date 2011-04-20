#ifndef HPP_INOTIFY_PRIMARY
#define HPP_INOTIFY_PRIMARY

#include <sys/inotify.h>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "INotifyListener.hpp"

using namespace std;

typedef map<int, string> WatchMap;
typedef function<void(const string& source, const string& path, const inotify_event&)> NotifyListener;

class INotify
{
public:
	INotify();
	~INotify();

	void watch(const string& path, const int& bitmask);
	void watch(const string& path);
	bool hasWatch(const string& path);
	void readEvents();
	void removeWatch(const string& path);

	void addListener(const NotifyListener& listener);
	bool removeListener(const NotifyListener& listener);
protected:

	void dispatchEvent(const inotify_event& event);
	int getWatchFD(const string& path);
private:
	static const int EVENT_SIZE = sizeof(inotify_event);
	static const int BUF_LEN = 1024*(EVENT_SIZE+16);

	const int fd;
	map<const int, string> watches;
	vector<INotifyListener*> listeners;
	char buffer[BUF_LEN];
};

#endif
