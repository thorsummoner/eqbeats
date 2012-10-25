#ifndef COMMENT_H
#define COMMENT_H

#include <string>
#include <vector>
class User;

class Comment {

    public:

        Comment(){ authorId = 0; type = Undefined; trackId = 0; }
        enum Type { Undefined, Track, User, News };

        Type type;
        std::string contents;
        int authorId;
        std::string _authorName;
        std::string authorName() const{ return _authorName.empty()? "Anonymous" : _authorName; }

        int trackId;
        std::string trackTitle;

        Comment(int nAuthorId, const std::string &nContents, const std::string &nAuthorName, Type nType, int nTrackId = 0,
                const std::string &nTrackTitle = "")
            { authorId = nAuthorId; contents = nContents; _authorName = nAuthorName; type = nType; trackId = nTrackId;
              trackTitle = nTrackTitle; }

};

#endif // COMMENT_H