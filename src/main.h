#include <iostream>
#include "ProcManager.h"
#include "DataModel.h"
#include "SDLView.h"
#include "Event_System.h"
#include "Evt_CloseApplication.h"
#include "Evt_CloseWindow.h"
#include "Evt_Keyboard.h"
#include "Evt_WindowFocus.h"
#include "ApplicationController.h"
#include <boost/shared_ptr.hpp>
#include <json/json.h>
#include <fstream>
#include "SDLInjector.h"
#include "MsgEvt.h"
#include "DebugOutput.h"
#include "DataController.h"
#include <ctime>
#include <time.h>


