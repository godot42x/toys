#include "helper.h"

struct IInterviewer {
    virtual fn askQuestions() -> void = 0;
    virtual ~IInterviewer()           = default;
};

struct Developer : IInterviewer {
    fn askQuestions() -> void override
    {
        debug(), "Developer", "Asking about design patterns, data structures, and algorithms.";
    }
};

struct CommunityExecutive : IInterviewer {
    fn askQuestions() -> void override
    {
        debug(), "Community Executive", "Asking about community building and events.";
    }
};

struct IHiringManager {
    virtual fn makeInterviewer() -> IInterviewer * = 0;

    fn takeInterview() -> void
    {
        auto interviewer = makeInterviewer();
        interviewer->askQuestions();
        delete interviewer;
    }
};

struct DevelopmentManager : IHiringManager {
    fn makeInterviewer() -> IInterviewer * override { return new Developer(); }
};

struct MarketingManager : IHiringManager {
    fn makeInterviewer() -> IInterviewer * override { return new CommunityExecutive(); }
};


fn main(int argc, char **argv) -> int
{
    auto devManager = DevelopmentManager();
    devManager.takeInterview();

    auto markManager = MarketingManager();
    markManager.takeInterview();

    return 0;
}