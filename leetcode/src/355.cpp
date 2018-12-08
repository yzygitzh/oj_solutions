class Twitter {
public:
    unordered_map<int, vector<pair<int, int> > > tweets;
    unordered_map<int, set<int> > follows;
    int ts = 0;
    
    /** Initialize your data structure here. */
    Twitter() {
        
    }
    
    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        tweets[userId].push_back(make_pair(ts, tweetId));
        ts++;
    }
    
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        map<int, int> tweetIdx;
        set<int> seeIds(follows[userId].begin(), follows[userId].end());
        seeIds.insert(userId);
        priority_queue<pair<int, pair<int, int> > > latestTweets;
        vector<int> result;

        // init heap
        for (set<int>::iterator itr = seeIds.begin();
                 itr != seeIds.end(); ++itr) {
            if (tweetIdx[*itr] < tweets[*itr].size()) {
                int latestIdx = tweets[*itr].size() - tweetIdx[*itr] - 1;
                // <ts, <tweetId, userId>>
                latestTweets.push(make_pair(tweets[*itr][latestIdx].first,
                                            make_pair(tweets[*itr][latestIdx].second, *itr)));
                tweetIdx[*itr]++;
            }
        }
        
        while (result.size() < 10 && !latestTweets.empty()) {
            pair<int, pair<int, int> > latest = latestTweets.top();
            latestTweets.pop();
            result.push_back(latest.second.first);
            int userId = latest.second.second;
            if (tweetIdx[userId] < tweets[userId].size()) {
                int latestIdx = tweets[userId].size() - tweetIdx[userId] - 1;
                latestTweets.push(make_pair(tweets[userId][latestIdx].first,
                                            make_pair(tweets[userId][latestIdx].second, userId)));
                tweetIdx[userId]++;
            }
        }
        
        return result;
    }
    
    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        if (followerId != followeeId) follows[followerId].insert(followeeId);
    }
    
    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        follows[followerId].erase(followeeId);
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter obj = new Twitter();
 * obj.postTweet(userId,tweetId);
 * vector<int> param_2 = obj.getNewsFeed(userId);
 * obj.follow(followerId,followeeId);
 * obj.unfollow(followerId,followeeId);
 */