#include "http.h"
#include <string.h>

using namespace std;

const char* statusMsg(int stat){
    switch(stat){
        case 200: return "200 OK";
        case 303: return "303 See Other";
        case 403: return "403 Forbidden";
        case 404: return "404 Not Found";
        case 500: return "500 Server Error";
    }
    return "";
}

string Http::header(int status){
    string msg = statusMsg(status);
    return (msg.empty() ? "\n\n" : "Status: " + msg + "\n\n");
}

string Http::header(const string &type, int status){
    return "Content-Type: " + type + "; charset=UTF-8\n" + header(status);
}

string Http::redirect(const string &location){
    return "Location: " + location + "\n" + header(303);
}

string httpFilename(const string &str){
    string buf;
    for(string::const_iterator i=str.begin(); i!=str.end(); i++){
        if(strchr("/\\?%*:|\"<>", *i) != 0);
        else buf += *i;
    }
    return buf;
}

string Http::download(const string &path, const string &filename, const string &mime, bool attachment){
    return (string)
        "X-Accel-Redirect: " + path + "\n"
        "Content-Disposition: " + (attachment?"attachment":"inline") + "; filename=\"" + httpFilename(filename) +"\"\n"
        "Content-Type: " + mime + "\n\n";
}
