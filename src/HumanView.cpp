#include "HumanView.h"


HumanView::HumanView(std::string playerName):
    IEventListener(playerName)
{
    plName = playerName;
}

HumanView::~HumanView()
{
    Logging().log("human view destroyed");
}

bool HumanView::init()
{
    Logging().log("Human View created");
    return true;
}

void HumanView::tick()
{
}

bool HumanView::handleEvent(Event const &event)
{
    return false;
}
