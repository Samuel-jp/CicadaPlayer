//
// Created by moqi on 2018/4/28.
//

#ifndef FRAMEWORK_SEGMENTTRACKER_H
#define FRAMEWORK_SEGMENTTRACKER_H

#include "Representation.h"
#include "data_source/IDataSource.h"
#include "utils/afThread.h"
#include <mutex>
#include <base/OptionOwner.h>

using namespace std;

namespace Cicada {

    class AlivcDataSource;
    class segment;

    class SegmentTracker : public OptionOwner {
    public:
        explicit SegmentTracker(Representation *rep, const IDataSource::SourceConfig &sourceConfig);

        ~SegmentTracker();

        int init();

        std::shared_ptr<segment> getNextSegment();

        std::shared_ptr<segment> getCurSegment();

        int getStreamType() const;

        const string getBaseUri();

        int getStreamInfo(int *width, int *height, uint64_t *bandwidth, std::string &language);

        string getDescriptionInfo();

        bool getSegmentNumberByTime(uint64_t &time, uint64_t &num);

        void print();

        int64_t getDuration();

        int reLoadPlayList();

        bool isLive();

        void interrupt(int inter);

        bool isInited();

        void setCurSegNum(uint64_t num)
        {
            mSeeked = true;
            mCurSegNum = num;
        }

        uint64_t getCurSegNum()
        {
            return mCurSegNum;
        }

        uint64_t getCurSegPosition();

        void setCurSegPosition(uint64_t position);

        uint64_t getFirstSegNum();

        uint64_t getLastSegNum();

        uint64_t getSegSize();

        string getPlayListUri();

        int GetRemainSegmentCount();

        bool isSeeked()
        {
            return mSeeked.load();
        }
        
        bool isRealTimeStream() { return mRealtime; }

        void MoveToLiveStartSegment(const int64_t liveStartIndex);

        int64_t getTargetDuration();

    private:
        int loadPlayList();

        int threadFunction();

    private:
        Representation *mRep;
        playList *mPPlayList = nullptr;
        uint64_t mCurSegNum = 0;
        uint64_t mCurSegPos = 0;

        std::string mLocation = "";
        std::atomic<int64_t> mTargetDuration{0};
        std::atomic<int64_t> mPartTargetDuration{0};

        int64_t mLastLoadTime = 0;
        bool playListOwnedByMe = false;

        bool mInited = false;

        std::atomic_bool mNeedUpdate{false};
        std::atomic_bool mStopLoading{false};

        std::mutex mSegMutex;
        std::condition_variable mSegCondition;
        afThread *mThread = nullptr;

        IDataSource *mPDataSource = nullptr;
        bool mInterrupted = false;

        IDataSource::SourceConfig mSourceConfig;
        std::recursive_mutex mMutex;

        std::atomic_int mPlayListStatus{0};

        std::atomic_bool mSeeked{false};
        
        bool mRealtime = false;

        int64_t mReloadErrorStartTime{INT64_MIN};
    };
}


#endif //FRAMEWORK_SEGMENTTRACKER_H
